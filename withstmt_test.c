#include <stdio.h>

#include <error.h>
#include <test.h>
#include <withstmt.h>

struct null_lock {
    int id, num_locks, num_unlocks;
};

void nl_lock(struct null_lock *lock) {
    lock->num_locks++;
    printf("Locking lock %d (now %d locks, %d unlocks).\n",
           lock->id, lock->num_locks, lock->num_unlocks);
}

void nl_unlock(struct null_lock *lock) {
    lock->num_unlocks++;
    printf("Unlocking lock %d (now %d locks, %d unlocks).\n",
           lock->id, lock->num_locks, lock->num_unlocks);
}

int main(void) {
    struct null_lock lock1, lock2;

    lock1.num_locks = lock1.num_unlocks =
        lock2.num_locks = lock2.num_unlocks = 0;
    lock1.id = 1;
    lock2.id = 2;

    printf("Start!\n");

    with(lock1, nl_lock, nl_unlock, {
            _assert(lock1.num_locks == 1);
            _assert(lock1.num_unlocks == 0);
            printf("Look, ma!  Lock 1 is locked!\n");
        });

    _assert(lock1.num_locks == 1);
    _assert(lock1.num_unlocks == 1);

    printf("Unlocked!\n");

    with(lock2, nl_lock, nl_unlock, {
            _assert(lock2.num_locks == 1);
            _assert(lock2.num_unlocks == 0);
            printf("Lock 2 locked.\n");

            with(lock1, nl_lock, nl_unlock, {
                    _assert(lock1.num_locks == 2);
                    _assert(lock1.num_unlocks == 1);
                    printf("Lock 1 also locked.\n");
                });
            _assert(lock2.num_locks == 1);
            _assert(lock2.num_unlocks == 0);
            printf("Lock 1 unlocked.\n");
        });
    _assert(lock2.num_locks == 1);
    _assert(lock2.num_unlocks == 1);

    _assert(lock1.num_locks == 2);
    _assert(lock1.num_unlocks == 2);

    printf("Unlocked again!\n");

    return 0;
}

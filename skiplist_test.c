#include <assert.h>
#include <stdlib.h>

#include "skiplist.h"
#include "unittest.h"

int int_cmp(const void *p1, const void *p2,
              const __attribute__((unused)) void *data) {
    return (*((int *) p1) > *((int *) p2)) - (*((int *) p1) < *((int *) p2));
}

void test_create(void) {
    SkipList sl;

    sl = NULL;
    sl = sl_new(int_cmp, NULL);
    assert(sl);

    sl_delete(sl, NULL);
}

void test_insert(void) {
    SkipList sl, tmp_sl;
    int i, *v;
    const int nelts = 1000;

    sl = sl_new(int_cmp, NULL);
    expect(sl);

    v = (int *) malloc(nelts * sizeof(int));
    expect(v);
    for (i = 0; i < nelts; ++i) {
        v[i] = i;
        tmp_sl = NULL;
        tmp_sl = sl_insert(sl, &v[i]);
        assert(tmp_sl);
    }

    sl_delete(sl, NULL);
    free(v);
}

void test_find(void) {
    SkipList sl, tmp_sl;
    int i, *v, *found;
    const int nelts = 1000;

    sl = sl_new(int_cmp, NULL);
    expect(sl);

    v = (int *) malloc(nelts * sizeof(int));
    expect(v);
    for (i = 0; i < nelts; ++i) {
        v[i] = i;
        tmp_sl = NULL;
        tmp_sl = sl_insert(sl, &v[i]);
        expect(tmp_sl);
    }

    for (i = 0; i < nelts; ++i) {
        found = (int *) sl_find(sl, &i);
        assert(found);
        assert(found == &v[i]);
        assert(*found == i);
    }

    sl_delete(sl, NULL);
    free(v);
}

void test_remove(void) {
    SkipList sl, tmp_sl;
    int i, j, *v, *found;
    const int nelts = 100;

    sl = sl_new(int_cmp, NULL);
    expect(sl);

    v = (int *) malloc(nelts * sizeof(int));
    expect(v);
    for (i = 0; i < nelts; ++i) {
        v[i] = i;
        tmp_sl = NULL;
        tmp_sl = sl_insert(sl, &v[i]);
        expect(tmp_sl);
    }

    for (i = 0; i < nelts; ++i) {
        found = (int *) sl_remove(sl, &i);
        assert(found);
        assert(found == &v[i]);
        assert(*found == i);
        for (j = 0; j < nelts; ++j) {
            found = (int *) sl_find(sl, &j);
            if (i == j) {
                assert(!found);
            } else {
                assert(found);
                assert(found == &v[j]);
                assert(*found == j);
            }
        }
        sl_insert(sl, &v[i]);
        found = (int *) sl_find(sl, &i);
        expect(found);
        expect(found == &v[i]);
        expect(*found == i);
    }

    sl_delete(sl, NULL);
    free(v);
}

int main(void) {
    TEST(create);
    TEST(insert);
    TEST(find);
    TEST(remove);

    return 0;
}

#include <assert.h>
#include "skiplist.h"
#include "unittest.h"

int int_cmp(const void *p1, const void *p2,
              const __attribute__((unused)) void *data) {
    return (*((int *) p1) > *((int *) p2)) - (*((int *) p1) < *((int *) p2));
}

void test_create(void) {
    SkipList sl, slp;

    sl = (SkipList) malloc(sizeof(*sl));
    assert(sl);
    sl_init(sl, int_cmp, NULL);
    slp = NULL;
    slp = sl_new(int_cmp, NULL);
    expect(slp);

    sl_delete(sl);
    sl_delete(slp);
}

void test_insert(void) {
    SkipList sl, tmp_sl;
    int i, *v;
    const int nelts = 1000;

    sl = sl_new(int_cmp, NULL);
    assert(sl);

    v = (int *) malloc(nelts * sizeof(int));
    assert(v);
    for (i = 0; i < nelts; ++i) {
        v[i] = i;
        tmp_sl = NULL;
        tmp_sl = sl_insert(sl, &v[i]);
        expect(tmp_sl);
    }

    sl_delete(sl);
}

void test_find(void) {

}

int main(void) {
    TEST(create);
    TEST(insert);
    TEST(find);

    return 0;
}

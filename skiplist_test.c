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
    assert(slp);

    sl_delete(sl);
    sl_delete(slp);
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

    sl_delete(sl);
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

    sl_delete(sl);
    free(v);
}

int main(void) {
    TEST(create);
    TEST(insert);
    TEST(find);

    return 0;
}

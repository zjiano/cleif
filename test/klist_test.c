#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../klist.h"
#include "../error.h"
#include "test.h"

struct item {
    int val;
    struct klist head;
};

int main(int argc, char *argv[])
{
    int i;
    LIST_HEAD(head);
    struct klist *p;
    struct item *e;

    for (i = 0; i < 100; ++i) {
	struct item *elt = (struct item *) malloc(sizeof(struct item));
	assert(elt);
	elt->val = i;
	ladd(&elt->head, &head);
    }

    i = 0;
    lforeach(p, &head) {
	i++;
    }
    if (i != 100) {
	fail("there should be 100 items in the klist");
    }
    i = 0;
    lforeach_entry(e, &head, struct item, head) {
	i += e->val;
    }
    if (i != 4950) {
	fail("klist should sum to 4950");
    }

    printf("success!\n");

    return 0;
}

#include <stdlib.h>

#include "../list.h"
#include "../error.h"
#include "test.h"

struct item {
    int val;
    struct list head;
};

int main(int argc, char *argv[])
{
    int i;
    LIST_HEAD(head);
    struct list *p;
    struct item *e;

    for (i = 0; i < 100; ++i) {
	struct item *elt = (struct item *) malloc(sizeof(struct item));
	elt->val = i;
	if (!elt) {
	    abort("malloc failed");
	}
	ladd(&elt->head, &head);
    }

    i = 0;
    lforeach(p, &head) {
	i++;
    }
    if (i != 100) {
	fail("there should be 100 items in the list");
    }
    i = 0;
    lforeach_entry(e, &head, struct item, head) {
	i += e->val;
    }
    if (i != 4950) {
	fail("list should sum to 4950");
    }

    return 0;
}

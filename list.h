#include "util.h"

struct list {
    struct list *next, *prev;
};

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) struct list name = LIST_HEAD_INIT(name)

#define lhead(head) (head)->next
#define ltail(head) (head)->prev

#define lentry(ptr, type, member) container_of(ptr, type, member)
#define lentry_first(l, type, member) lentry(lhead(l), type, member)

static inline void INIT_LIST_HEAD(struct list *l)
{
    lhead(l) = ltail(l) = l;
    return l;
}

static inline void __ladd(struct list *elt,
	struct list *prev, struct list *next)
{
    next->prev = elt;
    elt->next = next;
    elt->prev = prev;
    prev->next = elt;
}

static inline void ladd(struct list *elt, struct list *l)
{
    __list_add(elt, l, lhead(l));
}

static inline void ladd_tail(struct list *elt, struct list *l)
{
    __list_add(elt, ltail(l), l);
}

#define lpush(elt, l) ladd((elt), (l))
#define lenqueue(elt, l) ladd((elt), (l))

static inline void __ldel(struct list *prev, struct list *next)
{
    next->prev = prev;
    prev->next = next;
}

static inline void ldel(struct list *entry)
{
    __list_del(entry->prev, entry->next);
    entry->next = entry->prev = NULL;
}

static inline struct list *pop(struct list *l)
{
    struct list *elt = lhead(l);
    ldel(elt);
    return elt;
}

static inline struct list *dequeue(struct list *l)
{
    struct list *elt = ltail(l);
    ldel(elt);
    return elt;
}

static inline bool lempty(struct list *l)
{
    return lhead(l) == l;
}

static inline struct list *lsplice(struct list *l1, struct list *l2)
{
    ltail(l1)->next = lhead(l2);
    lhead(l2)->prev = ltail(l1);
    ltail(l2)->next = l1;
    l1->prev = ltail(l2);
    l2->next = l2->prev = NULL; 
    return l1;
}

#define lforeach(pos, head) \
    for ((pos) = (head)->next; (pos) != (head); (pos) = (pos)->next)

#define lforeach_rev(pos, head) \
    for ((pos) = (head)->prev; (pos) != (head); (pos) = (pos)->prev)

#define lforeach_entry(pos, head, member) \
    for ((pos) = list_entry((head)->next, typeof(*pos), member); \
	    &(pos)->member != (head); \
	    (pos) = list_entry((pos)->member.next, typeof(*pos), member))

#define lforeach_entry_rev(pos, head, member) \
    for ((pos) = list_entry((head)->prev, typeof(*pos), member); \
	    &(pos)->member != (head); \
	    (pos) = list_entry((pos)->member.prev, typeof(*pos), member))


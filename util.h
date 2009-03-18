#undef offsetof
#ifdef __compiler_offsetof
#define offsetof(type, member) __compiler_offsetof(type, member)
#else
#define offsetof(type, member) ((size_t) &((type *)0)->member)
#endif

/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:    the pointer to the member
 * @type:   the type of the container struct this is embedded in
 * @member: the name of the member within the struct
 *
 * (stolen from linux kernel)
 */
#if 0
#define container_of(ptr, type, member) ({ \
	    const typeof( ((type *)0)->member ) *__mptr = (ptr); \
	    (type *)( (char *)__mptr - offsetof(type, member) );})
#else
#define container_of(ptr, type, member) \
	((type *)( (char *) ptr - offsetof(type, member) ))
#endif

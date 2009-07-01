CC=gcc
CFLAGS=-Wall -Werror -Wextra
LDFLAGS=-g3

BINS=klist_test tree_test withstmt_test
SRCS=klist_test.c tree_test.c withstmt_test.c
HDRS=test.h
OBJS=$(SRCS:.c=.o)
DEPS=$(SRCS:.c=.d)
TAGFILE=tags

all: $(TAGFILE) $(BINS)

klist_test: klist_test.c
	$(CC) $(CFLAGS) -o $@ $<

tree_test: tree_test.c
	make -C .. tree.o
	$(CC) $(CFLAGS) -o $@ $< ../tree.o

withstmt_test: withstmt_test.c
	$(CC) $(CFLAGS) -o $@ $<

$(TAGFILE): $(SRCS) $(HDRS)
	ctags -f $(TAGFILE) $(SRCS) $(HDRS)

clean:
	rm -f $(BINS) $(OBJS) $(DEPS)

allclean: clean
	rm -f .*.sw? "#"*"#" *\~ $(TAGFILE)

%.o: %.d

%.d: %.c
	$(CC) -M $(CFLAGS) -o $@ $<

-include $(DEPS)

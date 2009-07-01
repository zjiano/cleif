CC=gcc
CFLAGS=-Wall -Werror
LDFLAGS=-g3

SRCS=tree.c
HDRS=tree.h klist.h util.h error.h
OBJS=$(SRCS:.c=.o)
DEPS=$(SRCS:.c=.d)
TAGFILE=tags

all: $(TAGFILE) $(OBJS)

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

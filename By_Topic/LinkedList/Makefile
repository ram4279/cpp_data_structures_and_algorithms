CC		 =	gcc
OPT		 =	-02
CFLAGS	 =	-Wall
CODEDIRS = .

ifeq ($(DEBUG),y)
CFLAGS += -g
endif

BINARY   = ll_main
CFILES   = $(foreach D,$(CODEDIRS),$(wildcard $(D)/*.c))
OBJFILES = $(patsubst %.c,%.o,$(CFILES))

all: $(BINARY)

$(BINARY) : $(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJFILES) $(BINARY)
# dmenu - dynamic menu
# See LICENSE file for copyright and license details.

include config.mk

SRC =\
	museus.cpp\
	src/cards.cpp\
	src/date.cpp
OBJ = $(SRC:.cpp=.o)

all: options museus

options:
	@echo museus build options:
	@echo "CFLAGS   = $(CFLAGS)"
	@echo "LDFLAGS  = $(CPPFLAGS)"
	@echo "CC       = $(CC)"

.c.o:
	$(CC) -c $(CFLAGS) $<

$(OBJ): include/cards.h include/date.h

dmenu: ${OBJ}
	@echo CC -o $@
	$(CC) -o $@ ${OBJ}

clean:
	@echo cleaning: $(OBJ)
	rm -f museus

install: all
	chmod 755 museus

uninstall:
	rm -f museus

.PHONY: all options clean install uninstall

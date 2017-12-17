CC      = gcc
OBJDIR  = obj
SRCDIR  = src
CLIDIR  = cliobj
INCDIR  = inc
CFLAGS  = -Wall
LDFLAGS = `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0 gthread-2.0`

SRCS    = $(wildcard $(SRCDIR)/*.c)
OBJS		= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
GUIOBJS = $(OBJS)

all: chessGUI

chessGUI: $(GUIOBJS)
	$(CC) $(CFLAGS) $(GUIOBJS) -o chessGUI $(LDFLAGS)

$(OBJS): | $(OBJDIR)
$(OBJDIR):
	mkdir -p $@

$(OBJDIR)/chessGUI.o: $(SRCDIR)/chessGUI.c
	$(CC) $(CFLAGS) $< -c -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(wildcard $(INCDIR)/*.h) Makefile
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm -rf $(OBJDIR)

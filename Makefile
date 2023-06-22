CC=clang
CFLAGS=
LIBS=

MKDIR=mkdir -p
RM=rm -r

SRCDIR=src
BUILDDIR=build
OBJS=$(BUILDDIR)/main.o
SOLVER=$(BUILDDIR)/solver

all: $(SOLVER)

run: $(SOLVER)
	./$(SOLVER)

.PHONY: clean
clean:
	$(RM) $(BUILDDIR)

$(SOLVER): $(BUILDDIR) $(OBJS)
	$(CC) $(OBJS) -o $(SOLVER) $(LIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(BUILDDIR):
	$(MKDIR) $(BUILDDIR)


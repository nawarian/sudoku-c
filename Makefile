CC=clang
CFLAGS=`pkg-config --cflags raylib`
LIBS=`pkg-config --libs raylib`

MKDIR=mkdir -p
RM=rm -r

SRCDIR=src
BUILDDIR=build
OBJS=$(BUILDDIR)/main.o \
	 $(BUILDDIR)/grid.o
SOLVER=$(BUILDDIR)/solver

SAMPLE_EASY_GRID="690805730518763020374192680007954312930217046421638900056381294040579168089406073"

all: $(SOLVER)

run: $(SOLVER)
	./$(SOLVER) $(SAMPLE_EASY_GRID)

.PHONY: clean
clean:
	$(RM) $(BUILDDIR)

$(SOLVER): $(BUILDDIR) $(OBJS)
	$(CC) $(OBJS) -o $(SOLVER) $(LIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(BUILDDIR):
	$(MKDIR) $(BUILDDIR)


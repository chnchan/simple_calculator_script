
CC         	= g++
CFLAGS      	= -g -Wall
OBJ         	= main.o

BUILDDIR		= build

all: dir calculate

dir:
	mkdir -p $(BUILDDIR)

calculate: $(BUILDDIR)/$(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(BUILDDIR)/%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf calculate $(BUILDDIR)

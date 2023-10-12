SRCDIR=src
LIBDIR=lib
BINDIR=bin
DOCDIR=doc
INCLUDEDIR=include
TESTDIR=tests
CC = gcc
AR = ar
CFLAGS=-Wall -pedantic -g -std=c99 -I$(INCLUDEDIR)  
LDFLAGS=-L$(LIBDIR)
EXEC=asispell

all : $(BINDIR)/$(EXEC)

tests : $(LIBDIR)/libtypesinternes.a $(LIBDIR)/libtypesexternes.a $(LIBDIR)/libtests.a $(SRCDIR)/testsUnitaires.o
	$(CC) $(LDFLAGS) -o $(TESTDIR)/testsUnitaires $(SRCDIR)/testsUnitaires.o -ltests -ltypesinternes -ltypesexternes -lcunit -g

doc : doc/html/index.html

$(BINDIR)/$(EXEC) : $(SRCDIR)/main.o $(LIBDIR)/libtypesinternes.a $(LIBDIR)/libtypesexternes.a
	$(CC) $(LDFLAGS) -o $@ $(SRCDIR)/main.o -ltypesinternes -ltypesexternes
	
$(LIBDIR)/libtests.a : $(SRCDIR)/testcorrecteur.o $(SRCDIR)/testDictionnaire.o $(SRCDIR)/testmot.o $(SRCDIR)/testfile.o
	$(AR) -r $@ $^

$(LIBDIR)/libtypesinternes.a : $(SRCDIR)/correcteurorthographique.o $(SRCDIR)/dictionnaire.o $(SRCDIR)/mot.o
	$(AR) -r $@ $^

$(LIBDIR)/libtypesexternes.a : $(SRCDIR)/file.o
	$(AR) -r $@ $^

$(SRCDIR)/%.o : $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS)
	
doc/html/index.html :
	doxygen doc/.Doxyfile

clean :
	rm -f $(BINDIR)/*
	rm -f $(LIBDIR)/*
	rm -f $(SRCDIR)/*.o
	rm -f $(TESTDIR)/*
	rm -rf $(DOCDIR)/*

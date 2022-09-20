# -*- Makefile -*-

CPP	     = g++
OPT	     = -O0
CODEDIRS = .
INCDIRS  = -I.
# Generate files that encode makerules for .h dependencies
DEPFLAGS = -MP -MD
CFLAGS   = -Wall -Wextra -g -std=c++11 $(OPT) $(DEPFLAGS) $(foreach D,$(INCDIRS),-I$(D))

#FILES
#DUMB WAY
#OBJFILES = runner.o diameter_of_tree.o iterative_traversals.o is_bst_balanced.o maxheight_of_bst.o
#CFILES   = runner.cpp diameter_of_tree.cpp iterative_traversals.cpp is_bst_balanced.cpp maxheight_of_bst.cpp

#SMART WAY
#LOOP THROUGH EACH DIRECTORY and include *.cpp
CFILES   = $(foreach D,$(CODEDIRS),$(wildcard $(D)/*.cpp))
OBJFILES = $(patsubst %.cpp,%.o,$(CFILES))
DEPFILES = $(patsubst %.cpp,%.d,$(CFILES))

BINARY = runner

all: $(BINARY)

$(BINARY): $(OBJFILES)
	$(CPP) -o $@ $^

%.o: %.cpp
	$(CPP) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf $(OBJFILES) $(BINARY) $(DEPFILES)

-include $(DEPFILES)

# DUMB WAY OF DOING 

# runner: runner.o diameter_of_tree.o iterative_traversals.o is_bst_balanced.o maxheight_of_bst.o
# 	g++ runner.o diameter_of_tree.o iterative_traversals.o is_bst_balanced.o maxheight_of_bst.o -o runner

# runner.o: runner.cpp mytree.h
# 	g++ -c runner.cpp

# diameter_of_tree.o: diameter_of_tree.cpp mytree.h
# 	g++ -c diameter_of_tree.cpp

# iterative_traversals.o: iterative_traversals.cpp mytree.h
# 	g++ -c iterative_traversals.cpp

# is_bst_balanced.o: is_bst_balanced.cpp mytree.h
# 	g++ -c is_bst_balanced.cpp

# maxheight_of_bst.o: maxheight_of_bst.cpp mytree.h
# 	g++ -c maxheight_of_bst.cpp

# clean:
# 	rm *.o runner 
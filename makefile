# Makefile is the text file the make utility will look for

# demo is the target
# demo.o is the prerequisite
# if demo is out of date (doesn't exist or has been updated)

# $@ = the target
# $< = the first prerequisite
# $^ = all prerequisites

compiler = g++
flags = -Wall -std=c++17
link = $(compiler) $(flags)
compile = $(compiler) $(flags) -c

demo : demo.o
	$(link) $^ -o $@
	./$@

demo.o : demo.cc MySet.h MySet.cc setinterface.h
	$(compile) $<

clean :
	rm -f *.o demo

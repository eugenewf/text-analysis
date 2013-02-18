
# 
#
# all is the first target and its also default 
# sum.o is also a target
# test.o is also a target 
# clean is to clean targets for rebuilding 
# 
all: test.o sum.o 
	gcc test.o sum.o -o test

sum.o: sum.c sum.h
	gcc -c sum.c 

test.o: test.c sum.h # dependencies
	gcc -c test.c # action for the dependency
	
clean:
	rm *.o test

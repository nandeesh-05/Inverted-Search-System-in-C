# Collect all .c files and convert them to .o object files
OBJ := $(patsubst %.c, %.o, $(wildcard *.c))

# Target to build the executable
inverted_search: $(OBJ)
	gcc $(OBJ) -o inverted_search

# Clean rule to remove generated files
clean:
	rm *.o  inverted_search
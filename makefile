CFLAGS = -Wall -Werror
filter: filter.o

filter:
	./filter input.ppm kernel output.ppm

clean:
	@rm -rf filter *.o
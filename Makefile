FLAGS := -g
INCLUDE := -I ~/include
LDFLAGS := -L ~/lib -lsense -lm
%.o: %.c
	cc -c $(CFLAGS) $< $(INCLUDE)

inputtest: inputtest.o
	cc -o inputtest $(INCLUDE) inputtest.o $(LDFLAGS)

clean:
	rm -f *.o inputtest

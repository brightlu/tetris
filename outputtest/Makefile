FLAGS := -g
INCLUDE := -I ~/include
LDFLAGS := -L ~/lib -lsense -lm
%.o: %.c
	cc -c $(CFLAGS) $< $(INCLUDE)

outputtest: outputtest.o
	cc -o outputtest $(INCLUDE) outputtest.o $(LDFLAGS)

clean:
	rm -f *.o inputtest

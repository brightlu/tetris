FLAGS := -g
INCLUDE := -I ~/include
LDFLAGS := -L ~/lib -lsense -lm
%.o: %.c
	cc -c $(CFLAGS) $< $(INCLUDE)

inputtest: inputtest.o
	cc -o inputtest $(INCLUDE) inputtest.o $(LDFLAGS)

testgame: testgame.o
	cc outputtest.c piece.c -o testgame $(INCLUDE) testgame.o $(LDFLAGS)

clean:
	rm -f *.o inputtest testgame

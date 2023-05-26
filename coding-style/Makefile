# TRIFAN BOGDAN-CRISTIAN , 312CD
# PROIECT PCLP 3

CC = gcc
CFLAGS = -Wall -g
EXC = coding_style

build: $(EXC)

$(EXC): checker.o liner.o ../byte_string.o
	$(CC) $(CFLAGS) -o $(EXC) checker.o liner.o ../byte_string.o

checker.o: checker.c ../macrouri.h liner.h ../byte_string.h
	$(CC) $(CFLAGS) -c checker.c

liner.o: liner.c liner.h ../macrouri.h ../byte_string.h
	$(CC) $(CFLAGS) -c liner.c

../byte_string.o: ../byte_string.c ../byte_string.h ../macrouri.h
	$(CC) $(CFLAGS) -c ../byte_string.c

clean:
	rm -f *.o exec $(EXC)

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(EXC) $< $(filter-out $@,$(MAKECMDGOALS))

archive:
	rm -rf coding_style.zip
	zip -r coding_style.zip *.c *.h README.md README Makefile

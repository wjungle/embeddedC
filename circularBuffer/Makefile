CC = gcc
INC = .
CFLAG = -g -Wall 
obj = circularBuffer.o main.o

all: main
main: $(obj)
	$(CC) -o main $(obj) 
main.o: main.c
	$(CC) -I$(INC) $(CFLAG) -c main.c
circularBuffer.o: circularBuffer.c circularBuffer.h
	$(CC) -I$(INC) $(CFLAG) -c circularBuffer.c
clean:
	rm main.exe $(obj)

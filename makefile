all: ConnectFour.c
	gcc -g -Wall -o connectfour ConnectFour.c
clean:
	$(RN) connectfour

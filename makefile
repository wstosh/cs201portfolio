all: ConnectFour.c
	gcc -Wall -o connectfour ConnectFour.c
clean:
	$(RN) connectfour

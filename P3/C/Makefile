all: training

training:
	gcc -o training -g -std=gnu11 Network.c main.c vector.c -lm

debug:
	gcc -o debug -g -std=gnu11 Network.c robot.c vector.c cbcDummy.c -lm

release:
	gcc -o release -std=gnu11 Network.c robot.c vector.c cbc.c -lm


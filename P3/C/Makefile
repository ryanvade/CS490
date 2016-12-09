all: training

training:
	gcc -o training -O3 -std=gnu11 main.c vector.c network.c -lm

debug:
	gcc -o debug -g -std=gnu11 robot.c network.c vector.c cbcDummy.c -lm

cbc:
	gcc -o cbc -std=gnu11 robot.c network.c vector.c cbc.c -lm

clean:
	rm -f training
	rm -f debug
	rm -f cbc


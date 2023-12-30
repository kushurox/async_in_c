run: main
	./main

main: main.c executor.c future.c
	clang -o main main.c executor.c future.c
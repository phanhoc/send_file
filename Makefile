all: server.c client.c
	gcc -o server server.c
	gcc -o client client.c
clean:
	rm -rf server client *~

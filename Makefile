CC=g++
CFLAGS=-Wall -Wextra

all:
	$(CC) $(CFLAGS) -o combi combi.cpp
	$(CC) $(CFLAGS) -o filter filter.cpp
	$(CC) $(CFLAGS) -o subst subst.cpp
	$(CC) $(CFLAGS) -o checkHash checkHash.cpp -lssl -lcrypto

clean:
	rm filter combi subst

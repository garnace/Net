all: n7 n6 n5 n4 n3 n2 n1


n7: n7.c
	gcc -o n7 n7.c
n6: n6.c
	gcc -o n6 n6.c
n5: n5.c
	gcc -o n5 n5.c
n4: n4.c
	gcc -o n4 n4.c
n3: n3.c
	gcc -o n3 n3.c
n2: n2.c
	gcc -o n2 n2.c

n1: n1.c
	gcc -o n1 n1.c

clean:
	rm n7 n6 n5 n4 n3 n2 n1 link1 link2 link3 link4 link5 link6

run:    all
	./n2 & ./n3 & ./n4 & ./n5 & ./n6 & ./n7 & ./n1 hi



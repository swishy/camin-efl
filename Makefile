ainit: bin/ainit.c  
	gcc -I /usr/include -I include/ -luv -ldl -lrt -pthread -o ainit bin/ainit.c /usr/lib/libuv.a
	
amin: bin/amin.c  
	gcc -I /usr/include -I include/ -luv -ldl -lrt -pthread -o amin bin/amin.c 
	
clean:
	rm ainit
	rm amin

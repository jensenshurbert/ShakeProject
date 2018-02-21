#MakeFile to build and deploy the Sample US CENSUS Name Data using ajax
# For CSC3004 Software Development

# Put your user name below:
USER= shurbertj

CC= g++

#For Optimization
#CFLAGS= -O2
#For debugging
CFLAGS= -std=c++14

RM= /bin/rm -f

all: wordserver testclient wordlookupclient PutCGI PutHTML

testclient.o: testclient.cpp fifo.h
	$(CC) -c $(CFLAGS) testclient.cpp
	
index.o: index.cpp index.h 
	$(CC) -c $(CFLAGS) index.cpp -c

wordserver.o: wordserver.cpp fifo.h index.h
	$(CC) -c $(CFLAGS) wordserver.cpp index.cpp

wordlookupclient.o: wordlookupclient.cpp fifo.h
	$(CC) -c $(CFLAGS) wordlookupclient.cpp

testclient: testclient.o fifo.o
	$(CC) $(CFLAGS) testclient.o fifo.o -o testclient

wordserver: wordserver.o fifo.o index.o
	$(CC) $(CFLAGS) wordserver.o index.o fifo.o -o wordserver

fifo.o:	fifo.cpp fifo.h
	g++ -c fifo.cpp

wordlookupclient: wordlookupclient.o  fifo.h
	$(CC) $(CFLAGS) wordlookupclient.o  fifo.o -o wordlookupclient -L/usr/local/lib -lcgicc

PutCGI: wordlookupclient
	chmod 757 wordlookupclient
	cp wordlookupclient /usr/lib/cgi-bin/$(USER)_wordlookupclient.cgi 

	echo "Current contents of your cgi-bin directory: "
	ls -l /usr/lib/cgi-bin/

PutHTML:
	cp wordlookupCS.html /var/www/html/class/softdev/$(USER)/Project1-3/
	cp wordlookupCS.css /var/www/html/class/softdev/$(USER)/Project1-3/
	cp wordlookupCS.js /var/www/html/class/softdev/$(USER)/Project1-3/

	echo "Current contents of your HTML directory: "
	ls -l /var/www/html/class/softdev/$(USER)/Project1-3/

clean:
	rm -f *.o wordlookupclient wordserver testclient

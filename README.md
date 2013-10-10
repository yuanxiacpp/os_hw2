bufferTest.cpp is a test program that verifies bounded buffer problem

Usage:
How to compile: make
How to run the program: ./test_buffer NumOfProducer NumOfConsumer
Sample usage: ./test_buffer 10 3 

Design:
buffer.h, buffer.cpp: implements the buffer that will be used to store the contents. The put and get function in class Buffer provides the functionalties to put in and get out elements from buffer in a thread-safe way. There is a mutex in Buffer class which will protect the counter.

bufferTest.cpp: this is a test program which utilized the Buffer class. The consumerThread acts as consumers to get the elements out of buffer; producerThread acts as producers to put elements into buffer. Each of them will run on a while loop which controlled by runtest variable. There are two semaphores, empty and full, for producers and consumers


Test:
Tested on zoo Linux machines, works fine. There are some minor errors on Mac OSX, not sure about the cause.
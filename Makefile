CXX = g++ -g

all: buffer_test

buffer_test:
	$(CXX) -o buffer_test *.cpp -lpthread

clean:
	rm *~

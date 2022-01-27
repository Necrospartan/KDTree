main: main.cpp Kdtree.cpp auxiliary.hpp
	g++ -O3 main.cpp -o main
run:
	./main
clean:
	rm main
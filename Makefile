all:
	g++ main.cpp -std=c++11 -lbenchmark -lpthread -O1 -o benchmark_O1
	g++ main.cpp -std=c++11 -lbenchmark -lpthread -O2 -o benchmark_O2
	g++ main.cpp -std=c++11 -lbenchmark -lpthread -O3 -o benchmark_O3

clean:
	rm benchmark_O1 benchmark_O2 benchmark_O3

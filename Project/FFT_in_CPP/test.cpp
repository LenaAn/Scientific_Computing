#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <chrono>

#include "fft.h"

// const int N = 160;

int main(int argc, char** argv) {
	srand (time(NULL));

	const int N = atoi(argv[1]);

	std::vector<int> a, b, res;
	for (int i = 0; i < N; ++i)	{
		a.push_back(std::rand() % 10);
		b.push_back(std::rand() % 10);
	}

	if (argc > 2) {
		std::cout << "first number is ";
		for (int i = N - 1; i > -1; --i) 
			std::cout << a[i];
		std::cout << std::endl;

		std::cout << "second number is ";
		for (int i = N - 1; i > -1; --i) 
			std::cout << b[i];
		std::cout << std::endl;
	}

	auto started = std::chrono::high_resolution_clock::now();
	// std::cout << "started = " << started << std::endl;

	parallel_multiply(a, b, res);

	auto done = std::chrono::high_resolution_clock::now();
	// std::cout << "done = " << done << std::endl;

	if (argc > 2) {
		std::cout << "result is ";
		for (int i = 2*N - 1; i > -1; --i)	{
			std::cout << res[i];
		}
		std::cout << std::endl;
	}

	std::cout << "Work time: " << std::chrono::duration_cast<std::chrono::microseconds>(done-started).count() << " ms" << std::endl;


}
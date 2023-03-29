#ifndef HIST_GENERATOR
#define HIST_GENERATOR

#include <iostream>
#include <vector>
#include <random>

int main() {
	//variables that the user defines
	int mean = 0;
	int stdDev = 0;
	//read in mean and standard deviation
	std::cin >> mean;
	std::cin >> stdDev;

	std::cout << "mean: " << mean << std::endl << "standard Deviation: " << stdDev << std::endl;

	std::random_device rand; //random seed
	// V V V mersenne_twister_engine: produces an unsigned random int based on an M.T. algorithm.
	std::mt19937 generator(rand()); //seeded with rand()

	std::normal_distribution<double> nDist(mean, stdDev); //creates normal distrobution for generated numbers to adhere to

	std::vector<int> hist; //vector to hold the numbers and their frequencies

	for (int i = 0; i < 20000; i++) {
		hist[round(nDist(generator))]++;
	}

	for (auto val : hist) {
		std::cout << val << " " << freq << std::endl;
	}

	return -1;
}

#endif // !HIST_GENERATOR

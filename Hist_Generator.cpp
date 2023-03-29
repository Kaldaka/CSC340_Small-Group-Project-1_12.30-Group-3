#ifndef HIST_GENERATOR
#define HIST_GENERATOR

#include <iostream>
#include <map>
#include <random>

int main() {
	//variables that the user defines
	int mean = 0;
	int stdDev = 0;

	std::cout << "Please enter a desired mean. Then press \"enter\" and enter a desired standard deviation. Then press \"enter\" again\n\n";

	//read in mean and standard deviation
	std::cin >> mean;
	std::cin >> stdDev;

	std::cout << "\nmean: " << mean << std::endl << "standard Deviation: " << stdDev << std::endl;

	std::random_device rand; //random seed
	// V V V mersenne_twister_engine: produces an unsigned random int based on an M.T. algorithm.
	std::mt19937 generator(rand()); //seeded with rand()

	std::normal_distribution<double> nDist(mean, stdDev); //creates normal distrobution for generated numbers to adhere to

	std::map<int, int> hist{}; //vector to hold the numbers and their frequencies

	//adds random numbers to the map. Random number used as key to access it's frequency number. ++ used to inc the frequency
	for (int i = 0; i < 20000; i++) {
		hist[round(nDist(generator))]++;
	}

	//print out the histogram
	for (const auto& pair : hist) {
		std::cout << pair.first << " " << pair.second << std::endl;
	}

	return -1;
}

#endif // !HIST_GENERATOR

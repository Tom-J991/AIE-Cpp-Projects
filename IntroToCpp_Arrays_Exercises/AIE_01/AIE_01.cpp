
#include <iostream>

int main(int argc, char** argv)
{
	const int NUM_NUMBERS = 5;
	int numbers[NUM_NUMBERS] = { 10, 20, 30, 40, 50 };

	/* 
	TODO: Print each value of the array in order
	Expected:
		10, 20, 30, 40, 50,
	*/
	// Task1: Write your Code here
	// ------------------------------------------------------------------------

	std::cout << "Part 1: " << std::endl;
	for (int i = 0; i < NUM_NUMBERS; ++i)
	{
		std::cout << numbers[i];
		if (i != NUM_NUMBERS-1)
			std::cout << ", ";
	}
	std::cout << std::endl;
	// ------------------------------------------------------------------------


	/*
	TODO: Print each value of the array in reverse order
	Expected:
		50, 40, 30, 20, 10,
	*/

	// Task 2: Write your Code here
	// ------------------------------------------------------------------------

	std::cout << "Part 2: " << std::endl;
	for (int i = NUM_NUMBERS-1; i >= 0; --i)
	{
		std::cout << numbers[i];
		if (i != 0)
			std::cout << ", ";
	}
	std::cout << std::endl;
	// ------------------------------------------------------------------------

	std::cin.ignore();

	return 0;
}

#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <random>
#include <time.h>

std::string LoadRandomWord();
void Guess(std::string &word, std::string &letter, std::string &output);

int main()
{
	srand(time(nullptr));

	std::string word = LoadRandomWord();
	std::string letter;
	std::string output = "";

	if (word.length() == 0)
	{
		std::cout << "The program could not execute." << std::endl;
		return 0;
	}
	output.resize(word.length(), '_');

	Guess(word, letter, output);
	std::cout << "The word is: " << word << std::endl;

	std::cout << std::endl << "Press 'Enter' to exit." << std::endl;

	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();
	return 0;
}

void Guess(std::string& word, std::string& letter, std::string& output)
{
	std::cout << "Enter a letter: " << std::endl;
	std::cin >> letter;
	if (letter.length() > 1)
		letter.resize(1);

	int startPos = 0;
	size_t searchPos = word.find(letter, startPos);
	while (searchPos != std::string::npos)
	{
		output[searchPos] = letter[0];
		startPos = searchPos + 1;
		if (startPos >= word.length())
			break;
		searchPos = word.find(letter, startPos);
	}

	std::cout << output << std::endl;

	if (output != word)
		Guess(word, letter, output);
}

std::string LoadRandomWord()
{
	std::ifstream in;
	in.open("dictionary.txt", std::ifstream::in);

	if (in.is_open() == false)
	{
		std::cout << "dictionary.txt could not be found." << std::endl;
		return "";
	}

	std::string text;

	in.unsetf(std::ios_base::skipws);
	unsigned int line_count = std::count(std::istream_iterator<char>(in), std::istream_iterator<char>(), '\n');
	
	in.clear();
	in.seekg(0, std::ios::beg);

	int selection = rand() % line_count;
	for (int i = 0; i < selection; i++)
	{
		std::getline(in, text);
	}

	in.close();
	return text;
}

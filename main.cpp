#include <iostream>
#include <Windows.h>
#include "AsciiDocParser.h"

int main(int argc, char* argv[]) {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	if (argc < 2) {
		std::cerr << "Использование: " << argv[0] << " <имя_файла>" << std::endl;
		return 1;
	}

	std::vector<std::string> bannedWords = { "text", "Ipsum" };

	AsciiDocParser parser;
	parser.parse(argv[1]);

	parser.Censore(bannedWords);

	parser.displayResults();

	return 0;
}
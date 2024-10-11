#include "AsciiDocParser.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <algorithm>

void AsciiDocParser::parse(const std::string& filename) {
	std::ifstream file(filename);
	std::string line;
	std::regex headerRegex(R"(^=+\s+(.*)$)");
	std::regex paragraphRegex(R"(^[^=\d].+$)");
	std::regex listItemRegex(R"(^\s*\d+\.\s*(.+)$)");
	std::regex listItemWithEqualRegex(R"(^\s*\d+\.\s*=.*$)");
	std::regex numberWithDotAndEqualRegex(R"(^\s*\d+\.\s*=\s*)");

	while (std::getline(file, line)) {
		std::smatch match;

		if (std::regex_match(line, match, headerRegex)) {
			headers.push_back(match[1].str());
		}
		else if (std::regex_match(line, match, listItemWithEqualRegex)) {
			orderedList.push_back(line);

			std::string header = std::regex_replace(line, numberWithDotAndEqualRegex, "");
			headers.push_back(header);
		}
		else if (std::regex_match(line, match, listItemRegex)) {
			orderedList.push_back(match[1].str());
		}
		else if (std::regex_match(line, match, paragraphRegex)) {
			paragraphs.push_back(line);
		}
	}

	file.close();
}

void AsciiDocParser::Censore(const std::vector<std::string>& bannedWords) {
	for (auto& paragraph : paragraphs) {
		for (const auto& word : bannedWords) {
			size_t pos = 0;
			while ((pos = paragraph.find(word, pos)) != std::string::npos) {
				paragraph.erase(pos, word.length());
				removedWordCount++;
			}
		}
	}
}

void AsciiDocParser::displayResults() const {
	std::cout << "Заголовки:\n";
	for (const auto& header : headers) {
		std::cout << header << std::endl;
	}

	std::cout << "\nАбзацы:\n";
	for (const auto& paragraph : paragraphs) {
		std::cout << paragraph << std::endl;
	}

	std::cout << "\nУпорядоченные списки:\n";
	for (const auto& item : orderedList) {
		std::cout << item << std::endl;
	}

	std::cout << "\nКоличество удалённых слов: " << removedWordCount << std::endl;
}
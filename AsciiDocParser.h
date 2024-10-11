#ifndef ASCIIDOC_PARSER_H
#define ASCIIDOC_PARSER_H

#include <string>
#include <vector>

class AsciiDocParser {
public:
	void parse(const std::string& filename);
	void displayResults() const;
	void Censore(const std::vector<std::string>& bannedWords);

private:
	std::vector<std::string> headers;
	std::vector<std::string> paragraphs;
	std::vector<std::string> orderedList;
	int removedWordCount = 0;
};

#endif
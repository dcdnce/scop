#include "../includes/ObjParser.hpp"

bool ObjParser::_isNewLineOrEOF()
{
	if (_ifs.eof())
		return (true);

	for (; _ifs.peek() != '\n' && std::isspace(_ifs.peek()); _ifs.get())
		;

	if (_ifs.peek() == '\n')
		return (true);

	return (false);
}

std::string ObjParser::_getWord()
{
    std::string word = "";

	for (; std::isspace(_ifs.peek()) && !_ifs.eof() ; _ifs.get())
		;

	for (; !std::isspace(_ifs.peek()) && !_ifs.eof(); word += _ifs.get())
		;

	return (word);
}

void ObjParser::_skipToNewLine()
{
	if (_ifs.eof())	
		return ;

    for (; _ifs.peek() != '\n'; _ifs.get())
		;
	_ifs.get();
}
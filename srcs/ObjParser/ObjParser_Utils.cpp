#include "../includes/ObjParser.hpp"

bool ObjParser::_isEOF()
{
	for (; std::isspace(_ifs.peek()); _ifs.get())
		;

	if (_ifs.peek() == std::char_traits<char>::eof())
		return (true);

	return (false);
}

bool ObjParser::_isNewLine()
{
	for (; _ifs.peek() != '\n' && std::isspace(_ifs.peek()); _ifs.get())
		;

	if (_ifs.peek() == '\n')
		return (true);

	return (false);
}

std::string ObjParser::_getWord()
{
    std::string word = "";

	for (; std::isspace(_ifs.peek()) ; _ifs.get())
		;
	for (; !std::isspace(_ifs.peek()) && !_ifs.eof(); word += _ifs.get())
		;

	return (word);
}

void ObjParser::_skipToNewLine()
{
    for (; _ifs.peek() != '\n' && !_isEOF(); _ifs.get())
		;
	_ifs.get();
}
#include "../includes/ObjParser.hpp"
#include "../includes/Logger.hpp"
#include <cstdlib>

ObjParser::ObjParser(char * const path)
{
    _ifs.open(path);

    if (!_ifs.is_open())
        throw std::runtime_error("Couldn't open file");

    while (!_isEOF())
        _parseLine();

    // do something with exceptions

    Logger::info(true) << "ObjParser successfully parsed \"" << path << "\"" << std::endl; 
    Logger::info(true) << "v: " << _v.size() << std::endl;
    Logger::info(true) << "vn: " << _vn.size() << std::endl;
    Logger::info(true) << "vt: " << _vt.size() << std::endl;
    Logger::info(true) << "f: " << _f.size() << std::endl;
}

void ObjParser::_parseLine() 
{
    std::string currSection = _getWord();

    if (currSection == "v")
        _parseV();
    else if (currSection == "vn")
        _parseVn();
    else if (currSection == "vt")
        _parseVt();
    else if (currSection == "f")
        _parseF();

    _skipToNewLine();
}

void ObjParser::_parseV()
{
    pfm::vec3 newV;

    for (size_t i = 0 ; i < 3 ; i++)
        newV[i] = strtof(_getWord().c_str(), nullptr);

    _v.push_back(newV);
}

void ObjParser::_parseVn()
{
    pfm::vec3 newVn;

    for (size_t i = 0 ; i < 3 ; i++)
        newVn[i] = strtof(_getWord().c_str(), nullptr);

    _vn.push_back(newVn);
}

void ObjParser::_parseVt()
{
    pfm::vec2 newVt;

    for (size_t i = 0 ; i < 2 ; i++)
        newVt[i] = strtof(_getWord().c_str(), nullptr);

    _vt.push_back(newVt);
}

void ObjParser::_parseF()
{
    std::string currIndice;

    for (size_t i = 0 ; i < 3 ; i++)
    {
        std::string currFace = _getWord(); 
        size_t  j = 0;

        currIndice.clear();
        for (; j < currFace.size() && currFace[j] != '/' ; j++)
            currIndice += currFace[j];
        _f.push_back(static_cast<unsigned int>(strtof(currIndice.c_str(), nullptr)));
        currIndice.clear();
        for (; j < currFace.size() && currFace[j] != '/' ; j++)
            currIndice += currFace[j];
        _f.push_back(static_cast<unsigned int>(strtof(currIndice.c_str(), nullptr)));
        currIndice.clear();
        for (; j < currFace.size() ; j++)
            currIndice += currFace[j];
        _f.push_back(static_cast<unsigned int>(strtof(currIndice.c_str(), nullptr)));
    }

    Logger::info(false) << "parsed F" << std::endl;
}


Mesh    ObjParser::buildMesh()
{
    Mesh
}
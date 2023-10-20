#include "../includes/ObjParser.hpp"
#include "../includes/Logger.hpp"
#include <cstdlib>
#include <algorithm>

ObjParser::ObjParser(char * const path)
{
    _v.clear();
    _vn.clear();
    _vt.clear();
    _faces.clear();
    _facesType = 0;

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
    Logger::info(true) << "f: " << _faces.size() << std::endl;
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
    Face    currFace = {};
    static bool firstVertexParsed = false;

    while (!_isNewLine())
    {
        currFace.vertexNb += 1;
        std::string currVertex = _getWord();
        std::string currIndex = "";
        size_t j = 0;

        // V parsing
        currIndex.clear();
        for (; j < currVertex.size() && currVertex[j] != '/' ; j++)
            currIndex += currVertex[j];
        j++; // replace by j+=1 in for loop ?
        if (currIndex.size())
        {
            if (!firstVertexParsed) _facesType = _facesType | FACE_ELEM_V; // replace by |= ?
            currFace.positionIndexes.push_back(
                static_cast<unsigned short>(strtof(currIndex.c_str(), nullptr)) - 1);
        }

        // Vt parsing
        currIndex.clear();
        for (; j < currVertex.size() && currVertex[j] != '/' ; j++)
            currIndex += currVertex[j];
        j++;
        if (currIndex.size())
        {
            if (!firstVertexParsed) _facesType = _facesType | FACE_ELEM_VT;
            currFace.textureIndexes.push_back(
                static_cast<unsigned short>(strtof(currIndex.c_str(), nullptr)) - 1);
        }

        // Vn parsing
        currIndex.clear();
        for (; j < currVertex.size() ; j++)
            currIndex += currVertex[j];
        if (currIndex.size())
        {
            if (!firstVertexParsed) _facesType = _facesType | FACE_ELEM_VN;
            currFace.normalIndexes.push_back(
                static_cast<unsigned short>(strtof(currIndex.c_str(), nullptr)) - 1);
        }

        firstVertexParsed = true;
    }

    _faces.push_back(currFace);
}

#include "../includes/ObjParser.hpp"
#include "../includes/Logger.hpp"
#include <cstdlib>
#include <algorithm>

ObjParser::ObjParser(char * const path)
{
    _inV.clear();
    _inVn.clear();
    _inVt.clear();
    _inFaces.clear();
    _facesType = 0;

    _ifs.open(path);

    if (!_ifs.is_open())
        throw std::runtime_error("Couldn't open file");

    while (!_isEOF())
        _parseLine();

    // do something with exceptions

    Logger::info(true) << "ObjParser successfully parsed \"" << path << "\"" << std::endl; 
    Logger::info(true) << "v: " << _inV.size() << std::endl;
    Logger::info(true) << "vn: " << _inVn.size() << std::endl;
    Logger::info(true) << "vt: " << _inVt.size() << std::endl;
    Logger::info(true) << "f: " << _inFaces.size() << std::endl;

    if (_facesType == FACE_TYPE_V)
        Logger::info(false) << "FACE_TYPE_V" << std::endl;
    if (_facesType == FACE_TYPE_VVT)
        Logger::info(false) << "FACE_TYPE_VVT" << std::endl;
    if (_facesType == FACE_TYPE_VVN)
        Logger::info(false) << "FACE_TYPE_VVN" << std::endl;
    if (_facesType == FACE_TYPE_VVTVN)
        Logger::info(false) << "FACE_TYPE_VVTVN" << std::endl;
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

    _inV.push_back(newV);
}

void ObjParser::_parseVn()
{
    pfm::vec3 newVn;

    for (size_t i = 0 ; i < 3 ; i++)
        newVn[i] = strtof(_getWord().c_str(), nullptr);

    _inVn.push_back(newVn);
}

void ObjParser::_parseVt()
{
    pfm::vec2 newVt;

    for (size_t i = 0 ; i < 2 ; i++)
        newVt[i] = strtof(_getWord().c_str(), nullptr);

    _inVt.push_back(newVt);
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
        if (currIndex.size())
        {
            if (!firstVertexParsed) _facesType = _facesType | FACE_ELEM_V; // replace by |= ?
            currFace.positionIndexes.push_back(
                static_cast<unsigned short>(strtof(currIndex.c_str(), nullptr)) - 1);
        }

        // Vt parsing
        currIndex.clear();
        for (j += 1; j < currVertex.size() && currVertex[j] != '/' ; j++)
            currIndex += currVertex[j];
        if (currIndex.size())
        {
            if (!firstVertexParsed) _facesType = _facesType | FACE_ELEM_VT;
            currFace.textureIndexes.push_back(
                static_cast<unsigned short>(strtof(currIndex.c_str(), nullptr)) - 1);
        }

        // Vn parsing
        currIndex.clear();
        for (j += 1 ; j < currVertex.size() ; j++)
            currIndex += currVertex[j];
        if (currIndex.size())
        {
            if (!firstVertexParsed) _facesType = _facesType | FACE_ELEM_VN;
            currFace.normalIndexes.push_back(
                static_cast<unsigned short>(strtof(currIndex.c_str(), nullptr)) - 1);
        }

        firstVertexParsed = true;
    }

    _inFaces.push_back(currFace);
}

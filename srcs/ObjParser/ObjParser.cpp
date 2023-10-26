#include "../includes/ObjParser.hpp"
#include "../includes/Logger.hpp"
#include <cstdlib>


ObjParser::ObjParser()
{
    _inV.clear();
    _inVn.clear();
    _inVt.clear();
    _inFaces.clear();
    _facesType = 0;
    _outIndices.clear();
    _outVertices.clear();
    _outTextures.clear();
}

void ObjParser::parse(char * const path)
{
    _ifs.open(path);

    if (!_ifs.is_open())
        throw std::runtime_error("ObjParse :: Couldn't open file");

    while (!_isEOF())
        _parseLine();

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

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

void ObjParser::parse(std::string const & path)
{
    if (path.substr(path.length() - 3, path.length()) != "obj")
        throw std::runtime_error("ObjParser :: Object file extension isn't .obj");

    _ifs.open(path);

    if (!_ifs.is_open())
        throw std::runtime_error("ObjParse :: Couldn't open file");

    while (!_ifs.eof())
        _parseLine();

    Logger::info(false) << "ObjParser successfully parsed \"" << path << "\"" << std::endl; 
    Logger::info(false) << "v: " << _inV.size() << std::endl;
    Logger::info(false) << "vn: " << _inVn.size() << std::endl;
    Logger::info(false) << "vt: " << _inVt.size() << std::endl;
    Logger::info(false) << "f: " << _inFaces.size() << std::endl;

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
    static bool firstPositionParsed = false;

    for (size_t i = 0 ; i < 3 ; i++)
        newV[i] = strtof(_getWord().c_str(), nullptr);

    if (!firstPositionParsed)
    {
        BoundingBox.min_x = BoundingBox.max_x = newV.x;
        BoundingBox.min_y = BoundingBox.max_y = newV.y;
        BoundingBox.min_z = BoundingBox.max_z = newV.z;
        firstPositionParsed = true;
    }

    BoundingBox.min_x = std::min(BoundingBox.min_x, newV.x);
    BoundingBox.min_y = std::min(BoundingBox.min_y, newV.y);
    BoundingBox.min_z = std::min(BoundingBox.min_z, newV.z);
    BoundingBox.max_x = std::max(BoundingBox.max_x, newV.x);
    BoundingBox.max_y = std::max(BoundingBox.max_y, newV.y);
    BoundingBox.max_z = std::max(BoundingBox.max_z, newV.z);

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

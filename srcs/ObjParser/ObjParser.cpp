#include "../includes/ObjParser.hpp"
#include "../includes/Logger.hpp"
#include <cstdlib>
#include <algorithm>

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
        _f.push_back(static_cast<unsigned int>(strtof(currIndice.c_str(), nullptr)) - 1);
        currIndice.clear();
        j++;
        for (; j < currFace.size() && currFace[j] != '/' ; j++)
            currIndice += currFace[j];
        _f.push_back(static_cast<unsigned int>(strtof(currIndice.c_str(), nullptr)) - 1);
        currIndice.clear();
        j++;
        for (; j < currFace.size() ; j++)
            currIndice += currFace[j];
        _f.push_back(static_cast<unsigned int>(strtof(currIndice.c_str(), nullptr)) - 1);
    }
}


Mesh    ObjParser::buildMesh()
{
    std::vector<Vertex>         vertices;
    std::vector<unsigned int>   indices;
    std::vector<Texture>        textures;

    for (size_t i = 0 ; i < _f.size() ; i += 3)
    {
        // Build current vertex
        Vertex  currVertex;
        currVertex.position = _v[_f[i]];
        currVertex.texCoords = _vt[_f[i+1]];
        currVertex.normal = _vn[_f[i+2]];

        // Find if already exists
        std::vector<Vertex>::iterator it = std::find_if(vertices.begin(), vertices.end(),
        [&currVertex](const Vertex& v) {
            return v.position.x == currVertex.position.x && v.position.y == currVertex.position.y && v.position.z == currVertex.position.z
                && v.normal.x == currVertex.normal.x && v.normal.y == currVertex.normal.y && v.normal.z == currVertex.normal.z
                && v.texCoords.x == currVertex.texCoords.x && v.texCoords.y == currVertex.texCoords.y;
        });

        // Similar vertex ?
        // - indices.push_back(index)
        if (it != vertices.end())
        {
            indices.push_back(std::distance(vertices.begin(), it));
        }
        // New vertex ?
        //  - vertices.push_back(currVertex)
        //  - indices.push_back(vertices.size()-1) <- last elem
        else
        {
            vertices.push_back(currVertex);
            indices.push_back(vertices.size() - 1);
        }
    }

    return (Mesh(vertices, indices, textures));
}
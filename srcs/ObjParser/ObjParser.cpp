#include "../includes/ObjParser.hpp"
#include "../includes/Logger.hpp"
#include <cstdlib>
#include <algorithm>
#include <unistd.h>

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


Mesh    ObjParser::buildMesh()
{
    std::vector<Vertex>         vertices;
    std::vector<unsigned int>   indices;
    std::vector<Texture>        textures;

    // Make triangles from vertexNb = 4
    for (std::vector<Face>::iterator it = _faces.begin() ; it != _faces.end() ; it++)
    {
        if (it->vertexNb != 4)
            continue ;

        Face  newFace1 = {};
        Face  newFace2 = {};

        newFace1.vertexNb = 3;
        newFace2.vertexNb = 3;

        newFace1.positionIndexes.push_back(it->positionIndexes[0]);
        newFace1.positionIndexes.push_back(it->positionIndexes[1]);
        newFace1.positionIndexes.push_back(it->positionIndexes[3]);

        newFace2.positionIndexes.push_back(it->positionIndexes[1]);
        newFace2.positionIndexes.push_back(it->positionIndexes[2]);
        newFace2.positionIndexes.push_back(it->positionIndexes[3]);

        newFace1.normalIndexes.push_back(it->normalIndexes[0]);
        newFace1.normalIndexes.push_back(it->normalIndexes[1]);
        newFace1.normalIndexes.push_back(it->normalIndexes[3]);

        newFace2.normalIndexes.push_back(it->normalIndexes[1]);
        newFace2.normalIndexes.push_back(it->normalIndexes[2]);
        newFace2.normalIndexes.push_back(it->normalIndexes[3]);

        newFace1.textureIndexes.push_back(it->textureIndexes[0]);
        newFace1.textureIndexes.push_back(it->textureIndexes[1]);
        newFace1.textureIndexes.push_back(it->textureIndexes[3]);

        newFace2.textureIndexes.push_back(it->textureIndexes[1]);
        newFace2.textureIndexes.push_back(it->textureIndexes[2]);
        newFace2.textureIndexes.push_back(it->textureIndexes[3]);

        _faces.push_back(newFace1);
        _faces.push_back(newFace2);

    }

    _faces.erase(std::remove_if(_faces.begin(), _faces.end(), [](const Face& face) {
        return face.vertexNb == 4;
    }), _faces.end());

    for (size_t i = 0 ; i < _faces.size() ; i++)
    {
        for (size_t j = 0 ; j < _faces[i].vertexNb ; j++)
        {
            // Build current vertex
            Vertex  currVertex = {};
            if (_facesType & FACE_ELEM_V)
                currVertex.position = _v[_faces[i].positionIndexes[j]];
            if (_facesType & FACE_ELEM_VT)
                currVertex.texCoords = _vt[_faces[i].textureIndexes[j]];
            if (_facesType & FACE_ELEM_VN)
                currVertex.normal = _vn[_faces[i].normalIndexes[j]];

            // Build indexes
            std::vector<Vertex>::iterator it = std::find_if(vertices.begin(), vertices.end(),
            [&currVertex](const Vertex& v) {
                return v.position.x == currVertex.position.x && v.position.y == currVertex.position.y && v.position.z == currVertex.position.z
                    && v.normal.x == currVertex.normal.x && v.normal.y == currVertex.normal.y && v.normal.z == currVertex.normal.z
                    && v.texCoords.x == currVertex.texCoords.x && v.texCoords.y == currVertex.texCoords.y;
            });
            if (it != vertices.end())
            {
                indices.push_back(std::distance(vertices.begin(), it));
            }
            else
            {
                vertices.push_back(currVertex);
                indices.push_back(vertices.size() - 1);
            }
        }
    }

    return (Mesh(vertices, indices, textures));
}
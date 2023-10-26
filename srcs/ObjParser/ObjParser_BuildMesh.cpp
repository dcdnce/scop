#include "../includes/ObjParser.hpp"
#include "../includes/Logger.hpp"
#include <cstdlib>
#include <algorithm>

Mesh    ObjParser::buildMesh()
{
    _buildMeshTriangulation();
    _buildMeshCraftVerticesIndices();

    return (Mesh(_outVertices, _outIndices, _outTextures, _facesType));
}

inline void    ObjParser::_buildMeshTriangulation()
{
    for (size_t i = 0 ; i < _inFaces.size() ; i++)
    {
        if (_inFaces[i].vertexNb != 4)
            continue ;

        Face  newFace1 = {};
        Face  newFace2 = {};

        newFace1.vertexNb = 3;
        newFace2.vertexNb = 3;

        newFace1.positionIndexes.push_back(_inFaces[i].positionIndexes[0]);
        newFace1.positionIndexes.push_back(_inFaces[i].positionIndexes[1]);
        newFace1.positionIndexes.push_back(_inFaces[i].positionIndexes[3]);
        newFace2.positionIndexes.push_back(_inFaces[i].positionIndexes[1]);
        newFace2.positionIndexes.push_back(_inFaces[i].positionIndexes[2]);
        newFace2.positionIndexes.push_back(_inFaces[i].positionIndexes[3]);

        if (_facesType & FACE_ELEM_VN)
        {
            newFace1.normalIndexes.push_back(_inFaces[i].normalIndexes[0]);
            newFace1.normalIndexes.push_back(_inFaces[i].normalIndexes[1]);
            newFace1.normalIndexes.push_back(_inFaces[i].normalIndexes[3]);
            newFace2.normalIndexes.push_back(_inFaces[i].normalIndexes[1]);
            newFace2.normalIndexes.push_back(_inFaces[i].normalIndexes[2]);
            newFace2.normalIndexes.push_back(_inFaces[i].normalIndexes[3]);
        }

        if (_facesType & FACE_ELEM_VT)
        {
            newFace1.textureIndexes.push_back(_inFaces[i].textureIndexes[0]);
            newFace1.textureIndexes.push_back(_inFaces[i].textureIndexes[1]);
            newFace1.textureIndexes.push_back(_inFaces[i].textureIndexes[3]);
            newFace2.textureIndexes.push_back(_inFaces[i].textureIndexes[1]);
            newFace2.textureIndexes.push_back(_inFaces[i].textureIndexes[2]);
            newFace2.textureIndexes.push_back(_inFaces[i].textureIndexes[3]);
        }

        _inFaces.push_back(newFace1);
        _inFaces.push_back(newFace2);
    }
}

inline void ObjParser::_buildMeshCraftVerticesIndices()
{
    for (size_t i = 0; i < _inFaces.size(); i++)
    {
        if (_inFaces[i].vertexNb <= 3)
        {
            for (size_t j = 0; j < _inFaces[i].vertexNb; j++)
            {
                Vertex currVertex = _buildCurrentVertex(i, j);
                size_t index = _findOrAddVertex(currVertex);
                _outIndices.push_back(index);
            }
        }
    }
}

inline Vertex ObjParser::_buildCurrentVertex(size_t const faceIndex, size_t const vertexIndex)
{
    Vertex currVertex = {};
    if (_facesType & FACE_ELEM_V)
        currVertex.position = _inV[_inFaces[faceIndex].positionIndexes[vertexIndex]];
    if (_facesType & FACE_ELEM_VT)
        currVertex.texCoords = _inVt[_inFaces[faceIndex].textureIndexes[vertexIndex]];
    if (_facesType & FACE_ELEM_VN)
        currVertex.normal = _inVn[_inFaces[faceIndex].normalIndexes[vertexIndex]];
    return currVertex;
}

inline size_t ObjParser::_findOrAddVertex(const Vertex& currVertex)
{
    std::vector<Vertex>::iterator it = std::find_if(_outVertices.begin(), _outVertices.end(),
        [&currVertex](const Vertex& v) {
            return v.position == currVertex.position && v.normal == currVertex.normal && v.texCoords == currVertex.texCoords;
        });
    if (it != _outVertices.end())
    {
        return std::distance(_outVertices.begin(), it);
    }
    _outVertices.push_back(currVertex);
    return _outVertices.size() - 1;
}
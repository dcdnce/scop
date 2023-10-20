#include "../includes/ObjParser.hpp"
#include "../includes/Logger.hpp"
#include <cstdlib>
#include <algorithm>

Mesh    ObjParser::buildMesh()
{
    _buildMeshTriangulation();
    _buildMeshCraftVerticesIndices();

    return (Mesh(_outVertices, _outIndices, _outTextures));
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

        newFace1.normalIndexes.push_back(_inFaces[i].normalIndexes[0]);
        newFace1.normalIndexes.push_back(_inFaces[i].normalIndexes[1]);
        newFace1.normalIndexes.push_back(_inFaces[i].normalIndexes[3]);

        newFace2.normalIndexes.push_back(_inFaces[i].normalIndexes[1]);
        newFace2.normalIndexes.push_back(_inFaces[i].normalIndexes[2]);
        newFace2.normalIndexes.push_back(_inFaces[i].normalIndexes[3]);

        newFace1.textureIndexes.push_back(_inFaces[i].textureIndexes[0]);
        newFace1.textureIndexes.push_back(_inFaces[i].textureIndexes[1]);
        newFace1.textureIndexes.push_back(_inFaces[i].textureIndexes[3]);
                                                   
        newFace2.textureIndexes.push_back(_inFaces[i].textureIndexes[1]);
        newFace2.textureIndexes.push_back(_inFaces[i].textureIndexes[2]);
        newFace2.textureIndexes.push_back(_inFaces[i].textureIndexes[3]);

        _inFaces.push_back(newFace1);
        _inFaces.push_back(newFace2);

    }
}


inline void    ObjParser::_buildMeshCraftVerticesIndices()
{
    for (size_t i = 0 ; i < _inFaces.size() ; i++)
    {
        if (_inFaces[i].vertexNb > 3)
            continue;

        for (size_t j = 0 ; j < _inFaces[i].vertexNb ; j++)
        {
            // Build current vertex
            Vertex  currVertex = {};
            if (_facesType & FACE_ELEM_V)
                currVertex.position = _inV[_inFaces[i].positionIndexes[j]];
            if (_facesType & FACE_ELEM_VT)
                currVertex.texCoords = _inVt[_inFaces[i].textureIndexes[j]];
            if (_facesType & FACE_ELEM_VN)
                currVertex.normal = _inVn[_inFaces[i].normalIndexes[j]];

            // Build indices
            std::vector<Vertex>::iterator it = std::find_if(_outVertices.begin(), _outVertices.end(),
            [&currVertex](const Vertex& v) {
                return v.position.x == currVertex.position.x && v.position.y == currVertex.position.y && v.position.z == currVertex.position.z
                    && v.normal.x == currVertex.normal.x && v.normal.y == currVertex.normal.y && v.normal.z == currVertex.normal.z
                    && v.texCoords.x == currVertex.texCoords.x && v.texCoords.y == currVertex.texCoords.y;
            });
            if (it != _outVertices.end())
            {
                _outIndices.push_back(std::distance(_outVertices.begin(), it));
            }
            else
            {
                _outVertices.push_back(currVertex);
                _outIndices.push_back(_outVertices.size() - 1);
            }
        }
    }

}
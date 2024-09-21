#pragma once

#include "Mesh.hpp"
#include "Vertex.hpp"
#include "BoundingBoxObject.hpp"
#include "FacesType.hpp"
#include <fstream>
#include <iostream>
#include <vector>

struct Face {
    size_t vertexNb;
    std::vector<unsigned short>  positionIndexes;
    std::vector<unsigned short>  normalIndexes;
    std::vector<unsigned short>  textureIndexes;
};

class ObjParser {
    private:
        std::ifstream _ifs;
        std::vector<pfm::vec3>      _inV;
        std::vector<pfm::vec3>      _inVn;
        std::vector<pfm::vec2>      _inVt;
        std::vector<Face>           _inFaces;
        int                         _facesType;

        std::vector<Vertex> _outVertices;
        std::vector<unsigned int> _outIndices;
        std::vector<Texture> _outTextures;

        bool        _isEOF();
        bool        _isNewLine();
        std::string _getWord();
        void        _skipToNewLine();

        void    _parseLine();
        void    _parseV();
        void    _parseVn();
        void    _parseVt();
        void    _parseF();

        void    _buildMeshTriangulation();
        void    _buildMeshCraftVerticesIndices();
        void    _buildMeshCraftTexCoords();
        void    _buildMeshNormalizePosition();
        size_t  _findOrAddVertex(const Vertex& currVertex);
        Vertex  _buildCurrentVertex(size_t const faceIndex, size_t const vertexIndex);

    public:
        ObjParser();

        BoundingBoxObject BoundingBox;

        void    parse(std::string const & path);
        Mesh    buildMesh();
};
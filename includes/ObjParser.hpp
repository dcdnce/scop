#include "../includes/Mesh.hpp"
#include <fstream>
#include <iostream>
#include <vector>

#define FACE_ELEM_V 0b0001
#define FACE_ELEM_VT 0b0010
#define FACE_ELEM_VN 0b0100

#define FACE_TYPE_V  FACE_ELEM_V
#define FACE_TYPE_VVT  FACE_ELEM_V | FACE_ELEM_VT
#define FACE_TYPE_VVN  FACE_ELEM_V | FACE_ELEM_VN
#define FACE_TYPE_VVTVN  FACE_ELEM_V | FACE_ELEM_VT | FACE_ELEM_VN

struct Face {
    size_t vertexNb;
    std::vector<unsigned short>  positionIndexes;
    std::vector<unsigned short>  normalIndexes;
    std::vector<unsigned short>  textureIndexes;
};

class ObjParser {
    private:
        std::ifstream _ifs;
        std::vector<pfm::vec3>      _v;
        std::vector<pfm::vec3>      _vn;
        std::vector<pfm::vec2>      _vt;
        std::vector<Face>           _faces;
        int                         _facesType;

        bool        _isEOF();
        bool        _isNewLine();
        std::string _getWord();
        void        _skipToNewLine();

        void    _parseLine();
        void    _parseV();
        void    _parseVn();
        void    _parseVt();
        void    _parseF();

    public:
        ObjParser(char * const path);

        Mesh    buildMesh();
};
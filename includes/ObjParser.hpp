#include "../includes/Mesh.hpp"
#include <fstream>
#include <iostream>
#include <vector>

class ObjParser {
    private:
        std::ifstream _ifs;
        std::vector<pfm::vec3>      _v;
        std::vector<pfm::vec3>      _vn;
        std::vector<pfm::vec2>      _vt;
        std::vector<unsigned int>   _f;

        bool        _isEOF();
        std::string _getWord();
        void        _skipToNewLine();

        void    _parseLine();
        void    _parseV();
        void    _parseVn();
        void    _parseVt();
        void    _parseF();

    public:
        ObjParser(char * const path);
};
#include "../includes/ObjParser.hpp"
#include <cstdlib>

static inline std::string _parseIndex(std::string const & currVertex, size_t& i);
static inline void _addToIndexes(const std::string& indexStr, Face& face, int elemType);

void ObjParser::_parseF()
{
    Face currFace = {};
    static bool firstVertexParsed = false;

    while (!_isNewLine())
    {
        currFace.vertexNb += 1;
        std::string currVertex = _getWord();
        size_t i = 0;

        for (int elemType = FACE_ELEM_V; elemType <= FACE_ELEM_VN; elemType <<= 1)
        {
            std::string currIndex = _parseIndex(currVertex, i);
            if (currIndex.size())
            {
                if (!firstVertexParsed)
                    _facesType = _facesType | elemType;
                _addToIndexes(currIndex, currFace, elemType);
            }
            i++;
        }

        firstVertexParsed = true;
    }

    _inFaces.push_back(currFace);
}

static inline std::string _parseIndex(std::string const & currVertex, size_t& i)
{
    std::string currIndex;
    for (; i < currVertex.size() && currVertex[i] != '/'; i++)
    {
        currIndex += currVertex[i];
    }
    return currIndex;
}

static inline void _addToIndexes(const std::string& indexStr, Face& currFace, int elemType)
{
    const unsigned short index = static_cast<unsigned short>(strtof(indexStr.c_str(), nullptr)) - 1;
    switch (elemType)
    {
        case FACE_ELEM_V:
            currFace.positionIndexes.push_back(index);
            break;
        case FACE_ELEM_VT:
            currFace.textureIndexes.push_back(index);
            break;
        case FACE_ELEM_VN:
            currFace.normalIndexes.push_back(index);
            break;
    }
}
 
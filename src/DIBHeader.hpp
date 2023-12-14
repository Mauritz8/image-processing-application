#include <ostream>


struct DIBHeader {
    int dibHeaderSize;
    int width;
    int height;
    int colorPlanes;
    int bitsPerPixel;
    int compressionMethod;
    int imageSize;
    int horizontalRes;
    int verticalRes;
    int nColors;
    int nImportantColors;
};
std::ostream& operator<<(std::ostream& os, const DIBHeader& dibHeader);

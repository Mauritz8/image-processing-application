#include <cstdint>
#include <ostream>


struct DIBHeader {
    uint32_t dibHeaderSize;
    uint32_t width;
    uint32_t height;
    uint16_t colorPlanes;
    uint16_t bitsPerPixel;
    uint32_t compressionMethod;
    uint32_t imageSize;
    uint32_t horizontalRes;
    uint32_t verticalRes;
    uint32_t nColors;
    uint32_t nImportantColors;
};
std::ostream& operator<<(std::ostream& os, const DIBHeader& dibHeader);

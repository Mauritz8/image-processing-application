#include "DIBHeader.hpp"


std::ostream& operator<<(std::ostream& os, const DIBHeader& dibHeader) {
    os << "DIBHeader{\n"
       << "  dibHeaderSize = " << dibHeader.dibHeaderSize << "\n"
       << "  width = " << dibHeader.width << "\n"
       << "  height = " << dibHeader.height << "\n"
       << "  colorPlanes = " << dibHeader.colorPlanes << "\n"
       << "  bitsPerPixel = " << dibHeader.bitsPerPixel << "\n"
       << "  compressionMethod = " << dibHeader.compressionMethod << "\n"
       << "  imageSize = " << dibHeader.imageSize << "\n"
       << "  horizontalRes = " << dibHeader.horizontalRes << "\n"
       << "  verticalRes = " << dibHeader.verticalRes << "\n"
       << "  nColors = " << dibHeader.nColors << "\n"
       << "  nImportantColors = " << dibHeader.nImportantColors << "\n"
       << "}\n";
    return os;
}

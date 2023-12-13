#include "DIBHeader.hpp"


std::ostream& operator<<(std::ostream& os, const DIBHeader& dibHeader) {
    os << "DIBHeader{\n"
       << "  size = " << dibHeader.size << "\n"
       << "  width = " << dibHeader.width << "\n"
       << "  height = " << dibHeader.height << "\n"
       << "  colorPlanes = " << dibHeader.colorPlanes << "\n"
       << "  bitsPerPixel = " << dibHeader.bitsPerPixel << "\n"
       << "}\n";
    return os;
}

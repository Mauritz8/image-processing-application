#include "BitmapHeader.hpp"


std::ostream& operator<<(std::ostream& os, const BitmapHeader& bitmapHeader) {
    os << "BitmapHeader{\n"
       << "  identity = " << bitmapHeader.identity[0] << bitmapHeader.identity[1] << "\n"
       << "  nBytes = " << bitmapHeader.nBytes << "\n"
       << "  reserved1 = " << bitmapHeader.reserved1 << "\n"
       << "  reserved2 = " << bitmapHeader.reserved2 << "\n"
       << "  offset = " << bitmapHeader.offset << "\n"
       << "}\n";
    return os;
}

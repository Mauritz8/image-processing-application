#include <ostream>
#include <string>


struct BitmapHeader {
    std::string identity;
    int nBytes;
    int reserved1;
    int reserved2;
    int offset;
};
std::ostream& operator<<(std::ostream& os, const BitmapHeader& bitmapHeader);

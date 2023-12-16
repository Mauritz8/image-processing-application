#include <cstdint>
#include <ostream>


#pragma pack(push, 1)
struct BitmapHeader {
    char identity[2];
    uint32_t nBytes;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
};
#pragma pack(pop)

std::ostream& operator<<(std::ostream& os, const BitmapHeader& bitmapHeader);

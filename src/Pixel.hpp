#include <cstdint>
#include <ostream>


struct Pixel {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
};

std::ostream& operator<<(std::ostream& os, const Pixel& pixel);

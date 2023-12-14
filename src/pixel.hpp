#include <ostream>


struct Pixel {
    int red;
    int green;
    int blue;
};

std::ostream& operator<<(std::ostream& os, const Pixel& pixel);

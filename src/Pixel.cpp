#include "Pixel.hpp"


std::ostream& operator<<(std::ostream& os, const Pixel& pixel) {
    os << "RGB(" 
       << (unsigned) pixel.red << ", "
       << (unsigned) pixel.green << ", "
       << (unsigned) pixel.blue << ")\n";
    return os;
}

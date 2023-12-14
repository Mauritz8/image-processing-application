#include "pixel.hpp"


std::ostream& operator<<(std::ostream& os, const Pixel& pixel) {
    os << "RGB(" 
       << pixel.red << ", "
       << pixel.green << ", "
       << pixel.blue << ")\n";
    return os;
}

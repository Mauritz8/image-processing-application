#include "Image.hpp"

#include <vector>


const std::vector<Pixel>& Image::getPixels() const {
    return pixels;
}

Pixel Image::getPixel(int pos) const {
    return pixels.at(pos);
}

void Image::flipVertically() {
    const size_t nPixels = this->pixels.size();
    std::vector<Pixel> new_pixels;
    new_pixels.reserve(nPixels);
    for (size_t i = 0; i < nPixels; i++) {
        new_pixels.push_back(this->pixels.at(nPixels - i - 1)); 
    }
    this->pixels = new_pixels;
}

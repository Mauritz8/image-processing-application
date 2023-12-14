#include "Image.hpp"


const std::vector<Pixel>& Image::getPixels() const {
    return pixels;
}

Pixel Image::getPixel(int pos) const {
    return pixels.at(pos);
}

Image Image::flipVertically() const {
    Image newImg;

    const size_t nPixels = this->pixels.size();
    newImg.pixels.reserve(nPixels);
    for (size_t i = 0; i < nPixels; i++) {
        newImg.pixels.push_back(this->pixels.at(nPixels - i - 1)); 
    }
    return newImg;
}

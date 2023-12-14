#include "Image.hpp"

#include <algorithm>
#include <vector>


const std::vector<Pixel>& Image::getPixels() const {
    return pixels;
}

Pixel Image::getPixel(int pos) const {
    return pixels.at(pos);
}

void Image::flipVertically() {
    std::reverse(pixels.begin(), pixels.end());
}

void Image::invertColor() {
    const size_t nPixels = this->pixels.size();
    for (size_t i = 0; i < nPixels; i++) {
        const Pixel p = {
            .red = 255 - pixels.at(i).red,
            .green = 255 - pixels.at(i).green,
            .blue = 255 - pixels.at(i).blue,
        };
        this->pixels.at(i) = p; 
    }
}

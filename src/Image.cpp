#include "Image.hpp"

#include <algorithm>
#include <vector>


const std::vector<Pixel>& Image::getPixels() const {
    return pixels;
}

Pixel Image::getPixel(int pos) const {
    return pixels.at(pos);
}

Image& Image::flipVertically() {
    std::reverse(pixels.begin(), pixels.end());
    return *this;
}

Image& Image::invertColor() {
    auto color_invert = [](Pixel p) {
        return Pixel{
            .red = 255 - p.red,
            .green = 255 - p.green,
            .blue = 255 - p.blue,
        };
    };

    std::transform(pixels.begin(), pixels.end(), pixels.begin(), color_invert);
    return *this;
}

Image& Image::colorRotate() {
    auto color_rotate = [](Pixel p) {
        return Pixel{
            .red = p.blue,
            .green = p.red,
            .blue = p.green,
        };
    };

    std::transform(pixels.begin(), pixels.end(), pixels.begin(), color_rotate);
    return *this;
}

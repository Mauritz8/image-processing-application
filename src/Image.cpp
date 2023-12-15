#include "Image.hpp"

#include <algorithm>
#include <vector>


const std::vector<std::vector<Pixel>>& Image::getPixels() const {
    return pixels;
}

Pixel Image::getPixel(int x, int y) const {
    return pixels.at(y).at(x);
}

int Image::getWidth() const {
    return pixels.at(0).size();
}

int Image::getHeight() const {
    return pixels.size();
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

    for (std::vector<Pixel>& row : pixels) {
        std::transform(row.begin(), row.end(), row.begin(), color_invert);
    }
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

    for (std::vector<Pixel>& row : pixels) {
        std::transform(row.begin(), row.end(), row.begin(), color_rotate);
    }
    return *this;
}

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
    auto colorInvert = [](Pixel p) {
        return Pixel{
            .red = 255 - p.red,
            .green = 255 - p.green,
            .blue = 255 - p.blue,
        };
    };

    for (std::vector<Pixel>& row : pixels) {
        std::transform(row.begin(), row.end(), row.begin(), colorInvert);
    }
    return *this;
}

Image& Image::colorRotate() {
    auto colorRotate = [](Pixel p) {
        return Pixel{
            .red = p.blue,
            .green = p.red,
            .blue = p.green,
        };
    };

    for (std::vector<Pixel>& row : pixels) {
        std::transform(row.begin(), row.end(), row.begin(), colorRotate);
    }
    return *this;
}

Image& Image::zoom(int factor) {
    scale(factor);
    crop(factor);
    return *this;
}

Image& Image::scale(int factor) {
    std::vector<std::vector<Pixel>> newPixels;
    newPixels.reserve(pixels.size() * factor);
    for (const std::vector<Pixel>& row : pixels) {
        std::vector<Pixel> newRow; 
        newRow.reserve(row.size() * factor);
        for (Pixel pixel : row) {
            for (int i = 0; i < factor; i++) {
                newRow.push_back(pixel);
            }
        }
        for (int i = 0; i < factor; i++) {
            newPixels.push_back(newRow);
        }
    }
    pixels = newPixels;

    return *this;
}

Image& Image::crop(int factor) {
    const int height = getHeight();
    const int newHeight = height / factor;
    const int heightOffset = (height - newHeight) / 2;

    const int width = getWidth();
    const int newWidth = width / factor;
    const int widthOffset = (width - newWidth) / 2;

    auto cropRow = [&](const std::vector<Pixel>& row) {
        return std::vector<Pixel>(row.begin() + widthOffset, row.end() - widthOffset);
    };

    std::vector<std::vector<Pixel>> newPixels;
    newPixels.reserve(newHeight);
    std::transform(pixels.begin() + heightOffset, pixels.end() - heightOffset, newPixels.begin(), cropRow);

    pixels = newPixels;

    return *this; 
}

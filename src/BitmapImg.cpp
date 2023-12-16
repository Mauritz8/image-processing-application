#include "BitmapImg.hpp"

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>


BitmapImg::BitmapImg(const std::string& filepath)  {
    if (!isValidBMP(filepath)) {
        throw std::invalid_argument("Invalid BMP file");
    }

    std::ifstream file(filepath, std::ifstream::binary);

    BitmapHeader bitmapHeader;
    file.read(reinterpret_cast<char*>(&bitmapHeader), sizeof(bitmapHeader));
    this->bitmapHeader = bitmapHeader;

    DIBHeader dibHeader;
    file.read(reinterpret_cast<char*>(&dibHeader), sizeof(dibHeader));
    this->dibHeader = dibHeader;
    

    const int rowPadding = dibHeader.width % 4;
    std::vector<std::vector<Pixel>> pixels;
    for (int i = 0; i < dibHeader.height; i++) {
        std::vector<Pixel> row;
        for (int j = 0; j < dibHeader.width; j++) {
            Pixel pixel;
            file.read(reinterpret_cast<char*>(&pixel), sizeof(pixel));
            row.push_back(pixel);
        }
        pixels.push_back(row);

        for (int i = 0; i < rowPadding; i++) {
            file.get();
        }
    }
    this->image = Image(pixels);


    file.close();
}

void BitmapImg::save(const std::string& filepath) {
    std::ofstream file(filepath, std::ofstream::binary);

    updateMetadata();

    file.write(reinterpret_cast<char*>(&bitmapHeader), sizeof(bitmapHeader));
    file.write(reinterpret_cast<char*>(&dibHeader), sizeof(dibHeader));

    const int nBytesPadding = image.getWidth() % 4;
    for (auto row : image.getPixels()) {
        for (auto pixel : row) {
            file.write(reinterpret_cast<char*>(&pixel), sizeof(pixel));
        }
        for (int i = 0; i < nBytesPadding; i++) {
            file << (int8_t) 0;
        }
    }

    file.close();
}

bool BitmapImg::isValidBMP(const std::string& filepath) const {
    std::ifstream file(filepath, std::ifstream::binary);

    char identity[2];
    file.read(identity, 2);
    file.close();

    const bool isValidIdentity = strcmp(identity, "BM") == 0; 
    return isValidIdentity;
}

const BitmapHeader& BitmapImg::getBitmapHeader() const {
    return bitmapHeader;
}

const DIBHeader& BitmapImg::getDIBHeader() const {
    return dibHeader;
}

Image& BitmapImg::getImage() {
    return image;
}

void BitmapImg::updateMetadata() {
    const int width = image.getWidth();
    const int height = image.getHeight();
    if (width == dibHeader.width && height == dibHeader.height) {
        return;
    }

    dibHeader.width = width;
    dibHeader.height = height;

    const int bytesPerPixel = dibHeader.bitsPerPixel / 8;
    const int paddingRow = width % 4;
    const int padding = paddingRow * height;
    dibHeader.imageSize = width * height * bytesPerPixel + padding;
    bitmapHeader.nBytes = bitmapHeader.offset + dibHeader.imageSize;
}

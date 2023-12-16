#include "BitmapImg.hpp"

#include <cstddef>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "HelperFunctions.hpp"


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

        read(rowPadding, file);
    }
    this->image = Image(pixels);


    file.close();
}

void BitmapImg::save(const std::string& filepath) {
    std::ofstream file(filepath, std::ofstream::binary);

    auto writeField = [&file](int num, int nBytes) {
        write(getBytes(num, nBytes), file);
    };

    updateMetadata();

    file << bitmapHeader.identity[0] << bitmapHeader.identity[1];
    writeField(bitmapHeader.nBytes, 4);
    writeField(bitmapHeader.reserved1, 2);
    writeField(bitmapHeader.reserved2, 2);
    writeField(bitmapHeader.offset, 4);

    writeField(dibHeader.dibHeaderSize, 4);
    writeField(dibHeader.width, 4);
    writeField(dibHeader.height, 4);
    writeField(dibHeader.colorPlanes, 2);
    writeField(dibHeader.bitsPerPixel, 2);
    writeField(dibHeader.compressionMethod, 4);
    writeField(dibHeader.imageSize, 4);
    writeField(dibHeader.horizontalRes, 4);
    writeField(dibHeader.verticalRes, 4);
    writeField(dibHeader.nColors, 4);
    writeField(dibHeader.nImportantColors, 4);

    for (auto row : image.getPixels()) {
        for (auto pixel : row) {
            writeField(pixel.blue, 1);
            writeField(pixel.green, 1);
            writeField(pixel.red, 1);
        }
        const int nBytesPadding = row.size() % 4;
        writeField(0, nBytesPadding);
    }

    file.close();
}

bool BitmapImg::isValidBMP(const std::string& filepath) const {
    std::ifstream file(filepath, std::ifstream::binary);

    const std::string identity = read(2, file);
    file.close();

    if (identity != "BM") {
        return false;
    }
    return true;
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

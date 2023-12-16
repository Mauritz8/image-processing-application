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

    auto calcBytes = [&file](int n) {
        return calcLittleEndianByteSequence(read(n, file));
    };

    const BitmapHeader bitmapHeader = {
        .identity = read(2, file),
        .nBytes = calcBytes(4), 
        .reserved1 = calcBytes(2),
        .reserved2 = calcBytes(2),
        .offset = calcBytes(4)
    };
    this->bitmapHeader = bitmapHeader;

    const DIBHeader dibHeader = {
        .dibHeaderSize = calcBytes(4),
        .width = calcBytes(4),
        .height = calcBytes(4),
        .colorPlanes = calcBytes(2),
        .bitsPerPixel = calcBytes(2),
        .compressionMethod = calcBytes(4),
        .imageSize = calcBytes(4),
        .horizontalRes = calcBytes(4),
        .verticalRes = calcBytes(4),
        .nColors = calcBytes(4),
        .nImportantColors = calcBytes(4),
    };
    this->dibHeader = dibHeader;
    

    const int rowPadding = dibHeader.width % 4;
    std::vector<std::vector<Pixel>> pixels;
    for (int i = 0; i < dibHeader.height; i++) {
        std::vector<Pixel> row;
        for (int j = 0; j < dibHeader.width; j++) {
            const int blue = calcBytes(1);
            const int green = calcBytes(1);
            const int red = calcBytes(1);


            const Pixel pixel = {
                .red = red,
                .green = green,
                .blue = blue,
            };
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

    file << bitmapHeader.identity;
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

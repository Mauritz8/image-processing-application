#include "BitmapImg.hpp"

#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "HelperFunctions.hpp"


BitmapImg::BitmapImg(const std::string& filepath)  {
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
    

    const int nPixels = dibHeader.imageSize / 3;
    std::vector<Pixel> pixels;
    pixels.reserve(nPixels);
    for (int i = 0; i < nPixels; i++) {
        const int blue = calcBytes(1);
        const int green = calcBytes(1);
        const int red = calcBytes(1);

        const Pixel pixel = {
            .red = red,
            .green = green,
            .blue = blue,
        };
        pixels.push_back(pixel);
    }
    this->image = Image(pixels);


    file.close();
}

void BitmapImg::save(const std::string& filepath) const {
    std::ofstream file(filepath, std::ofstream::binary);

    auto write_field = [&file](int num, int nBytes) {
        write(getBytes(num, nBytes), file);
    };

    file << bitmapHeader.identity;
    write_field(bitmapHeader.nBytes, 4);
    write_field(bitmapHeader.reserved1, 2);
    write_field(bitmapHeader.reserved2, 2);
    write_field(bitmapHeader.offset, 4);

    write_field(dibHeader.dibHeaderSize, 4);
    write_field(dibHeader.width, 4);
    write_field(dibHeader.height, 4);
    write_field(dibHeader.colorPlanes, 2);
    write_field(dibHeader.bitsPerPixel, 2);
    write_field(dibHeader.compressionMethod, 4);
    write_field(dibHeader.imageSize, 4);
    write_field(dibHeader.horizontalRes, 4);
    write_field(dibHeader.verticalRes, 4);
    write_field(dibHeader.nColors, 4);
    write_field(dibHeader.nImportantColors, 4);

    for (const Pixel& pixel : image.getPixels()) {
        write_field(pixel.blue, 1);
        write_field(pixel.green, 1);
        write_field(pixel.red, 1);
    }

    file.close();
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

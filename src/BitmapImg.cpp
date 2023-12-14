#include "BitmapImg.hpp"

#include <cmath>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


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
    this->header = bitmapHeader;

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
    this->pixels.reserve(nPixels);
    for (int i = 0; i < nPixels; i++) {
        const int blue = calcBytes(1);
        const int green = calcBytes(1);
        const int red = calcBytes(1);

        const Pixel pixel = {
            .red = red,
            .green = green,
            .blue = blue,
        };
        this->pixels.push_back(pixel);
    }


    file.close();
}

BitmapImg BitmapImg::createCopyExceptPixels(const BitmapImg& img) {
    BitmapImg newImg;
    newImg.header = img.header;
    newImg.dibHeader = img.dibHeader;
    return newImg;
}

void BitmapImg::save(const std::string& filepath) {
    std::ofstream file(filepath, std::ofstream::binary);

    auto write_field = [&file](int num, int nBytes) {
        write(getBytes(num, nBytes), file);
    };

    file << header.identity;
    write_field(header.nBytes, 4);
    write_field(header.reserved1, 2);
    write_field(header.reserved2, 2);
    write_field(header.offset, 4);

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

    for (const Pixel& pixel : pixels) {
        write_field(pixel.blue, 1);
        write_field(pixel.green, 1);
        write_field(pixel.red, 1);
    }

    file.close();
}

BitmapImg BitmapImg::flipVertically() const {
    BitmapImg newImg = createCopyExceptPixels(*this);

    const size_t nPixels = this->pixels.size();
    newImg.pixels.reserve(nPixels);
    for (size_t i = 0; i < nPixels; i++) {
        newImg.pixels.push_back(this->pixels.at(nPixels - i - 1)); 
    }
    return newImg;
}

std::string BitmapImg::read(int n, std::ifstream& file) {
    std::string res;
    for (int i = 0; i < n; i++) {
        res += file.get();
    }
    return res;
}

void BitmapImg::write(const std::vector<unsigned char>& chars, std::ofstream& file) {
    for (unsigned char ch : chars) {
        file << ch;
    }
}

int BitmapImg::calcLittleEndianByteSequence(const std::string& bytes) {
    const size_t nBytes = bytes.size();
    int sum = 0;
    for (size_t i = 0; i < nBytes; i++) {
        const int value = convertCharToUnsignedInt(bytes.at(i));
        sum += value * std::pow(256, i); 
    }
    return sum;
}

int BitmapImg::convertCharToUnsignedInt(char ch) {
    return static_cast<int>(static_cast<unsigned char>(ch));
}

std::vector<unsigned char> BitmapImg::getBytes(int num, int nBytes) {
    std::vector<unsigned char> bytes;
    bytes.reserve(nBytes);
    for (int i = 0; i < nBytes; i++) {
        bytes.push_back((num >> 8 * i) & 0xFF); 
    }
    return bytes;
}

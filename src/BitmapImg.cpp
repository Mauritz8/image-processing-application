#include "BitmapImg.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>


BitmapImg::BitmapImg(const std::string& filepath)  {
    std::ifstream file(filepath, std::ifstream::binary);

    auto calcBytes = [&file](int n) {return calcValue(read(n, file));};

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

    file.close();
}


std::string BitmapImg::read(int n, std::ifstream& file) {
    std::string res;
    for (int i = 0; i < n; i++) {
        res += file.get();
    }
    return res;
};

int BitmapImg::calcValue(const std::string& littleEndianBytes) {
    const int nBytes = littleEndianBytes.size();
    int sum = 0;
    for (int i = 0; i < nBytes; i++) {
        const int byte = convertCharToUnsignedByte(littleEndianBytes.at(i));
        sum += byte * std::pow(256, i); 
    }
    return sum;
}

int BitmapImg::convertCharToUnsignedByte(char ch) {
    return static_cast<int>(static_cast<unsigned char>(ch));
}

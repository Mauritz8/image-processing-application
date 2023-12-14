#include "BitmapImg.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>


BitmapImg::BitmapImg(const std::string& filepath)  {
    std::ifstream file(filepath, std::ifstream::binary);
    const std::string contents((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));

    const BitmapHeader bitmapHeader = {
        .identity = contents.substr(0, 2),
        .nBytes = calcValue(contents.substr(2, 4)), 
        .reserved1 = calcValue(contents.substr(6, 2)),
        .reserved2 = calcValue(contents.substr(8, 2)),
        .offset = calcValue(contents.substr(10, 4))
    };
    this->header = bitmapHeader;

    const DIBHeader dibHeader = {
        .dibHeaderSize = calcValue(contents.substr(14, 4)),
        .width = calcValue(contents.substr(18, 4)),
        .height = calcValue(contents.substr(22, 4)),
        .colorPlanes = calcValue(contents.substr(26, 2)),
        .bitsPerPixel = calcValue(contents.substr(28, 2)),
        .compressionMethod = calcValue(contents.substr(30, 4)),
        .imageSize = calcValue(contents.substr(34, 4)),
        .horizontalRes = calcValue(contents.substr(38, 4)),
        .verticalRes = calcValue(contents.substr(42, 4)),
        .nColors = calcValue(contents.substr(46, 4)),
        .nImportantColors = calcValue(contents.substr(50, 4)),
    };
    this->dibHeader = dibHeader;

    file.close();
}

int BitmapImg::calcValue(const std::string& littleEndianBytes) {
    const int n_bytes = littleEndianBytes.size();
    int sum = 0;
    for (int i = 0; i < n_bytes; i++) {
        const int byte = convertCharToUnsignedByte(littleEndianBytes.at(i));
        sum += byte * std::pow(256, i); 
    }
    return sum;
}

int BitmapImg::convertCharToUnsignedByte(char ch) {
    return static_cast<int>(static_cast<unsigned char>(ch));
}

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
        .nBytes = calcValue(getByteValues(contents.substr(2, 4))), 
        .reserved1 = calcValue(getByteValues(contents.substr(6, 2))),
        .reserved2 = calcValue(getByteValues(contents.substr(8, 2))),
        .offset = calcValue(getByteValues(contents.substr(10, 4)))
    };
    this->header = bitmapHeader;

    const DIBHeader dibHeader = {
        .dibHeaderSize = calcValue(getByteValues(contents.substr(14, 4))),
        .width = calcValue(getByteValues(contents.substr(18, 4))),
        .height = calcValue(getByteValues(contents.substr(22, 4))),
        .colorPlanes = calcValue(getByteValues(contents.substr(26, 2))),
        .bitsPerPixel = calcValue(getByteValues(contents.substr(28, 2))),
        .compressionMethod = calcValue(getByteValues(contents.substr(30, 4))),
        .imageSize = calcValue(getByteValues(contents.substr(34, 4))),
        .horizontalRes = calcValue(getByteValues(contents.substr(38, 4))),
        .verticalRes = calcValue(getByteValues(contents.substr(42, 4))),
        .nColors = calcValue(getByteValues(contents.substr(46, 4))),
        .nImportantColors = calcValue(getByteValues(contents.substr(50, 4))),
    };
    this->dibHeader = dibHeader;

    file.close();
}

int BitmapImg::calcValue(const std::vector<int>& littleEndianBytes) {
    int sum = 0;
    for (int i = 0; i < littleEndianBytes.size(); i++) {
        sum += littleEndianBytes.at(i) * std::pow(256, i); 
    }
    return sum;
}

int BitmapImg::convertCharToUnsignedByte(char ch) {
    return static_cast<int>(static_cast<unsigned char>(ch));
}

std::vector<int> BitmapImg::getByteValues(const std::string& str) {
    std::vector<int> values;
    values.resize(str.size());
    std::transform(str.begin(), str.end(), values.begin(), convertCharToUnsignedByte);
    return values;
}

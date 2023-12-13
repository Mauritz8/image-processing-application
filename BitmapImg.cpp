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
        .nBytes = calc_value(get_byte_values(contents.substr(2, 4))), 
        .reserved1 = calc_value(get_byte_values(contents.substr(6, 2))),
        .reserved2 = calc_value(get_byte_values(contents.substr(8, 2))),
        .offset = calc_value(get_byte_values(contents.substr(10, 4)))
    };
    this->header = bitmapHeader;

    const DIBHeader dibHeader = {
        .dibHeaderSize = calc_value(get_byte_values(contents.substr(14, 4))),
        .width = calc_value(get_byte_values(contents.substr(18, 4))),
        .height = calc_value(get_byte_values(contents.substr(22, 4))),
        .colorPlanes = calc_value(get_byte_values(contents.substr(26, 2))),
        .bitsPerPixel = calc_value(get_byte_values(contents.substr(28, 2))),
        .compressionMethod = calc_value(get_byte_values(contents.substr(30, 4))),
        .imageSize = calc_value(get_byte_values(contents.substr(34, 4))),
        .horizontalRes = calc_value(get_byte_values(contents.substr(38, 4))),
        .verticalRes = calc_value(get_byte_values(contents.substr(42, 4))),
        .nColors = calc_value(get_byte_values(contents.substr(46, 4))),
        .nImportantColors = calc_value(get_byte_values(contents.substr(50, 4))),
    };
    this->dibHeader = dibHeader;

    file.close();
}

int BitmapImg::calc_value(const std::vector<int>& little_endian_bytes) {
    int sum = 0;
    for (int i = 0; i < little_endian_bytes.size(); i++) {
        sum += little_endian_bytes.at(i) * std::pow(256, i); 
    }
    return sum;
}

int BitmapImg::convert_char_to_unsigned_byte(char ch) {
    return static_cast<int>(static_cast<unsigned char>(ch));
}

std::vector<int> BitmapImg::get_byte_values(const std::string& str) {
    std::vector<int> values;
    values.resize(str.size());
    std::transform(str.begin(), str.end(), values.begin(), convert_char_to_unsigned_byte);
    return values;
}

#include <algorithm>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>

#include "BitmapHeader.hpp"


int calc_value(std::vector<int> little_endian_bytes) {
    int sum = 0;
    for (int i = 0; i < little_endian_bytes.size(); i++) {
        sum += little_endian_bytes.at(i) * std::pow(256, i); 
    }
    return sum;
}

int get_byte_value(char ch) {
    return static_cast<int>(static_cast<unsigned char>(ch));
}

std::vector<int> get_byte_values(std::string str) {
    std::vector<int> values;
    values.resize(str.size());
    std::transform(str.begin(), str.end(), values.begin(), get_byte_value);
    return values;
}

int main() {
    std::ifstream file("test.bmp", std::ifstream::binary);
    const std::string contents((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));

    const BitmapHeader header = {
        .identity = contents.substr(0, 2),
        .size = calc_value(get_byte_values(contents.substr(2, 4))), 
        .reserved1 = calc_value(get_byte_values(contents.substr(6, 2))),
        .reserved2 = calc_value(get_byte_values(contents.substr(8, 2))),
        .offset = calc_value(get_byte_values(contents.substr(10, 4)))
    };

    file.close();
}

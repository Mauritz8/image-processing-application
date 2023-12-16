#include "HelperFunctions.hpp"

#include <cmath>


std::string read(int n, std::ifstream& file) {
    std::string res;
    for (int i = 0; i < n; i++) {
        res += file.get();
    }
    return res;
}

void write(const std::vector<unsigned char>& chars, std::ofstream& file) {
    for (unsigned char ch : chars) {
        file << ch;
    }
}

std::vector<unsigned char> getBytes(int num, int nBytes) {
    std::vector<unsigned char> bytes;
    bytes.reserve(nBytes);
    for (int i = 0; i < nBytes; i++) {
        bytes.push_back((num >> 8 * i) & 0xFF); 
    }
    return bytes;
}

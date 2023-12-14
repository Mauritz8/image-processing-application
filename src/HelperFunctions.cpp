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

int calcLittleEndianByteSequence(const std::string& bytes) {
    const size_t nBytes = bytes.size();
    int sum = 0;
    for (size_t i = 0; i < nBytes; i++) {
        const int value = convertCharToUnsignedInt(bytes.at(i));
        sum += value * std::pow(256, i); 
    }
    return sum;
}

int convertCharToUnsignedInt(char ch) {
    return static_cast<int>(static_cast<unsigned char>(ch));
}

std::vector<unsigned char> getBytes(int num, int nBytes) {
    std::vector<unsigned char> bytes;
    bytes.reserve(nBytes);
    for (int i = 0; i < nBytes; i++) {
        bytes.push_back((num >> 8 * i) & 0xFF); 
    }
    return bytes;
}

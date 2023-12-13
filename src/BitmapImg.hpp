#include <fstream>
#include <string>
#include <vector>

#include "BitmapHeader.hpp"
#include "DIBHeader.hpp"


class BitmapImg {
    public:
        BitmapHeader header;
        DIBHeader dibHeader;

        BitmapImg(const std::string& filepath);

    private:
        static int calcValue(const std::vector<int>& little_endian_bytes);
        static int convertCharToUnsignedByte(char ch);
        static std::vector<int> getByteValues(const std::string& str);
};

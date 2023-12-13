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
        static int calc_value(const std::vector<int>& little_endian_bytes);
        static int convert_char_to_unsigned_byte(char ch);
        static std::vector<int> get_byte_values(const std::string& str);
};

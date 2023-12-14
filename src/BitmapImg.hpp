#include <fstream>
#include <string>
#include <vector>

#include "BitmapHeader.hpp"
#include "DIBHeader.hpp"
#include "Pixel.hpp"


class BitmapImg {
    public:
        BitmapHeader header;
        DIBHeader dibHeader;
        std::vector<Pixel> pixels;

        BitmapImg(const std::string& filepath);

    private:
        static std::string read(int n, std::ifstream& file);
        static int calcLittleEndianByteSequence(const std::string& bytes);
        static int convertCharToUnsignedInt(char ch);
};

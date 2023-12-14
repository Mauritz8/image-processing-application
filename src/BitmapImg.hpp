#include <string>
#include <vector>

#include "BitmapHeader.hpp"
#include "DIBHeader.hpp"
#include "Image.hpp"


class BitmapImg {
    public:
        BitmapHeader header;
        DIBHeader dibHeader;
        Image image;

        BitmapImg(const std::string& filepath);
        void save(const std::string& filepath) const;
};

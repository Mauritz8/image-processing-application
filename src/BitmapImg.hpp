#include <string>
#include <vector>

#include "BitmapHeader.hpp"
#include "DIBHeader.hpp"
#include "Image.hpp"


class BitmapImg {
    public:
        Image image;

        BitmapHeader getBitmapHeader() const;
        DIBHeader getDIBHeader() const;

        BitmapImg(const std::string& filepath);
        void save(const std::string& filepath) const;

    private:
        BitmapHeader bitmapHeader;
        DIBHeader dibHeader;
};

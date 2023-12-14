#include <string>
#include <vector>

#include "BitmapHeader.hpp"
#include "DIBHeader.hpp"
#include "Image.hpp"


class BitmapImg {
    public:
        BitmapImg(const std::string& filepath);
        void save(const std::string& filepath) const;

        const BitmapHeader& getBitmapHeader() const;
        const DIBHeader& getDIBHeader() const;
        Image& getImage();

    private:
        BitmapHeader bitmapHeader;
        DIBHeader dibHeader;
        Image image;
};

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

        BitmapImg() {};
        BitmapImg(const std::string& filepath);
        static BitmapImg createCopyExceptPixels(const BitmapImg& img);

        void save(const std::string& filepath) const;
        BitmapImg flipVertically() const;
};

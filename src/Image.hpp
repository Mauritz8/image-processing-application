#include <vector>

#include "Pixel.hpp"


class Image {
    public:
        Image() {};
        Image(const std::vector<Pixel>& pixels) : pixels(pixels){};

        const std::vector<Pixel>& getPixels() const;
        Pixel getPixel(int pos) const;

        Image& flipVertically();
        Image& invertColor();

    private:
        std::vector<Pixel> pixels;
};

#include <vector>

#include "Pixel.hpp"


class Image {
    public:
        Image() {};
        Image(const std::vector<std::vector<Pixel>>& pixels) : pixels(pixels){};

        const std::vector<std::vector<Pixel>>& getPixels() const;
        Pixel getPixel(int x, int y) const;

        Image& flipVertically();
        Image& invertColor();
        Image& colorRotate();

    private:
        std::vector<std::vector<Pixel>> pixels;
};

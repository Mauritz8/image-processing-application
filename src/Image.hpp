#include <vector>

#include "Pixel.hpp"


class Image {
    public:
        Image() {};
        Image(const std::vector<std::vector<Pixel>>& pixels) : pixels(pixels){};

        const std::vector<std::vector<Pixel>>& getPixels() const;
        Pixel getPixel(int x, int y) const;
        int getWidth() const;
        int getHeight() const;

        Image& flipVertically();
        Image& invertColor();
        Image& colorRotate();
        Image& zoom(int factor);
        Image& scale(int factor);
        Image& crop(int factor);

    private:
        std::vector<std::vector<Pixel>> pixels;
};

#include <iostream>

#include "BitmapImg.hpp"


int main() {
    BitmapImg bitmapImg = BitmapImg("test.bmp");
    std::cout << bitmapImg.getBitmapHeader();
    std::cout << bitmapImg.getDIBHeader();
}

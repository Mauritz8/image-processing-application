#include <iostream>

#include "BitmapImg.hpp"


int main() {
    BitmapImg bitmapImg = BitmapImg("red.bmp");
    std::cout << bitmapImg.header;
    std::cout << bitmapImg.dibHeader;
}

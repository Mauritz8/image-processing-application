#include <iostream>

#include "BitmapImg.hpp"


int main() {
    BitmapImg bitmapImg = BitmapImg("test.bmp");
    std::cout << bitmapImg.header;
    std::cout << bitmapImg.dibHeader;
}

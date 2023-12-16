#include <iostream>

#include "BitmapImg.hpp"


int main() {
    BitmapImg bitmapImg = BitmapImg("test2.bmp");
    bitmapImg.getImage()
        .flipVertically()
        .colorRotate();
    bitmapImg.save("new-test.bmp");
}

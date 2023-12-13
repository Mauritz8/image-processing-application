#include <ostream>


class DIBHeader {
    public:
        int size;
        int width;
        int height;
        int colorPlanes;
        int bitsPerPixel;

        friend std::ostream& operator<<(std::ostream& os, const DIBHeader& dibHeader);
};

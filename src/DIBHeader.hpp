#include <ostream>


class DIBHeader {
    public:
        int dibHeaderSize;
        int width;
        int height;
        int colorPlanes;
        int bitsPerPixel;
        int compressionMethod;
        int imageSize;
        int horizontalRes;
        int verticalRes;
        int nColors;
        int nImportantColors;

        friend std::ostream& operator<<(std::ostream& os, const DIBHeader& dibHeader);
};

#include <ostream>
#include <string>


class BitmapHeader {
    public:
        std::string identity;
        int nBytes;
        int reserved1;
        int reserved2;
        int offset;

        friend std::ostream& operator<<(std::ostream& os, const BitmapHeader& bitmapHeader);
};

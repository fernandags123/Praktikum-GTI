#include <assert.h>
#include <fstream>
#include "imageloader.h"

using namespace std;

Image::Image(char* ps, int w, int h)
    : pixels(ps), width(w), height(h) {
}

Image::~Image() {
    delete[] pixels;
}

namespace {

// Konversi 4 byte ke integer (little endian)
int toInt(const char* bytes) {
    return (int)(
        ((unsigned char)bytes[3] << 24) |
        ((unsigned char)bytes[2] << 16) |
        ((unsigned char)bytes[1] << 8)  |
        (unsigned char)bytes[0]
    );
}

// Konversi 2 byte ke short (little endian)
short toShort(const char* bytes) {
    return (short)(
        ((unsigned char)bytes[1] << 8) |
        (unsigned char)bytes[0]
    );
}

// Baca integer
int readInt(ifstream& input) {
    char buffer[4];
    input.read(buffer, 4);
    return toInt(buffer);
}

// Baca short
short readShort(ifstream& input) {
    char buffer[2];
    input.read(buffer, 2);
    return toShort(buffer);
}

// Smart array sederhana
template<class T>
class auto_array {
private:
    T* array;
    mutable bool isReleased;

public:
    explicit auto_array(T* array_ = NULL)
        : array(array_), isReleased(false) {
    }

    auto_array(const auto_array<T>& aarray) {
        array = aarray.array;
        isReleased = aarray.isReleased;
        aarray.isReleased = true;
    }

    ~auto_array() {
        if (!isReleased && array != NULL) {
            delete[] array;
        }
    }

    T* get() const {
        return array;
    }

    T* release() {
        isReleased = true;
        return array;
    }

    T& operator[](int i) {
        return array[i];
    }
};

} // namespace

Image* loadBMP(const char* filename) {

    ifstream input(filename, ios::binary);

    assert(!input.fail() && "File tidak ditemukan!");

    char buffer[2];
    input.read(buffer, 2);

    assert(buffer[0] == 'B' && buffer[1] == 'M' &&
           "Bukan file bitmap!");

    input.ignore(8);

    int dataOffset = readInt(input);

    int headerSize = readInt(input);

    int width;
    int height;

    switch (headerSize) {

        case 40:
            width = readInt(input);
            height = readInt(input);

            input.ignore(2);

            assert(readShort(input) == 24 &&
                   "Gambar bukan 24-bit BMP!");

            assert(readShort(input) == 0 &&
                   "BMP terkompres tidak didukung!");

            break;

        case 12:
            width = readShort(input);
            height = readShort(input);

            input.ignore(2);

            assert(readShort(input) == 24 &&
                   "Gambar bukan 24-bit BMP!");

            break;

        default:
            assert(!"Format BMP tidak didukung!");
    }

    // Hitung padding
    int bytesPerRow = ((width * 3 + 3) / 4) * 4;

    int size = bytesPerRow * height;

    auto_array<char> pixels(new char[size]);

    input.seekg(dataOffset, ios::beg);

    input.read(pixels.get(), size);

    // Konversi BGR -> RGB
    // Konversi BGR -> RGB
auto_array<char> pixels2(new char[width * height * 3]);

for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {

        int srcPos = bytesPerRow * y + 3 * x;
        int dstPos = 3 * ((height - 1 - y) * width + x);

        // Blue -> Red
        pixels2[dstPos] = pixels[srcPos + 2];

        // Green
        pixels2[dstPos + 1] = pixels[srcPos + 1];

        // Red -> Blue
        pixels2[dstPos + 2] = pixels[srcPos];
    }
}

    input.close();

    return new Image(pixels2.release(), width, height);
}

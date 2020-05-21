#include <iostream>
#include <string>
#include <string.h>

using namespace std;
struct uint24_t
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};
class Bitmap
{
private:

    char tag[2];
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t pixelOffset;
    uint32_t headersize;
    int32_t imageWidth;
    int32_t imageHeight;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xPixels;
    int32_t yPixels;
    uint32_t totalColors;
    uint32_t importantColors;
    uint32_t redMask;
    uint32_t greenMask;
    uint32_t blueMask;
    uint32_t alphaMask;
    uint32_t * data;
    uint24_t * data2;
    uint32_t padding;

    int pixelCount;
    char buffer[68];
    uint32_t modifyPixel (uint32_t orig, uint32_t mask, uint32_t newVal);
    uint24_t modifyPixel (uint24_t orig, char color, uint8_t newVal);
    uint32_t getColorVal  ( uint32_t value, uint32_t mask);
    uint8_t getColorVal (uint24_t value, char color);
    void pixelateBox (Bitmap & b, uint32_t startingR, uint32_t startingC, uint32_t endingR, uint32_t endingC);
    void gaussPoint (Bitmap & b, int height, int width);



    /**
     * Read in an image.
     * reads a bitmap in from the stream
     *
     * @param in the stream to read from.
     * @param b the bitmap that we are creating.
     *
     * @return the stream after we've read in the image.
     *
     * @throws BitmapException if it's an invalid bitmap.
     * @throws bad_alloc exception if we failed to allocate memory.
     */
    friend std::istream& operator>>(std::istream& in, Bitmap& b) {

        in.read((char*)&b.tag,2);

        cout << b.tag[0] << " : " << b.tag[1] << endl;
        if(strncmp (b.tag, "BM",2)) {
            cout << "File not recognized as BMP format" << endl;
        }

        in.read((char*)&b.fileSize,4);
        cout << b.fileSize << " filesize" << endl;

        in.read((char*)&b.reserved1,2);
        in.read((char*)&b.reserved2,2);
        cout << b.reserved1 << " reserved 1 " << b.reserved2 << " reserved 2" << endl;


        in.read((char*)&b.pixelOffset,4);
        cout << b.pixelOffset << " offset" << endl;

        in.read((char*)&b.headersize,4);
        cout << b.headersize << " headersize" << endl;

        in.read((char*)&b.imageWidth,4);
        cout << b.imageWidth << " width" << endl;

        in.read((char*)&b.imageHeight,4);
        cout << b.imageHeight << " height" << endl;

        in.read((char*)&b.planes,2);
        cout << b.planes << " planes" << endl;

        in.read((char*)&b.bitsPerPixel,2);
        cout << b.bitsPerPixel << " bitsPerPixel" << endl;

        in.read((char*)&b.compression,4);
        cout << b.compression << " compression" << endl;

        in.read((char*)&b.imageSize,4);
        cout << b.imageSize << " imagesize" << endl;

        in.read((char*)&b.xPixels,4);
        cout << b.xPixels << " xPixels" << endl;

        in.read((char*)&b.yPixels,4);
        cout << b.yPixels << " yPixels" << endl;

        in.read((char*)&b.totalColors,4);
        cout << b.totalColors << " totalColors" << endl;

        in.read((char*)&b.importantColors,4);
        cout << b.importantColors << " importantColors" << endl;

        if (b.compression == 3){
            in.read((char *) &b.redMask, 4);
            cout << hex << b.redMask << " redMask" << endl;

            in.read((char *) &b.greenMask, 4);
            cout << hex << b.greenMask << " greenMask" << endl;

            in.read((char *) &b.blueMask, 4);
            cout << hex << b.blueMask << " blueMask" << endl;

            in.read((char *) &b.alphaMask, 4);
            cout << hex << b.alphaMask << " alphaMask" << endl;

            in.read((char *) &b.alphaMask, 68);
            cout << "read in 68 useless bits" << endl;
        }

        b.pixelCount = b.imageWidth * b.imageHeight;

        b.data = new uint32_t[b.pixelCount];
        b.data2 = new uint24_t[b.pixelCount];

        if (b.compression == 3) {
            cout << "Compression mode is 32 bits, currently ingesting" << endl;
            in.read((char*) b.data, b.pixelCount * 4);

        } else {
            cout << "Compression mode is 24 bits, currently ingesting" << endl;
            uint32_t padCounter = 0;
            uint32_t temp = b.imageWidth * 3;
            while(temp % 4 != 0) {
                temp++;
                padCounter++;
            }
            b.padding = padCounter;

            for(int i = 0; i < b.imageHeight; i++) {
                in.read((char*) &b.data2[i * b.imageWidth], 3*b.imageWidth);
                in.ignore(b.padding);
            }
        }

        return in;
    };


    /**
     * Write the binary representation of the image to the stream.
     *
     * @param out the stream to write to.
     * @param b the bitmap that we are writing.
     *
     * @return the stream after we've finished writting.
     *
     * @throws failure if we failed to write.
     */
    friend std::ostream& operator<<(std::ostream& in, Bitmap& b) {
        in.write((char*)&b.tag,2);

        cout << b.tag[0] << " : " << b.tag[1] << endl;

        in.write((char*)&b.fileSize,4);
        cout << b.fileSize << " filesize" << endl;

        in.write((char*)&b.reserved1,2);
        in.write((char*)&b.reserved2,2);
        cout << b.reserved1 << " reserved 1 " << b.reserved2 << " reserved 2" << endl;


        in.write((char*)&b.pixelOffset,4);
        cout << b.pixelOffset << " offset" << endl;

        in.write((char*)&b.headersize,4);
        cout << b.headersize << " headersize" << endl;

        in.write((char*)&b.imageWidth,4);
        cout << b.imageWidth << " width" << endl;

        in.write((char*)&b.imageHeight,4);
        cout << b.imageHeight << " height" << endl;

        in.write((char*)&b.planes,2);
        cout << b.planes << " planes" << endl;

        in.write((char*)&b.bitsPerPixel,2);
        cout << b.bitsPerPixel << " bitsPerPixel" << endl;

        in.write((char*)&b.compression,4);
        cout << b.compression << " compression" << endl;

        in.write((char*)&b.imageSize,4);
        cout << b.imageSize << " imagesize" << endl;

        in.write((char*)&b.xPixels,4);
        cout << b.xPixels << " xPixels" << endl;

        in.write((char*)&b.yPixels,4);
        cout << b.yPixels << " yPixels" << endl;

        in.write((char*)&b.totalColors,4);
        cout << b.totalColors << " totalColors" << endl;

        in.write((char*)&b.importantColors,4);
        cout << b.importantColors << " importantColors" << endl;

        if (b.compression == 3){
            in.write((char *) &b.redMask, 4);
            cout << hex << b.redMask << " redMask" << endl;

            in.write((char *) &b.greenMask, 4);
            cout << hex << b.greenMask << " greenMask" << endl;

            in.write((char *) &b.blueMask, 4);
            cout << hex << b.blueMask << " blueMask" << endl;

            in.write((char *) &b.alphaMask, 4);
            cout << hex << b.alphaMask << " alphaMask" << endl;

            in.write((char *) &b.alphaMask, 68);
        }

        if (b.compression == 3) {
            cout << "32 bits, currently writing" << endl;
            in.write((char*) b.data, 4*b.pixelCount);
        } else {
            cout << "24 bits, currently writing" << endl;
            for(int i = 0; i < b.imageHeight; i++) {
                in.write((char*) &b.data2[i * b.imageWidth], 3*b.imageWidth);
                uint8_t zero = 0;
                for (int j = 0; j < b.padding; j++){
                    in.write((char*) & zero, 1);
                }
            }
        }

        return in;
    };

public:
    Bitmap();

/**
 * cell shade an image.
 * for each component of each pixel we round to
 * the nearest number of 0, 180, 255
 *
 * This has the effect of making the image look like.
 * it was colored.
 */
    void cellShade(Bitmap& b);

/**
 * Grayscales an image by averaging all of the components.
 */
    void grayscale(Bitmap& b);

/**
 * Pixelats an image by creating groups of 16*16 pixel blocks.
 */
    void pixelate(Bitmap& b);

/**
 * Use gaussian bluring to blur an image.
 */
    void blur(Bitmap& b);

/**
 * rotates image 90 degrees, swapping the height and width.
 */
    void rot90(Bitmap& b);

/**
 * rotates an image by 180 degrees.
 */
    void rot180(Bitmap& b);

/**
 * rotates image 270 degrees, swapping the height and width.
 */
    void rot270(Bitmap& b);

/**
 * flips and image over the vertical axis.
 */
    void flipv(Bitmap& b);

/**
 * flips and image over the horizontal axis.
 */
    void fliph(Bitmap& b);

/**
 * flips and image over the line y = -x, swapping the height and width.
 */
    void flipd1(Bitmap& b);

/**
 * flips and image over the line y = xr, swapping the height and width.
 */
    void flipd2(Bitmap& b);

/**
 * scales the image by a factor of 2.
 */
    void scaleUp(Bitmap& b);

/**
 * scales the image by a factor of 1/2.
 */
    void scaleDown(Bitmap& b);

/**
 * Adds noise of pixelChangePer (%) and pixelChangeAmt.
 */
    void addNoise (Bitmap & b, int pixelChangePer, uint8_t pixelChangeAmt);
};

class BitmapException : public std::exception
{
    // the message to print out
    std::string _message;

    // position in the bitmap file (in bytes) where the error occured.
    uint32_t _position;

public:
    BitmapException() = delete;

    BitmapException(const std::string& message, uint32_t position);
    BitmapException(std::string&& message, uint32_t position);


    void print_exception() {}
};

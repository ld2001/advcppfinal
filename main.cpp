#include <iostream>
#include <fstream>
#include <string>
#include "bitmap.h"

using namespace std;

int main(int argc, char** argv)
{
    struct int24{
        unsigned int data : 24;
    };

    if(argc != 4)
    {
        cout << "usage:\n"
             << "bitmap option inputfile.bmp outputfile.bmp\n"
             << "options:\n"
             << "  -c cell shade\n"
             << "  -g gray scale\n"
             << "  -p pixelate\n"
             << "  -b blur\n"
             << "  -r90 rotate 90\n"
             << "  -r180 rotate 180\n"
             << "  -r270 rotate 270\n"
             << "  -v flip vertically\n"
             << "  -h flip horizontally\n"
             << "  -d1 flip diagonally 1\n"
             << "  -d2 flip diagonally 2\n"
             << "  -grow scale the image by 2\n"
             << "  -shrink scale the image by .5" << endl;

        return 0;
    }

    string flag(argv[1]);
    string infile(argv[2]);
    string outfile(argv[3]);

    ifstream in;
    Bitmap image;
    ofstream out;

    try
    {
        in.open(infile, ios::binary);
        in >> image;
        in.close();
    }
    catch(BitmapException& e)
    {
        e.print_exception();
        return 0;
    }

    if(flag == "-c"s)
    {
        image.cellShade(image);
//        cellShade(image);
    }
    if(flag == "-g"s)
    {
        image.grayscale(image);
//        grayscale(image);
    }
    if(flag == "-p"s)
    {
        image.pixelate(image);
//        pixelate(image);
    }
    if(flag == "-b"s)
    {
        image.blur(image);
//        blur(image);
    }
    if(flag == "-r90"s)
    {
        image.rot90(image);
//        rot90(image);
    }
    if(flag == "-r180"s)
    {
        image.rot180(image);
//        rot180(image);
    }
    if(flag == "-r270"s)
    {
        image.rot270(image);
//        rot270(image);
    }
    if(flag == "-v"s)
    {
        image.flipv(image);
//        flipv(image);
    }
    if(flag == "-h"s)
    {
        image.fliph(image);
//        fliph(image);
    }
    if(flag == "-d1"s)
    {
        image.flipd1(image);
//        flipd1(image);
    }
    if(flag == "-d2"s)
    {
        image.flipd2(image);
//        flipd2(image);
    }
    if(flag == "-grow"s)
    {
        image.scaleUp(image);
//        scaleUp(image);
    }
    if(flag == "-shrink"s)
    {
        image.scaleDown(image);
//        scaleDown(image);
    }
    if(flag == "-noise"s)
    {
        image.addNoise(image,100,10);
//        scaleDown(image);
    }

    out.open(outfile, ios::binary);
    out << image;
    out.close();

    return 0;
}


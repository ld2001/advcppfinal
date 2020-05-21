//
// Created by LDin21 on 3/31/2020.
//

#include "bitmap.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>

Bitmap::Bitmap () {}

void Bitmap::cellShade(Bitmap& b){

    if (&b == NULL){
        cout << "Please enter a valid bitmap" << endl;
        return;
    }

    // Create r,g,b masks for 32-bit and 24-bit arrays
    uint32_t dataMask[3] = {b.redMask,b.greenMask,b.blueMask};
    char data2Mask[3] = {'r','g','b'};

    // If 32-bits
    if (b.compression == 3) {
        // For every pixel
        for (int i = 0; i < b.pixelCount; i++) {
            // For every color
            for(int k = 0; k < 3; k++) {
                // Get the pixel value for that color
                uint32_t currentVal = getColorVal(b.data[i],dataMask[k]);
                // Round it to 0, 155, or 255
                if(currentVal < 64) {
                    b.data[i] = b.modifyPixel(b.data[i],dataMask[k],0);
                } else if (currentVal < 192) {
                    b.data[i] = b.modifyPixel(b.data[i],dataMask[k],155);
                } else {
                    b.data[i] = b.modifyPixel(b.data[i],dataMask[k],255);
                }
            }
        }
    } else {
        // Parallel to above section, except for 24 bit coloring
        for (int i = 0; i < b.pixelCount; i++) {
            for(int k = 0; k < 3; k++) {
                uint8_t currentVal = getColorVal(b.data2[i],data2Mask[k]);
                if(currentVal < 64) {
                    b.data2[i] = b.modifyPixel(b.data2[i],data2Mask[k],0);
                } else if (currentVal < 192) {
                    b.data2[i] = b.modifyPixel(b.data2[i],data2Mask[k],155);
                } else {
                    b.data2[i] = b.modifyPixel(b.data2[i],data2Mask[k],255);
                }
            }
        }
    }
}

/**
 * Grayscales an image by averaging all of the components.
 */
void Bitmap::grayscale(Bitmap& b){

    if (&b == NULL){
        cout << "Please enter a valid bitmap" << endl;
        return;
    }

    uint32_t dataMask[3] = {b.redMask,b.greenMask,b.blueMask};
    char data2Mask[3] = {'r','g','b'};

    if (b.compression == 3) {
        // For every pixel
        for (int i = 0; i < b.pixelCount; i++) {
            // Create a sum counter to count the total color vals for all three colors
            uint32_t sum = 0;
            // For every color add to counter
            for(int k = 0; k < 3; k++) {
                sum += getColorVal(b.data[i],dataMask[k]);
            }
            // Divide by three to get grayscale value
            sum = sum / 3;
            // Assign values to k
            for(int k = 0; k < 3; k++) {
                b.data[i] = modifyPixel(b.data[i],dataMask[k],sum);
            }
        }
    } else {
            // Parallel to above section, except for a uint32_t to uint8_t casting to adjust for data structures
            for (int i = 0; i < b.pixelCount; i++) {
                uint32_t sum = 0;
                for(int k = 0; k < 3; k++) {
                    sum = sum + getColorVal(b.data2[i],data2Mask[k]);
                }

                sum = sum / 3;
                sum = (uint8_t) sum;

                for(int j = 0; j < 3; j++) {
                    b.data2[i] = modifyPixel(b.data2[i],data2Mask[j],sum);
                }
        }
    }
}

/**
 * Pixelats an image by creating groups of 16*16 pixel blocks.
 */
void Bitmap::pixelate(Bitmap& b){
    if (&b == NULL){
        cout << "Please enter a valid bitmap" << endl;
        return;
    }

    // complete number of rows and columns
    uint32_t completeRows = b.imageHeight / 16;
    uint32_t completeCols = b.imageWidth / 16;

    // Call the pixelate box function for all complete columns
    for(int i = 0; i < completeRows; i++) {
        for(int j = 0; j < completeCols; j++) {
            b.pixelateBox(b, i * 16, j * 16, i * 16 + 16, j * 16 + 16);
        }
    }
}

/**
 * Use gaussian bluring to blur an image.
 */
void Bitmap::blur(Bitmap& b){
    if (&b == NULL){
        cout << "Please enter a valid bitmap" << endl;
        return;
    }

    // For every pixel that can be blurred (ignoring the edges), call gaussPoint on that pixel
    for(int i = 2; i < (int) b.imageHeight-2; i++) {
        for (int j = 2; j < (int) b.imageWidth-2; j++) {
            b.gaussPoint(b, i, j);
        }
    }
}

/**
 * rotates image 90 degrees, swapping the height and width.
 */
void Bitmap::rot90(Bitmap& b){

    if (&b == NULL){
        cout << "Please enter a valid bitmap" << endl;
        return;
    }

    // Make integer copies of the height and width for the image
    int intWidth = (int) b.imageWidth;
    int intHeight = (int) b.imageHeight;

    // Calculate total pixels
    int totalPixels = intWidth * intHeight;

    if(b.compression == 3) {

        // Allocate a new data array
        uint32_t * temp = new uint32_t[totalPixels];

        // For every pixel, assign the new pointer values the corresponding pixel in the original image
        for (int i = 0; i < intHeight; i++)
            for (int j = 0; j < intWidth; j++) {
                temp[(intWidth - j - 1) * intHeight + i ] = b.data[i * intWidth + j];
            }

        // Hold on to b.data's original values and free it later
        uint32_t * temp2 = b.data;

        // Assign data to the temp pointer
        b.data = temp;

        // Reverse the heights and widths of image
        b.imageHeight = (uint32_t) intWidth;
        b.imageWidth = (uint32_t) intHeight;

        // Free original b.data
        delete(temp2);

    } else {

        // Parallel except for 24 bit version
        uint24_t * temp = new uint24_t[totalPixels];

        for (int i = 0; i < intHeight; i++)
            for (int j = 0; j < intWidth; j++) {
                temp[(intWidth - j -1) * intHeight + i ] = b.data2[i * intWidth + j];
            }

        uint24_t * temp2 = b.data2;

        b.data2 = temp;

        b.imageHeight = (uint32_t) intWidth;
        b.imageWidth = (uint32_t) intHeight;

        // Reset padding
        uint32_t padCounter = 0;
        uint32_t totalWidth = b.imageWidth * 3;

        while(totalWidth % 4 != 0) {
            totalWidth++;
            padCounter++;
        }

        b.padding = padCounter;

        delete temp2;
    }


}

/**
 * rotates an image by 180 degrees.
 */
void Bitmap::rot180(Bitmap& b){
    if (&b == NULL){
        cout << "Please enter a valid bitmap" << endl;
        return;
    }

    // Rotate image by 90 degrees 2x
    b.rot90(b);
    b.rot90(b);
    return;
}

/**
 * rotates image 270 degrees, swapping the height and width.
 */
void Bitmap::rot270(Bitmap& b){
    if (&b == NULL){
        cout << "Please enter a valid bitmap" << endl;
        return;
    }

    // Rotate image by 90 degrees 3x
    b.rot90(b);
    b.rot90(b);
    b.rot90(b);
    return;
}

/**
 * flips and image over the vertical axis.
 */
void Bitmap::flipv(Bitmap& b){
    if (&b == NULL){
        cout << "Please enter a valid bitmap" << endl;
        return;
    }

    // Get integer values of image width and height
    int intWidth = (int) b.imageWidth;
    int intHeight = (int) b.imageHeight;

    // If 32 bits, for every height and width, switch the pixel with its vertical-mirror pixel on the same row
    if(b.compression == 3) {
        for (int i = 0; i < intHeight; i++)
            for (int j = 0; j < intWidth/2; j++) {
                uint32_t temp = b.data[i * intWidth + (intWidth-j)];
                b.data[i * intWidth + (intWidth-j)] = b.data[i * intWidth + j];
                b.data[i * intWidth + j] = temp;
            }
    } else {

    // Same for 24 bits
        for (int i = 0; i < intHeight; i++)
            for (int j = 0; j < intWidth/2; j++) {
                uint24_t temp = b.data2[i * intWidth + (intWidth-j)];
                b.data2[i * intWidth + (intWidth-j)] = b.data2[i * intWidth + j];
                b.data2[i * intWidth + j] = temp;
            }
    }
}

/**
 * flips and image over the horizontal axis.
 */
void Bitmap::fliph(Bitmap& b){
    if (&b == NULL){
        cout << "Please enter a valid bitmap" << endl;
        return;
    }

    // Rotate an image 180 degree then conduct a vertical flip
    b.rot180(b);
    b.flipv(b);
}

/**
 * flips and image over the line y = -x, swapping the height and width.
 */
void Bitmap::flipd1(Bitmap& b){
    if (&b == NULL){
        cout << "Please enter a valid bitmap" << endl;
        return;
    }

    // Rotate an image 90 degrees then flip it vertically
    b.rot90(b);
    b.flipv(b);
}

/**
 * flips and image over the line y = xr, swapping the height and width.
 */
void Bitmap::flipd2(Bitmap& b){
    if (&b == NULL){
        cout << "Please enter a valid bitmap" << endl;
        return;
    }

    // Rotate an image 270 degrees then flip it vertically
    b.rot270(b);
    b.flipv(b);
}

/**
 * scales the image by a factor of 2.
 */
void Bitmap::scaleUp(Bitmap& b){
    if (&b == NULL){
        cout << "Please enter a valid bitmap" << endl;
        return;
    }

    // Get the height and the width in integer forms
    int intWidth = (int) b.imageWidth;
    int intHeight = (int) b.imageHeight;

    // Scale the height and width by 2x
    int newIntWidth = intWidth * 2;
    int newIntHeight = intHeight * 2;

    // If 32 bits
    if(b.compression == 3) {

        // Create a new data array field
        uint32_t * temp = new uint32_t[newIntHeight * newIntWidth];

        // For every pixel in original data array, assign all pixels in new scaled up version that value
        for(int i = 0; i < intHeight; i++)
            for(int j = 0; j < intWidth; j++) {
                temp[(i*2) * (newIntWidth) + (j * 2)] = b.data[i * intWidth + j];
                temp[(i*2 + 1) * (newIntWidth) + (j * 2)] = b.data[i * intWidth + j];
                temp[(i*2) * (newIntWidth) + (j * 2 + 1)] = b.data[i * intWidth + j];
                temp[(i*2 + 1) * (newIntWidth) + (j * 2 + 1)] = b.data[i * intWidth + j];
            }

        uint32_t * temp2 = b.data;

        // Assign b.data to that value
        b.data = temp;

        // Reset image widths
        b.imageWidth = b.imageWidth * 2;
        b.imageHeight = b.imageHeight * 2;

        // Adjust header information
        b.fileSize = (b.pixelOffset)+ b.imageSize * 4;
        b.imageSize *= 4;
        b.pixelCount *= 4;

        delete temp2;
    } else {

        // Parallel except for uint24_t version
        uint24_t * temp = new uint24_t[newIntHeight * newIntWidth];

        for(int i = 0; i < intHeight; i++)
            for(int j = 0; j < intWidth; j++) {
                temp[(i*2) * (newIntWidth) + (j * 2)] = b.data2[i * intWidth + j];
                temp[(i*2 + 1) * (newIntWidth) + (j * 2)] = b.data2[i * intWidth + j];
                temp[(i*2) * (newIntWidth) + (j * 2 + 1)] = b.data2[i * intWidth + j];
                temp[(i*2 + 1) * (newIntWidth) + (j * 2 + 1)] = b.data2[i * intWidth + j];
            }

        uint24_t * temp2 = b.data2;

        b.data2 = temp;

        b.imageWidth = b.imageWidth * 2;
        b.imageHeight = b.imageHeight * 2;

        b.fileSize = (b.pixelOffset)+ b.imageSize * 4;
        b.imageSize *= 4;

        // Reset padding
        uint32_t padCounter = 0;
        uint32_t totalWidth = b.imageWidth * 3;

        while(totalWidth % 4 != 0) {
            totalWidth++;
            padCounter++;
        }

        b.padding = padCounter;

        delete temp2;
    }
}

/**
 * scales the image by a factor of 1/2.
 */
void Bitmap::scaleDown(Bitmap& b){
    if (&b == NULL){
        cout << "Please enter a valid bitmap" << endl;
        return;
    }

    // Get integer versions of heights and widths
    int intWidth = (int) b.imageWidth;
    int intHeight = (int) b.imageHeight;

    // Set new heights and widths to half of original values
    int newIntWidth = intWidth / 2;
    int newIntHeight = intHeight / 2;

    if(b.compression == 3) {

        // Set new pointer to new height and width
        uint32_t * temp = new uint32_t[newIntHeight * newIntWidth];

        // Set for every pixel of new pointer, it's equal to a 1/4 sampling of the old pixels
        for(int i = 0; i < newIntHeight; i++)
            for(int j = 0; j < newIntWidth; j++) {
                temp[(i) * (newIntWidth) + (j)] = b.data[(i*2) * intWidth + (j*2)];
            }

        uint32_t * temp2 = b.data;

        // Reset header information
        b.data = temp;

        b.imageWidth = (uint32_t) newIntWidth;
        b.imageHeight = (uint32_t) newIntHeight;

        b.fileSize = (b.pixelOffset)+ (b.imageWidth * b.imageHeight);
        b.imageSize = (b.imageWidth*b.imageHeight);
        b.pixelCount = (b.imageWidth*b.imageHeight);

        delete temp2;

    } else {

        // Parallel except for 24 bit version
        uint24_t * temp = new uint24_t[newIntHeight * newIntWidth];

        for(int i = 0; i < newIntHeight; i++)
            for(int j = 0; j < newIntWidth; j++) {
                temp[(i) * (newIntWidth) + (j)] = b.data2[(i*2) * intWidth + (j*2)];
            }

        uint24_t * temp2 = b.data2;

        b.data2 = temp;

        b.imageWidth = (uint32_t) newIntWidth;
        b.imageHeight = (uint32_t) newIntHeight;

        b.fileSize = (b.pixelOffset)+ (b.imageWidth*b.imageHeight);
        b.imageSize = (b.imageWidth*b.imageHeight);

        // Reset padding
        uint32_t padCounter = 0;
        uint32_t totalWidth = b.imageWidth * 3;
        while(totalWidth % 4 != 0) {
            totalWidth++;
            padCounter++;
        }
        b.padding = padCounter;

        delete temp2;
    }
}

uint32_t Bitmap::modifyPixel  ( uint32_t orig, uint32_t mask, uint32_t newVal) {

    // Shift Mask: Initialize a counter to count the number of zeroes to shift the mask by
    int numZeros = 0;

    // Shift Mask: Keep shifting mask until 1 reaches very final index, and count the number of zeroes
    while(mask % 2 == 0) {
        numZeros++;
        mask = mask>>1;
    }

    // Shift newval by that many bits
    newVal = newVal<<numZeros;
    mask = mask<<numZeros;

    // Add the compliment of the mask to the newval
    uint32_t returnVal = (~mask & orig) | (newVal);

    return (uint32_t ) returnVal;

}

uint24_t Bitmap::modifyPixel (uint24_t orig, char color, uint8_t newVal) {

    // Parallel version of 32 bit modify pixel (see above), except for 24 bit version
    uint24_t returnInt = orig;

    if (color == 'r' || color == 'R') {
        returnInt.r = newVal;
    } else if (color == 'g' || color == 'G') {
        returnInt.g = newVal;
    } else if (color == 'b' || color == 'B') {
        returnInt.b = newVal;
    } else {
        cout << "Invalid Color Choice, no changes made" << endl;
    }
    return returnInt;
}

uint32_t Bitmap::getColorVal  ( uint32_t value, uint32_t mask) {

    // Shift Mask: Initialize a counter to count the number of zeroes to shift the mask by
    int numZeros = 0;
    uint32_t tempMask = mask;

    // Shift Mask: Keep shifting mask until 1 reaches very final index, and count the number of zeroes
    while(mask % 2 == 0) {
        numZeros++;
        mask = mask>>1;
    }

    // Return values
    uint32_t returnVal = (value & tempMask);
    returnVal = returnVal >> numZeros;
    return returnVal;
}


// 24 bit version of the uint32_t version. See above.
uint8_t Bitmap::getColorVal (uint24_t value, char color) {
    if (color == 'r' || color == 'R') {
        return value.r;
    } else if (color == 'g' || color == 'G') {
        return value.g;
    } else if (color == 'b' || color == 'B') {
        return value.b;
    } else {
        cout << "Invalid Color Choice, no changes made" << endl;
        return 0;
    }
}

// Pixelates a box given a range of coordinates and a bitmap image
void Bitmap::pixelateBox(Bitmap & b, uint32_t startingR, uint32_t startingC, uint32_t endingR, uint32_t endingC){
    if (&b == NULL){
        cout << "Please enter a valid bitmap" << endl;
        return;
    }

    // Create rgb masks
    uint32_t dataMask[3] = {b.redMask,b.greenMask,b.blueMask};
    char data2Mask[3] = {'r','g','b'};

    // Calculate total number of pixels to average
    uint32_t totalPixels = (endingR-startingR) * (endingC-startingC);

    // If 32bit colors
    if (b.compression == 3) {

        // For each color
        for(int k = 0; k < 3; k++) {
            // Set a uint_32 to 0
            uint32_t sum = 0;

            // For every pixel of that color add that to the value
            for(int i = startingR; i < endingR; i++) {
                for (int j = startingC; j < endingC; j++) {
                    sum += getColorVal(b.data[i * b.imageWidth + j],dataMask[k]);
                }
            }

            // Calculate the average
            sum = sum / totalPixels;

            // Then set the value constant for every pixel
            for(int i = startingR; i < endingR; i++) {
                for (int j = startingC; j < endingC; j++) {
                    b.data[i * b.imageWidth + j] = modifyPixel(b.data[i * b.imageWidth + j],dataMask[k],sum);
                }
            }
        }
    } else {
        // We have 24 bit colors

        // For each color
        for(int k = 0; k < 3; k++) {
            // Set a uint_32 to 0
            uint32_t sum = 0;

            // For every pixel of that color add that to the value
            for(int i = startingR; i < endingR; i++) {
                for (int j = startingC; j < endingC; j++) {
                    sum += getColorVal(b.data2[i * b.imageWidth + j],data2Mask[k]);
                }
            }

            // Calculate the average
            sum = sum / totalPixels;
            sum = (uint8_t) sum;
            // Then set the value constant for every pixel
            for(int i = startingR; i < endingR; i++) {
                for (int j = startingC; j < endingC; j++) {
                    b.data2 [i * b.imageWidth + j] = modifyPixel(b.data2[i * b.imageWidth + j],data2Mask[k],sum);
                }
            }
        }
    }
    return;
}


void Bitmap::gaussPoint (Bitmap & b, int height, int width) {
    if (&b == NULL){
        cout << "Please enter a valid bitmap" << endl;
        return;
    }

    uint32_t dataMask[3] = {b.redMask,b.greenMask,b.blueMask};
    char data2Mask[3] = {'r','g','b'};

    uint32_t gaussArray[5][5] = {{1,4,6,4,1},{4,16,24,16,4},{6,24,36,24,6},{4,16,24,16,4},{1,4,6,4,1}};

    int intHeight = height;
    int intWidth = width;
    int intMaxHeight = (int) b.imageHeight;
    int intMaxWidth = (int) b.imageWidth;

    if (b.compression == 3) {
        // Then we have 32 bit colors

        // For each color
        for(int k = 0; k < 3; k++) {
            // Set a uint_32 to 0
            uint32_t sum = 0;

            // For every pixel of that color add that to the value
            for(int i = 0; i <= 4; i++) {
                for (int j = 0; j <= 4; j++) {
                        uint32_t temp = getColorVal(b.data[ (i-2 + intHeight) * intMaxWidth + (j-2 + intWidth)], dataMask[k]);
                        temp = temp * gaussArray[i][j];
                        temp /= 256;
                        sum += temp;
                }
            }

            b.data[intHeight * intMaxWidth + intWidth] = modifyPixel(b.data[intHeight * intMaxWidth + intWidth],dataMask[k],sum);
        }
    } else {
        // We have 24 bit colors
        // For each color
            for(int k = 0; k < 3; k++) {
                // Set a uint_32 to 0
                uint32_t sum = 0;

                // For every pixel of that color add that to the value
                for(int i = 0; i <= 4; i++) {
                    for (int j = 0; j <= 4; j++) {
                        uint32_t temp = getColorVal(b.data2[ (i-2 + intHeight) * intMaxWidth + (j-2 + intWidth)], data2Mask[k]);
                        temp = temp * gaussArray[i][j];
                        temp /= 256;
                        sum += temp;
                    }
                }

                sum = (uint8_t) sum;

                b.data2[intHeight * intMaxWidth + intWidth] = modifyPixel(b.data2[intHeight * intMaxWidth + intWidth],data2Mask[k],sum);
            }

    }
    return;
}

void Bitmap::addNoise (Bitmap & b, int pixelChangePer, uint8_t pixelChangeAmt) {

    srand((unsigned) time(0));

    char data2Mask[3] = {'r', 'g', 'b'};

    for (int i = 0; i < b.pixelCount; i++) {
        int randomVal = (rand() % 100);

        if(pixelChangePer >= randomVal) {
            if(randomVal % 2 == 0) {
                for (int j = 0; j < 3; j++) {
                    uint8_t currentVal = getColorVal(b.data2[i],data2Mask[j]);
                    uint8_t potentialVal = currentVal + pixelChangeAmt;
                    if(potentialVal < 255 && potentialVal < currentVal) {
                        // Buffer overflow happened
                        potentialVal = 255;
                    }
                    b.data2[i] = modifyPixel(b.data2[i], data2Mask[j], potentialVal);
                }
            } else {
                for (int j = 0; j < 3; j++) {
                    uint8_t currentVal = getColorVal(b.data2[i],data2Mask[j]);
                    uint8_t potentialVal = currentVal - pixelChangeAmt;
                    if(potentialVal > 0 && potentialVal > currentVal) {
                        // Buffer overflow happened
                        potentialVal = 0;
                    }
                    b.data2[i] = modifyPixel(b.data2[i], data2Mask[j], potentialVal);

//                    b.data2[i] = modifyPixel(b.data2[i], data2Mask[j], getColorVal(b.data2[i],data2Mask[j])+pixelChangeAmt);
                }
            }
        }
    }

    return;
}
#ifndef TGA_IMAGE_H
#define TGA_IMAGE_H

#include <string>
#include <vector>
using namespace std;


// Defining a structure to hold the headers of the tga files.
struct TGAHeader {
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
};

// Defining a class to hold the image data.
class TGAImage {
    // The TGAImage is made up of a header and image data.
    TGAHeader header;
    vector<unsigned char> imageData;

public:
    // Default constructor.
    TGAImage();

    // Function to get the width of the image.
    int getWidth() const;

    // Function to get the height of the image.
    int getHeight() const;

    // Function to set the width of the image.
    void setWidth(int width);

    // Function to set the height of the image.
    void setHeight(int height);

    // Gets the color data of a pixel at (x,y) coordinate.
    bool getPixelColor(int x, int y, unsigned char& red, unsigned char& green, unsigned char& blue) const;

    // Gets the color data of all pixels in the TGA image.
    void getPixelColor(vector<unsigned char>& reds, vector<unsigned char>& greens, vector<unsigned char>& blues) const;

    // Function to set the bits per pixel of the image.
    void setBitsPerPixel(unsigned char bitsPerPixel);

    // Function to set the color data of a pixel at (x, y) coordinate.
    bool setPixelColor(int x, int y, unsigned char red, unsigned char green, unsigned char blue);

    // Loads in a TGA file.
    bool loadTGA(const string& filename);

    // Saves data to a new TGA file.
    bool saveTGA(const string& filename) const;

    // Prints pixel data.
    void printPixelData() const;

    // Multiplies two TGAImage objects together.
    static TGAImage multiplyImages(const TGAImage& topLayer, const TGAImage& bottomLayer);

    // Substracts one TGAImage object from another.
    static TGAImage subtractImages(const TGAImage& topLayer, const TGAImage& bottomLayer);

    // Screen blends two TGAImage objects together.
    static TGAImage screenImages(const TGAImage& topLayer, const TGAImage& bottomLayer);

    // Overlays two TGAImage objects together.
    static TGAImage overlayImages(const TGAImage& background, const TGAImage& foreground);

    // Adds 200 to the green channel.
    static TGAImage add200Green(const TGAImage& image);

    // Scales the red and blue channels.
    static TGAImage scaleChannels(const TGAImage& image, float redScale, float blueScale);

    // Separates rgb channels and outputs them as separate files.
    static bool separateChannels(const TGAImage& image, const string& redFilename, 
                                 const string& greenFilename, const string& blueFilename);

    // Combines separate images into different color channels of one image.
    static TGAImage combineChannels(const TGAImage& layerRed, const TGAImage& layerGreen,
                                    const TGAImage& layerBlue);

    // Flips an image 180 degrees.
    static TGAImage flipImage180(const TGAImage& image);

    /*
    // Makes a 2x2 grid image out of 4 images.
    static TGAImage gridImage(const TGAImage& bottomLeftImage, const TGAImage& bottomRightImage,
                              const TGAImage& topLeftImage, const TGAImage& topRightImage);
    */
};

#endif // TGA_Image_H

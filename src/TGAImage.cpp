#include "TGAImage.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <cmath>
using namespace std;

TGAImage::TGAImage() : header{}, imageData{} {
    // Set the header properties for the default image.
    header.idLength = 0;
    header.colorMapType = 0;
    header.dataTypeCode = 2; // Uncompressed RGB image.
    header.colorMapOrigin = 0;
    header.colorMapLength = 0;
    header.colorMapDepth = 0;
    header.xOrigin = 0;
    header.yOrigin = 0;
    header.bitsPerPixel = 24;
    header.imageDescriptor = 0;
};

// Function to get the width of the image.
int TGAImage::getWidth() const {
    return header.width;
};

// Function to get the height of the image.
int TGAImage::getHeight() const {
    return header.height;
};

// Function to set the width of the image.
void TGAImage::setWidth(int width) {
    header.width = width;
};

// Function to set the height of the image.
void TGAImage::setHeight(int height) {
    header.height = height;
};

// Function to get the color data of a pixel at (x,y) coordinate. 
bool TGAImage::getPixelColor(int x, int y, unsigned char& red, unsigned char& green, 
    unsigned char& blue) const {

    // Checks if the coordinates are out of bounds.
    if (x < 0 || x >= header.width || y < 0 || y >= header.height) {
        return false;
    }

    // Calculates the index of the pixel in the imageData vector.
    int pixelIndex = (y * header.width + x) * 3;

    // Reads in the color data from the imageData vector.
    blue = imageData[pixelIndex];
    green = imageData[pixelIndex + 1];
    red = imageData[pixelIndex + 2];

    // Returns true when the color data is retrieved.
    return true;
};

// Function to the get the color data of all pixels in a TGA image.
void TGAImage::getPixelColor(vector<unsigned char>& reds, vector<unsigned char>& greens, 
    vector<unsigned char>& blues) const {
    
    // Calculates the size of the image.
    int imageSize = header.width * header.height;

    // Resizes the color vectors to store the data for all pixels.
    reds.resize(imageSize);
    greens.resize(imageSize);
    blues.resize(imageSize);

    // Iterates through all the pixels and stores their color data.
    for (int y = 0; y < header.height; ++y) {
        for (int x = 0; x < header.width; ++x) {
            int pixelIndex = (y * header.width + x) * 3;
            blues[y * header.width + x] = imageData[pixelIndex];
            greens[y * header.width + x] = imageData[pixelIndex + 1];
            reds[y * header.width + x] = imageData[pixelIndex + 2];

        }
    }
};

// Function to set the bits per pixel of the image.
void TGAImage::setBitsPerPixel(unsigned char bitsPerPixel) {
    header.bitsPerPixel = bitsPerPixel;
};

// Function to set the color data of a pixel at (x, y) coordinate.
bool TGAImage::setPixelColor(int x, int y, unsigned char red, unsigned char green, unsigned char blue) {
    // Check if the coordinates are out of bounds.
    if (x < 0 || x >= header.width || y < 0 || y >= header.height) {
        return false;
    }

    // Calculates the index of the pixel in the imageData vector.
    int pixelIndex = (y * header.width + x) * 3;

    // Sets the color data in the imageData vector.
    imageData[pixelIndex] = blue;   // Blue channel
    imageData[pixelIndex + 1] = green; // Green channel
    imageData[pixelIndex + 2] = red;    // Red channel

    return true;
};

// Function to load in the data of a TGA file.
bool TGAImage::loadTGA(const string& filename) {

    // Open the file in binary.
    fstream file(filename, ios_base::in | ios_base::binary);

    // If the file can't be opened, return false.
    if (!file) {
        return false;
    }

    // Debug prints to check if the function is called and the filename.
    cout << "Loading TGA image from file: " << filename << endl;

    // Reads in the header of the tga file.
    file.read(&header.idLength, sizeof(header.idLength));
    file.read(&header.colorMapType, sizeof(header.colorMapType));
    file.read(&header.dataTypeCode, sizeof(header.dataTypeCode));
    file.read(reinterpret_cast<char*>(&header.colorMapOrigin), sizeof(header.colorMapOrigin));
    file.read(reinterpret_cast<char*>(&header.colorMapLength), sizeof(header.colorMapLength));
    file.read(&header.colorMapDepth, sizeof(header.colorMapDepth));
    file.read(reinterpret_cast<char*>(&header.xOrigin), sizeof(header.xOrigin));
    file.read(reinterpret_cast<char*>(&header.yOrigin), sizeof(header.yOrigin));
    file.read(reinterpret_cast<char*>(&header.width), sizeof(header.width));
    file.read(reinterpret_cast<char*>(&header.height), sizeof(header.height));
    file.read(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
    file.read(&header.imageDescriptor, sizeof(header.imageDescriptor));

    // If the data type of the image is unsupported, return false.
    if (header.dataTypeCode != 2 && header.dataTypeCode != 10) {
        return false;
    }

    // Calculates the size of the image data based on the header information.
    int imageSize = header.width * header.height * (static_cast<int>(header.bitsPerPixel) / 8);

    // Resizes imageData to store the image data.
    imageData.resize(imageSize);

    // Reads the image data.
    file.read(reinterpret_cast<char*>(imageData.data()), imageSize);

    // Debug print to check the size of the imageData after loading.
    cout << "Image data size after loading: " << imageData.size() << " bytes." << endl;

    // Closes the file after reading the data.
    file.close();
    return true;
};

// Function to save a TGAImage object to a tga file.
bool TGAImage::saveTGA(const string& filename) const {
    // Opens the file in binary mode.
    fstream file(filename, ios_base::out | ios_base::binary);

    // Returns false if the file doesn't open.
    if (!file) {
        cout << "Error: Failed to open the file for writing." << endl;
        return false;
    }

    // Writes the header data to the file.
    file.write(&header.idLength, sizeof(header.idLength));
    file.write(&header.colorMapType, sizeof(header.colorMapType));
    file.write(&header.dataTypeCode, sizeof(header.dataTypeCode));
    file.write(reinterpret_cast<const char*>(&header.colorMapOrigin), sizeof(header.colorMapOrigin));
    file.write(reinterpret_cast<const char*>(&header.colorMapLength), sizeof(header.colorMapLength));
    file.write(&header.colorMapDepth, sizeof(header.colorMapDepth));
    file.write(reinterpret_cast<const char*>(&header.xOrigin), sizeof(header.xOrigin));
    file.write(reinterpret_cast<const char*>(&header.yOrigin), sizeof(header.yOrigin));
    file.write(reinterpret_cast<const char*>(&header.width), sizeof(header.width));
    file.write(reinterpret_cast<const char*>(&header.height), sizeof(header.height));
    file.write(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
    file.write(&header.imageDescriptor, sizeof(header.imageDescriptor));

    // Checks if the header data was written successfully.
    if (!file) {
        cout << "Error: Failed to write header data." << endl;
        file.close();
        return false;
    }

    // Writes the image data to the file.
    file.write(reinterpret_cast<const char*>(imageData.data()), imageData.size());

    // Checks if the image data was written successfully.
    if (!file) {
        cout << "Error: Failed to write image data." << endl;
        file.close();
        return false;
    }

    // Closes the file after a successful write and returns true.
    file.close();

    // Debug print to confirm that the image was saved successfully.
    cout << "TGA image saved successfully to file: " << filename << endl;

    return true;
};

// Prints pixel data.
void TGAImage::printPixelData() const {
    int maxPixelsToPrint = min(static_cast<int>(imageData.size() / 3), 10); // Print at most 10 pixels.
    for (int i = 0; i < maxPixelsToPrint * 3; i += 3) {
        unsigned char blue = imageData[i];
        unsigned char green = imageData[i + 1];
        unsigned char red = imageData[i + 2];

        int x = i / 3 % header.width;
        int y = i / 3 / header.width;
        cout << "Pixel[" << x << ", " << y << "]"
             << " - R: " << static_cast<int>(red) << ", G: " << static_cast<int>(green)
             << ", B: " << static_cast<int>(blue) << endl;
    }

    if (maxPixelsToPrint < imageData.size() / 3) {
        cout << "..." << endl;
    }
};

// Multiplies two TGAImage objects together.
TGAImage TGAImage::multiplyImages(const TGAImage& topLayer, const TGAImage& bottomLayer) {
    // Check if the dimensions of the two images are compatible for multiplication.
    if (topLayer.getWidth() != bottomLayer.getWidth() || topLayer.getHeight() != bottomLayer.getHeight()) {
        cout << "Error: Dimension mismatch. Images must have the same dimensions for multiplication." << endl;
        return TGAImage(); // Return an empty image on error.
    }

    // Create a new TGAImage to store the result of the blending operation.
    TGAImage resultImage;
    resultImage.setWidth(topLayer.getWidth());
    resultImage.setHeight(topLayer.getHeight());
    resultImage.setBitsPerPixel(24); // Assuming RGB image with 8 bits per channel.

    // Resize the imageData vector to store the calculated pixel values.
    resultImage.imageData.resize(topLayer.getWidth() * topLayer.getHeight() * 3);

    // Perform the Multiply blending operation for each pixel.
    for (int y = 0; y < topLayer.getHeight(); ++y) {
        for (int x = 0; x < topLayer.getWidth(); ++x) {
            unsigned char topR, topG, topB;
            unsigned char bottomR, bottomG, bottomB;

            // Get the color values of the top layer at (x, y).
            topLayer.getPixelColor(x, y, topR, topG, topB);

            // Get the color values of the bottom layer at (x, y).
            bottomLayer.getPixelColor(x, y, bottomR, bottomG, bottomB);

            // Calculate the blended RGB values using the Multiply blending mode.
            // Normalize the values between 0 and 1 before the calculation.
            float newR = (topR / 255.0f) * (bottomR / 255.0f);
            float newG = (topG / 255.0f) * (bottomG / 255.0f);
            float newB = (topB / 255.0f) * (bottomB / 255.0f);

            // Convert the normalized values back to the original range (0-255).
            unsigned char clampedR = static_cast<unsigned char>(newR * 255.0f + 0.5f);
            unsigned char clampedG = static_cast<unsigned char>(newG * 255.0f + 0.5f);
            unsigned char clampedB = static_cast<unsigned char>(newB * 255.0f + 0.5f);

            // Set the RGB values in the result image's imageData vector (in BGR order).
            int pixelIndex = (y * topLayer.getWidth() + x) * 3;
            resultImage.imageData[pixelIndex] = clampedB;   // Blue channel
            resultImage.imageData[pixelIndex + 1] = clampedG; // Green channel
            resultImage.imageData[pixelIndex + 2] = clampedR; // Red channel
        }
    }

    return resultImage;
};

// Subtracts one TGAImage object from another.
TGAImage TGAImage::subtractImages(const TGAImage& topLayer, const TGAImage& bottomLayer) {
    // Check if the dimensions of both images match.
    if (bottomLayer.getWidth() != topLayer.getWidth() || bottomLayer.getHeight() != topLayer.getHeight()) {
        cout << "Error: Dimension mismatch between the two images." << endl;
        return TGAImage(); // Return an empty image in case of dimension mismatch.
    }

    // Create a new TGAImage to store the result of the subtraction.
    TGAImage resultImage;
    resultImage.setWidth(bottomLayer.getWidth());
    resultImage.setHeight(bottomLayer.getHeight());
    resultImage.setBitsPerPixel(24); // Assuming RGB image with 8 bits per channel.

    // Resize the imageData vector to store the calculated pixel values.
    resultImage.imageData.resize(bottomLayer.getWidth() * bottomLayer.getHeight() * 3);

    // Perform the Subtract blending operation for each pixel.
    for (int y = 0; y < bottomLayer.getHeight(); ++y) {
        for (int x = 0; x < bottomLayer.getWidth(); ++x) {
            unsigned char bottomR, bottomG, bottomB;
            unsigned char topR, topG, topB;

            // Get the color data of the bottom layer pixel.
            bottomLayer.getPixelColor(x, y, bottomR, bottomG, bottomB);

            // Get the color data of the top layer pixel.
            topLayer.getPixelColor(x, y, topR, topG, topB);

            // Calculate the subtracted RGB values.
            unsigned char newR, newG, newB;
            newR = bottomR >= topR ? bottomR - topR : 0;
            newG = bottomG >= topG ? bottomG - topG : 0;
            newB = bottomB >= topB ? bottomB - topB : 0;

            // Set the RGB values in the result image's imageData vector (in BGR order).
            int pixelIndex = (y * bottomLayer.getWidth() + x) * 3;
            resultImage.imageData[pixelIndex] = newB; // Blue channel
            resultImage.imageData[pixelIndex + 1] = newG; // Green channel
            resultImage.imageData[pixelIndex + 2] = newR; // Red channel
        }
    }

    return resultImage;
};

TGAImage TGAImage::screenImages(const TGAImage& topLayer, const TGAImage& bottomLayer) {
    // Check if the dimensions of both images match.
    if (bottomLayer.getWidth() != topLayer.getWidth() || bottomLayer.getHeight() != topLayer.getHeight()) {
        cout << "Error: Dimension mismatch between the two images." << endl;
        return TGAImage(); // Return an empty image in case of dimension mismatch.
    }

    // Create a new TGAImage to store the result of the blending.
    TGAImage resultImage;
    resultImage.setWidth(bottomLayer.getWidth());
    resultImage.setHeight(bottomLayer.getHeight());
    resultImage.setBitsPerPixel(24); // Assuming RGB image with 8 bits per channel.

    // Resize the imageData vector to store the calculated pixel values.
    resultImage.imageData.resize(bottomLayer.getWidth() * bottomLayer.getHeight() * 3);

    // Perform the Screen blending operation for each pixel.
    for (int y = 0; y < bottomLayer.getHeight(); ++y) {
        for (int x = 0; x < bottomLayer.getWidth(); ++x) {
            unsigned char bottomR, bottomG, bottomB;
            unsigned char topR, topG, topB;

            // Get the color data of the bottom layer pixel.
            bottomLayer.getPixelColor(x, y, bottomR, bottomG, bottomB);

            // Get the color data of the top layer pixel.
            topLayer.getPixelColor(x, y, topR, topG, topB);

            // Convert the color values to normalized floats (0.0 to 1.0).
            float normBottomR = bottomR / 255.0f;
            float normBottomG = bottomG / 255.0f;
            float normBottomB = bottomB / 255.0f;

            float normTopR = topR / 255.0f;
            float normTopG = topG / 255.0f;
            float normTopB = topB / 255.0f;

            // Calculate the Screen blending mode values.
            float newR = 1.0f - (1.0f - normTopR) * (1.0f - normBottomR);
            float newG = 1.0f - (1.0f - normTopG) * (1.0f - normBottomG);
            float newB = 1.0f - (1.0f - normTopB) * (1.0f - normBottomB);

            // Convert the normalized floats back to unsigned char (0 to 255).
            newR = round(newR * 255.0f);
            newG = round(newG * 255.0f);
            newB = round(newB * 255.0f);

            // Clamp the values to ensure they stay within the valid range (0 to 255).
            newR = std::max(0.0f, std::min(255.0f, newR));
            newG = std::max(0.0f, std::min(255.0f, newG));
            newB = std::max(0.0f, std::min(255.0f, newB));

            // Set the RGB values in the result image's imageData vector (in BGR order).
            int pixelIndex = (y * bottomLayer.getWidth() + x) * 3;
            resultImage.imageData[pixelIndex] = static_cast<unsigned char>(newB); // Blue channel
            resultImage.imageData[pixelIndex + 1] = static_cast<unsigned char>(newG); // Green channel
            resultImage.imageData[pixelIndex + 2] = static_cast<unsigned char>(newR); // Red channel
        }
    }

    return resultImage;
};

// Function to perform Overlay blending between two TGAImage objects.
TGAImage TGAImage::overlayImages(const TGAImage& background, const TGAImage& foreground) {
    // Check if the dimensions of both images match.
    if (background.getWidth() != foreground.getWidth() || background.getHeight() != foreground.getHeight()) {
        cout << "Error: Dimension mismatch between the two images." << endl;
        return TGAImage(); // Return an empty image in case of dimension mismatch.
    }

    // Create a new TGAImage to store the result of the blending.
    TGAImage resultImage;
    resultImage.setWidth(background.getWidth());
    resultImage.setHeight(background.getHeight());
    resultImage.setBitsPerPixel(24); // Assuming RGB image with 8 bits per channel.

    // Resize the imageData vector to store the calculated pixel values.
    resultImage.imageData.resize(background.getWidth() * background.getHeight() * 3);

    // Perform the Overlay blending operation for each pixel.
    for (int y = 0; y < background.getHeight(); ++y) {
        for (int x = 0; x < background.getWidth(); ++x) {
            unsigned char backgroundR, backgroundG, backgroundB;
            unsigned char foregroundR, foregroundG, foregroundB;

            // Get the color data of the background pixel.
            background.getPixelColor(x, y, backgroundR, backgroundG, backgroundB);

            // Get the color data of the foreground pixel.
            foreground.getPixelColor(x, y, foregroundR, foregroundG, foregroundB);

            // Calculate the Overlay blending mode values.
            unsigned char newR, newG, newB;
            if (backgroundR < 128) {
                newR = static_cast<unsigned char>(2.0f * backgroundR * foregroundR / 255.0f + 0.5f); // C = 2 * A * B / 255
            } else {
                newR = static_cast<unsigned char>(255.0f - 2.0f * (255.0f - backgroundR) * (255.0f - foregroundR) / 255.0f + 0.5f); // C = 255 - 2 * (255 - A) * (255 - B) / 255
            }

            if (backgroundG < 128) {
                newG = static_cast<unsigned char>(2.0f * backgroundG * foregroundG / 255.0f + 0.5f); // C = 2 * A * B / 255
            } else {
                newG = static_cast<unsigned char>(255.0f - 2.0f * (255.0f - backgroundG) * (255.0f - foregroundG) / 255.0f + 0.5f); // C = 255 - 2 * (255 - A) * (255 - B) / 255
            }

            if (backgroundB < 128) {
                newB = static_cast<unsigned char>(2.0f * backgroundB * foregroundB / 255.0f + 0.5f); // C = 2 * A * B / 255
            } else {
                newB = static_cast<unsigned char>(255.0f - 2.0f * (255.0f - backgroundB) * (255.0f - foregroundB) / 255.0f + 0.5f); // C = 255 - 2 * (255 - A) * (255 - B) / 255
            }

            // Set the RGB values in the result image's imageData vector (in BGR order).
            int pixelIndex = (y * background.getWidth() + x) * 3;
            resultImage.imageData[pixelIndex] = newB; // Blue channel
            resultImage.imageData[pixelIndex + 1] = newG; // Green channel
            resultImage.imageData[pixelIndex + 2] = newR; // Red channel
        }
    }

    return resultImage;
};

// Function that adds 200 to the green channel.
TGAImage TGAImage::add200Green(const TGAImage& image) {
    // Create a copy of the input image
    TGAImage resultImage = image; 

    // Get image dimensions
    int width = resultImage.getWidth();
    int height = resultImage.getHeight();

    // Modify the green channel of each pixel
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned char red, green, blue;
            // Get the color data of the current pixel
            resultImage.getPixelColor(x, y, red, green, blue);

            // Add 200 to the green channel
            int newGreen = green + 200;

            // Clamp the value to the range [0, 255]
            newGreen = std::min(255, std::max(0, newGreen));

            // Update the pixel with the modified color values
            resultImage.setPixelColor(x, y, red, static_cast<unsigned char>(newGreen), blue);
        }
    }

    return resultImage;
};

// Scales the red and blue channels.
TGAImage TGAImage::scaleChannels(const TGAImage& image, float redScale, float blueScale) {
    TGAImage resultImage = image; // Create a copy of the input image

    // Get image dimensions
    int width = resultImage.getWidth();
    int height = resultImage.getHeight();

    // Scale the red and blue channels of each pixel
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned char red, green, blue;
            // Get the color data of the current pixel
            resultImage.getPixelColor(x, y, red, green, blue);

            // Scale the red and blue channels
            int newRed = red * redScale;
            int newBlue = blue * blueScale;

            // Clamp the values to the range [0, 255]
            newRed = std::min(255, std::max(0, newRed));
            newBlue = std::min(255, std::max(0, newBlue));

            // Update the pixel with the modified color values
            resultImage.setPixelColor(x, y, static_cast<unsigned char>(newRed), green, static_cast<unsigned char>(newBlue));
        }
    }

    return resultImage;
};

bool TGAImage::separateChannels(const TGAImage& image, const std::string& redFilename,
                                       const std::string& greenFilename, const std::string& blueFilename) {
    
    int width = image.getWidth();
    int height = image.getHeight();

    TGAImage redChannelImage = image;
    TGAImage greenChannelImage = image;
    TGAImage blueChannelImage = image;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned char red, green, blue;
            image.getPixelColor(x, y, red, green, blue);

            // Create separate images for each channel
            redChannelImage.setPixelColor(x, y, red, red, red);
            greenChannelImage.setPixelColor(x, y, green, green, green);
            blueChannelImage.setPixelColor(x, y, blue, blue, blue);
        }
    }

    // Save each channel as a separate file
    if (!redChannelImage.saveTGA(redFilename)) {
        std::cout << "Error saving red channel image." << std::endl;
        return false;
    }

    if (!greenChannelImage.saveTGA(greenFilename)) {
        std::cout << "Error saving green channel image." << std::endl;
        return false;
    }

    if (!blueChannelImage.saveTGA(blueFilename)) {
        std::cout << "Error saving blue channel image." << std::endl;
        return false;
    }

    std::cout << "Separate channel images saved successfully!" << std::endl;

    return true;
};

// Combines the red of one image, green of another, and blue of a third into a single image.
TGAImage TGAImage::combineChannels(const TGAImage& layerRed, const TGAImage& layerGreen, const TGAImage& layerBlue) {
    // Check if the dimensions of all images match.
    if (layerRed.getWidth() != layerGreen.getWidth() || layerRed.getHeight() != layerGreen.getHeight() ||
        layerRed.getWidth() != layerBlue.getWidth() || layerRed.getHeight() != layerBlue.getHeight()) {
        cout << "Error: Dimension mismatch between the input images." << endl;
        return TGAImage(); // Return an empty image in case of dimension mismatch.
    }

    // Create a new TGAImage to store the combined image.
    TGAImage resultImage;
    resultImage.setWidth(layerRed.getWidth());
    resultImage.setHeight(layerRed.getHeight());

    // Resize the imageData vector to store the combined pixel values.
    resultImage.imageData.resize(layerRed.getWidth() * layerRed.getHeight() * 3);

    // Combine the RGB channels of each pixel from the three input images.
    for (int y = 0; y < layerRed.getHeight(); ++y) {
        for (int x = 0; x < layerRed.getWidth(); ++x) {
            unsigned char red, green, blue;

            // Get the color data of the current pixel from each layer.
            layerRed.getPixelColor(x, y, red, green, blue);
            resultImage.imageData[(y * layerRed.getWidth() + x) * 3 + 2] = red; // Red channel

            layerGreen.getPixelColor(x, y, red, green, blue);
            resultImage.imageData[(y * layerRed.getWidth() + x) * 3 + 1] = green; // Green channel

            layerBlue.getPixelColor(x, y, red, green, blue);
            resultImage.imageData[(y * layerRed.getWidth() + x) * 3] = blue; // Blue channel
        }
    }

    return resultImage;
};

// Flips an image 180 degrees
TGAImage TGAImage::flipImage180(const TGAImage& image) {
    // TGAImage object to store the flipped image.
    TGAImage flippedImage;

    // Copy the header information from the original image to the flipped image.
    flippedImage.setWidth(image.getWidth());
    flippedImage.setHeight(image.getHeight());
    flippedImage.imageData = image.imageData;

    // Calculate the number of bytes per scanline in the image.
    int bytesPerScanline = image.getWidth() * 3; // Assuming 24 bits per pixel (RGB).

    // Loop through each row in the image and swap the data to flip it over the vertical axis.
    for (int y = 0; y < image.getHeight(); y++) {
        int rowOffset = y * bytesPerScanline;

        // Reverse the order of the pixels in the row.
        for (int x = 0; x < image.getWidth() / 2; x++) {
            int leftPixelOffset = rowOffset + x * 3;
            int rightPixelOffset = rowOffset + (image.getWidth() - x - 1) * 3;

            // Swap the pixels (R, G, B components) between left and right sides of the row.
            for (int channel = 0; channel < 3; channel++) {
                std::swap(flippedImage.imageData[leftPixelOffset + channel], flippedImage.imageData[rightPixelOffset + channel]);
            }
        }
    }

    // Loop through each column and swap the data to flip it over the horizontal axis.
    for (int y = 0; y < image.getHeight() / 2; y++) {
        int topRowOffset = y * bytesPerScanline;
        int bottomRowOffset = (image.getHeight() - y - 1) * bytesPerScanline;

        // Swap the entire rows between top and bottom.
        for (int i = 0; i < bytesPerScanline; i++) {
            std::swap(flippedImage.imageData[topRowOffset + i], flippedImage.imageData[bottomRowOffset + i]);
        }
    }

    return flippedImage;
};

/*Couldn't get it work
// Creates a 2x2 grid image from 4 images.
TGAImage TGAImage::gridImage(const TGAImage& bottomLeftImage, const TGAImage& bottomRightImage,
                          const TGAImage& topLeftImage, const TGAImage& topRightImage) {

    // Calculate the dimensions of the gridResultImage.
    int gridWidth = bottomLeftImage.getWidth() + bottomRightImage.getWidth();
    int gridHeight = bottomLeftImage.getHeight() + topLeftImage.getHeight();

    TGAImage gridResultImage;
    gridResultImage.setWidth(gridWidth);
    gridResultImage.setHeight(gridHeight);
    gridResultImage.imageData.resize(gridWidth * gridHeight * 3);

    // Variable to keep track of the index in the gridResultImage's imageData vector.
    int pixelIndex = 0;

    for (int y = 0; y < gridHeight; ++y) {
        for (int x = 0; x < gridWidth; ++x) {
            unsigned char red, green, blue;
            
            // Load bottomLeftImage and bottomRightImage line by line.
            if (y < bottomLeftImage.getHeight()) {
                // Load the bottomLeftImage line.
                if (x < bottomLeftImage.getWidth()) {
                    bottomLeftImage.getPixelColor(x, y, red, green, blue);
                }
                // Load the bottomRightImage line.
                else {
                    bottomRightImage.getPixelColor(x - bottomLeftImage.getWidth(), y, red, green, blue);
                }
            }
            // Load the topLeftImage and topRightImage line by line.
            else {
                // Load the topLeftImage line.
                if (x < topLeftImage.getWidth()) {
                    topLeftImage.getPixelColor(x, y - bottomLeftImage.getHeight(), red, green, blue);
                }
                // Load the topRightImage line.
                else {
                    topRightImage.getPixelColor(x - topLeftImage.getWidth(), y - bottomLeftImage.getHeight(), red, green, blue);
                }
            }

            // Set the RGB values in the gridResultImage's imageData vector (in BGR order).
            gridResultImage.imageData[pixelIndex] = blue;    // Blue channel
            pixelIndex++;
            gridResultImage.imageData[pixelIndex] = green;   // Green channel
            pixelIndex++;
            gridResultImage.imageData[pixelIndex] = red;     // Red channel
            pixelIndex++;
        }
    }

    return gridResultImage;
};
*/
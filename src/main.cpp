#include <iostream>
#include <fstream>
#include "TGAImage.h"
using namespace std;


int main() {

    /***** Part 1 *****/
    cout << "Part 1" << endl;

    // Loading in layer1 and pattern1.
    TGAImage layer1;
    cout << "Loading layer1.tga..." << endl;
    layer1.loadTGA("input/layer1.tga");

    TGAImage pattern1;
    cout << "Loading pattern1.tga..." << endl;
    pattern1.loadTGA("input/pattern1.tga");

    // Creating a TGAImage object to store the result of the multiplication, and then multiplying.
    TGAImage part1;
    part1 = TGAImage::multiplyImages(layer1, pattern1);

    // Checking if the result image is empty (dimension mismatch)
    if (part1.getWidth() == 0 || part1.getHeight() == 0) {
        cout << "Error: Result image is empty. Dimension mismatch." << endl;
        return 1;
    }

    // Saving the result image to a new file.
    string outputPart1 = "output/part1.tga";
    bool successPart1 = part1.saveTGA(outputPart1);
    if (!successPart1) {
        cout << "Error: Failed to save the result image." << endl;
        return 1;
    }

    cout << "Result image saved successfully to file: " << outputPart1 << endl;

    /***** Part 2 *****/
    cout << "Part 2" << endl;

    // Loading in layer2 and car.
    TGAImage layer2;
    cout << "Loading layer2.tga..." << endl;
    layer2.loadTGA("input/layer2.tga");

    TGAImage car;
    cout << "Loading car.tga..." << endl;
    car.loadTGA("input/car.tga");

    // Creating a TGAImage object to store the result of the subraction, and then subtracting.
    TGAImage part2;
    part2 = TGAImage::subtractImages(layer2, car);

    // Checking if the result image is empty (dimension mismatch)
    if (part2.getWidth() == 0 || part2.getHeight() == 0) {
        cout << "Error: Result image is empty. Dimension mismatch." << endl;
        return 1;
    }

    // Saving the result image to a new file.
    string outputPart2 = "output/part2.tga";
    bool successPart2 = part2.saveTGA(outputPart2);
    if (!successPart2) {
        cout << "Error: Failed to save the result image." << endl;
        return 1;
    }

    cout << "Result image saved successfully to file: " << outputPart2 << endl;

    /***** Part 3 *****/
    cout << "Part 3" << endl;

    // Loading in pattern2 and text, layer1 was loaded in previously.
    TGAImage pattern2;
    cout << "Loading pattern2.tga..." << endl;
    pattern2.loadTGA("input/pattern2.tga");

    TGAImage text;
    cout << "Loading text.tga..." << endl;
    text.loadTGA("input/text.tga");

    // Creating a TGAImage object to store the result of the multiplication, and then multiplying.
    TGAImage part3Mult;
    part3Mult = TGAImage::multiplyImages(layer1, pattern2);

    // Creating a TGAImage object to store the result of the screen, then screening.
    TGAImage part3;
    part3 = TGAImage::screenImages(text, part3Mult);

    // Checking if the result image is empty (dimension mismatch)
    if (part3.getWidth() == 0 || part3.getHeight() == 0) {
        cout << "Error: Result image is empty. Dimension mismatch." << endl;
        return 1;
    }

    // Saving the result image to a new file.
    string outputPart3 = "output/part3.tga";
    bool successPart3 = part3.saveTGA(outputPart3);
    if (!successPart3) {
        cout << "Error: Failed to save the result image." << endl;
        return 1;
    }

    cout << "Result image saved successfully to file: " << outputPart3 << endl;

    /***** Part 4 *****/
    cout << "Part 4" << endl;

    // Loading in circles, layer2 and pattern2 were loaded in previously.
    TGAImage circles;
    cout << "Loading circles.tga..." << endl;
    circles.loadTGA("input/circles.tga");

    // Creating a TGAImage object to store the result of the multiplication, and then multiplying.
    TGAImage part4Mult;
    part4Mult = TGAImage::multiplyImages(layer2, circles);

    // Creating a TGAImage object to store the result of the subtraction, and then subtracting.
    TGAImage part4;
    part4 = TGAImage::subtractImages(pattern2, part4Mult);

    // Checking if the result image is empty (dimension mismatch)
    if (part4.getWidth() == 0 || part4.getHeight() == 0) {
        cout << "Error: Result image is empty. Dimension mismatch." << endl;
        return 1;
    }

    // Saving the result image to a new file.
    string outputPart4 = "output/part4.tga";
    bool successPart4 = part4.saveTGA(outputPart4);
    if (!successPart4) {
        cout << "Error: Failed to save the result image." << endl;
        return 1;
    }

    cout << "Result image saved successfully to file: " << outputPart4 << endl;

    /***** Part 5 *****/
    cout << "Part 5" << endl;

    // Creating a TGAImage object to store the result of the overlay, then overlaying.
    TGAImage part5;
    part5 = TGAImage::overlayImages(pattern1, layer1);

    // Checking if the result image is empty (dimension mismatch)
    if (part5.getWidth() == 0 || part5.getHeight() == 0) {
        cout << "Error: Result image is empty. Dimension mismatch." << endl;
        return 1;
    }

    // Saving the result image to a new file.
    string outputPart5 = "output/part5.tga";
    bool successPart5 = part5.saveTGA(outputPart5);
    if (!successPart5) {
        cout << "Error: Failed to save the result image." << endl;
        return 1;
    }

    cout << "Result image saved successfully to file: " << outputPart5 << endl;

    /***** Part 6 *****/
    cout << "Part 6" << endl;

    // Creating a TGAImage object to store the result, then adding 200 Green to car.
    TGAImage part6;
    part6 = TGAImage::add200Green(car);

    // Saving the result image to a new file.
    string outputPart6 = "output/part6.tga";
    bool successPart6 = part6.saveTGA(outputPart6);
    if (!successPart6) {
        cout << "Error: Failed to save the result image." << endl;
        return 1;
    }

    cout << "Result image saved successfully to file: " << outputPart6 << endl;

    /***** Part 7 *****/
    cout << "Part 7" << endl;

    // Creating a TGAImage object to store the result, 
    // then multiplying the red channel by 4 and the blue by 0.
    TGAImage part7;
    part7 = TGAImage::scaleChannels(car, 4.0, 0.0);

    // Saving the result image to a new file.
    string outputPart7 = "output/part7.tga";
    bool successPart7 = part7.saveTGA(outputPart7);
    if (!successPart7) {
        cout << "Error: Failed to save the result image." << endl;
        return 1;
    }

    cout << "Result image saved successfully to file: " << outputPart7 << endl;

    /***** Part 8 *****/
    cout << "Part 8" << endl;

    // Separating and saving channels.
    bool result = TGAImage::separateChannels(car, "output/part8_r.tga", "output/part8_g.tga", "output/part8_b.tga");
    if (!result) {
        std::cout << "Error separating channels." << std::endl;
        return 1;
    }

    /***** Part 9 *****/
    cout << "Part 9" << endl;

    // Creating TGAImage objects for the different layers, and loading them in.
    TGAImage layerRed;
    TGAImage layerGreen;
    TGAImage layerBlue;

    layerRed.loadTGA("input/layer_red.tga");
    layerGreen.loadTGA("input/layer_green.tga");
    layerBlue.loadTGA("input/layer_blue.tga");

    // Creating a TGAImage object to store the result and combining the layers.
    TGAImage part9;
    part9 = TGAImage::combineChannels(layerRed, layerGreen, layerBlue);

    // Saving the result image to a new file.
    string outputPart9 = "output/part9.tga";
    bool successPart9 = part9.saveTGA(outputPart9);
    if (!successPart9) {
        cout << "Error: Failed to save the result image." << endl;
        return 1;
    }

    cout << "Result image saved successfully to file: " << outputPart9 << endl;

    /***** PART 10 *****/
    cout << "Part 10" << endl;

    // Creating a TGAImage object for text2 and loading it in.
    TGAImage text2;
    text2.loadTGA("input/text2.tga");

    // Creating a TGAImage object to store the flipped image, and flipping it.
    TGAImage part10;
    part10 = TGAImage::flipImage180(text2);

    // Saving the result image to a new file.
    string outputPart10 = "output/part10.tga";
    bool successPart10 = part10.saveTGA(outputPart10);
    if (!successPart10) {
        cout << "Error: Failed to save the result image." << endl;
        return 1;
    }

    cout << "Result image saved successfully to file: " << outputPart10 << endl;

    /***** Extra Credit *****
    cout << "Extra Credit" << endl;

    //Loading in text1.
    TGAImage text1;
    text1.loadTGA("input/text1.tga");

    // Creating a TGAImage object to store the grid image, and producing it.
    TGAImage extraCredit;
    extraCredit = TGAImage::gridImage(text1, pattern1, car, circles);

    // Saving the result image to a new file.
    string outputEC = "output/extracredit.tga";
    bool successEC = extraCredit.saveTGA(outputEC);
    if (!successEC) {
        cout << "Error: Failed to save the result image." << endl;
        return 1;
    }

    cout << "Result image saved successfully to file: " << outputEC << endl;
    */
    return 0;
};
/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once
#include <iostream>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "cs225/RGB_HSL.h"

using namespace std;


class Image : public cs225::PNG {
    public: 
        
        void lighten(double amount);
        void lighten();
        void darken(double amount);
        void darken();
        void saturate(double amount);
        void saturate();
        void desaturate(double amount);
        void desaturate();
        void grayscale();
        void rotateColor(double degrees);
        void illinify();
        void scale(double factor);
        void scale(unsigned w, unsigned h);

};

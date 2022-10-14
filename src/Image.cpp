#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <stdexcept>
#include <iostream>

void Image::lighten(double amount) {
    for (unsigned w = 0; w < this->width(); w++) {
        for (unsigned h = 0; h < this->height(); h++) {
            cs225::HSLAPixel& pix = this->getPixel(w, h);
            if (pix.l + amount <= 1) {
                pix.l += amount;
            } else {
                pix.l = 1;
            }
        }
    }
}
void Image::lighten() {
    for (unsigned w = 0; w < this->width(); w++) {
        for (unsigned h = 0; h < this->height(); h++) {
            cs225::HSLAPixel& pix = this->getPixel(w, h);
            if (pix.l + 0.1 <= 1) {
                pix.l += 0.1;
            } else {
                pix.l = 1;
            }
        }
    }
}


void Image::darken(double amount) {
    for (unsigned w = 0; w < this->width(); w++) {
        for (unsigned h = 0; h < this->height(); h++) {
            cs225::HSLAPixel& pix = this->getPixel(w, h);
            if (pix.l - amount >= 0) {
                pix.l -= amount;
            } else {
                pix.l = 0;
            }
        }
    }
}

void Image::darken() {
    for (unsigned w = 0; w < this->width(); w++) {
        for (unsigned h = 0; h < this->height(); h++) {
            cs225::HSLAPixel& pix = this->getPixel(w, h);
            if (pix.l - 0.1 >= 0) {
                pix.l -= 0.1;
            } else {
                pix.l = 0;
            }
        }
    }
}

void Image::saturate(double amount) {
    for (unsigned w = 0; w < this->width(); w++) {
        for (unsigned h = 0; h < this->height(); h++) {
            cs225::HSLAPixel& pix = this->getPixel(w, h);
            if (pix.s + amount <= 1) {
                pix.s += amount;
            } else {
                pix.s = 1;
            }
        }
    }

}

void Image::saturate() {
    for (unsigned w = 0; w < this->width(); w++) {
        for (unsigned h = 0; h < this->height(); h++) {
            cs225::HSLAPixel& pix = this->getPixel(w, h);
            if (pix.s + 0.1 <= 1) {
                pix.s += 0.1;
            } else {
                pix.s = 1;
            }
        }
    }
}
void Image::desaturate(double amount) {
    for (unsigned w = 0; w < this->width(); w++) {
        for (unsigned h = 0; h < this->height(); h++) {
            cs225::HSLAPixel& pix = this->getPixel(w, h);
            if (pix.s - amount >= 0) {
                pix.s -= amount;
            } else {
                pix.s = 0;
            }
        }
    }

}
void Image::desaturate() {
    for (unsigned w = 0; w < this->width(); w++) {
        for (unsigned h = 0; h < this->height(); h++) {
            cs225::HSLAPixel& pix = this->getPixel(w, h);
            if (pix.s - 0.1 >= 0) {
                pix.s -= 0.1;
            } else {
                pix.s = 0;
            }
        }
    }
}
void Image::grayscale() {
    for (unsigned w = 0; w < this->width(); w++) {
        for (unsigned h = 0; h < this->height(); h++) {
            cs225::HSLAPixel& pix = this->getPixel(w, h);
            pix.s = 0;
        }
    }
}

void Image::rotateColor(double degrees) {
    for (unsigned w = 0; w < this->width(); w++) {
        for (unsigned h = 0; h < this->height(); h++) {
            cs225::HSLAPixel& pix = this->getPixel(w, h);
            if (pix.h + degrees > 360) {
                pix.h += degrees - 360;
            } else if (pix.h + degrees < 0) {
                pix.h += degrees + 360;
            } else {
                pix.h += degrees;
            }
        }
    }
}

void Image::illinify() {
    for (unsigned w = 0; w < this->width(); w++) {
        for (unsigned h = 0; h < this->height(); h++) {
            cs225::HSLAPixel& pix = this->getPixel(w, h);
            if (pix.h >= 102) { //102 is the midpt between 11 and 216
                pix.h = 216;
            } else {
                pix.h = 11;
            } 
        }
    }
} 

void Image::scale(double factor) {
    if (factor == 1 || factor == 0) { 
        return; 
    }
    //make a new temporary image
    PNG* temp = new Image(*this);

    double new_width = factor * static_cast<double>(this->width());
    double new_height = factor * static_cast<double>(this->height());

    this->resize(new_width, new_height);
    
    // iterate over new image dimensions, set each pixel to corresponding original pixel (using factor to get Pixel)
    for (unsigned w = 0; w < new_width-1; w++) {
        for (unsigned h = 0; h < new_height-1; h++) {
            cs225::HSLAPixel& oldPix = this->getPixel(w, h);  
            //if we don't use a reference for oldPix it will assign oldPix = tempPix...
            //...but oldPix and tempPix disappear after the scope in which they are declared...
            //...if we use references, it will change the base image's pixels, which is what we want!
            cs225::HSLAPixel& tempPix = temp->getPixel(w/factor, h/factor);
            oldPix.s = tempPix.s; 
            oldPix.l = tempPix.l;
            oldPix.h = tempPix.h;
            oldPix.a = tempPix.a;
        }
    }
    delete temp;
}

void Image::scale(unsigned w, unsigned h) { //need to preserve the ratio

    double width_ratio = static_cast<double>(w) / static_cast<double>(this->width());
    double height_ratio = static_cast<double>(h) / static_cast<double>(this->height());

    double factor = static_cast<double>(std::min(width_ratio, height_ratio));

    this->scale(factor);
}

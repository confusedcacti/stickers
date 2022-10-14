/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include "cs225/PNG.h"
#include "Image.h"
#include "cs225/HSLAPixel.h"


using namespace std;

class StickerSheet {
    public: 
        StickerSheet(const Image &picture, unsigned max);
        ~StickerSheet();
        StickerSheet(const StickerSheet &other);
        const StickerSheet& operator=(const StickerSheet &other);
        
        void changeMaxStickers(unsigned max);
        int addSticker(Image &sticker, unsigned x, unsigned y);
        bool translate(unsigned index, unsigned x, unsigned y);
        void removeSticker(unsigned index);
        Image* getSticker(unsigned index);
        Image render() const;
    private:
        Image base;
        unsigned max_;
        vector <Image*> stickers;
        vector <std::pair<unsigned, unsigned>> coordinates;
        //for x to x + width
        //for y to y + height
            //draw each pixel
        //resize to dimensions of sticker 
        //if x+w > current w, then resize(x+w), same with height
};

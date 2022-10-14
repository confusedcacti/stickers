
#include "Image.h"
#include "StickerSheet.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <iostream>
#include <vector>
#include <utility>


StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    base = picture; //set private vairables
    max_ = max;
}

StickerSheet::~StickerSheet() {
    
    //delete StickerSheet;
}

StickerSheet::StickerSheet(const StickerSheet &other) {
    //StickerSheet* other = new StickerSheet(*this);
    this->base = other.base;
    this->max_ = other.max_;
    for (unsigned i = 0; i < other.stickers.size(); i++) {
        this->stickers.push_back(other.stickers[i]);
        this->coordinates.push_back(other.coordinates[i]); //copy over the stickers and their coordinates
    }
}

const StickerSheet& StickerSheet::operator=(const StickerSheet &other) {
    if (this == &other) {
        return *this; //dereference pointer to access the value
    }
    // StickerSheet temp = new StickerSheet(other);
    // delete other;
    // other = temp;
    this->base = other.base;
    this->max_ = other.max_;
    for (unsigned i = 0; i < other.stickers.size(); i++) {
        this->stickers.push_back(other.stickers[i]);
        this->coordinates.push_back(other.coordinates[i]); //copy over the stickers and their coordinates
    }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) { //if new max < current max, stickers at indexes max - 1 are lost
    if (max < max_) {
        while (max < stickers.size()) {
            stickers.pop_back();
            coordinates.pop_back();
        }
    }
    // if (max > max_) {
    //     for (unsigned i = 0; i < max - max_; i++) {
    //         stickers.push_back(NULL);
    //         coordinates.push_back(std::make_pair(NULL, NULL));
    //     }
    // }
    // stickers.resize(max);
    // coordinates.resize(max);
    max_ = max;
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
    if (stickers.size() != max_) {
        stickers.push_back(&sticker);
        coordinates.push_back(std::make_pair(x, y));
        return stickers.size()-1;
    }
    return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    if (index < stickers.size() && index >= 0 && stickers[index] != NULL) {
        coordinates[index].first = x;
        coordinates[index].second = y;
        return true;
    }
    return false;
}

void StickerSheet::removeSticker(unsigned index) {
    if (index >= 0 && index < stickers.size()) {
        stickers.erase(stickers.begin() + index);
        coordinates.erase(coordinates.begin() + index);
    }
   //std::cout<<"size before removal: "<< coordinates.size()<<std::endl; 
    
    //std::cout<<"size after removal: "<< coordinates.size()<<std::endl; 

}

Image* StickerSheet::getSticker(unsigned index) {
    if (index >= stickers.size()) {
        return NULL;
    }
    return stickers[index];
}

Image StickerSheet::render() const {
    Image base_temp = base;
    for (unsigned i = 0; i < coordinates.size(); i++) { //for each sticker's x and y coordinates:
        unsigned x_coord = coordinates[i].first;    //x coord  
        unsigned y_coord = coordinates[i].second;   //y coord
        unsigned sticker_width = stickers[i]->width();  //dimensions of the image
        unsigned sticker_height = stickers[i]->height();   

        if (x_coord + sticker_width > base_temp.width()) { //if the sticker's width goes off the image's width
            base_temp.resize(x_coord + sticker_width, base_temp.height()); 
        }
        if (y_coord + sticker_height > base_temp.height()) {
            base_temp.resize(base_temp.width(), sticker_height + y_coord);
        }

        for (unsigned j = 0; j < sticker_width; j++) {
            for (unsigned k = 0; k < sticker_height; k++) {
                cs225::HSLAPixel& base_pix = base_temp.getPixel(j + x_coord, k + y_coord);
                cs225::HSLAPixel sticker_pix = stickers[i]->getPixel(j, k); //without &, it makes a new copy of a pixel, which wont show up on the image
            //we DONT want to change the sticker if we change the base image
            //....so we DONT want to make a copy of the sticker pixel
                if (sticker_pix.a != 0) {
                    base_pix.h = sticker_pix.h;      
                    base_pix.s = sticker_pix.s;
                    base_pix.l = sticker_pix.l;
                    base_pix.a = sticker_pix.a;
                } //overwrite the pixel of the image with the pixel of the sticker 
            }
        }
    }
    return base_temp;
}
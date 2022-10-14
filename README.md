# stickers-
Class Machine Project (independent): Create a masterpiece of stickers made up of your very own images of choice! Like in kindergarten, but cooler.

Create your sticker art in main.cpp:

Image i;        

i.readFromFile("../i.png");

StickerSheet sheet(i, 18);

Image myImage = sheet.render();

myImage.writeToFile("../myImage.png");


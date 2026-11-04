#include "CharactersLoad.h"

#ifndef CHARACTERS_DIR
#define CHARACTERS_DIR "Template/src/characters/"
#endif

#define STB_IMAGE_IMPLEMENTATION
#include <vector>//temporarily store information about the image's pixels while filling the bubble.
#include "stb_image.h"


Pixeldata hulk;
//ashrar
Pixeldata magneto;
Pixeldata doom;
Pixeldata thanos;


Pixeldata SPcrouch;
Pixeldata SPstand;
Pixeldata web;
Pixeldata webimpact;

//captain a
Pixeldata Cap;
Pixeldata Capfight;
Pixeldata Cjump;
Pixeldata Ccrouch;


//cutscene
Pixeldata d1;
Pixeldata d2;
Pixeldata kneel;
Pixeldata u;
Pixeldata f;
//magneto part fel scene 
Pixeldata m1;
Pixeldata m2;
//thanis
Pixeldata t1;
Pixeldata t2;
//objects
Pixeldata background;
Pixeldata thought;
Pixeldata temple;
bool loadtemple(){
    temple.ppointer=stbi_load(CHARACTERS_DIR "doom/temple.png",&temple.width,&temple.height,&temple.channels,0);
    if (temple.ppointer==nullptr){
        return false;
    }
    return true;
}
bool loadback(){
    background.ppointer=stbi_load(CHARACTERS_DIR "doom/background.png",&background.width,&background.height,&background.channels,0);
    if (background.ppointer==nullptr){
        return false;
    }
    return true;

}
bool loadt1(){
   t1.ppointer=stbi_load(CHARACTERS_DIR "thanos/thanos1.png",&t1.width,&t1.height,&t1.channels,0);
    if (t1.ppointer==nullptr){
        return false;
    }
    return true;

}
bool loadt2(){
    t2.ppointer=stbi_load(CHARACTERS_DIR "thanos/thanos2.png",&t2.width,&t2.height,&t2.channels,0);
    if (t2.ppointer==nullptr){
        return false;
    }
    return true;

}


bool loadm1(){
    m1.ppointer=stbi_load(CHARACTERS_DIR "magneto/mag1.png",&m1.width,&m1.height,&m1.channels,0);
    if (m1.ppointer==nullptr){
        return false;
    }
    return true;

}

bool loadm2(){
    m2.ppointer=stbi_load(CHARACTERS_DIR "magneto/mag2.png",&m2.width,&m2.height,&m2.channels,0);
    if (m2.ppointer==nullptr){
        return false;
    }
    return true;
}






bool load1(){
    d1.ppointer=stbi_load(CHARACTERS_DIR "doom/doom1.png",&d1.width,&d1.height,&d1.channels,0);
    if (d1.ppointer==nullptr){
        return false;
    }
    return true;

}

bool load2(){
    d2.ppointer=stbi_load(CHARACTERS_DIR "doom/doom2.png",&d2.width,&d2.height,&d2.channels,0);
    if (d2.ppointer==nullptr){
        return false;
    }
    return true;

}

bool load3(){
    kneel.ppointer=stbi_load(CHARACTERS_DIR "doom/kneel.png",&kneel.width,&kneel.height,&kneel.channels,0);
    if (kneel.ppointer==nullptr){
        return false;
    }
    return true;

}




bool loadhulk(){
    hulk.ppointer=stbi_load(CHARACTERS_DIR "hulk/hulk.png",&hulk.width,&hulk.height,&hulk.channels,0);
    if (hulk.ppointer==nullptr){
        return false;
    }
    return true;

}
bool loadfight(){
    Capfight.ppointer=stbi_load(CHARACTERS_DIR "captainAmerica/weapon.png",&Capfight.width,&Capfight.height,&Capfight.channels,0);
    if (Capfight.ppointer==nullptr){
        return false;
    }
    return true;
}

bool loadCjump(){
    Cjump.ppointer=stbi_load(CHARACTERS_DIR "captainAmerica/jump.png",&Cjump.width,&Cjump.height,&Cjump.channels,0);
    if (Cjump.ppointer==nullptr){
        return false;
    }
    return true;
}

bool loadCcrouch(){
    Ccrouch.ppointer=stbi_load(CHARACTERS_DIR "captainAmerica/crouch.png",&Ccrouch.width,&Ccrouch.height,&Ccrouch.channels,0);
    if (Ccrouch.ppointer==nullptr){
        return false;
    }
    return true;
}


bool loadCap(){
    Cap.ppointer=stbi_load(CHARACTERS_DIR "captainAmerica/run.png",&Cap.width,&Cap.height,&Cap.channels,0);
    if (Cap.ppointer==nullptr){
        return false;
    }
    return true;
    
}


bool loadSPCROUCH(){
SPcrouch.ppointer=stbi_load(CHARACTERS_DIR "spiderman/crouch.png",&SPcrouch.width,&SPcrouch.height,&SPcrouch.channels,0);

if (SPcrouch.ppointer == nullptr) {
    return false;
}
return true;

}

bool loadSPSTAND(){
    stbi_set_flip_vertically_on_load(true);
    SPstand.ppointer=stbi_load(CHARACTERS_DIR "spiderman/stand.png",&SPstand.width,&SPstand.height,&SPstand.channels,0);
    if (SPstand.ppointer == nullptr) {
        return false;
    }
    return true;
}


//thanos
bool loadthanos(){
    thanos.ppointer=stbi_load(CHARACTERS_DIR "thanos/thanos.png",&thanos.width,&thanos.height,&thanos.channels,0);
    if (thanos.ppointer == nullptr) {
        return false;
    }
    return true;
}

// magneto
bool loadmagneto(){
    magneto.ppointer=stbi_load(CHARACTERS_DIR "magneto/magneto.png",&magneto.width,&magneto.height,&magneto.channels,0);
    if (magneto.ppointer == nullptr) {
        return false;
    }
    return true;
}

//i am doom
bool loaddoom(){
    doom.ppointer=stbi_load(CHARACTERS_DIR "doom/doom.png",&doom.width,&doom.height,&doom.channels,0);
    if (doom.ppointer == nullptr) {
        return false;
    }
    return true;
}

bool loadweb(){
    web.ppointer=stbi_load(CHARACTERS_DIR "spiderman/web.png",&web.width,&web.height,&web.channels,0);
    if (web.ppointer == nullptr) {
        return false;
    }
    return true;

}
bool loadwebimpact(){
    webimpact.ppointer=stbi_load(CHARACTERS_DIR "spiderman/collision.png",&webimpact.width,&webimpact.height,&webimpact.channels,0);
    if (webimpact.ppointer == nullptr) {
        return false;
    }
    return true;

}

//ok

void fillThoughtBubbleWhite(Pixeldata& image){
    // Make sure the image exists and has RGBA channels
    if (image.ppointer == nullptr || image.channels != 4)
        return;

    int width = image.width;
    int height = image.height;
    int totalPixels = width * height;

    unsigned char* pixels = image.ppointer;

    // Store the black outline pixels
    std::vector<unsigned char> outline(totalPixels, 0);

    // Store the outline after expanding it slightly
    std::vector<unsigned char> dilated(totalPixels, 0);

    // Store the outline after closing tiny gaps
    std::vector<unsigned char> closedOutline(totalPixels, 0);

    // Mark pixels that can be reached from outside the bubble
    std::vector<unsigned char> outside(totalPixels, 0);


    // STEP 1: Detect the black outline
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int index = y * width + x;
            int p = index * 4;

            if (pixels[p + 3] > 20 &&
                pixels[p] < 100 &&
                pixels[p + 1] < 100 &&
                pixels[p + 2] < 100)
            {
                outline[index] = 1;
            }
        }
    }


    // STEP 2: Expand the outline by one pixel
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            bool found = false;

            for (int dy = -1; dy <= 1; dy++)
            {
                for (int dx = -1; dx <= 1; dx++)
                {
                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx < 0 || nx >= width ||
                        ny < 0 || ny >= height)
                        continue;

                    int neighbour = ny * width + nx;

                    if (outline[neighbour])
                        found = true;
                }
            }

            dilated[y * width + x] = found ? 1 : 0;
        }
    }


    // STEP 3: Close tiny gaps in the outline
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            bool all = true;

            for (int dy = -1; dy <= 1; dy++)
            {
                for (int dx = -1; dx <= 1; dx++)
                {
                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx < 0 || nx >= width ||
                        ny < 0 || ny >= height)
                    {
                        all = false;
                        continue;
                    }

                    int neighbour = ny * width + nx;

                    if (!dilated[neighbour])
                        all = false;
                }
            }

            closedOutline[y * width + x] = all ? 1 : 0;
        }
    }


    // STEP 4: Start flood filling from the image borders
    std::vector<int> queue;
    queue.reserve(totalPixels);

    auto addOutside = [&](int x, int y)
    {
        if (x < 0 || x >= width ||
            y < 0 || y >= height)
            return;

        int index = y * width + x;

        if (!closedOutline[index] && !outside[index])
        {
            outside[index] = 1;
            queue.push_back(index);
        }
    };

    // Start from all four image borders
    for (int x = 0; x < width; x++)
    {
        addOutside(x, 0);
        addOutside(x, height - 1);
    }

    for (int y = 0; y < height; y++)
    {
        addOutside(0, y);
        addOutside(width - 1, y);
    }


    // STEP 5: Explore all connected outside pixels
    for (size_t i = 0; i < queue.size(); i++)
    {
        int index = queue[i];

        int x = index % width;
        int y = index / width;

        addOutside(x - 1, y);
        addOutside(x + 1, y);
        addOutside(x, y - 1);
        addOutside(x, y + 1);
    }


    // STEP 6: Fill enclosed areas with solid white
    for (int i = 0; i < totalPixels; i++)
    {
        int p = i * 4;

        bool originalBlackOutline =
            pixels[p + 3] > 0 &&
            pixels[p] < 100 &&
            pixels[p + 1] < 100 &&
            pixels[p + 2] < 100;

        if (!outside[i] && !originalBlackOutline)
        {
            pixels[p]     = 255;
            pixels[p + 1] = 255;
            pixels[p + 2] = 255;
            pixels[p + 3] = 255;
        }
    }
}





//ok
bool loadthought(){
    thought.ppointer = stbi_load(
    CHARACTERS_DIR "doom/chat.png",
    &thought.width,
    &thought.height,
    &thought.channels,
    0);

    if(thought.ppointer==nullptr){
        return false;
    }
    fillThoughtBubbleWhite(thought); 
    return true;

}

bool loadu(){
     u.ppointer=stbi_load(CHARACTERS_DIR "doom/u.png",&u.width,&u.height,&u.channels,0);
    if (u.ppointer == nullptr) {
        return false;
    }
    return true;

}
bool loadf(){
    f.ppointer=stbi_load(CHARACTERS_DIR "doom/f.png",&f.width,&f.height,&f.channels,0);
    if (f.ppointer == nullptr) {
        return false;
    }
    return true;


}
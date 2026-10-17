#include "CharactersLoad.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"




Pixeldata SPcrouch;
Pixeldata SPstand;
Pixeldata SPweb;
Pixeldata Hulk;
Pixeldata Cap;


bool loadSPCROUCH(){
SPcrouch.ppointer=stbi_load("Template/src/characters/spiderman/crouch.png",&SPcrouch.width,&SPcrouch.height,&SPcrouch.channels,0);

if (SPcrouch.ppointer == nullptr) {
    return false;
}
return true;

}

bool loadSPSTAND(){
    stbi_set_flip_vertically_on_load(true);
    SPstand.ppointer=stbi_load("Template/src/characters/spiderman/stand.png",&SPstand.width,&SPstand.height,&SPstand.channels,0);
    if (SPstand.ppointer == nullptr) {
        return false;
    }
    return true;
}

bool loadSPWEB(){
    SPweb.ppointer=stbi_load("Template/src/characters/spiderman/web.png",&SPweb.width,&SPweb.height,&SPweb.channels,0);
    if (SPweb.ppointer == nullptr) {
        return false;
    }
    return true;
}
#include <iostream>
#include <fstream>
#include <array>

#include <filesystem.h>
#include <nds.h>
#include <NEMain.h>
#include <nf_lib.h>

#include "vector2.hpp"
#include "terraingen.hpp"


TerrainGen::TerrainGen(std::string filename){
    std::ifstream file(filename);
    std::string readText;
    getline(file, readText);
    if(readText != "_TRN"){
        NF_Error(101, filename.data(), 3);
    }
    int index = 0;
    while(getline(file, readText)){
        if(index >= materialAmmount){
            NF_Error(6001, "_TRN", 3);
        }
        NE_MaterialTexLoadGRF(materials.at(index), NULL, NE_TEXGEN_TEXCOORD, readText.data());
        index += 1;
    }
    for(int i = 0; i < spritesAmmount; i++){
        sprites.at(i) = NE_SpriteCreate();
    }
}

void TerrainGen::moveSprite(NE_Sprite* sprite, Vector2i position, int i){
    //for(int i = 0; i < spritesAmmount; i++){
    NE_SpriteSetPos(sprite, (position.x%tileSize)-384 + (i%3)*256, (position.y%tileSize)-96 + (i/3)*192); // Position définie à partir du centre de l'écran
}

void TerrainGen::setSpriteMaterial(NE_Sprite* sprite, Vector2i position){
    int chosen_mat = 0;
    NE_SpriteSetMaterial(sprite, materials.at(chosen_mat));
}

void TerrainGen::update(Vector2i position){
    for(int i = 0; i < spritesAmmount; i++){
        moveSprite(sprites.at(i), position, i);
        setSpriteMaterial(sprites.at(i), position);
    }
}

TerrainGen::~TerrainGen(){
    for(NE_Material* material : materials){
        NE_MaterialDelete(material);
    }
    for(NE_Sprite* sprite : sprites){
        NE_SpriteDelete(sprite);
    }
}

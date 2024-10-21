#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include <nds.h>
#include <nf_lib.h>

#include "vector2.hpp"
#include "player.hpp"
#include "terraingen.hpp"


Player::Player(int x, int y){
    position = Vector2(x, y);
    sprite = TerrainGen::SPRITE_AMMOUNT;
    NF_LoadSpriteGfx("sprites/perso", TerrainGen::TEXTURE_AMMOUNT, 32, 32);
    NF_LoadSpritePal("sprites/perso", TerrainGen::PALETTE_AMMOUNT);
    NF_Vram3dSpriteGfx(TerrainGen::TEXTURE_AMMOUNT, TerrainGen::TEXTURE_AMMOUNT, false);
    NF_Vram3dSpritePal(TerrainGen::PALETTE_AMMOUNT, TerrainGen::PALETTE_AMMOUNT);
    NF_Create3dSprite(sprite, TerrainGen::TEXTURE_AMMOUNT, TerrainGen::PALETTE_AMMOUNT, 112, 80);
}

Player::~Player(){
    NF_Delete3dSprite(sprite);
    NF_Free3dSpriteGfx(TerrainGen::TEXTURE_AMMOUNT);
    NF_UnloadSpriteGfx(TerrainGen::TEXTURE_AMMOUNT);
    NF_UnloadSpritePal(TerrainGen::PALETTE_AMMOUNT);
}

int Player::index_from_direction(Vector2i direction){
    switch(direction.x){
        case 0:
            if(!direction.y){
                return -1;
            }
            if(direction.y > 0){
                return 0;
            }
            return 4;
        case 1:
            if(!direction.y){
                return 6;
            }
            if(direction.y > 0){
                return 7;
            }
            return 5;
        case -1:
            if(!direction.y){
                return 2;
            }
            if(direction.y > 0){
                return 1;
            }
            return 3;
    }
    return -1;
}

void Player::update(){
    Vector2i directionI(0, 0);
    //Vector2 direction(0, 0);
    if(KEY_UP & keysHeld()){
        directionI.y -= 1;
	}
    if(KEY_DOWN & keysHeld()){
        directionI.y += 1;
    }
    if(KEY_LEFT & keysHeld()){
        directionI.x -= 1;
    }
    if(KEY_RIGHT & keysHeld()){
        directionI.x += 1;
    }
    Vector2 direction((float)directionI.x, (float)directionI.y);
    direction.normal();
    if(!std::isnan(direction.x) && !std::isnan(direction.y)){
        walk_frame += 1;
        walk_frame %= 20;
        position.x += direction.x*1.5;
        position.y += direction.y*1.5;
    }
    camPosition = position.to_vector2i();
    int frame = index_from_direction(directionI);
    if(frame == -1) return;
    int current_walk_frame = walk_frame/5;
    if(current_walk_frame == 2){
        current_walk_frame = 0;
    }
    if(current_walk_frame == 3){
        current_walk_frame = 2;
    }
    NF_Set3dSpriteFrame(sprite, frame + 8*current_walk_frame);
}

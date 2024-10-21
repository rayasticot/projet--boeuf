#include <iostream>
#include <cmath>

#include "vector2.hpp"


Vector2i::Vector2i(int x, int y){
    this->x = x;
    this->y = y;
}

Vector2::Vector2(float x, float y){
    this->x = x;
    this->y = y;
}

Vector2i Vector2::to_vector2i(){
    return Vector2i((int)x, (int)y);
}

void Vector2::normal(){
    float norme = sqrt(x*x + y*y);
    x /= norme;
    y /= norme;
}

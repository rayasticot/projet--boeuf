#ifndef VECTOR2_HPP
#define VECTOR2_HPP

class Vector2i{
    public:
        int x;
        int y;
        Vector2i(int x, int y);
};

class Vector2{
    public:
        float x;
        float y;
        Vector2(float x, float y);
        Vector2i to_vector2i();
        void normal();
};

#endif
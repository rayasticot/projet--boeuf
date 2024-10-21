#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player{
    private:
        Vector2 position = Vector2(0, 0);
        u8 sprite;
        u8 walk_frame = 0;

        int index_from_direction(Vector2i direction);
    public:
        Vector2i camPosition = Vector2i(0, 0);
        Player(int x, int y);
        ~Player();
        void update();
};

#endif
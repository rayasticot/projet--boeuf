#ifndef TERRAINGGEN_HPP
#define TERRAINGGEN_HPP

class TerrainGen{
    private:
        static constexpr int materialAmmount = 1;
        static constexpr int spritesAmmount = 9;
        static constexpr int tileSize = 256;
        std::array<NE_Material*, materialAmmount> materials;
        std::array<NE_Sprite*, spritesAmmount> sprites;

        void moveSprite(NE_Sprite* sprite, Vector2i position, int i);
        void setSpriteMaterial(NE_Sprite* sprite, Vector2i position);
    public:
        TerrainGen(std::string filename);
        void update(Vector2i position);
        ~TerrainGen();
};

#endif
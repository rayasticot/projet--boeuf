#ifndef TERRAINGEN_HPP
#define TERRAINGEN_HPP

class TerrainGen{
    /*
        Le mot texture est utilisé pour désigner une image.
        Le mot sprite ici, désigne un "objet image" présent dans le monde.
    */
    bool textureLoaded = false;
    bool paletteLoaded = false;
    bool spriteCreated = false;

    void load_textures_and_palettes(std::string filename);
    void create_sprites();
    void delete_sprites();
    void unload_textures_and_palettes();

    int get_tile_from_pos(Vector2i pos);

    public:
        static constexpr int TEXTURE_AMMOUNT = 2;
        static constexpr int PALETTE_AMMOUNT = 1;
        static constexpr int TEXTURE_SIZE = 128;
        static constexpr int SPRITE_AMMOUNT = 16; // 4x3

        void update(Vector2i playerPos);
        TerrainGen(std::string filename);
        ~TerrainGen();
};

#endif
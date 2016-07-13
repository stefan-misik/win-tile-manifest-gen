#include "win_tile_manifest_gen.h"

int main()
{
    win_tile_manifest_t tile;
    
    tile.tile_color.red = 255;
    tile.tile_color.green = 127;
    tile.tile_color.blue = 16;
    tile.flags = WIN_TILE_FLAGS_SHOW_NAME | WIN_TILE_FLAGS_FOREGROUND_DARK;
    
    
    generate_win_tile_manifest("win-tile-manifest-gen.exe", &tile);
    return 0;
}
#include "win_tile_manifest_gen.h"
#include <stdio.h>

/******************************************************************************/
int static ask_yn_question(
    const char * question
)
{
    return 0;
}

/******************************************************************************/
int main(
    int argc, 
    char *argv[]
)
{
    win_tile_manifest_t tile;
    char file_name[1024];
    unsigned short int c_r, c_g, c_b;
    
    /* Get the file name */
    printf("Enter aplication file name (including .exe): ");
    fflush(stdout);
    scanf("%1023s", file_name);
    
    /* Get the tile color */
    printf("Enter tile color in the format RRR,GGG,BBB: ");
    fflush(stdout);
    scanf("%hu,%hu,%hu", &c_r, &c_g, &c_b);
    
    
   
    /* Fill the tile configuration structure */
    tile.tile_color.red = (unsigned char)c_r;
    tile.tile_color.green = (unsigned char)c_g;
    tile.tile_color.blue = (unsigned char)c_b;
    tile.flags = 0;
    tile.flags |= ask_yn_question("Show name on tile") * 
            WIN_TILE_FLAGS_SHOW_NAME;
    tile.flags |= ask_yn_question("Dark text on a tile") * 
            WIN_TILE_FLAGS_FOREGROUND_DARK;
    
    /* Generate manifest file */
    generate_win_tile_manifest(file_name, &tile);
    return 0;
}
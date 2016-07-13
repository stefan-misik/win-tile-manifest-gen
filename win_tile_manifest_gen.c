#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "win_tile_manifest_gen.h"

/******************************************************************************/
static const char manifest_head[] = 
    "<Application xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">\n"
    "<VisualElements";

/******************************************************************************/
static const char * manifest_visual_elements[] =
{
    "\nBackgroundColor=\"#%02hx%02hx%02hx\"",
    "\nShowNameOnSquare150x150Logo=\"%s\"",
    "\nForegroundText=\"%s\"",
};

/******************************************************************************/
static const char manifest_foot[] =
    "/>\n"
    "</Application>";

/******************************************************************************/
static const char * manifest_bool_values[] =
{
    "off",
    "on"
};

/******************************************************************************/
static const char * manifest_themes[] =
{
    "light",
    "dark"
};


/******************************************************************************/
void static get_maniest_file_name(char * file_name, int buffer_length)
{
    int pos;
    
    /* Remove extension */
    pos = strlen(file_name) - 1;
    for(; pos >= 0; pos --)
    {
        if('.' == file_name[pos])
        {
            file_name[pos] = '\0';
            break;
        }
    }
    
    /* Add new extension */
    strcat(file_name, ".VisualElementsManifest.xml");  
}

/******************************************************************************/
void generate_win_tile_manifest(
    const char * executable_file_name,
    win_tile_manifest_t * manifest
)
{    
    int file_name_length;
    char * file_name;
    
    file_name_length = strlen(executable_file_name) + 32;    
    
    /* Allocate memory for the file name */
    file_name = (char *)malloc(sizeof(char) * file_name_length);
    
    if((char *)0 != file_name)
    {
        FILE * manifest_file;
        
        /* Copy string */
        strcpy(file_name, executable_file_name);
        
        /* Get Manifest file name */
        get_maniest_file_name(file_name, file_name_length);
        
        /* Open manifest file for writing */
        manifest_file = fopen(file_name, "w");
        
        /* Free buffer containing the manifest file name */
        free(file_name);
        file_name = (char *)0;
        
        /* Check if manifest file was opened */
        if((FILE *)0 != manifest_file)
        {
            /* Write manifest header */
            fputs(manifest_head, manifest_file);
            
            /* Write configuration into manifest file */
            fprintf(manifest_file, manifest_visual_elements[0], 
                    (unsigned short int)(manifest->tile_color.red), 
                    (unsigned short int)(manifest->tile_color.green), 
                    (unsigned short int)(manifest->tile_color.blue));
            
            fprintf(manifest_file, manifest_visual_elements[1],
                    manifest_bool_values[
                        (manifest->flags & WIN_TILE_FLAGS_SHOW_NAME) ? 1 : 0
                    ]);
            
            fprintf(manifest_file, manifest_visual_elements[2],
                    manifest_themes[
                        (manifest->flags & WIN_TILE_FLAGS_FOREGROUND_DARK) ? 
                            1 : 0
                    ]);
            
            /* Write manifest footer */
            fputs(manifest_foot, manifest_file);
            
            /* Close manifest file */
            fclose(manifest_file);
        }      
    }
}
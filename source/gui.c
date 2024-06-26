/*******************************************************************************************
*	Creation and handling of all GUIs
*	Work in progress
*
*   Created by Evan Posharow
********************************************************************************************/
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION
#define NK_KEYSTATE_BASED_INPUT
#include <nuklear/nuklear.h>
#include <nuklear/nuklear_glfw_gl3.h>
#include <nuklear/style.c>
#include "game.h"
#include "common.h"

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

struct nk_glfw glfw = {0};
struct nk_context* ctx;
GLFWwindow* win;
int width1, height1;
struct nk_font *menuFont;
struct nk_font *basicFont;

//game resources
int wood = 500;
int gold = 500;
 
void gui_Init(GLFWwindow* window)
{
    //size of initial window: 960,540
    win = window;
    ctx = nk_glfw3_init(&glfw, win, NK_GLFW3_INSTALL_CALLBACKS);

    //adding custom fonts
    {struct nk_font_atlas *atlas;
    nk_glfw3_font_stash_begin(&glfw, &atlas);
    menuFont = nk_font_atlas_add_from_file(atlas, "../include/nuklear/extra_font/trade-winds.regular.ttf", 50, 0);
    basicFont = nk_font_atlas_add_from_file(atlas, "../include/nuklear/extra_font/amiko.regular.ttf", 18, 0);
    nk_glfw3_font_stash_end(&glfw);
    nk_style_set_font(ctx, &menuFont->handle);
    
    }
 
}

void gui_Render()
{
    glfwPollEvents();
    nk_glfw3_new_frame(&glfw);

    //creates all guis
    gui_admin();
    gui_settings();
    gui_buildings();
    gui_resources();
    gui_main_menu();
    

    
    nk_glfw3_render(&glfw, NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
}

void gui_admin()
{
    int INITIAL_GUI_X_POSITION = 0;
    int INITIAL_GUI_Y_POSITION = 0;
    int INITIAL_GUI_WIDTH = 250;
    int INITIAL_GUI_HEIGHT = 200;
    if (nk_begin(ctx, "Admin GUI", nk_rect(INITIAL_GUI_X_POSITION, INITIAL_GUI_Y_POSITION, INITIAL_GUI_WIDTH, INITIAL_GUI_HEIGHT), NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
        {
            nk_spacer(ctx);
            nk_layout_row_dynamic(ctx, 40, 2);
            if (nk_button_label(ctx, "add gold"))
            {
                gold = gold + 1000;
            }
            if (nk_button_label(ctx, "add wood"))
            {
                wood = wood + 1000;
            }
        }
    nk_end(ctx);
}

void gui_settings()
{
    int INITIAL_GUI_X_POSITION = 730;
    int INITIAL_GUI_Y_POSITION = 5;
    int INITIAL_GUI_WIDTH = 225;
    int INITIAL_GUI_HEIGHT = 200;
    if (nk_begin(ctx, "Settings", nk_rect(INITIAL_GUI_X_POSITION, INITIAL_GUI_Y_POSITION, INITIAL_GUI_WIDTH, INITIAL_GUI_HEIGHT), NK_WINDOW_BORDER|NK_WINDOW_TITLE|NK_WINDOW_MOVABLE))
        {
            //repositions gui when window size changes
            nk_window_set_position(ctx, "Settings", nk_vec2(get_width() - 230 , 5));

            //Volume slider
            static float value = 0.6f;
            nk_layout_row_begin(ctx, NK_STATIC, 30, 2);
                {
                    nk_layout_row_push(ctx, 50);
                    nk_label(ctx, "Volume:", NK_TEXT_LEFT);
                    nk_layout_row_push(ctx, 110);
                    nk_slider_float(ctx, 0, &value, 1.0f, 0.1f);
                 }
            nk_layout_row_end(ctx);

            //Theme selector toggles
            enum {BLACK, BLUE, DARK, RED, WHITE};
            static int current_Theme = RED;
            nk_layout_row_dynamic(ctx, 30, 2);
            if(nk_option_label(ctx, "red", current_Theme == RED))
            {
                current_Theme = RED;
                set_style(ctx, THEME_RED);
            } 
            if(nk_option_label(ctx, "blue", current_Theme == BLUE)) 
            {
                current_Theme = BLUE;
                set_style(ctx, THEME_BLUE);
            } 
            if(nk_option_label(ctx, "dark", current_Theme == DARK)) 
            {
                current_Theme = DARK;
                set_style(ctx, THEME_DARK);
            } 
            if(nk_option_label(ctx, "black", current_Theme == BLACK)) 
            {
                current_Theme = BLACK;
                set_style(ctx, THEME_BLACK);
            } 
            if(nk_option_label(ctx, "white", current_Theme == WHITE)) 
            {
                current_Theme = WHITE;
                set_style(ctx, THEME_WHITE);
            } 
            

        }
    nk_end(ctx);
}

void gui_buildings()
{
    int INITIAL_GUI_X_POSITION = 240;
    int INITIAL_GUI_Y_POSITION = 432;
    int INITIAL_GUI_WIDTH = 480;
    int INITIAL_GUI_HEIGHT = 108;
    if (nk_begin(ctx, "Build", nk_rect(INITIAL_GUI_X_POSITION, INITIAL_GUI_Y_POSITION, INITIAL_GUI_WIDTH, INITIAL_GUI_HEIGHT), NK_WINDOW_BORDER|NK_WINDOW_MOVABLE))
        {   
            //scale position with window
            int dynamicX = (get_width()/2) - (get_width()/4);
            int dynamicY = get_height() - 108;
            nk_window_set_position(ctx, "Build", nk_vec2(dynamicX , dynamicY));

            //scale size with window
            nk_window_set_size(ctx,"Build", nk_vec2(get_width()/2 , 108));

            nk_layout_row_dynamic(ctx, 20, 1);
            nk_label(ctx, "Price:", NK_TEXT_ALIGN_CENTERED);

            //4 labels for build menu
            nk_layout_row_dynamic(ctx, 20, 4);
            nk_label_colored(ctx, "100 Gold", NK_TEXT_ALIGN_CENTERED, nk_rgb(240, 252, 3));
            /* nk_label_colored(ctx, "200 Wood",   NK_TEXT_ALIGN_CENTERED, nk_rgb(0, 255, 0));
            nk_label_colored(ctx, "800 Wood", NK_TEXT_ALIGN_CENTERED, nk_rgb(0, 255, 0));
            nk_label_colored(ctx, "200 Gold", NK_TEXT_ALIGN_CENTERED, nk_rgb(240, 252, 3)); */

            //4 buttons for build menu
            nk_layout_row_dynamic(ctx, 36, 4);
            if (nk_button_label(ctx, "Buy Units"))
            {
                if(gold >= 100){
                    gold = gold - 100;
                    //fprintf(stdout, "\nBought a unit");
                    SpawnUnitFromCastle();
                }
                else{
                    fprintf(stdout, "\nNot enough Gold");
                }

            }
            /* if (nk_button_label(ctx, "Build Tree"))
            {
                if(wood >= 200){
                    wood = wood - 200;
                    fprintf(stdout, "\nBuilt Tree");
                }
                else{
                    fprintf(stdout, "\nNot enough Wood");
                }
            }
            if (nk_button_label(ctx, "Build House"))
            {
                if(wood >= 800){
                    wood = wood - 800;
                    fprintf(stdout, "\nBuilt House");
                }
                else{
                    fprintf(stdout, "\nNot enough Wood");
                }
            }
            if (nk_button_label(ctx, "Buy Horse"))
            {
                if(gold >= 200){
                    gold = gold - 200;
                    fprintf(stdout, "\nBought a Horse");
                }
                else{
                    fprintf(stdout, "\nNot enough Gold");
                }
            } */
            

        }
    nk_end(ctx);
}

void gui_main_menu()
{
    int INITIAL_GUI_X_POSITION = 0;
    int INITIAL_GUI_Y_POSITION = 0;
    int INITIAL_GUI_WIDTH = 960;
    int INITIAL_GUI_HEIGHT = 540;
    if (nk_begin(ctx, "Menu", nk_rect(INITIAL_GUI_X_POSITION, INITIAL_GUI_Y_POSITION, INITIAL_GUI_WIDTH, INITIAL_GUI_HEIGHT), NK_WINDOW_BORDER|NK_WINDOW_MOVABLE))
        {   
            //scale size to whole screen
            nk_window_set_size(ctx,"Menu", nk_vec2(get_width() , get_height()));

            //initially hides all gui when main menu is open
            nk_window_show(ctx, "Admin GUI", nk_false);
            nk_window_show(ctx, "Settings", nk_false);
            nk_window_show(ctx, "Build", nk_false);
            nk_window_show(ctx, "Resources", nk_false);

            nk_spacer(ctx);
            nk_layout_row_dynamic(ctx, 100, 1);

            nk_label_colored(ctx, "RTS Game Demo", NK_TEXT_ALIGN_CENTERED, nk_rgb(255, 165, 0));
            nk_label_colored(ctx, "Made Using Our Custom Blitz Engine!", NK_TEXT_ALIGN_CENTERED, nk_rgb(255, 165, 0));
            nk_label_colored(ctx, "By: Davis Teigeler, Evan Posharow, and Aaron Hartle", NK_TEXT_ALIGN_CENTERED, nk_rgb(255, 255, 255));
            if (nk_button_label(ctx, "Start demo"))
            {
                SetGameState(1);
                //shows all guis again
                nk_window_show(ctx, "Admin GUI", nk_true);
                nk_window_show(ctx, "Settings", nk_true);
                //nk_window_show(ctx, "Build", nk_true);
                nk_window_show(ctx, "Resources", nk_true);

                //change font ant then hides main menu
                nk_style_set_font(ctx, &basicFont->handle);
                nk_window_set_focus(ctx, "Resources");
                nk_window_show(ctx, "Menu", nk_false);
            }


        }
    nk_end(ctx);
}

void gui_resources()
{
    int INITIAL_GUI_X_POSITION = 360;
    int INITIAL_GUI_Y_POSITION = 0;
    int INITIAL_GUI_WIDTH = 240;
    int INITIAL_GUI_HEIGHT = 108;
    if (nk_begin(ctx, "Resources", nk_rect(INITIAL_GUI_X_POSITION, INITIAL_GUI_Y_POSITION, INITIAL_GUI_WIDTH, INITIAL_GUI_HEIGHT), NK_WINDOW_BORDER|NK_WINDOW_MOVABLE))
        {   
            int dynamicX = (get_width()/2) - 120;
            int dynamicY = 0;
            nk_window_set_position(ctx, "Resources", nk_vec2(dynamicX , dynamicY));

            nk_layout_row_dynamic(ctx, 20, 1);
            nk_label(ctx, "Resources:", NK_TEXT_ALIGN_CENTERED);

            nk_layout_row_dynamic(ctx, 20, 2);

            //Convert ints to strings
            int length1 = snprintf( NULL, 0, "%d", gold );
            int length2 = snprintf( NULL, 0, "%d", wood );
            char* str_gold[length1 + 1];
            char* str_wood[length2 + 1];
            snprintf( str_gold, length1 + 1, "%d", gold );
            snprintf( str_wood, length2 + 1, "%d", wood );

            nk_label_colored(ctx, "Gold", NK_TEXT_ALIGN_CENTERED, nk_rgb(240, 252, 3));
            nk_label_colored(ctx, "Wood", NK_TEXT_ALIGN_CENTERED, nk_rgb(0, 255, 0));
            nk_label(ctx, str_gold, NK_TEXT_ALIGN_CENTERED);
            nk_label(ctx, str_wood, NK_TEXT_ALIGN_CENTERED);
        }
    nk_end(ctx);
}

void gui_ShowMenu(bool tru)
{
    if (tru)
    {
        nk_window_show(ctx, "Build", nk_true);
        nk_window_set_focus(ctx, "Build");
    }
    else
    {
        nk_window_show(ctx, "Build", nk_false);
        nk_window_set_focus(ctx, "Resources");
    }
}

bool gui_CheckMouse()
{
    return nk_window_is_any_hovered(ctx);
}

get_height()
{
    glfwGetWindowSize(win, &width1, &height1);
    return height1;
}

get_width()
{
    glfwGetWindowSize(win, &width1, &height1);
    return width1;
}

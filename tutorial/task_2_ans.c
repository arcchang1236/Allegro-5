#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#define GAME_TERMINATE 3

ALLEGRO_DISPLAY* display = NULL;

ALLEGRO_FONT *font = NULL;
ALLEGRO_BITMAP *img = NULL;


const int width = 800;
const int height = 600;

const int img_width = 640;
const int img_height = 480;

void show_err_msg(int msg);
void game_init();
void game_begin();
void game_destroy();


int main(int argc, char *argv[]) {
    int msg = 0;

    game_init();
    game_begin();
    printf("Hello world!!!\n");
    al_rest(10);

    game_destroy();
    return 0;
}


void show_err_msg(int msg) {
    fprintf(stderr, "unexpected msg: %d", msg);
    game_destroy();
    exit(9);
}

void game_init() {
    if (!al_init()) {
        show_err_msg(-1);
    }

    display = al_create_display(width, height);
    if (display == NULL) {
        show_err_msg(-1);
    }

    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon

    font = al_load_ttf_font("pirulen.ttf",12,0); // load font


}

void game_begin() {
    al_clear_to_color(al_map_rgb(100,100,100));
    
    al_draw_text(font, al_map_rgb(255,255,255), img_width - 80, img_height + 20
            , ALLEGRO_ALIGN_CENTRE, "Why? ");
    al_draw_text(font, al_map_rgb(255,255,255), img_width - 80, img_height + 40
            , ALLEGRO_ALIGN_CENTRE, "Why am I the smartest professor in the world? ");
    
    al_draw_rectangle(img_width - 300, img_height + 10, width - 10, img_height + 70, al_map_rgb(255, 255, 255), 0);
    img = al_load_bitmap("htchen.jpg");
    if (img == NULL)
        show_err_msg(-1);
    al_draw_bitmap(img, 0, 0, 0);
    al_flip_display();
}
void game_destroy() {
    al_destroy_display(display);
}
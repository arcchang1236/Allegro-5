#include <stdio.h>
#include <allegro5/allegro.h>

ALLEGRO_DISPLAY* display = NULL;

const int width = 800;
const int height = 600;

void show_err_msg(int msg);
void game_init();
void game_begin();
void game_destroy();


int main(int argc, char *argv[]) {
    int msg = 0;

    printf("Hello world!!!\n");
    al_rest(5);

    game_init();
    game_begin();

    al_rest(5);
    printf("See you, world!!\n");

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
}

void game_begin() {
    al_clear_to_color(al_map_rgb(100,100,100));
    
    al_flip_display();
}
void game_destroy() {
    al_destroy_display(display);
}
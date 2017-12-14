#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>              //Our primitive header file

#define GAME_TERMINATE 666


ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_EVENT event;

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3


const int width = 800;
const int height = 600;

void show_err_msg(int msg);
void game_init();
void game_begin();
int process_event();
int game_run();
void game_destroy();

int pos_x, pos_y;

bool* keys;


int main(int argc, char *argv[]) {
    int msg = 0;

    game_init();
    game_begin();
    printf("Hello world!!!\n");

    while (msg != GAME_TERMINATE) {
        msg = game_run();
        if (msg == GAME_TERMINATE)
            printf("See you, world\n");
    }
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

    keys = (bool*) malloc(4 * sizeof(bool));
    memset(keys, false, 4 * sizeof(bool));

    pos_x = width / 2;
    pos_y = height / 2;

    display = al_create_display(width, height);
    event_queue = al_create_event_queue();

    if (display == NULL || event_queue == NULL) {
        show_err_msg(-1);
    }

    al_init_primitives_addon();
    al_install_keyboard();

    al_register_event_source(event_queue, al_get_keyboard_event_source());

}

void game_begin() {
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_filled_rectangle(pos_x, pos_y, pos_x + 30, pos_y + 30, al_map_rgb(255,0,255));
    al_flip_display();
}

int process_event() {
    al_wait_for_event(event_queue, &event);


    if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch(event.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
                keys[UP] = true;
                break;
            case ALLEGRO_KEY_DOWN:
                keys[DOWN] = true;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = true;
                break;
            case ALLEGRO_KEY_LEFT:
                keys[LEFT] = true;
                break;
        }
    }
    else if(event.type == ALLEGRO_EVENT_KEY_UP) {
        switch(event.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
                keys[UP] = false;
                break;
            case ALLEGRO_KEY_DOWN:
                keys[DOWN] = false;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = false;
                break;
            case ALLEGRO_KEY_LEFT:
                keys[LEFT] = false;
                break;
            case ALLEGRO_KEY_ESCAPE:
                return GAME_TERMINATE;
                break;
        }
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        return GAME_TERMINATE;
    }

    pos_y -= keys[UP] * 10;
    pos_y += keys[DOWN] * 10;
    pos_x -= keys[LEFT] * 10;
    pos_x += keys[RIGHT] * 10;

    al_draw_filled_rectangle(pos_x, pos_y, pos_x + 30, pos_y + 30, al_map_rgb(255,0,255));
    al_flip_display();
    al_clear_to_color(al_map_rgb(0,0,0));
    return 0;
}

int game_run() {
    int error = 0;
    if (!al_is_event_queue_empty(event_queue)) {
        error = process_event();
    }
    return error;
}

void game_destroy() {
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
}
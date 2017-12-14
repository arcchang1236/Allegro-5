#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define GAME_TERMINATE 3

ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_BITMAP *image = NULL;
ALLEGRO_SAMPLE *sample = NULL;

const int WIDTH = 1024;
const int HEIGHT = 768;

int pos_x_p1 = WIDTH / 2 - 100;
int pos_y_p1 = HEIGHT / 2 - 100;
int pos_x_p2 = WIDTH / 2 + 100;
int pos_y_p2 = HEIGHT / 2 + 100;
int imageWidth = 0;
int imageHeight = 0;

void show_err_msg(int msg);
void game_init();
void game_begin();
int process_event();
int game_run();
void game_destroy();


int main(int argc, char *argv[]) {
    int msg = 0;

    game_init();
    game_begin();

    while (msg != GAME_TERMINATE) {
        msg = game_run();
        if (msg == GAME_TERMINATE)
            printf("Game Over\n");
    }
    game_destroy();
    return 0;
}

void show_err_msg(int msg) {
    fprintf(stderr, "unexpected msg: %d\n", msg);
    game_destroy();
    exit(9);
}

void game_init() {
    if (!al_init()) {
        printf("failed to initialize allegro!\n");
        show_err_msg(-1);
    }
    if(!al_install_audio()){
        printf("failed to initialize audio!\n");
        show_err_msg(-1);
    }
    if(!al_init_acodec_addon()){
        printf("failed to initialize audio codecs!\n");
        show_err_msg(-1);
    }
    if (!al_reserve_samples(1)){
        printf("failed to reserve samples!\n");
        show_err_msg(-1);
    }
    sample = al_load_sample( "bubbs.wav" );
    if (!sample){
        printf( "Audio clip sample not loaded!\n" );
        show_err_msg(-1);
    }
    display = al_create_display(WIDTH, HEIGHT);
    event_queue = al_create_event_queue();

    if (display == NULL || event_queue == NULL) {
        show_err_msg(-1);
    }

    // Loop the sample until the display closes.
    al_play_sample(sample, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);

    al_init_primitives_addon();
    al_install_keyboard();
    al_install_audio();
    al_init_image_addon();
    al_init_acodec_addon();

    image = al_load_bitmap("teemo.jpg");

    imageWidth = al_get_bitmap_width(image);
    imageHeight = al_get_bitmap_height(image);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_reserve_samples(10);

}

void game_begin() {
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_flip_display();
}

//For Keyboard
int process_event(){
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);

    if(event.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        switch(event.keyboard.keycode)
        {
            //p1 control
            case ALLEGRO_KEY_UP:
                pos_y_p1 -= 10;
                break;
            case ALLEGRO_KEY_DOWN:
                pos_y_p1 += 10;
                break;
            case ALLEGRO_KEY_RIGHT:
                pos_x_p1 += 10;
                break;
            case ALLEGRO_KEY_LEFT:
                pos_x_p1 -= 10;
                break;

            //p2 control
            case ALLEGRO_KEY_W:
                pos_y_p2 -= 10;
                break;
            case ALLEGRO_KEY_S:
                pos_y_p2 += 10;
                break;
            case ALLEGRO_KEY_A:
                pos_x_p2 -= 10;
                break;
            case ALLEGRO_KEY_D:
                pos_x_p2 += 10;
                break;
        }
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        return GAME_TERMINATE;

    al_draw_filled_rectangle(pos_x_p1, pos_y_p1, pos_x_p1 + 30, pos_y_p1 + 30, al_map_rgb(255,0,255));
    al_draw_bitmap(image, pos_x_p2, pos_y_p2, 0);
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
    al_destroy_sample(sample);
    al_destroy_bitmap(image);
}

#include <stdio.h>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define GAME_TERMINATE 3

const float FPS = 60;

ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_BITMAP *image = NULL;
ALLEGRO_BITMAP *image2 = NULL;
ALLEGRO_BITMAP *image3 = NULL;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_KEYBOARD_STATE keyState ;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_TIMER *timer2 = NULL;
ALLEGRO_SAMPLE *song=NULL;

bool transfer ;

const int width = 800;
const int height = 600;

typedef struct character
{
    int x;
    int y;

}Character;

Character character1;
Character character2;

int imageWidth = 0;
int imageHeight = 0;
int draw = 0 ;
int done = 0 ;
int window = 1;
int judge_next_window = false;

void show_err_msg(int msg);
void game_init();
void game_begin();
int process_event();
int game_run();
void game_destroy();
bool ture_1 , ture_2 ;


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
        show_err_msg(-1);
    }
    if(!al_install_audio()){
        fprintf(stderr, "failed to initialize audio!\n");
        show_err_msg(-1);
    }
    if(!al_init_acodec_addon()){
        fprintf(stderr, "failed to initialize audio codecs!\n");
        show_err_msg(-1);
    }
    if (!al_reserve_samples(1)){
        fprintf(stderr, "failed to reserve samples!\n");
        show_err_msg(-1);
    }
    song = al_load_sample( "hello.wav" );
    if (!song){
        printf( "Audio clip sample not loaded!\n" );
        show_err_msg(-1);
    }

    display = al_create_display(width, height);
    event_queue = al_create_event_queue();

    if (display == NULL || event_queue == NULL) {
        show_err_msg(-1);
    }

    character1.x = width / 2 - 100;
    character1.y = height / 2 - 100;
    character2.x = width / 2 + 100;
    character2.y = height / 2 + 100;

    al_set_window_position( display, 0, 0);
    const char *title = "Final Project 10xxxxxxx";
    al_set_window_title( display, title);

    al_init_primitives_addon();
    al_install_keyboard();
    al_install_audio();
    al_init_image_addon();
    al_init_acodec_addon();

    image = al_load_bitmap("teemo.png");
    image2 = al_load_bitmap("maokai.png");
    image3 = al_load_bitmap("azir.png");

    background = al_load_bitmap("stage.jpg");


    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_reserve_samples(10);

}

void game_begin() {
    //Loop the song until the display closes
    al_play_sample(song, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_flip_display();

}

/* For Keyboard */
int process_event(){
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);


    if(event.timer.source == timer){
        ture_1 = !ture_1 ;

    }

    if(event.timer.source == timer2){
        ture_2 = !ture_2 ;
    }


    if(event.type == ALLEGRO_EVENT_KEY_UP)
    {
        switch(event.keyboard.keycode)
        {
            // p1 control
            case ALLEGRO_KEY_UP:
                character1.y -= 30;
                break;
            case ALLEGRO_KEY_DOWN:
                character1.y += 30;
                break;
            case ALLEGRO_KEY_RIGHT:
                character1.x += 30;
                break;
            case ALLEGRO_KEY_LEFT:
                character1.x -= 30;
                break;

             //p2 control
            case ALLEGRO_KEY_W:
                character2.y -= 30;
                break;
            case ALLEGRO_KEY_S:
                character2.y += 30;
                break;
            case ALLEGRO_KEY_A:
                character2.x -= 30;
                break;
            case ALLEGRO_KEY_D:
                character2.x += 30;
                break;

            case ALLEGRO_KEY_ENTER:
                judge_next_window = true;
                break;
        }

    }

    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        return GAME_TERMINATE;

    return 0;
}

int game_run() {
    int error = 0;
    if(window == 1){
        if (!al_is_event_queue_empty(event_queue)) {
            error = process_event();
            if(judge_next_window) {
                window = 2;
                //Initialize Timer
                timer  = al_create_timer(1.0);
                timer2  = al_create_timer(1.0/3.0);
                al_register_event_source(event_queue, al_get_timer_event_source(timer)) ;
                al_register_event_source(event_queue, al_get_timer_event_source(timer2)) ;
                al_start_timer(timer);
                al_start_timer(timer2);
            }
        }
    }
    else if(window == 2){
        al_draw_bitmap(background, 0,0, 0);
        if(ture_1)al_draw_bitmap(image2, character1.x, character1.y, 0);
        if(ture_2)al_draw_bitmap(image, character2.x, character2.y, 0);
        else al_draw_bitmap(image3, character2.x, character2.y, 0);

        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));
        if (!al_is_event_queue_empty(event_queue)) {
            error = process_event();
        }
    }
    return error;
}

void game_destroy() {
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_timer(timer2);
    al_destroy_bitmap(image);
    al_destroy_sample(song);
}

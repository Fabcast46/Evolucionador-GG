//se importan las libreria necesarias para que allegro funcione
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include "curl/curl.h"
#include "Gladiator.h"
#include "xCliente.h"
#include <iostream>

//se crean punteros para que la inteerfaz funcione
ALLEGRO_DISPLAY *display_Juego = NULL;
ALLEGRO_DISPLAY *display_Menu = NULL;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_BITMAP *background_menu = NULL;
ALLEGRO_BITMAP *attack = NULL;
ALLEGRO_BITMAP *kick = NULL;
ALLEGRO_BITMAP *charge = NULL;
ALLEGRO_BITMAP *play = NULL;
ALLEGRO_BITMAP *player_player = NULL;
ALLEGRO_BITMAP *player_bot = NULL;
ALLEGRO_BITMAP *bot_bot = NULL;
ALLEGRO_BITMAP *gladiator_player = NULL;
ALLEGRO_BITMAP *gladiator_enemy = NULL;
ALLEGRO_BITMAP *title = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer;
ALLEGRO_EVENT_QUEUE *event_queue_menu = NULL;
ALLEGRO_TIMER *timer_menu;

//variables globales
const int Ancho = 1136;
const int Alto = 640;
enum MYKEYS {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE};
bool key[5] = { false, false, false, false,false};
bool doexit = false;
bool redraw = true;
bool doexit_menu = false;
bool redraw_menu = true;
bool Kick = false;
bool Attack = false;
bool Charge = false;
bool authorize = false;
bool authorize_menu = false;
bool Play = false;
bool Player_Player = false;
bool Player_Bot = false;
bool Bot_Bot = false;
bool selected = false;
int posX = 284;
int posY = 285;
int posX_Enemy = 675;
int posY_Enemy = 285;
int counter = 3;

int parser(char* fuente, char* objetivo, int index){
    int j = 0;
    while(fuente[index] != '/'){
        objetivo[j] = fuente[index];
        index++;
        j++;
    }

    return index;
}

int main(int argc, char **argv){

    Gladiator* gladiator1 = new Gladiator();
    xCliente* client = new xCliente();


    if(!al_init()) {
        al_show_native_message_box(display_Juego, "Error", "Error", "Failed to initialize allegro!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }

    if(!al_init_image_addon()) {
        al_show_native_message_box(display_Juego, "Error", "Error", "Failed to initialize al_init_image_addon!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }

    //se crea el display
    display_Menu = al_create_display(800,450);

    if(!display_Menu) {
        al_show_native_message_box(display_Menu, "Error", "Error", "Failed to initialize display!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }

    //se cargan las imagenes correspondientes
    background_menu = al_load_bitmap("Fondo_Menu.jpg");
    play = al_load_bitmap("Play_Button.png");
    player_player = al_load_bitmap("Player_Player.png");
    player_bot = al_load_bitmap("Player_Bot.png");
    bot_bot = al_load_bitmap("Bot_Bot.png");
    title = al_load_bitmap("Title_Gladiator.png");

    if(!background_menu) {
        al_show_native_message_box(display_Menu, "Error", "Error", "Failed to load image!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display_Menu);
        return 0;
    }

    //Se inicializan las bibliotecas de allegro

    al_install_keyboard();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_install_mouse();

    event_queue_menu = al_create_event_queue();
    timer_menu = al_create_timer(1.0/60);
    al_register_event_source(event_queue_menu,al_get_timer_event_source(timer_menu));
    al_register_event_source(event_queue_menu,al_get_keyboard_event_source());
    al_start_timer(timer_menu); //Se inicia el timer

    while(!doexit_menu){
        ALLEGRO_EVENT ev_menu;
        al_wait_for_event(event_queue_menu, &ev_menu); //Espera a que se precione una tecla
        if(ev_menu.type == ALLEGRO_EVENT_TIMER) {

            if(key[KEY_UP]) {
                player_bot = al_load_bitmap("Player_Bot_Big.png");
                player_player = al_load_bitmap("Player_Player.png");
                bot_bot = al_load_bitmap("Bot_Bot.png");
                authorize_menu = true;
                Player_Bot = true;
                Player_Player = false;
                Bot_Bot = false;
            }

            if(key[KEY_DOWN]) {
                player_bot = al_load_bitmap("Player_Bot.png");
                player_player = al_load_bitmap("Player_Player.png");
                bot_bot = al_load_bitmap("Bot_Bot.png");
                authorize_menu = false;
                Player_Bot = false;
                Player_Player = false;
                Bot_Bot = false;
            }

            if(key[KEY_LEFT]) {
                if(authorize_menu == true){
                    player_player = al_load_bitmap("Player_Player_Big.png");
                    player_bot = al_load_bitmap("Player_Bot.png");
                    bot_bot = al_load_bitmap("Bot_Bot.png");
                    Player_Bot = false;
                    Player_Player = true;
                    Bot_Bot = false;
                }
            }

            if(key[KEY_RIGHT]) {
                if(authorize_menu == true){
                    player_player = al_load_bitmap("Player_Player.png");
                    player_bot = al_load_bitmap("Player_Bot.png");
                    bot_bot = al_load_bitmap("Bot_Bot_Big.png");
                    Player_Bot = false;
                    Player_Player = false;
                    Bot_Bot = true;
                }
            }

            if(key[KEY_SPACE]) {
                if(authorize_menu && selected == true){
                    doexit_menu = true;
                }

                else if(Player_Player == true){
                    player_player = al_load_bitmap("Player_Player_Select.png");
                    selected = true;
                }

                else if(Player_Bot == true){
                    player_bot = al_load_bitmap("Player_Bot_Select.png");
                    selected = true;
                }

                else if(Bot_Bot == true){
                    bot_bot = al_load_bitmap("Bot_Bot_Select.png");
                    selected = true;
                }
            }

            redraw_menu = true;
        }
        else if(ev_menu.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        //Aqui se registra si la tecla es precionada
        else if(ev_menu.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(ev_menu.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                key[KEY_UP] = true;
                break;

                case ALLEGRO_KEY_DOWN:
                key[KEY_DOWN] = true;
                break;

                case ALLEGRO_KEY_LEFT:
                key[KEY_LEFT] = true;
                break;

                case ALLEGRO_KEY_RIGHT:
                key[KEY_RIGHT] = true;
                break;

                case ALLEGRO_KEY_SPACE:
                key[KEY_SPACE]=true;
                break;
            }
        }
        //Aqui se registra si se deja de precionar la tecla
        else if(ev_menu.type == ALLEGRO_EVENT_KEY_UP) {
            switch(ev_menu.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                key[KEY_UP] = false;
                break;

                case ALLEGRO_KEY_DOWN:
                key[KEY_DOWN] = false;
                break;

                case ALLEGRO_KEY_LEFT:
                key[KEY_LEFT] = false;
                break;

                case ALLEGRO_KEY_RIGHT:
                key[KEY_RIGHT] = false;
                break;

                case ALLEGRO_KEY_ESCAPE:
                doexit_menu = true;
                break;

                case ALLEGRO_KEY_SPACE:
                key[KEY_SPACE] = false;
                break;
            }
        }
        //Aqui se actualiza todo el juego, printiando todo en su nuevo lugar
        if(redraw_menu && al_is_event_queue_empty(event_queue_menu)) {
            redraw_menu = false;
            al_draw_bitmap(background_menu,0,0,0);
            al_draw_bitmap(title,0,80,0);
            al_draw_bitmap(al_load_bitmap("Title_Front.png"),0,0,0);
            al_draw_bitmap(player_player,290,300,0);
            al_draw_bitmap(player_bot,480,300,0);
            al_draw_bitmap(bot_bot,670,300,0);
            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
        }
    }

    al_rest(2);
    al_destroy_display(display_Menu);
    al_destroy_bitmap(background_menu);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    display_Juego = al_create_display(Ancho,Alto);
    background = al_load_bitmap("fondo_coliseo.png");
    attack = al_load_bitmap("Attack_Circle.png");
    kick = al_load_bitmap("Kick_Circle.png");
    charge = al_load_bitmap("Charge_Circle.png");
    gladiator_player = al_load_bitmap("Gladiator_Player.png");
    gladiator_enemy = al_load_bitmap("Gladiator_Enemy.png");

    //Se crea el evento y el timer para poder obtener las teclas y llevar tiempo de ejecucion

    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0/60);
    al_register_event_source(event_queue,al_get_timer_event_source(timer));
    al_register_event_source(event_queue,al_get_keyboard_event_source());
    al_start_timer(timer); //Se inicia el timer

    while(!doexit){
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev); //Espera a que se precione una tecla
        if(ev.type == ALLEGRO_EVENT_TIMER) {

            if(key[KEY_UP]) {
                kick = al_load_bitmap("Kick_Circle_Big.png");
                attack = al_load_bitmap("Attack_Circle.png");
                charge = al_load_bitmap("Charge_Circle.png");
                Kick = true;
                Attack = false;
                Charge = false;
                authorize = true;
            }

            if(key[KEY_DOWN]) {
                kick = al_load_bitmap("Kick_Circle.png");
                attack = al_load_bitmap("Attack_Circle.png");
                charge = al_load_bitmap("Charge_Circle.png");
                Kick = false;
                authorize = false;
                Attack = false;
                Charge = false;
            }

            if(key[KEY_LEFT]) {
                if(authorize == true){
                    kick = al_load_bitmap("Kick_Circle.png");
                    attack = al_load_bitmap("Attack_Circle_Big.png");
                    charge = al_load_bitmap("Charge_Circle.png");
                    Attack = true;
                    Kick = false;
                    Charge = false;
                }
            }

            if(key[KEY_RIGHT]) {
                if(authorize == true){
                    kick = al_load_bitmap("Kick_Circle.png");
                    attack = al_load_bitmap("Attack_Circle.png");
                    charge = al_load_bitmap("Charge_Circle_Big.png");
                    Charge = true;
                    Attack = false;
                    Kick = false;
                }
            }

            if(key[KEY_SPACE]) {
                if(authorize == true){
                    if(Attack == true){
                        gladiator_player = al_load_bitmap("Gladiator_Player_Attack.png");
                        gladiator_enemy = al_load_bitmap("Gladiator_Enemy_Decapitated.png");
                        posY_Enemy = 295;
                        posX = 284;
                    }

                    else if(Kick == true){
                        gladiator_player = al_load_bitmap("Gladiator_Player_Kick.png");
                        gladiator_enemy = al_load_bitmap("Gladiator_Enemy_Dead.png");
                        posX = 284;
                        posY_Enemy = 285;
                    }

                    else if(Charge == true){
                        gladiator_player = al_load_bitmap("Gladiator_Player_Charge.png");
                        gladiator_enemy = al_load_bitmap("Gladiator_Enemy_Dead.png");
                        posX += 10;
                        posY_Enemy = 285;
                    }
                }
            }

            redraw = true;
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        //Aqui se registra si la tecla es precionada
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                key[KEY_UP] = true;
                break;

                case ALLEGRO_KEY_DOWN:
                key[KEY_DOWN] = true;
                break;

                case ALLEGRO_KEY_LEFT:
                key[KEY_LEFT] = true;
                break;

                case ALLEGRO_KEY_RIGHT:
                key[KEY_RIGHT] = true;
                break;

                case ALLEGRO_KEY_SPACE:
                key[KEY_SPACE]=true;
                break;
            }
        }
        //Aqui se registra si se deja de precionar la tecla
        else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                key[KEY_UP] = false;
                break;

                case ALLEGRO_KEY_DOWN:
                key[KEY_DOWN] = false;
                break;

                case ALLEGRO_KEY_LEFT:
                key[KEY_LEFT] = false;
                break;

                case ALLEGRO_KEY_RIGHT:
                key[KEY_RIGHT] = false;
                break;

                case ALLEGRO_KEY_ESCAPE:
                doexit = true;
                break;

                case ALLEGRO_KEY_SPACE:
                key[KEY_SPACE] = false;
                break;
            }
        }
        //Aqui se actualiza todo el juego, printiando todo en su nuevo lugar
        if(redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            al_draw_bitmap(background,0,0,0);
            al_draw_bitmap(al_load_bitmap("Genetic_Gladiator.png"),450,500,0);
            al_draw_bitmap(attack,250,80,0);
            al_draw_bitmap(kick,530,80,0);
            al_draw_bitmap(charge,810,80,0);
            al_draw_bitmap(gladiator_player,posX,posY,0);
            al_draw_bitmap(gladiator_enemy,posX_Enemy, posY_Enemy,0);
            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
        }
    }

    al_rest(2);
    al_destroy_display(display_Juego);
    al_destroy_bitmap(background);

    return 0;
}

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
#include <string>
#include <sstream>
#include <string.h>
#include <cmath>
#include <list>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

///Pointers are created///

//Menu pointers

ALLEGRO_DISPLAY *display_Menu = NULL;
ALLEGRO_BITMAP *background_menu = NULL;
ALLEGRO_BITMAP *play = NULL;
ALLEGRO_BITMAP *player_player = NULL;
ALLEGRO_BITMAP *player_bot = NULL;
ALLEGRO_BITMAP *bot_bot = NULL;
ALLEGRO_BITMAP *title = NULL;
ALLEGRO_EVENT_QUEUE *event_queue_menu = NULL;
ALLEGRO_TIMER *timer_menu;

//Maze pointers

ALLEGRO_DISPLAY *display_Maze = NULL;
ALLEGRO_BITMAP *road = NULL;
ALLEGRO_BITMAP *tower = NULL;
ALLEGRO_BITMAP *coliseum = NULL;
ALLEGRO_EVENT_QUEUE *event_queue_maze = NULL;
ALLEGRO_TIMER *timer_maze;

//Game pointers

ALLEGRO_DISPLAY *display_Juego = NULL;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_BITMAP *attack = NULL;
ALLEGRO_BITMAP *kick = NULL;
ALLEGRO_BITMAP *charge = NULL;
ALLEGRO_BITMAP *gladiator_player = NULL;
ALLEGRO_BITMAP *gladiator_enemy = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer;

///Global variables///

enum MYKEYS {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE};
bool key[5] = {false, false, false, false,false};
int victories_Team1 = 0;
int victories_Team2 = 0;
int Generations = 0;
string mutation_Probability = "1.2";
char fitness_player1[10] = "";
char fitness_population1[10] = "";
char mutation_population1[10] = "";
char fitness_player2[10] = "";
char fitness_population2[10] = "";
char mutation_population2[10] = "";


//Menu variables

const int Width_Menu = 800;
const int Height_Menu = 450;
bool doexit_menu = false;
bool redraw_menu = true;
bool Play = false;
bool Player_Player = false;
bool Player_Bot = false;
bool Bot_Bot = false;
bool selected = false;
bool authorize_menu = false;
int mode_game;

//Maze variables

const int Width_Maze = 1020;
const int Height_Maze = 710;
bool doexit_maze = false;
bool redraw_maze = true;
bool goal_player1 = false;
bool goal_player2 = false;
int change = 3;
int row;
int colum;

//Game variables

const int Width = 1136;
const int Height = 640;
bool doexit = false;
bool redraw = true;
bool Kick = false;
bool Attack = false;
bool Charge = false;
bool authorize = false;
bool flag_for_change = false;
bool player_round = false;
bool allow_attack1 = true;
bool allow_kick1 = true;
bool allow_charge1 = true;
bool allow_attack2 = true;
bool allow_kick2 = true;
bool allow_charge2 = true;
int posX = 284;
int posY = 285;
int posX_Enemy = 675;
int posY_Enemy = 285;
int life_player1;
int life_player2;

///Created for communication///

static size_t WriteCallBack(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int parser(const char* fuente, char* objetivo, int index)
{
    int j = 0;
    while(fuente[index] != '/')
    {
        objetivo[j] = fuente[index];
        index++;
        j++;
    }

    return index;
}

void setCharacteristics(Gladiator* gladiator, Gladiator* gladiator2,  const char* font)
{
    int i = 0;
    char data[10] = "";

    i = parser(font, data, i);
    i++;
    gladiator->setHandDam(atoi(data));
    memset(data, 0, 10);

    i = parser(font, data,i);
    i++;
    gladiator->setFootDam(atoi(data));
    memset(data, 0, 10);

    i = parser(font, data,i);
    i++;
    gladiator->setBodyDam(atoi(data));
    memset(data, 0, 10);

    i = parser(font, data,i);
    i++;
    gladiator->setHandDef(atoi(data));
    memset(data, 0, 10);

    i = parser(font, data,i);
    i++;
    gladiator->setFootDef(atoi(data));
    memset(data, 0, 10);

    i = parser(font, data,i);
    i++;
    gladiator->setBodyDef(atoi(data));
    memset(data, 0, 10);

    i = parser(font, data,i);
    i++;
    gladiator->setTotalDef(atoi(data));
    memset(data, 0, 10);

    i = parser(font, data,i);
    i++;
    for(int k = 0; k < 10; k++)
    {
        fitness_player1[k] = data[k];
    }
    memset(data, 0, 10);
    //cout<<fitness_player1 <<endl;
    //*fitness1 = *data;

    i = parser(font, data,i);
    i++;
    for(int k = 0; k < 10; k++)
    {
        fitness_population1[k] = data[k];
    }
    memset(data, 0, 10);
    //*fitnessT1 = *data;

    i = parser(font, data,i);
    i++;
    for(int k = 0; k < 10; k++)
    {
        mutation_population1[k] = data[k];
    }
    memset(data, 0, 10);

    i = parser(font, data,i);
    i++;
    gladiator2->setHandDam(atoi(data));
    memset(data, 0, 10);

    i = parser(font, data,i);
    i++;
    gladiator2->setFootDam(atoi(data));
    memset(data, 0, 10);

    i = parser(font, data,i);
    i++;
    gladiator2->setBodyDam(atoi(data));
    memset(data, 0, 10);

    i = parser(font, data,i);
    i++;
    gladiator2->setHandDef(atoi(data));
    memset(data, 0, 10);

    i = parser(font, data,i);
    i++;
    gladiator2->setFootDef(atoi(data));
    memset(data, 0, 10);

    i = parser(font, data,i);
    i++;
    gladiator2->setBodyDef(atoi(data));
    memset(data, 0, 10);

    i = parser(font, data,i);
    i++;
    gladiator2->setTotalDef(atoi(data));
    memset(data, 0, 10);

    i = parser(font, data,i);
    i++;
    for(int k = 0; k < 10; k++)
    {
        fitness_player2[k] = data[k];
    }
    memset(data, 0, 10);
    //*fitness2 = *data;

    i = parser(font, data,i);
    i++;
    for(int k = 0; k < 10; k++)
    {
        fitness_population2[k] = data[k];
    }
    memset(data, 0, 10);
    //*fitnessT2 = *data;

    i = parser(font, data,i);
    i++;
    for(int k = 0; k < 10; k++)
    {
        mutation_population2[k] = data[k];
    }
    memset(data, 0, 10);
//    return gladiator;
}

///Artificil Intelligence///

void artificial_attack(Gladiator* bot)
{

}

///Creation of the Maze///

class Vector2
{
    int x, y;
public:
    Vector2(int _x, int _y) : x(_x), y(_y) {}
    Vector2() = default;
    Vector2 operator +(const Vector2& other)
    {
        Vector2 temp;
        temp.x = this->x + other.x;
        temp.y = this->y + other.y;
        return temp;
    }
    int getX() const
    {
        return x;
    }
    int getY() const
    {
        return y;
    }

    friend class Map;
};

struct Node
{
    Vector2 position;
    int G, H, F;
    Node* parent = nullptr;

    Node() = default;
    Node(const Node& other) = default;
    Node(Vector2 pos):position(pos) {};

    void calc(const Vector2& endPos, Vector2& Current)
    {
        H = static_cast<int>((abs(static_cast<double>(position.getX() - endPos.getX())) + abs(static_cast<double>(position.getY() - endPos.getY()))));

        int temp = abs(static_cast<double>(position.getX() - Current.getX()))+abs(static_cast<double>(position.getY() - Current.getY()));


        if(temp == 2)
        {
            G = parent ? parent->G + 1 : 10000;

        }
        if(abs(static_cast<double>(position.getX() - Current.getX()))+abs(static_cast<double>(position.getY() - Current.getY())) == 1)
        {
            G = parent ? parent->G + 1 : 1;
        }


        F = G + H;
    }

    bool operator==(const Node& other) const
    {
        return (position.getX() == other.position.getX() && position.getY() == other.position.getY());
    }
    bool operator!=(const Node& other) const
    {
        return !(*this == other);
    }
    bool operator<(const Node& other)  const
    {
        return(F < other.F);
    }
};

class Map
{
    std::vector<char> data;
    int size;

public:
    int poblacion;
    int numerotorres = 0;
    int torres[1000];
    Map() = default;
    Map(int _size, int numpoblacion) : size(_size),poblacion(numpoblacion)
    {
        data.resize(size * size);
        for (int i = 0; i < size * size; ++i) data[i] = '.';
    }
    void display()
    {
        for (int i = 1; i <= size * size; ++i)
        {
            std::cout << data[i - 1] << " ";

            if (!(i % size)) std::cout << "\n";
        }
    }
    bool getIfInDanger(Vector2 position) const
    {
        if (position.y < 0) position.y = 0;
        if (position.x < 0) position.x = 0;
        if (position.y >= 20) position.y = size - 1;
        if (position.x >= 20) position.x = size - 1;
        return(data[position.getX() + (position.getY() * size)] == 'X');
    }
    void setElement(char&& value, Vector2 position)
    {
        data[position.getX() + (position.getY() * size)] = value;
    }
    bool getElement(char&& value, Vector2 position)
    {

        if (  data[position.getX() + (position.getY() * size)]=='X')
        {
            return true;
        }
        else
        {
            return false;
        }
    }


    void setTower(int towers)
    {
        numerotorres =0;
        int posx, posy;
        int compare;
        int flag;
        for (int n=0; n<towers; n++)
        {
            compare = 0;
            flag = 0;
            posx = rand()%10;
            posy = rand()%10;
            if(poblacion == 1)
            {
                while(posy > 4)
                {
                    posy = rand()%10;
                }
            }
            if(poblacion == 2)
            {
                while(posy <= 6)
                {
                    posy = rand()%10;
                }
            }

            //std::cout<< posy<<std::endl;
            //std::cout<< posx;

            if (posx == 5 && posy  == 0)
            {
                n--;
                setElement('.',Vector2(posx, posy));
                numerotorres--;
            }
            else if (posx == 5 && posy  == 9)
            {
                n--;
                setElement('.',Vector2(posx, posy));
                numerotorres--;
            }
            else if (posx == 5 && posy  == 5)
            {
                n--;
                setElement('.',Vector2(posx, posy));
                numerotorres--;
            }
            else  if (getElement('.',Vector2(posx, posy)))
            {
                n--;

                numerotorres--;
            }
            else
            {
                setElement('X',Vector2(posx, posy));
                torres[numerotorres]= posx*10 + posy;
                numerotorres++;
            }



        }
    }

};

class Solver
{
    Vector2 startPos, endPos;
    std::vector<Vector2> directions;
    //Map map;
public:
    Map map;
    int n;
    int respuesta[1000];
    int towers;
    int pob;
    Solver(Vector2 _startPos, Vector2 _endPos, int size, int towers, int pob) : startPos(_startPos), endPos(_endPos), towers(towers), pob(pob)
    {
        Map temp(size, pob);

        map = temp;
        map.setTower(towers);

        directions.resize(8);
        directions[0] = Vector2(-1, 0);
        directions[1] = Vector2(-1, 0);
        directions[2] = Vector2(0, -1);
        directions[3] = Vector2(0, -1);
        directions[4] = Vector2(0, 1);
        directions[5] = Vector2(0, 1);
        directions[6] = Vector2(1, 0);
        directions[7] = Vector2(1, 0);
    }
    bool aStar(int towers)
    {
        Node startNode(startPos);
        Node goalNode(Vector2(endPos.getX(), endPos.getY()));

        if (map.getIfInDanger(startNode.position) || map.getIfInDanger(goalNode.position))
        {
            std::cout << "Either the start of this map is obstructed or so is the end.";
            return false;
        }

        std::list<Node> openList;
        std::list<Node> closedList;

        openList.push_back(startNode);

        while (!openList.empty())
        {
            auto current = Node(*std::min_element(openList.begin(), openList.end()));

            current.calc(endPos, current.position);

            closedList.push_back(current);
            openList.remove(current);
            srand(time(NULL));
            if (current == goalNode) break;

            for (auto& direction : directions)
            {

                Node successor(direction + current.position);

                if (map.getIfInDanger(successor.position) || successor.position.getX() > 20 - 1 ||
                        successor.position.getY() > 20 - 1 || successor.position.getX() < 0 ||
                        successor.position.getY() < 0 ||
                        std::find(closedList.begin(), closedList.end(), successor) != closedList.end())
                {
                    continue;
                }

                successor.calc(endPos, current.position);

                auto inOpen = std::find(openList.begin(), openList.end(), successor);
                if (inOpen == openList.end())
                {
                    successor.parent = &closedList.back();
                    successor.calc(endPos, current.position);

                    openList.push_back(successor);
                }
                else if (successor.G < inOpen->G) successor.parent = &closedList.back();
            }
        }

        if (!openList.size())
        {
            std::cout << "No path has been found\n";
            return false;
        }

        n = 0;
        //int respuesta[1000];

        auto inClosed = std::find(closedList.begin(), closedList.end(), goalNode);
        if (inClosed != closedList.end())
        {
            while (*inClosed != startNode)
            {
                map.setElement('Y',inClosed->position);
                *inClosed = *inClosed->parent;

                respuesta[n] = 10*inClosed->position.getX()+inClosed->position.getY();
                n++;


            }
        }

        //for (int asd = map.numerotorres-1; asd >= 0; asd--) std::cout<<map.torres[asd]<<std::endl;
        //map.display();
        //for (int w = n-1; w >= 0; w--) std::cout<<respuesta[w]<<std::endl;
        return true;
    }
    void Show()
    {
        map.display();
        std::cout<<"//////////"<<std::endl;
    }
};

///Main begins///

int main(int argc, char **argv)
{

    Gladiator* gladiator1 = new Gladiator();
    Gladiator* gladiator2 = new Gladiator();
    xCliente* client = new xCliente();
    std::string readBuffer;

    /*CURL *curl = curl_easy_init();
    if(curl)
    {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.100.3:8080/EvolucionadorGenetico/api/evolucionador/generacion");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }*/
    //const char* msj = readBuffer.c_str();
    const char* msj = "24/25/26/14/15/16/50/1.04/0.24/4/24/25/26/14/15/16/50/1.04/0.24/4/";
    setCharacteristics(gladiator1, gladiator2, msj);
    cout<< gladiator1->getBodyDam()<< "/" <<gladiator1->getBodyDef()<< "/" << gladiator1->getFootDam()<< "/" << gladiator1->getFootDef()<< "/" <<gladiator1->getHandDam()<<
        "/" <<gladiator1->getHandDef()<< "/" <<gladiator1->getTotalDef()<< endl;
    cout<< gladiator2->getBodyDam()<< "/" <<gladiator2->getBodyDef()<< "/" <<gladiator2->getFootDam()<< "/" <<gladiator2->getFootDef()<< "/" <<gladiator2->getHandDam()<<
        "/" <<gladiator2->getHandDef()<< "/" <<gladiator2->getTotalDef()<< endl;
    cout<<msj<<endl;

    if(!al_init())
    {
        al_show_native_message_box(display_Juego, "Error", "Error", "Failed to initialize allegro!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }

    if(!al_init_image_addon())
    {
        al_show_native_message_box(display_Juego, "Error", "Error", "Failed to initialize al_init_image_addon!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }

    //Libraries are inicialized

    al_install_keyboard();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_install_mouse();

    /*ALLEGRO_FONT *font = al_load_ttf_font("comic.ttf",34,0 );
    ALLEGRO_FONT *font2 = al_load_ttf_font("perigord.ttf",40,0 );

    if (!font){
      fprintf(stderr, "Could not load 'arial.ttf'.\n");
      return -1;
    }*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///MENU SETTIGNS///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    background_menu = al_load_bitmap("Fondo_Menu.jpg");
    play = al_load_bitmap("Play_Button.png");
    player_player = al_load_bitmap("Player_Player.png");
    player_bot = al_load_bitmap("Player_Bot.png");
    bot_bot = al_load_bitmap("Bot_Bot.png");
    title = al_load_bitmap("Title_Gladiator.png");

    //All for menu begins to work

    display_Menu = al_create_display(Width_Menu,Height_Menu);
    event_queue_menu = al_create_event_queue();
    timer_menu = al_create_timer(1.0/60);
    al_register_event_source(event_queue_menu,al_get_timer_event_source(timer_menu));
    al_register_event_source(event_queue_menu,al_get_keyboard_event_source());
    al_start_timer(timer_menu); //Timer begins

    while(!doexit_menu)
    {
        ALLEGRO_EVENT ev_menu;
        al_wait_for_event(event_queue_menu, &ev_menu); //Wait for keyboard to be pressed
        if(ev_menu.type == ALLEGRO_EVENT_TIMER)
        {

            if(key[KEY_UP])
            {
                player_bot = al_load_bitmap("Player_Bot_Big.png");
                player_player = al_load_bitmap("Player_Player.png");
                bot_bot = al_load_bitmap("Bot_Bot.png");
                authorize_menu = true;
                Player_Bot = true;
                Player_Player = false;
                Bot_Bot = false;
            }

            if(key[KEY_DOWN])
            {
                player_bot = al_load_bitmap("Player_Bot.png");
                player_player = al_load_bitmap("Player_Player.png");
                bot_bot = al_load_bitmap("Bot_Bot.png");
                authorize_menu = false;
                Player_Bot = false;
                Player_Player = false;
                Bot_Bot = false;
            }

            if(key[KEY_LEFT])
            {
                if(authorize_menu == true)
                {
                    player_player = al_load_bitmap("Player_Player_Big.png");
                    player_bot = al_load_bitmap("Player_Bot.png");
                    bot_bot = al_load_bitmap("Bot_Bot.png");
                    Player_Bot = false;
                    Player_Player = true;
                    Bot_Bot = false;
                }
            }

            if(key[KEY_RIGHT])
            {
                if(authorize_menu == true)
                {
                    player_player = al_load_bitmap("Player_Player.png");
                    player_bot = al_load_bitmap("Player_Bot.png");
                    bot_bot = al_load_bitmap("Bot_Bot_Big.png");
                    Player_Bot = false;
                    Player_Player = false;
                    Bot_Bot = true;
                }
            }

            if(key[KEY_SPACE])
            {
                if(authorize_menu && selected == true)
                {
                    doexit_menu = true;
                }

                else if(Player_Player == true)
                {
                    player_player = al_load_bitmap("Player_Player_Select.png");
                    selected = true;
                    mode_game = 0;
                }

                else if(Player_Bot == true)
                {
                    player_bot = al_load_bitmap("Player_Bot_Select.png");
                    selected = true;
                    mode_game = 1;
                }

                else if(Bot_Bot == true)
                {
                    bot_bot = al_load_bitmap("Bot_Bot_Select.png");
                    selected = true;
                    mode_game = 2;
                }
            }

            redraw_menu = true;
        }
        else if(ev_menu.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }

        //Key is pressed

        else if(ev_menu.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(ev_menu.keyboard.keycode)
            {
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

        //Key is relesed

        else if(ev_menu.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch(ev_menu.keyboard.keycode)
            {
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

        //The menu is actualized

        if(redraw_menu && al_is_event_queue_empty(event_queue_menu))
        {
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

    al_rest(1);
    al_destroy_display(display_Menu);
    al_destroy_bitmap(background_menu);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///General While for the game///

    while(true)
    {
        doexit = false;
        doexit_maze = false;
        Kick = false;
        Attack = false;
        Charge = false;
        authorize = false;
        player_round = false;
        allow_attack1 = true;
        allow_kick1 = true;
        allow_charge1 = true;
        allow_attack2 = true;
        allow_kick2 = true;
        allow_charge2 = true;
        goal_player1 = false;
        goal_player2 = false;

        if(flag_for_change == true)
        {
            /*std::string readBuffer;

            CURL *curl = curl_easy_init();
            if(curl)
            {
                CURLcode res;
                curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.100.3:8080/EvolucionadorGenetico/api/evolucionador/generacion");
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
                res = curl_easy_perform(curl);
                curl_easy_cleanup(curl);
            }*/
            //const char* msj = readBuffer.c_str();
            const char* msj = "24/25/26/14/15/16/50/1.04/0.24/4/24/25/26/14/15/16/50/1.04/0.24/4/";
            setCharacteristics(gladiator1, gladiator2, msj);
            Generations += 1;
            change += 3;
        }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///MAZE SETTIGNS///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        display_Maze = al_create_display(Width_Maze, Height_Maze);
        road = al_load_bitmap("road.png");
        tower = al_load_bitmap("tower_road.png");
        coliseum = al_load_bitmap("coliseum.png");
        row = 0;
        colum = 0;
        int torres= 0;
        srand(time(NULL));

        Solver* solucionador = new Solver(Vector2(5,0),Vector2(5,5), 10, change, 1);
        Solver* solucionador2 = new Solver(Vector2 (5,9),Vector2 (5,5), 10, change, 2);
        solucionador->aStar(change);
        solucionador2->aStar(change);
        /*for (int asd = torres; asd < 20; asd+=3){
            Solver solve(Vector2(5,0),Vector2(5,5), 10,torres, 1);
            Solver solve2(Vector2 (5,9),Vector2 (5,5), 10, torres, 2);
            if(solve.aStar(torres)){
                solve.aStar(torres);
                solve.Show();

            }
            if(solve2.aStar(torres)){
                solve2.aStar(torres);
                solve2.Show();

            }
            else{
                cambio = 0;
                asd = asd-3;

            }
            std::cout<<torres<<std::endl;
            torres+=cambio;

        }*/

        //All for menu begins to work

        event_queue_maze = al_create_event_queue();
        timer_maze = al_create_timer(1.0/60);
        al_register_event_source(event_queue_maze,al_get_timer_event_source(timer_maze));
        al_register_event_source(event_queue_maze,al_get_keyboard_event_source());
        al_start_timer(timer_maze); //Timer begins

        while(!doexit_maze)
        {
            ALLEGRO_EVENT ev_maze;
            al_wait_for_event(event_queue_maze, &ev_maze); //Wait for keyboard to be pressed
            if(ev_maze.type == ALLEGRO_EVENT_TIMER)
            {

                if(key[KEY_UP])
                {
                }

                if(key[KEY_DOWN])
                {
                    doexit_maze = true;
                }

                if(key[KEY_LEFT])
                {
                }

                if(key[KEY_RIGHT])
                {
                }

                if(key[KEY_SPACE])
                {
                }

                redraw_maze = true;
            }
            else if(ev_maze.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                break;
            }

            //Key is pressed

            else if(ev_maze.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                switch(ev_maze.keyboard.keycode)
                {
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

            //Key is relesed

            else if(ev_maze.type == ALLEGRO_EVENT_KEY_UP)
            {
                switch(ev_maze.keyboard.keycode)
                {
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
                    doexit_maze = true;
                    break;

                case ALLEGRO_KEY_SPACE:
                    key[KEY_SPACE] = false;
                    break;
                }
            }

            //The menu is actualized

            if(redraw_maze && al_is_event_queue_empty(event_queue_maze))
            {
                redraw_maze = false;
                for(int position = 0; position <= 10; position++)
                {
                    if(position <= 9)
                    {
                        al_draw_bitmap(road, colum * 102, row * 71,0);
                        colum++;
                    }

                    else if(position = 10)
                    {
                        row++;
                        colum = 0;
                    }
                }

                solucionador->map.numerotorres;
                solucionador2->map.numerotorres;

                for(int index = change - 1; index >= 0; index--){
                    int fila_matriz = solucionador->map.torres[index] / 10;
                    int columna_matriz = solucionador->map.torres[index] % 10;
                    al_draw_bitmap(tower, fila_matriz * 102, columna_matriz * 71,0);
                    cout<<solucionador->map.torres[index]<<endl;
                }

                for(int index = change - 1; index >= 0; index--){
                    int fila_matriz = solucionador2->map.torres[index] / 10;
                    int columna_matriz = solucionador2->map.torres[index] % 10;
                    al_draw_bitmap(tower, fila_matriz * 102, columna_matriz * 71,0);
                }
                //solucionador->Show();
                solucionador2->Show();
                cout<<change<<endl;
                al_flip_display();
            }
        }

        al_rest(1);
        al_destroy_display(display_Maze);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///GAME SETTIGNS///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        ALLEGRO_FONT *font = al_load_ttf_font("comic.ttf",34,0 );
        ALLEGRO_FONT *font2 = al_load_ttf_font("perigord.ttf",40,0 );
        display_Juego = al_create_display(Width,Height);
        background = al_load_bitmap("fondo_coliseo.png");
        attack = al_load_bitmap("Attack_Circle.png");
        kick = al_load_bitmap("Kick_Circle.png");
        charge = al_load_bitmap("Charge_Circle.png");
        gladiator_player = al_load_bitmap("Gladiator_Player.png");
        gladiator_enemy = al_load_bitmap("Gladiator_Enemy.png");

        //All for menu begins to work

        event_queue = al_create_event_queue();
        timer = al_create_timer(1.0/60);
        al_register_event_source(event_queue,al_get_timer_event_source(timer));
        al_register_event_source(event_queue,al_get_keyboard_event_source());
        al_start_timer(timer); //Timer begins

        life_player1 = gladiator1->getTotalDef();
        life_player2 = gladiator2->getTotalDef();

        while(!doexit)
        {

            /*cout<< "equipo 1: "   << victories_Team1 << endl;
            cout<< "equipo 2: "   << victories_Team2 << endl;
            cout<< "Generaciones: "   << Generations << endl;*/

            if(mode_game == 0)
            {
                //PvsP logic
                ALLEGRO_EVENT ev;
                al_wait_for_event(event_queue, &ev); //Wait for keyboard to be pressed
                if(ev.type == ALLEGRO_EVENT_TIMER)
                {

                    if(key[KEY_UP])
                    {
                        kick = al_load_bitmap("Kick_Circle_Big.png");
                        attack = al_load_bitmap("Attack_Circle.png");
                        charge = al_load_bitmap("Charge_Circle.png");
                        Kick = true;
                        Attack = false;
                        Charge = false;
                        authorize = true;
                    }

                    if(key[KEY_DOWN])
                    {
                        kick = al_load_bitmap("Kick_Circle.png");
                        attack = al_load_bitmap("Attack_Circle.png");
                        charge = al_load_bitmap("Charge_Circle.png");
                        Kick = false;
                        authorize = false;
                        Attack = false;
                        Charge = false;
                    }

                    if(key[KEY_LEFT])
                    {
                        if(authorize == true)
                        {
                            kick = al_load_bitmap("Kick_Circle.png");
                            attack = al_load_bitmap("Attack_Circle_Big.png");
                            charge = al_load_bitmap("Charge_Circle.png");
                            Attack = true;
                            Kick = false;
                            Charge = false;
                        }
                    }

                    if(key[KEY_RIGHT])
                    {
                        if(authorize == true)
                        {
                            kick = al_load_bitmap("Kick_Circle.png");
                            attack = al_load_bitmap("Attack_Circle.png");
                            charge = al_load_bitmap("Charge_Circle_Big.png");
                            Charge = true;
                            Attack = false;
                            Kick = false;
                        }
                    }

                    if(key[KEY_SPACE])
                    {
                        if(authorize == true)
                        {
                            if(Attack == true)
                            {
                                if(player_round == false)
                                {
                                    if(allow_attack1 == true)
                                    {
                                        if((gladiator1->getHandDam() - gladiator2->getHandDef()) <= 0)
                                        {
                                            gladiator2->setHandDef(gladiator2->getHandDef() - 5);
                                        }

                                        else
                                        {
                                            life_player2 -= (gladiator1->getHandDam() - gladiator2->getHandDef());
                                            gladiator2->setHandDef(gladiator2->getHandDef() - 5);
                                        }

                                        if(life_player2 > 0)
                                        {
                                            gladiator_player = al_load_bitmap("Gladiator_Player_Attack.png");
                                            gladiator_enemy = al_load_bitmap("Gladiator_Enemy.png");
                                            posX_Enemy = 705;
                                            posX = 284;
                                            allow_attack1 = false;
                                            allow_kick1 = true;
                                            allow_charge1 = true;
                                            player_round = true;
                                            authorize = false;
                                        }

                                        else if(life_player2 <= 0)
                                        {
                                            gladiator_player = al_load_bitmap("Gladiator_Player_Attack.png");
                                            gladiator_enemy = al_load_bitmap("Gladiator_Enemy_Decapitated.png");
                                            posY_Enemy = 305;
                                            posX = 284;
                                            victories_Team1 += 1;
                                            doexit = true;
                                        }
                                    }

                                    else
                                    {
                                        gladiator_player = al_load_bitmap("Gladiator_Player.png");
                                        gladiator_enemy = al_load_bitmap("Gladiator_Enemy.png");
                                        posX = 284;
                                        posX_Enemy = 675;
                                        allow_attack1 = true;
                                        player_round = true;
                                        authorize = false;
                                    }
                                }

                                else if(player_round == true)
                                {
                                    if(allow_attack2 == true)
                                    {
                                        if((gladiator2->getHandDam() - gladiator1->getHandDef()) <= 0)
                                        {
                                            gladiator1->setHandDef(gladiator1->getHandDef() - 5);
                                        }

                                        else
                                        {
                                            life_player1 -= (gladiator2->getHandDam() - gladiator1->getHandDef());
                                            gladiator1->setHandDef(gladiator1->getHandDef() - 5);
                                        }

                                        if(life_player1 > 0)
                                        {
                                            gladiator_player = al_load_bitmap("Gladiator_Player.png");
                                            gladiator_enemy = al_load_bitmap("Gladiator_Enemy_Attack.png");
                                            posX = 254;
                                            posX_Enemy = 675;
                                            allow_attack2 = false;
                                            allow_kick2 = true;
                                            allow_charge2 = true;
                                            player_round = false;
                                            authorize = false;
                                        }

                                        else if(life_player1 <= 0)
                                        {
                                            gladiator_player = al_load_bitmap("Gladiator_Player_Decapitated.png");
                                            gladiator_enemy = al_load_bitmap("Gladiator_Enemy_Attack.png");
                                            posY = 305;
                                            posX_Enemy = 675;
                                            victories_Team2 += 1;
                                            doexit = true;
                                        }
                                    }

                                    else
                                    {
                                        gladiator_player = al_load_bitmap("Gladiator_Player.png");
                                        gladiator_enemy = al_load_bitmap("Gladiator_Enemy.png");
                                        posX = 284;
                                        posX_Enemy = 675;
                                        allow_attack2 = true;
                                        player_round = false;
                                        authorize = false;
                                    }

                                }
                            }

                            else if(Kick == true)
                            {
                                if(player_round == false)
                                {
                                    if(allow_kick1 == true)
                                    {
                                        if((gladiator1->getFootDam() - gladiator2->getFootDef()) <= 0)
                                        {
                                            gladiator2->setFootDef(gladiator2->getFootDef() - 5);
                                        }

                                        else
                                        {
                                            life_player2 -= (gladiator1->getFootDam() - gladiator2->getFootDef());
                                            gladiator2->setFootDef(gladiator2->getFootDef() - 5);
                                        }

                                        if(life_player2 > 0)
                                        {
                                            gladiator_player = al_load_bitmap("Gladiator_Player_Kick.png");
                                            gladiator_enemy = al_load_bitmap("Gladiator_Enemy.png");
                                            posX_Enemy = 705;
                                            posX = 284;
                                            allow_attack1 = true;
                                            allow_kick1 = false;
                                            allow_charge1 = true;
                                            player_round = true;
                                            authorize = false;
                                        }

                                        else if(life_player2 <= 0)
                                        {
                                            gladiator_player = al_load_bitmap("Gladiator_Player_Kick.png");
                                            gladiator_enemy = al_load_bitmap("Gladiator_Enemy_Dead.png");
                                            posY_Enemy = 285;
                                            posX = 284;
                                            victories_Team1 += 1;
                                            doexit = true;
                                        }
                                    }

                                    else
                                    {
                                        gladiator_player = al_load_bitmap("Gladiator_Player.png");
                                        gladiator_enemy = al_load_bitmap("Gladiator_Enemy.png");
                                        posX = 284;
                                        posX_Enemy = 675;
                                        allow_kick1 = true;
                                        player_round = true;
                                        authorize = false;
                                    }
                                }

                                else if(player_round == true)
                                {
                                    if(allow_kick2 == true)
                                    {
                                        if((gladiator2->getFootDam() - gladiator1->getFootDef()) <= 0)
                                        {
                                            gladiator1->setFootDef(gladiator1->getFootDef() - 5);
                                        }

                                        else
                                        {
                                            life_player1 -= (gladiator2->getFootDam() - gladiator1->getFootDef());
                                            gladiator1->setFootDef(gladiator1->getFootDef() - 5);
                                        }

                                        if(life_player1 > 0)
                                        {
                                            gladiator_player = al_load_bitmap("Gladiator_Player.png");
                                            gladiator_enemy = al_load_bitmap("Gladiator_Enemy_Kick.png");
                                            posX = 254;
                                            posX_Enemy = 675;
                                            allow_attack2 = true;
                                            allow_kick2 = false;
                                            allow_charge2 = true;
                                            player_round = false;
                                            authorize = false;
                                        }

                                        else if(life_player1 <= 0)
                                        {
                                            gladiator_player = al_load_bitmap("Gladiator_Player_Dead.png");
                                            gladiator_enemy = al_load_bitmap("Gladiator_Enemy_Kick.png");
                                            posY = 305;
                                            posX_Enemy = 675;
                                            victories_Team2 += 1;
                                            doexit = true;
                                        }
                                    }

                                    else
                                    {
                                        gladiator_player = al_load_bitmap("Gladiator_Player.png");
                                        gladiator_enemy = al_load_bitmap("Gladiator_Enemy.png");
                                        posX = 284;
                                        posX_Enemy = 675;
                                        allow_kick2 = true;
                                        player_round = false;
                                        authorize = false;
                                    }

                                }
                            }

                            else if(Charge == true)
                            {
                                if(player_round == false)
                                {
                                    if(allow_charge1 == true)
                                    {
                                        if((gladiator1->getBodyDam() - gladiator2->getBodyDef()) < 0)
                                        {
                                            gladiator2->setBodyDef(gladiator2->getBodyDef() - 5);
                                        }

                                        else
                                        {
                                            life_player2 -= (gladiator1->getBodyDam() - gladiator2->getBodyDef());
                                            gladiator2->setBodyDef(gladiator2->getBodyDef() - 5);
                                        }

                                        if(life_player2 > 0)
                                        {
                                            gladiator_player = al_load_bitmap("Gladiator_Player_Charge.png");
                                            gladiator_enemy = al_load_bitmap("Gladiator_Enemy.png");
                                            posX_Enemy = 705;
                                            posX += 10;
                                            allow_attack1 = true;
                                            allow_kick1 = true;
                                            allow_charge1 = false;
                                            player_round = true;
                                            authorize = false;
                                        }

                                        else if(life_player2 <= 0)
                                        {
                                            gladiator_player = al_load_bitmap("Gladiator_Player_Charge.png");
                                            gladiator_enemy = al_load_bitmap("Gladiator_Enemy_Dead.png");
                                            posY_Enemy = 285;
                                            posX = 284;
                                            victories_Team1 += 1;
                                            doexit = true;
                                        }
                                    }

                                    else
                                    {
                                        gladiator_player = al_load_bitmap("Gladiator_Player.png");
                                        gladiator_enemy = al_load_bitmap("Gladiator_Enemy.png");
                                        posX = 284;
                                        posX_Enemy = 675;
                                        allow_charge1 = true;
                                        player_round = true;
                                        authorize = false;
                                    }
                                }

                                else if(player_round == true)
                                {
                                    if(allow_charge2 == true)
                                    {
                                        if((gladiator2->getBodyDam() - gladiator1->getBodyDef()) < 0)
                                        {
                                            gladiator1->setBodyDef(gladiator1->getBodyDef() - 5);
                                        }

                                        else
                                        {
                                            life_player1 -= (gladiator2->getBodyDam() - gladiator1->getBodyDef());
                                            gladiator1->setBodyDef(gladiator1->getBodyDef() - 5);
                                        }

                                        if(life_player1 > 0)
                                        {
                                            gladiator_player = al_load_bitmap("Gladiator_Player.png");
                                            gladiator_enemy = al_load_bitmap("Gladiator_Enemy_Charge.png");
                                            posX = 254;
                                            posX_Enemy -= 10;
                                            allow_attack2 = true;
                                            allow_kick2 = true;
                                            allow_charge2 = false;
                                            player_round = false;
                                            authorize = false;
                                        }

                                        else if(life_player1 <= 0)
                                        {
                                            gladiator_player = al_load_bitmap("Gladiator_Player_Dead.png");
                                            gladiator_enemy = al_load_bitmap("Gladiator_Enemy_Charge.png");
                                            posY = 305;
                                            posX_Enemy = 675;
                                            victories_Team2 += 1;
                                            doexit = true;
                                        }
                                    }

                                    else
                                    {
                                        gladiator_player = al_load_bitmap("Gladiator_Player.png");
                                        gladiator_enemy = al_load_bitmap("Gladiator_Enemy.png");
                                        posX = 284;
                                        posX_Enemy = 675;
                                        allow_charge2 = true;
                                        player_round = false;
                                        authorize = false;
                                    }

                                }
                            }

                            //doexit = true;
                        }
                    }

                    redraw = true;
                }
                else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                {
                    break;
                }

                //Key is pressed

                else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
                {
                    switch(ev.keyboard.keycode)
                    {
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

                //Key is relesed

                else if(ev.type == ALLEGRO_EVENT_KEY_UP)
                {
                    switch(ev.keyboard.keycode)
                    {
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
            }

            else if(mode_game == 1)
            {
                //PvsB Logic
                if(player_round == false)
                {
                    ALLEGRO_EVENT ev;
                    al_wait_for_event(event_queue, &ev); //Wait for keyboard to be pressed
                    if(ev.type == ALLEGRO_EVENT_TIMER)
                    {

                        if(key[KEY_UP])
                        {
                            kick = al_load_bitmap("Kick_Circle_Big.png");
                            attack = al_load_bitmap("Attack_Circle.png");
                            charge = al_load_bitmap("Charge_Circle.png");
                            Kick = true;
                            Attack = false;
                            Charge = false;
                            authorize = true;
                        }

                        if(key[KEY_DOWN])
                        {
                            kick = al_load_bitmap("Kick_Circle.png");
                            attack = al_load_bitmap("Attack_Circle.png");
                            charge = al_load_bitmap("Charge_Circle.png");
                            Kick = false;
                            authorize = false;
                            Attack = false;
                            Charge = false;
                        }

                        if(key[KEY_LEFT])
                        {
                            if(authorize == true)
                            {
                                kick = al_load_bitmap("Kick_Circle.png");
                                attack = al_load_bitmap("Attack_Circle_Big.png");
                                charge = al_load_bitmap("Charge_Circle.png");
                                Attack = true;
                                Kick = false;
                                Charge = false;
                            }
                        }

                        if(key[KEY_RIGHT])
                        {
                            if(authorize == true)
                            {
                                kick = al_load_bitmap("Kick_Circle.png");
                                attack = al_load_bitmap("Attack_Circle.png");
                                charge = al_load_bitmap("Charge_Circle_Big.png");
                                Charge = true;
                                Attack = false;
                                Kick = false;
                            }
                        }

                        if(key[KEY_SPACE])
                        {
                            if(authorize == true)
                            {
                                if(Attack == true)
                                {
                                    if(allow_attack1 == true)
                                    {
                                        if((gladiator1->getHandDam() - gladiator2->getHandDef()) <= 0)
                                        {
                                            gladiator2->setHandDef(gladiator2->getHandDef() - 5);
                                        }

                                        else
                                        {
                                            life_player2 -= (gladiator1->getHandDam() - gladiator2->getHandDef());
                                            gladiator2->setHandDef(gladiator2->getHandDef() - 5);
                                        }

                                        if(life_player2 > 0)
                                        {
                                            gladiator_player = al_load_bitmap("Gladiator_Player_Attack.png");
                                            gladiator_enemy = al_load_bitmap("Gladiator_Enemy.png");
                                            posX_Enemy = 705;
                                            posX = 284;
                                            allow_attack1 = false;
                                            allow_kick1 = true;
                                            allow_charge1 = true;
                                            player_round = true;
                                            authorize = false;
                                        }

                                        else if(life_player2 <= 0)
                                        {
                                            gladiator_player = al_load_bitmap("Gladiator_Player_Attack.png");
                                            gladiator_enemy = al_load_bitmap("Gladiator_Enemy_Decapitated.png");
                                            posY_Enemy = 305;
                                            posX = 284;
                                            victories_Team1 += 1;
                                            doexit = true;
                                        }
                                    }

                                    else
                                    {
                                        gladiator_player = al_load_bitmap("Gladiator_Player.png");
                                        gladiator_enemy = al_load_bitmap("Gladiator_Enemy.png");
                                        posX = 284;
                                        posX_Enemy = 675;
                                        allow_attack1 = true;
                                        player_round = true;
                                        authorize = false;
                                    }
                                }

                                else if(Kick == true)
                                {
                                    if(allow_kick1 == true)
                                    {
                                        if((gladiator1->getFootDam() - gladiator2->getFootDef()) <= 0)
                                        {
                                            gladiator2->setFootDef(gladiator2->getFootDef() - 5);
                                        }

                                        else
                                        {
                                            life_player2 -= (gladiator1->getFootDam() - gladiator2->getFootDef());
                                            gladiator2->setFootDef(gladiator2->getFootDef() - 5);
                                        }

                                        if(life_player2 > 0)
                                        {
                                            gladiator_player = al_load_bitmap("Gladiator_Player_Kick.png");
                                            gladiator_enemy = al_load_bitmap("Gladiator_Enemy.png");
                                            posX_Enemy = 705;
                                            posX = 284;
                                            allow_attack1 = true;
                                            allow_kick1 = false;
                                            allow_charge1 = true;
                                            player_round = true;
                                            authorize = false;
                                        }

                                        else if(life_player2 <= 0)
                                        {
                                            gladiator_player = al_load_bitmap("Gladiator_Player_Kick.png");
                                            gladiator_enemy = al_load_bitmap("Gladiator_Enemy_Dead.png");
                                            posY_Enemy = 285;
                                            posX = 284;
                                            victories_Team1 += 1;
                                            doexit = true;
                                        }
                                    }

                                    else
                                    {
                                        gladiator_player = al_load_bitmap("Gladiator_Player.png");
                                        gladiator_enemy = al_load_bitmap("Gladiator_Enemy.png");
                                        posX = 284;
                                        posX_Enemy = 675;
                                        allow_kick1 = true;
                                        player_round = true;
                                        authorize = false;
                                    }
                                }

                                else if(Charge == true)
                                {
                                    if(allow_charge1 == true)
                                    {
                                        if((gladiator1->getBodyDam() - gladiator2->getBodyDef()) < 0)
                                        {
                                            gladiator2->setBodyDef(gladiator2->getBodyDef() - 5);
                                        }

                                        else
                                        {
                                            life_player2 -= (gladiator1->getBodyDam() - gladiator2->getBodyDef());
                                            gladiator2->setBodyDef(gladiator2->getBodyDef() - 5);
                                        }

                                        if(life_player2 > 0)
                                        {
                                            gladiator_player = al_load_bitmap("Gladiator_Player_Charge.png");
                                            gladiator_enemy = al_load_bitmap("Gladiator_Enemy.png");
                                            posX_Enemy = 705;
                                            posX += 10;
                                            allow_attack1 = true;
                                            allow_kick1 = true;
                                            allow_charge1 = false;
                                            player_round = true;
                                            authorize = false;
                                        }

                                        else if(life_player2 <= 0)
                                        {
                                            gladiator_player = al_load_bitmap("Gladiator_Player_Charge.png");
                                            gladiator_enemy = al_load_bitmap("Gladiator_Enemy_Dead.png");
                                            posY_Enemy = 285;
                                            posX = 284;
                                            victories_Team1 += 1;
                                            doexit = true;
                                        }
                                    }

                                    else
                                    {
                                        gladiator_player = al_load_bitmap("Gladiator_Player.png");
                                        gladiator_enemy = al_load_bitmap("Gladiator_Enemy.png");
                                        posX = 284;
                                        posX_Enemy = 675;
                                        allow_charge1 = true;
                                        player_round = true;
                                        authorize = false;
                                    }
                                }

                                //doexit = true;
                            }
                        }

                        redraw = true;
                    }
                    else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                    {
                        break;
                    }

                    //Key is pressed

                    else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
                    {
                        switch(ev.keyboard.keycode)
                        {
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

                    //Key is relesed

                    else if(ev.type == ALLEGRO_EVENT_KEY_UP)
                    {
                        switch(ev.keyboard.keycode)
                        {
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
                }

            }

            /*ALLEGRO_EVENT ev;
            al_wait_for_event(event_queue, &ev); //Wait for keyboard to be pressed
            if(ev.type == ALLEGRO_EVENT_TIMER)
            {

                if(key[KEY_UP])
                {
                    kick = al_load_bitmap("Kick_Circle_Big.png");
                    attack = al_load_bitmap("Attack_Circle.png");
                    charge = al_load_bitmap("Charge_Circle.png");
                    Kick = true;
                    Attack = false;
                    Charge = false;
                    authorize = true;
                }

                if(key[KEY_DOWN])
                {
                    kick = al_load_bitmap("Kick_Circle.png");
                    attack = al_load_bitmap("Attack_Circle.png");
                    charge = al_load_bitmap("Charge_Circle.png");
                    Kick = false;
                    authorize = false;
                    Attack = false;
                    Charge = false;
                }

                if(key[KEY_LEFT])
                {
                    if(authorize == true)
                    {
                        kick = al_load_bitmap("Kick_Circle.png");
                        attack = al_load_bitmap("Attack_Circle_Big.png");
                        charge = al_load_bitmap("Charge_Circle.png");
                        Attack = true;
                        Kick = false;
                        Charge = false;
                    }
                }

                if(key[KEY_RIGHT])
                {
                    if(authorize == true)
                    {
                        kick = al_load_bitmap("Kick_Circle.png");
                        attack = al_load_bitmap("Attack_Circle.png");
                        charge = al_load_bitmap("Charge_Circle_Big.png");
                        Charge = true;
                        Attack = false;
                        Kick = false;
                    }
                }

                if(key[KEY_SPACE])
                {
                    if(authorize == true)
                    {
                        if(Attack == true)
                        {
                            gladiator_player = al_load_bitmap("Gladiator_Player_Attack.png");
                            gladiator_enemy = al_load_bitmap("Gladiator_Enemy_Decapitated.png");
                            posY_Enemy = 305;
                            posX = 284;
                        }

                        else if(Kick == true)
                        {
                            gladiator_player = al_load_bitmap("Gladiator_Player_Kick.png");
                            gladiator_enemy = al_load_bitmap("Gladiator_Enemy_Dead.png");
                            posX = 284;
                            posY_Enemy = 285;
                        }

                        else if(Charge == true)
                        {
                            gladiator_player = al_load_bitmap("Gladiator_Player_Charge.png");
                            gladiator_enemy = al_load_bitmap("Gladiator_Enemy_Dead.png");
                            posX += 10;
                            posY_Enemy = 285;
                        }

                        doexit = true;
                    }
                }

                redraw = true;
            }
            else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                break;
            }

            //Key is pressed

            else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                switch(ev.keyboard.keycode)
                {
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

            //Key is relesed

            else if(ev.type == ALLEGRO_EVENT_KEY_UP)
            {
                switch(ev.keyboard.keycode)
                {
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
            }*/

            //The game is actualized

            if(redraw && al_is_event_queue_empty(event_queue))
            {
                redraw = false;
                al_draw_bitmap(background,0,0,0);
                al_draw_bitmap(al_load_bitmap("Genetic_Gladiator.png"),430,500,0);
                stringstream strs;
                strs << life_player1;
                string temp_str = strs.str();
                char const* player1_resistance = temp_str.c_str();
                al_draw_text(font2, al_map_rgb(0,0,0), 150, 550,ALLEGRO_ALIGN_CENTRE, "Gladiator One:");
                al_draw_text(font, al_map_rgb(0,0,0), 270, 550,0, player1_resistance);
                stringstream strs1;
                strs1 << life_player2;
                string temp_str1 = strs1.str();
                char const* player2_resistance = temp_str1.c_str();
                al_draw_text(font2, al_map_rgb(0,0,0), 1030, 550,ALLEGRO_ALIGN_CENTRE, "Gladiator Two:");
                al_draw_text(font, al_map_rgb(0,0,0), 850, 550,ALLEGRO_ALIGN_CENTRE, player2_resistance);
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
        al_destroy_font(font);
        al_destroy_font(font2);
        flag_for_change = true;
    }

    return 0;
}

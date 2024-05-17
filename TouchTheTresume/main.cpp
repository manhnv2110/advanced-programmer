#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
using namespace std;
#define window_height 800
#define window_width 1500
#define Land_Unit 60
#define Size_Cnt(x) (sizeof(x)/sizeof((x)[0]))
SDL_Window *window;
SDL_Renderer *renderer;
struct Input_State
{
    int up,pre_up;
    SDL_Event event;
};
enum Game_Phase
{
    GAME_START,
    GAME_PLAY,
    GAME_PAUSE,
    GAME_OVER,
};
struct Game_State
{
    Game_Phase Phase;
    int Now_Map,Next_Map,point,level,Margin,Guild_Open,Delay_Time,Time_To_Next_Level,Mute_Mode=0;
};
bool quit=false;
int Margin_x=0;

SDL_Texture *Coin,*Shield,*Trap,*Obs,*Point,*Point_Bar,*Amor,*Amor_Bar,*Explosion;
SDL_Texture *Guild1,*Guild2,*Pause1,*Pause2, *Play1, *Play2, *Quit1,*Quit2,*Menu,*Out1,*Out2,*Restart1,*Restart2,*Music1,*Music2,*Music3,*Guild_Table;
TTF_Font *font;
Mix_Chunk *coin_sound,*game_over_sound,*get_shield_sound,*jump_sound,*play_music,*explosion_sound;

int Move_Speed[]= {1,2,3,4,5};

SDL_Rect Rect_With_Margin(SDL_Rect rect,int margin)
{
    rect.x=rect.x+margin;
    return rect;
}
void Get_Point_Texture(int val) {
    SDL_Color color = {255, 255, 255, 255};
    string text = to_string(val);

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    Point = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}
bool In_Rect(SDL_Rect rect,int x,int y)
{
    if(x<rect.x || rect.x+rect.w<x) return false;
    if(y<rect.y || rect.y+rect.h<y) return false;
    return true;
}
#include "Map.h"
#include "MainCharacter.h"
#include "Draw.h"
void Restore_Map(int vt)
{
    int i;
    for(i=0;i<Map_List[vt].Item_List.size();i++) Map_List[vt].Item_List[i].status=0;
    for(i=0;i<Map_List[vt].Obstacle.size();i++) Map_List[vt].Obstacle[i].status=0;
    for(i=0;i<Map_List[vt].Trap_List.size();i++) Map_List[vt].Trap_List[i].second=0;
    return;
}
void Reset_Data(Game_State *game)
{
    Restore_Map(game->Now_Map);
    game->point=0;
    game->level=0;
    game->Margin=0;
    game->Now_Map=0;
    game->Time_To_Next_Level=SDL_GetTicks()+10000;
    game->Next_Map=rand()%Size_Cnt(Map_List);
    Margin_x=Move_Speed[0];
    MC.Pos={0,400,100,100};
    MC.status=0;
    MC.IMG_num=1;
    MC.time_end_undead=0;
    MC.Distan[0]=Move_Speed[0];
}
void update_game_play(Game_State *game,Input_State *input)
{
    if(MC.Pos.x<Margin_x) MC.Distan[0]+=1;
    else MC.Distan[0]=Move_Speed[game->level];
    Margin_x+=Move_Speed[game->level];
    if(MC.Pos.x+MC.Pos.w>=game->Margin+window_width)
    {
        Restore_Map(game->Now_Map);
        game->Now_Map=game->Next_Map;
        Restore_Map(game->Now_Map);
        game->Next_Map=rand()%Size_Cnt(Map_List);
        game->Margin+=window_width;
    }
    Character_Move(game,input);
    Impact_Handle(game);
    if(SDL_GetTicks()>=game->Time_To_Next_Level && game->level<=Size_Cnt(Move_Speed))
    {
        game->level++;
        MC.Distan[0]=Move_Speed[game->level];
        game->Time_To_Next_Level+=Move_Speed[game->level]*10000;
    }
    return;
}
void Control_Wait_Menu(Game_State *game,Input_State *input)
{
    SDL_Rect pause_button,guild_button,quit_button,out_button,restart_button,music_button,menu_table;
    pause_button={600,400,300,150};
    guild_button={900,600,300,150};
    quit_button={1300,0,200,100};
    music_button={300,600,300,150};
    menu_table={0,0,1500,800};
    if(game->Guild_Open==1)
    {
        SDL_RenderCopy(renderer,Guild_Table,NULL,NULL);
        if(In_Rect(out_button,input->event.motion.x,input->event.motion.y)==false) SDL_RenderCopy(renderer,Out1,NULL,&out_button);
        else
        {
            SDL_RenderCopy(renderer,Out2,NULL,&out_button);
            if(input->event.type==SDL_MOUSEBUTTONUP) game->Guild_Open=0;
        }
        return;
    }
    SDL_RenderCopy(renderer,Menu,NULL,&menu_table);

    if(In_Rect(pause_button,input->event.motion.x,input->event.motion.y)==false) SDL_RenderCopy(renderer,Pause1,NULL,&pause_button);
    else
    {
        SDL_RenderCopy(renderer,Pause2,NULL,&pause_button);
        if(input->event.type==SDL_MOUSEBUTTONUP)
        {
            if(game->Phase==GAME_START || game->Phase==GAME_OVER) Reset_Data(game);
            else game->Time_To_Next_Level=game->Time_To_Next_Level+SDL_GetTicks()-game->Delay_Time;
            game->Phase=GAME_PLAY;
        }
    }

    if(In_Rect(guild_button,input->event.motion.x,input->event.motion.y)==false) SDL_RenderCopy(renderer,Guild1,NULL,&guild_button);
    else
    {
        SDL_RenderCopy(renderer,Guild2,NULL,&guild_button);
        if(input->event.type==SDL_MOUSEBUTTONUP) game->Guild_Open=1;
    }

    if(In_Rect(quit_button,input->event.motion.x,input->event.motion.y)==false) SDL_RenderCopy(renderer,Quit1,NULL,&quit_button);
    else
    {
        SDL_RenderCopy(renderer,Quit2,NULL,&quit_button);
        if(input->event.type==SDL_MOUSEBUTTONUP) quit=true;
    }

    if(game->Phase==GAME_PAUSE)
    {
        if(In_Rect(restart_button,input->event.motion.x,input->event.motion.y)==false) SDL_RenderCopy(renderer,Restart1,NULL,&restart_button);
        else
        {
            SDL_RenderCopy(renderer,Restart2,NULL,&restart_button);
            if(input->event.type==SDL_MOUSEBUTTONUP)
            {
                Reset_Data(game);
                game->Phase=GAME_PLAY;
            }
        }
    }

    if(In_Rect(music_button,input->event.motion.x,input->event.motion.y)==true)
    {
        SDL_RenderCopy(renderer,Music2,NULL,&music_button);
        if(input->event.type==SDL_MOUSEBUTTONUP)
        {
            game->Mute_Mode=1-game->Mute_Mode;
            if(game->Mute_Mode==1) Mix_Pause(2);
            else Mix_PlayChannel(2,play_music,-1);
        }
    }
    else if(In_Rect(music_button,input->event.motion.x,input->event.motion.y)==false && game->Mute_Mode==0) SDL_RenderCopy(renderer,Music1,NULL,&music_button);
    else if(In_Rect(music_button,input->event.motion.x,input->event.motion.y)==false && game->Mute_Mode==1) SDL_RenderCopy(renderer,Music3,NULL,&music_button);
    return;
}
void Update_game(Game_State *game,Input_State *input)
{
    switch(game->Phase)
    {
        case
         GAME_START:
             Control_Wait_Menu(game,input);break;
        case
         GAME_PLAY:
            update_game_play(game,input);break;
         case GAME_PAUSE:
            Control_Wait_Menu(game,input);break;
        case GAME_OVER:
            Control_Wait_Menu(game,input);break;
    }
    return;
}
void Prepare()
{
    SDL_Surface *surface;
    font=TTF_OpenFont("font.ttf",20);
    for (int i = 1; i <= 14; i++)
{
    string filename = "Title/" + to_string(i) + ".png";
    surface = IMG_Load(filename.c_str());

    Map_Texture[i] = SDL_CreateTextureFromSurface(renderer, surface);
}

    surface=IMG_Load("background.jpg");
    Back_Ground=SDL_CreateTextureFromSurface(renderer,surface);

    surface=IMG_Load("other/1.png");
    Coin=SDL_CreateTextureFromSurface(renderer,surface);
    surface=IMG_Load("other/shield.png");
    Shield=SDL_CreateTextureFromSurface(renderer,surface);
    surface=IMG_Load("other/3.png");
    Trap=SDL_CreateTextureFromSurface(renderer,surface);
    surface=IMG_Load("other/4.png");
    Obs=SDL_CreateTextureFromSurface(renderer,surface);
    surface=IMG_Load("other/Point_Bar.png");
    Point_Bar=SDL_CreateTextureFromSurface(renderer,surface);
    surface=IMG_Load("other/Amor.png");
    Amor=SDL_CreateTextureFromSurface(renderer,surface);
    surface=IMG_Load("other/Amor_Bar.png");
    Amor_Bar=SDL_CreateTextureFromSurface(renderer,surface);
    surface=IMG_Load("other/explosion.png");
    Explosion=SDL_CreateTextureFromSurface(renderer,surface);

    surface=IMG_Load("button/Guild1.png");
    Guild1=SDL_CreateTextureFromSurface(renderer,surface);
    surface=IMG_Load("button/Guild2.png");
    Guild2=SDL_CreateTextureFromSurface(renderer,surface);
    surface=IMG_Load("button/Pause1.png");
    Pause1=SDL_CreateTextureFromSurface(renderer,surface);
    surface=IMG_Load("button/Pause2.png");
    Pause2=SDL_CreateTextureFromSurface(renderer,surface);
    surface=IMG_Load("button/Quit1.png");
    Quit1=SDL_CreateTextureFromSurface(renderer,surface);
    surface=IMG_Load("button/Quit2.png");
    Quit2=SDL_CreateTextureFromSurface(renderer,surface);
    surface=IMG_Load("button/Music1.png");
    Music1=SDL_CreateTextureFromSurface(renderer,surface);
    surface=IMG_Load("button/Music2.png");
    Music2=SDL_CreateTextureFromSurface(renderer,surface);
    surface=IMG_Load("button/Music3.png");
    Music3=SDL_CreateTextureFromSurface(renderer,surface);
    surface=IMG_Load("button/Guild_Table.png");
    Guild_Table=SDL_CreateTextureFromSurface(renderer,surface);
    surface=IMG_Load("button/Menu_Table.png");
    Menu=SDL_CreateTextureFromSurface(renderer,surface);

    coin_sound=Mix_LoadWAV("Sound/coin.wav");
    game_over_sound=Mix_LoadWAV("Sound/game_over.wav");
    get_shield_sound=Mix_LoadWAV("Sound/get_shield.wav");
    jump_sound=Mix_LoadWAV("Sound/jump.wav");
    explosion_sound=Mix_LoadWAV("Sound/explosion_sound.wav");
    play_music=Mix_LoadWAV("Sound/play_music.wav");

    Create_Main_Character();
    SDL_FreeSurface(surface);
    return;
}
void Free_Data()
{
    int i,j;
    for(i=1;i<=14;i++) SDL_DestroyTexture(Map_Texture[i]);
    for(i=0;i<=2;i++)
    for(j=0;j<10;j++) SDL_DestroyTexture(MC.Mc_Textuter[i][j]);
    SDL_DestroyTexture(Coin);
    SDL_DestroyTexture(Shield);
    SDL_DestroyTexture(Trap);
    SDL_DestroyTexture(Obs);
    SDL_DestroyTexture(Point_Bar);
    SDL_DestroyTexture(Amor);
    SDL_DestroyTexture(Amor_Bar);
    SDL_DestroyTexture(Explosion);
    SDL_DestroyTexture(Guild1);
    SDL_DestroyTexture(Guild2);
    SDL_DestroyTexture(Pause1);
    SDL_DestroyTexture(Pause2);;
    SDL_DestroyTexture(Quit1);
    SDL_DestroyTexture(Quit2);
    SDL_DestroyTexture(Music1);
    SDL_DestroyTexture(Music2);
    SDL_DestroyTexture(Music3);
    SDL_DestroyTexture(Guild_Table);
    SDL_DestroyTexture(Menu);
    SDL_DestroyTexture(Point);
    SDL_DestroyTexture(Back_Ground);
    Mix_FreeChunk(coin_sound);
    Mix_FreeChunk(game_over_sound);
    Mix_FreeChunk(jump_sound);
    Mix_FreeChunk(play_music);
    Mix_FreeChunk(explosion_sound);


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

}
int main(int argv,char *argc[])
{
    if(SDL_Init(SDL_INIT_EVERYTHING)) return 1;
    if(TTF_Init()) return 2;
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,2,4096)==-1) return 3;
    window=SDL_CreateWindow("TouchTheTresume",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,window_width,window_height,SDL_WINDOW_OPENGL);
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_TARGETTEXTURE);
    Game_State game{};
    Input_State input;

    Prepare();
    Mix_PlayChannel(2,play_music,-1);
    while(!quit)
    {
        if(input.event.type==SDL_QUIT) quit=1;
        const uint8_t *key_state=SDL_GetKeyboardState(NULL);

        input.pre_up=input.up;
        input.up=key_state[SDL_SCANCODE_UP];

        SDL_PollEvent(&input.event);


        SDL_RenderClear(renderer);
        Draw_Game_Play(&game,&input);

        Update_game(&game,&input);
        SDL_RenderPresent(renderer);
    }
    Mix_CloseAudio();
    SDL_RenderPresent(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    return 0;
}

struct Character
{
    SDL_Rect Pos;
    int IMG_num,status,undead;
    int time_end_undead;
    int Distan[3];
    SDL_Texture *Mc_Textuter[4][20];
};
Character MC;
    void Create_Main_Character() {
        MC.Pos = {0, 400, 100, 100};
        MC.status = 0;
        MC.IMG_num = 1;
        MC.time_end_undead = 0;
        MC.Distan[0] = Move_Speed[0];
        MC.Distan[1] = 20;
        MC.Distan[2] = 1;
        int i, j;
        SDL_Surface* surface;

        for (i = 0; i <= 2; i++) {
            for (j = 0; j < 10; j++) {
            string filename;
            if (i == 0)
                filename = "Character/run" + to_string(j) + ".png";
            else if (i == 1)
                filename = "Character/jump" + to_string(j) + ".png";
            else if (i == 2)
                filename = "Character/fly" + to_string(j) + ".png";
                surface = IMG_Load(filename.c_str());
                MC.Mc_Textuter[i][j] = SDL_CreateTextureFromSurface(renderer, surface);
            }
        }
        SDL_FreeSurface(surface);
        return;
    }

bool on_earth(int vt,int margin)
{
    int x=MC.Pos.x;
    int y=MC.Pos.x+MC.Pos.w;
    SDL_Rect rect;
    for(int i=0;i<Map_List[vt].Ground.size();i++)
    {
        rect=Rect_With_Margin(Map_List[vt].Ground[i],margin);
        int z=rect.x;
        int t=rect.x+rect.w;
        if(MC.Pos.y+MC.Pos.h!=rect.y) continue;
        if(x<=z && z<y && y<=t) return true;
        if(z<=x && x<t && t<=y) return true;
        if(z<=x && y<=t) return true;
        if(x<=z && t<=y) return true;
    }
    return false;
}
bool Impact_Check_Primery(SDL_Rect a,SDL_Rect b)
{
    if(b.y<a.y+a.h && a.y+a.h<=b.y+b.h)
    {
        if(b.x<=a.x && a.x<b.x+b.w) return true;
        if(b.x<a.x+a.w && a.x+a.w<=b.x+b.w) return true;
    }
    if(b.y<=a.y && a.y<b.y+b.h)
    {
        if(b.x<=a.x && a.x<b.x+b.w) return true;
        if(b.x<a.x+a.w && a.x+a.w<=b.x+b.w) return true;
    }
    return false;
}
bool Impact_Check(SDL_Rect a,SDL_Rect b)
{
    if(Impact_Check_Primery(a,b)==1 || Impact_Check_Primery(b,a)==1) return true;
    return false;
}
int Map_Impact(SDL_Rect rect,int vt,int margin)
{
    int i;
    SDL_Rect rect1;
    for(i=0;i<Map_List[vt].Ground.size();i++)
    {
        rect1=Rect_With_Margin(Map_List[vt].Ground[i],margin);
        if(Impact_Check(rect,rect1)==true) return i;
    }
    return -1;
}
SDL_Rect Next_Pos(int status,int val,SDL_Rect Pos,SDL_Rect ground,int margin)
{
    ground.x+=margin;
    if(status==0) //front
    {
        if(Pos.x+Pos.w+val<=ground.x) Pos.x=Pos.x+val;
        else Pos.x=ground.x-Pos.w;
    }
    if(status==1) //jump
    {
        if(Pos.y-val>=ground.y+ground.h || Pos.y-val<=ground.y) Pos.y=Pos.y-val;
        else Pos.y=ground.y+ground.h;
    }
    if(status==2) //fall
    {
        if(Pos.y+Pos.h+val<=ground.y) Pos.y=Pos.y+val;
        else Pos.y=ground.y-Pos.h;
    }
    return Pos;
}
SDL_Rect Get_Valid_Pos(int status,SDL_Rect rect,int val,int vt,int margin)
{
    SDL_Rect rect1=rect;
    if(status==0) rect1.x+=val;
    if(status==1) rect1.y-=val;
    if(status==2) rect1.y+=val;
    int ground=Map_Impact(rect1,vt,margin);
    while(ground!=-1)
    {
        rect1=Next_Pos(status,val,rect,Map_List[vt].Ground[ground],margin);
        ground=Map_Impact(rect1,vt,margin);
    }
    return rect1;
}
void Impact_Handle(Game_State *game)
{
    int i;
    SDL_Rect rect;
    double Now_time=SDL_GetTicks();
    if(Now_time>MC.time_end_undead) MC.undead=0;
    for(i=0;i<Map_List[game->Now_Map].Item_List.size();i++)
    {
        if(Map_List[game->Now_Map].Item_List[i].status==1) continue;
        rect=Rect_With_Margin(Map_List[game->Now_Map].Item_List[i].Pos,game->Margin);
        if(Impact_Check(MC.Pos,rect)==true)
        {
            if(Map_List[game->Now_Map].Item_List[i].type==1)
            {
                game->point+=Map_List[game->Now_Map].Item_List[i].value;
                Get_Point_Texture(game->point);
                Mix_PlayChannel(1,coin_sound,0);
            }
            if(Map_List[game->Now_Map].Item_List[i].type==2)
            {
                MC.undead=1;
                MC.time_end_undead=Now_time+10000;
                Mix_PlayChannel(1,get_shield_sound,0);
            }
            Map_List[game->Now_Map].Item_List[i].status=1;
        }
    }
    for(i=0;i<Map_List[game->Now_Map].Trap_List.size();i++)
    {
        if(MC.Pos.y+MC.Pos.h!=Map_List[game->Now_Map].Trap_List[i].first.y) continue;
        rect=Rect_With_Margin(Map_List[game->Now_Map].Trap_List[i].first,game->Margin);
        if(MC.Pos.x>rect.x && MC.Pos.x<rect.x+rect.w)
        {
            Map_List[game->Now_Map].Trap_List[i].second=1;
            if(MC.undead==0)
            {
                game->Phase=GAME_OVER;
                Mix_PlayChannel(1,game_over_sound,0);
            }
        }
    }
    for(i=0;i<Map_List[game->Now_Map].Obstacle.size();i++)
    {
        rect=Rect_With_Margin(Map_List[game->Now_Map].Obstacle[i].Pos,game->Margin);
        if(MC.Pos.x+MC.Pos.w>rect.x+10 && MC.Pos.x+MC.Pos.w<rect.x+rect.w)
        {
            if(Impact_Check(MC.Pos,rect)==false) continue;
            Map_List[game->Now_Map].Obstacle[i].status=1;
            Map_List[game->Now_Map].Obstacle[i].Impact_Time=SDL_GetTicks();
            Mix_PlayChannel(1,explosion_sound,0);
            if(MC.undead==0)
            {
                game->Phase=GAME_OVER;
                Mix_PlayChannel(1,game_over_sound,0);
            }
        }
    }
    return;
}
void Character_Move(Game_State *game,Input_State *input)
{
    if(MC.Pos.x+MC.Pos.w<=Margin_x || MC.Pos.y>=window_height)
    {
        game->Phase=GAME_OVER;
        Mix_PlayChannel(1,game_over_sound,0);
        return;
    }
    bool ok=on_earth(game->Now_Map,game->Margin);
    if(MC.IMG_num==9 || (ok==true && MC.status!=0))
    {
        MC.status=0;
        MC.IMG_num=-1;
    }
    MC.Pos=Get_Valid_Pos(0,MC.Pos,MC.Distan[0],game->Now_Map,game->Margin);
    if(MC.status!=0)
    {
        if(input->up==0) MC.Distan[2]=4;
        if(MC.status==1) MC.Pos=Get_Valid_Pos(1,MC.Pos,MC.Distan[1],game->Now_Map,game->Margin);
        if(MC.status==2) MC.Pos=Get_Valid_Pos(2,MC.Pos,MC.Distan[2],game->Now_Map,game->Margin);
        MC.IMG_num++;
        return;
    }
    if(ok==false)
    {
        MC.status=2;
        MC.IMG_num=0;
        MC.Pos=Get_Valid_Pos(2,MC.Pos,MC.Distan[2],game->Now_Map,game->Margin);
        return;
    }
    if(input->up>0 && input->pre_up==0)
    {
        MC.status=1;
        MC.IMG_num=0;
        MC.Distan[2]=1;
        Mix_PlayChannel(1,jump_sound,0);
        MC.Pos=Get_Valid_Pos(1,MC.Pos,MC.Distan[1],game->Now_Map,game->Margin);
        return;
    }
    MC.IMG_num++;
    return;
}

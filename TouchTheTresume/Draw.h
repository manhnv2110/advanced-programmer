SDL_Texture *Back_Ground;
SDL_Texture *Map_Texture[20];

void Draw_character(SDL_Texture *texture,SDL_Rect pos)
{
    pos.x-=Margin_x;
    SDL_RenderCopy(renderer,texture,NULL,&pos);
}
void Draw_Land(SDL_Rect rect)
{
    int i,j;
    SDL_Rect Unit_Pos;
    rect.h-=Land_Unit;
    rect.w-=Land_Unit;
    Unit_Pos.h=Land_Unit;
    Unit_Pos.w=Land_Unit;
    if(rect.h==0)
    {
        Unit_Pos.y=rect.y;
        for(i=rect.x;i<=rect.x+rect.w;i+=Land_Unit)
        {
            Unit_Pos.x=i;
            if(i==rect.x) SDL_RenderCopy(renderer,Map_Texture[10],NULL,&Unit_Pos);
            if(i!=rect.x && i!=rect.x+rect.w) SDL_RenderCopy(renderer,Map_Texture[11],NULL,&Unit_Pos);
            if(i==rect.x+rect.w) SDL_RenderCopy(renderer,Map_Texture[12],NULL,&Unit_Pos);
        }
        return;
    }
    for(i=rect.x;i<=rect.x+rect.w;i+=Land_Unit)
    {
        for(j=rect.y;j<=rect.y+rect.h;j+=Land_Unit)
        {
            Unit_Pos.x=i;
            Unit_Pos.y=j;
            if(i==rect.x && j==rect.y) SDL_RenderCopy(renderer,Map_Texture[1],NULL,&Unit_Pos);
            if(i==rect.x && j==rect.y+rect.h) SDL_RenderCopy(renderer,Map_Texture[7],NULL,&Unit_Pos);
            if(i==rect.x && j!=rect.y && j!=rect.y+rect.h) SDL_RenderCopy(renderer,Map_Texture[4],NULL,&Unit_Pos);

            if(j==rect.y && i!=rect.x && i!=rect.x+rect.w) SDL_RenderCopy(renderer,Map_Texture[2],NULL,&Unit_Pos);
            if(j!=rect.y && i!=rect.x && i!=rect.x+rect.w && j!=rect.y+rect.h) SDL_RenderCopy(renderer,Map_Texture[5],NULL,&Unit_Pos);
            if(j!=rect.y && i!=rect.x && i!=rect.x+rect.w && j==rect.y+rect.h) SDL_RenderCopy(renderer,Map_Texture[8],NULL,&Unit_Pos);

            if(i==rect.x+rect.w && j==rect.y) SDL_RenderCopy(renderer,Map_Texture[3],NULL,&Unit_Pos);
            if(i==rect.x+rect.w && j==rect.y+rect.h) SDL_RenderCopy(renderer,Map_Texture[9],NULL,&Unit_Pos);
            if(i==rect.x+rect.w && j!=rect.y && j!=rect.y+rect.h) SDL_RenderCopy(renderer,Map_Texture[6],NULL,&Unit_Pos);

        }
    }
    return;
}
bool Ok_To_Draw(SDL_Rect rect)
{
    if(rect.x+rect.w<0) return false;
    if(window_width<rect.x) return false;
    return true;
}
void Draw_Map(int vt,int next_vt,int margin)
{
    int i;
    SDL_Rect rect;
    SDL_RenderCopy(renderer,Back_Ground,NULL,NULL);
    //
    for(i=0;i<Map_List[vt].Ground.size();i++)
    {
        rect=Rect_With_Margin(Map_List[vt].Ground[i],margin-Margin_x);
        if(Ok_To_Draw(rect)==false) continue;
        Draw_Land(rect);
    }
    //
    for(i=0;i<Map_List[vt].Item_List.size();i++)
    {
        if(Map_List[vt].Item_List[i].status==1) continue;

        rect=Rect_With_Margin(Map_List[vt].Item_List[i].Pos,margin-Margin_x);
        if(Ok_To_Draw(rect)==false) continue;
        if(Map_List[vt].Item_List[i].type==1) SDL_RenderCopy(renderer,Coin,NULL,&rect);
        else SDL_RenderCopy(renderer,Shield,NULL,&rect);
    }
    //
    for(i=0;i<Map_List[vt].Trap_List.size();i++)
    {
        if(Map_List[vt].Trap_List[i].second==0) continue;

        rect=Rect_With_Margin(Map_List[vt].Trap_List[i].first,margin-Margin_x);
        if(Ok_To_Draw(rect)==false) continue;
        SDL_RenderCopy(renderer,Trap,NULL,&rect);
    }
    //
    for(i=0;i<Map_List[vt].Obstacle.size();i++)
    {
        rect=Rect_With_Margin(Map_List[vt].Obstacle[i].Pos,margin-Margin_x);
        if(Ok_To_Draw(rect)==false) continue;
        if(Map_List[vt].Obstacle[i].status==0) SDL_RenderCopy(renderer,Obs,NULL,&rect);
        else if(SDL_GetTicks()-Map_List[vt].Obstacle[i].Impact_Time<500) SDL_RenderCopy(renderer,Explosion,NULL,&rect);
    }

    for(i=0;i<Map_List[next_vt].Ground.size();i++)
    {
        rect=Rect_With_Margin(Map_List[next_vt].Ground[i],window_width+margin-Margin_x);
        if(Ok_To_Draw(rect)==false) continue;
        Draw_Land(rect);
    }
    //
    for(i=0;i<Map_List[next_vt].Item_List.size();i++)
    {
        rect=Rect_With_Margin(Map_List[next_vt].Item_List[i].Pos,window_width+margin-Margin_x);
        if(Ok_To_Draw(rect)==false) continue;
        if(Map_List[next_vt].Item_List[i].type==1) SDL_RenderCopy(renderer,Coin,NULL,&rect);
        else SDL_RenderCopy(renderer,Shield,NULL,&rect);
    }
    //
    for(i=0;i<Map_List[next_vt].Trap_List.size();i++)
    {
        rect=Rect_With_Margin(Map_List[next_vt].Trap_List[i].first,window_width+margin-Margin_x);
        if(Ok_To_Draw(rect)==false) continue;
        SDL_RenderCopy(renderer,Trap,NULL,&rect);
    }
    //
    for(i=0;i<Map_List[next_vt].Obstacle.size();i++)
    {
        rect=Rect_With_Margin(Map_List[next_vt].Obstacle[i].Pos,window_width+margin-Margin_x);
        if(Ok_To_Draw(rect)==false) continue;
        SDL_RenderCopy(renderer,Obs,NULL,&rect);
    }
    return;
}
void Draw_Shiled_Bar()
{
    int time_left=MC.time_end_undead-SDL_GetTicks();
    if(time_left<=0) return;
    SDL_Rect rect;
    rect.x=500;
    rect.y=0;
    rect.w=900;
    rect.h=100;
    SDL_RenderCopy(renderer,Amor_Bar,NULL,&rect);
    rect.x=678;
    rect.y=0;
    rect.w=time_left*675/10000;
    rect.h=100;
    SDL_RenderCopy(renderer,Amor,NULL,&rect);
    return;
}
void Draw_Game_Play(Game_State *game,Input_State *input)
{
    Draw_Map(game->Now_Map,game->Next_Map,game->Margin);
    Draw_character(MC.Mc_Textuter[MC.status][MC.IMG_num],MC.Pos);
    Get_Point_Texture(game->point);
    SDL_Rect rect;
    rect={0,0,200,100};
    SDL_RenderCopy(renderer,Point_Bar,NULL,&rect);
    rect={55,15,125,60};
    SDL_RenderCopy(renderer,Point,NULL,&rect);
    Draw_Shiled_Bar();
    rect={1700,0,100,100};
    if(In_Rect(rect,input->event.motion.x,input->event.motion.y)==false) SDL_RenderCopy(renderer,Play1,NULL,&rect);
    else
    {
        SDL_RenderCopy(renderer,Play2,NULL,&rect);
        if(input->event.type==SDL_MOUSEBUTTONUP)
        {
            game->Phase=GAME_PAUSE;
            game->Delay_Time=SDL_GetTicks();
        }
    }
    return;
}

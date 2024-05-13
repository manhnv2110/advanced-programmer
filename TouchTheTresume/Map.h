struct Item
{
    int value,status,type;
    SDL_Rect Pos;
};
struct OBStac
{
    int Impact_Time,status;
    SDL_Rect Pos;
};
struct Map
{
    vector<SDL_Rect> Ground;
    vector<Item> Item_List;
    vector<pair<SDL_Rect,int> > Trap_List;
    vector<OBStac> Obstacle;
};
Map Create_Map1()
{
    Map NewMap;

    NewMap.Ground.push_back({0,600,30*Land_Unit,Land_Unit});

    NewMap.Item_List.push_back({100,0,1,{300,400,80,80}});
    NewMap.Item_List.push_back({100,0,1,{400,400,80,80}});
    NewMap.Item_List.push_back({100,0,1,{500,400,80,80}});
    NewMap.Item_List.push_back({100,0,1,{600,400,80,80}});


    NewMap.Item_List.push_back({100,0,1,{800,300,80,80}});
    NewMap.Item_List.push_back({100,0,1,{900,300,80,80}});
    NewMap.Item_List.push_back({100,0,1,{1000,300,80,80}});
    NewMap.Item_List.push_back({100,0,1,{1100,300,80,80}});

    NewMap.Item_List.push_back({100,0,1,{1300,500,80,80}});
    NewMap.Item_List.push_back({100,0,1,{1400,450,80,80}});
    NewMap.Item_List.push_back({100,0,1,{1500,400,80,80}});
    NewMap.Item_List.push_back({100,0,1,{1600,350,80,80}});
    return NewMap;
}
Map Create_Map2()
{
    Map NewMap;

    NewMap.Ground.push_back({0,600,10*Land_Unit,3*Land_Unit});
    NewMap.Ground.push_back({900,600,10*Land_Unit,3*Land_Unit});


    NewMap.Item_List.push_back({100,0,1,{50,400,80,80}});
    NewMap.Item_List.push_back({100,0,1,{150,400,80,80}});
    NewMap.Item_List.push_back({100,0,1,{250,400,80,80}});
    NewMap.Item_List.push_back({100,0,1,{350,400,80,80}});

    NewMap.Item_List.push_back({100,0,1,{1050,400,80,80}});
    NewMap.Item_List.push_back({100,0,1,{1150,400,80,80}});
    NewMap.Item_List.push_back({100,0,1,{1250,400,80,80}});
    NewMap.Item_List.push_back({100,0,1,{1350,400,80,80}});

    NewMap.Trap_List.push_back({{400,600,60,60},1});
    NewMap.Trap_List.push_back({{1000,600,60,60},1});
    NewMap.Trap_List.push_back({{1400,600,60,60},1});

    return NewMap;
}
Map Create_Map3()
{
    Map NewMap;
    NewMap.Ground.push_back({0,600,8*Land_Unit,3*Land_Unit});
    NewMap.Ground.push_back({480,480,2*Land_Unit,5*Land_Unit});

    NewMap.Ground.push_back({600,600,8*Land_Unit,3*Land_Unit});
    NewMap.Ground.push_back({1080,480,2*Land_Unit,5*Land_Unit});

    NewMap.Ground.push_back({1200,600,8*Land_Unit,3*Land_Unit});
    NewMap.Ground.push_back({1680,480,2*Land_Unit,5*Land_Unit});

    NewMap.Item_List.push_back({100,0,1,{100,400,80,80}});
    NewMap.Item_List.push_back({0,0,2,{480,400,80,80}});
    NewMap.Item_List.push_back({100,0,1,{780,400,80,80}});
    NewMap.Item_List.push_back({100,0,1,{1080,400,80,80}});
    NewMap.Item_List.push_back({100,0,1,{1380,400,80,80}});
    NewMap.Item_List.push_back({100,0,1,{1680,400,80,80}});


    NewMap.Trap_List.push_back({{400,600,60,60},1});
    NewMap.Trap_List.push_back({{1000,600,60,60},1});

    NewMap.Obstacle.push_back({0,0,{800,540,60,60}});
    NewMap.Obstacle.push_back({0,0,{300,540,60,60}});
    NewMap.Obstacle.push_back({0,0,{1300,540,60,60}});

    return NewMap;
}
Map Create_Map4()
{
    Map NewMap;
    NewMap.Ground.push_back({0,600,5*Land_Unit,3*Land_Unit});
    NewMap.Ground.push_back({0,100,2*Land_Unit,5*Land_Unit});
    NewMap.Ground.push_back({300,480,2*Land_Unit,5*Land_Unit});
    NewMap.Ground.push_back({600,420,6*Land_Unit,2*Land_Unit});
    NewMap.Ground.push_back({1200,600,6*Land_Unit,2*Land_Unit});

    NewMap.Item_List.push_back({100,0,1,{50,400,80,80}});
    NewMap.Item_List.push_back({100,0,1,{150,400,80,80}});
    NewMap.Item_List.push_back({100,0,1,{250,400,80,80}});
    NewMap.Item_List.push_back({100,0,1,{350,400,80,80}});

    NewMap.Item_List.push_back({0,0,2,{1100,340,80,80}});

    NewMap.Item_List.push_back({100,0,1,{1300,400,80,80}});
    NewMap.Item_List.push_back({100,0,1,{1400,400,80,80}});
    NewMap.Item_List.push_back({100,0,1,{1500,400,80,80}});
    NewMap.Item_List.push_back({100,0,1,{1600,400,80,80}});

    NewMap.Trap_List.push_back({{1200,600,60,60},1});

    NewMap.Obstacle.push_back({0,0,{700,360,60,60}});

    return NewMap;
}
Map Create_Map5()
{
    Map NewMap;
    NewMap.Ground.push_back({0,600,3*Land_Unit,3*Land_Unit});
    NewMap.Ground.push_back({300,600,3*Land_Unit,3*Land_Unit});
    NewMap.Ground.push_back({600,600,3*Land_Unit,3*Land_Unit});
    NewMap.Ground.push_back({900,600,3*Land_Unit,3*Land_Unit});
    NewMap.Ground.push_back({1200,600,3*Land_Unit,3*Land_Unit});
    NewMap.Ground.push_back({1500,600,3*Land_Unit,3*Land_Unit});

    NewMap.Item_List.push_back({100,0,1,{300,400,80,80}});
    NewMap.Item_List.push_back({100,0,1,{600,400,80,80}});
    NewMap.Item_List.push_back({100,0,1,{900,400,80,80}});
    NewMap.Item_List.push_back({100,0,1,{1200,400,80,80}});
    NewMap.Item_List.push_back({100,0,1,{1500,400,80,80}});

    NewMap.Trap_List.push_back({{420,600,60,60},1});
    NewMap.Trap_List.push_back({{1020,600,60,60},1});
    NewMap.Trap_List.push_back({{1620,600,60,60},1});
    return NewMap;
}
Map Create_Map6()
{
    Map NewMap;
    NewMap.Ground.push_back({0,600,30*Land_Unit,3*Land_Unit});
    NewMap.Ground.push_back({180,480,24*Land_Unit,Land_Unit});
    NewMap.Ground.push_back({360,360,18*Land_Unit,Land_Unit});
    NewMap.Ground.push_back({540,240,12*Land_Unit,Land_Unit});

    NewMap.Item_List.push_back({100,0,1,{50,520,80,80}});
    NewMap.Item_List.push_back({100,0,1,{250,400,80,80}});
    NewMap.Item_List.push_back({100,0,1,{400,280,80,80}});

    NewMap.Item_List.push_back({100,0,1,{1300,280,80,80}});
    NewMap.Item_List.push_back({100,0,1,{1500,400,80,80}});
    NewMap.Item_List.push_back({100,0,1,{1700,520,80,80}});

    NewMap.Obstacle.push_back({0,0,{700,180,60,60}});
    NewMap.Obstacle.push_back({0,0,{1000,180,60,60}});
    return NewMap;
}
Map Map_List[]=
{
    Create_Map1(),
    Create_Map2(),
    Create_Map3(),
    Create_Map4(),
    Create_Map5(),
    Create_Map6(),
};

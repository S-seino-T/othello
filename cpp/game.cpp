#include "game.hpp"

game::game()
    :now_board(make_shared<board>())
    ,log()
    ,p(desc::black)
    ,p1(nullptr)
    ,p2(nullptr)
{

}

game::~game()
{

}

bool game::Initialize()
{
    bool flag=true;
    while(flag)
    {
        string input;
        cout<<"オセロ"<<endl;
        cout<<"1:Player vs Player  2:Player vs Enemy  3:Enemy vs Enemy"<<endl<<"E: End"<<endl<<"選択 > "<<flush;
        cin>>input;

        

        random_device rnd;
        board tmp;
        desc t;

        if(rnd()%2==0)
        {
            t=desc::black;
        }
        else
        {
            t=desc::white;
        }

        flag=false;
        if(input=="1")
        {
            p1=make_unique<player>(t);
            p2=make_unique<player>(tmp.opponent(t));
        }
        else if(input=="2")
        {
            p1=make_unique<player>(t);
            p2=make_unique<random_enemy>(tmp.opponent(t));
        }
        else if(input=="3")
        {
            p1=make_unique<random_enemy>(t);
            p2=make_unique<random_enemy>(tmp.opponent(t));
        }
        else if(input=="E")
        {
            cout<<"ShutDown"<<endl;
            return false;
        }
        else
        {
            flag=true;
            cout<<"invalid input."<<endl;
        }
    }
    return true;
}

void game::Loop()
{
    bool flag=true;
    while(flag)
    {
        flag=OneLoop();
    }
}

bool game::OneLoop()
{
    now_board->print_placeable(p);
    if(!now_board->is_playable()) return false;
    co ret;
    shared_ptr<play> tmp;

    if(p1->getter()==p)
    {
        tmp=p1;
    }
    else
    {
        tmp=p2;
    }

    if(!now_board->is_placeable(tmp->getter()))
    {
        p=now_board->opponent(p);
        return true;
    }

    bool fflag=false;

    ret=tmp->put_desc(now_board);
    if(now_board->is_turnover(ret.row,ret.column,p)) fflag=true;

    now_board->flip(ret.row,ret.column,p);
    if(fflag) p=now_board->opponent(p);

    return true;
}

void game::Terminate()
{
    int b_count=0;
    int w_count=0;
    for(int i=0;i<8;++i)
    {
        for(int j=0;j<8;++j)
        {
            if(now_board->get_desc(i,j)==desc::black)
            {
                b_count++;
            }
            else if(now_board->get_desc(i,j)==desc::white)
            {
                w_count++;
            }
        }
    }
    cout<<"黒："<<b_count<<" ,白："<<w_count<<endl;
    if(b_count>w_count)
    {
        cout<<"黒！"<<endl;
    }
    else if(w_count>b_count)
    {
        cout<<"白！"<<endl;
    }
    else
    {
        cout<<"Draw."<<endl;
    }
}

void game::Game()
{
    if(!Initialize()) return;

    Loop();

    Terminate();
    return;
}
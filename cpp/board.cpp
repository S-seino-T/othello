#include "board.hpp"

board::board()
    : b(100,desc::wall)
{
    
    for(int k=0;k<100;++k) b[k]=desc::wall;
    for(int i=0;i<8;++i)
    {
        for(int j=0;j<8;++j)
        {
            if((i==3&&j==3)||(i==4&&j==4))
            {
                at(i,j)=desc::black;
            }
            else if((i==3&&j==4)||(i==4&&j==3))
            {
                at(i,j)=desc::white;
            }
            else
            {
                at(i,j)=desc::space;
            }
        }
    }
}

board::~board()
{

}

desc& board::at(int row,int column)
{
    return b.at(10*(row+1)+column+1);
}

desc board::get_desc(int row, int column) const
{
    return b.at(10*(row+1)+column+1);
}

void board::print() const
{
    // system("clear");
    cout<<" | 0 1 2 3 4 5 6 7 | "<<endl;
    cout<<"-+-----------------+-"<<endl;
    for(int i=0;i<8;++i)
    {
        cout<<i<<"|"<<flush;
        for(int j=0;j<8;++j)
        {
            desc d = get_desc(i,j);
            if(d==desc::black)
            {
                cout<<" ○"<<flush;
            }
            else if(d==desc::white)
            {
                cout<<" ●"<<flush;
            }
            else
            {
                cout<<" -"<<flush;
            }
        }
        cout<<" |"<<endl;
    }
    cout<<"-+-----------------+-"<<endl;
}

void board::print_placeable(desc player) const
{
    // system("clear");
    cout<<" | 0 1 2 3 4 5 6 7 | "<<endl;
    cout<<"-+-----------------+-"<<endl;
    for(int i=0;i<8;++i)
    {
        cout<<i<<"|"<<flush;
        for(int j=0;j<8;++j)
        {
            desc d = get_desc(i,j);
            if(d==desc::black)
            {
                cout<<" ○"<<flush;
            }
            else if(d==desc::white)
            {
                cout<<" ●"<<flush;
            }
            else if(is_turnover(i,j,player))
            {
                cout<<" ×"<<flush;
            }
            else
            {
                cout<<" ･"<<flush;
            }
        }
        cout<<" |"<<endl;
    }
    cout<<"-+-----------------+-"<<endl;
}

bool board::is_turnover(int row, int column, desc player) const
{
    int dir[8][2]={{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1}};

    for(auto& s : dir)
    {
        // cout<<"is_turnover:"<<s[0]<<s[1]<<endl;
        if(is_turnover_onedir(row,column,s[0],s[1],player)) return true;
    }

    return false;
}

bool board::is_turnover_onedir(int row, int column, int rdir, int cdir, desc player) const
{
    if(get_desc(row,column)!=desc::space) return false;
    
    if(get_desc(row+rdir,column+cdir)!=opponent(player)) return false;
    
    for(int i=row+rdir,j=column+cdir; get_desc(i,j)!=desc::wall; i+=rdir,j+=cdir)
    {
        // cout<<"is_turnover_onedir:"<<i<<j<<endl;
        if(get_desc(i,j)==player)
        {
            return true;
        }
        else if(get_desc(i,j)==opponent(player))
        {
            continue;
        }
        else
        {
            break;
        }
    }
    
    return false;
}

desc board::opponent(desc player) const
{
    if(player==desc::black)
    {
        return desc::white;
    }
    else if(player==desc::white)
    {
        return desc::black;
    }
    else
    {
        cout<<"プレイヤー以外の石が参照されました"<<endl;
        std::exit(1);
    }
}

desc board::player(desc player) const
{
    if(player==desc::black)
    {
        return desc::black;
    }
    else if(player==desc::white)
    {
        return desc::white;
    }
    else
    {
        cout<<"プレイヤー以外の石が参照されました"<<endl;
        std::exit(1);
    }
}

bool board::is_placeable(desc player) const
{
    for(int i=0;i<8;++i)
    {
        for(int j=0;j<8;++j)
        {
            if(is_turnover(i,j,player)) return true;
        }
    }

    return false;
}

void board::flip_onedir(int row, int column, int rdir, int cdir, desc player)
{
    for(int i=row+rdir,j=column+cdir; get_desc(i,j)!=this->player(player); i+=rdir,j+=cdir)
    {
        at(i,j)=this->player(player);
    }
}

void board::flip(int row, int column, desc player)
{
    if(!is_turnover(row, column, player))
    {
        cout<<"そこに石は置けないよ！"<<endl;
        return;
    }
    
    int dir[8][2]={{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1}};

    for(auto& s : dir)
    {
        // cout<<"is_turnover:"<<s[0]<<s[1]<<endl;
        if(is_turnover_onedir(row,column,s[0],s[1],player)) flip_onedir(row,column,s[0],s[1],player);
    }
    at(row,column) = this->player(player);
}

bool board::is_playable() const
{
    if(is_placeable(desc::black) || is_placeable(desc::white)) return true;

    return false;
}
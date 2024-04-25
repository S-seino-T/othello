#include "play.hpp"

co::co()
    : row(0)
    ,column(0)
{

}

co::~co()
{

}

desc play::getter() const
{
    if(m_desc==desc::black)
    {
        return desc::black;
    }
    else
    {
        return desc::white;
    }
}

play::play(desc d)
    : m_desc{d}
{

}

play::~play()
{

}

player::player(desc d)
    : play(d)
{

}

random_enemy::random_enemy(desc d)
    : play(d)
{
    
}

co player::put_desc(shared_ptr<board> b)
{
    string input;
    regex re{R"(\(|\)|,|\t| |)"};
    int num = 0;

    while(true)
    {
        cout<<"座標(row, column):"<<flush;
        cin>>input;
        // string c = regex_replace(input,re,"");
        string c=input;
        cout<<c<<endl;
        
        try
        {
            num=stoi(c);
        }
        catch(const std::exception& e)
        {
            std::cerr << "数字を入力してね"<<endl;
            continue;
        }
        if(num>=0 && num<=77)
        {
            break;
        }
        std::cout<<"座標を入力してね：(0, 0) ~ (7, 7)"<<endl;
    }
    
    co ret;
    ret.row = num/10;
    ret.column = num%10;
    return ret;
}

co random_enemy::put_desc(shared_ptr<board> b)
{
    vector<co> placeable_co;
    for(int i=0;i<8;++i)
    {
        for(int j=0;j<8;++j)
        {
            if(b->is_turnover(i,j,getter()))
            {
                co tmp;
                tmp.row=i;
                tmp.column=j;
                placeable_co.push_back(tmp);
            } 
        }
    }
    random_device rnd;
    int idx= rnd() % placeable_co.size();
    return placeable_co[idx];
}

#include "AI.hpp"

eval_play::eval_play(desc d)
    : play(d)
    , eval_sheet{
        {30,-12,5,-1,-1,5,-12,30}
        ,{-12,-15,-3,-3,-3,-3,-15,-12}
        ,{5,-3,1,0,0,1,-3,5}
        ,{-1,-3,0,-1,-1,0,-3,-1}
        ,{-1,-3,0,-1,-1,0,-3,-1}
        ,{5,-3,1,0,0,1,-3,5}
        ,{-12,-15,-3,-3,-3,-3,-15,-12}
        ,{30,-12,5,-1,-1,5,-12,30}
        }
{
    
}

int eval_play::at(int r,int c)
{
    return eval_sheet.at(r).at(c);
}

co eval_play::put_desc(shared_ptr<board> b)
{
    return put_desc_eval(b);
}

once_ahead_enemy::once_ahead_enemy(desc d)
    :eval_play(d)
    ,score(8,vector<int>(8,0))
{

}

void once_ahead_enemy::eval(shared_ptr<board> b)
{
    for(int i=0;i<8;++i)
    {
        for(int j=0;j<8;++j)
        {
            if(b->is_turnover(i,j,getter()))
            {
                board tmp = *b.get();
                tmp.flip(i,j,getter());
                score.at(i).at(j)=eval_count(tmp);
            }
        }
    }
}

int once_ahead_enemy::eval_count(board b)
{
    int scr=0;
    // cout<<"in:eval_count";
    // b.print();
    for(int i=0;i<8;++i)
    {
        for(int j=0;j<8;++j)
        {
            if(b.get_desc(i,j)==getter())
            {
                scr+=at(i,j);
            }
            else if(b.get_desc(i,j)==b.opponent(getter()))
            {
                scr-=at(i,j);
            }
        }
    }
    // cout<<scr;
    return scr;
}

co once_ahead_enemy::put_desc_eval(shared_ptr<board> b)
{
    eval(b);
    co coord;
    coord.row=-1;
    coord.column=0;
    tuple<co,int> max=make_tuple(coord,0);
    for(int i=0;i<8;++i)
    {
        for(int j=0;j<8;++j)
        {
            if(b->is_turnover(i,j,getter()) && (at(i,j)>get<1>(max) || get<0>(max).row==-1))
            {
                coord.row=i;
                coord.column=j;
                max=make_tuple(coord,score.at(i).at(j));
            }
        }
    }
    // string io;
    // cin>>io;
    // cout<<get<0>(max).row<<get<0>(max).column<<endl;
    return get<0>(max);
}

negamax_enemy::negamax_enemy(desc d)
    :eval_play(d)
{

}

negamax_enemy::~negamax_enemy()
{

}

co negamax_enemy::put_desc_eval(shared_ptr<board> b)
{
    int alpha = -250,beta = 250;
    co ret;
    for(int i=0;i<8;++i)
    {
        for(int j=0;j<8;++j)
        {
            board tp = *b.get();
            if(tp.is_turnover(i,j,getter()))
            {
                tp.flip(i,j,getter());
                int scr = -eval(tp,tp.opponent(getter()),dp - 1,-beta,-alpha);

                if(alpha < scr){
                    alpha=scr;
                    ret.row=i;
                    ret.column=j;
                }
            }
        }
    }
    // cout<<"座標：("<<ret.row<<", "<<ret.column<<")"<<endl;
    // debug(5);
    return ret;
}

int negamax_enemy::eval(board b,desc d,int depth,int alpha,int beta)
{
    if(depth==0) return eval_count(b,d);

    if(!b.is_playable()) return eval_count(b,d);

    if(!b.is_placeable(d)) return -eval(b,b.opponent(d),depth,-beta,-alpha);

    int max_=-250;
    for(int i=0;i<8;++i)
    {
        for(int j=0;j<8;++j)
        {
            board tmp = b;
            if(tmp.is_turnover(i,j,d))
            {
                tmp.flip(i,j,d);
                int re = -eval(tmp,tmp.opponent(d),depth-1,-beta,-alpha);
                if(re>=beta) return re;
                alpha=max(alpha,re);
                max_ = max(max_,re);
            }
        }
    }
    return max_;
}

int negamax_enemy::eval_count(board b,desc d)
{
    int ret=0;
    for(int i=0;i<8;++i)
    {
        for(int j=0;j<8;++j)
        {
            if(b.get_desc(i,j)==d)
            {
                ret+=at(i,j);
            }
            else if(b.get_desc(i,j)==b.opponent(d))
            {
                ret-=at(i,j);
            }
        }
    }
    return ret;
}
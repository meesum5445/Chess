#include<iostream>
using namespace std;
//......................
#include"utilities.h"
#include"piece.h"
#include"board.h"
#include"king.h"
#include"chess.h"
//header file to be defined
#include"player.h"
player::player(chess *C)
{
    this->C = C;
}
loc player::player_move()
{   
    loc temp;
    cout << "Enter x coordinate:";
    cin >> temp.x;
    cout << "Enter y coordinate:";
    cin >> temp.y;
    return temp;
};
loc player::king_loc()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            king* ptr = dynamic_cast<king*>(this->C->B->Piece[i][j]);
            if (ptr && ptr->Player==this)
            {
                return { i,j };
            }
        }
    }
}
bool player::check()
{
    loc king_location=(this == this->C->P[0])   ?   this->C->P[1]->king_loc()   :    this->C->P[0]->king_loc();    //will find enemy king location.
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (this->C->valid_source_move({ i,j }))
            {
                if (this->C->valid_destination_move(king_location) && this->C->B->Piece[i][j]->valid_move({ i,j }, king_location))
                    return true;
            }
            
        }
    }
    return false;
}
bool player::self_check()
{
    this->C->turn_change();
    bool self_check= this->C->turn->check();
    this->C->turn_change();
    return self_check;
}
bool player::blocked()
{
    this->C->turn_change();
    for (int s = 0; s < 8; s++)
    {
        for (int o = 0; o < 8; o++)
        {
            if(this->C->valid_source_move({ s,o }))
            {               
                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {                  
                        if(this->C->valid_overall_destination({ s,o }, { i,j }))
                        {
                            this->C->turn_change();
                            return false;
                        }
                    }
                }
            }
        }
    }
    
    this->C->turn_change();
    return true;
}
bool player::will_getinto_check(loc src,loc des)
{
    piece* temp{};
    temp = this->C->B->Piece[des.x][des.y];        
    this->C->move(src, des);
    //....................................
    if (this->self_check())
    {
        this->C->move(des,src);
        this->C->B->Piece[des.x][des.y] = temp;
        return true;
    }

    this->C->move(des, src);
    this->C->B->Piece[des.x][des.y] = temp;

    return false;
}
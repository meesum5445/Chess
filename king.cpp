#include<iostream>
using namespace std;
#include"utilities.h"
#include"player.h"
#include"piece.h"
#include"board.h"
#include"chess.h"
//header file to be defined
#include"king.h"   
king::king(player* P, board* B) :piece(P, B)
{

}
void king::print()
{
    if(this->Player==this->B->C->P[0])
        cout << "K";
    else
        cout << "k";
}
bool king::valid_move(loc src, loc des)
{
    if (abs(src.x - des.x) > 1 || abs(src.y - des.y) > 1)
        return false;
    return true;
}

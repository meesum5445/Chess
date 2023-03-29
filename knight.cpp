#include<iostream>
using namespace std;
//.....................
#include"utilities.h"
#include"player.h"
#include"piece.h"
#include"board.h"
#include"chess.h"
//header file to be defined
#include"knight.h"
knight::knight(player* P, board* B) :piece(P, B)
{

}
void knight::print()
{
    if (this->Player == this->B->C->P[0])
        cout << "N";
    else
        cout << "n";
}
bool knight::valid_move(loc src, loc des)
{
    if ((abs(src.y - des.y) == 1 && abs(des.x - src.x) == 2) || (abs(src.y - des.y) == 2 && abs(des.x - src.x) == 1))
        return true;
    return false;
}   
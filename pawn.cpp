#include<iostream>
using namespace std;
//.....................
#include"utilities.h"
#include"player.h"
#include"piece.h"
#include"board.h"
#include"chess.h"
//header file to be defined
#include"pawn.h"

pawn::pawn(player* P, board* B) :piece(P, B)
{

}
void pawn::print()
{
    if (this->Player == this->B->C->P[0])
        cout << "P";
    else
        cout << "p";
}
bool pawn::valid_move(loc src, loc des)
{
    board* temp = this->B;   
    //................................
    int difference;
    if (this->Player == this->B->C->P[0])
    {
        difference = des.x - src.x;
    }
    else
    {
        difference = src.x-des.x;
    }
    if (abs(src.y - des.y) == 1 && difference == 1)
    {
            if(this->B->Piece[des.x][des.y]!=nullptr)
                return true;
            return false;
    }
    //..................
    if (src.y == des.y && this->B->Piece[des.x][des.y] == nullptr)
    {
        if (first_time)
        {
            if (difference <= 2)
                return true;
        }
        else
        {
            if (difference == 1)
                return true;
        }
    }
    return false;
}
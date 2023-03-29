#include <iostream>
#include <string.h>
using namespace std;
//..................
#include"utilities.h"
#include"player.h"
#include"board.h"
#include"piece.h"
#include"chess.h"
//header file to be defined
#include"rook.h"
rook::rook(player* P, board* B) :piece(P, B)
{

}
void rook::print()
{
    if (this->Player == this->B->C->P[0])
        cout << "R";
    else
        cout << "r";
}
bool rook::valid_move(loc src, loc des)
{

    if (src.x == des.x)
    {
        for (int i = 1; i < abs(des.y-src.y); i++)
        {
            if (src.y > des.y)
            {
                if (this->B->Piece[src.x][src.y - i] != nullptr)
                    return false;
            }
            else
            {
                if (this->B->Piece[src.x][src.y + i] != nullptr)
                    return false;
            }
        }
        return true;
    }
    else if (src.y == des.y)
    {
        for (int i = 1; i < abs(des.x - src.x); i++)
        {
            if (src.x > des.x)
            {
                if (this->B->Piece[src.x-i][src.y] != nullptr)
                    return false;
            }
            else
            {
                if (this->B->Piece[src.x+i][src.y] != nullptr)
                    return false;
            }
        }
        return true;
    }
    return false;
}
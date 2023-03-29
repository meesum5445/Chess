#include<iostream>
using namespace std;
//.....................
#include"utilities.h"
#include"player.h"
#include"piece.h"
#include"board.h"
#include"chess.h"
//header file to be defined
#include"queen.h"

queen::queen(player* P, board* B) :piece(P, B)
{

}
void queen::print()
{
    if (this->Player == this->B->C->P[0])
        cout << "Q";
    else
        cout << "q";
}
bool queen::valid_move(loc src, loc des)
{
    if (abs(src.x - des.x) == abs(src.y - des.y))
    {
        int diffirence = abs(src.x - des.x);

        for (int i = 1; i < diffirence; i++)
        {
            if (des.x > src.x && des.y > src.y)
            {
                if (this->B->Piece[src.x + i][src.y + i] != nullptr)
                    return false;
            }
            else if (des.x < src.x && des.y > src.y)
            {
                if (this->B->Piece[src.x - i][src.y + i] != nullptr)
                    return false;
            }
            else if (des.x < src.x && des.y < src.y)
            {
                if (this->B->Piece[src.x - i][src.y - i] != nullptr)
                    return false;
            }
            else
            {
                if (this->B->Piece[src.x + i][src.y - i] != nullptr)
                    return false;
            }
        }
        return true;
    }
    else if (src.x == des.x)
    {
        for (int i = 1; i < abs(des.y - src.y); i++)
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
                if (this->B->Piece[src.x - i][src.y] != nullptr)
                    return false;
            }
            else
            {
                if (this->B->Piece[src.x + i][src.y] != nullptr)
                    return false;
            }
        }
        return true;
    }
    return false;
}   
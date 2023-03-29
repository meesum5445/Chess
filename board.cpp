#include<iostream>
using namespace std;
//.................
#include"utilities.h"
#include"player.h"
#include"piece.h"
#include"king.h"
#include"queen.h"
#include"bishop.h"
#include"knight.h"
#include"rook.h"
#include"pawn.h"
#include"chess.h"
//header file to be defined
#include"board.h"
void board::delete_dynamically_allocate_memory(piece*** state)
{
    for (int i = 0; i < 8; i++)
    {
        delete[] state[i];
    }
    delete[] state;
}
board::board()
{

}
void board::init(chess* C)
{
    this->C = C;
    //...............................
    this->Piece = new piece * *[8] {};
    for (int i = 0; i < 8; i++)
        this->Piece[i] = new piece * [8] {};
    //...............................   
   this->Piece[0][0] = new rook(this->C->P[0], this);
    this->Piece[0][1] = new knight(this->C->P[0], this);
    this->Piece[0][2] = new bishop(this->C->P[0], this);
    this->Piece[0][3] = new king(this->C->P[0], this);
    this->Piece[0][4] = new queen(this->C->P[0], this);
    this->Piece[0][5] = new bishop(this->C->P[0], this);
    this->Piece[0][6] = new knight(this->C->P[0], this);
    this->Piece[0][7] = new rook(this->C->P[0], this);
    for (int i = 0; i < 8; i++)
    {
        this->Piece[1][i] = new pawn(this->C->P[0], this);
    }
    ////..............................
   for (int i = 0; i < 8; i++)
    {
        this->Piece[6][i] = new pawn(this->C->P[1], this);
    }
    this->Piece[7][0] = new rook(this->C->P[1], this);
    this->Piece[7][1] = new knight(this->C->P[1], this);
    this->Piece[7][2] = new bishop(this->C->P[1], this);
    this->Piece[7][3] = new king(this->C->P[1], this);
    this->Piece[7][4] = new queen(this->C->P[1], this);
    this->Piece[7][5] = new bishop(this->C->P[1], this);
    this->Piece[7][6] = new knight(this->C->P[1], this);
    this->Piece[7][7] = new rook(this->C->P[1], this);
    //................
}
void board::print()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (this->Piece[i][j] == nullptr)
                cout << " _ ";
            else
            {
                cout << " ";
                this->Piece[i][j]->print();
                cout << " ";
            }
        }
        cout << endl;
    }
}

board::~board()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            delete Piece[i][j];
        }
    }
    delete_dynamically_allocate_memory(Piece);
}

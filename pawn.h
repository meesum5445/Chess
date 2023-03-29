#pragma once
//....Forward Declarations....
struct loc;
class player;
class piece;
class board;
//......................
class pawn:public piece
{
    private:
        
    public:
        pawn(player*,board*);         // Constructor which will initiate bishop with its player and board on which it shall be placed.
        void print();                 // It shall print this piece
        bool valid_move(loc, loc);    // This function shall take position (row,col) as parameter and return true or false depending on legality of move and Bishop
};

   
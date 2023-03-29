#pragma once                // This file cant be included more than one time in one file while linking. 
//....Forward Declarations....
struct loc;
class player;
class piece;
class chess;
//.......................
class board
{    
public:
    static void delete_dynamically_allocate_memory(piece*** state);
    chess* C{};             // Board is linked to chess class(controller class) through this pointer.
    piece*** Piece{};       // Its a 2D array of pointers of pieces class ,pointing toward each type of piece (as they as inherited by piece class).
    board();                // default constructor
    void init(chess*);      // This method will initialize board and place pieces on it.
    void print();           // It will print whole board.
    ~board();
};
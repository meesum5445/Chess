#include <iostream>
#include <string>
#include<stack>
using namespace std;
//............................
#include"utilities.h"
#include"player.h"
#include"piece.h"
#include"board.h"
#include"pawn.h"
#include"queen.h";
#include"knight.h";
#include"rook.h";
#include"bishop.h";
#include"king.h"
//header file to be defined
#include"chess.h"

void chess::save(stack<piece***>&stack)
{
    piece*** temp;         //creating a *** temp pointer to create a board structure of single * pointer.
    temp = new piece**[8];          // memory allocation of array of ** pointer.
    for (int i = 0; i < 8; i++)
    {
        temp[i] = new piece * [8];          // memory allocation of array of * pointer on each ** pointer.
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            temp[i][j] = this->B->Piece[i][j];           // copying addresses of all pieces from original board structure to this temp .
        }
    }
    stack.push(temp);           //pushing board to vector of of board structure stack.
}
void chess::undo_redo(stack<piece***>& stack)
{
    piece***state=stack.top();
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            this->B->Piece[i][j] = state[i][j];
        }
    }
    board::delete_dynamically_allocate_memory(state);
    stack.pop();
}
void chess::maintaining_first_time_movement()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (this->B->Piece[i][j])
            {
                if (this->B->Piece[i][j]->stack_number_before_first_move == states_for_undo.size())
                {
                    this->B->Piece[i][j]->first_time = true;
                }
                else
                    this->B->Piece[i][j]->first_time = false;
            }
        }
    }
}
void chess::replace_by_promotion(loc loc_of_piece)
{
    pawn* ptr = dynamic_cast<pawn*>(this->B->Piece[loc_of_piece.x][loc_of_piece.y]);
    if (ptr)
    {
        if (loc_of_piece.x==0 || loc_of_piece.x == 7)
        {
            int choice{};
            cout << "(1 for queen, 2 for bishop,3 for rook, 4 for knight)";
            cin >> choice;
            if (choice == 1)
            {
                this->B->Piece[loc_of_piece.x][loc_of_piece.y] = new queen(ptr->Player, this->B);
            }
            else if (choice == 2)
            {
                this->B->Piece[loc_of_piece.x][loc_of_piece.y] = new bishop(ptr->Player, this->B);
            }
            else if (choice == 3)
            {
                this->B->Piece[loc_of_piece.x][loc_of_piece.y] = new rook(ptr->Player, this->B);
            }
            else if (choice == 4)
            {
                this->B->Piece[loc_of_piece.x][loc_of_piece.y] = new knight(ptr->Player, this->B);
            }
           
        }
    }
}
void chess::turn_change()
{
    if (turn == P[0])
        turn = P[1];
    else
        turn = P[0];
}
chess::chess()
{

    this->B = new board();
    //............................
    this->P = new player * [2];
    this->P[0] = new player(this);
    this->P[1] = new player(this);
    this->turn = P[0];
    //............................
    B->init(this);
}
bool chess::castle()
{

    if (!turn->self_check())
    {
        bool left_castle{}, right_castle{};
        if (turn == this->P[0])
        {
            if (this->B->Piece[0][3] && this->B->Piece[0][3]->first_time)
            {
                if (this->B->Piece[0][0] && this->B->Piece[0][0]->first_time)
                {
                    if (!this->B->Piece[0][1] && !this->B->Piece[0][2])
                    {
                        if (!(turn->will_getinto_check({ 0,3 }, { 0,1 }) || turn->will_getinto_check({ 0,3 }, { 0,2 })))
                        {
                            left_castle = true;
                        }
                    }
                }
                if (this->B->Piece[0][7] && this->B->Piece[0][7]->first_time)
                {
                    if (!this->B->Piece[0][4] && !this->B->Piece[0][5] && !this->B->Piece[0][6])
                    {
                        if (!(turn->will_getinto_check({ 0,3 }, { 0,4 }) || turn->will_getinto_check({ 0,3 }, { 0,5 })))
                        {
                            right_castle = true;
                        }
                    }
                }
            }
        }
        else
        {
            if (this->B->Piece[7][3] && this->B->Piece[7][3]->first_time)
            {
                if (this->B->Piece[7][0] && this->B->Piece[7][0]->first_time)
                {
                    if (!this->B->Piece[7][1] && !this->B->Piece[7][2])
                    {
                        if (!(turn->will_getinto_check({ 7,3 }, { 7,1 }) || turn->will_getinto_check({ 7,3 }, { 7,2 })))
                        {
                            left_castle = true;
                        }
                    }
                }
                if (this->B->Piece[7][7] && this->B->Piece[7][7]->first_time)
                {
                    if (!this->B->Piece[7][4] && !this->B->Piece[7][5] && !this->B->Piece[7][6])
                    {
                        if (!(turn->will_getinto_check({ 7,3 }, { 7,4 }) || turn->will_getinto_check({ 7,3 }, { 7,5 })))
                        {
                            right_castle = true;
                        }
                    }
                }
            }
        }
        if (left_castle || right_castle)
        {
            int choice=-1;
            cout << "Which direction : (0 for left and 1 for right and -1 for not)";
            cin >> choice;
            if (turn == this->P[0])
            {
                if (choice == 0 && left_castle)
                {
                    save(states_for_undo);
                    this->B->Piece[0][1] = this->B->Piece[0][3];
                    this->B->Piece[0][2] = this->B->Piece[0][0];
                    this->B->Piece[0][0] = this->B->Piece[0][3] = nullptr;
                    return true;
                }
                else if (choice == 1 && right_castle)
                {
                    save(states_for_undo);
                    this->B->Piece[0][5] = this->B->Piece[0][3];
                    this->B->Piece[0][4] = this->B->Piece[0][7];
                    this->B->Piece[0][7] = this->B->Piece[0][3] = nullptr;
                    return true;
                }
                    
            }
            else
            {
                if (choice == 0 && left_castle)
                {
                    save(states_for_undo);
                    this->B->Piece[7][1] = this->B->Piece[7][3];
                    this->B->Piece[7][2] = this->B->Piece[7][0];
                    this->B->Piece[7][0] = this->B->Piece[7][3] = nullptr;
                    return true;
                }
                else if (choice == 1 && right_castle)
                {
                    save(states_for_undo);
                    this->B->Piece[7][5] = this->B->Piece[7][3];
                    this->B->Piece[7][4] = this->B->Piece[7][7];
                    this->B->Piece[7][7] = this->B->Piece[7][3] = nullptr;
                    return true;
                }
                   
            }                       
        }
    }  
    return false;
}
void chess::play()
{
    
    int choice;
    while (1)
    {
        bool valid_choice{};
        this->B->print();           //print board on screen.
        do {
            valid_choice = false;
            cout << "\n you want to undo(1 for undo ,2 for redo,3 for castle and 0 for turn)\n";        //asking whether wants to undo or redo.
            cin >> choice;                                   //taking input from user
            if (choice == 1 && !states_for_undo.empty())
            {
                save(states_for_redo);                       //save every state before undo in stack(states_for_redo) to be later used by redo.
                undo_redo(states_for_undo);                  //undo.   
                valid_choice = true;
            }
            else if (choice == 2 && !states_for_redo.empty())
            {
                save(states_for_undo);                       //save every state before undo in stack(states_for_redo) to be later used by redo.
                undo_redo(states_for_redo);                  //redo.        
                valid_choice = true;
            }
            else if (choice == 3)
            {
                valid_choice = castle();                    //castling function, will check validity and ask choice from user about castling. if successful will return true else false.
            }
            else if (choice == 0)
            {
                while (!states_for_redo.empty())
                    states_for_redo.pop();
                save(states_for_undo);                      //save every state in stack(states_for_undo) to be later used by undo.             
                this->maketurn();                           //function to have a turn by player.
                valid_choice = true;
            }
        } while (!valid_choice);

        if (choice !=0)
        {
            maintaining_first_time_movement();
        }
        if (this->turn->blocked())                          //If enemy has no legal move.
        {
            if (turn->check())
            {
                cout << "\n\nCHECK MATE\n\n";   break;
            }
            else
            {
                cout << "\n\nSTALE MATE\n\n";   break;
            }
        }           
        this->turn_change();
    }
}
bool chess::valid_source_move(loc src)
{
    if (src.x >=8 || src.y >= 8)
        return false;
    if (this->B->Piece[src.x][src.y] == nullptr)
        return false;
    if (this->B->Piece[src.x][src.y]->getplayer() != this->turn)
        return false;
    return true;
}
bool chess::valid_destination_move(loc des)
{
    if (des.x >= 8 || des.y >= 8)
        return false;
    if (this->B->Piece[des.x][des.y] == nullptr)
        return true;
    if (this->B->Piece[des.x][des.y]->getplayer() != this->turn)
        return true;
    return false;
}   
void chess::maketurn()
{
    loc source, destination;
    do
    {
        do {
            cout << "SOURCE:";
            source = turn->player_move();
        } while (!this->valid_source_move(source));
        cout << "DESTINATION:";
        destination = turn->player_move();
    } while (!this->valid_overall_destination(source, destination)); 
    this->move(source, destination);
    if (this->B->Piece[destination.x][destination.y]->first_time)
    {
        this->B->Piece[destination.x][destination.y]->stack_number_before_first_move=states_for_undo.size()-1;
        this->B->Piece[destination.x][destination.y]->first_time = false;
    }
    replace_by_promotion(destination);
    
    //......................

}
void chess::move(loc src, loc des)
{
    this->B->Piece[des.x][des.y] = this->B->Piece[src.x][src.y];
    this->B->Piece[src.x][src.y] = nullptr;
}
bool chess::can_make_move(loc source, loc destination)
{
    return this->valid_source_move(source) && valid_overall_destination(source,destination);      
}
bool chess::valid_overall_destination(loc source, loc destination)
{
    king* ptr = dynamic_cast<king*>(this->B->Piece[destination.x][destination.y]);
    return !ptr&& this->valid_destination_move(destination) && this->B->Piece[source.x][source.y]->valid_move(source, destination) && !this->turn->will_getinto_check(source, destination);
}
chess::~chess()
{
    delete B;
    for (int i = 0; i < 2; i++)
        delete P[i];
    delete[]P;
}

#pragma once
//....Forward Declarations....
struct loc;
class player;
class board;
//.......................
class piece
{   
    public:   
        player* Player;
        board* B;
        bool first_time = true;         // legality shall change after first turn so this bool_check will handle it.
        int stack_number_before_first_move = 0;

        piece(player *,board*);
        player *getplayer();
        virtual void print()=0;
        virtual bool valid_move(loc,loc)=0;   
};





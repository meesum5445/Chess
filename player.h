#pragma once
//....Forward Declarations....
class chess;
struct loc;
//......................
class player
{
    public:
        chess* C;
        player(chess *B);
        loc player_move();
        loc king_loc();
        bool check();
        bool self_check();
        bool blocked();
        bool will_getinto_check(loc,loc);
};
    
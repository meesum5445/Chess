#pragma once
#include"utilities.h"
#include"player.h"
#include"board.h"
//header file to be defined
#include"piece.h"

//....................
player* piece::getplayer()
{
    return this->Player;
}
piece::piece(player* P, board* B)
{
    this->Player = P;
    this->B = B;
}
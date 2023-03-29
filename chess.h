#pragma once
#include<stack>
//....Forward Declarations....
struct loc;
class board;
class player;
//...................
class chess
{
public:
	board* B;
	player* turn{};
	player** P{};
	stack<piece***>states_for_undo;
	stack<piece***>states_for_redo;
	void save(stack<piece***>&);
	void undo_redo(stack<piece***>&);
	chess();
	bool castle();
	void maintaining_first_time_movement();
	void replace_by_promotion(loc);
	void play();
	void turn_change();
	bool valid_source_move(loc);
	bool valid_destination_move(loc);
	bool valid_overall_destination(loc source, loc destination);
	bool can_make_move(loc, loc);
	void move(loc src, loc des);
	void maketurn();
	~chess();
};



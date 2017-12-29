#ifndef GAMECLASS_H_INCLUDED
#define GAMECLASS_H_INCLUDED

#include "stdafx.h"
#include <vector>
#include <algorithm>
#include "time.h"
using namespace std;

// 排行榜结构体
typedef struct {
	int poi;
	char name[12];
} record;

typedef struct {
	int row, col;
} vertex;
bool operator!=(vertex, vertex);

class GameClass
{
public:
	GameClass(int, int, int);
	GameClass(int, int, int, int *);
	GameClass(){}
	~GameClass();
	void GenerateMap();
	void GetMap(int **&, int &, int &, int &);
	bool Remove(vertex, vertex, int &, int &);
	bool FindAPathInMap(vertex &, vertex &, int &, int &);
	void DisplayMap();
	bool ReDrawMap();
	bool IsEmptyMap();
	virtual  bool move();
//protected:
	bool GetPath(vertex, vertex, int &, int &);
	bool IsHandsomeMap();
	void GenerateAMap();

	int **map;
	int map_row_size, map_col_size, map_bmp_size;
	vertex vertices[4];
	int *map_mould;
	const static int nullplace = 0;
	const static int direction_vertical = 1;
	const static int direction_horizontal = 2;
private:
	void GetRangeY(vertex, int &, int &);
	void GetRangeX(vertex, int &, int &);

	
};

class GameClass_Up : public GameClass
{
public:
	GameClass_Up(int, int, int);

	bool move();
};

class GameClass_Down : public GameClass
{
public:
	GameClass_Down(int, int, int);

	bool move();
};

class GameClass_Left : public GameClass
{
public:
	GameClass_Left(int, int, int);

	bool move();
};

class GameClass_Right : public GameClass
{
public:
	GameClass_Right(int, int, int);

	bool move();
};

class GameClass_Up_Down : public GameClass
{
public:
	GameClass_Up_Down(int, int, int);

	bool move();
};

class GameClass_Left_Right : public GameClass
{
public:
	GameClass_Left_Right(int, int, int);

	bool move();
};


#endif // GAMECLASS_H_INCLUDED
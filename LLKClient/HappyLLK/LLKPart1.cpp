// LLKPart1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "GameClass.h"


int main()
{
	GameClass_Up_Down gc(8, 6, 8);
	gc.DisplayMap();
	int index, direction;
	vertex v1, v2;

	gc.FindAPathInMap(v1, v2, index, direction);
	printf("v1<%d, %d> v2<%d, %d> %d, %d\n", v1.row, v1.col, v2.row, v2.col, index, direction);
	gc.Remove(v1, v2, index, direction);
	
	gc.DisplayMap();

	gc.FindAPathInMap(v1, v2, index, direction);
	gc.Remove(v1, v2, index, direction);
	printf("v1<%d, %d> v2<%d, %d> %d, %d\n", v1.row, v1.col, v2.row, v2.col, index, direction);
	gc.DisplayMap();

	gc.FindAPathInMap(v1, v2, index, direction);
	gc.Remove(v1, v2, index, direction);
	printf("v1<%d, %d> v2<%d, %d> %d, %d\n", v1.row, v1.col, v2.row, v2.col, index, direction);
	gc.DisplayMap();

	return 0;
}


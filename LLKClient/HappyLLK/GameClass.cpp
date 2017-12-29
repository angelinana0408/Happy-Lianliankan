#include "stdafx.h"
#include "GameClass.h"
#include <time.h>

/********************************
*	       ����������           *
********************************/
bool operator!=(vertex v1, vertex v2)
{
	if (v1.row == v2.row && v1.col == v2.col)
		return false;
	else
		return true;
}
/********************************
*	   ���캯������������       *
********************************/
/*2014/12/17 ���޸� ʼ*/
GameClass::GameClass(int _map_row_size, int _map_col_size, int _map_bmp_size)
{
	// ׼����Ա����
	map_row_size = _map_row_size; map_col_size = _map_col_size; map_bmp_size = _map_bmp_size;
	map = new int*[map_row_size];
	for (int i = 0; i < map_row_size; i++)
	{
		map[i] = new int[map_col_size];
	}
	// Ĭ�ϵ�ͼģ��
	map_mould = new int[map_row_size * map_col_size];
	for (int i = 0; i < map_row_size * map_col_size; i++)
	{
		map_mould[i] = 1;
	}
	for (int i = 0; i < map_row_size; i++)
	{
		map_mould[i * map_col_size] = map_mould[(i + 1) * map_col_size - 1] = 0;
	}
	for (int i = 0; i < map_col_size; i++)
	{
		map_mould[i] = map_mould[(map_row_size - 1) * map_col_size + i] = 0;
	}
	// ���ɵ�ͼ
	GenerateMap();
}
GameClass::GameClass(int _map_row_size, int _map_col_size, int _map_bmp_size, int *_map_mould)
{
	// ׼����Ա����
	map_row_size = _map_row_size; map_col_size = _map_col_size; map_bmp_size = _map_bmp_size;
	map_mould = _map_mould;
	map = new int*[map_row_size];
	for (int i = 0; i < map_row_size; i++)
	{
		map[i] = new int[map_col_size];
	}
	// �޸ĵ�ͼģ�壬��ͼģ�����п�Ϊ1�޿�Ϊ0
	map_mould = new int[map_row_size * map_col_size];
	for (int i = 0; i < map_row_size * map_col_size; i++)
	{
		map_mould[i] = _map_mould[i];
	}
	// ���ɵ�ͼ
	GenerateMap();
}
/*2014/12/17 ���޸� ��*/
GameClass::~GameClass()
{
	for (int i = 0; i < map_row_size; i++)
	{
		delete[] map[i];
	}
	delete[] map;
	delete[] map_mould;
}
/********************************
*	        ��ͼ���            *
********************************/
/*2014/12/17 ���޸� ʼ*/
// ���ɺϷ���ͼ
void GameClass::GenerateMap()
{
	do
	{
		GenerateAMap();
	} while (!IsHandsomeMap());
}
// �ǲ���������������˧���ĵ�ͼ�أ�
bool GameClass::IsHandsomeMap()
{
	// ������Ը����������̫�෵��false����
	int index, direction;
	vertex v1, v2;
	if (FindAPathInMap(v1, v2, index, direction))
		return true;
	return false;
}
// ����һ�ŵ�ͼ
void GameClass::GenerateAMap()
{
	// �������ݴ�С
	int count = 0;
	for (int i = 0; i < map_row_size; i++)
	{
		for (int j = 0; j < map_col_size; j++)
		{
			if (map_mould[i * map_col_size + j] == 1)
				count++;
		}
	}
	// �������������
	vector<int> buff;
	srand(time(NULL));
	for (int i = 0; i < count / 2; i++)
	{
		int j = 1 + rand() % (map_bmp_size - 1);
		buff.push_back(j);
		buff.push_back(j);
	}
	random_shuffle(buff.begin(), buff.end());
	// �����ͼ
	vector<int>::iterator it = buff.begin();
	for (int i = 0; i < map_row_size; i++)
	{
		for (int j = 0; j < map_col_size; j++)
		{
			if (map_mould[i * map_col_size + j] == 1)
			{
				map[i][j] = *it;
				it++;
			}
			else
			{
				map[i][j] = 0;
			}
		}
	}
}
/*2014/12/17 ���޸� ��*/
// ��ȡ��ͼ
void GameClass::GetMap(int **&_map, int &_map_row_size, int &_map_col_size, int &_map_bmp_size)
{
	_map = map;
	_map_row_size = map_row_size;
	_map_col_size = map_col_size;
	_map_bmp_size = map_bmp_size;
}
// ���Է����� �����ͼ
void GameClass::DisplayMap()
{
	// �����ͼ
	for (int i = 0; i < map_row_size; i++)
	{
		for (int j = 0; j < map_col_size; j++)
		{
			printf_s("%2d ", map[i][j]);
		}
		printf_s("\n");
	}
}
/********************************
*	        �ж����            *
********************************/
// ����
bool GameClass::Remove(vertex v1, vertex v2, int &index, int &direction)
{


	if (GetPath(v1, v2, index, direction))
	{
		map[v1.row][v1.col] = map[v2.row][v2.col] = 0;
		move();
		int index_temp, direction_temp;
		vertex v1_temp, v2_temp;
		while (!FindAPathInMap(v1_temp, v2_temp, index_temp, direction_temp) && !IsEmptyMap())
			ReDrawMap();

		return true;
	}
	return false;
}
// ��ȡ·��
bool GameClass::GetPath(vertex v1, vertex v2, int &index, int &direction)
{
	index = -1;
	// �������ͬ�� 
	if (map[v1.row][v1.col] != map[v2.row][v2.col]) return false;
	// ���Ϊ�յ�
	if (map[v1.row][v1.col] == nullplace || map[v2.row][v2.col] == nullplace) return false;
	// �������
	if (v1.row == v2.row && (v1.col == v2.col + 1 || v1.col == v2.col - 1))
	{
		index = v1.row; direction = direction_horizontal;
		return true;
	}
	if (v1.col == v2.col && (v1.row == v2.row + 1 || v1.row == v2.row - 1))
	{
		index = v1.col; direction = direction_vertical;
		return true;
	}
	// Ѱ·
	int upper1, lower1;	int upper2, lower2;
	GetRangeY(v1, upper1, lower1);
	GetRangeY(v2, upper2, lower2);
	int upper = upper1 > upper2 ? upper1 : upper2;
	int lower = lower1 < lower2 ? lower1 : lower2;
	TRACE("%d, %d", upper, lower);
	if (upper <= lower)
	{
		vertex v1_new, v2_new;
		if (v1.col > v2.col)
		{
			v1_new.col = v2.col; v1_new.row = v2.row;
			v2_new.col = v1.col; v2_new.row = v1.row;
		}
		else
		{
			v1_new.col = v1.col; v1_new.row = v1.row;
			v2_new.col = v2.col; v2_new.row = v2.row;
		}
		int i; bool isconnect = false;
		bool isconnect_local = false;
		for (i = upper; i <= lower; i++)
		{
			if (i < 0) continue;
			isconnect_local = true;
			for (int j = v1_new.col + 1; j < v2_new.col; j++)
			{
				if (map[i][j] != nullplace)
					isconnect_local = false;
			}
			if (isconnect_local)
			{
				if (index == -1 || (i <= v1_new.row && i <= v2_new.row && i > index))
				{
					index = i;
					if (index != -1)
						isconnect = true;
				}
			}
		}
		if (isconnect)
		{
			direction = direction_horizontal;
			return true;
		}
	}
	int left1, right1; int left2, right2;
	GetRangeX(v1, left1, right1);
	GetRangeX(v2, left2, right2);
	int left = left1 > left2 ? left1 : left2;
	int right = right1 < right2 ? right1 : right2;
	TRACE("%d, %d", left, right);
	if (left <= right)
	{
		vertex v1_new, v2_new;
		if (v1.row > v2.row)
		{
			v1_new.col = v2.col; v1_new.row = v2.row;
			v2_new.col = v1.col; v2_new.row = v1.row;
		}
		else
		{
			v1_new.col = v1.col; v1_new.row = v1.row;
			v2_new.col = v2.col; v2_new.row = v2.row;
		}
		int i; bool isconnect = false;
		bool isconnect_local = false;
		for (i = left; i <= right; i++)
		{
			if (i < 0) continue;
			isconnect_local = true;
			for (int j = v1_new.row + 1; j < v2_new.row; j++)
			{
				if (map[j][i] != nullplace)
					isconnect_local = false;
			}
			if (isconnect_local)
			{
				if (index == -1 || (i <= v1_new.col && i <= v2_new.col && i > index))
				{
					index = i;
					if (index != -1)
						isconnect = true;
				}
			}
		}
		if (isconnect)
		{
			direction = direction_vertical;
			return true;
		}
	}

	return false;
}

void GameClass::GetRangeY(vertex p, int &upper, int &lower)
{
	for (lower = p.row + 1; lower < map_row_size; lower++)
	{
		if (map[lower][p.col] != 0)
		{
			lower--;
			break;
		}
	}
	if (lower == map_row_size) lower--;
	for (upper = p.row - 1; upper >= 0; upper--)
	{
		if (map[upper][p.col] != 0)
		{
			upper++;
			break;
		}
	}

}
void GameClass::GetRangeX(vertex p, int &left, int &right)
{
	for (right = p.col + 1; right < map_col_size; right++)
	{
		if (map[p.row][right] != 0)
		{
			right--;
			break;
		}
	}
	if (right == map_col_size) right--;
	for (left = p.col - 1; left >= 0; left--)
	{
		if (map[p.row][left] != 0)
		{
			left++;
			break;
		}
	}
}
// ��ʾ����
bool GameClass::FindAPathInMap(vertex &_v1, vertex &_v2, int &index, int &direction)
{
	for (int i = 1; i < map_row_size - 1; i++)
	{
		for (int j = 1; j < map_col_size - 1; j++)
		{
			for (int s = 1; s < map_row_size - 1; s++)
			{
				for (int t = 1; t < map_col_size - 1; t++)
				{
					vertex v1; v1.row = i; v1.col = j;
					vertex v2; v2.row = s; v2.col = t;
					if (v1 != v2 && GetPath(v1, v2, index, direction))
					{
						_v1 = v1; _v2 = v2;
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool GameClass::IsEmptyMap(){
	bool empty = true;
	for (int row = 1; row < map_row_size - 1; row++){
			for (int column = 1; column < map_col_size - 1; column++){
				if(map[row][column]!=0)
					empty = false;
			}
	}
	return empty;
}
//�޷�������������ػ���ͼ
bool GameClass::ReDrawMap(){
	vector<int> random;

	for (int row = 1; row < map_row_size - 1; row++){
		for (int column = 1; column < map_col_size - 1; column++){
			if (map[row][column] != 0)
				random.push_back(map[row][column]);
		}
	}

	random_shuffle(random.begin(), random.end()); //��������˳��

	vector<int>::iterator it = random.begin();

	for (int row = 1; row < map_row_size - 1; row++){
		for (int column = 1; column < map_col_size - 1; column++){
			if (map[row][column] != 0)
				map[row][column] = *it++;
		}
	}
	return true;
}

bool GameClass::move()
{
	return true;
}

GameClass_Up::GameClass_Up(int _map_row_size, int _map_col_size, int _map_bmp_size) : GameClass(_map_row_size, _map_col_size, _map_bmp_size)

{
	// ׼����Ա����
	map_row_size = _map_row_size; map_col_size = _map_col_size; map_bmp_size = _map_bmp_size;
	map = new int*[map_row_size];
	for (int i = 0; i < map_row_size; i++)
	{
		map[i] = new int[map_col_size];
	}
	// ���ɵ�ͼ
	GenerateMap();
}

bool GameClass_Up::move()
{
	for (int col = 1; col < map_col_size - 1; col++)
	{
		for (int row = 1; row < map_row_size - 1; row++)
		{
			int bechanged = row - 1;
			while (bechanged != 0 && map[bechanged][col] == 0)
			{
				bechanged--;
			}
			if (bechanged != row - 1)
			{
				map[bechanged + 1][col] = map[row][col];
				map[row][col] = 0;
			}
		}
	}
	return true;
}

GameClass_Down::GameClass_Down(int _map_row_size, int _map_col_size, int _map_bmp_size): GameClass(_map_row_size, _map_col_size, _map_bmp_size)
{
	// ׼����Ա����
	map_row_size = _map_row_size; map_col_size = _map_col_size; map_bmp_size = _map_bmp_size;
	map = new int*[map_row_size];
	for (int i = 0; i < map_row_size; i++)
	{
		map[i] = new int[map_col_size];
	}
	// ���ɵ�ͼ
	GenerateMap();
}

bool GameClass_Down::move()
{
	for (int col = 1; col < map_col_size - 1; col++)
	{
		for (int row = map_row_size - 2; row > 0; row--)
		{
			int bechanged = row + 1;
			while (bechanged <map_row_size - 1 && map[bechanged][col] == 0)
			{
				bechanged++;
			}
			if (bechanged != row + 1)
			{
				map[bechanged - 1][col] = map[row][col];
				map[row][col] = 0;
			}
		}
	}
	return true;
}


GameClass_Left::GameClass_Left(int _map_row_size, int _map_col_size, int _map_bmp_size): GameClass(_map_row_size, _map_col_size, _map_bmp_size)
{
	// ׼����Ա����
	map_row_size = _map_row_size; map_col_size = _map_col_size; map_bmp_size = _map_bmp_size;
	map = new int*[map_row_size];
	for (int i = 0; i < map_row_size; i++)
	{
		map[i] = new int[map_col_size];
	}
	// ���ɵ�ͼ
	GenerateMap();
}

bool GameClass_Left::move()
{
	for (int row = 1; row < map_row_size - 1; row++)
	{
		for (int col = 1; col < map_col_size - 1; col++)
		{
			int bechanged = col - 1;
			while (bechanged != 0 && map[row][bechanged] == 0)
			{
				bechanged--;
			}
			if (bechanged != col - 1)
			{
				map[row][bechanged + 1] = map[row][col];
				map[row][col] = 0;
			}
		}
	}
	return true;
}

GameClass_Right::GameClass_Right(int _map_row_size, int _map_col_size, int _map_bmp_size): GameClass(_map_row_size, _map_col_size, _map_bmp_size)
{
	// ׼����Ա����
	map_row_size = _map_row_size; map_col_size = _map_col_size; map_bmp_size = _map_bmp_size;
	map = new int*[map_row_size];
	for (int i = 0; i < map_row_size; i++)
	{
		map[i] = new int[map_col_size];
	}
	// ���ɵ�ͼ
	GenerateMap();
}

bool GameClass_Right::move()
{
	for (int row = 1; row < map_row_size - 1; row++)
	{
		for (int col = map_col_size - 2; col > 0; col--)
		{
			int bechanged = col + 1;
			while (bechanged <map_col_size - 1 && map[row][bechanged] == 0)
			{
				bechanged++;
			}
			if (bechanged != col + 1)
			{
				map[row][bechanged - 1] = map[row][col];
				map[row][col] = 0;
			}
		}
	}
	return true;
}


GameClass_Up_Down::GameClass_Up_Down(int _map_row_size, int _map_col_size, int _map_bmp_size): GameClass(_map_row_size, _map_col_size, _map_bmp_size)
{
	// ׼����Ա����
	map_row_size = _map_row_size; map_col_size = _map_col_size; map_bmp_size = _map_bmp_size;
	map = new int*[map_row_size];
	for (int i = 0; i < map_row_size; i++)
	{
		map[i] = new int[map_col_size];
	}
	// ���ɵ�ͼ
	GenerateMap();
}

bool GameClass_Up_Down::move()
{
	for (int col = 1; col < map_col_size - 1; col++)
	{
		//�ӵ�һ�е���map_row_size/2ȡ���������ƶ�
		for (int row = 1; row < (int)(map_row_size / 2); row++)
		{
			int bechanged = row - 1;
			while (bechanged != 0 && map[bechanged][col] == 0)
			{
				bechanged--;
			}
			if (bechanged != row - 1)
			{
				map[bechanged + 1][col] = map[row][col];
				map[row][col] = 0;
			}
		}

		//֮��ģ������ƶ�
		for (int row = map_row_size - 2; row > (int)(map_row_size / 2) - 1; row--)
		{
			int bechanged = row + 1;
			while (bechanged <map_row_size - 1 && map[bechanged][col] == 0)
			{
				bechanged++;
			}
			if (bechanged != row + 1)
			{
				map[bechanged - 1][col] = map[row][col];
				map[row][col] = 0;
			}
		}

	}
	return true;
}


GameClass_Left_Right::GameClass_Left_Right(int _map_row_size, int _map_col_size, int _map_bmp_size): GameClass(_map_row_size, _map_col_size, _map_bmp_size)
{
	// ׼����Ա����
	map_row_size = _map_row_size; map_col_size = _map_col_size; map_bmp_size = _map_bmp_size;
	map = new int*[map_row_size];
	for (int i = 0; i < map_row_size; i++)
	{
		map[i] = new int[map_col_size];
	}
	// ���ɵ�ͼ
	GenerateMap();
}

bool GameClass_Left_Right::move()
{
	for (int row = 1; row < map_row_size - 1; row++)
	{
		//�ӵ�һ�е���map_row_size/2ȡ���������ƶ�
		for (int col = 1; col < (int)(map_col_size / 2); col++)
		{
			int bechanged = col - 1;
			while (bechanged != 0 && map[row][bechanged] == 0)
			{
				bechanged--;
			}
			if (bechanged != col - 1)
			{
				map[row][bechanged + 1] = map[row][col];
				map[row][col] = 0;
			}
		}

		//֮��ģ������ƶ�
		for (int col = map_col_size - 2; col > (int)(map_col_size / 2) - 1; col--)
		{
			int bechanged = col + 1;
			while (bechanged <map_col_size - 1 && map[row][bechanged] == 0)
			{
				bechanged++;
			}
			if (bechanged != col + 1)
			{
				map[row][bechanged - 1] = map[row][col];
				map[row][col] = 0;
			}
		}

	}
	return true;
}
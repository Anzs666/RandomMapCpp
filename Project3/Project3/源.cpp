#include<iostream>
#include<time.h>
#include<windows.h>
#include<graphics.h>
#include<conio.h>
using namespace std;
struct Canvas
{
	int width;
	int height;
	int **map;
};
struct Room
{
	int width;
	int height;
	int **map;
};
const int wallRote = 45;
const int girdSize = 5;

void InitRoom(Room &sRoom, int h, int w)
{
	sRoom.height = h;
	sRoom.width = w;
	sRoom.map = new int*[sRoom.height];
	for (int i = 0;i < h;i++) {
		sRoom.map[i] = new int[sRoom.width];
	}
	//边框赋值
	for (int i = 0;i < sRoom.height;i++) {
		for (int j = 0;j < sRoom.width;j++) {
			if (i == 0 || i == h - 1 || j == 0 || j == w - 1)
				sRoom.map[i][j] = 0;//0代表不可更改的墙
			else
				sRoom.map[i][j] = 101;//代表不可更改的路
		}
	}
}
void InitCanvas(Canvas &canvas, int h, int w)
{
	canvas.height = h;
	canvas.width = w;
	initgraph(canvas.width * girdSize, canvas.height *girdSize);//初始画布
	//创建数组
	canvas.map = new int*[canvas.height];
	for (int i = 0;i < canvas.height;i++) {
		canvas.map[i] = new int[canvas.width];
	}
	//全是墙
	for (int i = 0;i < canvas.height;i++) {
		for (int j = 0;j < canvas.width;j++) {
			canvas.map[i][j] = 1;
		}
	}
}
void RandCanvas(Canvas &canvas)
{
	//随机赋值0代表空 1代表墙	
	for (int i = 1;i < canvas.height - 1;i++)
		for (int j = 1;j < canvas.width - 1;j++) {
			if (canvas.map[i][j] > 0 && canvas.map[i][j] <= 100)
				canvas.map[i][j] = rand() % 100 + 1;
		}
}
void PrintCanvas(Canvas &canvas)
{
	for (int i = 0;i < canvas.height;i++) {
		for (int j = 0;j < canvas.width;j++) {
			if (canvas.map[i][j] <= wallRote)//控制概率小于50%生成墙1~4为墙6~10为路
			{
				//setcolor(BLACK);
				setfillcolor(BLACK);
				fillrectangle(i * girdSize, j * girdSize, i * girdSize + girdSize, j * girdSize + girdSize);
			}
			else
			{
				setcolor(WHITE);
				setfillcolor(WHITE);
				fillrectangle(i * girdSize, j * girdSize, i *girdSize + girdSize, j * girdSize + girdSize);
			}
		}
		cout << endl;
	}
}
void CleanCanvas()
{
	setfillcolor(BLACK);
	fillcircle(0, 0, 2000);
}
void InputSpecialRoom(Room &sRoom, Canvas &can)
{
	int rx = rand() % (can.width - sRoom.width);
	int ry = rand() % (can.height - sRoom.height);
	for (int i = 0;i < sRoom.height;i++)
		for (int j = 0;j < sRoom.width;j++)
		{
			can.map[i + rx][j + ry] = sRoom.map[i][j];
		}
}
int CheckNeighborWall(Canvas &canvas, int x, int y, int r)
{
	int wallNum = 0;
	for (int i = x - r;i <= x + r;i++)
		for (int j = y - r;j <= y + r;j++)
			if (i >= 0 && i < canvas.height&&j >= 0 && j < canvas.width &&
				!(i == x && j == y) && canvas.map[i][j] <= wallRote)
				wallNum++;
	return wallNum;
}
void CellAM(Canvas &canvas)
{
	for (int i = 1;i < canvas.width - 1;i++)
		for (int j = 1;j < canvas.height - 1;j++)
			if (canvas.map[i][j] <= wallRote && canvas.map[i][j] > 0) {
				if (CheckNeighborWall(canvas, i, j, 1) < 4)
					canvas.map[i][j] = 100;
			}
			else if (canvas.map[i][j] > wallRote&&canvas.map[i][j] <= 100) {
				if (CheckNeighborWall(canvas, i, j, 1) >= 5)
					canvas.map[i][j] = 1;
			}
}
void CellAM2(Canvas &canvas)
{
	for (int i = 1;i < canvas.width - 1;i++)
		for (int j = 1;j < canvas.height - 1;j++)
			if (canvas.map[i][j] > 0 && canvas.map[i][j] <= 100&&
				CheckNeighborWall(canvas, i, j, 1) >= 5 || CheckNeighborWall(canvas, i, j, 2) < 5)canvas.map[i][j] = 1;
}


int main()
{
	Canvas can;
	Room room;
	srand((unsigned)time(NULL));
	InitRoom(room, 5, 40);
	InitCanvas(can, 100, 100);
	InputSpecialRoom(room, can);
	PrintCanvas(can);
	RandCanvas(can);
	CleanCanvas();
	PrintCanvas(can);
	int num = 0;
	do
	{
		for (int i = 0;i < 2;i++)
		{
			//Sleep(1000);
			CleanCanvas();
			CellAM(can);
			PrintCanvas(can);
		}
		for (int i = 0;i < 4;i++)
		{
			//Sleep(1000);
			CleanCanvas();
			CellAM2(can);
			PrintCanvas(can);
		}
		num++;
	} while (num < 3);

	CleanCanvas();
	CellAM(can);
	PrintCanvas(can);

	/*int cx = 20, cy = 20;
	setcolor(WHITE);
	setfillcolor(RED);
	fillrectangle(cx * girdSize, cy * girdSize, cx * girdSize + girdSize, cy * girdSize + girdSize);
	char c[8];
	sprintf_s(c, "%05X", CheckNeighborWall(can, cx, cy, 1));
	outtextxy(150, 150, c);*/
	getchar();
	return 0;
}



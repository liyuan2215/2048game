// ConsoleApplication3.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#undef UNICODE
#undef _UNICODE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <graphics.h>
#include <windows.h>
#pragma warning(disable:4996)
#pragma comment(lib,"Winmm.lib")
#define WIDTH 700
#define HEIGHT 900

#include "Game_menu.h"
#include "DB2048.h"
#include "Instruction.h"
#include "Game_introduction.h"

int point = 0;
int map[4][4] = { 0 };
int score, score_i;
int FLAG;

void show1()
{
	game_menu();
}

void show2()
{
	game_introduction();
}

void show3()
{
	instruction();
}

void show4()
{
	cleardevice();//清屏
	settextstyle(145, 0, "Microsoft Yahei UI Bold");
	settextcolor(RGB(164, 214, 248));//设置字体
	outtextxy(15, 0, "2048");



	setfillcolor(RGB(184, 175, 160));//设置当前填充颜色
	solidroundrect(390, 10, 530, 80, 15, 15);//圆角梯形
	settextstyle(28, 0, "Microsoft Yahei UI Bold");//设置当前字
	setbkcolor(RGB(184, 175, 160));//背景颜色
	settextcolor(RGB(248, 247, 241));//字体颜色
	outtextxy(435, 20, "得分");


	char str[10], str_i[10];
	setbkcolor(RGB(184, 175, 160));
	itoa(score_i, str_i, 10);
	outtextxy(450, 52, str_i);//分数



	solidroundrect(550, 10, 690, 80, 15, 15);//圆角梯形
	outtextxy(600, 20, "总分");
	setbkcolor(RGB(184, 175, 160));
	itoa(score, str, 10);
	outtextxy(605, 52, str);//分数


	setfillcolor(RGB(141, 122, 105));
	solidroundrect(480, 95, 690, 137, 15, 15);
	setbkcolor(RGB(141, 122, 105));//背景颜色
	settextstyle(33, 0, "Microsoft Yahei UI Bold");
	outtextxy(498, 100, "返回主页面(Esc)");


	setfillcolor(RGB(141, 122, 105));
	solidroundrect(480, 152, 690, 195, 15, 15);
	setbkcolor(RGB(141, 122, 105));//背景颜色
	settextstyle(33, 0, "Microsoft Yahei UI Bold");
	outtextxy(520, 160, "重新开始(T)");


	setfillcolor(RGB(0, 0, 0));
	solidroundrect(10, 210, 690, 890, 20, 20);

	//绘制小方块
	int i, j;
	for (i = 0; i<4; i++)
	{
		setfillcolor(RGB(206, 192, 181));
		for (j = 0; j<4; j++)
		{
			solidroundrect(30 + 165 * i, 230 + 165 * j, 175 + 165 * i, 375 + 165 * j, 5, 5);
		}
	}

	//在小方块内添加图片
	IMAGE img0, img2, img4, img8, img16, img32, img64, img128, img256, img512, img1024, img2048;

	for (i = 0; i<4; i++)
	{
		for (j = 0; j<4; j++)
		{
			switch (map[j][i])
			{
			case 0:loadimage(&img0, "0.jpg"); putimage(i * 165 + 30, j * 165 + 230, &img0); break;

			case 2:loadimage(&img2, "2.jpg"); putimage(i * 165 + 30, j * 165 + 230, &img2); break;

			case 4:loadimage(&img4, "4.jpg"); putimage(i * 165 + 30, j * 165 + 230, &img4); break;

			case 8:loadimage(&img8, "8.jpg"); putimage(i * 165 + 30, j * 165 + 230, &img8); break;

			case 16:loadimage(&img16, "16.jpg"); putimage(i * 165 + 30, j * 165 + 230, &img16); break;

			case 32:loadimage(&img32, "32.jpg"); putimage(i * 165 + 30, j * 165 + 230, &img32); break;

			case 64:loadimage(&img64, "64.jpg"); putimage(i * 165 + 30, j * 165 + 230, &img64); break;

			case 128:loadimage(&img128, "128.jpg"); putimage(i * 165 + 30, j * 165 + 230, &img128); break;

			case 256:loadimage(&img256, "256.jpg"); putimage(i * 165 + 30, j * 165 + 230, &img256); break;

			case 512:loadimage(&img512, "512.jpg"); putimage(i * 165 + 30, j * 165 + 230, &img512); break;

			case 1024:loadimage(&img1024, "1024.jpg"); putimage(i * 165 + 30, j * 165 + 230, &img1024); break;

			case 2048:loadimage(&img2048, "2048.jpg"); putimage(i * 165 + 30, j * 165 + 230, &img2048); break;
			}
		}
	}
}

int judge()
{
	int i, j;

	//检查是否有0值
	for (i = 0; i<4; i++)
		for (j = 0; j<4; j++)
			if (map[i][j] == 0)
				return 0;

	//查看边界是否有相同的
	for (i = 0; i<4; i += 3)
		for (j = 1; j<3; j++)
			if (map[i][j - 1] == map[i][j] || map[i][j + 1] == map[i][j])
				return 1;

	for (i = 1; i<3; i++)
		for (j = 0; j<4; j += 3)
			if (map[i - 1][j] == map[i][j] || map[i + 1][j] == map[i][j])
				return 1;

	//查看中心是否有相同
	for (i = 1; i<3; i++)
		for (j = 1; j<3; j++)
			if (map[i - 1][j] == map[i][j] || map[i + 1][j] == map[i][j] || map[i][j - 1] == map[i][j] || map[i][j + 1] == map[i][j])
				return 1;
	lose();
}

void rands()
{
	int x, y, temp, num;

	srand((int)time(0));

	while (1)
	{
		x = rand() % 4;

		y = rand() % 4;

		temp = rand() % 5;

		if (temp == 1)

			num = 4;

		else

			num = 2;

		if (map[y][x] == 0)
		{
			map[y][x] = num;

			break;
		}
		if (judge())

			break;
	}
}

void updateWithInput()//与输入有关的更新
{
	char keyboard;

	if (kbhit())

	{
		keyboard = _getch();

		//EndBatchDraw();//结束批量绘图

		score_i = 0;
	}

	int i, j, n, num = 0;
	if (keyboard == 'w' || keyboard == 'W' || keyboard == 72)//上
	{
		for (n = 0; n<4; n++)//次数

			for (i = 1; i<4; i++)//行

				for (j = 0; j<4; j++)//列

					if (map[i][j] != 0)

					{

						if (map[i - 1][j] == 0)

						{

							map[i - 1][j] = map[i][j];

							map[i][j] = 0;

						}

						if (map[i - 1][j] == map[i][j])

						{

							num = map[i][j] * 2;//得分

							score_i = score_i + num;

							map[i - 1][j] = map[i][j] * 2;

							map[i][j] = 0;
						}
					}
		score = score + score_i;
		rands();
	}

	else if (keyboard == 's' || keyboard == 'S' || keyboard == 80)//下
	{
		for (n = 0; n<4; n++)//次数

			for (i = 2; i >= 0; i--)//行

				for (j = 0; j<4; j++)//列

					if (map[i][j] != 0)
					{
						if (map[i + 1][j] == 0)
						{
							map[i + 1][j] = map[i][j];

							map[i][j] = 0;
						}

						if (map[i + 1][j] == map[i][j])
						{
							num = map[i][j] * 2;//得分

							score_i = score_i + num;

							map[i + 1][j] = map[i][j] * 2;

							map[i][j] = 0;
						}
					}
		score = score + score_i;
		
		rands();
	}

	else if (keyboard == 'a' || keyboard == 'A' || keyboard == 75)//左
	{
		for (n = 0; n<4; n++)//次数

			for (i = 0; i<4; i++)//行

				for (j = 1; j<4; j++)//列

					if (map[i][j] != 0)
					{
						if (map[i][j - 1] == 0)
						{
							map[i][j - 1] = map[i][j];
							map[i][j] = 0;
						}
						if (map[i][j - 1] == map[i][j])
						{
							num = map[i][j] * 2;//得分
							score_i = score_i + num;
							map[i][j - 1] = map[i][j] * 2;
							map[i][j] = 0;
						}
					}
		score = score + score_i;
		rands();
	}

	else if (keyboard == 'd' || keyboard == 'D' || keyboard == 77)//右
	{
		for (n = 0; n<4; n++)//次数
			for (i = 0; i<4; i++)//行
				for (j = 2; j >= 0; j--)//列
					if (map[i][j] != 0)
					{
						if (map[i][j + 1] == 0)
						{
							map[i][j + 1] = map[i][j];
							map[i][j] = 0;
						}
						if (map[i][j + 1] == map[i][j])
						{
							num = map[i][j] * 2;//得分
							score_i = score_i + num;
							map[i][j + 1] = map[i][j] * 2;
							map[i][j] = 0;
						}
					}

		score = score + score_i;

		rands();
	}

	else if (keyboard == 27)
		lent();
	else if (keyboard == 't')
	{
		for (i = 0; i<4; i++)
			for (j = 0; j<4; j++)
				map[i][j] = 0;
		score = 0;
		rands();
		rands();
	}
     
	FLAG = score;
}

void win()
{
	mciSendString("close music", NULL, 0, NULL);
	mciSendString("open \"pic\\win.mp3\" alias music ", NULL, 0, NULL);//背景音乐
	mciSendString("play music", NULL, 0, NULL);
	cleardevice();//清屏
	settextcolor(RGB(249, 6, 43));
	setfont(40, 0, "Microsoft Yahei UI Bold");
	RECT C2 = { 100,400,640,790 };
	drawtext("恭喜你完成了2048，小锐锐决定给你一个摸摸大，作为对你的奖励_(:з」∠)_", &C2, DT_WORDBREAK);
	RECT R1 = { 2,HEIGHT - 200,WIDTH - 2,HEIGHT - 2 };
	drawtext("回到主页面", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	MOUSEMSG m;

	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (m.x>2 && m.x<WIDTH - 2 && m.y>HEIGHT - 200 && m.y<HEIGHT - 2)

				lent();
		}
	}
}

void lose()

{
	mciSendString("close music", NULL, 0, NULL);
	mciSendString("open \"失败.mp3\" alias music ", NULL, 0, NULL);//背景音乐
	mciSendString("play music", NULL, 0, NULL);

	cleardevice();//清屏
	settextcolor(RGB(120, 155, 0));
	setfont(40, 0, "Microsoft Yahei UI Bold");
	RECT C2 = { 100,400,640,790 };
	drawtext("2048都完成不了？？！ ￣へ￣重新玩！！！", &C2, DT_WORDBREAK);
	RECT R1 = { 2,HEIGHT - 200,WIDTH - 2,HEIGHT - 2 };
	drawtext("回到主页面", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT R2 = { 2,HEIGHT - 400,WIDTH - 2,HEIGHT - 202 };
	
	if (point == 0)
	{
		settextcolor(GREEN);
		drawtext("看广告复活（1次）", &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	MOUSEMSG m;

	IMAGE MV;
	loadimage(&MV, "MV.jpg"); 
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{

			if (m.x > 2 && m.x<WIDTH - 2 && m.y>HEIGHT - 200 && m.y < HEIGHT - 2)
			{
				score = 0;
				lent();
			}
			else if (m.x > 2 && m.x<WIDTH - 2 && m.y>HEIGHT - 400 && m.y < HEIGHT - 202 )
			{
				point = 1;
				putimage(-665,50,&MV);
				RECT R3 = { 50,HEIGHT - 400,650,HEIGHT - 350 };
				settextcolor(BLUE);
				drawtext("看够了没？！看完点这里！", &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				if (m.x > 50 && m.x<650 && m.y>HEIGHT - 400 && m.y < HEIGHT - 350)
				{
					if (point == 1)
					{
						score = FLAG;
					}
					start();
				}
			}
		}
		FlushBatchDraw();
	}
}

void start()
{
	//MOUSEMSG m;
	int i, j;

	for (i = 0; i<4; i++)
		for (j = 0; j<4; j++)
			map[i][j] = 0;
	rands();
	rands();
	while (1)
	{
		show4();
		setbkcolor(RGB(27, 9, 62));
		updateWithInput();//与输入有关的更新

		if (score_i >= 2048)
			win();
		FlushBatchDraw();
	}
}

void lent()
{	
	mciSendString("open 背景音乐1.mp3 alias mymusic", NULL, 0, NULL);
	mciSendString("play mymusic", NULL, 0, NULL);
	initgraph(WIDTH, HEIGHT);//长宽
	setbkcolor(RGB(251, 248, 241));//背景
	settextcolor(RGB(150, 126, 104));
	BeginBatchDraw();//批量画图
	

	MOUSEMSG m;

	while (1)
	{
		show1();
		
		m = GetMouseMsg();//获取鼠标信息
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			//EndBatchDraw();//结束批量绘图		
			

			if (m.x>WIDTH / 2 - 45 && m.x<WIDTH / 2 + 45 && m.y>HEIGHT / 3 && m.y<HEIGHT / 3 + 30)

				start();

            
			else if (m.x>WIDTH / 2 - 45 && m.x<WIDTH / 2 + 45 && m.y>HEIGHT / 3 + 30 && m.y<HEIGHT / 3 + 60)

				show2();


			else if (m.x>WIDTH / 2 - 45 && m.x<WIDTH / 2 + 45 && m.y>HEIGHT / 3 + 60 && m.y<HEIGHT / 3 + 90)

				show3();


			else if (m.x>WIDTH / 2 - 45 && m.x<WIDTH / 2 + 45 && m.y>HEIGHT / 3 + 90 && m.y<HEIGHT / 3 + 120)

				exit(0);
		} 
		FlushBatchDraw();
	}
	_getch();
}

int main(void)

{
	lent();	
	EndBatchDraw();
}





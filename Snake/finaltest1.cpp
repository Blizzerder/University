#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <stdio.h>

#include "FindPathBFS.h"
using namespace std;

int dir[4][2]={ {0,1},{0,-1},{1,0},{-1,0}};
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define HEAD 0

int speed = 0;
void gotoxy(int x,int y)//光标移动函数
{
	COORD c;
	c.X=x; c.Y=y; //c表示为要求的坐标位置
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c); //光标停在c的位置处
}

void setColor(unsigned short ForeColor = 7,unsigned short BackGroundColor = 0)//颜色设置函数
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //Windows API 函数
	SetConsoleTextAttribute(handle, ForeColor + BackGroundColor * 0x10);  
}

class GameSetting
{
public://设置游戏窗口的长宽
	static const int window_height ;  
	static const int window_width ;   //静态成员变量
public:
	static void GameInt()
	{
		//设置游戏窗口大小
		char buffer[32];
		sprintf(buffer,"more con cols=%d lines=%d",window_width,window_height);
		system(buffer);
	

	//隐藏光标
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle,&CursorInfo); //获取控制台光标信息
	CursorInfo.bVisible = false; //隐藏控制台光标
	SetConsoleCursorInfo(handle,&CursorInfo);//设置控制台光标状态
	//初始化随机数种子
	srand((unsigned int ) time(0));
	}
};

const int GameSetting::window_height=40;
const int GameSetting::window_width=80;

class PrintInfo
{
public:
	static void DrawChoiceInfo();  //选择模式
	static void	DrawMap();		   //画出地图边界
	static void GameOver(int score);//游戏结束
	static void DrawScore(int score);//显示分数
	static void DrawGameInfo(bool model);//显示游戏操作说明
};

void PrintInfo::DrawChoiceInfo()
{
	gotoxy(GameSetting::window_width/2 - 10,GameSetting::window_height/2 - 7);
	cout<<"1：玩家模式"<<endl;

	gotoxy(GameSetting::window_width/2 - 10,GameSetting::window_height/2 - 5);
	cout<<"2：AI模式"<<endl;
	
	gotoxy(GameSetting::window_width/2 - 10,GameSetting::window_height/2 - 9);
	cout<<"请决定您的选择"<<endl;
	
	
}

void PrintInfo::DrawMap()
{
		system("cls"); //清屏
		int i,j;
		for (i=0;i<GameSetting::window_width;i++)
		{
			cout<<"#";
		}
		cout<<endl;
		for (i=0;i<GameSetting::window_height-2;i++)
		{
			for (j=0;j<GameSetting::window_width;j++)
			{
				if (i==13&&j>=GameSetting::window_width-29)
				{
					cout<<"#";
					continue;
				}
				if (j==0 || j == GameSetting::window_width-29 || j == GameSetting::window_width-1)
				{
					cout<<"#";
				}
				else
					cout<<" ";
			}
			cout<<endl;
		}
		for (i=0;i<GameSetting::window_width;i++)
			cout<<"#";
}

void PrintInfo::GameOver(int score)
{
	setColor(12,0);   //设置为红色
	gotoxy(GameSetting::window_width/2 - 20,GameSetting::window_height / 2 - 5);
	cout<<"游戏结束！"<<endl;
	gotoxy(GameSetting::window_width / 2 -20,GameSetting::window_height / 2 -3);
	cout<<"您的得分为："<<score<<endl;
}

void PrintInfo::DrawScore(int score)
{
	gotoxy(GameSetting::window_width-22+14,6);
	cout<<" ";
	gotoxy(GameSetting::window_width-22+14,4);
	cout<<" ";

	gotoxy(GameSetting::window_width-22,6);
	cout<<"当前玩家分数："<<score<<endl;
	gotoxy(GameSetting::window_width-22,4);
	cout<<"当前游戏速度："<<10-speed/25<<endl;
}

void PrintInfo::DrawGameInfo(bool model)
{
	gotoxy(GameSetting::window_width - 22, 8);
	if (model)
	{
		cout<<"当前游戏模式："<<"玩家模式"<<endl;
	}
	else
	{
		cout<<"当前游戏模式："<<"AI模式"<<endl;
	}

	gotoxy(GameSetting::window_width - 22, 18);
	cout<<"游戏操作说明："<<endl;

	gotoxy(GameSetting::window_width - 22, 20);
	cout<<"W:上    S:下"<<endl;

	gotoxy(GameSetting::window_width - 22, 23);
	cout<<"A:左    D:右"<<endl;

	gotoxy(GameSetting::window_width - 22, 26);
	cout<<"调节游戏速度："<<endl;

	gotoxy(GameSetting::window_width - 22, 29);
	cout<<"小键盘 + ：加快"<<endl;

	gotoxy(GameSetting::window_width - 22, 32);
	cout<<"小键盘 - ：减慢"<<endl;

}

/*struct COORDINATE  //坐标函数
{
	int x;
	int y;
};*/

class Food
{
private:
	COORDINATE m_coordinate; // 食物坐标
public:

	Food() {} // 默认构造函数
	void RandomXY(vector<COORDINATE> & coord);//坐标范围
	Food(vector<COORDINATE> & coord) //随机位置生成食物
	{
		RandomXY(coord);
	}
	void DrawFood();   //画出食物位置
	COORDINATE GetFoodCoordinate()  //获取食物位置
	{
		return m_coordinate;
	}
	int GetFoodX()
	{
		return m_coordinate.x;
	}
	int GetFoodY()
	{
		return m_coordinate.y;
	}
};

void Food::RandomXY(vector<COORDINATE> & coord)
{
	m_coordinate.x = rand() % (GameSetting::window_width - 30) + 1;
	m_coordinate.y = rand() % (GameSetting::window_height - 2) + 1;
	unsigned int i;
	for (i=0;i<coord.size();i++) //如果食物生成在了蛇身的位置需要重新生成
	{
		if (coord[i].x==m_coordinate.x && coord[i].y == m_coordinate.y)
		{
			m_coordinate.x = rand() % (GameSetting::window_width - 30) + 1;
			m_coordinate.y = rand() % (GameSetting::window_height - 2) + 1;
			i=0;
		}
	}
}



void Food::DrawFood()   
{
	setColor(12,0);
	gotoxy(m_coordinate.x,m_coordinate.y);
	cout<<"@";
	setColor(7,0);
}

class Snake
{
private:
	bool m_model; //游戏模式设置，true 玩家，false AI
	int m_direction;  //蛇的移动方向
	bool m_is_alive;  //判断贪吃蛇是否还活着
private://AI功能相关
	bool m_chess[GameSetting::window_width- 29 + 1][GameSetting::window_height];//AI功能用
	FindPathBFS m_AISnake;
	COORDINATE map_size;
public: //蛇身坐标
	vector<COORDINATE> m_coordinate;

public:
	Snake(bool model = false) //默认构造函数，默认AI模式
	{
		m_direction = 1; // 默认向上
		m_is_alive = true;//开始蛇存活
		COORDINATE  snake_head;//蛇头
		snake_head.x = GameSetting::window_width/2 - 15; 
		snake_head.y = GameSetting::window_height/2;     //确定蛇头位置

		this->m_coordinate.push_back(snake_head);
		snake_head.y++;
		this->m_coordinate.push_back(snake_head);
		snake_head.y++;
		this->m_coordinate.push_back(snake_head); //初始蛇身长度为3

		for (int i=0;i<GameSetting::window_width - 29 + 1 ; i++)
		{
			m_chess[i][0]= true;
			m_chess[i][GameSetting::window_height - 1] = true;
		} //设立边界

		for (int j=0 ; j < GameSetting::window_height - 1; j++)
		{
			m_chess[0][j] = true;
			m_chess[GameSetting::window_width-29][j] = true;
		}//设立边界
	}
	void set_model(bool m) {m_model = m;}//设置游戏模式
	void listen_key_board();//监听键盘
//	void AI_speed();//AI功能
	void AI_find_path(Food &f);//AI功能
	bool self_collision(COORDINATE head);//自我碰撞检测
	void AI_move_snake(Food &f);//AI功能
	void move_snake();
	bool is_eat_food(Food & f);
	bool snake_is_alive();
	void draw_snake();
	void ClearSnake();
	int GetSnakeSize();
	bool GetModel();
};

void Snake::listen_key_board()
{
	char ch;
	if (_kbhit())//检测是否有键入
	{
		ch =_getch(); //得到键入变量
		switch(ch)
		{
		case 'w':
		case 'W':
			if (this->m_direction == DOWN)
				break;//反向
			this->m_direction = UP; //向上
			break;
		case's':
		case'S':
			if (this->m_direction == UP)
				break;
			this->m_direction = DOWN;
			break;
		case'a':
		case'A':
			if (this->m_direction == RIGHT)
				break;
			this->m_direction = LEFT;
			break;
		case'd':
		case'D':
			if (this->m_direction == LEFT)
				break;
			this->m_direction = RIGHT;
			break;
		case '+':
			if (speed>=0) //speed是休眠时间，时间越短速度越快
			{
				speed-=25;
			}
		case '-':
			if (speed<250)
			{
				speed+=25;
			}
			break;
		}
	}
}



void Snake::AI_find_path(Food &f)
{
	static int not_found = 1;
	COORDINATE fpoint = f.GetFoodCoordinate();//获取食物位置

	for (unsigned int i=0; i<m_coordinate.size();i++)
	{
		m_chess[m_coordinate[i].x][m_coordinate[i].y] = true;
	}
	COORDINATE begin_point, end_point;

	begin_point = m_coordinate[HEAD]; 
	end_point = fpoint; //确定起始点和终止点

	m_AISnake.InitMap((bool**)m_chess);//初始化地图
	m_AISnake.GetPath(begin_point, end_point);//寻找路径
}

bool Snake::self_collision(COORDINATE head)
{
	for (unsigned int i=1;i<m_coordinate.size();i++)
	{
		if (head.x == m_coordinate[i].x && head.y == m_coordinate[i].y) //自我碰撞
		{
			return true;
		}
	}
	return false;
}

void Snake::AI_move_snake(Food &f)
{
	static int cot = 0;
	COORDINATE head,temp;
	if (!m_AISnake.m_paths_queue.empty())
	{
		head = m_AISnake.m_paths_queue.front();
		m_AISnake.m_paths_queue.pop();
	}
	else
	{
		for (int i = 0; i < 4;i++)
		{
			int break_num = rand() % 4;	
			temp = m_coordinate[HEAD];
			int t1=f.GetFoodX(); int t2=f.GetFoodY();
			double d=(temp.x-t1)*(temp.x-t1)+(temp.y-t2)*(temp.y-t2);
			temp.x = temp.x + dir[i][0];
			temp.y = temp.y + dir[i][1];
			
			
			if (temp.x<=0 ||
				(temp.x>=(GameSetting::window_width-2))||
				temp.y<=0 ||
				(temp.y>=(GameSetting::window_height-1))||
				self_collision(temp)||(((temp.x-t1)*(temp.x-t1)+(temp.y-t2)*(temp.y-t2))>d))//路径不通
			{
				
				continue;
			}
				head = temp;
			if (break_num == i)
				break;
		}
	}
		

	m_coordinate.insert(m_coordinate.begin(),head);
}

void Snake::move_snake()
{
	listen_key_board();//监听键盘
	COORDINATE head = m_coordinate[0];//确立蛇头
	switch (this->m_direction)
	{
	case UP:
		head.y--;  //蛇头向上
		break;
	case DOWN:
		head.y++;//蛇头向下
		break;
	case LEFT:
		head.x--;//蛇头向左
		break;
	case RIGHT:
		head.x++;//蛇头向右
	}
	m_coordinate.insert(m_coordinate.begin(),head); //插入新的蛇头
													//是否删除蛇尾在食物类中处理
}

bool Snake::is_eat_food(Food &f) 
{
	COORDINATE food_coordinate = f.GetFoodCoordinate(); //食物位置
	if (m_coordinate[HEAD].x== food_coordinate.x && m_coordinate[HEAD].y == food_coordinate.y)
	{                              
		f.RandomXY(m_coordinate);
		return true;
	}//吃到食物，随机生成食物
	else
	{
		m_coordinate.erase(m_coordinate.end()-1);
		return false;
	}//没有吃到食物，去掉蛇尾
}

bool Snake::snake_is_alive()
{
	if (m_coordinate[HEAD].x<=0 ||
		m_coordinate[HEAD].x>=GameSetting::window_width-29||
		m_coordinate[HEAD].y<=0 ||
		m_coordinate[HEAD].y>=GameSetting::window_height-1)//检测是否撞到墙壁
	{
		m_is_alive = false;  
		return m_is_alive;
	}
	for (unsigned int i	= 1;i<m_coordinate.size();i++)
	{
		if (m_coordinate[i].x == m_coordinate[HEAD].x && m_coordinate[i].y == m_coordinate[HEAD].y)
		{//检测是否自撞
			m_is_alive = false;
			return m_is_alive;
		}
	}
	m_is_alive = true;

	return m_is_alive;
}


void Snake::draw_snake()
{
	setColor(10,0); //设置颜色
	for (unsigned int i=0;i<this->m_coordinate.size();i++)//打印蛇身
	{
		gotoxy(m_coordinate[i].x,m_coordinate[i].y);
		cout<<"*";
	}
	setColor(7,0); 
}

void Snake::ClearSnake()
{
	for (unsigned int i = 0;i < m_coordinate.size(); i++)
	{
		m_chess[m_coordinate[i].x][m_coordinate[i].y] = false;
	}
	gotoxy(m_coordinate[this->m_coordinate.size()-1].x,m_coordinate[this->m_coordinate.size()-1].y);
	cout<<" ";//清除蛇尾
}

int Snake::GetSnakeSize()
{
	return m_coordinate.size();
}

bool Snake::GetModel()
{
	return m_model;
}

int main()
{
	GameSetting setting;
	PrintInfo print_info;
	Snake snake;			//初始化游戏
	setting.GameInt();		//模式选择
											
	print_info.DrawChoiceInfo(); //打印选择游戏模式信息
									
	char ch=_getch();
	switch (ch)
	{
	case '1':
		snake.set_model(true);
		speed = 50;
		break;
	case '2':
		snake.set_model(false);
		speed = 80;
		break;
	default:
		gotoxy(GameSetting::window_width / 2 -10,GameSetting::window_height / 2 + 3);
		cout<< "输入错误!"<<endl;
		cin.get();
		cin.get();
		return 0;
	}
	gotoxy(GameSetting::window_width / 2 - 10,GameSetting::window_height / 2 + 3);
	system("pause");//暂停黑窗口

	print_info.DrawMap();  // 画地图
	print_info.DrawGameInfo(snake.GetModel());  //显示游戏信息
	Food food(snake.m_coordinate); //生成食物


	while (true) //游戏死循环
	{
		print_info.DrawScore(snake.GetSnakeSize());   //刷新成绩
		food.DrawFood();	//画出食物
		snake.ClearSnake(); //清理蛇尾
		snake.is_eat_food(food);//判断是否吃到食物
		if (snake.GetModel() == true)//用户模式选择判断
		{
			snake.move_snake();
		}
		else
		{
			snake.AI_find_path(food);
			snake.AI_move_snake(food);
		}
		snake.draw_snake(); //画蛇
		if (!snake.snake_is_alive()) //判断蛇是否还活着
		{
			print_info.GameOver(snake.GetSnakeSize());
			break;
		}
		Sleep(speed); //控制游戏速度
	}
	cin.get();
	cin.get();
}
#include<iostream>
#include<cstdlib>
#include<windows.h>
#include<conio.h>
#include<ctime>

//初始化需要的数据 
using namespace std;
//游戏的地图大小 
const int WIDTH=20;
const int HIGH=10;
//蛇得身体结构，用数组存每个节点的坐标
int snakeX[100],snakeY[100];
//蛇的长度 
int snakeLength;
//食物的坐标 
int foodX,foodY;
//方向：1-上，2-下，3-左，4-右
int direction;
//游戏状态
bool gameOver;



//初始化游戏 
void setUp(){
	gameOver=false;
	//初始方向向右
	direction=4;
	//蛇的初始化位置在地图正中间 
	snakeX[0]=WIDTH/2;
	snakeY[0]=HIGH/2;
	//蛇的初始化长度为3
	snakeLength=3;
	
	//随机生成食物的位置 
	srand(time(NULL));
	foodX=rand()%WIDTH;
	foodY=rand()%HIGH; 
} 

//绘制游戏地图 
void draw(){
	//清屏
	system("cls"); 
	//绘制上边边框 
	for(int i=0;i<WIDTH+2;i++){
		cout<<"#";
	}
	cout<<endl;
	//绘制中间部分(绘制地图主体部分） 
	for(int i=0;i<HIGH;i++){
		for(int j=0;j<WIDTH;j++){
			//绘制左边框 
			if(j==0){
				cout<<"#"; 
			}
			//判断是否为蛇头
			bool isSnakeHead=(i==snakeY[0]&&j==snakeX[0]);
			//判断是否为蛇身
			bool isSnakeBody=false;
			for(int k=1;k<snakeLength;k++){
				if(i==snakeY[k]&&j==snakeX[k]){
					isSnakeBody=true;
					break;
				}
			} 
			//判断是否为食物
			bool isFood=(i==foodY&&j==foodX);
			if(isSnakeHead){
				cout<<"O";
			}else if(isSnakeBody){
				cout<<"o";
			}else if(isFood){
				cout<<"*";
			}else{
				cout<<" ";
			}
			
			//绘制右边框
			if(j==WIDTH-1){
				cout<<"#";
			} 
		}
		cout<<endl;
	} 
	//绘制下边框 
	for(int i=0;i<WIDTH+2;i++)
		cout<<"#";
	cout<<endl;
	
	//显示分数（分数=蛇得长度-初始长度） 
	cout<<"得分："<<snakeLength-3<<endl;
} 

//控制方向（非阻塞输入，不需要回车）
void input(){
	//判断键盘是否有输入 
	if(_kbhit()){
		switch(_getch()){
			case 'w':direction=1;break;
			case 's':direction=2;break;
			case 'a':direction=3;break;
			case 'd':direction=4;break;
			case 'x':gameOver=true;break;
		}
	}
}

//游戏逻辑
void logic(){
	//记录蛇的位置 ，用于蛇身活动
	int prevX=snakeX[0];
	int prevY=snakeY[0];
	int prev2X,prev2Y;
	
	//移动蛇头的位置
	switch(direction){
		//上 
		case 1:snakeY[0]--;break; 
		//下 
		case 2:snakeY[0]++;break;
		//左 
		case 3:snakeX[0]--;break;
		//右 
		case 4:snakeX[0]++;break;
	} 
	//蛇身跟随移动
	for(int i=1;i<snakeLength;i++){
		prev2X=snakeX[i];
		prev2Y=snakeY[i];
		snakeX[i]=prevX;
		snakeY[i]=prevY;
		prevX=prev2X;
		prevY=prev2Y; 
	} 
	//边界碰撞检测 ：撞墙游戏结束
	if(snakeX[0]<0||snakeX[0]>=WIDTH||snakeY[0]<0||snakeY[0]>=HIGH){
		gameOver=true;
	}
	//自身碰撞检测：撞自己游戏结束 
	for(int i=1;i<snakeLength;i++){
		if(snakeX[0]==snakeX[i]&&snakeY[0]==snakeY[i]){
			gameOver=true;
		}
	} 
	//吃到食物：蛇身变长，重新生成新的食物
	if(snakeX[0]==foodX&&snakeY[0]==foodY){
		snakeLength++;
		foodX=rand()%WIDTH;
		foodY=rand()%HIGH;
	} 
} 

int main()
{
	setUp();
	while(!gameOver){
		draw();
		input();
		logic();
		Sleep(500);
	}
	cout<<"游戏结束！最终得分："<<snakeLength-3<<endl;
	return 0; 
}
 

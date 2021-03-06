#include <stdio.h>
#include <stdlib.h>
/**************************************************/
/*AI算法*/
/*玩家下子在对应区域记为1,电脑下子在对应区域记2,
空白区域为0,定义,存储下子位置的数组与存储可能性的数
组作为全局变量使用*/
/*残留问题：
(1)电脑不会优先选取气最多的棋子进行堵截
以一种诡异的方式暂时解决了
(2)电脑对于双向四与单向四没有判读区分（所以我就有
赢的希望了）
不太想解决，按照算法说明，空连子数是到中级才判别
的东西*/
/**************************************************/
void showGo(int go[][15]);
typedef struct Hand{
	int x;
	int y;
} hand;
int deep(int x, int y, int a_num, int color);
void disDeep();
int deepl(int x, int y, int color);

int play_sum[15][15] = {{0}}, ai_sum[15][15] = {{0}}, go[15][15] = {{0}};
void showHand(hand * a);
hand a[4] = { {-1,0}, {-1,1},{0,1},{1,1}};
int main()
{
	int player_x=1, player_y=1;
	#ifdef DEBUG
	showHand(a);
	#endif
	#ifndef DEBUG
	printf("\033[2J");
	#endif
	showGo(go);
	do{
		printf("----------------------------------------\n");
		scanf("%d%d", &player_x, &player_y);
		if (!(player_x>0&&player_x<16&&player_y>0&&player_y<16)){
			printf("Wrong!");
			break;
		}
		printf("----------------------------------------\n");
		go[player_x-1][player_y-1] = 1;
		//deepl(player_x-1, player_y-1, 1);
		deepl(player_x-1, player_y-1, 1);

		disDeep();
		#ifndef DEBUG
		printf("\033[2J");
		#endif

		showGo(go);
		//deepl(player_x-1, player_y-1, 1);
	}while(player_x<16&&player_y<16);
	//show(go);
	return 0;
}
void showGo(int go[][15])
{
	int i=0, j=0;
	#ifdef DEBUG
	printf("\t");
	#endif
	printf("\t\t\tgo");
	#ifdef DEBUG
	printf("\t\t\t\t\tplay_sum\t\t\t\t\tai_sum");
	#endif
	printf("\n");
	//#ifndef DEBUG
	//printf("   \033[32m1    2    3    4    5    6    7    8    9    10   11   12   13   14   15\n");
	//#endif
	//#ifdef DEBUG
	printf("   \033[32m1   2   3   4   5   6   7   8   9   10  11  12  13  14  15\033[0m\n");
	//#endif
	for (i=0;i<15;i++)
	{
			//#ifndef DEBUG
			if (i<9)
			printf("\033[32m%d  \033[0m", i+1);
			else
			printf("\033[32m%d \033[0m", i+1);
			//#endif
			for (j=0;j<15;j++)
			{
				printf("\033[40m");
				if (go[i][j] == 0)
					printf("\033[30m%d\033[0m", /*go[i][j]*/10);
				//printf("%d", go[i][j]);
				else if(go[i][j] == 1)
					printf("\033[43m\033[33m%d\033[0m", /*go[i][j]*/10);
				else if(go[i][j] == 2)
					printf("\033[44m\033[34m%d\033[0m", /*go[i][j]*/10);
				//想让刚下的棋闪烁，方案是go[i][j]+2,之后遍历的时候再-2,但还得好好想想
				//else if(go[i][j] == 3)
					
				//#ifdef DEBUG
				if (j<14)
				//#endif
				printf("  ");
				#ifndef DEBUG
				//printf(" ");
				#endif
				//printf("\33[0m");
			}
			printf("\033[32m|\033[0m");
			#ifdef DEBUG
			for (j=0;j<15;j++)
			{
				if (play_sum[i][j]!=-1)
				printf("%d", play_sum[i][j]);
				else
				printf("*");
				if (j<14)
				printf("  ");
			}
			printf("\033[32m|\033[0m");
			#endif
			#ifdef DEBUG
			for (j=0;j<15;j++)
			{
				printf("%d", ai_sum[i][j]);
				if (j<14)
				printf("  ");
			}
			printf("|");
			#endif
		printf("\n\n");
	}
}
void showHand(hand * a)
{
	int i = 0;
	for (i=0; i<4;i++)
	{
		printf("%d %d\t", a[i].x, a[i].y);
	}
	printf("\n");
}
/**************************************************/
/*函数功能，将寻路算法的值映射到play_sum数组里
（之后映射到ai_sum里）*/
/**/
/**/
/**************************************************/
void disDeep()
{
	int i=0, j=0;
	int max_p = 0;
	int max_a = 0;
	int x_p=7, y_p=7;
	int x_a=7, y_a=7;
	int x_w=7, y_w=7;
	int flag = 0;//等于0时默认防守，等于一时默认进攻
	int t = 1;//算随机位置时叠加的步长
	//只有空位能参与寻路算法
	for (i=0;i<15;i++)
	{
		for (j=0;j<15;j++)
		{
			if (go[i][j]==0)
			{
				play_sum[i][j] = deepl(i, j, 1);
				ai_sum[i][j] = deepl(i ,j, 2);
			}
			else
			{
				play_sum[i][j] = 0;
				ai_sum[i][j] = 0;
			}
			if (play_sum[i][j]>=max_p)
			{
				if (play_sum[i][j] == max_p)
				{
					if (ai_sum[x_p][y_p] < ai_sum[i][j])
					{
						x_p = i;
						y_p = j;

					}
				}
				else
				{
					x_p = i;
					y_p = j;
				}
				max_p = play_sum[i][j];
			}
			if (ai_sum[i][j]>=max_a)
			{
				x_a = i;
				y_a = j;
				max_a = ai_sum[i][j];
			}
		}
	}
	if (max_p == max_a&&max_a == 1)
	{
		while (1){
		if (go[x_w][y_w] == 0){
			go[x_w][y_w] = 2;
			break;
		}
		else
		{
			if (go[x_w+a[0].x][y_w+a[0].y]==0)
			{
				x_w = x_w + a[0].x;
				y_w = y_w + a[0].y;
				go[x_w][y_w] = 2;
				break;

			}
			else if (go[x_w+a[1].x][y_w+a[1].y]==0)
			{
				x_w = x_w + a[1].x;
				y_w = y_w + a[1].y;
				go[x_w][y_w] = 2;
				break;

			}
			else if (go[x_w+a[2].x][y_w+a[2].y]==0)
			{
				x_w = x_w + a[2].x;
				y_w = y_w + a[2].y;
				go[x_w][y_w] = 2;
				break;

			}
			else if (go[x_w+a[3].x][y_w+a[3].y]==0)
			{
				x_w = x_w + a[3].x;
				y_w = y_w + a[3].y;
				go[x_w][y_w] = 2;
				break;

			}
			else
			{
				x_w = x_w + a[0].x;
				y_w = y_w + a[0].y;
			}
		}
		}
	}
	else{
	//怎么判断棋局已经结束了？下子的那一刻之后就应该有答案，而不是等到下一局进行判断
	//未考虑两子情况优先选择己方连子（待考虑）（解决）（有两个选择的时候可能被覆盖）
	if (deepl(x_a, y_a, 1) >= max_p)
	{
		x_p = x_a;
		y_p = y_a;
	}
	//优先级待完成，目前只有围追堵截（还行）
	if (max_a>max_p)
		flag=1;
	else if (max_a<max_p)
		flag=0;
	else if (max_a=max_p)
	{
		if (max_a>=4)
			flag = 1;
		else
			flag = 0;
	}
	if (flag==0)
	{
		go[x_p][y_p] = 2;
		deepl(x_p, y_p, 2);
	}
	else
	{
		go[x_a][y_a] = 2;
		deepl(x_a, y_a, 2);
	}
	}

}
/**************************************************/
/*寻路算法，计算单一方向的连子数*/
/*x，y是传入的坐标，a是方向*/
/*判断，循环取路，如果a方向上有本方棋子（用color判断）
则继续用该方法判断a方向上的棋子，每次返回a方向上
的棋子数+1*/
/**************************************************/
int deep(int cx, int cy, int num, int color)
{
	int x = cx, y=cy;
	//count是所直接相连的棋子数
	int count = 1;
	//是否持续连接
	int conti = 1;
	//empty是直接相连的棋子数加上空子数（大于5就行），计算棋子是否有下的必要
	int empty = 0;
	#ifdef DEBUG
	//if (x<3)
	//printf("当前坐标为%d, %d", x, y);
	#endif
	//忘了考虑边界情况（x+a[a_num]为非法值的时候），之后考虑(已考虑)，注释掉的区域代表的判断棋子是否有下的必要的部分，具体写法待商榷（已完成）
	if (x+a[num].x>=0&&x+a[num].x<15&&y+a[num].y>=0&&y+a[num].y<15)
	{
		while ((go[x+a[num].x][y+a[num].y]==color||(go[x+a[num].x][y+a[num].y]==0&&empty<5))&&(x+a[num].x>=0&&x+a[num].x<15&&y+a[num].y>=0&&y+a[num].y<15))
		{	
			x = x + a[num].x;
			y = y + a[num].y;
			if (go[x][y]==color && conti == 1)
			{
				#ifdef DEBUG
				printf("当前坐标为%d, %d", x, y);

				printf(" 你进来了，位置是%d, %d, 计数为%d, 颜色为%d，之后计数的大小为", x, y, count, go[x][y]);
				#endif
				count++;
				#ifdef DEBUG
				printf("%d\n", count);
				#endif
			}
			else
			{
				conti = 0;
			}
			if (!(x>=0&&x<15&&y>=0&&y<15))
				break;
			empty++;
		}
	}
	x = cx;
	y = cy;
	conti = 1;
	if (x-a[num].x>=0&&x-a[num].x<15&&y-a[num].y>=0&&y-a[num].y<15)
	{	
		while ((go[x-a[num].x][y-a[num].y]==color||(go[x-a[num].x][y-a[num].y]==0&&empty<5))&&(x-a[num].x>=0&&x-a[num].x<15&&y-a[num].y>=0&&y-a[num].y<15))
		{
			x = x - a[num].x;
			y = y - a[num].y;
			if (go[x][y]==color&&conti == 1)
			{
				#ifdef DEBUG
				printf("当前坐标为%d, %d", x, y);
				printf("你进来了，位置是%d, %d, 计数为%d， 颜色为%d，之后计数的大小为", x, y, count, go[x][y]);
				#endif
				count++;
				#ifdef DEBUG
				printf("%d\n", count);
				#endif
			}
			else
			{
				conti = 0;
			}
			if (!(x>=0&&x<15&&y>=0&&y<15))
				break;
			empty++;
		}
	}
	//对边界情况的判断
	if ((cx==0||cx==14||cy==0||cy==14)&&count<4)
		count = 1;
	if ((cx==1||cx==13||cy==1||cy==13)&&count<3)
		count = 1;
	//if (count>5)
	//{
	//	if (color==1)
	//		printf("你赢了");
	//	else if (color == 2)
	//		printf("你输了");
	//	exit(0);
	//}
	if (empty<5)
		return -1;
	else
		return count;
}
/**************************************************/
/*寻路算法，计算多个方向的连子数*/
/*x，y是传入的坐标*/
/*调用deep(int x, int y, int a_num, int color)*/
/**************************************************/
int deepl(int x, int y, int color)
{
	//int count = 0;printf("\033[2J");

	int a=0, b=0, c=0, d=0;
	int max = a;
	a = deep(x, y, 0, color);
	b = deep(x, y, 1, color);
	c = deep(x, y, 2, color);
	d = deep(x, y, 3, color);
	max = a;
	#ifdef DEBUG
	printf("x=%d;y=%d;a=%d;b=%d;c=%d;d=%d;",  x, y, a, b, c, d );
	#endif
	if (b > max)
		max = b;
	if (c > max)
		max = c;
	if (d > max)
		max = d;
	#ifdef DEBUG
	//if (x<4)
	printf("之后是x=%d;y=%d;a=%d;b=%d;c=%d;d=%d;max=%d;\n",  x, y, a, b, c, d, max );
	#endif
	if (max>=5&&color==go[x][y]&&color!=0)
	{
		if (color==1)
		{
			printf("\033[2J");
			showGo(go);
			printf("你赢了\n");
		}
		else if (color == 2)
		{
			printf("\033[2J");
			showGo(go);
			printf("你输了\n");
		}
		exit(0);
	}
	return max;
}


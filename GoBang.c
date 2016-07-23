#include <stdio.h>
#include <stdlib.h>
/**************************************************/
/*AI算法*/
/*玩家下子在对应区域记为1,电脑下子在对应区域记2,
空白区域为0,定义,存储下子位置的数组与存储可能性的数
组作为全局变量使用*/
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
	showHand(a);
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
		disDeep();
		showGo(go);
	}while(player_x<16&&player_y<16);
	//show(go);
	return 0;
}
void showGo(int go[][15])
{
	int i=0, j=0;
	printf("\t\t\tgo\t\t\t\t\tplay_sum\t\t\t\t\tai_sum\n");
	for (i=0;i<15;i++)
	{
			for (j=0;j<15;j++)
			{
				printf("%d", go[i][j]);
				printf("  ");
			}
			printf("|");
			for (j=0;j<15;j++)
			{
				if (play_sum[i][j]!=-1)
				printf("%d", play_sum[i][j]);
				else
				printf("*");
				printf("  ");
			}
			printf("|");
			for (j=0;j<15;j++)
			{
				printf("%d", ai_sum[i][j]);
				printf("  ");
			}
			printf("|");
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
	int x_p=8, y_p=8;
	int x_a=8, y_a=8;
	int flag = 0;//等于0时默认防守，等于一时默认进攻
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
				play_sum[i][j] = 0;
			if (play_sum[i][j]>max_p)
			{
				x_p = i;
				y_p = j;
				max_p = play_sum[i][j];
			}
			
			if (ai_sum[i][j]>max_a)
			{
				x_a = i;
				y_a = j;
				max_a = ai_sum[i][j];
			}
		}
	}
	//优先级待完成，目前只有围追堵截
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
		go[x_p][y_p] = 2;
	else
		go[x_a][y_a] = 2;

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
	//忘了考虑边界情况（x+a[a_num]为非法值的时候），之后考虑(已考虑)，注释掉的区域代表的判断棋子是否有下的必要的部分，具体写法待商榷（已完成）
	if (x+a[num].x>=0&&x+a[num].x<15&&y+a[num].y>=0&&y+a[num].y<15)
	{
		while (go[x+a[num].x][y+a[num].y]==color||(go[x+a[num].x][y+a[num].y]==0&&empty<5))
		{
			if (go[x+a[num].x][y+a[num].y]==color && conti == 1)
			{
				printf("你进来了，位置是%d, %d\n, 计数为%d\n, 颜色为%d", x, y, count, go[x+a[num].x][y+a[num].y]);
				count++;
				printf("%d\n", count);
			}
			else
			{
				conti = 0;
			}
			x = x + a[num].x;
			y = y + a[num].y;
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
		while (go[x-a[num].x][y-a[num].y]==color||(go[x-a[num].x][y-a[num].y]==0&&empty<5))
		{
			if (go[x-a[num].x][y-a[num].y]==color&&conti == 1)
			{
				printf("你进来了，位置是%d, %d\n, 计数为%d\n", x, y, count);
				count++;
				printf("%d\n", count);
			}
			else
			{
				conti = 0;
			}
			x = x - a[num].x;
			y = y - a[num].y;
			if (!(x>=0&&x<15&&y>=0&&y<15))
				break;
			empty++;
		}
	}
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
	//int count = 0;
	int a=0, b=0, c=0, d=0;
	int max = a;
	a = deep(x, y, 0, color);
	b = deep(x, y, 1, color);
	c = deep(x, y, 2, color);
	d = deep(x, y, 3, color);
	max = a;
	printf("x =%d ;y =%d ; a =%d ; b =%d ; c =%d ; d =%d ;\n",  x, y, a, b, c, d );
	if (b > max)
		max = b;
	if (c > max)
		max = c;
	if (d > max)
		max = d;
	printf("x =%d ;y =%d ; a =%d ; b =%d ; c =%d ; d =%d ; max = %d;\n",  x, y, a, b, c, d, max );

	return max;
}


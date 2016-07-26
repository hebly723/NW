#include <stdio.h>
#include <stdlib.h>
/**************************************************/
/*AI算法中级*/
/*玩家下子在对应区域记为1,电脑下子在对应区域记2,
空白区域为0,定义,存储下子位置的数组与存储可能性的数
组作为全局变量使用*/
/*残留问题：
(1)电脑不会优先选取气最多的棋子进行堵截
以一种诡异的方式暂时解决了
(2)电脑对于双向与单向没有判读区分（所以我就有
赢的希望了）
正在解决
(3)电脑无法识别双龙
应该可以了，也会优先选择双龙来攻击或者堵截
(3)如果获取的点连子外的话，它的双龙判定条件就变成了
选子所在的那一头要有两子或两字以上，不知道是不是bug
(4)五子连1000,四子空连500,四子连200,三子空连100,三
子连50，二子空连20，二子10, 单子5 */
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
		while (!(player_x>0&&player_x<16&&player_y>0&&player_y<16)||(go[player_x-1][player_y-1]!=0)){
			printf("请重新输入:\n");
			scanf("%d%d", &player_x, &player_y);
		}
		printf("----------------------------------------\n");
		go[player_x-1][player_y-1] = 1;
		deepl(player_x-1, player_y-1, 1);

		disDeep();
		#ifndef DEBUG
		printf("\033[2J");
		#endif

		showGo(go);
	}while(player_x<16&&player_y<16);
	return 0;
}
void showGo(int go[][15])
{
	int i=0, j=0;
	#ifdef DEBUG
	//printf("");
	#endif
	printf("\t\t\tgo");
	#ifdef DEBUG
	printf("\t\t\t\t\tplay_sum\t\t\t\t\tai_sum");
	#endif
	printf("\n");
	#ifndef DEBUG
	printf("   \033[32m1   2   3   4   5   6   7   8   9   10  11  12  13  14  15\n");
	#endif
	#ifdef DEBUG
	printf("  \033[32m1 2 3 4 5 6 7 8 9 101112131415\n");
	#endif
	for (i=0;i<15;i++)
	{
			if (i<9)
			printf("\033[32m%d ", i+1);
			else
			printf("\033[32m%d", i+1);
			#ifndef DEBUG
			printf(" ");
			#endif
			for (j=0;j<15;j++)
			{
				printf("\033[40m");
				if (go[i][j] == 0)
					printf("\033[30m%d\033[49m", /*go[i][j]*/10);
				else if(go[i][j] == 1)
					printf("\033[43m\033[33m%d\033[49m", /*go[i][j]*/10);
				else if(go[i][j] == 2)
					printf("\033[44m\033[34m%d\033[49m", /*go[i][j]*/10);
				#ifndef DEBUG
				if (j<14)
				//#endif
				printf("  ");
				#endif
			}
			printf("\033[32m|");
			#ifdef DEBUG
			for (j=0;j<15;j++)
			{
				if (play_sum[i][j]!=-1)
				{
					printf("%d", play_sum[i][j]);
					if (play_sum[i][j]<10)
						printf(" ");
				}
				else
				printf("* ");
				if (j<14&&play_sum[i][j]<100)
				printf(" ");
			}
			printf("\033[32m|");
			#endif
			#ifdef DEBUG
			for (j=0;j<15;j++)
			{
				if (ai_sum[i][j]!=-1)
				{
					printf("%d", ai_sum[i][j]);
					if (ai_sum[i][j]<10)
						printf(" ");
				}
				else
				printf("* ");
				if (j<14&&play_sum[i][j]<100)
				printf(" ");
			}
			printf("|");
			#endif
		printf("\n");
		#ifndef DEBUG
		printf("\n");
		#endif
		//printf("                                                             \n");

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
	//双头情况加一会出现三字进攻优先于四字防守的情况
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
			if (play_sum[i][j]>=(max_p))
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
					max_p = play_sum[i][j];
				}
			}
			if (ai_sum[i][j]>=max_a)
			{
				max_a = ai_sum[i][j];
				x_a = i;
				y_a = j;
			}
		}
	}
	if (max_p == max_a&&max_a == 5)
	{
		while (1)
		{
			if (go[x_w][y_w] == 0)
			{
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
	else if ((max_a)<(max_p))
		flag=0;
	else if ((max_a)==(max_p))
	{
		flag = 1;	
	}
	}
	if (flag==0)
	{
		go[x_p][y_p] = 2;
		deepl(x_p, y_p, 2);
		printf("%d, %d", x_p+1, y_p+1);
	}
	else
	{
		go[x_a][y_a] = 2;
		deepl(x_a, y_a, 2);
		printf("%d, %d", x_a+1, y_a+1);
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
	int empty = 1;
	int emptyl = 0;
	int emptyr = 0;
	//连子两头坐标
	//修正，考虑空连子情况，count个位为连字数，十位是空连子的标志位
	int lx = cx;
	int ly = cy;
	int rx = cx;
	int ry = cy;
	//忘了考虑边界情况（x+a[a_num]为非法值的时候），之后考虑(已考虑)，注释掉的区域代表的判断棋子是否有下的必要的部分，具体写法待商榷（已完成）
	if (x+a[num].x>=0&&x+a[num].x<15&&y+a[num].y>=0&&y+a[num].y<15)
	{
		while ((go[x+a[num].x][y+a[num].y]==color||(go[x+a[num].x][y+a[num].y]==0&&empty<5))&&(x+a[num].x>=0&&x+a[num].x<15&&y+a[num].y>=0&&y+a[num].y<15))
		{	
			x = x + a[num].x;
			y = y + a[num].y;
			if (go[x][y]==color && conti == 1)
			{
				count++;
				lx = x;
				ly = y;
			}
			else
			{
				conti = 0;
				emptyl ++;
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
				count++;
				rx = x;
				ry = y;
			}
			else
			{
				conti = 0;
				emptyr++;
			}
			if (!(x>=0&&x<15&&y>=0&&y<15))
				break;
			empty++;
		}
	}
	if ((go[lx+a[num].x][ly+a[num].y]==0||go[lx][ly]==0)&&(go[rx-a[num].x][ry-a[num].y]==0||go[rx][ry]==0)&&(!(lx == cx&&ly == cy && rx==cx&&ry == cy)))
	{
		if (count>1)
		count = count + 11;//提高了一个优先级
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
/*(4)五子连1000,四子空连500,四子连200,三子空连100,三
子连50，二子空连20，二子10, 单子5 */

/**************************************************/
int deepl(int x, int y, int color)
{
	//int count = 0;printf("\033[2J");

	int a=0, b=0, c=0, d=0;
	int max = a;
	int k[4] = {0};
	int count = 0;
	int sum = 0;
	int i = 0;
	k[0] = deep(x, y, 0, color);
	k[1] = deep(x, y, 1, color);
	k[2] = deep(x, y, 2, color);
	k[3] = deep(x, y, 3, color);
	for (i=0;i<4;i++)
	{
		printf("sum = %d\t, k[i]=%d", sum, k[i]);
		if ((k[i]%10)>=5&&color==go[x][y]&&color!=0)
		{
			if (k[i]>10&&((max%10)-1)<5)
			;
			else if (color==1)
			{
				printf("\033[2J");
				showGo(go);
				printf("你赢了\n");
				exit(0);
			}
			else if (color == 2)
			{
				printf("\033[2J");
				showGo(go);
				printf("你输了\n");
				exit(0);
			}
		}
		switch(k[i])
		{
			case 5:
			case 16:
				if (color == go[x][y])
				{
					if (color == 1)
						printf("你赢了\n");
					else if (color == 2)
						printf("你输了\n");
				}	
				sum += 1000;
				break;
			case 15:
				sum += 500;
				break;
			case 4:
				sum += 200;
				break;
			case 14:
				sum+= 100;
				break;
			case 3:
				sum+= 50;
				break;
			case 13:
				sum+= 20;
				break;
			case 2:
				sum+= 10;
				break;
			case 1:
			case 12:
				sum+= 5;
				break;
			case 0:
				sum+=0;
				break;
			case 6:
			case 17:
				if (color == go[x][y])
				{
					if (color == 1)
						printf("你赢了\n");
					else if (color == 2)
						printf("你输了\n");
					exit(0);
				}
				sum+=10000;
				break;
			case -1:
				sum+=0;
				break;
			default:
				printf("Wrong!k[i] = %d, x = %d, y=%d", k[i], x, y);
				exit(0);
		}
	}
	printf("\n");
	return sum;
}


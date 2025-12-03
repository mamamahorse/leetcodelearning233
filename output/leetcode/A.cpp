#include<iostream>
#include<queue>
#include<string.h>
using namespace std;
int moves[1001][1001];
int dir[8][2]={-2,-1,-2,1,-1,2,1,2,2,1,2,-1,1,-2,-1,-2};
int b1, b2;
// F = G + H
// G = 从起点到该节点路径消耗
// H = 该节点到终点的预估消耗
struct Knight
{
    int x,y;
    int g,h,f;
    bool operator <(const Knight & k)const
    {
        return k.f<f;//配合大顶堆使用，反向逻辑实现了小顶堆。
    }
};

priority_queue<Knight> que;

int Heuristic (const Knight & k)
{
    return (k.x - b1) * (k.x - b1) + (k.y - b2) * (k.y - b2);
}

void astar(const Knight &k)
{
     Knight cur,next;
    que.push(k);
    while(!que.empty())
    {
        cur =que.top();
        que.pop();
        if(cur.x == b1 && cur.y == b2)
		break;
		for(int i = 0; i < 8; i++)
		{
			next.x = cur.x + dir[i][0];
			next.y = cur.y + dir[i][1];
			if(next.x < 1 || next.x > 1000 || next.y < 1 || next.y > 1000)
			continue;//处理边界
			if(!moves[next.x][next.y])
			{
				moves[next.x][next.y] = moves[cur.x][cur.y] + 1;

                // 开始计算F
				next.g = cur.g + 5; // 统一不开根号，这样可以提高精度，马走日，1 * 1 + 2 * 2 = 5
                next.h = Heuristic(next);
                next.f = next.g + next.h;
                que.push(next);
			}
		}
    }
}
int main()
{
    int n, a1, a2;
    cin >> n;
    while (n--) 
    {
        cin >> a1 >> a2 >> b1 >> b2;
        memset(moves,0,sizeof(moves));
        Knight start;
        start.x = a1;
        start.y = a2;
        start.g = 0;
        start.h = Heuristic(start);
        start.f = start.g + start.h;
		astar(start);
        while(!que.empty()) que.pop(); // 队列清空
		cout << moves[b1][b2] << endl;
	}
	return 0;
}

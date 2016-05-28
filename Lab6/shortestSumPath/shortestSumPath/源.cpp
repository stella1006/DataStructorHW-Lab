#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
#include <stdio.h>
using namespace std;
int ROW;
int COL;
#define LL long long
#define INF 1000000
int graph[101][101];   //store the information of graph
bool flag[101][101];   //store the path that is chosen to the result
int d[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};   //four adjacent position


bool valid(int a, int b, int r, int c) {   //check that if the indexs are valid 
	return a >= 0 && a < r && b >= 0 && b < c;
}

struct Path {   //a struct stores the information of row and column index and the distances
	int r, c;
	LL distance;
	Path(int a, int b, int c):r(a), c(b), distance(c){}
	friend bool operator < (const Path & a, const Path & b) {   //override the operator function in order to put the path of shortest distance into the queue
		return a.distance > b.distance;
	}
};


LL shortestSumPath_Dijkstra(const int G[][101], int row, int column, int s0, int s1, int end0, int end1) { 
	memset(flag, 0, sizeof(flag));   //reset the matrix
	priority_queue<Path> q;   //use priority_queue to save the vertexs that is not contained in the resulting path
	flag[s0][s1] = true;     //put the starting point to the resulting path
	Path temp = Path(s0, s1, graph[s0][s1]);
	while (!flag[end0][end1]) {   //nonstop until the ending point is contained in the resulting path
		for (int i = 0; i < 4; i++) {   //check whether four adjacent positions is adding to the resulting path, if not, add to the queue
			int newr, newc;
			newr = temp.r + d[i][0];
			newc = temp.c + d[i][1];
			if (valid(newr, newc, row, column) && !flag[newr][newc])   
				q.push(Path(newr, newc, temp.distance + graph[newr][newc]));
		}

		temp = q.top();
		if (flag[temp.r][temp.c]) {  //pop out the points that is contained in the resulting path
			q.pop();
			temp = q.top();
		}
		flag[temp.r][temp.c] = true;   //put the vertex that is cloest to the resulting path to the resulting path
	}
	return temp.distance;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {   //test cases
		memset(graph, 0, sizeof(graph));    //clear and reset the graph matrix
		
		int row,column, dis;
		scanf("%d%d", &row, &column);
		for (int i = 0; i < row; i++) {   //input the graph's information 
			for (int j = 0; j < column; j++) {
				scanf("%d", &dis);
				graph[i][j] = dis;
			}
		}
		
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		cout << shortestSumPath_Dijkstra(graph, row, column, a-1, b-1, c-1, d-1) << endl;    //output the results
	}
	system("pause");
	return 0;
}

#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <math.h>


using namespace std;

//0:空地   1:墙     @:起点    #:终点     *:寻找过的路 


vector<int> minCostFind(vector<vector<int> >& que, vector<int>& minCost) {
	int minc = INT_MAX;
	int l = -1;
	vector<int> c;
	for(int i = 0; i < minCost.size(); i++) {
		if(minCost[i] < minc) {
			minc = minCost[i];
			l = i;
		}
	}
	if(l == -1) return c;
	
	
	c.push_back(que[l][0]);
	c.push_back(que[l][1]); 
	minCost[l] = INT_MAX;
	return c;
}

bool AStar(vector<string>& map, int startX, int startY, int endX, int endY) {
	vector<vector<int> > cost(map.size(), vector<int>(map[0].size(), INT_MAX));
	
	for(int i = 0; i < cost.size(); i++) {
		for(int j = 0; j < cost[i].size(); j++) {
			if(map[i][j] == '0' || map[i][j] == '@' || map[i][j] == '#') {
				int g = abs(startX - i) + abs(startY - j);
				int h = abs(endX - i) + abs(endX - j);
				cost[i][j] = g + h;
			}
		}
	}
	
	
	vector<int> minCost;
	vector<vector<int> > que;
	vector<int> f;
	f.push_back(startX);
	f.push_back(startY);
	minCost.push_back(cost[startX][startY]);
	que.push_back(f);
	map[startX][startY] = '*';
	
	while(!que.empty()) {
		vector<int> c = minCostFind(que, minCost);
		int x = c[0];
		int y = c[1];
		
		if(x == endX && y == endY) {
			return true;
		}
		
		if(x - 1 >= 0 && (map[x - 1][y] == '0' || map[x - 1][y] == '#')) {
			vector<int> z;
			z.push_back(x - 1);
			z.push_back(y);
			minCost.push_back(cost[x - 1][y]);
			que.push_back(z);
			map[x - 1][y] = '*';
		}
		if(x + 1 < map.size() && (map[x + 1][y] == '0' || map[x + 1][y] == '#')) {
			vector<int> z;
			z.push_back(x + 1);
			z.push_back(y);
			minCost.push_back(cost[x + 1][y]);
			que.push_back(z);
			map[x + 1][y] = '*';
		}
		if(y - 1 >= 0 && (map[x][y - 1] == '0' || map[x][y - 1] == '#')) {
			vector<int> z;
			z.push_back(x);
			z.push_back(y - 1);
			minCost.push_back(cost[x][y - 1]);
			que.push_back(z);
			map[x][y - 1] = '*';
		}
		if(y + 1 < map[x].size() && (map[x][y + 1] == '0' || map[x][y + 1] == '#')) {
			vector<int> z;
			z.push_back(x);
			z.push_back(y + 1);
			minCost.push_back(cost[x][y + 1]);
			que.push_back(z);
			map[x][y + 1] = '*';
		}
	}
}



int main() {
	int high, width;
	vector<string> map;
	
	int startX = -1, startY = -1, endX = -1, endY = -1;
	
	cin >> high >> width;
	
	for(int i = 0; i < high; i++) {
		string str;
		
		cin >> str;
		map.push_back(str);
	}
	
	for(int i = 0; i < high; i++) {
		for(int j = 0; j < width; j++) {
			if(map[i][j] == '@') {
				startX = i;
				startY = j;
			}
			if(map[i][j] == '#') {
				endX = i;
				endY = j;
			}
		}
	}
	
	AStar(map, startX, startY, endX, endY);
	
	for(int i = 0; i < high; i++) {
		for(int j = 0; j < width; j++) {
			cout << map[i][j];
		}
		cout << endl;
	}
	
	return 0;
}

#include <bits/stdc++.h>
#include<iostream>
#include<algorithm>

using namespace std;
const int N  = 3 ;
const int max_tabu_list = 5 ;
const int max_iterations = 20 ;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};


struct tabu_search {
	vector<vector<int>> v;
	int heuristic , x , y;
	tabu_search() {
		heuristic = INT_MAX;	
	}
	tabu_search(vector<vector<int>>& vi, vector<vector<int>>& goal_s, int xi, int yi) {
		v = vi;
		x = xi;
		y = yi;
		heuristic = find_heuristic(goal_s);
	}
	int find_heuristic(vector<vector<int>>& goal_s) {
		int mismatch = 0;
		for(int i = 0; i < 3; ++i) {
			for(int j = 0; j < 3; ++j) {
				if(v[i][j] != goal_s[i][j] && v[i][j] != 0) mismatch++;
			}
		}
		return mismatch;
	}
	
	string store_it_as_string() {
		string ans = "";	
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < N; ++j) {
				ans += v[i][j];
			}
		}
		return ans;
	}
	
	void display() {
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < N; ++j) {
				cout << v[i][j] << " ";
			}
			cout << endl;
		}
		cout<<endl;
	}
};

struct cmp {
	bool operator()(tabu_search& p1,tabu_search& p2) {
		return p1.heuristic < p2.heuristic;
	}
};

int main() {

	vector<vector<int> > init_s = { {1, 2, 3},{4, 8, 5},{7, 0, 6}};
	vector<vector<int> > goal_s = {{1, 2, 3},{4, 5, 6},{7, 8, 0} };
	tabu_search tb(init_s, goal_s, 2, 1);
	tabu_search global_best = tb;

	set<string> tabu_list;
	tabu_list.insert(tb.store_it_as_string());	
	bool found = false;
	
	int curr = 0;  // it is the current level
	while(curr <= max_iterations){
		
		tabu_search prevState = tb;
		cout<<"at "<<curr<<" level : "<<endl;
		tb.display();
		if( tb.v == goal_s ){
			cout <<"Solution found perfectly "<<endl;
			tb.display();
			found = true;
			break;
		}
		
		vector<int> rem_moves = {0, 1, 2, 3};		
		vector<int> extra_moves;
		
		while(!rem_moves.empty()) {
			int randIdx = rand() % rem_moves.size();
			extra_moves.push_back(rem_moves[randIdx]);
			rem_moves.erase(rem_moves.begin() + randIdx);
		}
		
		tabu_search local_best;
		
		for(auto i: extra_moves) {
			vector<vector<int>> currv = tb.v;
			int x = tb.x + dx[i];
			int y = tb.y + dy[i];
			if(x < 0 || y < 0 || x >= N || y >= N) continue;
			swap(currv[tb.x][tb.y], currv[x][y]);
		
			tabu_search currState(currv, goal_s, x, y);
			string currStateString = currState.store_it_as_string();
			
			if(currState.heuristic < local_best.heuristic) {
				if(tabu_list.find(currStateString) != tabu_list.end()) {   // tabu move
					if((rand() % 2)) {             // aspiration criteria  - taking move from tabu list 
						cout << "Tabu move  "<<endl;
					}
					else continue;  //left this move
				}
				local_best = currState;
			}
		}
		
		string local_bestString = local_best.store_it_as_string();
		tabu_list.insert(local_bestString);
		tb = local_best;
		
		if( local_best.heuristic < global_best.heuristic) {
			global_best = local_best;
		}

		if(tabu_list.size() > 4 ){
			auto it = tabu_list.begin() ; 
			tabu_list.erase(it);
		} 
		++curr;
	}
	
	cout << "final achieved state is : "<<endl;
	global_best.display();
	
	return 0;
}

#include <bits/stdc++.h>
#define N 3
using namespace std;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

class PuzzleState {
	public:
	vector<vector<int>> data;
	int heuristic , x , y ;
	PuzzleState(){ } ;
	PuzzleState(vector<vector<int>>& data, vector<vector<int>>& goalState, int x, int y) {
		this->data = data;
		this->x = x;
		this->y = y;
		heuristic = calcHeurisitic(goalState);
	}
	int calcHeurisitic(vector<vector<int>>& goalState) {
		int mismatch = 0;
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < N; ++j) {
				if(data[i][j] != goalState[i][j] && data[i][j] != 0) mismatch++;
			}
		}
		return mismatch;
	}

	string stringify() {
		string build = "";
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < N; ++j) {
				build += data[i][j];
			}
		}
		return build;
	}
	void print() {

		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < N; ++j) {
				cout << data[i][j] << " ";
			}
			cout<<endl;
		}
		cout<<endl;
	}
	int energy() {
		return heuristic;
	}
};

struct MyCmp {
	bool operator()(const PuzzleState& p1, const PuzzleState& p2) {
		return p1.heuristic < p2.heuristic;
	}
};

int main() {
	srand(time(0));
	vector<vector<int>> initialState = {
		{1, 2, 3},
		{7, 8, 4},
		{6, 0, 5}
	};
	vector<vector<int>> goalState = {
		{1, 2, 3},
		{8, 0, 4},
		{7, 6, 5}
	};
	
	PuzzleState pzState(initialState, goalState, 2, 1);
	int depth = 0;
	unordered_set<string> visited;
	visited.insert(pzState.stringify());
	 		
	bool found = false;
	
	int temperature = 20;
	double probFactor = 0.01;
	
	while(temperature > 0) {
		PuzzleState prevState = pzState;
		cout << "Moving to depth: " << depth << "\n";
		
		int oldE = pzState.energy();
		
		if(pzState.data == goalState) {
			cout << "\nSolution found!\n";
			pzState.print();
			found = true;
			break;
		}
		
		bool accepted = false;
	
		while(!accepted) {
			int i = rand() % 4;
			//cout << i << "\n";
			
			vector<vector<int>> currData = pzState.data;
			int x = pzState.x + dx[i];
			int y = pzState.y + dy[i];
			
			if(x < 0 || y < 0 || x >= N || y >= N) continue;
						
			swap(currData[pzState.x][pzState.y], currData[x][y]);
			
			PuzzleState currState(currData, goalState, x, y);
			
			string currStateString = currState.stringify();
			//if(visited.find(currStateString) != visited.end()) continue;
			
			int newE = currState.energy();
			double deltaE = newE - oldE;
			
			
			if(deltaE >= 0) {
				cout << "Adding normally\n";
				//visited.insert(currStateString);
				pzState = currState;
				
				accepted = true;
			} 
			else {
				double prob = exp(-deltaE/temperature);
				double currProb = ((double) rand() / (RAND_MAX)) + 1;
				if(prob > probFactor*currProb) {
					//visited.insert(currStateString);
					pzState = currState;
					cout << "Adding by probability factor\n";			
					accepted = true;				
				}
			}	
		}
		temperature--;
		depth++;
	}
	if(!found) {
		cout << "\nSimulated Annealing failed\n";
	}
	return 0;
}

//8 Puzzle Problem 
// Heuristic function = no. of matching cells.

#include<bits/stdc++.h>
using namespace std;

int dx[4] = { -1 , 0 , 0 , 1 };
int dy[4] = { 0 , -1 , 1 , 0 };

void solve( vector<vector<int>> current, vector<vector<int>>& final, int h, int x_0, int y_0, vector<vector<vector<int>>> temppath, bool& done){
    if( current == final){
        cout<<"Solution Found "<<endl;
        done = true;
        int level = 1 ;
        for(auto matrix: temppath){
            cout<<"At level : "<<level<<endl;
            ++level ; 
            for( auto it : matrix ) {
                for( auto itr : it ){ 
                    cout<<itr<<" ";
                }
                cout<<endl;
            }
            cout<<endl;
        }
        return;
    }
    for(int i=0; i<4; i++){
        int x = x_0 + dx[i];
        int y = y_0 + dy[i];
        if(x >= 0 && y>=0 && x<3 && y < 3 ){
            int new_h = h;
            if( current[x_0][y_0] == final[x_0][y_0] ) new_h--;
            if( current[x][y] == final[x][y]) new_h--;
            swap(current[x_0][y_0], current[x][y]);

            if( current[x_0][y_0] == final[x_0][y_0] ) new_h++;
            if( current[x][y] == final[x][y] ) new_h++;

            //actual concept of simple hill climbing.
            if(new_h > h){
                temppath.push_back(current);
                solve(current, final, new_h, x, y, temppath, done);
                break;  //most important for 'SIMPLE' hill climbing.
            }
            swap(current[x_0][y_0], current[x][y]);
        }
    }
}

int main(){

    vector<vector<int>> initial = {{1,2,3},{7,8,4},{6,0,5}};
    vector<vector<int>> final = {{1,2,3},{0,7,4},{6,8,5}};

    int h = 0;
    for( int i = 0 ; i < 3 ; ++i ){
        for(int j = 0 ; j < 3 ; ++j ){
            if(initial[i][j] == final[i][j]) ++h;
        }
    }
    int x_0 = -1, y_0 = -1; //location of cell containing 0.
    for( int i = 0 ; i < 3 ; ++i ){
        for(int j = 0 ; j < 3 ; ++j ){
            if( initial[i][j] == 0 ){
                x_0 = i;
                y_0 = j;
                break;
            }
        }
    }
    vector<vector<vector<int>>> temppath;
    temppath.push_back(initial);
    bool done = false;
    solve(initial, final, h, x_0, y_0, temppath, done);
    if(!done){
        cout<<"Simple Hill Climbing, is unable to find solution for this 8Puzzle"<<endl;
    }
}
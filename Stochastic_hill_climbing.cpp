//  Stochastic hill climbing is a variant of the basic hill climbing method. While basic
//  hill climbing always chooses the steepest uphill move, "stochastic hill climbing
//  chooses at random from among the uphill moves; the probability of selection can 
// vary with the steepness of the uphill move.

#include<bits/stdc++.h>
using namespace std;
int dx[4] = { -1 , 0 , 0 , 1 };
int dy[4] = { 0 , -1 , 1 , 0 };
void print(vector<vector<vector<int>>>& v  ){
    int level = 1 ;
        for(auto matrix: v ){
            cout<<"At level : "<<level<<endl;
            ++level ; 
            for( auto it : matrix ) {
                for( auto itr : it ){ 
                    cout<<itr<<" ";
                }
                cout<<endl;
            }cout<<endl;
        }
}
void solve( vector<vector<int>> current, vector<vector<int>>& final, int h, int x_0, int y_0, vector<vector<vector<int>>>& temppath, bool& done){
    temppath.push_back(current);
    if( current == final){
        cout<<"Solution Found "<<endl;
        done = true;
        print(temppath) ;
        return;
    }

    vector<vector<int>> random_moves ;  // for schotastic 

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

            if(new_h > h){
                random_moves.push_back({x , y , new_h }) ;
            }
            swap(current[x_0][y_0], current[x][y]);
        }
    }
    // cout<<"sz : "<<random_moves.size()<<endl; 
    if(random_moves.size()> 0  ){
        int random_num = rand() % random_moves.size() ;
        // cout<<random_num<<endl;
        int x_ = random_moves[random_num][0] ;
        int y_ = random_moves[random_num][1] ;
        int heu = random_moves[random_num][2] ;
        swap(current[x_0][y_0], current[x_][y_]);
        solve(current, final, heu , x_, y_, temppath, done);
    }
}
int main(){
    srand(time(NULL)) ;
    vector<vector<int>> initial = {{1,2,3},{7,8,4},{6,0,5}};
    vector<vector<int>> final = {{1,2,3},{8,0,4},{7,6,5}};
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
    bool done = false;
    solve(initial, final, h, x_0, y_0, temppath, done);
    if(!done){
        cout<<"Steepest Accent, is unable to find solution for this 8Puzzle"<<endl;
        print(temppath);
    }
    return 0;
}
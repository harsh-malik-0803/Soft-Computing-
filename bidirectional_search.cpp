#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
vector<vector<int>> adj;

void BFS( queue<int>& que , vector<bool> &visited, vector<int> &parent ){
    int current = que.front();
    que.pop();
    
    for(auto it : adj[current] ){
        if( !visited[ it ] ){
            parent[ it ] = current ;
            visited[ it ] = true;
            que.push( it );
        }
    }
};

int isIntersecting(vector<bool>& visited_s, vector<bool>& visited_t){
    int n = visited_s.size() ;
    for(int i = 0 ; i < n ; i++ ){
        if(visited_s[i] && visited_t[i]) return i;
    }
    return -1;
};

void printPath(vector<int>& parent_s, vector<int>& parent_t , int s, int t, int intersectNode){

    vector<int> path;
    path.push_back(intersectNode);
    int i = intersectNode;

    while (i != s){
        path.push_back(parent_s[i]);
        i = parent_s[i];
    }
    reverse(path.begin(), path.end());
    i = intersectNode;

    while(i != t){
        path.push_back(parent_t[i]);
        i = parent_t[i];
    }
 
    cout<<"   Path is :   \n";
    for( auto it : path )  cout<<it<<" ";
    cout<<endl;

};

void bidirectional_search (int s, int t , int n ){

    vector<bool> visited_s(n , 0 ) , visited_t(n , 0 )  ; 
    vector<int> parent_s(n , 0 ), parent_t(n , 0 );
    queue<int> q_s, q_t;
 
    q_s.push(s);
    q_t.push(t);

    visited_s[s] = true;
    visited_t[t] = true;

    parent_s[s]= -1;
    parent_t[t]= -1;
 
    while (!q_s.empty() && !q_t.empty()){

        BFS( q_s, visited_s, parent_s );
        BFS( q_t, visited_t, parent_t );
 
        int intersectNode = isIntersecting( visited_s , visited_t );
 
        if(intersectNode != -1){
            cout << "Path exist between " << s << " and " << t << "\n";
            cout << "Intersection at: " << intersectNode << "\n";
            printPath( parent_s , parent_t , s , t , intersectNode );
            return ;
        }
    }
    return ;
}


int main(){
    int n ;
    cout<<"Enter no of nodes ";
    cin>>n;
    adj.resize(n ) ;
    int m ;
    cout<<"Enter no of edges ";
    cin>>m;
    for(int i = 0 ; i< m ; ++i ){
        int l , r ;
        cin>>l >>r;
        adj[l].push_back(r) ;
        adj[r].push_back(l);
    }

    bidirectional_search(0 , n-1 , n ) ;
}
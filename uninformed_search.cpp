#include<iostream>
#include<vector>
#include<queue>
using namespace std;
void dfs(int src , vector<vector<int> >& adj , vector<bool>& visited , vector<int>& ans ){
    visited[src] = 1 ;
    ans.push_back(src) ;
    for(int it : adj[src]){
        if(!visited[it]){
            dfs(it , adj ,  visited , ans ) ;
        }
    }
}
void bfs(int src , vector<vector<int>>& adj , vector<bool>& visited , vector<int> & ans  ){
    
    queue<int> q ;
    q.push(src);
    while(!q.empty()){
        auto f = q.front();
        q.pop();
        if(visited[f]) continue;
        ans.push_back(f) ; 
        visited[f] = 1 ; 
        for(auto it : adj[f]){
            if(!visited[it]){
                q.push(it) ;
            }
        }
    }
    
}


void depth_dfs(int src , vector<vector<int> >& adj , vector<bool>& visited , vector<int>& ans , int depth ){
    if(depth == 0 ) return ; 
    visited[src] = 1 ;
    ans.push_back(src) ;
    for(int it : adj[src]){
        if(!visited[it]){
            depth_dfs(it , adj , visited , ans , depth -1 ) ;
        }
    }
}

int height (vector<vector<int>>& adj , int src , int n ){
    vector<bool> visited(n , 0 );
    
    queue<int> q ;
    q.push(src);
    int height = 0 ;
    while(!q.empty()){
        int len = q.size() ;

        for(int i = 0 ; i< len ; ++i ){
            auto f = q.front();
            q.pop();
            if(visited[f]) continue;
            visited[f] = 1 ; 
            for(auto it : adj[f]){
                if(!visited[it]){
                    q.push(it) ;
                }
            }
        }
        ++height ;
    }
    return height ;
}

void iterative_deepening(int src , vector<vector<int> >& adj , vector<bool>& visited , vector<int>& ans  , int max_depth ){
    int n = adj.size() ;
    for(int depth = 1 ; depth <= max_depth ; ++depth ){
        depth_dfs(src , adj , visited , ans , depth ) ;
        cout<<"Till depth "<<depth<<" : ";
        for(auto it : ans ){
            cout<<it<<" ";
        }    
        cout<<endl;
        visited.clear();
        visited.resize(n , 0 );
        ans.clear();
    }
}

void print_tree(string what , vector<int> & ans , vector<bool> & visited , int n ){
    cout<<what<<" traversal is : ";
    for(auto it : ans ){
        cout<<it<<" ";
    }
    cout<<endl;
    visited.clear();
    visited.resize(n , 0 );
    ans.clear();
}

int main(){
    int n ;
    cout<<"Enter no of nodes ";
    cin>>n;
    vector<vector<int>> adj(n) ;
    int m ;
    cout<<"Enter no of edges ";
    cin>>m;
    for(int i = 0 ; i< m ; ++i ){
        int l , r ;
        cin>>l >>r;
        adj[l].push_back(r) ;
        adj[r].push_back(l);
    }
    vector<int> ans ;
    vector<bool> visited(n , 0 ) ;

    // printing dfs
    dfs(0 , adj , visited , ans ) ;
    print_tree( "dfs" , ans , visited , n ) ;
    cout<<endl;
    
    // printing bfs 
    bfs(0 , adj , visited , ans ) ;
    print_tree( "bfs" , ans , visited , n ) ;
    cout<<endl;

    int max_depth = height(adj , 0 , n ) ;
    // depth dfs is : 
    depth_dfs(0 , adj , visited , ans , max_depth ) ;
    print_tree( "depth_dfs" , ans , visited , n ) ;
    cout<<endl;

    // iterative deepening is : 
    cout<<"For iterative deepening : "<<endl;
    iterative_deepening(0 , adj , visited , ans , max_depth ) ;
    
}
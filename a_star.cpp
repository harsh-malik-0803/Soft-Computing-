#include<bits/stdc++.h>
using namespace std;
vector<int> iHeuristic ;
class node{
    public:
    int val , heuristic , dist ;
    node(){
    }
    node(int v , int h , int d ){
        val = v ; 
        heuristic = h ; 
        dist = d ; 
    }
};
int h_function(int node ){
    return iHeuristic[node] ;
}
struct cmp {
    bool operator()(node & n1 , node & n2 ){
        return n1.dist + n1.heuristic > n2.heuristic + n2.dist ; 
    }
};
int A_star(vector<vector<pair<int, int>>> &adj, int src, int dest, int n ){
    priority_queue<node , vector<node> , cmp > open;
    set<int> closed;
    open.push(node(src , 0 , 0 )) ;
    while( !open.empty() ){
        auto f = open.top() ;  open.pop() ;
        closed.insert(f.val) ;
        cout<<f.val<<" ";
        if(f.val == dest ) return f.heuristic + f.dist ; 

        for( auto it : adj[f.val] ){
            if( closed.find( it.first ) == closed.end() ){
                open.push(node(it.first , h_function(it.first ) , f.dist + it.second ) ) ;
            }
        }
    }
    return INT_MAX ; 
}
int main(){   
    int n ;
    cout<<"Enter total number of nodes : ";
    cin>>n ;
    vector<vector<pair<int, int>> > adj(n);
    int m ;
    cout<<"Enter total number of edeges : ";
    cin>>m ;
    for(int i = 0 ; i<m ; i++ ){
        cout<<"Enter u, v, w : ";
        int u,v,w ;
        cin>>u>>v>>w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    int src, destination ;
    cout<<"Enter source node : ";
    cin>>src;
    cout<<"Enter destination node : ";
    cin>>destination;
    iHeuristic.resize(n , 0 ) ;
    cout<<"Enter heuristic value for each node : " ;
    for(int i = 0 ; i< n ; ++i ){
        cin>>iHeuristic[i] ;
    }
    int aDist = A_star(adj, src, destination, n) ;
    cout<<" \nA* distance is : "<<aDist<<endl;
    return 0;
}

// 6
// 8
// 0 1 1
// 0 5 10
// 1 2 2
// 1 3 1
// 3 4 3
// 3 5 4
// 4 5 2
// 2 4 5
// 0 5
// 5 3 4 2 6 0
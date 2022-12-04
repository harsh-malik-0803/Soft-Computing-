#include<bits/stdc++.h>
#include<time.h>
using namespace std;
class Ant{
    bool* visited;
    int no_of_cities;
    public:
    vector<int> trail;
    Ant(int cities){
        no_of_cities = cities;
        visited = new bool[cities];
        for(int i =0; i<no_of_cities; i++){
            visited[i]=  false;
        }
        trail.clear();
    }
    void visitCity(int city){
        visited[city] = true;
        trail.push_back(city);
    }
    bool isVisited(int city){
        return visited[city];
    }
    double trailLength(int** adj){
        if(trail.size() == 0) return 0;
        double length = 0.0;
        for(int i =0; i<trail.size() -1; i++){
            length += adj[trail[i]][trail[i+1]];
        }
        // cout<<trail.size()<<" "<<trail.front()<<" "<<trail.back()<<" ";
        length += adj[trail.back()][trail.front()];
        return length;
    }
    void reintialise(){
        for(int i =0; i<no_of_cities; i++){
            visited[i]= false;
        }
    }
};
class Ant_Colony{
    double ant_factor = 0.8;
    double alpha = 2;
    double beta = 4;
    double evaportaion = 0.5;
    double random_factor = 0.1;
    double Q = 500;
    double* probabilities;
    int** adjMatrix;
    double** pheremone;
    int no_of_cities;
    int no_of_ants;
    vector<int> bestPath;
    double minCost;
    vector<Ant*> ants;
    void getInputGraph(){
        for(int i =0; i<no_of_cities; i++){
            for(int j = i; j<no_of_cities; j++){
                if(i == j) adjMatrix[i][j] = 0;
                else {
                    adjMatrix[i][j] = rand()%50 + 5;
                    adjMatrix[j][i] = adjMatrix[i][j];
                }
                pheremone[i][j] = 100;
            }
        }
    }
    void getProbability(Ant* a){
        int curr_city = a->trail[a->trail.size() - 1];
        double total_pheromone =0.0;
        for(int i =0; i<no_of_cities; i++){
            if(!a->isVisited(i)){
                total_pheromone += pow(pheremone[curr_city][i], alpha)*pow(1.0/adjMatrix[curr_city][i], beta);
                
            }
        }
        for(int i =0; i<no_of_cities; i++){
            if(a->isVisited(i)) probabilities[i] = 0.0;
            else{
                double pheromone_of_city = pow(pheremone[curr_city][i], alpha)*pow(1.0/adjMatrix[curr_city][i], beta);
                probabilities[i] = pheromone_of_city/total_pheromone;
            }
        }
    }
    void updatePheromones(){
        for(int i =0; i<no_of_cities; i++){
            for(int j = 0; j<no_of_cities; j++){
                pheremone[i][j] *= evaportaion;
            }
        }

        for(auto ant : ants){
            double contribution = Q/ant->trailLength(adjMatrix);
            for(int i = 0; i<ant->trail.size() - 1; i++){
                pheremone[ant->trail[i]][ant->trail[i+1]] += contribution;
            }
            pheremone[ant->trail.back()][ant->trail.front()] += contribution;
        }
    }
    void setupAnts(){
        for(int i =0; i<no_of_cities; i++){
            for(int j =0; j<no_of_cities; j++){
                pheremone[i][j] = 100;
            }
        }
        for(auto ant : ants){
            ant->reintialise();
            int city_no = rand()%(no_of_cities);
            ant->visitCity(city_no);
        }
    }
    void moveAnts(){
        for(auto ant : ants){
            ant->visitCity(selectNextCity(ant));
        }
    }
    int selectNextCity(Ant* a){
        double r = (double)rand()/(double) RAND_MAX;
        int city = -1;
        if(r < random_factor){
            while(city == -1){
                int c = rand()%no_of_cities;
                if(a->isVisited(c) == false){
                    city = c;
                    break;
                }
            }
        }else{
            getProbability(a);
            double p = 0.0;
            for(int i =0; i<no_of_cities; i++){
                p += probabilities[i];
                if(p >= r){
                    city = i;
                    break;
                }
            }
        }
    
        return city;
    }
    void updateBest(){
        if(bestPath.size() == 0){
            bestPath = ants[0]->trail;
            minCost = ants[0]->trailLength(adjMatrix);
        }

        for(auto ant : ants){
            double len = ant->trailLength(adjMatrix);
            if(len < minCost){
                bestPath = ant->trail;
                minCost = len;
            }
        }
    }
    public:
     Ant_Colony(int cities){
        no_of_cities = cities;
        adjMatrix = new int*[cities];
        pheremone = new double*[cities];
        probabilities = new double[no_of_cities];
        no_of_ants = cities*ant_factor;
        for(int i =0; i<cities; i++){
            adjMatrix[i] = new int[cities];
            pheremone[i] = new double[cities];
        }
        for(int i =0; i<no_of_ants; i++){
            ants.push_back(new Ant(no_of_cities));
        }
        getInputGraph();
    }
    void solve(){
        setupAnts();
        for(int j = 1; j<no_of_cities; j++){
            moveAnts();
            updatePheromones();
        }
        updateBest();
        cout<<"Minimum cost for travelling : "<<minCost<<endl;;
        cout<<"Path of traversal : ";
        for(auto it : bestPath){
            cout<<it<<" ";
        }
    }
    void show(){
        cout<<"The adjacency matrix is : \n";
        for(int i = 0; i<no_of_cities; i++){
            for(int j =0; j<no_of_cities; j++){
                cout<<adjMatrix[i][j]<<" ";
            }
            cout<<"\n";
        }
    }
};
int main(){
    srand(time(0));
    Ant_Colony* ac = new Ant_Colony(4);
    ac->show();
    ac->solve();
    return 0;
}
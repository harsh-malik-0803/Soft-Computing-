#include<bits/stdc++.h>
#include<time.h>
using namespace std;
double calculate_fitness(double* position, int dimension){
    double fitness = 0.0;
    for(int i =0; i<dimension; i++){
        fitness += position[i]*position[i];
    }
    return fitness;
}   
void copy_value(double* src, double* dest, int dimension){
    for(int i =0; i<dimension; i++){
        dest[i] = src[i];
    }
}
class Particle{
    public:
    double dimension;
    double* position;
    double* velocity;
    double* best_particle_position;
    double best_particle_fitness;
    double min_acceptable, max_acceptable;
    double fitness;

    Particle(){}
    Particle(int d, double mi, double ma){
        dimension = d;
        position = new double[d];
        velocity = new double[d];
        best_particle_position = new double[d];
        min_acceptable = mi;
        max_acceptable = ma;
        for(int i =0; i<d; i++){
            double rand_pos = mi +  1.0*(rand()/RAND_MAX)*(ma - mi);
            position[i] = rand_pos;
            best_particle_position[i] = position[i];

            double rand_velocity = mi + 1.0*(rand()/RAND_MAX)*(ma- mi);
            velocity[i] = rand_velocity;
        }
        fitness = calculate_fitness(position, d);
        best_particle_fitness = fitness;
    }
};
double* particle_swarm_optimization(int max_iteration, int dimension, int minx, int maxx, int n){
    double intertia = 0.8;
    double c1 = 1.5, c2 = 1.5;
    Particle** swarm;
    swarm = new Particle*[n];
    for(int i=0; i<n; i++){
        swarm[i] = new Particle(dimension, minx, maxx);
    }
    double* best_swarm_position = new double[dimension];
    double best_swarm_fitness = DBL_MAX_EXP;
    for(int i =0; i<n; i++){
        if(swarm[i]->fitness < best_swarm_fitness){
            best_swarm_fitness = swarm[i]->fitness;
            copy_value(swarm[i]->position, best_swarm_position, dimension);
        }
    }
    int i =0;
    while(i++ < max_iteration){
        if(i%10 == 0){
            cout<<"At iteration "<<i<<" best fitness value : "<<best_swarm_fitness<<"\n\n";
        }
        for(int i =0; i<n; i++){
            for(int j =0; j<dimension; j++){
                double r1 = 1.0*rand()/RAND_MAX;
                double r2 = 1.0*rand()/RAND_MAX;
                swarm[i]->velocity[j] = (intertia * swarm[i]->velocity[j]  + c1*r1*(swarm[i]->best_particle_position[j] - swarm[i]->position[j]) + c2*r1*(best_swarm_position[j] - swarm[i]->position[j]));
                if(swarm[i]->velocity[j] > maxx) swarm[i]->velocity[j] = maxx;
                else if(swarm[i]->velocity[j] < minx) swarm[i]->velocity[j] = minx;
                swarm[i]->position[j] += swarm[i]->velocity[j];
            }
            swarm[i]->fitness = calculate_fitness(swarm[i]->position, dimension);
            if(swarm[i]->fitness < swarm[i]->best_particle_fitness){
                swarm[i]->best_particle_fitness = swarm[i]->fitness;
                copy_value(swarm[i]->position, swarm[i]->best_particle_position, dimension);
            }
            if(swarm[i]->fitness  < best_swarm_fitness){
                best_swarm_fitness = swarm[i]->fitness;
                copy_value(swarm[i]->position, best_swarm_position, dimension);
            }
        }
    }
    return best_swarm_position;
}


int main(){
    srand(time(0));
    cout<<"Begin PSO for Sphereproblem with fitness = sum(x^2)\n";
    int dimension = 3;
    cout<<"Goal is to minimise fitness\n\n";

    int num_particles = 50;
    int max_iteration = 100;

    cout<<"Number of particles  : "<<50<<"\n";

    double* best_positon = particle_swarm_optimization(max_iteration, dimension, -10.0, 10.0, num_particles);

    double best_fitness=  calculate_fitness(best_positon, dimension);

    cout<<"Best fitness achieved is : "<<best_fitness<<"\n\n";
    cout<<"Best coordinates are : ";
    for(int i =0; i<dimension; i++){
        cout<<best_positon[i]<<" ";
    }
    cout<<"\n\n";
    return 0;
}
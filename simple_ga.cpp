#include <bits/stdc++.h>
using namespace std;

// f(x) = -x^2 + 5
// 0 <= x <= 31

vector<vector<int>> initPopulation() {
	int n = 4;
	int bits = 5;
	vector<vector<int>> population;
	for(int i = 0; i < n; ++i) {
		vector<int> curr;
		for(int j = 0; j < bits; ++j) {
			curr.push_back(rand()%2);
		}
		population.push_back(curr);
	}
	return population;
}

vector<pair<int, vector<int>>> caclulateFitness(vector<vector<int>> population) {
	int n = population.size();
	int bits = population[0].size();
	vector<pair<int, vector<int>>> fitness;
	for(auto chromosome: population) {
		int value = 0;
		for(int i = 0; i < bits; ++i) {
			value += chromosome[i]*pow(2, bits-i-1);
		}
		fitness.push_back({-(value*value) + 5, chromosome});
	}
	sort(fitness.begin(), fitness.end(), greater<pair<int, vector<int>>>());
	return fitness;
}

vector<vector<int>> selection(vector<pair<int, vector<int>>> populationFitness) {
	return {populationFitness[0].second, populationFitness[1].second};  // only 2 are selected out of 4 
}

vector<vector<int>> crossover(vector<vector<int>> selected) {
	vector<vector<int>> offsprings = selected;
	for(int i = 0; i < selected.size(); i+=2) {
		int bits = selected[i].size();
		// cross point
		int k = rand() % (bits-1);	
		vector<int> parent1 = selected[i];
		vector<int> parent2 = selected[i+1];
		vector<int> offspring1, offspring2;
		for(int j = 0; j < k + 1; ++j) {
			offspring1.push_back(parent1[j]);
			offspring2.push_back(parent2[j]);
		}
		for(int j = k+1; j < bits; ++j) {
			offspring1.push_back(parent2[j]);
			offspring2.push_back(parent1[j]);
		}
		offsprings.push_back(offspring1);
		offsprings.push_back(offspring2);
	}
	return offsprings;
}

vector<vector<int>> mutation(vector<vector<int>> population) {
	int n = population.size()/2;
	int bits = population[0].size();
	int r = rand();
	if(r % 7 == 0) {
		int i = n + rand() % n;
		int bit = rand() % bits;
		// flip bit
		population[i][bit] = 1 - population[i][bit];
	}
	return population;
}

int main() {
	srand(time(0));
	int iterations = 25;
	int overallBest = INT_MIN;
	while(iterations--) {
		vector<vector<int>> population = initPopulation();
		vector<pair<int, vector<int>>> fitnessPopulation = caclulateFitness(population);

		int currBest = fitnessPopulation[0].first;
		cout << "Current best score = " << currBest << "\n";
		overallBest = max(overallBest, currBest);
		
		vector<vector<int>> selected = selection(fitnessPopulation);
		vector<vector<int>> newPopulation = crossover(selected);
		vector<vector<int>> mutated = mutation(newPopulation);
	}
	cout << "\nOverall best score = " << overallBest << "\n";
	return 0;
}
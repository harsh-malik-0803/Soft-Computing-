#include<bits/stdc++.h>
using namespace std;
#define PI 3.1415926

const int NP = 40; // colony size (employed bees+onlooker bees)
const int FoodNumber = NP / 2;//food sources
const int limit = 20;// limit trials 
const int maxCycle = 10;//cycles for search
const int D = 2;//parameters of the problem to be optimized
const double lb = -100;//lower bounds of the parameters
const double ub = 100;//upper bound of the parameters
double result[maxCycle] = { 0 };

//struct of Bees
struct BeeGroup{
	double code[D];//the number of weights and bias is D 
	double trueFit;//objective function value 
	double fitness;//holding fitness values associated with food sources
	double rfitness;//probabilities of food sources (solutions) to be chosen
	int trail;// trial numbers through which solutions can not be improved
}Bee[FoodNumber];
BeeGroup NectarSource[FoodNumber];
BeeGroup EmployedBee[FoodNumber];
BeeGroup OnLooker[FoodNumber];
BeeGroup BestSource;

double random(double start, double end){
	return start + (end - start)*rand() / (RAND_MAX + 1.0);
}
double calculationTruefit(BeeGroup);
double calculationFitness(double);
void initilize(){
	int i, j;
	for (i = 0;i<FoodNumber;i++){
		for (j = 0;j<D;j++){
			//initialized food matrix FoodNumber*D and fulled with random values
			NectarSource[i].code[j] = random(lb, ub);
			EmployedBee[i].code[j] = NectarSource[i].code[j];
			OnLooker[i].code[j] = NectarSource[i].code[j];
			BestSource.code[j] = NectarSource[0].code[j];
		}
		//initialized the food
		NectarSource[i].trueFit = calculationTruefit(NectarSource[i]);
		NectarSource[i].fitness = calculationFitness(NectarSource[i].trueFit);
		NectarSource[i].rfitness = 0;
		NectarSource[i].trail = 0;
		//initialized the employed
		EmployedBee[i].trueFit = NectarSource[i].trueFit;
		EmployedBee[i].fitness = NectarSource[i].fitness;
		EmployedBee[i].rfitness = NectarSource[i].rfitness;
		EmployedBee[i].trail = NectarSource[i].trail;
		//initialized the onlooker
		OnLooker[i].trueFit = NectarSource[i].trueFit;
		OnLooker[i].fitness = NectarSource[i].fitness;
		OnLooker[i].rfitness = NectarSource[i].rfitness;
		OnLooker[i].trail = NectarSource[i].trail;
	}
	//initialized the best food
	BestSource.trueFit = NectarSource[0].trueFit;
	BestSource.fitness = NectarSource[0].fitness;
	BestSource.rfitness = NectarSource[0].rfitness;
	BestSource.trail = NectarSource[0].trail;
}
double calculationTruefit(BeeGroup bee){
	double truefit = 0;
	truefit = 4 - (bee.code[0] * sin(4 * PI * bee.code[0]) - bee.code[1] * sin(4 * PI * bee.code[1] + PI + 1));
	return truefit;
}
double calculationFitness(double truefit){
	double fitnessResult = 0;
	if (truefit >= 0) fitnessResult = 1 / (truefit + 1);
	else fitnessResult = 1 + abs(truefit);
	return fitnessResult;
}
//EMPLOYED BEE PHASE 
void sendEmployedBees(){
	int i, j, k;
	int param2change;
	double Rij;
	for (i = 0;i<FoodNumber;i++){
		param2change = (int)random(0, D);
		while (1){
			k = (int)random(0, FoodNumber);
			if (k != i){
				break;
			}
		}
		for (j = 0;j<D;j++){
			EmployedBee[i].code[j] = NectarSource[i].code[j];
		}
		Rij = random(-1, 1);
		EmployedBee[i].code[param2change] = NectarSource[i].code[param2change] + Rij*(NectarSource[i].code[param2change] - NectarSource[k].code[param2change]);
		if (EmployedBee[i].code[param2change]>ub){
			EmployedBee[i].code[param2change] = ub;
		}
		if (EmployedBee[i].code[param2change]<lb){
			EmployedBee[i].code[param2change] = lb;
		}
		//evaluate new solution
		EmployedBee[i].trueFit = calculationTruefit(EmployedBee[i]);
		EmployedBee[i].fitness = calculationFitness(EmployedBee[i].trueFit);
		if (EmployedBee[i].trueFit<NectarSource[i].trueFit)		{
			for (j = 0;j<D;j++)			{
				NectarSource[i].code[j] = EmployedBee[i].code[j];
			}
			NectarSource[i].trail = 0;
			NectarSource[i].trueFit = EmployedBee[i].trueFit;
			NectarSource[i].fitness = EmployedBee[i].fitness;
		}
		else{
			NectarSource[i].trail++;
		}
	}
}
void CalculateProbabilities(){
	int i;
	double maxfit;
	maxfit = NectarSource[0].fitness;
	for (i = 1;i<FoodNumber;i++)	{
		if (NectarSource[i].fitness>maxfit)
			maxfit = NectarSource[i].fitness;
	}

	for (i = 0;i<FoodNumber;i++)	{
		NectarSource[i].rfitness = (0.9*(NectarSource[i].fitness / maxfit)) + 0.1;
	}
}
//ONLOOKER BEE PHASE 
void sendOnlookerBees(){
	int i, j, t, k;
	double R_choosed;//the rate to be choosed
	int param2change;//parameter to be changed
	double Rij;//random number between [-1,1]
	i = 0;
	t = 0;
	while (t<FoodNumber){
		R_choosed = random(0, 1);
		if (R_choosed<NectarSource[i].rfitness)		{
			t++;
			param2change = (int)random(0, D);
			while (1)			{
				k = (int)random(0, FoodNumber);
				if (k != i)				{
					break;
				}
			}
			for (j = 0;j<D;j++)			{
				OnLooker[i].code[j] = NectarSource[i].code[j];
			}
			Rij = random(-1, 1);
			OnLooker[i].code[param2change] = NectarSource[i].code[param2change] + Rij*(NectarSource[i].code[param2change] - NectarSource[k].code[param2change]);
			if (OnLooker[i].code[param2change]<lb)			{
				OnLooker[i].code[param2change] = lb;
			}
			if (OnLooker[i].code[param2change]>ub){
				OnLooker[i].code[param2change] = ub;
			}
			OnLooker[i].trueFit = calculationTruefit(OnLooker[i]);
			OnLooker[i].fitness = calculationFitness(OnLooker[i].trueFit);
			if (OnLooker[i].trueFit<NectarSource[i].trueFit)			{
				for (j = 0;j<D;j++)				{
					NectarSource[i].code[j] = OnLooker[i].code[j];
				}
				NectarSource[i].trail = 0;
				NectarSource[i].trueFit = OnLooker[i].trueFit;
				NectarSource[i].fitness = OnLooker[i].fitness;
			}
			else			{
				NectarSource[i].trail++;
			}
		}
		i++;
		if (i == FoodNumber)		{
			i = 0;
		}
	}
}
//SCOUT BEE PHASE
void sendScoutBees(){
	int maxtrialindex, i, j;
	double R;//random number between [0,1]
	maxtrialindex = 0;
	for (i = 1;i<FoodNumber;i++){
		if (NectarSource[i].trail>NectarSource[maxtrialindex].trail){
			maxtrialindex = i;
		}
	}
	if (NectarSource[maxtrialindex].trail >= limit)	{
		for (j = 0;j<D;j++)		{
			R = random(0, 1);
			NectarSource[maxtrialindex].code[j] = lb + R*(ub - lb);
		}
		NectarSource[maxtrialindex].trail = 0;
		NectarSource[maxtrialindex].trueFit = calculationTruefit(NectarSource[maxtrialindex]);
		NectarSource[maxtrialindex].fitness = calculationFitness(NectarSource[maxtrialindex].trueFit);
	}
}
void MemorizeBestSource(){
	int i, j;
	for (i = 1;i<FoodNumber;i++){
		if (NectarSource[i].trueFit<BestSource.trueFit){
			for (j = 0;j<D;j++){
				BestSource.code[j] = NectarSource[i].code[j];
			}
			BestSource.trueFit = NectarSource[i].trueFit;
		}
	}
}
int main(){
	char c;
	srand(time(NULL));
	initilize();
	MemorizeBestSource();
	int gen = 0;
	while (gen<maxCycle){
		sendEmployedBees();
		CalculateProbabilities();
		sendOnlookerBees();
		MemorizeBestSource();
		sendScoutBees();
		MemorizeBestSource();
		cout << "Time= " << gen << ", BestSource.trueFit= " << BestSource.trueFit << endl;
		cout << "Solutions= " << BestSource.code[0] << ", " << BestSource.code[1] << endl;
		gen++;
	}
	cout << "PROGRAM ENDED!!" << endl;
	cin >> c;
	return 0;
}
#include <bits/stdc++.h>
using namespace std;
class Member{
    public:
	int x;
	double u;
    Member(){} ;
    Member(int xi , int ui ){
        x = xi ; 
        u = ui ;
    }
};
/* INPUT 5 15 0.5 20 0.85 25 0.8 30 0.5 35 0.3*/
double heightMaxima(int n, vector<Member>& values) {	
	while(n--) {
		std::cout << "Enter Xi Ui = ";
		int x; cin >> x;
		double u; cin >> u;
		values.push_back(Member(x,u));
	}
	Member heightMaxMember = *max_element(values.begin(), values.end(), [](const Member& m1, const Member& m2) {
		return m1.u < m2.u;
	});
	std::cout << "Maxima Height = " << heightMaxMember.x << "\n";
	return heightMaxMember.x;
}
double fom(int n, vector<Member>& values) {	
	while(n--) {
		std::cout << "Enter Xi Ui = ";
		int x; cin >> x;
		double u; cin >> u;
		values.push_back(Member(x,u));
	}
	sort(values.begin(), values.end(), [](const Member& m1, const Member& m2) {
		if(m1.u == m2.u) return m1.x < m2.x;
		return m1.u > m2.u;
	});	
	Member FoM = *max_element(values.begin(), values.end(), [](const Member& m1, const Member& m2) {
		return m1.u < m2.u;
	});
	std::cout << "Maxima FoM = " << FoM.x << "\n";
	return FoM.x;
}
double lom(int n, vector<Member>& values) {	
	while(n--) {
		std::cout << "Enter Xi Ui = ";
		int x; cin >> x;
		double u; cin >> u;
		values.push_back(Member(x,u));
	}
	sort(values.begin(), values.end(), [](const Member& m1, const Member& m2) {
		if(m1.u == m2.u) return m1.x < m2.x;
		return m1.u > m2.u;
	});
	Member LoM = *max_element(values.begin(), values.end(), [](const Member& m1, const Member& m2) {
		return m1.u <= m2.u;
	});
	std::cout << "Maxima LoM = " << LoM.x << "\n";
	return LoM.x;
}
double mom(int n, vector<Member>& values) {	
		while(n--) {
		std::cout << "Enter Xi Ui = ";
		int x; cin >> x;
		double u; cin >> u;		
		values.push_back(Member(x,u));
	}
	sort(values.begin(), values.end(), [](const Member& m1, const Member& m2) {
		if(m1.u == m2.u) return m1.x < m2.x;
		return m1.u > m2.u;
	});
	Member maxEntry = *max_element(values.begin(), values.end(), [](const Member& m1, const Member& m2) {
		return m1.u < m2.u;
	});
	double sum = 0;
	int ni = 0;
	for(auto entry: values) {
		if(entry.u == maxEntry.u) {
			sum += entry.x;
			ni++;
		}
	}
	double MoM = sum/ni;
	std::cout << "Maxima MoM = " << MoM << "\n";
	return MoM;
}

double cog(int n, vector<Member>& values) {	
	while(n--) {
		std::cout << "Enter Xi Ui = ";
		int x; cin >> x;
		double u; cin >> u;
		values.push_back(Member(x,u));
	}	
	// cog calculation
	double numerator = 0;
	double denominator = 0;
	for(auto entry: values) {
		int x = entry.x;
		double u = entry.u;
		numerator += x*u;
		denominator += u;
	}
	double CoG = numerator/denominator;
	std::cout << "CoG = " << CoG << "\n";
	return CoG;
}
/* INPUT 3 2.5  , 1.2 5  , 1.5  , 6.5 2 */
double coa(int n, vector<Member>& values) {	
	while(n--) {
		std::cout << "Enter Xi Ai = ";
		double x; cin >> x;
		double area; cin >> area;
		values.push_back(Member(x, area));
	}
	// coa calculation
	double numerator = 0;
	double denominator = 0;
	for(auto entry: values) {
		double x = entry.x;
		// u = area
		double area = entry.u;
		numerator += x*area;
		denominator += area;
	}
	double CoA = numerator/denominator;
	std::cout << "CoA = " << CoA << "\n";
	return CoA;
}
/* INPUT 5 15 0.5 20 0.85 25 0.8 30 0.5 35 0.3*/
double weightedAvg(int n, vector<Member>& values) {	
	while(n--) {
		std::cout << "Enter Xi Uci = ";
		int x; cin >> x;
		double u; cin >> u;
		
		values.push_back(Member(x,u));
	}
	// weighted avg calculation
	double numerator = 0;
	double denominator = 0;
	for(auto entry: values) {
		int x = entry.x;
		double u = entry.u;
		numerator += x*u;
		denominator += u;
	}
	double weighted_avg = numerator/denominator;
	std::cout << "Weighted Average = " << weighted_avg << "\n";
	return weighted_avg;
}
int main() {
	std::cout << "1. Height Maxima  "<< "2. FoM  "<< "3. LoM  "<< "4. MoM  "<< "5. CoG  "<< "6. CoA  "<< "7. Weighted Avg  ";
	int type;
	std::cout<<"Enter type: ";
	cin >> type;
	int n;
	if(type != 0) {
		std::cout << "Enter number of values: ";
		cin >> n;
	}
	vector<Member> values;
	double crispLimit;
	switch(type) {
		case 1:
			crispLimit = heightMaxima(n, values);
			break;
		case 2:
			crispLimit = fom(n, values);
			break;
		case 3:
			crispLimit = lom(n, values);
			break;
		case 4:
			crispLimit = mom(n, values);
			break;
		case 5:
			crispLimit = cog(n, values);
			break;
		case 6:
			crispLimit = coa(n, values);
			break;
		case 7:
			crispLimit = weightedAvg(n, values);
			break;
		default:
			exit(0);
	}
	std::cout << "Crisp set: ";
	for(auto entry: values) {
		int x = entry.x;
		if(x > crispLimit) std::cout << x << " ";
	}
	std::cout<<endl;
	return 0;
}
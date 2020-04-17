// Count your cousins
// Caleb Rudder
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct person {
	int me = 0;
	int childCount = 0;
	int parent = NULL;
	int grandParent = NULL;
};

void main() {
	ifstream fin("cousins.in");
	if (fin.is_open()) {
		ofstream fout("cousins.out");

		int numberOfRelatives;
		int cousin;
		int cousinsCount;
		int relative;
		vector<person> relatives;
		person tempPerson;
		person person;

		fin >> numberOfRelatives >> cousin;

		while (numberOfRelatives != 0 && cousin != 0) {
			cousinsCount = 0;
			int cousinMarker = 0;
			if (numberOfRelatives == 1) {
				cousinsCount = 0;
				fin >> cousin;
			}
			else {
				//store relatives into a vector of persons
				for (int i = 0; i < numberOfRelatives; i++) {
					fin >> relative;
					person.me = relative;
					relatives.push_back(person);
				}
				//loop through relatives and define grandparents/parents
				for (int i = 1; i < relatives.size(); i++) {

					if (relatives[i - 1].me < (relatives[i].me - 1) && relatives[i - 1].parent == NULL) {
						relatives[i].parent = relatives[i - 1].me;
						relatives[i - 1].childCount++;
					}
					else if (relatives[i - 1].me == relatives[i].me - 1 && relatives[i].parent == NULL) {
						relatives[i].parent = relatives[i - 1].parent;
						relatives[i].grandParent = relatives[i - 1].grandParent;
					}
					else if (relatives[i - 1].me < relatives[i].me + 1 && relatives[i - 1].parent != NULL) {
						for (int j = 0; j < i; j++) {
							if (relatives[j].childCount == 0) {
								relatives[i].parent = relatives[j].me;
								relatives[i].grandParent = relatives[j].parent;
								relatives[j].childCount++;
								break;
							}
						}
					}

				}
				//loop through and count cousins
				for (int i = 0; i < relatives.size(); i++) {
					if (relatives[i].me == cousin) {
						cousinMarker = i;
						break;
					}
				}
				for (int i = 0; i < relatives.size(); i++) {
					if (relatives[cousinMarker].parent == relatives[0].me) {
						cousinsCount = 0;
						break;
					}
					else if (relatives[i].parent != relatives[cousinMarker].parent && relatives[i].grandParent == relatives[cousinMarker].grandParent
								&& relatives[i].grandParent != NULL && relatives[cousinMarker].grandParent != NULL) {
						cousinsCount++;
					}
				}
			}
			fout << cousinsCount << endl;

			relatives.clear();
			fin >> numberOfRelatives >> cousin;
		}

		fout.close();
		fin.close();
	}
	else {
		cout << "Input file not found." << endl;
	}
}
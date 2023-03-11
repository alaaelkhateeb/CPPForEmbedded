#include <iostream>
#include <map>
#include <cstdint>
#include <string.h>

using namespace std;
uint8_t RegisterBank[128];
class Reg {
public:
	uint32_t Command;
	uint8_t Control;
	uint8_t Status;
	uint16_t Options;

};

int main() {
	Reg RegA;
	Reg RegB;
	Reg RegC;
	Reg RegD;
	RegA = { 0,1,2,3};
	RegB = {4,5,6,7};
	RegC = { 8,9,10,11};
	RegD = {12,13,14,15};

	map<string, Reg> test;
	test["RegA"] = RegA;
	test["RegB"] = RegB;
	test["RegC"] = RegC;
	test["RegD"] = RegD;

	map<string, map<string, Reg>> RegisterBank;
	RegisterBank["test"] = test;


	for (map<string, map<string, Reg>>::iterator itr = RegisterBank.begin(); itr != RegisterBank.end(); itr++) {

		for (map<string, Reg>::iterator ptr = itr->second.begin(); ptr != itr->second.end(); ptr++) {
		/*cout << itr->first << " ";*/
			cout << ptr->first<<endl;
			cout << " Command " << (unsigned) ptr->second.Command << endl;
			cout << " Control " << (unsigned) ptr->second.Control << endl;
			cout << " Status " << (unsigned) ptr->second.Status << endl;
			cout << " Option " << (unsigned) ptr->second.Options << endl;
		}
	}

	return 0;

}

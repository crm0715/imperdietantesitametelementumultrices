#include "bank.h"

Bank::Bank( unsigned int numStudents ) {
	for ( unsigned int i = 0; i < numStudents; i++ ) {
		balance.push_back(0); 					//initialize all student balances as zero
	}
    locks = new uCondition[numStudents];
} //Bank

Bank::~Bank() {
    delete[] locks;
}

void Bank::deposit( unsigned int id, unsigned int amount ) {
	balance[id] += amount;
    if (!locks[id].empty() && locks[id].front() <= balance[id]) {
        locks[id].signal();
    } // if
} //deposit

void Bank::withdraw( unsigned int id, unsigned int amount ) {
    if (amount > balance[id]) {
        locks[id].wait(amount);
    } // if
	balance[id] -= amount;
} //withdraw

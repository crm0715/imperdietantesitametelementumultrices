#include "bank.h"

Bank::Bank( unsigned int numStudents ) {
	for ( int i = 0; i < numStudents; i++ ) {
		balance.push_back(0); 					//initialize all student balances as zero
	}
} //Bank

//TODO use wait(amount) and front to signal

void Bank::deposit( unsigned int id, unsigned int amount ) {
	balance[id] += amount;
	while (!lock.empty()) {
		lock.signal();
	} //while
} //deposit

void Bank::withdraw( unsigned int id, unsigned int amount ) {
	while (amount > balance[id]) {
		lock.wait();
	} //while
	balance[id] -= amount;
} //withdraw

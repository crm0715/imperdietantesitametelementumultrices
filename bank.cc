#include "bank.h"

Bank::Bank( unsigned int numStudents ) {
	for ( unsigned int i = 0; i < numStudents; i++ ) {
		balance.push_back(0); 										//initialize all student balances as zero
	}
} //Bank

void Bank::deposit( unsigned int id, unsigned int amount ) {
	balance[id] += amount;											//increase balance
	while (!lock.empty()) {
		lock.signal();
	} //while
} //deposit

void Bank::withdraw( unsigned int id, unsigned int amount ) {
	while (amount > balance[id]) {									//lock until there is enough balance
		lock.wait();
	} //while
	balance[id] -= amount;											//decrease balance
} //withdraw

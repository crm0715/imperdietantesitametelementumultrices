#ifndef __BANK_H
#define __BANK_H

#include <uC++.h>
#include <vector>

_Monitor Bank {
	uCondition lock;											//Used to make sure only withdraw when there is enough funds
	std::vector<unsigned int> balance;							//Keep track of balance
  public:
    Bank( unsigned int numStudents );
    void deposit( unsigned int id, unsigned int amount );		
    void withdraw( unsigned int id, unsigned int amount );
};

#endif

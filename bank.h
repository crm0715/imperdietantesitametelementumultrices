#ifndef __BANK_H
#define __BANK_H

#include <uC++.h>
#include <vector>

_Monitor Bank {
	uCondition lock;
	std::vector<unsigned int> balance;
  public:
    Bank( unsigned int numStudents );
    void deposit( unsigned int id, unsigned int amount );
    void withdraw( unsigned int id, unsigned int amount );
};

#endif

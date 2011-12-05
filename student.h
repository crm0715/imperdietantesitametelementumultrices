#ifndef __STUDENT_H
#define __STUDENT_H

#include <uC++.h>

#include "printer.h"
#include "nameServer.h"
#include "watCardOffice.h"
#include "vendingMachine.h"
#include "watCard.h"

_Task Student {
	Printer &prt;									//printer
	NameServer &nameServer;							//nameserver
	WATCardOffice &cardOffice;						//wat card office
	unsigned int id;								//id for the student
	unsigned int numOfPurchases;					//number of purchases to make
	bool lost;										//marker for is watcard has been lost
	VendingMachine::Flavours favouriteFlavour;		//favourite

	WATCard *watCardHolder;							//wat card pointer
	FWATCard watCard;								//future wat card
	VendingMachine *vendingMachine;					//vending machine to use

    void main();
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases );
    ~Student();
};

#endif

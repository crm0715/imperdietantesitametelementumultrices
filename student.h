#ifndef __STUDENT_H
#define __STUDENT_H

#include <uC++.h>

#include "printer.h"
#include "nameServer.h"
#include "watCardOffice.h"
#include "vendingMachine.h"
#include "watCard.h"

_Task Student {
	Printer &prt;
	NameServer &nameServer;
	WATCardOffice &cardOffice;
	unsigned int id;
	unsigned int numOfPurchases;
	VendingMachine::Flavours favouriteFlavour;

	//WATCard &watCard;
	FWATCard futureWATCard;
	VendingMachine *vendingMachine;

    void main();
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases );
};

#endif

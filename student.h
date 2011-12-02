#ifndef __STUDENT_H
#define __STUDENT_H

#include <uC++.h>

#include "printer.h"
#include "nameServer.h"
#include "watCardOffice.h"

_Task Student {
	Printer &prt;
	NameServer &nameServer;
	WATCardOffice &cardOffice;
	unsigned int id;
	unsigned int maxPurchases;
    void main();
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases );
};

#endif

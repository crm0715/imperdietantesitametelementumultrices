#ifndef __TRUCK_H
#define __TRUCK_H

#include <uC++.h>
#include "printer.h"
#include "nameServer.h"
#include "bottlingPlant.h"

_Task Truck {
	Printer &prt;
	NameServer &nameServer;
	BottlingPlant &plant;
	unsigned int numVendingMachines;
	unsigned int maxStockPerFlavour;
	unsigned int cargo[];

    void main();
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};

#endif

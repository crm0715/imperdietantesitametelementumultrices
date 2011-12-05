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
	unsigned int cargo[];				//used to keep track of number of bottles on truck for each flavour

    void main();
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};

#endif

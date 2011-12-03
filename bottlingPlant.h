#ifndef __BOTTLINGPLANT_H
#define __BOTTLINGPLANT_H

#include <uC++.h>
#include "printer.h"
#include "nameServer.h"
#include "vendingMachine.h"

_Task Truck;

_Task BottlingPlant {
    Printer &prt;
    unsigned int maxShippedPerFlavour;
    unsigned int timeBetweenShipments;
    uCondition cargoReadyLock;
    bool cargoReadyFlag;
    bool plantClosingFlag;
    unsigned int soda[VendingMachine::NUM_OF_FLAVOURS];
    Truck * truck;
    void main();
  public:
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments );
    bool getShipment( unsigned int cargo[] );
};

#endif

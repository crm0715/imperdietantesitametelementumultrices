#ifndef __BOTTLINGPLANT_H
#define __BOTTLINGPLANT_H

#include <uC++.h>
#include "printer.h"
#include "nameServer.h"

_Task Truck;

_Task BottlingPlant {
    Printer &prt;
    NameServer &nameServer;
    unsigned int numVendingMachines;
    unsigned int maxShippedPerFlavour;
    unsigned int maxStockPerFlavour;
    unsigned int timeBetweenShipments;
    uCondition cargoReadyLock;
    bool cargoReadyFlag;
    Truck * truck;
    void main();
  public:
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments );
    bool getShipment( unsigned int cargo[] );
};

#endif

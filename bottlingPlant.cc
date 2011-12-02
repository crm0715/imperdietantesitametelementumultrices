#include "bottlingPlant.h"
#include "vendingMachine.h"
#include "truck.h"

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines, unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments) :
    prt(prt),
    nameServer(nameServer),
    numVendingMachines(numVendingMachines),
    maxShippedPerFlavour(maxShippedPerFlavour),
    maxStockPerFlavour(maxStockPerFlavour),
    timeBetweenShipments(timeBetweenShipments),
    cargoReadyLock(),
    cargoReadyFlag(false)
{

} // BottlingPlant::BottlingPlant


bool BottlingPlant::getShipment(unsigned int cargo[]) {

} // BottlingPlant::getShipment

void BottlingPlant::main() {

} // BottlingPlant::main()

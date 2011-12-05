#include "bottlingPlant.h"
#include "truck.h"
#include "MPRNG.h"

extern MPRNG prng;

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines, unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments) :
    prt(prt),
    maxShippedPerFlavour(maxShippedPerFlavour),
    timeBetweenShipments(timeBetweenShipments),
    cargoReadyLock(),
    cargoReadyFlag(false),
    plantClosingFlag(false)
{
    truck = new Truck(prt, nameServer, *this, numVendingMachines, maxStockPerFlavour);
} // BottlingPlant::BottlingPlant

BottlingPlant::~BottlingPlant() {
	delete truck;
} //BottlingPlant::~BottlingPlant


bool BottlingPlant::getShipment(unsigned int cargo[]) {
    if (plantClosingFlag) {
        return true;
    } // if

    if (!cargoReadyFlag) {
        // wait for cargo to be ready
        cargoReadyLock.wait();
    } // if

    // pick up producation
    for (int i = 0; i < VendingMachine::NUM_OF_FLAVOURS; i++) {
        cargo[i] = soda[i];
    } // for
    return false;
} // BottlingPlant::getShipment

void BottlingPlant::main() {
    prt.print(Printer::BottlingPlant, 'S');
    for ( ;; ) {
        // simulate producation
        yield(timeBetweenShipments);

        // produce some soda
        int count = 0;
        for (int i = 0; i < VendingMachine::NUM_OF_FLAVOURS; i++) {
            soda[i] = prng(0, maxShippedPerFlavour);
            count += soda[i];
        } // for
        prt.print(Printer::BottlingPlant, 'G', count);

        // wake up truck
        cargoReadyFlag = true;
        cargoReadyLock.signal();

        _Accept(~BottlingPlant) {
            break;
        } or _Accept(getShipment) {
            prt.print(Printer::BottlingPlant, 'P');
            // book keeping
            for (int i = 0; i < VendingMachine::NUM_OF_FLAVOURS; i++) {
                soda[i] = 0;
            } // for
            cargoReadyFlag = false;
        } // _Accept
    } // for
    prt.print(Printer::BottlingPlant, 'F');

    // wait for truck to complete final round
    plantClosingFlag = true;
	_Accept(getShipment)
} // BottlingPlant::main()

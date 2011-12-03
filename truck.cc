#include "truck.h"
#include "MPRNG.h"
#include "vendingMachine.h"

extern MPRNG prng;

Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant, unsigned int numVendingMachines, unsigned int maxStockPerFlavour ) :
	prt(prt), nameServer(nameServer), plant(plant), numVendingMachines(numVendingMachines), maxStockPerFlavour(maxStockPerFlavour) {
} //Truck

void Truck::main() {
	prt.print ( Printer::Truck, 'S' );
	while ( true ) {
		VendingMachine **vendingMachines = nameServer.getMachineList();				//get list of locations of vending machines
		yield ( prng ( 1, 10 ) );													//coffee break
		if ( plant.getShipment ( cargo ) ) {										//if bottling plant closing down, terminate
			prt.print ( Printer::Truck, 'F' );
			break;
		} //if
		int shipmentTotal = 0;
		for ( int flavour = 0; flavour <= VendingMachine::NUM_OF_FLAVOURS; flavour++ ) {
			shipmentTotal += cargo[flavour];
		} //for
		prt.print ( Printer::Truck, 'P', shipmentTotal );
		int count = 0;
		while ( vendingMachines[count] != NULL ) {
			VendingMachine *vendingMachine = vendingMachines[count];
			unsigned int *inventory = vendingMachine->inventory();
			int remaining = 0;

			prt.print ( Printer::Truck, 'd', vendingMachine->getId(), shipmentTotal );

			for ( int flavour = 0; flavour <= VendingMachine::NUM_OF_FLAVOURS; flavour++ ) {		//loop through all the flavours
				if ( inventory[flavour] < maxStockPerFlavour ) {
					int available = cargo[flavour];
					int need = maxStockPerFlavour - inventory[flavour];
					if ( available < need ) {
						remaining += need - available;
						inventory[flavour] += available;
						cargo[flavour] = 0;
						shipmentTotal -= available;
					} else {
						inventory[flavour] = maxStockPerFlavour;
						cargo[flavour] -= need;
						shipmentTotal -= need;
					} //if
				}//if
			} //for

			if ( remaining > 0 ) {
				prt.print ( Printer::Truck, 'U', vendingMachine->getId(), remaining );
			} else {
				prt.print ( Printer::Truck, 'D', vendingMachine->getId(), shipmentTotal );
			}//if
			vendingMachine->restocked();
			count++;
			if ( shipmentTotal == 0 ) break;
		} //while
	}//while
}//main


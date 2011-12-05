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
		for ( int flavour = 0; flavour < VendingMachine::NUM_OF_FLAVOURS; flavour++ ) {
			shipmentTotal += cargo[flavour];										//total up the shipment received
		} //for
		prt.print ( Printer::Truck, 'P', shipmentTotal );
		for ( unsigned int i = 0; i < numVendingMachines; i++ ) {					//go to all the vending machines one by one
			VendingMachine *vendingMachine = vendingMachines[i];
			unsigned int *inventory = vendingMachine->inventory();					//get inventory info for vending machine
			int remaining = 0;

			prt.print ( Printer::Truck, 'd', vendingMachine->getId(), shipmentTotal );

			for ( int flavour = 0; flavour < VendingMachine::NUM_OF_FLAVOURS; flavour++ ) {		//loop through all the flavours
				if ( inventory[flavour] < maxStockPerFlavour ) {								//if the flavour needs restocking
					int available = cargo[flavour];												//get the number of bottles available
					int need = maxStockPerFlavour - inventory[flavour];							//get the number of bottles needed
					if ( available < need ) {													//if there is not enough bottles available
						remaining += need - available;											//keep track of the number of bottles not stocked
						inventory[flavour] += available;										//update inventory
						cargo[flavour] = 0;														//update cargo
						shipmentTotal -= available;												//update shipment total count
					} else {																	//if enough, bottles to complete restocking
						inventory[flavour] = maxStockPerFlavour;								//update inventory
						cargo[flavour] -= need;													//update cargo
						shipmentTotal -= need;													//update shipment total
					} //if
				}//if
			} //for

			if ( remaining > 0 ) {																//print messages
				prt.print ( Printer::Truck, 'U', vendingMachine->getId(), remaining );
			} else {
				prt.print ( Printer::Truck, 'D', vendingMachine->getId(), shipmentTotal );
			}//if
			vendingMachine->restocked();														//restock for current vending machine complete
			if ( shipmentTotal == 0 ) break;													//stop if no more bottles on truck
		} //for
	}//while
}//main


#include <uC++.h>
#include <iostream>
#include <stdlib.h>

#include "config.h"
#include "printer.h"
#include "bank.h"
#include "parent.h"
#include "watCardOffice.h"
#include "nameServer.h"
#include "vendingMachine.h"
#include "bottlingPlant.h"
#include "student.h"
#include "MPRNG.h"

using namespace std;

MPRNG prng;

void usage ( char* program ) {
  cerr << "Usage: " << program << " [ config-file [ random-seed (> 0) ] ]" << endl;
  exit( EXIT_FAILURE );	
} //usage

void uMain::main() {

	char* configFile = ( char* ) "soda.config";				//set default config file name to "sode.config"
	int seed = ( int ) getpid();							//set default seed to pid
	struct ConfigParms configParms;

	try {
		if ( argc > 1 ) configFile = ( argv[1] );			//if exist, set config file
		if ( argc > 2 ) seed = atoi ( argv[2] );        	//if exists, set seed
		if ( argc > 3 || seed <= 0 ) {  					//Error checking for argument length and seed
			usage ( argv[0] );
		}
	} catch (...) {
		usage ( argv[0] );
	} //try

	prng.seed ( seed );										//set seed

	processConfigFile ( configFile, configParms );			//process config file

	//Print start message
	cout << "Parent\tWATOff\tNames\tTruck\tPlant\t";

	for (unsigned int i = 0; i < configParms.numStudents; i++) 
		cout << "Stud:" << i << "\t";

	for (unsigned int i = 0; i < configParms.numVendingMachines; i++) 
		cout << "Mach:" << i << "\t";

	for (unsigned int i = 0; i < configParms.numCouriers; i++) 
		cout << "Cour:" << i << "\t";
	cout << endl;

	for (unsigned int i = 0; i < 5 + configParms.numStudents + configParms.numVendingMachines + configParms.numCouriers; i++)
	cout << "*******\t";
	cout << endl;

	//Set up
	{
		Printer printer ( configParms.numStudents, configParms.numVendingMachines, configParms.numCouriers );
		Bank bank ( configParms.numStudents );
		Parent parent ( printer, bank, configParms.numStudents, configParms.parentalDelay );
		WATCardOffice office ( printer, bank, configParms.numCouriers );
		NameServer nameServer ( printer, configParms.numVendingMachines, configParms.numStudents );

		VendingMachine *vendingMachines[configParms.numVendingMachines];
	
		for ( unsigned int i = 0; i < configParms.numVendingMachines; i++ ) {
			vendingMachines[i] = new VendingMachine ( printer, nameServer, i, configParms.sodaCost, configParms.maxStockPerFlavour );
		} //for
	
		BottlingPlant *bottlingPlant  = new BottlingPlant ( printer, nameServer, configParms.numVendingMachines, configParms.maxShippedPerFlavour, configParms.maxStockPerFlavour, configParms.timeBetweenShipments );

		Student *student[configParms.numStudents];

		for ( unsigned int i = 0; i < configParms.numStudents; i++ ) {
			student[i] = new Student ( printer, nameServer, office, i, configParms.maxPurchases );
		} //for

		for ( unsigned int i = 0; i < configParms.numStudents; i++ ) {
			delete student[i];		
		} //for

		delete bottlingPlant;														//delete bottling plant before vending machines
		for ( unsigned int i = 0; i < configParms.numVendingMachines; i++ ) {
			delete vendingMachines[i];
		} //for
	}

	//Print end message
	cout << "***********************" << endl;

} // uMain::main

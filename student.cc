#include "student.h"
#include "MPRNG.h"

#include <iostream>

using namespace std;

extern MPRNG prng;

Student::Student ( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases ) :
	prt ( prt ), nameServer ( nameServer ), cardOffice ( cardOffice ), id ( id ) {

	lost = false;
	numOfPurchases = prng ( 1, maxPurchases );
	favouriteFlavour = (VendingMachine::Flavours) prng ( 0, VendingMachine::NUM_OF_FLAVOURS - 1 );

	prt.print ( Printer::Student, id, 'S', (int) favouriteFlavour, (int) numOfPurchases );

	watCard = cardOffice.create ( id, 5, watCardHolder );
	vendingMachine = nameServer.getMachine ( id );

	prt.print ( Printer::Student, id, 'V', vendingMachine->getId() );
} //Student::Student

void Student::main() {
	Student *This = this;
	for ( unsigned int i = 0; i < numOfPurchases; i++ ) {
		bool done = false;
		while (!done) {
			if (!lost) yield ( prng ( 1, 10 ) );
			try {
				_Enable {
					lost = false;
					VendingMachine::Status status = vendingMachine->buy ( favouriteFlavour, *(watCard()) );
					if (!lost) {
						switch (status) {
							case VendingMachine::STOCK:
								vendingMachine = nameServer.getMachine ( id );
								break;
							case VendingMachine::FUNDS:
								watCard = cardOffice.transfer ( id, vendingMachine->cost() + 5, watCard() );
								break;
							case VendingMachine::BUY:
								prt.print ( Printer::Student, id, 'B', watCard()->getBalance() );
								done = true;
								break;
						} //switch
					} //if
				} //_Enable
			} _CatchResume( WATCardOffice::Lost &lost ) (Student *This) {
				prt.print ( Printer::Student, id, 'L' );
				delete This->watCardHolder;
				This->watCard = This->cardOffice.create ( This->id, 5, This->watCardHolder );
				This->lost = true;
			} //try
		} //while
	} //for
	prt.print ( Printer::Student, id, 'F' );
} //Student::main

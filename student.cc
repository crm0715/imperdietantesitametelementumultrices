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
} //Student::Student

Student::~Student() {
    delete watCardHolder;
}

void Student::main() {
	prt.print ( Printer::Student, id, 'S', (int) favouriteFlavour, (int) numOfPurchases );
	
	watCard = cardOffice.create ( id, 5, watCardHolder );
	vendingMachine = nameServer.getMachine ( id );

	prt.print ( Printer::Student, id, 'V', vendingMachine->getId() );

	for ( unsigned int i = 0; i < numOfPurchases; i++ ) {
		bool done = false;
		while (!done) {
			yield ( prng ( 1, 10 ) );			
			do {
				try {
					_Enable {
		      	    	lost = false;
		            	watCard();
					} //Enable
				
					VendingMachine::Status status = vendingMachine->buy ( favouriteFlavour, *watCard);
					switch (status) {
						case VendingMachine::STOCK:
							vendingMachine = nameServer.getMachine ( id );
							prt.print ( Printer::Student, id, 'V', vendingMachine->getId() );
							break;
						case VendingMachine::FUNDS:
							watCard = cardOffice.transfer ( id, vendingMachine->cost() + 5, watCard );
							break;
						case VendingMachine::BUY:
							prt.print ( Printer::Student, id, 'B', (*watCard).getBalance() );
							done = true;
							break;
					} //switch
				} catch( WATCardOffice::Lost &lostException ) {
					prt.print ( Printer::Student, id, 'L' );
					delete watCardHolder;
					watCard = cardOffice.create ( id, 5, watCardHolder );
					lost = true;
				} //try
			} while (lost);//while
		}//while
	} ///for
	prt.print ( Printer::Student, id, 'F' );
} //Student::main

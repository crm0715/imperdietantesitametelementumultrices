#include "student.h"
#include "MPRNG.h"

extern MPRNG prng;

Student::Student ( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases ) :
	prt ( prt ), nameServer ( nameServer ), cardOffice ( cardOffice ), id ( id ) {

	numOfPurchases = prng ( 1, maxPurchases );
	favouriteFlavour = (VendingMachine::Flavours) prng ( 0, VendingMachine::NUM_OF_FLAVOURS - 1 );

	prt.print ( Printer::Student, 'S', (int) favouriteFlavour, (int) numOfPurchases );

	watCard = cardOffice.create ( id, 5, watCardHolder );
	vendingMachine = nameServer.getMachine ( id );

	prt.print ( Printer::Student, 'V', vendingMachine->getId() );
} //Student::Student

void Student::main() {
	for ( unsigned int i = 0; i < numOfPurchases; i++ ) {
		yield ( prng ( 1, 10 ) );
		VendingMachine::Status status;
		while (status != VendingMachine::BUY) {
			status = vendingMachine->buy ( favouriteFlavour, *watCard() );
			//TODO Lost WatCard
			switch (status) {
				case VendingMachine::STOCK:
					vendingMachine = nameServer.getMachine ( id );
					break;
				case VendingMachine::FUNDS:
					watCard = cardOffice.transfer ( id, vendingMachine->cost() + 5, watCard() );
					break;
				case VendingMachine::BUY:
					prt.print ( Printer::Student, 'B', watCard()->getBalance() );
					break;
			} //switch
		} //while
	} //for
	prt.print ( Printer::Student, 'F' );
} //Student::main

#include "student.h"
#include "MPRNG.h"

extern MPRNG prng;

Student::Student ( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases ) :
	prt ( prt ), nameServer ( nameServer ), cardOffice ( cardOffice ), id ( id ) {

	lost = false;
	numOfPurchases = prng ( 1, maxPurchases );				//decided on the number of purchases
	favouriteFlavour = (VendingMachine::Flavours) prng ( 0, VendingMachine::NUM_OF_FLAVOURS - 1 );		//pick a favourite flavour
} //Student::Student

Student::~Student() {
    delete watCardHolder;									//delete watCardHolder
}

void Student::main() {
	prt.print ( Printer::Student, id, 'S', (int) favouriteFlavour, (int) numOfPurchases );				//print starting message
	
	watCard = cardOffice.create ( id, 5, watCardHolder );												//create watcard
	vendingMachine = nameServer.getMachine ( id );														//find vending machine

	prt.print ( Printer::Student, id, 'V', vendingMachine->getId() );									//print found vending machine message

	for ( unsigned int i = 0; i < numOfPurchases; i++ ) {												//repeat until numOfPurchases are made
		bool done = false;																				//check if a purchase has been made
		while (!done) {																					//loop until a purchase has completed
			yield ( prng ( 1, 10 ) );			
			do {
				try {
					_Enable {
		      	    	lost = false;
		            	watCard();																		//make sure the watcard is availble
					} //Enable
				
					VendingMachine::Status status = vendingMachine->buy ( favouriteFlavour, *watCard);	//buy drink
					switch (status) {
						case VendingMachine::STOCK:
							vendingMachine = nameServer.getMachine ( id );								//if out of stock, switch vending machine
							prt.print ( Printer::Student, id, 'V', vendingMachine->getId() );
							break;
						case VendingMachine::FUNDS:
							watCard = cardOffice.transfer ( id, vendingMachine->cost() + 5, watCard );	//if out of funds, transfer money
							break;
						case VendingMachine::BUY:
							prt.print ( Printer::Student, id, 'B', (*watCard).getBalance() );			//if bought, mark purchases has been completed
							done = true;
							break;
					} //switch
				} catch( WATCardOffice::Lost &lostException ) {
					prt.print ( Printer::Student, id, 'L' );											//print lost card message
					delete watCardHolder;																//delete old watcard
					watCard = cardOffice.create ( id, 5, watCardHolder );								//create a new watcard
					lost = true;																		//mark watCard as lost
				} //try
			} while (lost);//while
		}//while
	} ///for
	prt.print ( Printer::Student, id, 'F' );															//print finished message
} //Student::main

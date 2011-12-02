#include "student.h"
#include "MPRNG.h"
#include "vendingMachine.h"
#include "watCardOffice.h"
#include "watCard.h"

extern MPRNG prng;

Student::Student ( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases ) :
	prt ( prt ), nameServer ( nameServer ), cardOffice ( cardOffice ), id ( id ) {
	numOfPurchases = prng ( 1, maxPurchases );
	favouriteFlavour = (VendingMachine::Flavours) prng ( 0, VendingMachine::NUM_OF_FLAVOURS - 1 );
	watCard = cardOffice.create (id, 5, new WATCard());
} //Student::Student

void Student::main() {
	
} //Student::main

#include "parent.h"
#include "MPRNG.h"

extern MPRNG prng;

Parent::Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay ) :
    prt(prt),
    bank(bank),
    numStudents(numStudents),
    parentalDelay(parentalDelay)
{

} // Parent::Parent

void Parent::main() {
    prt.print(Printer::Parent, 'S');
    for ( ;; ) {
        _Accept(~Parent) {
            break;
        } else {
            // busy wait
            yield(parentalDelay);

            int randAmount = prng(1,3);
            int randStudent = prng(0, numStudents - 1);
            prt.print(Printer::Parent, 'D', randStudent, randAmount);

            // Deposit money
            bank.deposit(randStudent, randAmount);
        } // _Accept
    } // for
    prt.print(Printer::Parent, 'F');
} // Parent::main

#ifndef __WATCARDOFFICE_H
#define __WATCARDOFFICE_H

#include <uC++.h>
#include "watCard.h"
#include "bank.h"
#include "printer.h"

_Task WATCardOffice {
    struct Args {

    };
    struct Job {				// marshalled arguments and return future
        Args args;				// call arguments (YOU DEFINE "Args")
        FWATCard result;			// return future
        Job( Args args ) : args( args ) {}
    };
    _Task Courier { };			// communicates with bank

    void main();
  public:
    _Event Lost {};
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    FWATCard create( unsigned int sid, unsigned int amount, WATCard *&card );
    FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
};

#endif

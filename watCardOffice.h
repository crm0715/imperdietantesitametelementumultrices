#ifndef __WATCARDOFFICE_H
#define __WATCARDOFFICE_H

#include <uC++.h>
#include <vector>
#include <list>
#include "watCard.h"
#include "bank.h"
#include "printer.h"

_Task WATCardOffice {
    struct Args {
        unsigned int sid;
        unsigned int amount;
        WATCard *card;
    };
    struct Job {				// marshalled arguments and return future
        Args args;				// call arguments
        FWATCard result;			// return future
        Job( Args args ) : args( args ) {}
    };

    _Task Courier {
        Printer &prt;
        Bank &bank;
        WATCardOffice &cardOffice;
        unsigned int id;

        void main();
      public:
        Courier(Printer &prt, Bank &bank, WATCardOffice &cardOffice, unsigned int id);
    };

    void createJob(); // used by server to create jobs for courier
    FWATCard transferHelper(unsigned int sid, unsigned int amount, WATCard *card); // used by client to indicate transfer of money is needed
    std::list<Job *> jobs;
    std::vector<Courier *> couriers;

    Printer &prt;

    // for communication
    Args previousArgs;
    FWATCard previousFWATCard;
    bool officeClosingDown;

    void main();
  public:
    _Event Lost {};
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    ~WATCardOffice();
    FWATCard create( unsigned int sid, unsigned int amount, WATCard *&card );
    FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
};

#endif

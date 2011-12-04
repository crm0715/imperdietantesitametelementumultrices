#include "watCardOffice.h"
#include "MPRNG.h"
#include <iostream>

using namespace std;
extern MPRNG prng;

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) :
    prt(prt),
    officeClosingDown(false)
{
    for (unsigned int i = 0; i < numCouriers; i++) {
        Courier *courier = new Courier(prt, bank, *this, i);
        couriers.push_back(courier);
    } // for
} // WATCardOffice::WATCardOffice

WATCardOffice::~WATCardOffice() {
    for (unsigned int i = 0; i < couriers.size(); i++) {
        delete couriers[i];
    } // for
    for (list<Job *>::const_iterator iter = jobs.begin(); iter != jobs.end(); ++iter) {
        delete *iter;
    } // for
} // WATCardOffice::~WATCardOffice

FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount, WATCard *&card ) {
    card = new WATCard();

    return transferHelper(sid, amount, card);
} //WATCardOffice::create

FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
    return transferHelper(sid, amount, card);
} //WATCardOffice::transfer

WATCardOffice::Job *WATCardOffice::requestWork() {
    if (officeClosingDown) {
        return NULL;
    } // if

    return jobs.front();
} //WATCardOffice::requestWork

FWATCard WATCardOffice::transferHelper(unsigned int sid, unsigned int amount, WATCard *card) {
    Args arg;
    arg.sid = sid;
    arg.amount = amount;
    arg.card = card;

    FWATCard fCard;

    // store info in member varaible for communication with server
    previousArgs = arg;
    previousFWATCard = fCard;

    return fCard;
} //WATCardOffice::transferHelper

void WATCardOffice::createJob() {
    Job *job = new Job(previousArgs);
    job->result = previousFWATCard;
    jobs.push_back(job);
}

void WATCardOffice::main() {
    prt.print(Printer::WATCardOffice, 'S');
    for ( ;; ) {
        _Accept(~WATCardOffice) {
            break;
        } or _Accept(create) {
            prt.print(Printer::WATCardOffice, 'C', previousArgs.sid, previousArgs.amount);

            createJob();
        } or _Accept(transfer) {
            prt.print(Printer::WATCardOffice, 'T', previousArgs.sid, previousArgs.amount);

            createJob();
        } or _When (!jobs.empty()) _Accept(requestWork) {
            prt.print(Printer::WATCardOffice, 'W');

            jobs.pop_front();
        } // _Accept
    } // for
    prt.print(Printer::WATCardOffice, 'F');

    // wait for couriers to finish
    officeClosingDown = true;
    for (unsigned int i = 0; i < couriers.size(); i++) {
        _Accept(requestWork);
    } // for

} //WATCardOffice::main

WATCardOffice::Courier::Courier(Printer &prt, Bank &bank, WATCardOffice &cardOffice, unsigned int id) :
    prt(prt),
    bank(bank),
    cardOffice(cardOffice),
    id(id)
{

} // WATCardOffice::Courier::Courier

void WATCardOffice::Courier::main() {
    prt.print(Printer::Courier, id, 'S');
    for ( ;; ) {
        Job *job = cardOffice.requestWork();
      if (!job) break;
        Args arg = job->args;

        prt.print(Printer::Courier, id, 't', arg.sid, arg.amount);
        bank.withdraw(arg.sid, arg.amount);
        prt.print(Printer::Courier, id, 'T', arg.sid, arg.amount);

        arg.card->deposit(arg.amount);

        // 1 in 6 chance of losing a card
        if (prng(0, 1) == 0) {
            job->result.exception(new Lost);
        } else {
            job->result.delivery(arg.card);
        } // if
        delete job;
    } // for
    prt.print(Printer::Courier, id, 'F');
} // WATCardOffice::Courier::main

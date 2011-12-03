#ifndef __VENDINGMACHINE_H
#define __VENDINGMACHINE_H

#include <uC++.h>
#include "watCard.h"
#include "printer.h"
#include "nameServer.h"

_Task VendingMachine {
  public:
    enum Flavours { RABBIT, CAT, DOG, BEAR, NUM_OF_FLAVOURS }; 			// flavours of soda (YOU DEFINE)
  private:
    Printer &prt;
    NameServer &nameServer;
    unsigned int id;
    unsigned int sodaCost;
    unsigned int maxStockPerFlavour;
    bool restockingFlag;
    unsigned int stock[NUM_OF_FLAVOURS];
    Flavours flavourBought;
    WATCard *cardUsed;
    void main();
  public:
    enum Status { BUY, STOCK, FUNDS };		// purchase status: successful buy, out of stock, insufficient funds
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour );
    Status buy( Flavours flavour, WATCard &card );
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
};

#endif

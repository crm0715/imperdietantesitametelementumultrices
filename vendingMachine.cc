#include "vendingMachine.h"
#include <iostream>

using namespace std;

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour ) :
    prt(prt),
    nameServer(nameServer),
    id(id),
    sodaCost(sodaCost),
    maxStockPerFlavour(maxStockPerFlavour)
{
    // initialize array
    for (int i = 0; i < NUM_OF_FLAVOURS; i++) {
        stock[i] = 0;
    } // for
    nameServer.VMregister(this);
} //VendingMachine::VendingMachine

VendingMachine::Status VendingMachine::buy( Flavours flavour, WATCard &card ) {
    if (card.getBalance() < sodaCost) {
        status = FUNDS;
    } else if (stock[flavour] < 1) {
        status = STOCK;
    } else {
        flavourBought = flavour;
        card.withdraw(sodaCost);
        status = BUY;
    }  // if
    return status;
} //VendingMachine::buy

unsigned int *VendingMachine::inventory() {
    return stock;
} //VendingMachine::inventory

void VendingMachine::restocked() {

} //VendingMachine::restocked

_Nomutex unsigned int VendingMachine::cost() {
    return sodaCost;
} //VendingMachine::cost

_Nomutex unsigned int VendingMachine::getId() {
    return id;
} //VendingMachine::getId

void VendingMachine::main() {
    prt.print(Printer::Vending, id, 'S', sodaCost);
    for ( ;; ) {
        _Accept(~VendingMachine) {
            break;
        } or _Accept(inventory) {
            prt.print(Printer::Vending, id, 'r');
            _Accept(restocked) {
                prt.print(Printer::Vending, id, 'R');
            } // _Accept
        } or _Accept(buy) {
            if (status == BUY) {
                stock[flavourBought]--;
                prt.print(Printer::Vending, id, 'B', (int)flavourBought, stock[flavourBought]);
            } // if
        } //_Accept
    } // for
    prt.print(Printer::Vending, id, 'F');
} //VendingMachine::main

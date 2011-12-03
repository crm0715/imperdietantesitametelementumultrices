#include "vendingMachine.h"

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour ) :
    prt(prt),
    nameServer(nameServer),
    id(id),
    sodaCost(sodaCost),
    maxStockPerFlavour(maxStockPerFlavour)
{
    nameServer.VMregister(this);
} //VendingMachine::VendingMachine

VendingMachine::Status VendingMachine::buy( Flavours flavour, WATCard &card ) {
  if (card.getBalance() < sodaCost) return FUNDS;
  if (stock[flavour] < 1) return STOCK;
    flavourBought = flavour;
    card.withdraw(sodaCost);
    return BUY;
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
    prt.print(Printer::Vending, id, 'S');
    for ( ;; ) {
        _Accept(~VendingMachine) {
            break;
        } or _Accept(inventory) {
            prt.print(Printer::Vending, id, 'r');
            _Accept(restocked) {
                prt.print(Printer::Vending, id, 'R');
            } // _Accept
        } or _Accept(buy) {
            stock[flavourBought]--;
            prt.print(Printer::Vending, id, 'B', (int)flavourBought, stock[flavourBought]);
        } //_Accept
    } // for
    prt.print(Printer::Vending, id, 'F');
} //VendingMachine::main

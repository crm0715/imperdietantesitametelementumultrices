#include "vendingMachine.h"

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour ) {
} //VendingMachine::VendingMachine

void VendingMachine::main() {
} //VendingMachine::main

VendingMachine::Status VendingMachine::buy( Flavours flavour, WATCard &card ) {
} //VendingMachine::buy

unsigned int *VendingMachine::inventory() {
} //VendingMachine::inventory

void VendingMachine::restocked() {
} //VendingMachine::restocked

_Nomutex unsigned int VendingMachine::cost() {
} //VendingMachine::cost

_Nomutex unsigned int VendingMachine::getId() {
} //VendingMachine::getId

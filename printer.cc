#include "printer.h"
#include <iostream>

using namespace std;

//Parent, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier

Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ) :
	numStudents( numStudents ), numVendingMachines ( numVendingMachines ), numCouriers ( numCouriers ) {
	total = Student + numStudents + numVendingMachines + numCouriers;
	for ( unsigned int i = 0; i < total; i++ ) {				//initialize buffer
		Buffer buffer;
		buffer.override = false;
		buffer.val1 = -1;
		buffer.val2 = -1;
		buffers.push_back (buffer);
	} //for
} //Printer::Printer

void Printer::print( Kind kind, char state ) {
	printHelper ( kind, 0, state, -1, -1 );
} //Printer::print

void Printer::print( Kind kind, char state, int value1 ) {
	printHelper ( kind, 0, state, value1, -1 );
} //Printer::print

void Printer::print( Kind kind, char state, int value1, int value2 ) {
	printHelper ( kind, 0, state, value1, value2 );
} //Printer::print

void Printer::print( Kind kind, unsigned int lid, char state ) {
	printHelper ( kind, lid, state, -1, -1 );
} //Printer::print

void Printer::print( Kind kind, unsigned int lid, char state, int value1 ) {
	printHelper ( kind, lid, state, value1, -1 );
} //Printer::print

void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ) {
	printHelper ( kind, lid, state, value1, value2 );
} //Printer::print

void Printer::flushBuffer (bool finished) {
	for (unsigned int i = 0; i < total; i++) {      
		if (finished && buffers[i].state != 'F') {      					//print ... if one of the state is finished
			cout << "...\t";
			continue;
		} else if (!buffers[i].override) {        							//print nothing if the state is not defined
			cout << "\t";
			continue;
		} //if
		cout << buffers[i].state;											//print state
		if ( buffers[i].val1 != -1 ) {										//print value1 if exists
			cout << ":" << buffers[i].val1;
			buffers[i].val1 = -1;
		} //if
		if ( buffers[i].val2 != -1 ) {										//print value2 if exists
			cout << "," << buffers[i].val2;
			buffers[i].val2 = -1;
		} //if
		cout << "\t";
	} //for
	cout << endl;
	for (unsigned int i = 0; i < total; i++) {         						//clear buffer
		buffers[i].override = false;
	} //for
} //Printer::flushBuffer

void Printer::printHelper ( Kind kind, unsigned int lid, char state, int val1, int val2) {

	int id = getId (kind, lid);												//get a unique id by parsing kind and id
	if ( buffers[id].override) flushBuffer(false);							//flush buffer if override occurred

	buffers[id].override = true;
	buffers[id].state = state;
	buffers[id].val1 = val1;
	buffers[id].val2 = val2;

	if ( state == 'F' ) {													//flush buffer if finished state is reached
		flushBuffer(true);
		buffers[id].state = '-';											//mark as finished
	}
} //Printer::printHelper

int Printer::getId( Kind kind, unsigned int id) {							//calculate a unique id based on the kind and id
	switch (kind) {
		case Student: 
			return Student + id;
		case Vending:
			return Student + numStudents + id;
		case Courier:
			return Student + numStudents + numVendingMachines + id;
		default:
			return kind;
	} //switch
} //Printer::getId

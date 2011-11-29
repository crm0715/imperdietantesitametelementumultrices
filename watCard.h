#ifndef __WATCARD_H
#define __WATCARD_H

class WATCard {
    WATCard( const WATCard & );			// prevent copying
    WATCard &operator=( const WATCard & );
  public:
    WATCard();
    void deposit( unsigned int amount );
    void withdraw( unsigned int amount );
    unsigned int getBalance();
};
typedef Future_ISM<WATCard *> FWATCard;		// future WATCard pointer

#endif
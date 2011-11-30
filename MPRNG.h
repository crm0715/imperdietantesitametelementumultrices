#ifndef __MPRNG_H
#define __MPRNG_H

#include <uC++.h>
#include "PRNG.h"

// Monitor Wrapper for PRNG
_Monitor MPRNG : private PRNG {
  public:
    // wrappers
    MPRNG( uint32_t s = 362436069 ) :
        PRNG()
    {
    }

    uint32_t seed() {
        return PRNG::seed();
    }

    void seed( uint32_t s) {
        PRNG::seed(s);
    }

    uint32_t operator()() {
        return PRNG::operator()();
    }

    uint32_t operator()( uint32_t u ) {
        return PRNG::operator()(u);
    }

    uint32_t operator()( uint32_t l, uint32_t u ) {
        return PRNG::operator()(l, u);
    }
};

#endif

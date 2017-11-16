//======================================================================
//   ***** Simplified -- only 63-bit gen #5 *****
//
// C version of MCNP5 routines for random number generation
//
//   - These routine require the use of 'unsigned long long' integers,
//     as specified in the ANSI-C99 standard - 64-bit integers.
//
//   - These routines were developed & tested with the gcc and 
//     g++ compiler. No special options are needed to compile & test.
//
//   - For other C/C++ compilers, some tweaking may be needed. 
//     Be sure to run & examine the tests.
//
//   - NOTE: These routines are not thread-safe. 
//           (OpenMP threading will be coming soon.)
//
//   - To mix these C routines with Fortran-90 compiled
//     with the g95 compiler, use these options when
//     compiling the fortran:
//        g95 -funderscoring -fno-second-underscore ... 
//
//
// Author:  FB Brown, 2005-12-02
//======================================================================

//=======================================================================
// Description:
//  mcnp_random.F90 -- random number generation routines
//=======================================================================
//  This module contains:
//
//   * Constants for the RN generator, including initial RN seed for the
//     problem & the current RN seed
//
//   * MCNP interface routines:
//     - random number function:           Urand()
//     - RN initialization for problem:    RN_init_problem
//     - RN initialization for particle:   RN_init_particle
//     - skip-ahead in the RN sequence:    RN_skip_ahead
//     - Unit tests:                       RN_test_basic
//
//   * For interfacing with the rest of MCNP, arguments to/from these
//     routines will have types of I8 or I4.
//     Any args which are to hold random seeds, multipliers,
//     skip-distance will be type I8, so that 63 bits can be held without
//     truncation.
//
// Revisions:
// * 10-04-2001 - F Brown, initial mcnp version
// * 06-06-2002 - F Brown, mods for extended generators
// * 12-21-2004 - F Brown, added 3 of LeCuyer's 63-bit mult. RNGs
// * 01-29-2005 - J Sweezy, Modify to use mcnp modules prior to automatic
//                io unit numbers.
// * 12-02-2005 - F Brown, mods for consistency with C version
//=======================================================================

//#ifdef __cplusplus
//extern "C" {
//#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// function names to match what g95 expects
//#define  Urand               Urand_
//#define  RN_init_problem    rn_init_problem_
//#define  RN_init_particle   rn_init_particle_
//#define  RN_test_basic      rn_test_basic_

  //---------------------------------------------------
  // Kinds for LONG INTEGERS (64-bit) & REAL*8 (64-bit)
  //---------------------------------------------------
#define	 LONG  long long
#define	ULONG  unsigned long long
#define	 REAL  double

  //-------------------------------------
  // Public interface for functions
  //-------------------------------------
  REAL   Urand(void);
  ULONG  RN_skip_ahead( ULONG* seed, LONG* nskip );
  void   RN_init_problem( ULONG* new_seed,    int* print_info );
  void   RN_init_particle( ULONG* nps );
  void   RN_test_basic(void);

  //-------------------------------------
  // Constants for standard RN generators
  //-------------------------------------
  static int    RN_INDEX   = 1;
  static ULONG  RN_MULT    = 3512401965023503517ULL;
  static ULONG  RN_ADD     = 0ULL;
  static int    RN_BITS    = 63;
  static ULONG  RN_STRIDE  = 152917ULL;
  static ULONG  RN_SEED0   = 1ULL;
  static ULONG  RN_MOD     = 1ULL<<63;
  static ULONG  RN_MASK    = (~0ULL) >> 1;
  static ULONG  RN_PERIOD  = 1ULL<<61;
  static REAL   RN_NORM    = 1./(REAL)(1ULL<<63);
  //------------------------------------
  // Private data for a single particle
  //------------------------------------
  static ULONG  RN_SEED    = 1ULL; // current seed

  //----------------------------------------------------------------------
  // reference data:  seeds for case of init.seed = 1,
  //                  seed numbers for index 1-5, 123456-123460
  //----------------------------------------------------------------------
  static const ULONG  RN_CHECK[10] = { 
    // ***** 5 *****
    3512401965023503517ULL, 5461769869401032777ULL, 1468184805722937541ULL,
    5160872062372652241ULL, 6637647758174943277ULL,  794206257475890433ULL,
    4662153896835267997ULL, 6075201270501039433ULL,  889694366662031813ULL,
    7299299962545529297ULL
  };

//----------------------------------------------------------------------
//
  REAL	Urand( void ) {
    // MCNP random number generator
	RN_SEED   = (RN_MULT*RN_SEED) & RN_MASK;

        return  (REAL) (RN_SEED*RN_NORM);
  }

//----------------------------------------------------------------------
//
  ULONG   RN_skip_ahead( ULONG* s, LONG* n ) {
    //  skip ahead n RNs:   RN_SEED*RN_MULT^n mod RN_MOD
    ULONG seed  = *s;
    LONG  nskip = *n;
    while( nskip<0 )  nskip += RN_PERIOD;      // add period till >0
    nskip = nskip & RN_MASK;                   // mod RN_MOD
    ULONG  gen=1,  g=RN_MULT, gp, inc=0, c=RN_ADD, rn;
    // get gen=RN_MULT^n,  in log2(n) ops, not n ops !
    for( ; nskip; nskip>>=1 ) {  
      if( nskip&1 ) {
        gen =  gen*g      & RN_MASK;
        inc = (inc*g + c) & RN_MASK;
      }
      c  = g*c+c & RN_MASK;
      g  = g*g   & RN_MASK;
    }
    rn = (gen*seed + inc) & RN_MASK;
  
    return (ULONG) rn;
  }
//----------------------------------------------------------------------
//
  void RN_init_problem( ULONG* new_seed,
                        int*   print_info ) {
    // * initialize MCNP random number parameters for problem,
    //   based on user input.  This routine should be called
    //   only from the main thread, if OMP threading is being used.
    //
    // * for initial & continue runs, these args should be set:
    //     new_seed   - from RAND seed=        (or dbcn(1))
    //     output     - logical, print RN seed & mult if true
    //
    // * check on size of long-ints & long-int arithmetic
    // * check the multiplier
    // * advance the base seed for the problem
    // * set the initial particle seed
    // * initialize the counters for RN stats

    // set defaults, override if input supplied: seed, mult, stride
    if( *new_seed>0 ) {
      RN_SEED0 = *new_seed;
    }
    if( *print_info ) {
      printf( "\n%s\n%s%20llu%s\n%s%20llu%s\n"
              "%s%20llu%s\n%s%20d%s\n%s%20llu%s\n%s\n\n",
          " ***************************************************",
          " * Random Number Seed       = ", RN_SEED0,       " *",
          " * Random Number Multiplier = ", RN_MULT,        " *",
          " * Random Number Adder      = ", RN_ADD,         " *",
          " * Random Number Bits Used  = ", RN_BITS,        " *",
          " * Random Number Stride     = ", RN_STRIDE,      " *",
          " ***************************************************");
      printf(" using random number generator initial seed = %llu\n", RN_SEED0 );
    }
    // double-check on number of bits in a long long unsigned int
    if( sizeof(RN_SEED)<8 ) {
      printf("***** RN_init_problem ERROR:"
             " <64 bits in long-int, can-t generate RN-s\n");
      exit(1);
    }
    // set the initial particle seed
    RN_SEED    = RN_SEED0;
    return;
  }
//----------------------------------------------------------------------
//
  void	RN_init_particle( ULONG* nps ) {
    // initialize MCNP random number parameters for particle "nps"
    //
    //     * generate a new particle seed from the base seed
    //       & particle index
    //     * set the RN count to zero
        LONG  nskp = *nps * RN_STRIDE;
	RN_SEED  = RN_skip_ahead( &RN_SEED0, &nskp );
  }
//----------------------------------------------------------------------
//
  void	RN_test_basic( void ) {
    // test routine for basic random number generator
    //
    ULONG  seeds[10],  one=1ULL, z=0ULL;  
    int i,j, k=1;
    double s = 0.0;
  
    printf("\n ***** random number - basic test *****\n");
  
    // set seed 
    RN_init_problem( &one,  &k );
  
    // get the    5 seeds, then skip a few, get 5 more - directly
    for( i=0; i<5;      i++ ) { s += Urand(); seeds[i] = RN_SEED; }
    for( i=5; i<123455; i++ ) { s += Urand(); }
    for( i=5; i<10;     i++ ) { s += Urand(); seeds[i] = RN_SEED; }
  
    // compare
    for( i=0; i<10; i++ ) {
      j = (i<5)? i+1 : i+123451;
      printf(" %6d  reference: %20llu  computed: %20llu\n",
               j, RN_CHECK[i], seeds[i] );
      if( seeds[i] != RN_CHECK[i] ) {
        printf(" ***** basic_test of RN generator failed\n");
      }
    }
  }
//----------------------------------------------------------------------

//#ifdef __cplusplus
//}
//#endif


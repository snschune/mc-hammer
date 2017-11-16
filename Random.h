#ifndef _RANDOM_HEADER_
#define _RANDOM_HEADER_

// call to return a uniform random number
double Urand( void );

// call at the beginning of the problem
void RN_init_problem( unsigned long long* new_seed, int* print_info );

// call at the beginning of each history, nps = index for the history
void RN_init_particle( unsigned long long* nps ); 


#endif

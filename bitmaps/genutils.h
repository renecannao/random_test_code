#include <time.h>
#include <iostream>

inline unsigned long long monotonic_time() {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (((unsigned long long) ts.tv_sec) * 1000000) + (ts.tv_nsec / 1000);
}

struct cpu_timer
{
    cpu_timer() {
        begin = monotonic_time();
    }
    ~cpu_timer()
    {   
        unsigned long long end = monotonic_time();
        std::cerr << double( end - begin ) / 1000 << " millisecs.\n" ;
        begin=end-begin; // here only to make compiler happy
    };
    unsigned long long begin;
};


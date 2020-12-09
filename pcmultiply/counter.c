/*
 *  Signal example
 *  Based on Operating Systems: Three Easy Pieces by R. Arpaci-Dusseau and A. Arpaci-Dusseau
 *
 *  This example uses locks and a condition to synchronize a child thread and
 *  the parent.  The child generates matrices and the parent computes the
 *  average when the matrix is ready for processing.
 *
 *  University of Washington, Tacoma
 *  TCSS 422 - Operating Systems
 *  Kero Adib and Jason Shaffer
 */

// Include libraries required for this module only
#include <stdio.h>
#include <pthread.h>
#include "counter.h"

// SYNCHRONIZED COUNTER METHOD IMPLEMENTATION
// Based on Three Easy Pieces

//Initializes the Counter
void init_cnt(counter_t *c)  {
  c->value = 0;
  pthread_mutex_init(&c->lock, NULL);
}

//Increments the value of the Counter
void increment_cnt(counter_t *c)  {
  pthread_mutex_lock(&c->lock);
  c->value++;
  pthread_mutex_unlock(&c->lock);
}

//Returns the Value of the Counter
int get_cnt(counter_t *c)  {
  pthread_mutex_lock(&c->lock);
  int rc = c->value;
  pthread_mutex_unlock(&c->lock);
  return rc;
}
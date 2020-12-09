/*
 *  prodcons module
 *  Producer Consumer module
 *
 *  Implements routines for the producer consumer module based on
 *  chapter 30, section 2 of Operating Systems: Three Easy Pieces
 *
 *  University of Washington, Tacoma
 *  TCSS 422 - Operating Systems
 *  Kero Adib and Jason Shaffer
 */

// Include only libraries for this module
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "counter.h"
#include "matrix.h"
#include "pcmatrix.h"
#include "prodcons.h"


// Define Locks and Condition variables here
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
int next_in = 0;
int next_out = 0;

// Producer consumer data structures

// Bounded buffer bigmatrix defined in prodcons.h
//Matrix ** bigmatrix;

// Bounded buffer put() get()

//Put inserts a matrix at the end of the bounded buffer
int put(Matrix * value)
{
	if (bigmatrix != NULL)
	{
		bigmatrix[next_in] = value;
		next_in = (next_in + 1) % BOUNDED_BUFFER_SIZE;
		increment_cnt(count->prod);
	}
	return 0;
}

//Get removes and returns a matrix from the other end of the Bounded Buffer
Matrix * get()
{
	Matrix* temp = NULL;
	if (bigmatrix != NULL)
	{
		temp = bigmatrix[next_out];
		next_out = (next_out + 1) % BOUNDED_BUFFER_SIZE;
		increment_cnt(count->cons);
	}
	return temp;
}

// Matrix PRODUCER worker thread
void *prod_worker(void *arg)
{
	ProdConsStats* prstats = (ProdConsStats*) arg;
	Matrix* m = NULL;
	for (int i = 0; i < NUMBER_OF_MATRICES; i++)
	{
		m = GenMatrixRandom(m);
		pthread_mutex_lock(&mutex);
		while (get_cnt(count->prod) - get_cnt(count->cons) == BOUNDED_BUFFER_SIZE)
		{
			pthread_cond_wait(&empty, &mutex);
		}
		put(m);
		prstats->matrixtotal++;
		prstats->sumtotal += SumMatrix(m);
		pthread_cond_signal(&full);
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

// Matrix CONSUMER worker thread
void *cons_worker(void *arg)
{	
	//
	ProdConsStats* costats = (ProdConsStats*) arg;
	Matrix* m1;
	Matrix* m2;
	Matrix* m3;
	for (int i = 0; i < NUMBER_OF_MATRICES; i++)
	{
		pthread_mutex_lock(&mutex);
		while (get_cnt(count->prod) - get_cnt(count->cons) == 0)
		{
			pthread_cond_wait(&full, &mutex);
		}
		
		m1 = NULL;
		m2 = NULL;
		m3 = NULL;
		
		m1 = get();
		costats->sumtotal += SumMatrix(m1);
		costats->matrixtotal++;
	
		//Try and a m2 that can multiply with m1
		do
		{
			i++;
			if (i < NUMBER_OF_MATRICES)
			{
				while (get_cnt(count->prod) - get_cnt(count->cons) == 0)
				{
					pthread_cond_wait(&full, &mutex);
				}
			
				m2 = get();
				costats->sumtotal += SumMatrix(m2);
				costats->matrixtotal++;
				m3 = MatrixMultiply(m1, m2);
				
				//If m3 is null, then free m2 and try the next matrix
				if (m3 == NULL)
				{
					FreeMatrix(m2);
					m2 = NULL;
				}
			}
		} while(m3 == NULL && i < NUMBER_OF_MATRICES);
		
		//While i is still within the bounds, print out the equation
		if (i < NUMBER_OF_MATRICES)
		{
			costats->multtotal++;
			DisplayMatrix(m1, stdout);
			printf("      X\n");
			DisplayMatrix(m2, stdout);
			printf("      =\n");
			DisplayMatrix(m3, stdout);
			printf("\n");
    			FreeMatrix(m3);
    			FreeMatrix(m2);
    			FreeMatrix(m1);
    		}
    		pthread_cond_signal(&empty);
    		pthread_mutex_unlock(&mutex);
	}
  	return NULL;
}

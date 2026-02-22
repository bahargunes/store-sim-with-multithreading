#include <iostream>
#include <pthread.h>
using namespace std; 

enum ItemType { AAA, BBB, CCC };

/* You can define any global variable
   function and class definition here.
   Programs will first call initStore() then
   all other functions
*/
static int avail[3] = {0, 0, 0};
static int capacity[3] = {0, 0, 0};
static int reserved[3] = {0, 0, 0};
static int waitingSupplier = 0;
static int waitingCustomer = 0;
static pthread_mutex_t mutex_st;
static pthread_cond_t newSupply;
static pthread_cond_t newBuy;
static int maxO;


void initStore(int cA, int cB, int cC, int mO) {
      pthread_mutex_init(&mutex_st, NULL);
      pthread_cond_init(&newBuy, NULL);
      pthread_cond_init(&newSupply, NULL);
      capacity[AAA] = cA;
      capacity[BBB] = cB;
      capacity[CCC] = cC;
      avail[AAA] = capacity[AAA];
      avail[BBB] = capacity[BBB];
      avail[CCC] = capacity[CCC];

      maxO = mO;
}      

void buy(int aA, int aB, int aC) {
      pthread_mutex_lock(&mutex_st);
      while (aA > avail[AAA] || aB > avail[BBB] || aC > avail[CCC]) {
          waitingCustomer++;
          pthread_cond_wait(&newSupply, &mutex_st);
          waitingCustomer--;
      }
      avail[AAA] -= aA;
      avail[BBB] -= aB;
      avail[CCC] -= aC;
      pthread_mutex_unlock(&mutex_st);
      pthread_cond_broadcast(&newBuy);
      return;
}

void maysupply(int itype, int n) {
      pthread_mutex_lock(&mutex_st);
      if (reserved[itype] + avail[itype] + n <= capacity[itype]) {
          reserved[itype] += n;
          pthread_mutex_unlock(&mutex_st);
          return;
      }
      else{
            while(reserved[itype] + avail[itype] + n > capacity[itype]) {
                waitingSupplier++;
                pthread_cond_wait(&newBuy, &mutex_st);
                waitingSupplier--;
            }
            reserved[itype] += n;
            pthread_mutex_unlock(&mutex_st);
            return;
      }

}

void supply(int itype, int n) {
      pthread_mutex_lock(&mutex_st);
      avail[itype] += n;
      reserved[itype] -= n;
      pthread_mutex_unlock(&mutex_st);
      pthread_cond_broadcast(&newSupply);
      return;
}

void monitorStore(int c[3], int a[3]) {
      pthread_mutex_lock(&mutex_st);
      c[AAA] = capacity[AAA];
      c[BBB] = capacity[BBB];
      c[CCC] = capacity[CCC];
      a[AAA] = avail[AAA];
      a[BBB] = avail[BBB];
      a[CCC] = avail[CCC];
      pthread_mutex_unlock(&mutex_st);
      return;
}

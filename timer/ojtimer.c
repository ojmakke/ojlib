#include "ojtimer.h"

#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <string.h>
#include <sys/timerfd.h>
#include <stdint.h>

void timer_handler(int signum)
{
  static int count = 0;
  printf("Timer expired %d times\n", ++count);
}

void handleCtrlC()
{
  printf("Terminating\n");
  fflush(stdout);
  exit(1);
}

void thandler(int sig, siginfo_t *si, void *uc)
{
  printf("Caught signal %d\n", sig);
  timer_t *tidp;
  tidp = si->si_value.sival_ptr;
  printf("*sival_ptr = 0x%lx\n", (long) *tidp);
  // signal(sig, SIG_IGN);
  //print_siginfo(si);
  
}

int main(int argc, char* argv[])
{

  /* Install signal handler */
  struct sigaction sa;
  sa.sa_flags = SA_SIGINFO;
  sa.sa_sigaction = thandler;
  sigemptyset(&sa.sa_mask);
  sigaction(SIGRTMIN , &sa, NULL);
  
  

  
  /* This creates the timer. */
  timer_t timerid;
  
  struct sigevent sevp;
  sevp.sigev_notify = SIGEV_SIGNAL;
  sevp.sigev_signo = SIGRTMIN;
  sevp.sigev_value.sival_ptr = &timerid;

  struct sigevent sevp2 = sevp;

  timer_t timerid2 = timerid;
  sevp2.sigev_value.sival_ptr = &timerid2;



  if(timer_create(CLOCK_MONOTONIC, &sevp, &timerid) == -1)
    {
      printf("Error in timer_create\n");
      return 0;
    }

  if(timer_create(CLOCK_MONOTONIC, &sevp2, &timerid2) == -1)
    {
      printf("error in timer2\n");
    }
  printf("Timer id is 0x%lx and 0x%lx\n", (long) timerid, (long) timerid2);
  struct itimerspec spec2;
  spec2.it_interval.tv_nsec = 100*1000000; /* 100 ms */
  spec2.it_interval.tv_sec = 0;
  spec2.it_value.tv_nsec = 0;
  spec2.it_value.tv_sec = 5; /* Start after 5 sec */

  struct itimerspec spec3 = spec2;
  spec3.it_interval.tv_nsec = 113*1000000;
  
  if(timer_settime(timerid, 0, &spec2, NULL) == -1)
    {
      printf("Error timer_set\n");
      return 0;
    }

  if(timer_settime(timerid2, 0, &spec3, NULL) == -1)
    {
      printf("Error in timer_set2\n");
      return 0;
    }

  
  while(1)
    {
      
      //    res = read(timerfd, &exp, sizeof(exp));
      //   printf("%lld\n", exp);

    }

  return 0;
}

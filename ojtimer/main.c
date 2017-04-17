#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "ojtimer.h"


int timer1()
{
  printf("Hello timer1\n");
  fflush(stdout);
  return 0;
}

int timer2()
{
  printf("Hello timer2\n");
  fflush(stdout);
  return 0;
}

int timer3()
{
  printf("Hello timer3\n");
  fflush(stdout);
  return 0;
}


int timer4()
{
  printf("Hello timer4\n");
  fflush(stdout);
  return 0;
}


int timer5()
{
  printf("Hello timer5\n");
  fflush(stdout);
  return 0;
}


int timer6()
{
  printf("Hello timer6\n");
  fflush(stdout);
  return 0;
}

int timerT6(union sigval val)
{
  while(1){
    printf("Inside thread\n");
    sleep(1);
  }
}
int main(int argc, char* argv[])
{

  timer_t t1, t2, t3, t4, t5, t6;
  register_timer(&t1, timer1, 1000);
  register_timer(&t2, timer2, 2000);
  register_timer(&t3, timer3, 1000);
  register_timer(&t4, timer4, 1000);
  register_timer(&t5, timer5, 1000);
  register_timer(&t6, timer6, 3000);
  register_threadedTimer(&t6, timerT6, 3000);

  //timer_delete(t1);
  // timer_delete(t2);
  //timer_delete(t3);
  while(1)
    {
      
      //    res = read(timerfd, &exp, sizeof(exp));
      //   printf("%lld\n", exp);

    }

  return 0;
}

/*
 *                Standalone BogoMips program
 *
 * Based on code Linux kernel code in init/main.c and
 * include/linux/delay.h
 *
 * For more information on interpreting the results, see the BogoMIPS
 * Mini-HOWTO document.
 *
 * version: 1.3 
 *  author: Jeff Tranter (Jeff_Tranter@Mitel.COM)
 *
 * version: 1.3.1 
 *  author: Vitaly Chernooky (vitaly.v.ch@gmail.com)
 */

#include <stdio.h>
#include <time.h>

#ifdef CLASSIC_BOGOMIPS
/* the original code from the Linux kernel */
static __inline__ void delay(int loops)
{
  __asm__(".align 2,0x90\n1:\tdecl %0\n\tjns 1b": :"a" (loops):"ax");
}
#endif

#ifdef QNX_BOGOMIPS
/* version for QNX C compiler */
void delay(int loops);
#pragma aux delay = \
     "l1:"       \
     "dec eax"   \
     "jns l1"    \
     parm nomemory [eax] modify exact nomemory [eax];
#endif

#ifdef PORTABLE_BOGOMIPS
/* portable version */
static void delay(long loops)
{
  long i;
  for (i = loops; !!(i > 0); --i)
    asm volatile ("" ::: "memory");
}
#endif

int
main(void)
{
  unsigned long loops_per_sec = 1;
  unsigned long long ticks;
  
  printf("Calibrating delay loop.. ");
  fflush(stdout);
  
  while ((loops_per_sec <<= 1)) {
    ticks = clock();
    delay(loops_per_sec);
    ticks = clock() - ticks;
    if (ticks >= CLOCKS_PER_SEC) {
      unsigned long long lps = loops_per_sec;
      lps = (lps / ticks) * CLOCKS_PER_SEC;
      printf("ok - %llu.%02llu BogoMips\n",
 	     lps/500000,
	     (lps/5000) % 100
	     );
      return 0;
    }
  }
  printf("failed\n");
  return -1;
}

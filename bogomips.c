/*
 * bogomips.c -- Program to measure bogomips... this program will probably go
 * totally wacky with cpufreq enabled.
 *
 * Copyright (C) 2005 Darrick Wong.
 */
#include <stdio.h>
#include <time.h>

/* this should be approx 2 Bo*oMips to start (note initial shift), and will
 *    still work even if initially too large, it will just take slightly longer */
unsigned long loops_per_jiffy = (1<<12);

/* This is the number of bits of precision for the loops_per_jiffy.  Each
 *    bit takes on average 1.5/HZ seconds.  This (like the original) is a little
 *       better than 1% */
#define LPS_PREC 8

extern int HZ;

extern void delay(unsigned int loops);

//plagiarized straight from the 2.4 sources.
void calibrate_delay(void)
{
        unsigned long ticks, loopbit;
        int lps_precision = LPS_PREC;

        loops_per_jiffy = (1<<12);

        printf("Calibrating delay loop... ");
        while (loops_per_jiffy <<= 1) {
                /* wait for "start of" clock tick */
                ticks = clock();
                while (ticks == clock())
                        /* nothing */;
                /* Go .. */
                ticks = clock();
                delay(loops_per_jiffy);
                ticks = clock() - ticks;
                if (ticks)
                        break;
        }

/* Do a binary approximation to get loops_per_jiffy set to equal one clock
   (up to lps_precision bits) */

       loops_per_jiffy >>= 1;
        loopbit = loops_per_jiffy;
        while ( lps_precision-- && (loopbit >>= 1) ) {
                loops_per_jiffy |= loopbit;
                ticks = clock();
                while (ticks == clock());
                ticks = clock();
                delay(loops_per_jiffy);
                if (clock() != ticks)   /* longer than 1 tick */
                        loops_per_jiffy &= ~loopbit;
        }


/* Round the value and print it */      
        printf("%lu.%02lu BogoMIPS\n",
                loops_per_jiffy/(500000/HZ),
                (loops_per_jiffy/(5000/HZ)) % 100);
}

int main(int c, char *v[]) {
	if(c > 1) {
		while(1) {calibrate_delay();}
	}
        calibrate_delay();

	return 0;
}

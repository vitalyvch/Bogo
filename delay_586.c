//Pentiums-with-TSC delay.

int HZ = 100;

#define rdtscl(low) \
     __asm__ __volatile__ ("rdtsc" : "=a" (low) : : "edx")

//This delay() is the one used on x86's with TSC after 2.2.14.
//It won't work on a non TSC x86, period.
void __inline__ delay(unsigned long loops)
{
        unsigned long bclock, now;
        
        rdtscl(bclock);
        do
        {
                rdtscl(now);
        }
        while((now-bclock) < loops);
}

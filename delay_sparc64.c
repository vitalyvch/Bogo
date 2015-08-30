//Sparc64 delay.

int HZ = 100;

void __inline__ delay(unsigned long loops)
{
        __asm__ __volatile__(
"       b,pt    %%xcc, 1f\n"
"        cmp    %0, 0\n"
"       .align  32\n"
"1:\n"
"       bne,pt  %%xcc, 1b\n"
"        subcc  %0, 1, %0\n"
        : "=&r" (loops)
        : "0" (loops)
        : "cc");
}

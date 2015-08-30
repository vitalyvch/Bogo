//PA-RISC

int HZ = 100;

__inline__ void delay(unsigned long loops) {
        asm volatile(
        "       .balignl        64,0x34000034
                addib,UV -1,%0,.
                nop"
                : "=r" (loops) : "0" (loops));
}

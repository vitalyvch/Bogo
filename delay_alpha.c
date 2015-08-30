//Alpha delay.

int HZ = 1024;

void __inline__ delay(int loops)
{
	int tmp;
	__asm__ __volatile__(
		"       rpcc %0\n"
		"       addl %1,%0,%1\n"
		"1:     rpcc %0\n"
		"       subl %1,%0,%0\n"
		"       bgt %0,1b"
		: "=&r" (tmp), "=r" (loops) : "1"(loops));
}

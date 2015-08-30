//386 delay.

int HZ = 100;

/*
 *      Non TSC based delay loop for 386, 486, MediaGX
 */
 
void __inline__ delay(unsigned long loops)
{
	int d0;
	__asm__ __volatile__(
		"\tjmp 1f\n"
		".align 16\n"
		"1:\tjmp 2f\n"
		".align 16\n"
		"2:\tdecl %0\n\tjns 2b"
		:"=&a" (d0)
		:"0" (loops));
}

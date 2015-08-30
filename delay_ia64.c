//IA64 delay

int HZ = 1024;

__inline__ void
delay (unsigned long loops)
{
	unsigned long saved_ar_lc;

	if (loops < 1)
		return;

	__asm__ __volatile__("mov %0=ar.lc;;" : "=r"(saved_ar_lc));
	__asm__ __volatile__("mov ar.lc=%0;;" :: "r"(loops - 1));
	__asm__ __volatile__("1:\tbr.cloop.sptk.few 1b;;");
	__asm__ __volatile__("mov ar.lc=%0" :: "r"(saved_ar_lc));
}

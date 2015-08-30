//PPC delay

int HZ = 100;

void __inline__ delay(unsigned long loops)
{

	__asm__ __volatile__("cmpwi	0,r3,0\n\t"
			     "mtctr	r3\n\t"
			     "beqlr\n\t"
			     "1:	bdnz	1b\n\t"
			     "blr");
}

/*
_GLOBAL(delay)
	cmpwi   0,r3,0
	mtctr   r3
	beqlr
1:      bdnz    1b
	blr
*/

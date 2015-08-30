//portable delay.

int HZ = 100;

void delay(int loops)
{
  long i;
  for (i = loops; i >= 0 ; i--) ;
}

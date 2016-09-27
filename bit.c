#include<stdio.h>

int main()
{
	int i;
	short b = 0x2;
	char a = 1;
	short c = 1;
	short bb[5] = {1,2,4,8,16};
	short aa[5] = {1,2,4,8,16};
	for(i = 0;i < 5;i++)
	{
		printf("bb[%d]:%x ",i,bb[i]);
	}
	printf("\n");
	bb[2] = bb[2]&0xfffb | (short)aa[0]<<8 & 0x0100;
	for(i = 0;i < 5;i++)
	{
		printf("bb[%d]:%x ",i,bb[i]);
	}
	printf("\n--------------------------\n");
	printf("a:%x \n",a);
	printf("b:%x \n",b);
	a = a<<8;
	printf("a:%x \n",a);
	a = 1;
	c = (short)a<<8;
	printf("c:%x \n",c);
	b = b<<8;
	printf("b:%x \n",b);
	return 0;
}

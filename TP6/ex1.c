#include<stdio.h>

int main()
{
	
	unsigned char a, b, orEx; 
	unsigned char desloc[100];
	int bit;
	int cont = 0;
	
	do{
		scanf("%hhu", &a);
		scanf("%hhu", &b);
		if((b != 0xFF)&&(a != 0x00))
		{
			scanf("%u", &bit);
			if(bit >= 0x00 && bit <= 0x07)
			{
				orEx = a ^ b;
				desloc[cont] = orEx >> bit;
				cont++;
			}
		}
	}while((b != 0xFF)&&(a != 0x00));
	
	for(int i = 0; i < cont; i++)
	{
		if((desloc[i] & 0x01) == 0x01)
			printf("SIM\n");
		else
			printf("NAO\n");
	}
	return 0;
}

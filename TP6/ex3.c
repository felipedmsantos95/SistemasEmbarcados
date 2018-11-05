#include <stdio.h>
int main(){
	unsigned char valor, bit, maskAnd = 0xF8;
	unsigned char mascarado, result[100];
	int cont = 0;
	do{
		scanf("%hhu", &valor);
		if(valor != 255)
		{
			scanf("%hhu", &bit);
			if(bit >= 0x00 && bit <= 0x07)
			{
				mascarado = valor & maskAnd;
				result[cont] = (mascarado | bit);
				cont++;
			}
							
		}
				
		
	}while(valor != 255);
	
	int i;
	for(i = 0; i < cont; i++)
		printf("%hu\n", result[i]);
	return 0;
}

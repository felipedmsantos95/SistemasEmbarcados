#include <stdio.h>
int main(){
	unsigned short int valor, bit, mask = 0x0001;
	unsigned short int desloc, result[100];
	int cont = 0;
	do{
		scanf("%hu", &valor);
		if(valor != 65535)
		{
			scanf("%hu", &bit);
			desloc = mask << bit;
			result[cont] = (valor ^ desloc);
			cont++;
							
		}
				
		
	}while(valor != 65535);
	int i;
	for(i = 0; i < cont; i++)
		printf("%hu\n", result[i]);
	return 0;
}

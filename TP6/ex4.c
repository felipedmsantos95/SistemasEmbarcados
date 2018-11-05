#include <stdio.h>
int main(){
	unsigned short int valor, bit, mask = 0x8000, opAnd, resultParc;
	unsigned short int desloc, result[100];
	int cont = 0, contBit = 0;
	do{
		scanf("%hu", &valor);
		if(valor != 65535)
		{
			scanf("%hu", &bit);
			
			for(contBit = 0; contBit < bit; contBit++){
				opAnd = valor & mask;
				opAnd = opAnd >> 15;
				valor = valor << 1;
				resultParc = valor| opAnd;
				valor = resultParc;
			}
			
			result[cont] = resultParc;
			cont++;
							
		}
				
		
	}while(valor != 65535);
	int i;
	for(i = 0; i < cont; i++)
		printf("%hu\n", result[i]);
	return 0;
}

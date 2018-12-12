#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct hrac{
		char menos[201];
		int finalnebody;
}hrac[201];

int celkovysucet=0;
int y =0;

void poradie(){
  	char prvy[201];
  	char druhy[201];
  	char treti[201];
  	int prvya = 0, druhyb = 0, tretic = 0;
	for(int i = 0; i<100; i++){
		if(hrac[i].finalnebody>=prvya){
			// posunieme body o jedno dozadu, prvého na druhé a druhého na tretie
			tretic=druhyb;
			druhyb=prvya;

			// posunieme mená
			strcpy(treti,druhy);
			strcpy(druhy,prvy);

			// deklarujeme prvého body a potom meno
			prvya=hrac[i].finalnebody;
			strcpy(prvy,hrac[i].menos);
						}
		else if(hrac[i].finalnebody>druhyb){
			// posunieme body predošlého druhého na tretie miesto
			tretic=druhyb;

			// posunieme meno predošlého 2. na 3.
			strcpy(treti,druhy);

			// deklarujeme druhého body a potom meno
			druhyb=hrac[i].finalnebody;
			strcpy(druhy,hrac[i].menos);
						}
		else if(hrac[i].finalnebody>tretic){
			//rovno deklarujeme, neposúvame predošlého, nie je to potrebné
			tretic=hrac[i].menos;
			strcpy(treti,hrac[i].menos);
						}
	
				   }
		// výpis prvého, druhého a tretieho
		if(strlen(prvy)>1)printf("%s %d\n",prvy,prvya);
		if(strlen(druhy)>1)printf("%s %d\n",druhy,druhyb);
		if(strlen(treti)>1)printf("%s %d\n",treti,tretic);
}

// funkcia na dekláraciu meno a celkového poètu bodov zo všetkých hier
int deklaraciahracov(char *meno,int body){
 	strcpy(hrac[y].menos, meno);
	
	/*
	for(int v=1;v<y;v++){
			if(strcmp(hrac[v].menos,hrac[y].menos)){
						memset(hrac[y].menos,NULL,sizeof hrac[y].menos);
						break;
										 			}
					     }
	*/
	
	hrac[y].finalnebody+=celkovysucet;	
	y++;

	}

// funkcia na sèítanie a vyhodnotenie bodov tajnièky
int bodovka(char pismeno,char *tajne,int body){
	int pomocna=0;
	for(int z=1;z<=strlen(tajne);z++){
			if(tajne[z]==pismeno){	
							pomocna+=body;
	 						tajne[z]='$';
								}
			}
	return pomocna;
}

int main() {
	
	char meno[201];
	char pismeno;
	char buffer[201];
	char tajne[201];
	int x;
	int body=0;
	
	for(x = 1; x <= 1000; x++)
	{
		sprintf(buffer,"hra_%d.txt", x); 			// prepíše meno premennej
		FILE *koleso = fopen(buffer, "r+"); 		// deklarujeme fp koleso a otvoríme v òom buffer
		
		if(fgets(meno,100,koleso)==NULL){
									break; 			// naèítame prvý riadok aj s enterom, prièom ak je prázdny break
											} 	
		if(fgets(tajne,100,koleso)==NULL){
									break;			// naèítame druhý riadok aj s enterom, prièom ak je prázdny break
											} 
		meno[strlen(meno)-1]='\0';   				// odstránim enter na konci
		tajne[strlen(tajne)-1]='\0';				// odstránim enter na konci


		for(int w = 1; w < strlen(tajne); w++){
			fscanf(koleso,"%d %c",&body,&pismeno);
			celkovysucet+=bodovka(pismeno,tajne,body);
		}

		deklaraciahracov(meno,body);			

			//reset hodnôt
			hrac[y].finalnebody=0;
			celkovysucet=0;
			body=0;
			
		fclose(koleso);				// zavrieme súbor
	}
   poradie();
   body=0;
   return 0;
}

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
			// posunieme body o jedno dozadu, prv�ho na druh� a druh�ho na tretie
			tretic=druhyb;
			druhyb=prvya;

			// posunieme men�
			strcpy(treti,druhy);
			strcpy(druhy,prvy);

			// deklarujeme prv�ho body a potom meno
			prvya=hrac[i].finalnebody;
			strcpy(prvy,hrac[i].menos);
						}
		else if(hrac[i].finalnebody>druhyb){
			// posunieme body predo�l�ho druh�ho na tretie miesto
			tretic=druhyb;

			// posunieme meno predo�l�ho 2. na 3.
			strcpy(treti,druhy);

			// deklarujeme druh�ho body a potom meno
			druhyb=hrac[i].finalnebody;
			strcpy(druhy,hrac[i].menos);
						}
		else if(hrac[i].finalnebody>tretic){
			//rovno deklarujeme, nepos�vame predo�l�ho, nie je to potrebn�
			tretic=hrac[i].menos;
			strcpy(treti,hrac[i].menos);
						}
	
				   }
		// v�pis prv�ho, druh�ho a tretieho
		if(strlen(prvy)>1)printf("%s %d\n",prvy,prvya);
		if(strlen(druhy)>1)printf("%s %d\n",druhy,druhyb);
		if(strlen(treti)>1)printf("%s %d\n",treti,tretic);
}

// funkcia na dekl�raciu meno a celkov�ho po�tu bodov zo v�etk�ch hier
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

// funkcia na s��tanie a vyhodnotenie bodov tajni�ky
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
		sprintf(buffer,"hra_%d.txt", x); 			// prep�e meno premennej
		FILE *koleso = fopen(buffer, "r+"); 		// deklarujeme fp koleso a otvor�me v �om buffer
		
		if(fgets(meno,100,koleso)==NULL){
									break; 			// na��tame prv� riadok aj s enterom, pri�om ak je pr�zdny break
											} 	
		if(fgets(tajne,100,koleso)==NULL){
									break;			// na��tame druh� riadok aj s enterom, pri�om ak je pr�zdny break
											} 
		meno[strlen(meno)-1]='\0';   				// odstr�nim enter na konci
		tajne[strlen(tajne)-1]='\0';				// odstr�nim enter na konci


		for(int w = 1; w < strlen(tajne); w++){
			fscanf(koleso,"%d %c",&body,&pismeno);
			celkovysucet+=bodovka(pismeno,tajne,body);
		}

		deklaraciahracov(meno,body);			

			//reset hodn�t
			hrac[y].finalnebody=0;
			celkovysucet=0;
			body=0;
			
		fclose(koleso);				// zavrieme s�bor
	}
   poradie();
   body=0;
   return 0;
}

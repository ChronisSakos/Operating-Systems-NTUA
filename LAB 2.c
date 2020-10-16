#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

int z,a=0,ch;

void sigalarm() { //diadikasia p allazi tin timi tou z oste na stamata na ektiponi to paidi
	z=0;
}

void handler(int sig) //diadikasia handler i opia kalite apo to kathe paidi ksexorista
{ 	
	signal(SIGALRM, sigalarm); //otan perasoun 3 sec ektelese tin sinartisi singalarm
	alarm(3);
	z=1;
	while(z){ //tiponi mexri to z na allaksi timi
    printf("Child %d %d is executed (%d) \n", ch, getpid(), a); 
	a++;
	sleep(1);
	}
	return;
}

int main(int argc, char **argv){
	int i,j,k=0,l,p,input[6];
	pid_t c[6];
	if (argc!=6){ //elegxos an to plithos ton stixion tis isodou ine sostos
		printf("error-wrong input \n");
		return 0;
	}
	else {
		for (i=1; i<argc; i++){ //metatropi ton stixion tis isodou se arithmous
			input[i]=atoi(argv[i]);
		}
		i=1;
		for (j=1; j<argc; j++)
			for (i=1; i<argc; i++)
				if (j==input[i]){ //elegxos an iparxoun oloi oi arithmoi apo 1-5 (mia fora)
					k++;
					i++;
				}
				
		if (k!=5){
			printf("error-wrong input \n");
			return 0;
		}
		else {
			c[1]=fork();
			if (c[1]<0){
				printf("error \n");
				exit(-1);
			}
			else if (c[1]==0) { //kodikas tou protou paidiou
				ch=1;
				signal(SIGINT,handler); //molis lavo sima SIGINT ektelo tin handler
				while(1) //panta se katastasi anamonis mexri na lavi kapoio sima
				pause();
			}	
			else {
				c[2]=fork();
				if (c[2]<0){
					printf("error \n");
					exit(-1);
				}
				else if (c[2]==0) { //kodikas tou defterou paidiou
					ch=2;
					signal(SIGINT,handler); //molis lavo sima SIGINT ektelo tin handler
					while(1) //panta se katastasi anamonis mexri na lavi kapoio sima
					pause();
				}	
				else {
					c[3]=fork();
					if (c[3]<0){
						printf("error \n");
						exit(-1);
					}
					else if (c[3]==0) { //kodikas tou tritou paidiou
						ch=3;
						signal(SIGINT,handler); //molis lavo sima SIGINT ektelo tin handler
						while(1) //panta se katastasi anamonis mexri na lavi kapoio sima
						pause();
					}	
					else {
						c[4]=fork();
						if (c[4]<0){
							printf("error \n");
							exit(-1);
						}
						else if (c[4]==0) { //kodikas tou tetartou paidiou
							ch=4;
							signal(SIGINT,handler); //molis lavo sima SIGINT ektelo tin handler
							while(1) //panta se katastasi anamonis mexri na lavi kapoio sima
							pause();
						}	
						else {
							c[5]=fork();
							if (c[5]<0){
								printf("error \n");
								exit(-1);
							}
							else if (c[5]==0) { // kodikas tou pemptou paidiou
								ch=5;
								signal(SIGINT,handler); //molis lavo sima SIGINT ektelo tin handler
								while(1)//panta se katastasi anamonis mexri na lavi kapoio sima
								pause();
							}	
							else {
								sleep(1);//kathisterisi 1 sec oste na prolavoun na dimiourgithous ta paidia
								for (l=0; l<4; l++){
									for (p=1; p<6; p++) {
										kill(c[input[p]], SIGINT); // stelno sima sto paidi p exi sira
										sleep(3); //kathisterisi 3 sec oste na prolavi na stamatisi to paidi prin ektelistei to epomeno
									}
									if (l==3) //an ine i teleftea fora p kalo to paidi tote to skotono
										kill(c[input[p]], SIGKILL); 
								}
							}
						}
					}
				}
			}
		}
	}
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>  

int main(int argc, char **argv){

int s=1,sum,i,n,k,status,j,l=0,a,telos=1;

n=atoi(argv[1]);
k=atoi(argv[2]);

if (argc!=3){
	printf("error-wrong input\n");
	return 0;
}

int pd[20];

for(i = 0; i<n; i++){//vazo tis thesi ton pipes se ena pinaka gia to sum (apotelesma)
        pipe(pd+i*2);
    }

pid_t child[n];

for (i=0; i<n; i++){ //dimiourgia ton n paidion
	child[i]=fork();
	if (child[i]<0){
		printf("error");
		exit(-1);
	}
	else if (child[i]==0){
		s=i+1-n;
		if (i<(k%n))//an to paidi einai mmikrotero apo to arithmo mod paidion tote prosthese mia ektelesi 
			a=k/n+1; 
		else
			a=k/n;
		while (telos){
			l=l+1; //auksano poses fores etrekse kathe paidi
			s=s+n; //auksano to pollaplasiasti
			close(pd[i*2+1]); 
			read(pd[i*2],&sum,sizeof(sum)); //diavazo to sum apo to proigoumeno paidi
			sum=sum*s; //kano ton pollaplasiasmo
			if (a==l){ // an etreksa to paidi oses fores tha treksei sinolika
				if (s==k) //tipono mono se ena paidi to telefteo
				printf("ime sto pedi %d kai to paragontiko einai:%d \n",i+1, sum);
				telos=0;
			}
			if (i==n-1){ //an vriskome sto telefteo paidi to sindeo me pipe sto proto paidi
				close(pd[0]); 
				write(pd[1],&sum,sizeof(sum)); //grafo to sum sto proto paidi
			}
			else { // alios to sindeo me to pipe tou epomenou paidiou
				close(pd[i*2+2]);
				write(pd[i*2+3],&sum,sizeof(sum)); //grafo to sum sto epomeno paidi
			}
		}
		exit(0);
	}
	else 
	if ((child[i]>0) & (i==n-1)) {
		sum=1;//i isodos apo to patera sto proto paidi
		close(pd[0]); 
		write(pd[1],&sum,sizeof(sum)); // vazo tin isodo (sum) sto proto paidi
		for (j=0; j<n; j++)	//perimeno ta paidia na teliosoun
			wait(&status);
		for (j=0; j<n; j++) //termatizo ola ta paidia
			kill(child[j],SIGKILL);
		exit(0);
	}
}
return 0;
}
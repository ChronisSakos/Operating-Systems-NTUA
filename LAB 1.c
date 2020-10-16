#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main () {
	int status;
	pid_t c1,c2,c3,c4,c5,mypid,parentpid;
	c1=fork(); //proto paidi c1
	if (c1<0) {
	printf("error\n");
	exit(-1);
	}
	else if(c1==0){
		c3=fork(); //to paidi c3 tou paidiou c1
		if (c3<0) {
		printf("error\n");
		exit(-1);
		}
		else if(c3==0){
		mypid=getpid();
		parentpid=getppid();
		for(int i=0; i<10; i++) {
		printf("Process %d is executed, my father is %d\n", mypid, parentpid);
		sleep(1);
		}
		exit(0);
		}
		else { //kodikas tou patera tou c3 diladi kodikas tous c1
			c4=fork(); //dimiourgia tou paidiou c4 pou ine paidi tou c1
			if (c4<0) {
			printf("error\n");
			exit(-1);
			}
			else if(c4==0){
			mypid=getpid();
			parentpid=getppid();
			for(int i=0; i<10; i++) {
			printf("Process %d is executed, my father is %d\n", mypid, parentpid);
			sleep(1);
			}
			exit(0);
			}
			else {
			mypid=getpid();
			parentpid=getppid();
			for(int i=0; i<10; i++) {
			printf("Process %d is executed, my father is %d\n", mypid, parentpid);
			sleep(1);}
			wait(&status);
			}
		wait(&status);
		exit(0);}
	exit(0);}
	else { //kodikas tou main diladi tou protou patera
		c2=fork(); //dimiourgia tou paidiou c2
		if (c2<0) {
		printf("error\n");
		exit(-1);
		}
		else if(c2==0){
			c5=fork();
			if (c5<0) {
			printf("error\n");
			exit(-1);
			}
			else if(c5==0){
			mypid=getpid();
			parentpid=getppid();
			for(int i=0; i<10; i++) {
			printf("Process %d is executed, my father is %d\n", mypid, parentpid);
			sleep(1);
			}
			exit(0);
			}
			else {
			mypid=getpid();
			parentpid=getppid();
			for(int i=0; i<10; i++) {
			printf("Process %d is executed, my father is %d\n", mypid, parentpid);
			sleep(1);
			}				
			wait(&status);
			exit(0);
			}
		exit(0);
		}
		else {
		wait(&status);
		}
	wait(&status);
	exit(0);
	}
return 0;
}
	

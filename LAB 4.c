#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

struct pipesem {
	int rfd; 	//read pipe
	int wfd; 	//write pipe
}sem;

void pipesem_init(struct pipesem *sem, int val);
void pipesem_wait(struct pipesem *sem);
void pipesem_signal(struct pipesem *sem);

void pipesem_init(struct pipesem *sem, int val)
{
    int i;
    int f[ 2 ];
    int status;

    status = pipe(f);
    if (status < 0) {
        perror("Could not create semaphore");
        return;
    }

    sem->rfd = f[ 0 ];
    sem->wfd = f[ 1 ];

    for (i = 0; i < val; ++i) {
        pipesem_signal(sem);
    }
}

void pipesem_wait(struct pipesem *sem)
{
    char buffer[ 1 ];
    int status;

    status = read(sem->rfd, buffer, 1);

    if (status < 0) {
        perror("Could not wait on semaphore");
        return;
    }
}

void pipesem_signal(struct pipesem *sem)
{
    int status;
	char x='y';
    status = write(sem->wfd, &x, sizeof(x));

    if (status < 0) {
        perror("Could not signal semaphore");
        return;
    }
}

void critical(int child, pid_t pid){
	for (int k=0; k<5; k++){
		printf("Child%d %d executes a critical section.\n",child, pid);
		sleep(1);
	}
}

void noncritical(int child, pid_t pid){
	for (int k=0; k<7; k++){
		printf("Child%d %d executes a non critical section.\n",child, pid);
		sleep(1);
	}
}

int main () {
	int status,i;
	pid_t c1,c2,c3;
		pipesem_init(&sem, 1);
		c1=fork(); 
		if (c1<0) {
		printf("error\n");
		exit(-1);
		}
		else if(c1==0){
			kill(getpid(),SIGSTOP);
			i=1;
			pipesem_wait(&sem);
			critical(i,getpid());
			pipesem_signal(&sem);
				noncritical(i,getpid());
				noncritical(i,getpid());
			pipesem_wait(&sem);
			critical(i,getpid());
			pipesem_signal(&sem);
				noncritical(i,getpid());
			pipesem_wait(&sem);
			critical(i,getpid());
			pipesem_signal(&sem);
			exit(0);
		}
		else {
			c2=fork(); 
			if (c2<0) {
			printf("error\n");
			exit(-1);
			}
			else if(c2==0){
				kill(getpid(),SIGSTOP);
				i=2;
					noncritical(i,getpid());
				pipesem_wait(&sem);
				critical(i,getpid());
				pipesem_signal(&sem);
					noncritical(i,getpid());
				pipesem_wait(&sem);
				critical(i,getpid());
				pipesem_signal(&sem);
					noncritical(i,getpid());
				pipesem_wait(&sem);
				critical(i,getpid());
				pipesem_signal(&sem);
				exit(0);
			}
			else {
				c3=fork(); 
				if (c3<0) {
				printf("error\n");
				exit(-1);
				}
				else if(c3==0){
					kill(getpid(),SIGSTOP);
					i=3;
					pipesem_wait(&sem);
					critical(i,getpid());
					pipesem_signal(&sem);
						noncritical(i,getpid());
					pipesem_wait(&sem);
					critical(i,getpid());
					pipesem_signal(&sem);
						noncritical(i,getpid());
					pipesem_wait(&sem);
					critical(i,getpid());
					pipesem_signal(&sem);
						noncritical(i,getpid());
					exit(0);
				}
				else {
				sleep(2);
				kill(c1,SIGCONT);
				kill(c2,SIGCONT);
				kill(c3,SIGCONT);
				wait(&status);
				wait(&status);
				wait(&status);
				exit(0);
				}	
			}
		}
return 0;
}
	
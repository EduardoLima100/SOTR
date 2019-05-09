#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sched.h>
#define _GNU_SOURCE

int primo(int n, int d){
	int r = n%d;
	if(r==0 && d!=1 && n!=d){
		return 0;
	}
	if(d == 1){
		return 1;
	}
	return primo(n,d-1);
}

void *th_primos(void *arg){
	int i;
	for(i=5;i<=10000;i++){
		if(primo(i,i-1)){
			printf("%d é primo\n",i);
		}
	}
	pthread_exit(NULL);
}

int main(){
	struct cpu_set_t t_cpu;
	CPU_ZERO(&t_cpu);
	CPU_SET(4,&t_cpu);

	struct sched_param t_sched;
	t_sched.SCHED_PRIORITY = 5;

	pthread_t t;
	pthread_create(&t, NULL, th_primos,NULL);
	pthread_setschedparam(t,SHED_FIFO,&t_sched);

	pthread_join(t, NULL);

	return 0;
}

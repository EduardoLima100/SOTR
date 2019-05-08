#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int primo(int n, int d){
	int res = n%d;
	if(res == 0 && d!=n && d!=1){
		return 0;
	}
	if(d==1){
		return 1;
	}
	return primo(n,d-1);
}

void *th_primo(void *arg){
	int i = 5;
	for(;i<=1000;i++){
		if(primo(i,i)){
			printf("[%d] é primo",i);
		}
	}
}

int main(){
	pthread_t t;
	struct cpu_set_t t_cpu;
	struct sched_param t_sched;

	cpu_zero(&t_cpu);
	cpu_set(4,&t_cpu);

	t_sched.sched_priority = 5;

	pthread_create(&t, NULL, th_primo,NULL);
	pthread_setaffinity_np(t,sizeof(t_cpu),&t_cpu);
	pthread_setschedparam(t,sched_fifo,&t_sched);
	pthread_join(t,NULL);
	return 0;
}
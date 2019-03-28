#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Task{
	int prio;
	int C;
	int P;
	int D;
	float U;
} Task;

void analise_u(Task *tasks){
	prtinf()
	float s = 0;
	float n = 3;//sizeof(tasks)/sizeof(Task);

	int i;
	for(i=0;i<n;i++){
		printf("\n%i ",i);
		printf(" U = %f", tasks[i].U);
		s = s + tasks[i].U;
	}

	printf("\nU = %f", s);

	float lim = n*(pow(2,1/n)-1);
	printf("\nLimite = %f", lim);
	if(s < lim){
		printf("\nEscalonamento é possível\n");
	}
	else{
		printf("\nPossibilidade de escalonamento incerta\n");
	}
}

/*
void analise_tr(){
}
*/

int main(){
	Task tasks[3];
	//definir forma aleatória os valores de C e P(srand(); rand())

	tasks[0].P = 100;
	tasks[0].C = 20;
	tasks[0].prio = 1;
	tasks[0].D = tasks[0].P;
	tasks[0].U = (float)tasks[0].C/(float)tasks[0].P;

	tasks[1].P = 150;
	tasks[1].C = 50;
	tasks[1].prio = 2;
	tasks[1].D = tasks[1].P;
	tasks[1].U = (float)tasks[1].C/(float)tasks[1].P;

	tasks[2].P = 200;
	tasks[2].C = 40;
	tasks[2].prio = 3;
	tasks[2].D = tasks[2].P;
	tasks[2].U = (float)tasks[2].C/(float)tasks[2].P;

	analise_u(tasks);
	//analise_tr();
}

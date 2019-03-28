#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N_TASKS 3

typedef struct Task{
	int prio;
	int C;
	int P;
	int D;
	float U;
} Task;

void analise_u(Task *tasks,float n){
	printf("\n\nAnálise de Utilização");
	float s = 0;

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
	srand(time(0));

	int n = N_TASKS;
	Task tasks[n];
	//definir forma aleatória os valores de C e P(srand(); rand())

	int i;
	for(i=0;i<n;i++){
		tasks[i].P = (rand() % 500);
		tasks[i].C = (rand() % 100);
		tasks[i].prio = i;
		tasks[i].D = tasks[i].P;
		tasks[i].U = (float)tasks[i].C/(float)tasks[i].P;
		printf("\nTask = %i", i);
		printf("\nP = %i", tasks[i].P);
		printf("\nC = %i\n", tasks[i].C);
	}

	analise_u(tasks,n);
	//analise_tr();
}

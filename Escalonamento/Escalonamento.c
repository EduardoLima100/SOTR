#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N_TASKS 3

typedef struct Task{
	int prio;	//Prioridade
	int C;
	int P;		//Período
	int D;
	float U;
} Task;

void analise_u(Task *tasks, float n){
	printf("\n\nAnálise por Utilização");
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

void analise_tr(Task *tasks, float n){
	printf("\n\nAnálise por Tempo de Resposta");
	float Ci, Cj;
	float Pi, Pj;
	float Rant, R;
	float I;
	int i;
	int j;

	i = 0;
	while(j<n){
		Ci = tasks[i].C;
		Pi = tasks[i].P;

		Rant = 0;
		R = Ci;
		while(!(Rant == R) && R<Pi && i>0){
			Rant = R;
			I = 0;
			for(j=0; j<i;j++){
				Cj = tasks[j].C;
				Pj = tasks[j].P;
				I = I + ceil(Rant/Pj)*Cj;
			}
			R = Ci + I;
		}
		i = i + 1;
	}


	if(R>=Pi){
		printf("\nEscalonamento não é possível\n");
	}
	else{
		printf("\nEscalonamento é possível\n");
	}
}

int main(){
	srand(time(0));

	int n = N_TASKS;
	Task tasks[n], tasks_prio[n];
	
	int i;
	for(i=0;i<n;i++){
		tasks[i].prio = 0;
		tasks[i].P = rand() % 500;
		tasks[i].C = rand() % 100;
		tasks[i].prio = i;
		tasks[i].D = tasks[i].P;
		tasks[i].U = (float)tasks[i].C/(float)tasks[i].P;
		printf("\nTask = %i", i);
		printf("\nP = %i", tasks[i].P);
		printf("\nC = %i\n", tasks[i].C);
	}

	analise_u(tasks,n);
		
	int j = 0;
  	int men = 0;
  	for (i = 0;i<n;i++){
    	while(j<(n-1)){
      		if (tasks[men].P >= tasks[j+1].P){
        		men = j+1;
      		}
      		j++;
    	}
    	tasks[men].prio = i+1;
   		tasks_prio[i] = tasks[men];
    	tasks[men].P = 500*n;
    	j = -1;
  	}
	for(i=0;i<n;i++){
		printf("prio[%i] = %i\n", i, tasks[i].prio);
	}

	analise_tr(tasks,n);
}
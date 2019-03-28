#include <stdio.h>
#include <stdlib.h>

typedef struct Task{
	int prio;
	int C;
	int P;
	int D = P;
	float U = (float)C/(float)P;
} Task;

void analise_u(Task *tasks){
	int s = 0;
	int n = sizeof(tasks)/sizeof(Task);

	int i;
	for(i=0;i<n;i++){
		s = s + tasks[i].U;
	}

	printf("\n U = %f", s);

	if(s<n*(pow(2,(float)1/n)-1)){
		printf("Escalonamento é possível");
	}
	else{
		printf("Possibilidade de escalonamento incerta");
	}
}

//void analise_tr(){
//}

int main(){
	printf("Main")
	Task tasks[10];
	//definir forma aleatória os valores de C e P(srand(); rand())

	analise_u(tasks);
	//analise_tr();
}

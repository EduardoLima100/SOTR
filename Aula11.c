Programação de Tarefas Periódicas
	Sinais (Signals)
		A criação de um Timer em POSIX permite gerar sinais em intervalos regulares de tempo
		É possível criar um software que captura sinais vindos do SO e que liberam a thread para execução
			Assim, a thread fica em modo bloqueio (sem utilizar CPU) até que seja acordada pelo SO
		Para lidar com sinais é necessário utilizar a biblioteca <signal.h>
			Sinais em POSIX para Tempo Real variam de SIGRTMIN(33) até SIGRTMAX(64) - 32 sinais por processo

		Em especial, para capturar sinais utiliza-se:
			sigset_t sinais;				//Conjunto de sinais
			sigemptyset(sigset_t *S);		//Limpa um conjunto de sinais
			sigaddset(sigset_t *S, int N);	//Adiciona sinal N ao conjunto
			int sigprocmask(int HOW, const sigset_t *S, sigset_t *OLDSET);	//Indica COMO(SIG_BLOCK,SIG_UNBLOCK) bloqueia sinais
			int sigwait(const sigset_t *S, int SIG);	//Espera a ocorrência de um sinal do conjunto de sinais. Ao capturar o sinal, SIG aponta para o sinal que foi capturado

		Exemplo:
			#include <signal.h>
			#include <stdio.h>
			#include<stdlib.h>

			int main(){
				int sig;
				sigset_t s;
				sigemptyset(&s);
				sigaddset(&s, SIGINT);	//CONTROL-C
				sigprocmask(SIG_BLOCK, &s, NULL);
				for(;;){
					sigwait(&s, &sig);
					printf("Recebeu sinal: %d\n", sig);
				}
				return 0;
			}
			//Buscar outros sinais POSIX e modificar o exemplo para capturar outros sinais

	
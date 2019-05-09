/*
Programação Pthreads (Mutexes)
	Semáforos
		Lembrando:
			wait(semaforo) ou P(semáforo) - proberen(testar)
				Enquanto semáforo for igual a 0, processo bloqueia
				Caso contrário, decrementa o semáforo

			signal(semáforo) ou V(semaforo) - verhogen(incrementar)
				Se existir processo bloqueado, desbloqueia um processo
				Caso contrário, incrementa o semáforo

	Mutex
		Tem operações para lock e unlock (assim como para um semáforo) de uma variável do tipo mutex (mutual exclusion)
		Porém, diferentemente do semáforo, o mutex pertence a uma thread(ownership)
			Uma vez que uma thread A executa um lock e obtém o mutex X, outra thread B não pode liberar (unlock) o mutex X, pois o mesmo já pertence a thread A
			Já um semáforo pode ter suas operações executadas por diferentes threads de execução

		Para usar mutex em pthreads temos:
			#include <pthread.h>
			pthread_mutex_t mutex; //Cria uma variável do tipo mutex
			int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutex_t *attr); //Inicializa um mutex
			int pthread_mutex_destroy(pthread_mutex_t *mutex); //Destrói um mutex
			pthread_mutex_t mutex = PTREAD_MUTEX_INITIALIZER; //Macro para inicializar um mutex

			int pthread_mutex_lock(pthread_mutex_t *mutex); 	//Obtém o mutex para uso da thread
			int pthread_mutex_trylock(pthread_mutex_t *mutex); 	//Funciona pthread_mutex_lock, mas se o mutex estiver sendo ocupado, retorna imediatamente indicando que o recurso está em uso
			int pthread_mutex_unlock(pthread_mutex_t *mutex);	//Libera o mutex para uso

	Exemplo:
*/
		#include <pthread.h>
		#include <stdio.h>
		#include <stdlib.h>
		#include <unistd.h>

		#define NUM_THREADS	5

		pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

		void *PrintHello(void *threadid){
			long tid;
			tid = (long) threadid;
			printf("Thread %ld tentando obter mutex!\n", tid);
			pthread_mutex_lock(&mutex);
			printf("Thread %ld executando no mutex!\n", tid);
			usleep(1000000);
			printf("Thread %ld saindo do mutex!\n", tid);
			pthread_mutex_unlock(&mutex);
			printf("Thread %ld fora do mutex!\n", tid);
			pthread_exit(NULL);
		}

		int main(int argc, char *argv[]){
			pthread_t threads[NUM_THREADS];
			int rc;
			long t;
			for(t=0; t<NUM_THREADS; t++){
				printf("In main: crating thread %ld\n", t);
				rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
				if(rc){
					printf("ERROR: return code from pthread_create() is %d\n", rc);
					exit(-1);
				}
			}
			for(t=0; t<NUM_THREADS; t++){
				pthread_join(threads[t], NULL);
			}
		}
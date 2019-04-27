
Programação Pthreads
	Conceitos Básicos
		Processo
			Entidade ativa, uma instância de um programa, que está sendo executada
			Possibilita a execução de diferentes instruções, sendo escalonado pelo sistema operacional para execução

		Thread
			Um processo pode ser composto por várias threads de execução
			Cada thread executa de forma independente, mas tem acesso aos recursos do processo como, por exemplo, as variáveis globais do processo
			A execução independente ocorre porque as threads mantêm suas próprias esruturas de execução
			Ao compartilhar informações, todos os recursos modificados por uma thread afetam outras
			Dessa forma, existe uma "concorrência" entre as threads que precisam de programação do desenvolvedor para sincronizar explicitamente o acesso aos recursos pelas threads

	Pthreads
		É um conjunto padronizado de interface de programação
		POSIX threads, ou simplesmente Pthreads
		São definidas na linguagem C, através da implementação do header pthread.h

		O uso de Pthreads está ligado:
			A velocidade de criação comparado a processos normais (chamadas fork())
			Ao compartilhamento eficiente de informações entre threads (sem ter a necessidade de criar esruturas específicas de compartilhamento como uso de shm_open() em UNIX)

		Outra motivação ligada ao uso de concorrência em geral, está relacionada a ganhos expressivos de performance pela aplicação

	Programação Concorrente
		Compartilhamento de informações em conjunto com threads (ou tarefas) concorrente possibilita um aumento considerável na performance das aplicações
		Porém, introduz problemas relacionados a sincronização entre tarefas

	API Pthreads
		As funções oferecidas pela API (Aplication Programming Interface) são divididas em 4 grandes partes:
			Gerenciamento de Threads:
				Rotinas para:
					Criar
					Liberar
					Esperar
					Definir atributos
					Entre outros

			Mutexes:
				Rotinas para:
					Criar
					Destruir
					Lock e Unlock de mutexes

				Mutex (abreviação para "Mutual Exclusion")

			Variáveis de condição:
				Rotinas para trabalhar com variáveis de condições associadas a mutexes

			Sincronização:
				Rotinas para:
					Locks
					Leitura/Escrita
					Barriers

		Por convenção, todos os identificadores para tipos e funções em pthreads iniciam com o prefixo "pthread_"
		Para compilar programas Pthreads utiliza-se a inclusão da biblioteca Pthread (exemplo com gcc): gcc -lpthread

	Criando e Terminando Threads
		pthread_create(thread_id, attr, rotina_execução, argumentos)
		pthread_exit(status)
		pthread_join(thread_id, status)
		pthread_cancel(thread)
		pthread_attr_init(attr)
		pthread_attr_destroy(attr)

		Exemplo:

			#include <pthread.h>
			#include <stdio.h>
			#include <stdlib.h>

			#define NUM_TRHEADS 10

			void *PrintHello(void *threadid){
				long tid;
				tid = (long)threadid;
				printf("Hello World! It's me, thread #%ld!\n", tid);
				pthread_exit(NULL);
			}

			int main(int argc, char *argv[]){
				pthread_t threads[NUM_TRHEADS];
				int rc;
				long t;
				for(t=0; t<NUM_TRHEADS; t++){
					printf("In main: creating thread %ld\n", t);
					rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
					if(rc){
						printf("ERROR: return code from pthread_create() is %d\n", rc);
						exit(-1);
					}
				}
				pthread_exit(NULL)
			}


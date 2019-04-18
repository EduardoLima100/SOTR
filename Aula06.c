
Programação Pthreads (Prioridades e Afinidades)
	As prioridades podem ser definidas junto com a fila de escalonamento associado ao processo
	
	Para isso as seguintes funções são utilizadas:
		int pthread_setschedparam(pthread_t thread, int policy, const struct sched_param *param);
		int pthread_getchedparam(pthread_t thread, int *policy, struct sched_param *param);

	Onde a estrutura sched_param é definida:
		struct sched_param{
			int sched_priority; //Sheduling priority
		};

Definir prioridades
	As seguintes políticas de escalonamento são definidas:
		SCHED_FIFO:
			FIFO com prioridades
		SCHED_RR:
			RR com prioridades
		SCHED_OTHER:
			Política normal do sistema (normalmente RR e outros mecanismos para otimizar o sistema do ponto de vista do usuário)

	Em Linux, é possível ler as prioridades max e min do escalonador da seguinte forma:
		#include <sched.h>
		int sched_get_priority_max(int policy);
		int sched_get_priority_min(int policy);

Definir afinidades
	Afinidade consiste em especificar para o Sistema Operacional, qual o processador em que a thread deve ser alocada
	Isso possibilita gerenciar da melhor forma o uso dos processadores de acordo com as necessidades da aplicação

	Em Linux, a seguinte função é definida para pthreads:
		#define _GNU_SOURCE //See feature_test_macros(7)
		#include <pthread.h>
		int pthread_setaffinity_np(pthread_t thread, size_t cpusetsize, const cpu_set_t *cpuset);
		int pthread_getaffinity_np(pthread_t thread, size_t cpusetsize, cpu_set_t *cpuset);

	Porém, para definir corretamente as afinidades, é necessário manipular a estrutura cpu_set_t(que apresenta o conjunto de processadores do sistema) para definir o processador para execução da thread

	Em Linux, as principais macros incluem:
		#define _GNU_SOURCE //See feature_test_macros(7)
		#include <sched.h>

		void CPU_ZERO(cpu_set_t *set);				//Limpa o conjunto
		void CPU_SET(int cpu, cpu_set_t *set);		//Adiciona uma CPU ao conjunto
		void CPU_CLR(int cpu, cpu_set_t *set);		//Remove uma CPU do conjunto
		int CPU_ISSET(int cpu, cpu_set_t *set);		//Verifica se a CPU está no conjunto
		int CPU_COUNT(cpu_set_t *set);				//Retorna a quantidade de CPUs no conjunto

Obter a quantidade de processadores
	As macros anteriores permitem manipular a estrutura cpu_set_t, mas não permitem obter do sistema a quantidade de processadores existentes
	Uma das maneiras para obter isso é utilizar a função sysconf (que obtém dados de alguma configuração do sistema, em processadores atualmente disponíveis);
		#include <unistd.h>
		long sysconf(int name) //definiçaõ
		long procs = sysconf(_SC_NPROCESSORS_ONLN); //uso
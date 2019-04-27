Programação Pthreads
	Variáveis de condição
		Permite que uma thread espere, dentro de uma região crítica, atpe que uma condição sobre algum dado seja modificada
		Efetivemente, permite que as threads deixem de realizar "busy waiting" sobre um dado, aumentando a utilização do processador
		
		Por exemplo (considerando os filósofos glutões):
			while(garfo[i] != 0){};				//busy waiting
			while(garfo[i] != 0){espere();};	//var. condição
		
		Uma variável de condição sempre estará relacionada a um mutex
		Ou seja, a condição para esperar na variável de condição, necessita que a thread já tenha obtido o mutex

		Por exemplo:
			mutex_lock();
				while(garfo[i] != 0) espere();
			mutex_unlock();

		Para usar variáveis de condição temos:
			#include <pthread.h>

			int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
			int pthread_cond_timewait(pthread_cond_t *cond, pthread_mutex_t *mutex, const struct timespec *abstime);
			int pthread_cond_signal(pthread_cond_t *cond);
			int pthread_cond_broadcast(pthread_cond_t *cond);
			int pthread_cond_destroy(pthread_cond_t *cond);
			int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr);
			pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
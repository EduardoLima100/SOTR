//Aula 02


Escalonamento Taxa Monotônica(RM)
	Tarefas são periódicas e independentes
	O "deadline" das tarefas são iguais aos seus períodos (Di = Pi)
	Tempo de computação da tarefa Ci é conhecido e constante (derivação do WECET)
	O tempo overhead para o chaveamento entre tarefas (context switch) é dito nulo

	Política de definição de prioridades:
		Prioridades decrescem em função do aumento dos períodos
		Ou seja, quanto maior a frequÊncia de ativação da tarefa, maior será a sua prioridade

	Atribuição é feita de forma estática, em tempo de projeto, antes da execução do sistema
		Como o uso do escalonamento baseado em filas de prioridades, em conjunto com preempção, o sistema irá se comportar (do ponto de vista temporal) de acordo com sua análise anterior

	Utilizando o escalonamento de Taxa Monotônica, é possível impor uma condição suficiente (baseada em utilização) para a análise de escalonamento:
		U = somatório(Ui)< n * (2**(1/n)-1), onde n é o número de tarefas da aplicação

Escalonamento "Earliest Deadline First" (EDF)
	O escalonamento ocorre dinamicamente, durante o tempo de execução através de um escalonamento preemptivo e baseado em prioridades

	Tarefas são periódicas e independentes
	O "deadline" das tarefas são iguais aos seus períodos
	Tempo de computação da tarefa Ci é conhecido e constante (derivação do WECET)
	O tempo overhead para o chaveamento entre tarefas (context switch) é dito nulo
	(Mesmas descritas anteriormente para o RM)

	Política de escalonamento:
		No EDF a atribuição dinâmica de prioridades ocorre a cada momento que uma tarefa entra na fila de processos prontos para escalonamento
		Nesse momento, ocorre uma "reordenação" das tarefas na fila para encontrar o processo cujo deadline absoluto está mais próximo (considerando o tempo atual do sistema)
		Esse processo, como o deadline absoluto mais próximo é escolhido para execução

	Uma das grandes vantagens do EDF é que seu teste suficiente e necessário é o limite teórico:
		U = somatório(Ui) <= 1, onde n é o número de tarefas da aplicação

	Problemas podem ser:
		Maior overhead de escalonamento
		Possíveis imprevisibilidades na ocorrência de falhas

Escalonamento Deadline Monotônico (DM):
	Estende o RM que limitava períodos para deadlines
	Também considerado um algorítmo ótimo em sua classe

	Tarefas são periódicas e independentes
	O "deadline" das tarefas são iguais ou menores ao do seu período (Di <= Pi)
	Tempo de computação da tarefa Ci é conhecido e constante (derivação do WECET)
	O tempo "overhead" para o chaveamento entre tarefas (context switch) é dito nulo



Análise por Tempo de Resposta
	Análise de escalonamento exata (tanto suficiente como necessária)
	Utilizada para modelos de escalonamento baseado em prioridades estáticas

	Contém um conjunto grande de extensões como, por exemplo:
		Lidar com dependências (offsets)
		COmpartilhamento de dados (bloqueio)
		Comunicação

	Conceitos básicos:
		Baseada na noção de instante crítico
			Momento em que todas as tarefas do sistema encontram-se na fila de processos prontos para execução
		
		É pior momento (maior sobrecarga) para a execução das tarefas do sistema
			Interferência decorrente de tarefas de maior ou igual prioridade sobre as outras tarefas de menor ou igual prioridade
		
		Caso as tarefas sejam escalonáveis nesse momento, elas serão escalonáveis em qualquer momento

		Utiliza o conceito de tempo de resposta máximo de uma tarefa (response time)
			Tempo de chegada da tarefa até o término de sua execução
			Considera a interferência de tarefas de maior ou igual prioridade sobre a tarefa sendo analisada

	Para calcular o tempo de resposta de uma tarefa i, temos a seguinte equação:
		Ri = Ci + somatório(Ij)j & hp(i)

		Onde:
			hp(i) são tarefas de maior prioridade que i
			Ij é a interferência que a tarefa i pode sofrer

		Ij = [Ri/Pj] * Cj

		Onde:
			Ri é a janela de tempo em análise
			[Ri/Pj] representa o número de liberações da tarefa j na janela de tempo

		A expreção pode ser reescrita como:
			Ri = Ci + somatório([Ri/Pi]*Ci0) j & hp(i)

		Como Ri aparece em ambos os lados da expreção, é necessário utilizar uma solução iterativa:
			Ri n+1 = Ci + somatório([Ri/Pi]*Ci0) j & hp(i)

			Ri 0 = Ci

		O método converge quando a tarefa é escalonável


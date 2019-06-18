# Sistemas Operacionais em Tempo Real

**Nome:** Eduardo Machado de Lima

**Matrícula:** 201620605


## Trabalho Final

O objetivo do trabalho é implementar um controle de temperatura para processos de fabricação de cerveja artesanal, tanto para aquecimento quanto para resfriamento, com controle via rede.

**1) Interface de controle:** Envia comandos para o simulador e recebe informações de temperatura

**2) Simulador:** Simula um programa embarcado que controla teperatura nos processos de fabricação de cerveja artesanal

Funções:

* Ligar sistema de aquecimento/refrigeração
* Desligar sistema de aquecimento/refrigeração
* Ajustar temperaturas máxima e mínima
* Definir aquecimento ou resfriamento
* Solicitar temperatura atual

Tarefas:

* Leitura de temperatura
* Envio da informação da temperatura para o monitor
* Controle do relé
* Recepção de comandos do monitor

Ojetivos adicionais:

* Programar rampas de temperaturas e seus tempos
* Avisar trocas de temperaturas


# Desenvolvimento

**Controle:**
	
* Conectar com um ou mais embarcados

Comandos enviados:

* Liga
* Desliga
* Configurar
	
	* Temperatura: max e min
	* Modo: aquecimento e resfriamento

* Solicitar estado atual (temperatura, modo, max e min)

**Embarcado**

* Conexão com o monitor

Funções:

* Leitura da temperatura
* Controle do relé

Comunicação com o monitor:

* Envio da temperatura para o monitor
* Recepção de controles do monitor





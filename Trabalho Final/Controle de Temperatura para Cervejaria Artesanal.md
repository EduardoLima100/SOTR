# Controle de Temperatura para Cervejaria Artesanal
**Nome:** Eduardo Machado de Lima

**Matrícula:** 201620605

## Introdução:

O objetivo do trabalho é implementar um controle de temperatura para processos de fabricação de cerveja artesanal, tanto para aquecimento quanto para resfriamento, com controle via rede. Para isso, a comunicação entre controle e embarcado será por comandos. Os comandos planejados de controle para embarcado serão: ligar, desligar, configurar e estado. A comunicação de embarcado para controle será através de informações, como: temperatura e estado, assim como o comando sair.

O servidor de controle deverá conectar com mais de um embarcado ao mesmo tempo.

## Desenvolvimento:

**Controle:**
	
Iniciado algum desenvolvimento de comunicação com o embarcado através dos códigos dos trabalhos realizados anteriormente na disciplina.
Função embarcado() criada para receber as informações e comandos do embarcado.

**Embarcado:**

Assim como no controle, o código do embarcado será baseado nos trabalhos realizados, então algumas partes da conexão já estão prontas, necessitando apenas de ajustes para a aplicação.
A função tmp_read() foi criada para rodar em uma thread, fazendo a leitura do termômetro do embarcado a cada 5 segundos e ainda informar se houver mudanças de temperatura de uma leitura para outra.
A função on_off() rodará em um thtread sómente para controle do relé, ela aguarda uma mudança de temperatura e liga ou desliga o relé de acordo com as configurações de funcionamento.


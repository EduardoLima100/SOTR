Programação Utilizando Sockets
	Socket?
		Define uma interface, abstração, entre a aplicção e a rede
		Uma aplicação cria um socket por onde passam os dados a serem trafegados pela rede
			O tipo do socket especifica a comunicação a ser utilizada, por exemplo (considerando o protocolo TCP/IP):
				Sem conexão (UDP)
				Orientação à conecção (TCP)

			Após a configuração do socket é possível receber e enviar dados pela rede para diferentes máquinas (hosts)

	Tipos básicos de sockets
		SOCK_STREAM
			Como o nome diz (stream), define sockets que utilizam o protocolo TCP
			Com garantias de recepção
			Com ordem
			Orientado à conexão

		SOCK_DGRAM
			Como o nome diz (datagram), define sockets que utilizam o protocolo UDP
			Sem garantias de recepção
			Sem ordem
			Sem noção de conexão

	Criação de socket em C
		

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <arpa/inet.h>      // inet_aton
#include <pthread.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t tmp_change = PTHREAD_COND_INITIALIZER;
pthread_cond_t rele_change = PTHREAD_COND_INITIALIZER;

/*
THREADS:
* void *tmp_read(void *arg)
* void *on_off(void *arg)

* void *read_control(void *arg)
* void *write_control(void *args)
*/

float tmp; //entrada do sensor
int rele = 0;

int tmin, tmax;
int mode; //1 for cool and 2 for heat

int sockfd;

//função modelo
void *leitura(void *arg) {
    char buffer[256];
    int n;
    while(1){
        bzero(buffer,sizeof(buffer));
        n = recv(sockfd,buffer,50,0);
        if (n <= 0) {
            printf("\nErro lendo do socket!\n");
            exit(1);
        }
        printf("\nMSG: %s",buffer);
    }
}

//leitura de temperatura
void *tmp_read(void*arg){
    while(1){
        pthread_mutex_lock(&m);
        temp_ant = temp;
        temp = tmp;

        if(temp-temp_ant>0.1 || -0.1<temp-temp_ant){
            pthread_cond_signal(&tmp_change);
        }
        pthread_mutex_unlock(&m);
    }
    delay(5000);
}

//controle do relé
void *on_off(){
    while(1){
        pthread_cond_wait(&tmp_change, &m);
        pthread_mutex_lock(&m);
        switch(mode){
            case 1:
            if(tmp>tmax){
                rele = 1;
                pthread_cond_signal(&rele_change);
            }
            else{
                if(tmp>tmin){
                    rele = 0;
                    pthread_cond_signal(&rele_change);
                }
            }
            break;
            case 2:
            if(tmp<tmin){
                rele = 1;
                pthread_cond_signal(&rele_change);
            }
            else{
                if(tmp>tmax){
                    rele = 0;
                    pthread_cond_signal(&rele_change);
                }
            }
            break;
        }
        pthread_mutex_unlock(&m);
    }
}


//código pouco modificado daqui para frente
int main(int argc, char *argv[]) {
    int portno, n;
    struct sockaddr_in serv_addr;
    pthread_t t;

    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"\nUso: %s nomehost porta\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("\nErro criando socket!\n");
        return -1;
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
//    serv_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    inet_aton(argv[1], &serv_addr.sin_addr);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
        printf("\nErro conectando!\n");
        return -1;
    }
    pthread_create(&t, NULL, leitura, NULL);
    do {
        bzero(buffer,sizeof(buffer));
        printf("\nDigite a mensagem (ou sair):");
        fgets(buffer,50,stdin);
        n = send(sockfd,buffer,50,0);
        if (n == -1) {
            printf("\nErro escrevendo no socket!\n");
            return -1;
        }
        if (strcmp(buffer,"sair\n") == 0) {
            send(sockfd, "sair", 4, 0);
            break;
        }
    } while (1);
    close(sockfd);
    return 0;
}

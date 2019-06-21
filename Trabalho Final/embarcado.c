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

#define AMB 22

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t TMP_change = PTHREAD_COND_INITIALIZER;
pthread_cond_t rele_change = PTHREAD_COND_INITIALIZER;

/*
THREADS:
* void *tmp_read(void *arg)
* void *on_off(void *arg)

* void *read_control(void *arg)
* void *write_control(void *args)
*/

float TMP; //entrada do sensor
int RUN = 0;
int rele = 0;

int tmin, tmax; //temperatura: min e max
int mode = 0; //0 para esfriar 1 para esquentar

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

//função para receber comandos
void *cmd_read(void *arg){
    char buffer[256];
    int n;
    while(1){
        bzero(buffer,sizeof(buffer));
        n = recv(sockfd,buffer,50,0);
        if(n<=0){
            printf("\nErro lendo do socket!\n");
            exit(1);
        }
        if(strcmp(buffer,"on")){
            RUN = 1;
        }
        if(strcmp(buffer,"off")){
            RUN = 0;
        }
        if(strcmp(buffer,"minmax")){
            bzero(buffer,sizeof(buffer));
            n = recv(sockfd,buffer,50,0);
            if(n<=0){
                printf("\nErro lendo do socket!\n");
                exit(1);
            }
            tmin = atoi(buffer);
            bzero(buffer,sizeof(buffer));
            n = recv(sockfd,buffer,50,0);
            if(n<=0){
                printf("\nErro lendo do socket!\n");
                exit(1);
            }
            tmax = atoi(buffer);

        }
        if(strcmp(buffer,"mode")){
            bzero(buffer,sizeof(buffer));
            n = recv(sockfd,buffer,50,0);
            if(n<=0){
                printf("\nErro lendo do socket!\n");
                exit(1);
            }
            mode = atoi(buffer);
        }
        if(strcmp(buffer,"status")){
            pthread_mutex_lock(&m);
            buffer = "Temperatura atual: %f\nModo %i\nTemperatura mínima: %i\nTemperatura máxima: %i\nRele: %i\nRun: %i",TMP,mode,tmin,tmax,rele,RUN;
            n = send(sockfd,buffer,50,0);
            if (n == -1) {
                printf("\nErro escrevendo no socket!\n");
                return -1;
            }
            pthread_mutex_unlock(&m);
        }
    }
}

/*LEITURA DE TEMPERATURA
A cada 1 segundo
    Verifica temperatura atual
    Se houver diferença maior que 0.1ºC entre duas medições
        Avisa o sistema da mudança de temperatura
*/
void *TMP_read(void*arg){
    pthread_mutex_lock(&m);
    float temp_ant = TMP;
    pthread_mutex_unlock(&m);
    while(1){
        pthread_mutex_lock(&m);
        if(TMP-temp_ant>=0.1 || -0.1>=TMP-temp_ant){
            temp_ant = TMP;
            pthread_cond_signal(&TMP_change);
        }
        pthread_mutex_unlock(&m);
        delay(1000);
    }
    
}

//controle do relé
void *on_off(void*arg){
    while(1){
        pthread_cond_wait(&TMP_change, &m);
        pthread_mutex_lock(&m);
        if(RUN){}
            switch(mode){
                case 0:
                if(TMP>tmax){
                    rele = 1;
                    pthread_cond_signal(&rele_change);
                }
                else{
                    if(TMP>tmin){
                        rele = 0;
                        pthread_cond_signal(&rele_change);
                    }
                }
                break;
                case 1:
                if(TMP<tmin){
                    rele = 1;
                    pthread_cond_signal(&rele_change);
                }
                else{
                    if(TMP>tmax){
                        rele = 0;
                        pthread_cond_signal(&rele_change);
                    }
                }
                break;
            }
        }
        pthread_mutex_unlock(&m);
    }
}

void *send_TMP(void*arg){
    int n;
    char buffer[256];
    while(1){
        pthread_cond_wait(&TMP_change,&m);
        pthread_mutex_lock(&m);
        buffer = "Temperatura: %f",TMP;
        n = send(sockfd,buffer,50,0);
        if (n == -1) {
            printf("\nErro escrevendo no socket!\n");
            return -1;
        }
        pthread_mutex_unlock(&m);
    }
}

void *amb(void*arg){
    while(1){
        pthread_mutex_lock(&m);
        if(rele == 0){
            if(TMP > AMB){
                TMP = TMP - (TMP-AMB)/4;
            }
            if(TMP<AMB){
                TMP = TMP + (AMB-TMP)/4;
            }
        }
        if(rele == 1){
            if(mode == 0){
                TMP = TMP - 1;
            }
            if(mode == 1){
                TMP = TMP + 1;
            }
        }
        pthread_mutex_unlock(&m);
        delay(3000);
    }
}

//código pouco modificado daqui para frente
int main(int argc, char *argv[]) {
    int portno, n;
    struct sockaddr_in serv_addr;
    pthread_t t[5];

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
    
    pthread_create(&t[0], NULL, cmd_read, NULL);
    pthread_create(&t[1], NULL, TMP_read, NULL);
    pthread_create(&t[2], NULL, on_off, NULL);
    pthread_create(&t[3], NULL, send_TMP, NULL);
    do {
        bzero(buffer,sizeof(buffer));
        printf("\nDigite sair para desconectar:");
        fgets(buffer,50,stdin);
        if (strcmp(buffer,"sair\n") == 0) {
            n = send(sockfd, "sair", 4, 0);
            if (n == -1) {
                printf("\nErro escrevendo no socket!\n");
                return -1;
            }
            break;
        }        
    } while (1);
    close(sockfd);
    return 0;
}

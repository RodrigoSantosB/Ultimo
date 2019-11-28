#include "ACore.h"
#include "server.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "Game.h"

#define MSG_MAX_SIZE 350
#define BUFFER_SIZE (MSG_MAX_SIZE + 100)
#define LOGIN_MAX_SIZE 13
#define MAX_CHAT_CLIENTS 3

#define CAIU 8
#define PLATAFORMA 1
#define POS_PERSON 5


int main() 
{
  //inicializa o server 
  char client_names[MAX_CHAT_CLIENTS][LOGIN_MAX_SIZE];
  char str_buffer[BUFFER_SIZE], aux_buffer[BUFFER_SIZE];
  
  serverInit(MAX_JOGADORES);
  printf("Server is running!\n");
  int sair = 0;

  ServerPack pacoteServidor;
  ClientPack pacoteCliente[3];
  int comecou = 0;

  //seta os jogadores em uma posição no mapa 
  //for (int i = 0; i < MAX_JOGADORES; i++){
     
  while (1) 
  {
    startTimer();
    //realiza conexao com o cliente
    int id = acceptConnection();
    if (id != NO_CONNECTION) {
      recvMsgFromClient(client_names[id], id, WAIT_FOR_IT);
      printf("%s connected id = %d\n", client_names[id], id);
      sendMsgToClient(&id, sizeof(int), id);
      pacoteServidor.jogadores[id].hp = 100;
      printf("%d conectou-se\n", id);
    }
    
    //Recebe a mensagem
    struct msg_ret_t msg_ret = recvMsg(&pacoteCliente);
    if (msg_ret.status == MESSAGE_OK) {
      printf("%d %d id: %d\n", pacoteCliente[id].posyPerso, pacoteCliente[id].posxPerso, id);
      if(!comecou){
        if (pacoteCliente[id].comecou == 1) {
                   // pacoteServidor.jogadores[0] = 0;
                    comecou = 1;
                    broadcast(&pacoteServidor, sizeof(ServerPack));
                }
     }else{
       id = msg_ret.client_id;
        broadcast(&pacoteServidor, sizeof(ServerPack));
      }
    }
  }
}

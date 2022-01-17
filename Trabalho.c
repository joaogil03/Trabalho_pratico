#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define TAMANHO 100

typedef struct 
{
  int nif;
  char codigo[50];
  int tempo;
  int distancia;
  int nrPedido;
}Utilizacao;

typedef struct 
{ 
 float custo;
 char tipo[50];
 int livre;
 int autonomia;
 char codigo[50];
}Equipamento;

int menu(); // onde vou criar o menu para o Utilizacao
int inserirEquipamento(Equipamento M[TAMANHO], int qt, char cod[50], char tp[50], int autonom, float ct); // inserir a Equipamento 
void listarEquipamento(Equipamento M[TAMANHO], int qt);
int removerEquipamento(Equipamento M[TAMANHO], int qt, char cod[50]);
int pedidoutilizacao(Equipamento M[TAMANHO], Utilizacao U[TAMANHO], int nPedido, int num, char cod[50], int temp, int dist, int qt);
int verificarcodigo(Equipamento M[TAMANHO], int qt, char cod[50]);
//int verificarlivre(Equipamento M[TAMANHO], Utilizacao U[TAMANHO], char cod[50], int qt, int nPedido);
int verificardistancia(Equipamento M[TAMANHO], int qt, int dist, char cod[50]);
void listarpedidos(Utilizacao U[TAMANHO], int nPedido);
int removerpedidos(Equipamento M[TAMANHO],Utilizacao U[TAMANHO], int qt, int contaPed, int nPedido);
int calcularpreco(Utilizacao U[TAMANHO], Equipamento M[TAMANHO], int qt, int nPedido);
//int vertransacoes(Utilizacao U[TAMANHO], Equipamento M[TAMANHO], char cod[50]);
int entregarEquipamento(Utilizacao U[TAMANHO], Equipamento M[TAMANHO], int qt, char cod[50]);

int menu()
{
  int opcao;
  
  do
      {
       printf(" M E N U \n");
       printf("1- Inserir Equipamento\n");
       printf("2- Listar Equipamento\n");
       printf("3- Remover Equipamento\n");
       printf("4- Pedido de utilizacao\n");
       printf("5- Listar pedidos\n");
       printf("6- Remover pedido de utilizacao\n");
       printf("7- Entregar Equipamento\n");
       printf("8- Calcular custo do pedido\n");
       printf("9- Ver Transacoes\n");
       printf("0- Sair\n");
       printf("Opcao: ");
       scanf("%d", &opcao);
      }
  while ((opcao>10)||(opcao<0));  // as opcoes para ja vao de 8 ate 0, logo tem de ser sempre menores que 9 e maiores que 0 
  
  return (opcao);
}

int inserirEquipamento(Equipamento M[TAMANHO], int qt, char cod[50], char tp[50], int autonom, float ct)
{
  if (qt<TAMANHO){
    strcpy(M[qt].codigo,cod);
    strcpy(M[qt].tipo,tp);
    M[qt].autonomia = autonom;
    M[qt].custo = ct; 
    M[qt].livre = 1;
    return(1);
  }
 
  return (0);
}

void listarEquipamento(Equipamento M[TAMANHO], int qt)
{
  int i;

  for ( i = 0; i < qt; i++)
  {
    printf("----------------\n");
    printf("Codigo: %s\n",M[i].codigo);
    printf("Tipo: %s\n",M[i].tipo);
    printf("Autonomia: %d\n",M[i].autonomia);
    printf("Custo: %.2f\n",M[i].custo);
    printf("Livre: %d\n", M[i].livre);
    printf("----------------\n");
  }
}

int removerEquipamento(Equipamento M[TAMANHO], int qt, char cod[50]) // se tiver 3 Equipamentos nao remove a segunda
{
  int i;
  for ( i = 0; i < qt; i++){
    if (strcmp(M[i].codigo,cod)==0){
      if (i == qt-1)
          return (1);
      else
         {       
          strcpy(M[i].codigo,M[qt-1].codigo);
          strcpy(M[i].tipo,M[qt-1].tipo);
          M[i].autonomia = M[qt-1].autonomia;
          M[i].custo = M[qt-1].custo;
          M[i].livre = M[qt-1].livre;
          return(1);
         }
     }
  }

  return (0);
}

int pedidoutilizacao(Equipamento M[TAMANHO], Utilizacao U[TAMANHO], int contaPed, int num, char cod[50], int temp, int dist, int qt)
{
  int i;
  
  for (i = 0; i < qt; i++){   
    if (contaPed<TAMANHO && strcmp(M[i].codigo,cod)==0)
    {
      strcpy(U[contaPed].codigo,cod);
      U[contaPed].nif = num;
      U[contaPed].tempo = temp;
      U[contaPed].distancia = dist;
      U[contaPed].nrPedido=contaPed+1;
      M[i].livre = 0;
      return (1);        
    }
  }
  
  return (0);
}

int verificarcodigo(Equipamento M[TAMANHO], int qt, char cod[50]) 
{
  int i;
  for ( i = 0; i < qt; i++){
    if (strcmp(M[i].codigo,cod)==0)
      return(1);
  }

  return (0);
}

int verificarlivre(Equipamento M[TAMANHO], char cod[50], int qt)
{
  int i, a;
  for ( a = 0; i < qt; a++){
    if (strcmp(M[a].codigo,cod)==0 && M[a].livre==1)
        return (1);    
  }
  printf("Nao esta disponovel\n");
  
  return(0);
}

int verificardistancia(Equipamento M[TAMANHO], int qt, int dist, char cod[50])  
{
  int i;
  for ( i = 0; i < qt; i++){
    if (strcmp(M[i].codigo,cod)==0 && M[i].autonomia>=dist)     
      return(1);
    
  }
  printf("Escolha uma distancia menor\n");       
  
  return(0);
}

void listarpedidos(Utilizacao U[TAMANHO], int nPedido)
{
  int i;
  for ( i = 0; i < nPedido; i++)
  {
      printf("----------------------\n");
      printf("Numero de ordem: %d\n", U[i].nrPedido);
      printf("NIF: %d\n", U[i].nif);
      printf("Codigo: %s\n", U[i].codigo);
      printf("Tempo: %d\n", U[i].tempo);
      printf("Distancia: %d\n", U[i].distancia);
      printf("----------------------\n"); 
  }
}

int removerpedidos(Equipamento M[TAMANHO],Utilizacao U[TAMANHO], int qt, int contaPed, int nPedido)
{
  int i, a;

  for ( i = 0; i < contaPed; i++){
    
    if (nPedido == U[i].nrPedido){
      
      for (a = 0; a < qt; a++){
        if (strcmp(M[a].codigo, U[i].codigo) == 0) {
            M[a].livre = 1;
            break;
        }
      }
      
      if (i == contaPed-1)
        return (1);
      else{       
        strcpy(U[i].codigo,U[contaPed-1].codigo);
        U[i].nif = U[contaPed-1].nif;
        U[i].tempo = U[contaPed-1].tempo;
        U[i].distancia = U[contaPed-1].distancia;
      
        return(1);
      }
    }
  }
  return (0);
}

int entregarEquipamento(Utilizacao U[TAMANHO], Equipamento M[TAMANHO], int qt, char cod[50])
{
  int i;
  for ( i = 0; i < qt; i++)
    if (strcmp(U[i].codigo,cod)==0 && strcmp(M[i].codigo,cod)==0)
     {
       M[i].livre--; 
       printf("Livre: %d\n", M[i].livre);
       break;
       return(1);
     }
   printf("Essa Equipamento nao foi requisitada, logo nao pode ser entregue\n");
   return(0);   
}

int calcularpreco(Utilizacao U[TAMANHO], Equipamento M[TAMANHO], int qt, int nPedido)
{
int i, a;
float preco;

for ( i = 0; i < nPedido; i++)
for ( a = 0; a < qt; a++)
if (U[i].nrPedido == nPedido)
 {
   if (strcmp(M[a].codigo,U[i].codigo)==0)
   {
    preco= U[i].tempo *M[a].custo;   
    printf("Preco a pagar: %d * %d = %.2f euros\n", U[i].tempo, M[a].custo, preco);
    break; 
    return (1);
   } 
 } 
  else
  {
  return 0;
  }
}

/*
int vertransacoes (Utilizacao U[TAMANHO], Equipamento M[TAMANHO], char cod[50])
{
  // pedir e verificar se existe o codigo
  // listar todas as transacoes adicionando os tempos e as distancias

  return 0;
}
*/
int main(int argc, char *argv[]) 
{
  Utilizacao Uti[TAMANHO];
  int contaPedidos=0;  // contador dos pedidos 
  int tempo, distancia, nif; 
  char codigoU[50];
  int uinserir, vcodigoU, vdistancia, premov;
  int stempo=0;
  int numPedido=0;

  
  Equipamento Mob[TAMANHO];
  int opcao;
  int livre=0, autonomia, quantidade=0;
  char codigoM[50];
  char tipo[50];
  float custo;
  int minserido, mremov, vcodigoM;
  int sdistancia=autonomia;
  int entregarm;
  int cpreco;

    do {
      opcao= menu();
      switch (opcao)
        {
      case 1:      // inserir Equipamento
            printf("Codigo: ");
            scanf("%s", codigoM);
            
            vcodigoM=verificarcodigo(Mob,quantidade,codigoM);  
          
          while (vcodigoM==1)
          {
               printf("Esse codigo ja existe\n");
               printf("Codigo: ");
               scanf("%s", codigoM);
               vcodigoM=verificarcodigo(Mob,quantidade,codigoM);
          }

            printf("Tipo: ");
            scanf("%s", tipo);
            printf("Autonomia: ");
            scanf("%d", &autonomia);
            printf("Custo: ");
            scanf("%f", &custo);
            

            minserido = inserirEquipamento(Mob,quantidade,codigoM,tipo,autonomia,custo); 
          if (minserido == 1)
          {
              printf("Inserido!\n");
              quantidade++;
              livre++;
          }
          else 
          printf("Nao inserido!\n");

      break;
      
      case 2:                   // listar Equipamento
           listarEquipamento(Mob, quantidade);
      break;

      case 3:
            printf("Codigo: ");
            scanf("%s", codigoM);
            mremov = removerEquipamento(Mob, quantidade, codigoM);
           while (mremov==0)
           {
             printf("Esse codigo nao existe\n");
             printf("Codigo: ");
             scanf("%s", codigoM);
             mremov = removerEquipamento(Mob, quantidade, codigoM);
           }
           printf("Removido\n");
           quantidade--;
      break;

      case 4:  
          printf("Codigo: ");
          scanf("%s", codigoU);
          vcodigoU=verificarcodigo(Mob,quantidade,codigoU);  

          while (vcodigoU==0)
          {
               printf("Nao existe esse codigo\n");
               printf("Codigo: ");
               scanf("%s", codigoU);
               vcodigoU=verificarcodigo(Mob,quantidade,codigoU);
          }

          vcodigoU=verificarlivre(Mob,codigoU,quantidade);
          if (vcodigoU == 0){
            break;
          }

          printf("NIF: ");
          scanf("%d", &nif);
          printf("Tempo: ");
          scanf("%d", &tempo);
          printf("Distancia: ");
          scanf("%d", &distancia);
          vdistancia=verificardistancia(Mob,quantidade,distancia,codigoU); 
           
           while (vdistancia==0)
           {
             printf("Distancia: ");
             scanf("%d", &distancia);
             vdistancia=verificardistancia(Mob,quantidade,distancia,codigoU);
           }
           
           
           uinserir = pedidoutilizacao(Mob, Uti, contaPedidos, nif, codigoU, tempo, distancia, quantidade);
           
           if (uinserir == 1)
              {
                 printf("O pedido foi registado!\n");
                 contaPedidos++;
                 stempo=stempo + tempo;                
                 sdistancia= sdistancia - distancia;
              }
              else 
              printf("Pedido recusado!\n");
      break;
       
      case 5:
              listarpedidos(Uti,contaPedidos); 
      break;
      
      case 6:  
            printf("Numero do Pedido: ");
            scanf("%d", &numPedido);
            premov=removerpedidos(Mob,Uti,quantidade,contaPedidos, numPedido);

             while (premov==0)
             {
                printf("Nao existe esse Pedido\n");
                printf("Numero do Pedido: ");
                scanf("%d", &numPedido);
                premov=removerpedidos(Mob,Uti,quantidade,contaPedidos, numPedido);
             }
              printf("Removido\n");
              contaPedidos--;
      break;

      case 7: // entregar veiculos
             printf("Codigo: ");
             scanf("%s", codigoM);
            entregarm=entregarEquipamento(Uti,Mob,quantidade,codigoU);
               while (entregarm==0)
               {
                 printf("Codigo: ");
                 scanf("%s", codigoM);
                 entregarm=entregarEquipamento(Uti,Mob,quantidade,codigoU);
               }
               printf("Entregue\n"); 
      break;

      case 8:
            printf("Numero do Pedido: ");
            scanf("%d", &numPedido);
            cpreco=calcularpreco(Uti,Mob,quantidade,numPedido);
            
            while (cpreco==0)
            {
             printf("Numero de ordem: ");
             scanf("%d", &numPedido);
             cpreco=calcularpreco(Uti,Mob,quantidade,numPedido);
            }
      break;
      
      case 9:
            // ver transacoes 
      break;
        
      }  
       } while (opcao != 0);            
    return(0);   
}

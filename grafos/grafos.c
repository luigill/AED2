// Lui Gill, Luísa Ribeiro e Marcus Monteiro

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maximo 20
#define infinito 999

int menu();
void limpaGrafo(int ma[maximo][maximo], int tamanho);
void inserirAresta(int ma[maximo][maximo], int tamanho);
void removerAresta(int ma[maximo][maximo], int tamanho);
void listaGrafo(int ma[maximo][maximo], int tamanho);
void dijkstra(int ma[maximo][maximo], int tamanho);

int main()
{

  int tamanho = 0;
  int ma[maximo][maximo];
  int switchMenu = 0;

  printf("Digite o tamanho do grafo:\n");
  printf("Número máximo de vértices: %d\n", maximo);
  scanf("%d", &tamanho);
  while (tamanho > maximo)
  {
    printf("Número de vértices inválido!\n");
    printf("Digite novamente...\n");
    scanf("%d", &tamanho);
  }

  limpaGrafo(ma, tamanho);

  do
  {
    switchMenu = menu();
    switch (switchMenu)
    {
    case 1:
      inserirAresta(ma, tamanho);
      break;
    case 2:
      removerAresta(ma, tamanho);
      break;
    case 3:
      listaGrafo(ma, tamanho);
      break;
    case 4:
      dijkstra(ma, tamanho);
      break;
    case 5:
      printf("Saindo...\n");
      exit(0);
      break;
    default:
      printf("Opção Inválida!\n");
      break;
    }
  } while (1);

  return 0;
}

int menu()
{
  int op;
  printf("MENU:\n");
  printf("1) Adicionar Aresta:\n");
  printf("2) Remover Aresta:\n");
  printf("3) Listar Grafo:\n");
  printf("4) Algoritmo de Dijkstra:\n");
  printf("5) Sair...:\n");
  scanf("%d", &op);
  return op;
}

void limpaGrafo(int ma[maximo][maximo], int tamanho)
{
  for (int i = 0; i < tamanho; i++)
  {
    for (int j = 0; j < tamanho; j++)
    {
      ma[i][j] = 0;
    }
  }
}

void inserirAresta(int ma[maximo][maximo], int tamanho)
{
  int num1, num2, peso;

  printf("Escolha o vértice de origem entre 0 e %d:\n", tamanho - 1);
  scanf("%d", &num1);
  printf("Escolha o vértice de destino entre 0 e %d:\n", tamanho - 1);
  scanf("%d", &num2);
  printf("Escolha o peso da aresta:\n");
  scanf("%d", &peso);

  ma[num1][num2] = peso;
  ma[num2][num1] = peso;
}

void removerAresta(int ma[maximo][maximo], int tamanho)
{
  int num1, num2, peso;
  printf("Escolha o vértice de origem entre 0 e %d\n", tamanho - 1);
  scanf("%d", &num1);
  printf("Escolha o vértice de destino entre 0 e %d\n", tamanho - 1);
  scanf("%d", &num2);
  printf("Removendo...\n");

  ma[num1][num2] = 0;
  ma[num2][num1] = 0;
}

void listaGrafo(int ma[maximo][maximo], int tamanho)
{
  if (tamanho == 0)
  {
    printf("Não foi adicionado nenhum vértice ao grafo!\n");
  }
  printf("   ");
  for (int i = 0; i < tamanho; i++)
  {
    printf(" V%d ", i);
  }
  printf("\n");
  for (int i = 0; i < tamanho; i++)
  {
    for (int j = 0; j < tamanho; j++)
    {
      if (j == 0)
      {
        printf("V%d ", i);
      }
      printf("  %1d ", ma[i][j]);
    }
    printf("\n");
  }
}

void dijkstra(int ma[maximo][maximo], int tamanho)
{
  int inicio, fim, menorVertice, countVertice = 0, menorDistancia;
  int distancia[tamanho], anterior[tamanho], visitado[tamanho];

  printf("Digite o vértice de partida:\n");
  scanf("%d", &inicio);
  printf("Digite o vértice de chegada:\n");
  scanf("%d", &fim);

  menorVertice = fim;

  // inicialização dos vetores auxiliares
  for (int i = 0; i < tamanho; i++)
  {
    distancia[i] = infinito;
    anterior[i] = -1;
    visitado[i] = 0;
  }

  distancia[inicio] = 0;
  countVertice = 1;

  while (countVertice < tamanho)
  {
    menorDistancia = infinito;

    for (int i = 0; i < tamanho; i++)
    {
      if (distancia[i] < menorDistancia && visitado[i] == 0)
      {
        menorDistancia = distancia[i];
        menorVertice = i;
      }
    }

    visitado[menorVertice] = 1;

    for (int i = 0; i < tamanho; i++)
    {
      if (ma[menorVertice][i] != 0)
      {
        if (visitado[i] == 0)
        {
          if (menorDistancia + ma[menorVertice][i] < distancia[i])
          {
            distancia[i] = menorDistancia + ma[menorVertice][i];
            anterior[i] = menorVertice;
          }
        }
      }
    }
    countVertice++;
  }

  if (distancia[fim] == infinito)
  {
    printf("Não existem caminhos válidos.\n");
  }
  else
  {
    printf("A distância é de: %d\n", distancia[fim]);
    printf("O menor caminho é de %d\n", fim + 1);
    do
    {
      fim = anterior[fim];
      printf("%d ", fim + 1);
    } while (fim != inicio);

    printf("\n");
  }
}

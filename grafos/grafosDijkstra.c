// Lui Gill, Luísa Ribeiro e Marcus Monteiro

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_VERTICES 20
#define INFINITO INT_MAX

int menu();
void limpaGrafo(int grafo[MAX_VERTICES][MAX_VERTICES], int tamanho);
void inserirAresta(int grafo[MAX_VERTICES][MAX_VERTICES], int tamanho);
void removerAresta(int grafo[MAX_VERTICES][MAX_VERTICES], int tamanho);
void listaGrafo(int grafo[MAX_VERTICES][MAX_VERTICES], int tamanho);
void dijkstra(int grafo[MAX_VERTICES][MAX_VERTICES], int tamanho);

int main()
{
  int grafo[MAX_VERTICES][MAX_VERTICES];
  int tamanho = 0;
  int switchMenu = 0;

  while (tamanho <= 0 || tamanho > MAX_VERTICES)
  {
    printf("O número máximo de vértices é %d\n\n", MAX_VERTICES);
    printf("Quantos vértices deseja adicionar? ");
    scanf("%d", &tamanho);
  }

  limpaGrafo(grafo, tamanho);

  do
  {
    switchMenu = menu();

    switch (switchMenu)
    {
    case 1:
      inserirAresta(grafo, tamanho);
      break;
    case 2:
      removerAresta(grafo, tamanho);
      break;
    case 3:
      listaGrafo(grafo, tamanho);
      break;
    case 4:
      dijkstra(grafo, tamanho);
      break;
    case 5:
      printf("Saindo do programa...\n");
      exit(0);
      break;
    default:
      printf("Opção inválida!\n");
      break;
    }
  } while (1);

  return 0;
}

int menu()
{
  int op;
  printf("Menu - Implementação de Grafos\n");
  printf("1) Adicionar Aresta:\n");
  printf("2) Remover Aresta:\n");
  printf("3) Listar Grafo\n");
  printf("4) Algoritmo de Dijkstra\n");
  printf("5) Sair...\n");
  scanf("%d", &op);
  return op;
}

void limpaGrafo(int grafo[MAX_VERTICES][MAX_VERTICES], int tamanho)
{
  for (int i = 0; i < tamanho; i++)
  {
    for (int j = 0; j < tamanho; j++)
    {
      grafo[i][j] = 0;
    }
  }
}

void inserirAresta(int grafo[MAX_VERTICES][MAX_VERTICES], int tamanho)
{
  int num1, num2, peso;

  do
  {
    printf("Inserir vértice 1: ");
    scanf("%d", &num1);

    printf("Inserir vértice 2: ");
    scanf("%d", &num2);

    num1--;
    num2--;
  } while ((num1 < 0 || num1 >= tamanho) && (num2 < 0 || num2 >= tamanho));

  printf("Qual o peso da aresta?\n");
  scanf("%d", &peso);

  while (peso < 0)
  {
    printf("Peso inválido.\n");
    printf("Qual o peso da aresta?\n");
    scanf("%d", &peso);
  }
  // grafo não direcionado
  grafo[num1][num2] = peso;
  grafo[num2][num1] = peso;

  printf("Aresta adicionada.\n");
}

void removerAresta(int grafo[MAX_VERTICES][MAX_VERTICES], int tamanho)
{
  int num1, num2, peso;
  printf("Escolha o vértice de origem entre 1 e %d\n", tamanho);
  scanf("%d", &num1);
  num1--;
  printf("Escolha o vértice de destino entre 1 e %d\n", tamanho);
  scanf("%d", &num2);
  num2--;
  printf("Removendo...\n");

  if (grafo[num1][num2] == 0)
  {
    printf("Não existe aresta nessa posição!\n");
    return;
  }

  grafo[num1][num2] = 0;
  grafo[num2][num1] = 0;
}

void listaGrafo(int grafo[MAX_VERTICES][MAX_VERTICES], int tamanho)
{
  if (tamanho == 0)
  {
    printf("Não foi adicionado nenhum vértice ao grafo!\n");
  }
  printf("   ");
  for (int i = 0; i < tamanho; i++)
  {
    printf(" V%d ", i + 1);
  }
  printf("\n");
  for (int i = 0; i < tamanho; i++)
  {
    for (int j = 0; j < tamanho; j++)
    {
      if (j == 0)
      {
        printf("V%d ", i + 1);
      }
      printf("  %1d ", grafo[i][j]);
    }
    printf("\n");
  }
}

void dijkstra(int grafo[MAX_VERTICES][MAX_VERTICES], int tamanho)
{
  int inicio, final, menorVertice, countVertice = 0, menorDistancia;
  int distancia[tamanho], anterior[tamanho], visitado[tamanho];
  // vetores auxiliares do tamanho do grafo
  // distancia -> distancia do vértice inicial até o vértice corrente
  // anterior -> caminho até o vértice corrente
  // visitado -> controle dos vértices já visitados

  printf("Escolha o número do vértice de partida: \n");
  scanf("%d", &inicio);
  inicio--;

  printf("Escolha o número do vértice de chegada: \n");
  scanf("%d", &final);
  final--;

  menorVertice = final;

  // inicialização dos vetores
  for (int i = 0; i < tamanho; i++)
  {
    distancia[i] = INFINITO;
    anterior[i] = -1;
    visitado[i] = 0;
  }

  distancia[inicio] = 0;
  countVertice++;

  while (countVertice < tamanho)
  {
    menorDistancia = INFINITO;

    for (int i = 0; i < tamanho; i++)
    {
      // Procura vértice com menor distância e que não tenha sido visitado
      if (distancia[i] < menorDistancia && visitado[i] == 0) // tem conexão com o outro vértice && não foi visitado
      {
        menorDistancia = distancia[i];
        menorVertice = i;
      }
    }

    // verifica se existe o melhor caminho
    visitado[menorVertice] = 1; // marca que o nó está sendo visitado
    for (int i = 0; i < tamanho; i++)
    {
      if (grafo[menorVertice][i] != 0)
      {
        if (visitado[i] == 0)
        {
          if (menorDistancia + grafo[menorVertice][i] < distancia[i]) // testa se a conexão é menor que a já existente
          {
            distancia[i] = menorDistancia + grafo[menorVertice][i]; // se sim, atualiza a menor distancia
            anterior[i] = menorVertice;                             // e salvar na posição do vértice o vértice anterior
          }
        }
      }
    }
    countVertice++;
  }

  if (distancia[final] == INFINITO)
  {
    printf("Não tem caminhos válidos.\n");
  }
  else
  {
    printf("A distância é: %d\n", distancia[final]);
    printf("O menor caminho é: %d ", final + 1);
    do
    {
      final = anterior[final];
      printf("%d ", final + 1);
    } while (final != inicio);

    printf("\n");
  }
}
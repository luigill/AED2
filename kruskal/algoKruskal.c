#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct grafo
{
  int eh_ponderado;
  int nro_vertices;
  int grau_max;
  int **arestas;
  float **pesos;
  int *grau;
} Grafo;

Grafo *cria_Grafo(int nro_vertices, int grau_max, int eh_ponderado);
int insereAresta(Grafo *gr, int orig, int dest, int eh_digrafo, float peso);
void algKruskal(Grafo *gr, int orig, int *pai);

int main()
{
  int eh_digrafo = 0;
  Grafo *gr = cria_Grafo(6, 6, 1);
  insereAresta(gr, 0, 1, eh_digrafo, 6);
  insereAresta(gr, 0, 2, eh_digrafo, 1);
  insereAresta(gr, 0, 3, eh_digrafo, 5);
  insereAresta(gr, 1, 2, eh_digrafo, 2);
  insereAresta(gr, 1, 4, eh_digrafo, 5);
  insereAresta(gr, 2, 3, eh_digrafo, 2);
  insereAresta(gr, 2, 4, eh_digrafo, 6);
  insereAresta(gr, 2, 5, eh_digrafo, 4);
  insereAresta(gr, 3, 5, eh_digrafo, 4);
  insereAresta(gr, 4, 5, eh_digrafo, 3);

  int i, pai[6];
  algKruskal(gr, 0, pai);
  for (i = 0; i < 6; i++)
  {
    printf("%d: %d\n", pai[i], i);
  }

  return 0;
}

Grafo *cria_Grafo(int nro_vertices, int grau_max, int eh_ponderado)
{
  Grafo *gr;
  gr = (Grafo *)malloc(sizeof(struct grafo));
  if (gr != NULL)
  {
    int i;
    gr->nro_vertices = nro_vertices;
    gr->grau_max = grau_max;
    gr->eh_ponderado = (eh_ponderado != 0) ? 1 : 0;
    gr->grau = (int *)calloc(nro_vertices, sizeof(int));

    gr->arestas = (int **)malloc(nro_vertices * sizeof(int *));
    for (i = 0; i < nro_vertices; i++)
      gr->arestas[i] = (int *)malloc(grau_max * sizeof(int));

    if (gr->eh_ponderado)
    {
      gr->pesos = (float **)malloc(nro_vertices * sizeof(float *));
      for (i = 0; i < nro_vertices; i++)
        gr->pesos[i] = (float *)malloc(grau_max * sizeof(float));
    }
  }
  return gr;
}

int insereAresta(Grafo *gr, int orig, int dest, int eh_digrafo, float peso)
{
  if (gr == NULL)
    return 0;
  if (orig < 0 || orig >= gr->nro_vertices)
    return 0;
  if (dest < 0 || dest >= gr->nro_vertices)
    return 0;

  gr->arestas[orig][gr->grau[orig]] = dest;
  if (gr->eh_ponderado)
    gr->pesos[orig][gr->grau[orig]] = peso;
  gr->grau[orig]++;

  if (eh_digrafo == 0)
    insereAresta(gr, dest, orig, 1, peso);
  return 1;
}

// Parâmetros -> Grafo, vértice de origem e vetor pai
void algKruskal(Grafo *gr, int orig, int *pai)
{
  int i, j, dest, primeiro, NV = gr->nro_vertices;
  double menorPeso;
  // vetor auxiliar com o mesmo número de vértices do grafo;
  int *arv = (int *)malloc(NV * sizeof(int));
  for (i = 0; i < NV; i++)
  {
    arv[i] = i;  // vetor de árvores, começa como uma árvore independente;
                 // cada vértice recebe ele mesmo como valor;
    pai[i] = -1; // os vértices não possuem pai ainda
  }
  pai[orig] = orig; // vértice de origem recebe ele mesmo como pai;

  // Começa a busca
  while (1)
  {
    primeiro = 1;            // teste de condição;
    for (i = 0; i < NV; i++) // percorre os vértices;
    {
      for (j = 0; j < gr->grau[i]; j++) // percorre as arestas daquele vértice;
      {
        // procura a aresta de menor custo;

        // caso os vértices sejam diferentes, é possível conectar eles em uma mesma árvore;
        // gr->arestas[i][j] = aresta que liga i a j;
        if (arv[i] != arv[gr->arestas[i][j]])
        {
          if (primeiro) // já se tentou conectar alguém antes?
          {
            menorPeso = gr->pesos[i][j];
            orig = i;
            dest = gr->arestas[i][j];
            primeiro = 0;
          }
          else
          // trata quando se acha alguma aresta menor do que a anterior;
          {
            if (menorPeso > gr->pesos[i][j])
            {
              menorPeso = gr->pesos[i][j]; // menor peso passa a ser o novo peso da aresta testada;
              orig = i;
              dest = gr->arestas[i][j]; // dest passa a ser a aresta conectando i e j;
            }
          }
        }
      }
    }
    if (primeiro == 1) // caso nenhum vértice tenha satisfeito a condição ou todos ja fazem parte da árvore geradora;
      break;
    // tratamento para ajuste de pais;
    if (pai[orig] == -1)
      pai[orig] = dest;
    else
      pai[dest] = orig;
    // os vértices passam a fazer parte da mesma árvore;
    // transforma-se as árvores orig e dest no mesmo identificador;
    for (i = 0; i < NV; i++)
    {
      if (arv[i] == arv[dest])
        arv[i] = arv[orig];
    }
  }
  free(arv);
}
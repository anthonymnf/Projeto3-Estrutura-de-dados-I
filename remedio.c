#include <stdio.h>
#include <stdlib.h>
#include "remedio.h"

// Projeto de um sistema de fármacia (FINALIZADO)

struct Remedio
{
  int codigo;
  char nome[30];
  float preco;
  int estoque;
};

// Funções adicionadas para lidar com listas
struct no
{
  Remedio dado;
  struct no *prox;
};

struct lista
{
  No *inicio;
};

void adicionaFim(Lista *lista, Remedio e)
{
  No *novo = (No *)malloc(sizeof(No));
  novo->dado = e;
  novo->prox = NULL;
  if (lista->inicio == NULL)
  {
    lista->inicio = novo;
  }
  else
  {
    No *pi;
    for (pi = lista->inicio; pi->prox != NULL; pi = pi->prox)
      ;
    pi->prox = novo;
  }
}

void editarLista(Lista *lista, int cod)
{
  if (lista->inicio == NULL)
  {
    printf("Lista vazia\n");
  }
  else
  {
    No *pi;
    for (pi = lista->inicio; pi != NULL && pi->dado.codigo != cod; pi = pi->prox)
      ;
    if (pi == NULL)
    {
      printf("Remedio nao encontrado\n");
    }
    else
    {
      int option;
      printf("Escolha uma opcao:\n");
      printf("1 - Editar preco\n");
      printf("Qualquer outro numero - Editar estoque\n");
      scanf("%d", &option);
      if (option == 1)
      {
        float price;
        printf("Informe o novo preco:\n");
        scanf("%f", &price);
        pi->dado.preco = price;
        printf("Preco atualizado: %.2f\n", pi->dado.preco);
      }
      else
      {
        int stock;
        printf("Informe o novo estoque:\n");
        scanf("%i", &stock);
        pi->dado.estoque = stock;
        printf("Estoque atualizado: %d\n", pi->dado.estoque);
      }
    }
  }
}

void deletar(Lista *lista, int cod)
{
  if (lista->inicio == NULL)
  {
    printf("Lista vazia\n");
  }
  else
  {
    No *pa = NULL;
    No *pi;
    for (pi = lista->inicio; pi->prox != NULL && pi->dado.codigo != cod; pi = pi->prox)
    {
      pa = pi;
    }
    if (pa == NULL)
    {
      if (pi->dado.codigo == cod)
      {
        lista->inicio = pi->prox;
        free(pi);
      }
      else
      {
        printf("Elemento nao encontrado\n");
      }
    }
    else
    {
      if (pi->dado.codigo == cod)
      {
        pa->prox = pi->prox;
        free(pi);
      }
      else
      {
        printf("Elemento nao encontrado\n");
      }
    }
  }
}

void lerLista(Lista *lista)
{
  FILE *file = fopen("pharma.b", "rb");
  Remedio e;
  while (fread(&e, sizeof(Remedio), 1, file))
  {
    adicionaFim(lista, e);
  }
  fclose(file);
}

void salvaLista(Lista *lista)
{
  FILE *file = fopen("pharma.b", "wb");
  No *pi;
  for (pi = lista->inicio; pi != NULL; pi = pi->prox)
  {
    fwrite(&pi->dado, sizeof(Remedio), 1, file);
  }
  fclose(file);
}

void ordenarLista()
{
  Lista lista;
  lista.inicio = NULL;
  lerLista(&lista);
  No *pi;
  No *pj;
  No *pfim = NULL;
  if (lista.inicio == NULL)
  {
    return;
  }
  for (pi = lista.inicio; pi->prox != NULL; pi = pi->prox)
  {
    for (pj = lista.inicio; pj->prox != pfim; pj = pj->prox)
    {
      if (pj->dado.codigo > pj->prox->dado.codigo)
      {
        Remedio temp = pj->dado;
        pj->dado = pj->prox->dado;
        pj->prox->dado = temp;
      }
    }
  }
  salvaLista(&lista);
}

// Função responsável por cadastrar remédios em pharma.b
void cadastrar()
{
  FILE *file = fopen("pharma.b", "ab");
  Remedio a;
  printf("Informe os dados do remedio na ordem: Codigo Nome Preco e Estoque\n");
  scanf("%d %s %f %d", &a.codigo, a.nome, &a.preco, &a.estoque);
  fwrite(&a, sizeof(Remedio), 1, file);
  fclose(file);
}

// Função responsável por cadastrar remédios em promoçaõ no arquivo promocao.b
void cadastrarPromocao()
{
  FILE *file = fopen("promocao.b", "ab");
  int a;
  printf("Informe o codigo do remedio em promocao:\n");
  scanf("%d", &a);
  fwrite(&a, sizeof(int), 1, file);
  fclose(file);
}

// Função responsável por buscar remédios em pharma.b
void buscar(int cod)
{
  FILE *file = fopen("pharma.b", "rb");
  Remedio a;
  int entrou = 0;
  while (fread(&a, sizeof(Remedio), 1, file))
  {
    if (a.codigo == cod)
    {
      printf("\nNome: %s\n", a.nome);
      printf("- Codigo: %d\n", a.codigo);
      printf("- Preco: %.2f\n", a.preco);
      printf("- Quantidade em estoque: %d\n", a.estoque);
      entrou = 1;
    }
  }
  if (entrou == 0)
  {
    printf("Remedio nao encontrado\n");
  }
  fclose(file);
}

// Função responsável por buscar remédios em promoção no arquivo promocao.b
void buscarPromocao()
{
  FILE *file = fopen("promocao.b", "rb");
  int a;
  printf("Remedios em promocao:\n");
  while (fread(&a, sizeof(int), 1, file))
  {
    buscar(a);
  }
  fclose(file);
}

// Função responsável por listar os remédios de pharma.b
void listar()
{
  FILE *file = fopen("pharma.b", "rb");
  Remedio a;
  while (fread(&a, sizeof(Remedio), 1, file))
  {
    printf("\nNome: %s\n", a.nome);
    printf("- Codigo: %d\n", a.codigo);
    printf("- Preco: %.2f\n", a.preco);
    printf("- Quantidade em estoque: %d\n", a.estoque);
  }
  fclose(file);
}

// Função responsável por contar a quantidade de remédios cadastrados em pharma.b
int tamanho()
{
  FILE *file = fopen("pharma.b", "rb");
  Remedio a;
  int cont = 0;
  while (fread(&a, sizeof(Remedio), 1, file))
  {
    cont++;
  }
  fclose(file);
  return cont;
}

// Função que checa os remédios com o estoque acabando, aqui o parametro para saber que está acabando é ter menos de 50 no estoque
void estoqueAcabando()
{
  FILE *file = fopen("pharma.b", "rb");
  Remedio a;
  int entrou = 0;
  printf("Remedios com o estoque acabando: \n");
  while (fread(&a, sizeof(Remedio), 1, file))
  {
    if (a.estoque < 50)
    {
      printf("\nNome: %s\n", a.nome);
      printf("- Codigo: %d\n", a.codigo);
      printf("- Quantidade em estoque: %d\n", a.estoque);
      entrou++;
    }
  }
  if (entrou == 0)
  {
    printf("Estoque cheio, nenhum remedio com menos de 50 unidades no estoque.\n");
  }

  fclose(file);
}

// Função responsável por excluir um remédio em pharma.b, através do seu código
void excluir(int cod)
{
  Lista lista;
  lista.inicio = NULL;
  lerLista(&lista);
  deletar(&lista, cod);
  salvaLista(&lista);
}

// Função responsável por editar um remédio em pharma.b, através do seu código
void editar(int cod)
{
  Lista lista;
  lista.inicio = NULL;
  lerLista(&lista);
  editarLista(&lista, cod);
  salvaLista(&lista);
}

void retirarDoEstoqueComLista(Lista *lista, int cod, int quant)
{
  No *pi;
  for (pi = lista->inicio; pi != NULL && pi->dado.codigo != cod; pi = pi->prox)
    ;
  if (pi == NULL)
  {
    printf("Remedio nao encontrado\n");
  }
  else
  {
    pi->dado.estoque = pi->dado.estoque - quant;
  }
}

// Função que faz o carrinho de compras e simula uma compra de remedios, é fornecido pelo cliente o código e a quantidade do remédio
float carrinhoDeCompras(int cod, int quant)
{
  // Retirando remedios do estoque
  Lista lista;
  lista.inicio = NULL;
  lerLista(&lista);
  retirarDoEstoqueComLista(&lista, cod, quant);
  salvaLista(&lista);
  // Parte responsável por retornar o preço dos remedios que serão comprados
  FILE *file = fopen("pharma.b", "rb");
  Remedio a;
  int entrou = 0;
  while (fread(&a, sizeof(Remedio), 1, file))
  {
    if (a.codigo == cod)
    {
      printf("\nNome: %s\n", a.nome);
      printf("- Codigo: %d\n", a.codigo);
      printf("- Preco: %.2f\n", a.preco);
      printf("- Quantidade em estoque: %d\n", a.estoque + quant); // Somei de volta a quantidade do estoque pois antes de finalizar a comprar eu já retirei do pharma.b
      entrou = 1;
      return a.preco * quant;
    }
  }
  if (entrou == 0)
  {
    printf("Codigo de remedio incorreto\n");
  }
  fclose(file);

  return 0;
}

// Função que busca os remédios que estão abaixo de um valor X de dinheiro fornecido pelo cliente
void remediosBaratos(float x)
{
  FILE *file = fopen("pharma.b", "rb");
  Remedio a;
  int entrou = 0;
  while (fread(&a, sizeof(Remedio), 1, file))
  {
    if (a.preco <= x)
    {
      printf("\nNome: %s\n", a.nome);
      printf("- Codigo: %d\n", a.codigo);
      printf("- Preco: %.2f\n", a.preco);
      printf("- Quantidade em estoque: %d\n", a.estoque);
      entrou = 1;
    }
  }
  if (entrou == 0)
  {
    printf("Nao ha remedio com um preco menor ou igual ao do que o informado\n");
  }
  fclose(file);
}
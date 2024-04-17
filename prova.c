#include <stdio.h>
#include "remedio.h"
#include "login.h"

// Esse será o menu e opções do modo admin
void menuAdmin()
{
  printf("\nBem vindo ao modo admin!\n");
  printf("\nEscolha uma opcao:\n");
  printf("1 - Cadastar remedio\n");
  printf("2 - Listar remedios\n");
  printf("3 - Buscar remedio\n");
  printf("4 - Quantidade de remedios\n");
  printf("5 - Excluir um remedio\n");
  printf("6 - Editar um remedio\n");
  printf("7 - Remedios com o estoque acabando\n");
  printf("8 - Cadastrar promocao\n");
  printf("9 - Ordenar Remedios por seu codigo\n");
  printf("0 - Sair\n");
  printf("===================\n");
}

// Esse será o menu e opções do modo client
void menuClient()
{
  printf("\nSeja bem-vindo a nossa farmacia!\n");
  printf("\nEscolha uma opcao:\n");
  printf("1 - Comprar remedios\n");
  printf("2 - Listar remedios\n");
  printf("3 - Buscar remedio\n");
  printf("4 - Quantidade de remedios\n");
  printf("5 - Remedios que cabem no seu bolso!\n");
  printf("6 - Buscar remedios em promocao\n");
  printf("0 - Sair\n");
  printf("===================\n");
}

// Função responsável por tratar o modo adm
void admMode()
{
  int op;
  menuAdmin();
  scanf("%d", &op);
  while (op != 0)
  {
    if (op == 1)
    {
      cadastrar();
    }
    else if (op == 2)
    {
      listar();
    }
    else if (op == 3)
    {
      int cod;
      printf("Informe o codigo do produto:\n");
      scanf("%d", &cod);
      buscar(cod);
    }
    else if (op == 4)
    {
      int n = tamanho();
      printf("Quantidade de remedios na farmacia: %d\n", n);
    }
    else if (op == 5)
    {
      int cod;
      printf("Informe o codigo do remedio que voce deseja excluir:\n");
      scanf("%d", &cod);
      excluir(cod);
    }
    else if (op == 6)
    {
      int cod;
      printf("Informe o codigo do remedio que voce deseja editar:\n");
      scanf("%d", &cod);
      editar(cod);
    }
    else if (op == 7)
    {
      estoqueAcabando();
    }
    else if (op == 8)
    {
      cadastrarPromocao();
    }
    else if (op == 9)
    {
      ordenarLista();
    }
    menuAdmin();
    scanf("%d", &op);
  }
}

// Função responsável por tratar o modo cliente
void clientMode()
{
  int op;
  menuClient();
  scanf("%d", &op);
  while (op != 0)
  {
    if (op == 1)
    {
      int qnt;
      printf("Quantos itens voce deseja comprar?\n");
      scanf("%d", &qnt);
      float cart = 0;
      for (int i = 0; i < qnt; i++)
      {
        int cod, qnt;
        printf("Informe o codigo do remedio: ");
        scanf("%d", &cod);
        printf("Informe a quantidade: ");
        scanf("%d", &qnt);
        cart += carrinhoDeCompras(cod, qnt);
      }
      printf("Total da compra foi: %.2f\n", cart);
    }
    else if (op == 2)
    {
      listar();
    }
    else if (op == 3)
    {
      int cod;
      printf("Informe o codigo do produto:\n");
      scanf("%d", &cod);
      buscar(cod);
    }
    else if (op == 4)
    {
      int n = tamanho();
      printf("Quantidade de remedios na farmacia: %d\n", n);
    }
    else if (op == 5)
    {
      float x;
      printf("Informe o quanto voce esta disposto a pagar e descubra os remedios que cabem no seu bolso: ");
      scanf("%f", &x);
      remediosBaratos(x);
    }
    else if (op == 6)
    {
      buscarPromocao();
    }

    menuClient();
    scanf("%d", &op);
  }
}

// Função que exibi a mensagem de boas vindas do programa
void mensagemDeBoasVindas()
{
  printf("Bem-vindo a VitalFarMed, onde saude e bem-estar se encontram em cada visita! Aqui, nossa missao e cuidar de voce e de sua familia com dedicacao e expertise. Entre em nossa loja virtual e descubra uma ampla variedade de produtos farmaceuticos de qualidade, aliados a um atendimento personalizado que faz toda a diferenca. Na VitalFarMed, sua saude e nossa prioridade numero um. Juntos, vamos trilhar o caminho para uma vida mais saudavel e feliz. Seja bem-vindo a sua nova casa de saude e bem-estar!\n");
  printf("\nVitalFarMed: Vitalizando sua vida, medicando seu bem-estar!\n");
}

int main()
{
  mensagemDeBoasVindas();
  int checkout = login();
  if (checkout == 1)
  {
    admMode();
  }
  else
  {
    clientMode();
  }

  return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login.h"

// Partes responsáveis pela verificação do email
#define MAX_EMAIL_LENGTH 80

// Função para verificar se o email já existe no arquivo
int verificarEmailExistente(const char *email)
{
  FILE *arquivo = fopen("emails.txt", "r");
  if (arquivo == NULL)
  {
    return 0; // Arquivo não existe, então email não está cadastrado
  }
  char linha[MAX_EMAIL_LENGTH];
  while (fgets(linha, MAX_EMAIL_LENGTH, arquivo) != NULL)
  {
    // Remover o caractere de nova linha de fgets
    linha[strcspn(linha, "\n")] = 0;
    if (strcmp(linha, email) == 0)
    {
      fclose(arquivo);
      return 1; // Email já cadastrado
    }
  }
  fclose(arquivo);
  return 0; // Email não encontrado no arquivo
}

// Função para verificar a validade do email
int verificarEmail(const char *email)
{
  if (strlen(email) >= MAX_EMAIL_LENGTH)
  {
    return 0; // Email muito longo
  }
  char *posArroba = strchr(email, '@');
  if (posArroba == NULL)
  {
    return 0; // Email não contém @
  }
  if (verificarEmailExistente(email))
  {
    return 0; // Email já cadastrado
  }
  return 1; // Email válido
}

int email()
{
  char email[MAX_EMAIL_LENGTH];
  int valido = 0;

  while (!valido)
  {
    printf("Digite seu email: ");
    fgets(email, MAX_EMAIL_LENGTH, stdin);
    // Remover o caractere de nova linha de fgets
    email[strcspn(email, "\n")] = 0;

    if (verificarEmail(email))
    {
      valido = 1;
    }
    else
    {
      printf("Email invalido ou ja cadastrado. Por favor, tente novamente.\n");
    }
  }

  // Agora que temos um email válido, vamos adicioná-lo ao arquivo
  FILE *arquivo = fopen("emails.txt", "a");
  if (arquivo == NULL)
  {
    printf("Erro ao abrir o arquivo para escrita.\n");
    return 1;
  }
  fprintf(arquivo, "%s\n", email);
  fclose(arquivo);

  printf("Email cadastrado com sucesso!\n");

  return 0;
}

// Partes responsáveis pelo login nos dois modos
struct Login
{
  char email[81];
  int id;
  int senha;
};

int login()
{
  printf("\n---------------------\n");
  printf("INFORMES PARA REUDISMAM\n");
  printf("As funcoes estao divididas em dois modos: Admin Mode e Client Mode, cada uma com suas funcoes especificas\n");
  printf("Credenciais para entrar nos modos:\n");
  printf("- Email valido e ainda nao cadastrado\n");
  printf("- Para entrar no Adm Mode e Id = 1 e Senha = 11\n");
  printf("- Para entrar no Client Mode e Id = 2 e Senha = 22\n");
  printf("---------------------\n");
  Login user;
  int verificado = email();

  while (verificado == 0)
  {
    printf("Informe o id: ");
    scanf("%d", &user.id);
    printf("Informe a senha: ");
    scanf("%d", &user.senha);

    if (user.id == 1 && user.senha == 11)
    {
      verificado = 1;
      return 1; // Igual a entrar no modo admin
    }
    else if (user.id == 2 && user.senha == 22)
    {
      verificado = 1;
      return 2; // Igual a entrar no modo cliente/user
    }
    else
    {
      printf("Id ou senha incorretos, tente novamente!\n");
    }
  }

  return 0;
}
#ifndef H_REMEDIO
#define H_REMEDIO

typedef struct Remedio Remedio;
typedef struct lista Lista;
typedef struct no No;

void adicionaFim(Lista *lista, Remedio e);
void editarLista(Lista *lista, int cod);
void deletar(Lista *lista, int cod);
void lerLista(Lista *lista);
void salvaLista(Lista *lista);
void ordenarLista();
void cadastrar();
void cadastrarPromocao();
void buscar(int cod);
void buscarPromocao();
void listar();
int tamanho();
void estoqueAcabando();
void excluir(int cod);
void editar(int cod);
void retirarDoEstoqueComLista(Lista *lista, int cod, int quant);
float carrinhoDeCompras(int cod, int quant);
void remediosBaratos(float x);

#endif
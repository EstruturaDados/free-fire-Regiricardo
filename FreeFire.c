
#include <stdio.h>   // Biblioteca padrão para entrada e saída (printf, scanf, etc.)
#include <string.h>  // Biblioteca usada para manipulação de strings (strcmp, strcspn, etc.)

#define MAX_ITENS 10    // Define o número máximo de itens que a mochila pode ter
#define TAM_NOME 30     // Define o tamanho máximo do nome de um item
#define TAM_TIPO 20     // Define o tamanho máximo do tipo de um item


// Estrutura que representa um item do inventário
typedef struct {
    char nome[TAM_NOME];     // nome do item (fuzil ,Kit Médico, etc)
    char tipo[TAM_TIPO];     // tipo do item (arma, munição, cura, ferramenta, etc)
    int quantidade;          // quantidade do item
} Item;

// Protótipos das funções
void inserirItem(Item mochila[], int *qtd);
void removerItem(Item mochila[], int *qtd);
void listarItens(Item mochila[], int qtd);

int main() {
    Item mochila[MAX_ITENS];   // Cria um vetor de itens (a mochila)
    int qtd = 0;               // Contador de quantos itens há na mochila
    int opcao;                 // Variável para armazenar a opção do menu


    do { //menu principal
        printf("\n=================================================");
        printf("\n=== MOCHILA DE SOBREVIVÊNCIA - CÓDIGO DA ILHA ===");
        printf("\n=================================================\n");
        printf("Itens na mochila: %d de %d disponíveis.\n", qtd, MAX_ITENS);
        printf("-----------------------------\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

                // Executa a ação correspondente à opção escolhida
        switch(opcao) {
            case 1:  // Adicionar novo item
                inserirItem(mochila, &qtd);
                listarItens(mochila, qtd);
                break;

            case 2:  // Remover item existente
                removerItem(mochila, &qtd);
                listarItens(mochila, qtd);
                break;

            case 3:  // Listar todos os itens
                listarItens(mochila, qtd);
                break;

            case 0:  // Sair do programa
                printf("Saindo do sistema...\n");
                break;

            default: // Caso o usuário digite uma opção inválida
                printf("Opção inválida. Tente novamente.\n");
        }

    } while(opcao != 0);  // Repete o menu até o usuário escolher “0”

    return 0;  // Finaliza o programa
}

// Função para cadastrar um novo item
void inserirItem(Item mochila[], int *qtd) {
    if (*qtd >= MAX_ITENS) {
        printf("Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;
    printf("\n--- Adicionar Novo Item ---\n");
    printf("Nome do item: ");
    while (getchar() != '\n'); // limpar buffer
    fgets(novo.nome, TAM_NOME, stdin); // Lê o nome do item
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; // Remove o \n do final da string

    printf("Tipo do item (arma, munição, cura, etc): ");
    fgets(novo.tipo, TAM_TIPO, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[*qtd] = novo;
    (*qtd)++;

    // Mostra os detalhes do item cadastrado
    printf("\n Item adicionado com sucesso!\n");
    printf("Nome: %s\n", novo.nome);
    printf("Tipo: %s\n", novo.tipo);
    printf("Quantidade: %d\n", novo.quantidade);
 
}
// Função para remover um item pelo nome
void removerItem(Item mochila[], int *qtd) {
    if (*qtd == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    char nomeRemover[TAM_NOME];
    printf("\nDigite o nome do item a remover: ");
    while (getchar() != '\n'); // Limpa o buffer de entrada
    fgets(nomeRemover, TAM_NOME, stdin); // Lê o nome do item a remover
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0'; // Remove o \n final


    int encontrado = 0;  // Flag para saber se o item foi encontrado
    for (int i = 0; i < *qtd; i++) { // Percorre todos os itens da mochila
        if (strcmp(mochila[i].nome, nomeRemover) == 0) { // Compara nomes
            // Se encontrou, desloca os itens seguintes uma posição para trás
            for (int j = i; j < *qtd - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*qtd)--;           // Diminui a quantidade total
            encontrado = 1;     // Marca que o item foi encontrado
            printf("Item '%s' removido com sucesso!\n", nomeRemover);
            break;              // Sai do loop
        }
    }

    if (!encontrado) { // Caso não tenha achado o item
        printf("Item '%s' não encontrado na mochila.\n", nomeRemover);
    }
}


// Função para listar todos os itens da mochila
void listarItens(Item mochila[], int qtd) {
    printf("\n--- Itens na Mochila ---\n");
    if (qtd == 0) {
        printf("A mochila está vazia.\n");
        return;
    }

    printf("\n============================================================\n");
    printf("Nome                     | Tipo                 | Quantidade\n");
    printf("============================================================\n");

// Percorre e imprime cada item formatado

    for (int i = 0; i < qtd; i++) {
        
        printf("%-24s | %-20s | %-10d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);

        
    }
}

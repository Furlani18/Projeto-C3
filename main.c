#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUNOS 100        // Número máximo de alunos
#define MAX_NOME 50           // Tamanho máximo do nome do aluno
#define MAX_NOTAS 3           // Número máximo de notas que um aluno pode ter

// Struct para armazenar os dados dos alunos
typedef struct {
    char nome[MAX_NOME];    // Nome do aluno
    int matricula;          // Matrícula do aluno
    float notas[MAX_NOTAS]; // Notas do aluno
    float media;            // Média das notas
    char status[10];        // Status de aprovação ou reprovação
} Aluno;

// Função para calcular a média das notas de um aluno
float calcular_media(float notas[], int qtd_notas) {
    float soma = 0.0;
    for (int i = 0; i < qtd_notas; i++) {
        soma += notas[i]; // Soma todas as notas
    }
    return soma / qtd_notas; // Retorna a média
}

// Função para determinar o status de aprovação ou reprovação
void determinar_status(Aluno *aluno) {
    if (aluno->media >= 5.0) {
        strcpy(aluno->status, "Aprovado"); // Se a média for maior ou igual a 7.0
    } else {
        strcpy(aluno->status, "Reprovado"); // Se a média for menor que 7.0
    }
}

// Função para cadastrar um novo aluno
void cadastrar_aluno(Aluno *alunos, int *qtd_alunos) {
    if (*qtd_alunos >= MAX_ALUNOS) {
        printf("Limite de alunos atingido!\n");
        return; // Retorna se o limite de alunos for atingido
    }
    
    Aluno novo_aluno;
    
    printf("Nome do aluno: ");
    getchar(); // Limpar o buffer do teclado
    fgets(novo_aluno.nome, MAX_NOME, stdin); // Lê o nome do aluno
    novo_aluno.nome[strcspn(novo_aluno.nome, "\n")] = '\0'; // Remove o \n da string
    
    printf("Matricula: ");
    scanf("%d", &novo_aluno.matricula); // Lê a matrícula do aluno
    
    printf("Insira as notas do aluno:\n");
    for (int i = 0; i < MAX_NOTAS; i++) {
        printf("Nota %d: ", i + 1);
        scanf("%f", &novo_aluno.notas[i]); // Lê as notas do aluno
    }
    
    novo_aluno.media = calcular_media(novo_aluno.notas, MAX_NOTAS); // Calcula a média
    determinar_status(&novo_aluno); // Determina o status do aluno
    
    alunos[*qtd_alunos] = novo_aluno; // Adiciona o aluno ao array
    (*qtd_alunos)++; // Incrementa a quantidade de alunos
    
    printf("Aluno cadastrado com sucesso!\n");
}

// Função para exibir os dados de todos os alunos
void exibir_alunos(Aluno *alunos, int qtd_alunos) {
    if (qtd_alunos == 0) {
        printf("Nenhum aluno cadastrado!\n");
        return; // Retorna se não houver alunos cadastrados
    }
    
    for (int i = 0; i < qtd_alunos; i++) {
        printf("Nome: %s\n", alunos[i].nome);
        printf("Matricula: %d\n", alunos[i].matricula);
        printf("Media: %.2f\n", alunos[i].media);
        printf("Status: %s\n", alunos[i].status);
        printf("----------------------\n");
    }
}

// Função para salvar os dados dos alunos em arquivos binários e texto
void salvar_dados(Aluno *alunos, int qtd_alunos) {
    FILE *arquivo_bin = fopen("alunos.dat", "wb");
    FILE *arquivo_txt = fopen("status.txt", "w");
    
    if (arquivo_bin == NULL || arquivo_txt == NULL) {
        printf("Erro ao abrir arquivos!\n");
        return; // Retorna se não conseguir abrir os arquivos
    }
    
    fwrite(alunos, sizeof(Aluno), qtd_alunos, arquivo_bin); // Salva os dados em formato binário
    
    for (int i = 0; i < qtd_alunos; i++) {
        // Salva os dados dos alunos em formato texto
        fprintf(arquivo_txt, "Nome: %s\nMatricula: %d\nMedia: %.2f\nStatus: %s\n\n", 
                alunos[i].nome, alunos[i].matricula, alunos[i].media, alunos[i].status);
    }
    
    fclose(arquivo_bin); // Fecha o arquivo binário
    fclose(arquivo_txt); // Fecha o arquivo de texto
    
    printf("Dados salvos com sucesso!\n");
}

// Função para carregar os dados dos alunos de um arquivo binário
int carregar_dados(Aluno *alunos) {
    FILE *arquivo_bin = fopen("alunos.dat", "rb");
    if (arquivo_bin == NULL) {
        printf("Arquivo de alunos nao encontrado!\n");
        return 0; // Retorna 0 se o arquivo não for encontrado
    }
    
    int qtd_alunos = fread(alunos, sizeof(Aluno), MAX_ALUNOS, arquivo_bin); // Lê os dados dos alunos
    fclose(arquivo_bin); // Fecha o arquivo
    
    return qtd_alunos; // Retorna a quantidade de alunos carregados
}

// Função principal
int main() {
    Aluno alunos[MAX_ALUNOS]; // Array para armazenar os alunos
    int qtd_alunos = 0, opcao; // Variável para a quantidade de alunos e a opção do menu
    
    // Carrega dados de alunos ao iniciar o programa
    qtd_alunos = carregar_dados(alunos);
    
    do {
        // Exibe o menu de opções
        printf("1. Cadastrar Aluno\n");
        printf("2. Exibir Alunos\n");
        printf("3. Salvar Dados\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                cadastrar_aluno(alunos, &qtd_alunos); // Chama a função para cadastrar aluno
                break;
            case 2:
                exibir_alunos(alunos, qtd_alunos); // Chama a função para exibir alunos
                break;
            case 3:
                salvar_dados(alunos, qtd_alunos); // Chama a função para salvar dados
                break;
            case 4:
                printf("Saindo...\n"); // Mensagem de saída
                break;
            default:
                printf("Opcao invalida!\n"); // Mensagem de opção inválida
        }
    } while (opcao != 4); // Continua o loop até que a opção 4 seja escolhida
    
    return 0; // Finaliza o programa
}
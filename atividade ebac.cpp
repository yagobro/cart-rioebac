#include <stdlib.h> // Biblioteca para alocação de memória
#include <stdio.h>  // Biblioteca para operações de entrada e saída
#include <locale.h> // Biblioteca para configurações regionais
#include <string.h> // Biblioteca responsável para cuidar das strings

// Função de registro, reponsável por cadastrar os usuários do sistema
int registro() {
	// inicio de criação das variáveis/string
    char arquivo[40];
    char cpf[40];
    char nome[40];
    char sobrenome[40];
    char cargo[40];

    printf("Digite o CPF a ser cadastrado: ");
    scanf("%s", cpf); // "%s" refere-se a strings

    strcpy(arquivo, cpf); // Responsável por copiar o valor das strings

    FILE *file; // Cria o arquivo no banco de dados
    file = fopen(arquivo, "w"); // Cria o arquivo
    if (file == NULL) {
        printf("Erro ao criar o arquivo.\n");
        return 1;
    }
    fprintf(file, "%s", cpf); // Salva o valor da variável
    fclose(file); // Fecha o arquivo

    file = fopen(arquivo, "a"); // Abre para adicionar dados
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    fprintf(file, ",");
    fclose(file);

    printf("Digite o nome a ser cadastrado: ");
    scanf("%s", nome);

    file = fopen(arquivo, "a");
    fprintf(file, "%s", nome);    
    fclose(file);

    file = fopen(arquivo, "a");
    fprintf(file, ",");
    fclose(file);

    printf("Digite o sobrenome a ser cadastrado: ");
    scanf("%s", sobrenome);

    file = fopen(arquivo, "a");
    fprintf(file, "%s", sobrenome);
    fclose(file);

    file = fopen(arquivo, "a");
    fprintf(file, ",");
    fclose(file);

    printf("Digite o cargo a ser cadastrado: ");
    scanf("%s", cargo);

    file = fopen(arquivo, "a");
    fprintf(file, "%s", cargo);
    fclose(file);

    system("pause"); // Pausa para o usuário ver a mensagem
    return 0;
}

// Função de consulta
int consulta() {
	 setlocale(LC_ALL, "portuguese");
    char cpf [40];
    char conteudo [200];
    
    printf ("digite o cpf a ser consultado");
    scanf ("%s",cpf);
    
    FILE *file;
    file = fopen (cpf,"r");
    
    if (file == NULL) 
{
	printf ("não foi possível abrir o arquivo!./n");
}

while (fgets(conteudo, 200, file) != NULL)

{
	printf ("\nEssas são as informações do usuário:");
	printf ("%s",conteudo);
	printf ("\n\\n");
}
system ("pause");
}

// Função de deletação 
 
int deletar() {
    char cpf[40];
    
    printf("Digite o CPF a ser deletado: ");
    scanf("%s", cpf);
    
    FILE *file, *tempFile;
    char linha[256];
    int encontrado = 0;

    // Abre o arquivo original para leitura
    file = fopen(cpf, "r");
    if (file == NULL) {
        printf("O usuário não se encontra no sistema.\n");
        system("pause");
        return 1; // Arquivo não encontrado, o usuário não existe
    }

    // Cria um arquivo temporário para armazenar os dados sem o CPF a ser deletado
    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Erro ao criar o arquivo temporário.\n");
        fclose(file);
        system("pause");
        return 1;
    }

    // Lê o arquivo original linha por linha e copia para o arquivo temporário, exceto a linha com o CPF
    while (fgets(linha, sizeof(linha), file)) {
        if (strstr(linha, cpf) == NULL) { // Se o CPF não está na linha, escreve no arquivo temporário
            fputs(linha, tempFile);
        } else {
            encontrado = 1; // Caso o CPF seja encontrado, marca como encontrado
        }
    }

    fclose(file);
    fclose(tempFile);

    // Se o CPF foi encontrado, substitui o arquivo original pelo arquivo temporário
    if (encontrado) {
        remove(cpf); // Deleta o arquivo original com os dados antigos
        rename("temp.txt", cpf); // Renomeia o arquivo temporário para o nome do arquivo original
        printf("Usuário com CPF %s deletado com sucesso.\n", cpf);
    } else {
        printf("O CPF não foi encontrado no sistema.\n");
        remove("temp.txt"); // Deleta o arquivo temporário caso o CPF não tenha sido encontrado
    }

    system("pause");
    return 0;
}



int main() {
    int opcao = 0; // Definindo as variáveis
    int laco = 1; 

    // Abertura do menu até que o usuário escolha sair
    while (1) { // Usando um loop infinito para manter o menu ativo até que o usuário escolha uma opção válida
        system("cls"); 
        
        setlocale(LC_ALL, "portuguese"); // Definindo a linguagem
        
        // Exibe o menu
        printf("### Cartório da EBAC ###\n\n");
        printf("Escolha a opção desejada no menu:\n\n");
        printf("\t1 - Registrar nomes\n");
        printf("\t2 - Consultar nomes\n");
        printf("\t3 - Deletar nomes\n");
        printf("\t4 - Sair\n");  // Adicionando a opção para sair
        printf("Opção: "); // Fim do menu
        
        // Lê a opção escolhida
        scanf("%d", &opcao); 
        
        system("cls"); // Limpa a tela para a próxima interação
        
        // Processa a opção escolhida
        switch(opcao) {
            case 1:
                registro();
                break;
            
            case 2:
                consulta(); // Função para consulta
                break;
            
            case 3:
                deletar(); // Função para deletar
                break;
            
            case 4:
                printf("Saindo do sistema...\n");
                exit(0); // Encerra o programa
                break;
            
            default:
                printf("Essa opção não está disponível! Tente novamente.\n");
                system("pause"); // Pausa para o usuário ver a mensagem
                break;
        }
    }

    return 0;
}


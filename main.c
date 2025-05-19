#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TF 255
// #define TFP 255
// #define TFC 255
// #define TFS 255

int main(void) {
    /*
        Formula int for float -> cents / 100.0
        Formula float for int -> (int)(real * 100 + 0.5)

        Example:
            float real = 19.99;
            int conversionNext = (int)(real * 100 + 0.5); 
            float conversionBack = conversionNext / 100.0; -> (12.3)
            (Result: 19.99)        
    */

    // Position at a given physical size
    int TLV=0, TLP=0, TLC=0, TLS=0;

    // Product
    char vCod[TF][50], vProdServ[TF][50];
    int vQtde[TF], vPreco[TF];

    // Client
    char vRG[TF][12], vCliente[TF][30];

    // Sellings
    char vRGV[TF][12], vCodV[TF][50];
    int vQtdeV[TF], vPrecoV[TF];

    // Controllers
    // Program
    int program_exit = 1, program_execute_action;
    char program_confirm_exit;

    // Interface
    do {
        printf("\n"
        "1: Cadastro\n"
        "2: Excluir\n"
        "3: Venda\n"
        "4: Relatórios\n"
        "5: Finalizar\n"
        "> ");

        scanf(" %d", &program_exit);

        switch(program_exit) {
            case 1:
                do {
                    printf("\n"
                    "1: Produtos/Serviços\n"
                    "2: Clientes\n"
                    "3: Retornar\n"
                    "> ");
                    scanf(" %d", &program_execute_action);
                    
                    switch(program_execute_action) {
                        case 1: 
                            // Code Products and Services (Otávio && Breno Henrique)
                            // printf("\n Produtos e Serviços selecionado");
                            // char vcod_temp[50];

                            // do {
                            //     printf("Digite o produto ou serviço: ");
                            //     while(getchar() != '\n');
                            //     gets(vcod_temp);

                            //     printf("");





                            // } while();

                            break;
                        case 2:
                            // Code Client (Rafael && Matheus Bispo)
                            // printf("\n Cliente selecionado");

                            char continue_choosen;
                            char rg_temp[12];

                            do {
                                int repeat;

                                do {
                                    repeat = 0;
                                    int i = 0;

                                    while (getchar() != '\n'); 

                                    printf("Digite o RG: ");
                                    fflush(stdin);
                                    gets(rg_temp);

                                    if(strlen(rg_temp) != 11) {
                                        printf("RG com tamanho inválido! \n");
                                        printf("Pressione enter para digitar novamente... \n");
                                        repeat = 1;
                                    }

                                    while(i < TLC && strlen(rg_temp) == 12 && repeat == 0) {
                                        if (strcmp(rg_temp, vRG[i]) == 0) {
                                            printf("RG já registrado! \n");
                                            printf("Pressione enter para digitar outro... \n");
                                            repeat = 1; 
                                        }
                                        i++;
                                    }

                                } while (repeat == 1);
                                    
                                strcpy(vRG[TLC], rg_temp);

                                printf("Digite o nome do cliente: ");
                                gets(vCliente[TLC]);

                                TLC++;

                                printf("\nQuer adicionar mais um cliente? (s/n)\n> ");
                                scanf(" %c", &continue_choosen);
                         

                                } while (tolower(continue_choosen) == 's');
                            break;
                    }

                    if(program_execute_action > 3 || program_execute_action <= 0) printf("\nOpção inválida! Tente novamente.\n"); 
                    printf("\n");
                } while(program_execute_action != 3);
                break;
            case 2: 
                // Code Delete (Breno Passarela && Kaua)
                printf("\n Exclusão selecionado \n");

                do {
                    printf("\n"
                    "1: Produtos/Serviços\n"
                    "2: Clientes\n"
                    "3: Vendas\n"
                    "4: Retornar\n"
                    "> ");
                    scanf(" %d", &program_execute_action);

                    switch(program_execute_action) {
                        case 1:
                            break;
                        case 2:
                            char continue_choosen;
                            char rg_temp[12];
                            
                            do {
                                int repeat = 0;

                                do {
                                    repeat = 0;
                                    int i = 0;
                                    int j = 0;

                                    while (getchar() != '\n');

                                    printf("Digite o RG do cliente que deseja excluir: ");
                                    fflush(stdin);
                                    gets(rg_temp);

                                    while(i < TLV && repeat == 0) {
                                        if (strcmp(rg_temp, vRGV[i]) == 0) {
                                            printf("RG com vendas pendentes! \n");
                                            printf("Pressione enter para digitar outro... \n");
                                            repeat = 1;
                                        } else {
                                            i++;
                                        }
                                    }

                                    for(i = 0; i < TLC && strcmp(rg_temp, vRG[i]) != 0; i++);

                                    if(i == TLC) {
                                        printf("RG não existe! \n");
                                        printf("Pressione enter para digitar outro... \n");
                                        repeat = 1;
                                    } else {
                                        for(j = i; j < TLC - 1; j++) {
                                            strcpy(vRG[j], vRG[j + 1]);
                                            strcpy(vCliente[j], vCliente[j + 1]);
                                        }
                                        TLC--;
                                        
                                        printf("Cliente com RG %s excluído com sucesso.\n", rg_temp);
                                    }
                                } while (repeat == 1);

                                printf("\nQuer excluir mais um cliente? (s/n)\n> ");
                                scanf(" %c", &continue_choosen);
                            } while (tolower(continue_choosen) == 's');
                        break;
                    }

                    if(program_execute_action > 3 || program_execute_action <= 0) printf("\nOpção inválida! Tente novamente.\n"); 
                    printf("\n");
                } while(program_execute_action != 3);
                break;
            case 3:
                // Code Sell (Lucas && Gui Leal)
                printf("\n Venda selecionado \n");
                break;
            case 4: 
                // Code Report (Otávio && Breno Passarela && Breno Henrique)
                printf("\n Relatório selecionado \n");
                break;
            case 5: 
                // Confirm program exit
                int conditional;
                do {
                    printf("Tem certeza ? (S/n) \n");
                    scanf(" %c", &program_confirm_exit);
                    // Condition to be checked, it kind of returns 0 for false and 1 for true
                    conditional = tolower(program_confirm_exit) != 'n' && tolower(program_confirm_exit) != 's';
                    if(conditional) printf("Resposta inválida! Tente novamente...");
                } while(conditional);

                if(tolower(program_confirm_exit) == 's') {
                    program_exit = 0;
                } else {
                    program_exit = -1;
                }

                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
                break;
        }
    } while(program_exit!=0);

    return 0;
}
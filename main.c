#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TF 255
// #define TFP 255
// #define TFC 255
// #define TFS 255

int main(void)
{
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
    int TLV = 0, TLP = 0, TLC = 0, TLS = 0;

    // Product
    char vCod[TF][50], vProdServ[TF][50];
    int vQtde[TF], vPreco[TF];

    // Client
    char vCliente[TF][30],nomeCliente[30];
    int TLC = 0, rg = 1, op, achou, i, vRG[TF];
    // Services
    char vRGV[TF][11], vCodV[TF][50];
    int vQtdeV[TF], vPrecoV[TF];

    // Controllers
    // Program
    int program_exit = 1, program_execute_action;
    char program_confirm_exit;

    // Interface
    do
    {
        printf("\n"
               "1: Cadastro\n"
               "2: Excluir\n"
               "3: Venda\n"
               "4: Relatórios\n"
               "5: Finalizar\n\n"
               "> ");

        scanf(" %d", &program_exit);

        switch (program_exit)
        {
        case 1:
            do
            {
                printf("\n"
                       "1: Produtos/Serviços\n"
                       "2: Clientes\n"
                       "3: Retornar\n"
                       "> ");
                scanf(" %d", &program_execute_action);

                if (program_execute_action == 3)
                    break;

                switch (program_execute_action)
                {
                case 1:
                    // Code Products and Services (Otávio && Breno Henrique)
                    printf("\n Produtos e Serviços selecionado");
                    break;
                case 2:
                    // Code Client (Rafael && Matheus Bispo)
                    do
                    {
                        printf("\n------------------Menu------------------\n");
                        printf("1-Inserir\n");
                        printf("2-Excluir\n");
                        printf("3-Consultar\n");
                        printf("4-Sair\n");

                        printf("Selecione a opcao desejada: ");
                        scanf("%d", &op);

                        switch (op)
                        {
                        case 1:
                            if (TLC < TF)
                            {

                                while (rg > 0 && TLC < TF)
                                {
                                    printf("\nDigite o RG do cliente ou 0 para parar: ");
                                    scanf("%d", &rg);

                                    if (rg <= 0)
                                    {
                                        rg = 0;
                                    }
                                    else
                                    {
                                        achou = 0;
                                        for (i = 0; i < TLC; i++)
                                        {
                                            if (vRG[i] == rg)
                                            {
                                                printf("RG ja cadastrado!\n");
                                                achou = 1;
                                            }
                                        }

                                        if (achou == 0)
                                        {
                                            printf("Nome: ");
                                            fflush(stdin);
                                            gets(nomeCliente);

                                            vRG[TLC] = rg;
                                            strcpy(vCliente[TLC], nomeCliente);
                                            TLC++;
                                            printf("Cadastrado com sucesso!\n");
                                        }
                                    }
                                }
                            }
                            else
                                printf("Sistema cheio!!!!!!!!!!");
                            break;

                        case 2:
                            printf("Funcao de exclusao ainda nao implementada.\n");
                            break;

                        case 3:
                            printf("Funcao de consulta ainda nao implementada.\n");
                            break;

                        case 4:
                            printf("Saindo do programa...\n");
                            break;

                        default:
                            printf("Opcao selecionada incorreta.\n");
                            break;
                        }

                    } while (op != 4);
                    break;
                default:
                    printf("\nOpção inválida! Tente novamente.\n");
                    break;
                }
                printf("\n");
            } while (program_execute_action != 3);
            break;
        case 2:
            // Code Delete (Breno Passarela && Kaua)
            printf("\n Exclusão selecionado \n");
            break;
        case 3:
            // Code Sell (Lucas && Gui Leal)
            printf("\n Venda selecionado \n");
            break;
        case 4:
            // Code Report (Otávio && Breno Passarela)
            printf("\n Relatório selecionado \n");
            break;
        case 5:
            // Confirm program exit
            int conditional;
            do
            {
                printf("Tem certeza ? (S/n) \n");
                scanf(" %c", &program_confirm_exit);
                // Condition to be checked, it kind of returns 0 for false and 1 for true
                conditional = tolower(program_confirm_exit) != 'n' && tolower(program_confirm_exit) != 's';
                if (conditional)
                    printf("Resposta inválida! Tente novamente...");
            } while (conditional);

            if (tolower(program_confirm_exit) == 's')
            {
                program_exit = 0;
            }
            else
            {
                program_exit = -1;
            }

            break;
        default:
            printf("\nOpção inválida! Tente novamente.\n");
            break;
        }
    } while (program_exit != 0);

    return 0;
}
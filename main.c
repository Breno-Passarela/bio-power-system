#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define TF 255

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
    int TLV = 0, TLP = 0, TLC = 0;

    // Product
    char vCod[TF][50], vProdServ[TF][50];
    int vQtde[TF], vPreco[TF];

    // Client
    char vRG[TF][10], vCliente[TF][30];

    // Selling
    char vRGV[TF][10], vCodV[TF][50], vProdServV[TF][50];
    int vQtdeV[TF], vPrecoV[TF];

    // Controllers
    // Program
    int program_exit = 1, program_execute_action;
    char program_confirm_exit, continue_choosen = 'n';

    // Interface
    do
    {
        printf("\n"
               "1: Cadastro\n"
               "2: Excluir\n"
               "3: Venda\n"
               "4: Relatorios\n"
               "5: Finalizar\n"
               "> ");

        scanf(" %d", &program_exit);

        switch (program_exit)
        {
        case 1:
            do
            {

                printf("\nCadastro selecionado: \n");

                printf("\n"
                       "1: Produtos/Servicos\n"
                       "2: Clientes\n"
                       "3: Retornar\n"
                       "> ");
                scanf(" %d", &program_execute_action);

                switch (program_execute_action)
                {
                case 1:
                    // Code Products and Services (Otávio && Breno Henrique)
                    printf("\nProdutos e Servicos selecionado \n");
                    char vcod_temp[50];
                    char vprodserv_temp[50];
                    float vpreco_temp;
                    int repeat;

                    do
                    {
                        repeat = 0;
                        while (getchar() != '\n')
                            ;

                        do
                        {
                            repeat = 0;
                            printf("\nDigite o codigo do produto ou servico: ");
                            gets(vcod_temp);

                            int i = 0;
                            while (i < TLP)
                            {
                                if (strcmp(vcod_temp, vCod[i]) == 0)
                                {
                                    printf("Codigo %s ja cadastrado! \n", vcod_temp);
                                    repeat = 1;
                                }
                                i++;
                            }
                        } while (repeat == 1);

                        strcpy(vCod[TLP], vcod_temp);

                        do
                        {
                            repeat = 0;
                            printf("Digite o nome produto ou servico: ");
                            gets(vprodserv_temp);

                            int i = 0;
                            while (i < TLP)
                            {
                                if (strcmp(vprodserv_temp, vProdServ[i]) == 0)
                                {
                                    printf("Produto %s ja cadastrado! \n", vprodserv_temp);
                                    repeat = 1;
                                }
                                i++;
                            }

                        } while (repeat == 1);

                        strcpy(vProdServ[TLP], vprodserv_temp);

                        printf("Quantidade do produto: ");
                        scanf(" %d", &vQtde[TLP]);

                        printf("Digite o preco: ");
                        scanf(" %f", &vpreco_temp);

                        vPreco[TLP] = (int)(vpreco_temp * 100 + 0.5);

                        printf("\n-> %d | Cod. Produto: %s | Produto: %s | Quantidade: %d | Preco Unitario: %d -> %.2f\n", TLP + 1, vCod[TLP], vProdServ[TLP], vQtde[TLP], vPreco[TLP], (float)vPreco[TLP] / 100.0);

                        TLP++;

                        while (getchar() != '\n')
                            ;
                        printf("\nQuer adicionar mais um produto? (S/N)\n> ");
                        scanf(" %c", &continue_choosen);
                    } while (tolower(continue_choosen) == 's');

                    break;
                case 2:
                    // Code Client (Rafael && Matheus Bispo)
                    printf("\nCliente selecionado \n");

                    char rg_temp[10];

                    do
                    {
                        int repeat;

                        do
                        {
                            repeat = 0;
                            int i = 0;

                            while (getchar() != '\n')
                                ;

                            printf("Digite o RG: ");
                            fflush(stdin);
                            gets(rg_temp);

                            if (strlen(rg_temp) != 9)
                            {
                                printf("RG com tamanho invalido! \n");
                                printf("Pressione enter para digitar novamente... \n");
                                repeat = 1;
                            }

                            while (i < TLC && strlen(rg_temp) == 9 && repeat == 0)
                            {
                                if (strcmp(rg_temp, vRG[i]) == 0)
                                {
                                    printf("RG ja registrado! \n");
                                    printf("Pressione enter para digitar outro... \n");
                                    repeat = 1;
                                }
                                i++;
                            }

                        } while (repeat == 1);

                        strcpy(vRG[TLC], rg_temp);

                        printf("Digite o nome do cliente: ");
                        gets(vCliente[TLC]);

                        printf("%d | RG: %s | Nome Cliente: %s", TLC + 1, vRG[TLC], vCliente[TLC]);

                        TLC++;

                        printf("\nQuer adicionar mais um cliente? (S/N)\n> ");
                        scanf(" %c", &continue_choosen);

                    } while (tolower(continue_choosen) == 's');
                    break;
                }

                if (program_execute_action > 3 || program_execute_action <= 0)
                    printf("\nOpcao invalida! Tente novamente.\n");
                printf("\n");
            } while (program_execute_action != 3);
            break;
        case 2:
            // Code Delete (Breno Passarela && Kaua)
            printf("\n Exclusao selecionado \n");

            do
            {
                printf("\n"
                       "1: Produtos/Servicos\n"
                       "2: Clientes\n"
                       "3: Retornar\n"
                       "> ");
                scanf(" %d", &program_execute_action);

                switch (program_execute_action)
                {
                case 1:
                    char vcod_temp[50];

                    do
                    {
                        int repeat = 0;

                        do
                        {
                            int i = 0;
                            int j = 0;

                            while (getchar() != '\n')
                                ;

                            printf("Digite o codigo do produto que deseja excluir: ");
                            fflush(stdin);
                            gets(vcod_temp);

                            while (i < TLV && repeat == 0)
                            {
                                if (strcmp(vcod_temp, vCodV[i]) == 0)
                                {
                                    printf("Produto com vendas pendentes! \n");
                                    printf("Pressione enter para digitar outro... \n");
                                    repeat = 1;
                                }
                                else
                                {
                                    i++;
                                }
                            }

                            for (i = 0; i <= TLP && strcmp(vcod_temp, vCod[TLP]) != 0; i++)
                                ;

                            if (i == TLP)
                            {
                                printf("Produto nao existe! \n");
                                printf("Pressione enter para digitar outro... \n");
                                repeat = 1;
                            }
                            else
                            {
                                for (j = i; j < TLP - 1; j++)
                                {
                                    strcpy(vCod[j], vCod[j + 1]);
                                    strcpy(vProdServ[j], vProdServ[j + 1]);
                                    vQtde[j], vQtde[j + 1];
                                    vPreco[j], vPreco[j + 1];
                                }
                                TLP--;

                                printf("\nProduto com codigo %s excluído com sucesso.\n", vcod_temp);
                            }
                        } while (repeat == 1);

                        printf("\nQuer excluir mais um produto? (S/N)\n> ");
                        scanf(" %c", &continue_choosen);
                    } while (tolower(continue_choosen) == 's');

                    break;
                case 2:
                    char rg_temp[10];

                    do
                    {
                        int repeat = 0;

                        do
                        {
                            int i = 0;
                            int j = 0;

                            while (getchar() != '\n')
                                ;

                            printf("Digite o RG do cliente que deseja excluir: \n");
                            fflush(stdin);
                            gets(rg_temp);

                            while (i < TLV && repeat == 0)
                            {
                                if (strcmp(rg_temp, vRGV[i]) == 0)
                                {
                                    printf("\nRG com vendas pendentes! \n");
                                    printf("\nPressione enter para digitar outro... \n");
                                    repeat = 1;
                                }
                                else
                                {
                                    i++;
                                }
                            }

                            for (i = 0; i <= TLC && strcmp(rg_temp, vRG[i]) != 0; i++)
                                ;

                            if (i == TLC)
                            {
                                printf("RG nao existe! \n");
                                printf("Pressione enter para digitar outro... \n");
                                repeat = 1;
                            }
                            else
                            {
                                for (j = i; j < TLC - 1; j++)
                                {
                                    strcpy(vRG[j], vRG[j + 1]);
                                    strcpy(vCliente[j], vCliente[j + 1]);
                                }
                                TLC--;

                                printf("\nCliente com RG %s excluído com sucesso.\n", rg_temp);
                            }
                        } while (repeat == 1);

                        printf("\nQuer excluir mais um cliente? (S/N)\n> ");
                        scanf(" %c", &continue_choosen);
                    } while (tolower(continue_choosen) == 's');
                    break;
                }

                if (program_execute_action > 3 || program_execute_action <= 0)
                    printf("\nOpcao invalida! Tente novamente.\n");
                printf("\n");
            } while (program_execute_action != 3);
            break;
        case 3:
            char rg_temp[10];
            char vcod_temp[50];
            int qtd_temp;

            if (TLP > 0)
            {
                do
                {
                    int repeat = 0;
                    int client_found = 0;
                    int product_found = 0;
                    int product_index = -1;
                    float product_price = 0.0;

                    printf("\nVenda selecionada\n");
                    
                    do
                    {
                        repeat = 0;

                        printf("\nDigite o RG a cadastrar para a venda:");
                        scanf(" %s", &rg_temp);

                        for (int i = 0; i < TLC; i++)
                        {
                            if (strcmp(vRG[i], rg_temp) == 0)
                            {
                                client_found = 1;
                            }
                        }

                        if (strlen(rg_temp) != 9)
                        {
                            printf("RG com tamanho invalido! \n");
                            printf("Pressione enter para digitar novamente... \n");
                            repeat = 1;
                        }

                        if (!client_found && repeat == 0)
                        {
                            printf("RG nao cadastrado! Nao é possível realizar a venda.\n");
                            repeat = 1;
                        }
                    } while (repeat == 1);

                    strcpy(vRGV[TLV], rg_temp);

                    do
                    {
                        repeat = 0;

                        printf("\nDigite o codigo do produto:");
                        scanf(" %s", &vcod_temp);

                        for (int i = 0; i < TLP; i++)
                        {
                            if (strcmp(vCod[i], vcod_temp) == 0)
                            {
                                product_found = 1;
                                product_price = (float)vPreco[i] / 100.0;
                                product_index = i;
                            }
                        }

                        strcpy(vProdServV[product_index], vProdServ[product_index]);

                        if (!product_found)
                        {
                            printf("Codigo do produto nao encontrado!\n");
                            repeat = 1;
                        }
                    } while (repeat == 1);

                    strcpy(vCodV[TLV], vcod_temp);

                    do
                    { 
                        repeat = 0;

                        printf("\nDigite a quantidade do produto: ");
                        scanf("%d", &qtd_temp);

                        if (qtd_temp <= 0 || qtd_temp > vQtde[product_index])
                        {
                            printf("Quantidade invalida ou insuficiente em estoque!\n");
                            printf("Nao foi possível concluir a venda\n");
                            repeat = 1;
                        }

                        if (!repeat)
                        {
                            float total = (float)qtd_temp * product_price;
                            vQtde[product_index] -= qtd_temp;

                            printf("\nO valor da venda foi: %.2f\n", total);
                            
                            vPrecoV[TLV] = (int)(total * 100 + 0.5);
                        }
                    } while(repeat == 1);

                    vQtdeV[TLV] = qtd_temp;

                    printf("\n-> %d | Cod. Produto: %s | Quantidade: %s | Quantidade: %d | Preco: %.2f", TLV + 1, vCodV[TLV], vProdServV[TLV], vQtdeV[TLV], (float)vPrecoV[TLV] / 100.0);

                    TLV++;

                    printf("\nQuer cadastrar mais uma venda? (S/N)\n> ");
                    scanf(" %c", &continue_choosen);
                } while (tolower(continue_choosen) == 's');
            }
            else
            {
                printf("Nao ha produtos cadastrados!\n");
            }
            break;
        case 4:
            // Code Report (Otávio && Breno Passarela && Breno Henrique)
            printf("\nRelatorio selecionado \n");

            do
            {
                printf("\n"
                       "1: Gerenciar Produtos/Servicos\n"
                       "2: Gerenciar Clientes\n"
                       "3: Gerenciar Vendas\n"
                       "4: Retornar\n"
                       "> ");
                scanf(" %d", &program_execute_action);

                switch (program_execute_action)
                {
                case 1:
                    printf("\n");
                    for (int i = 0; i < TLP; i++)
                    {
                        printf("%d | Cod. Produto: %s | Produto: %s | Quantidade: %d | Preco: %.2f\n", i + 1, vCod[i], vProdServ[i], vQtde[i], (float)vPreco[i] / 100.0);
                    }
                    printf("\n");

                    printf("Pressione Enter para continuar...\n");
                    while (getchar() != '\n')
                        ;
                    getchar();

                    break;
                case 2:
                    printf("\n");
                    for (int i = 0; i < TLC; i++)
                    {
                        printf(" %d | RG: %s | Nome Cliente: %s\n", i + 1, vRG[i], vCliente[i]);
                    }
                    printf("\n");

                    printf("Pressione Enter para continuar...\n");
                    while (getchar() != '\n');
                    getchar();

                    break;
                case 3:
                    printf("\n");
                    for (int i = 0; i < TLV; i++)
                    {
                        printf("%d | Cliente: %s |Cod. Produto: %s | Produto: %s | Quantidade: %d | Preco: %.2f\n", i + 1, vCliente[i] ,vCodV[i], vProdServV[i], vQtdeV[i], (float)vPrecoV[i] / 100.0);
                    }
                    printf("\n");

                    printf("Pressione Enter para continuar...\n");
                    while (getchar() != '\n')
                        ;
                    getchar();

                    break;
                }

                if (program_execute_action > 4 || program_execute_action <= 0)
                    printf("\nOpcao invalida! Tente novamente.\n");
                printf("\n");
            } while (program_execute_action != 4);

            break;
        case 5:
            // Confirm program exit
            int conditional;
            do
            {
                printf("Tem certeza ? (S/N) \n");
                scanf(" %c", &program_confirm_exit);
                // Condition to be checked, it returns 0 for false and 1 for true
                conditional = tolower(program_confirm_exit) != 'n' && tolower(program_confirm_exit) != 's';
                if (conditional)
                    printf("Resposta invalida! Tente novamente...");
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
            printf("\nOpcao invalida! Tente novamente.\n");
            break;
        }
    } while (program_exit != 0);

    return 0;
}

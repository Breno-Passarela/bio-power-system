#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
    int TLV = 0, TLP = 0, TLC = 0, TLS = 0;

    // Product
    char vCod[TF][50], vProdServ[TF][50];
    int vQtde[TF], vPreco[TF],qtd;

    // Client
    char vRG[TF][12], vCliente[TF][30];

    // Services
    char vRGV[TF][11], vCodV[TF][50];
    int vQtdeV[TF], vPrecoV[TF];

    // Controllers
    // Program
    int program_exit = 1, program_execute_action;
    char program_confirm_exit, continue_choosen;

    // Interface
    do
    {
        printf("\n"
               "1: Cadastro\n"
               "2: Excluir\n"
               "3: Venda\n"
               "4: Relatórios\n"
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
                       "1: Produtos/Serviços\n"
                       "2: Clientes\n"
                       "3: Retornar\n"
                       "> ");
                scanf(" %d", &program_execute_action);

                switch (program_execute_action)
                {
                case 1:
                    // Code Products and Services (Otávio && Breno Henrique)
                    printf("\n Produtos e Serviços selecionado");
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
                            printf("\nDigite o código do produto ou serviço: ");
                            gets(vcod_temp);

                            int i = 0;
                            while (i < TLP)
                            {
                                if (strcmp(vcod_temp, vCod[i]) == 0)
                                {
                                    printf("Código %s já cadastrado! \n", vcod_temp);
                                    repeat = 1;
                                }
                                i++;
                            }
                        } while (repeat == 1);

                        strcpy(vCod[TLP], vcod_temp);

                        do
                        {
                            repeat = 0;
                            printf("Digite o produto ou serviço: ");
                            gets(vprodserv_temp);

                            int i = 0;
                            while (i < TLP)
                            {
                                if (strcmp(vprodserv_temp, vProdServ[i]) == 0)
                                {
                                    printf("Produto %s já cadastrado! \n", vprodserv_temp);
                                    repeat = 1;
                                }
                                i++;
                            }

                        } while (repeat == 1);

                        strcpy(vProdServ[TLP], vprodserv_temp);

                        printf("Quantidade do produto: ");
                        scanf(" %d", &vQtde[TLP]);

                        printf("Digite o preço: ");
                        scanf(" %f", &vpreco_temp);

                        vPreco[TLP] = (int)(vpreco_temp * 100 + 0.5); // Casting

                        printf("\n-> %d | %s | %s | %d | %d -> %.2f\n", TLP + 1, vCod[TLP], vProdServ[TLP], vQtde[TLP], vPreco[TLP], (float)vPreco[TLP] / 100.0);

                        TLP++;

                        printf("\nQuer adicionar mais um produto? (S/N)\n> ");
                        scanf(" %c", &continue_choosen);
                    } while (tolower(continue_choosen) == 's');

                    break;
                case 2:
                    // Code Client (Rafael && Matheus Bispo)
                    // printf("\n Cliente selecionado");

                    char continue_choosen;
                    char rg_temp[12];

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

                            if (strlen(rg_temp) != 11)
                            {
                                printf("RG com tamanho inválido! \n");
                                printf("Pressione enter para digitar novamente... \n");
                                repeat = 1;
                            }

                            while (i < TLC && strlen(rg_temp) == 11 && repeat == 0)
                            {
                                if (strcmp(rg_temp, vRG[i]) == 0)
                                {
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

                        printf("\nQuer adicionar mais um cliente? (S/N)\n> ");
                        scanf(" %c", &continue_choosen);

                    } while (tolower(continue_choosen) == 's');
                    break;
                }

                if (program_execute_action > 3 || program_execute_action <= 0)
                    printf("\nOpção inválida! Tente novamente.\n");
                printf("\n");
            } while (program_execute_action != 3);
            break;
        case 2:
            // Code Delete (Breno Passarela && Kaua)
            printf("\n Exclusão selecionado \n");

            do
            {
                printf("\n"
                       "1: Produtos/Serviços\n"
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

                            printf("Digite o código do produto que deseja excluir: ");
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
                                printf("Produto não existe! \n");
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

                                printf("Produto com código %s excluído com sucesso.\n", vcod_temp);
                            }
                        } while (repeat == 1);

                        printf("\nQuer excluir mais um produto? (S/N)\n> ");
                        scanf(" %c", &continue_choosen);
                    } while (tolower(continue_choosen) == 's');

                    break;
                case 2:
                    char rg_temp[12];

                    do
                    {
                        int repeat = 0;

                        do
                        {
                            int i = 0;
                            int j = 0;

                            while (getchar() != '\n')
                                ;

                            printf("Digite o RG do cliente que deseja excluir: ");
                            fflush(stdin);
                            gets(rg_temp);

                            while (i < TLV && repeat == 0)
                            {
                                if (strcmp(rg_temp, vRGV[i]) == 0)
                                {
                                    printf("RG com vendas pendentes! \n");
                                    printf("Pressione enter para digitar outro... \n");
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
                                printf("RG não existe! \n");
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

                                printf("Cliente com RG %s excluído com sucesso.\n", rg_temp);
                            }
                        } while (repeat == 1);

                        printf("\nQuer excluir mais um cliente? (S/N)\n> ");
                        scanf(" %c", &continue_choosen);
                    } while (tolower(continue_choosen) == 's');
                    break;
                }

                if (program_execute_action > 3 || program_execute_action <= 0)
                    printf("\nOpção inválida! Tente novamente.\n");
                printf("\n");
            } while (program_execute_action != 3);
            break;
        case 3:
            char continue_choosen;
            do {
                int repeat;
                int client_found = 0;
                int product_found = 0;
                int product_index = -1;
                float product_price = 0.0;
                
                do{
                    printf("\nVenda selecionada\n");

                    printf("\nDigite seu RG:\n");
                    scanf("%s", vRG[TLC]);

                    do{
                        for (int i = 0; i < TLC; i++) {
                            if (strcmp(vRG[TLC], vRG[i]) == 0) {                           
                                client_found = 1; 
                            }
                        }

                        if (!client_found) {
                            printf("RG não cadastrado! Não é possível realizar a venda.\n");
                            repeat = 1;
                        }
                    } while(repeat = 1);
                    
                    do{
                        printf("\nDigite o código do produto:\n");
                        scanf("%s", vCod[TLP]);

                        for (int i = 0; i < TLP; i++) {
                            if (strcmp(vCod[TLP], vCod[i]) == 0) {                                             
                                product_found = 1;                   
                                product_price = (float)vPreco[i] / 100.0; 
                                product_index = i;                       
                            }
                        }

                        if (!product_found) {
                            printf("Código do produto não encontrado!\n");
                        }
                    } while(repeat = 1);

                    printf("Digite a quantidade do produto: ");
                    scanf("%d", &qtd);

                    if (qtd <= 0 || qtd > vQtde[product_index]) {
                        printf("Quantidade inválida ou insuficiente em estoque!\n");
                        printf("Não foi possível concluir a venda\n");
                        repeat = 1;
                    }

                    if (repeat = 0) {
                        float selling = qtd * product_price;
                        vQtde[product_index] -= qtd;
                        TLV++;

                        printf("O valor da venda foi: %.2f\n", selling);
                    }
                } while (repeat = 1);

                printf("\nQuer cadastrar uma venda? (S/N)\n> ");
                scanf(" %c", &continue_choosen);
            } while (tolower(continue_choosen) == 's');
            break;
        case 4:
            // Code Report (Otávio && Breno Passarela && Breno Henrique)
            printf("\nRelatório selecionado \n");
            
                do {
                    printf("\n"
                    "1: Gerenciar Produtos/Serviços\n"
                    "2: Gerenciar Clientes\n"
                    "3: Gerenciar Vendas\n"
                    "4: Retornar\n"
                    "> ");
                    scanf(" %d", &program_execute_action);

                    switch(program_execute_action) {
                        case 1:
                            int i = 0;

                            printf("\n");
                            for (i = 0; i < TLP; i++) {
                                printf("%d | %s | %s | %d | %.2f\n", i + 1, vCod[i], vProdServ[i], vQtde[i], (float)vPreco[i] / 100.0);
                            }
                            printf("\n");

                            printf("Pressione Enter para continuar...\n");
                            while(getchar() != '\n');
                            getchar();

                            break;
                        case 2:
                            printf("\n");
                            for (int i = 0; i < TLC; i++) {
                                printf("%d | %s | %s\n", i + 1, vRG, vCliente);
                            }
                            printf("\n");

                            printf("Pressione Enter para continuar...\n");
                            while(getchar() != '\n');
                            getchar();

                            break;
                        case 3:
                            printf("\n");
                            for (int i = 0; i < TLV; i++) {
                                printf("%d | %s | %s | %d | %.2f\n", i + 1, vRGV[i], vCodV[i], vQtdeV[i], (float)vPrecoV[i] / 100.0);
                            }
                            printf("\n");

                            printf("Pressione Enter para continuar...\n");
                            while(getchar() != '\n');
                            getchar();

                            break;
                    }

                    if(program_execute_action > 4 || program_execute_action <= 0) printf("\nOpção inválida! Tente novamente.\n"); 
                    printf("\n");
                } while(program_execute_action != 3);   

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
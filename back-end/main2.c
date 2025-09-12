#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef struct
{

    int codigo, quantidade;
    char nome[200], descricao[255], criadoPor[200];
    float valor, desconto;

} Produto;

typedef struct
{

    char usuario[200], senha[200];

} Administrador;

// Telas do software
void sistemaAdmin(char *login, Produto *produtos, int *produtosTopo)
{
    printf("\nVoc selecionou o sistema de Administrador!\n");
    int menu, submenu;

    do
    {
        printf("\n 1: Administradores \n 2: Produtos \n 3: Relatórios \n 4: Voltar para login \n > ");
        scanf("%d", &menu);

        switch (menu)
        {
        case 1:
            printf("\n 1: Cadastrar Administrador \n 2: Deletar Administrador \n 3: Editar Administrador \n 4: Voltar \n > ");
            scanf("%d", &submenu);
            switch (submenu)
            {
            case 1:
                printf("\nOpcao 'Cadastrar Administrador' selecionada.\n");
                printf("\nFuncao em desenvolvimento, aguarde novas atualizacoes\n");
                break;
            case 2:
                printf("\nOpcao 'Deletar Administrador' selecionada.\n");
                printf("\nFuncao em desenvolvimento, aguarde novas atualizacoes\n");
                break;
            case 3:
                printf("\nOpcao 'Editar Administrador' selecionada.\n");
                printf("\nFuncao em desenvolvimento, aguarde novas atualizacoes\n");
                break;
            case 4:
                printf("\nVoltando ao menu principal.\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
            }
            break;
        case 2:
            printf("\n 1: Cadastrar Produto \n 2: Deletar Produto \n 3: Editar Produto \n 4: Vender Produto \n 5: Controlar Estoque do Produto \n 6: Voltar \n > ");
            scanf("%d", &submenu);
            switch (submenu)
            {
            case 1:
                printf("\nOpcao 'Cadastrar Produto' selecionada.\n");
                printf("\nFuncao em desenvolvimento, aguarde novas atualizacoes\n");
                break;
            case 2:
                printf("\nOpcao 'Deletar Produto' selecionada.\n");
                printf("\nFuncao em desenvolvimento, aguarde novas atualizacoes\n");
                break;
            case 3:
                printf("\nOpcao 'Editar Produto' selecionada.\n");
                printf("\nFuncao em desenvolvimento, aguarde novas atualizacoes\n");
                break;
            case 4:
                printf("\nOpcao 'Vender Produto' selecionada.\n");
                printf("\nFuncao em desenvolvimento, aguarde novas atualizacoes\n");
                break;
            case 5:
                printf("\nOpcao 'Controlar Estoque' selecionada.\n");
                printf("\nFuncao em desenvolvimento, aguarde novas atualizacoes\n");
                break;
            case 6:
                printf("\nVoltando ao menu principal.\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
            }
            break;
        case 3:
            printf("\nOpcao 'Relatorios' selecionada.\n");
            printf("\nFuncao em desenvolvimento, aguarde novas atualizacoes\n");
            break;
        case 4:
            printf("\nVoltando para o login.\n");
            break;
        default:
            printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (menu != 4);
}

void sistemaCliente(Produto *produtos, int *produtosTopo)
{
    printf("\nVoce selecionou o sistema de cliente!\n");
    int menu, submenu;

    do
    {
        printf("\n 1: Produtos \n 2: Voltar para login \n");
        scanf("%d", &menu);

        switch (menu)
        {
        case 1:
            printf("\n 1: Ver Catalogo \n 2: Voltar \n");
            scanf("%d", &submenu);
            switch (submenu)
            {
            case 1:
                printf("\nOpcao 'Ver Catalogo' selecionada.\n");
                printf("\nFuncao em desenvolvimento, aguarde novas atualizacoes\n");
                break;
            case 2:
                printf("\nVoltando ao menu principal.\n");
                printf("\nFuncao em desenvolvimento, aguarde novas atualizacoes\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
            }
            break;
        case 2:
            printf("\nVoltando para o login.\n");
            break;
        default:
            printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (menu != 2);
}

// Autentificacao
main()
{
    int menuLogin, c;
    int tmnhListaAdm = 200;

    Administrador administradores[tmnhListaAdm];
    Produto produtos[200];

    // Inicializando topos
    int admTopo = 0, produtosTopo = 0;

    // Inicializando conta master
    strcpy(administradores[admTopo].usuario, "biopower");
    strcpy(administradores[admTopo].senha, "123456");
    admTopo++;

    char loginSalvo[200];

    do
    {
        printf("\nEntrar como:\n 1: Administrador\n 2: Cliente\n 3: Sair\n");
        scanf("%d", &menuLogin);

        switch (menuLogin)
        {
        case 1:
            char usuarioPedido[50], senhaPedido[50];

            printf("\nDigite o usuario: ");
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            gets(usuarioPedido);

            printf("\nDigite a senha: ");
            //   while ((c = getchar()) != '\n' && c != EOF);
            gets(senhaPedido);

            int achou = 0;
            for (int i = 0; i < admTopo && !achou; i++)
            {
                if (strcmp(administradores[i].usuario, usuarioPedido) == 0 && strcmp(administradores[i].senha, senhaPedido) == 0)
                {
                    strcpy(loginSalvo, usuarioPedido);
                    sistemaAdmin(loginSalvo, produtos, &produtosTopo);
                    achou = 1;
                }
            }

            if (achou == 0)
                printf("\nConta nao encontrada. Tente novamente!\n");

            break;
        case 2:
            sistemaCliente(produtos, &produtosTopo);
            break;
        }
    } while (menuLogin != 3);
}
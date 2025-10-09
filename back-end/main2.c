#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct
{
    int dia, mes, ano;
} Dia;

typedef struct
{
    int lote, quantidade;
    char nome[200], descricao[255], laboratorio[200], tipo[100];
    float valor, desconto;
    Dia validade;
} Produto;

typedef struct
{
    char usuario[200], senha[200];
} Administrador;

// Telas do software

void sistemaAdmin(char *login, Produto *produtos, int *produtosTopo)
{
    system("cls");
    printf("\nVoce selecionou o sistema de Administrador!\n");
    int menu, submenu;

    do
    {
        printf("\n1: Administradores\n");
        printf("2: Gerenciar Produtos\n");
        printf("3: Relatórios\n");
        printf("4: Gerenciar Laboratórios\n");
        printf("5: Voltar para Login\n");
        printf("> ");
        scanf("%d", &menu);
        system("cls");

        switch (menu)
        {
        case 1:
            printf("\n1: Cadastrar Administrador\n");
            printf("2: Deletar Administrador\n");
            printf("3: Editar Administrador\n");
            printf("4: Voltar\n");
            printf("> ");

            scanf("%d", &submenu);
            system("cls");
            switch (submenu)
            {
            case 1:
                printf("\nCadastrar Administrador em desenvolvimento\n");
                system("pause");
                break;
            case 2:
                printf("\nDeletar Administrador em desenvolvimento\n");
                system("pause");
                break;
            case 3:
                printf("\nEditar Administrador em desenvolvimento\n");
                system("pause");
                break;
            case 4:
                printf("\nVoltando ao menu principal.\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
            }
            break;
        case 2:
            printf("\n1: Cadastrar Produto\n");
            printf("2: Deletar Produto\n");
            printf("3: Editar Produto\n");
            printf("4: Vender Produto\n");
            printf("5: Controlar Estoque\n");
            printf("6: Verificar por Tipo de Produto\n");
            printf("7: Voltar para o Menu\n");
            printf("> ");
            scanf("%d", &submenu);
            system("cls");
            switch (submenu)
            {
            case 1:
                printf("\nCadastrar Produto em desenvolvimento\n");
                system("pause");
                break;
            case 2:
                printf("\nDeletar Produto em desenvolvimento\n");
                system("pause");
                break;
            case 3:
                printf("\nEditar Produto em desenvolvimento\n");
                system("pause");
                break;
            case 4:
                printf("\nVender Produto em desenvolvimento\n");
                system("pause");
                break;
            case 5:
                printf("\nControlar Estoque em desenvolvimento\n");
                system("pause");
                break;
            case 6:
                printf("\nVerificar por tipo de produto em desenvolvimento\n");
                system("pause");
                break;
            case 7:
                printf("\nVoltando ao menu principal.\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
            }
            break;
        case 3:
            printf("\nRelatórios em desenvolvimento\n");
            system("pause");
            break;
        case 4:
            printf("\nGerenciar laboratórios em desenvolvimento\n");
            system("pause");
            break;
        case 5:
            printf("\nVoltando para o login.\n");
            break;
        default:
            printf("\nOpção inválida! Tente novamente.\n");
        }
    } while (menu != 5);
}

void sistemaCliente(Produto *produtos, int *produtosTopo)
{
    system("cls");
    printf("\nVoce selecionou o sistema de cliente!\n");
    int menu, submenu;

    do
    {
        printf("\n1: Produtos\n");
        printf("2: Voltar para Login\n");
        printf("> ");
        scanf("%d", &menu);
        system("cls");

        switch (menu)
        {
        case 1:
            printf("\n1: Ver Catálogo\n");
            printf("2: Voltar\n");
            printf("> ");
            scanf("%d", &submenu);
            system("cls");
            switch (submenu)
            {
            case 1:
                printf("\nVer Catálogo em desenvolvimento\n");
                system("pause");
                break;
            case 2:
                printf("\nVoltando ao menu principal.\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
            }
            break;
        case 2:
            printf("\nVoltando para o login.\n");
            break;
        default:
            printf("\nOpção inválida! Tente novamente.\n");
        }
    } while (menu != 2);
}

void gerenciarLaboratorios(Produto *produtos)
{
    system("cls");
    printf("\nVocê selecionou gerenciar laboratórios de produto.\n");
    int menu;

    do
    {
        printf("\n1: Relatório de Vendas por Laboratório\n");
        printf("2: Verificar Estoque de Produtos por Laboratório\n");
        printf("3: Voltar\n");
        printf("> ");
        scanf("%d", &menu);
        system("cls");

        switch (menu)
        {
        case 1:
            printf("\nRelatório de venda por laboratórios em desenvolvimento\n");
            system("pause");
            break;
        case 2:
            printf("\nVerificar estoque de produtos por laboratório em desenvolvimento\n");
            system("pause");
            break;
        case 3:
            printf("\nVoltando ao menu anterior.\n");
            break;
        default:
            printf("\nOpção inválida!\n");
        }
    } while (menu != 3);
}

void gerenciarTiposProdutos(Produto *produtos)
{
    system("cls");
    printf("\nVocê selecionou gerenciar tipos de produto.\n");
    int menu;

    do
    {
        printf("\n1: Relatórios de Vendas por Tipo de Produto\n");
        printf("2: Controle de Estoque por Tipo de Produto\n");
        printf("3: Voltar para o Menu\n");
        printf("> ");
        scanf("%d", &menu);
        system("cls");

        switch (menu)
        {
        case 1:
            printf("\nRelatório de venda por tipo de produto em desenvolvimento\n");
            system("pause");
            break;
        case 2:
            printf("\nControle de estoque por tipo de produto em desenvolvimento\n");
            system("pause");
            break;
        case 3:
            printf("\nVoltando ao menu principal.\n");
            break;
        default:
            printf("\nOpção inválida!\n");
        }
    } while (menu != 3);
}

void gerenciarCategoriaProdutos(Produto *produtos)
{
    system("cls");
    printf("\nVocê selecionou gerenciar categorias de produto.\n");
    int menu;

    do
    {
        printf("\n1: Relatórios de Vendas por Categoria de Produto\n");
        printf("2: Controle de Estoque por Categoria de Produto\n");
        printf("3: Voltar para o Menu\n");
        printf("> ");
        scanf("%d", &menu);
        system("cls");

        switch (menu)
        {
        case 1:
            printf("\nRelatório de venda por categoria de produto em desenvolvimento\n");
            system("pause");
            break;
        case 2:
            printf("\nControle de estoque por categoria de produto em desenvolvimento\n");
            system("pause");
            break;
        case 3:
            printf("\nVoltando ao menu principal.\n");
            break;
        default:
            printf("\nOpção inválida!\n");
        }
    } while (menu != 3);
}

void promocaoValidade(Produto *produtos, int produtosTopo)
{
    system("cls");
    int m, a, l, i;

    printf("\nDigite o lote do produto:\n> ");
    scanf("%d", &l);
    system("cls");

    printf("\nDigite a data de hoje:\nMês(mm):\n> ");
    scanf("%d", &m);
    system("cls");

    printf("\nAno(aaaa):\n> ");
    scanf("%d", &a);
    system("cls");

    for (i = 0; i < produtosTopo; i++)
    {
        if (produtos[i].lote == l)
        {
            if (produtos[i].validade.ano == a && produtos[i].validade.mes == m)
            {
                printf("\nProduto %s está perto de vencer!\n", produtos[i].nome);
            }
        }
    }
}

main()
{
    int menuLogin, c;
    int tmnhListaAdm = 200;

    Administrador administradores[tmnhListaAdm];
    Produto produtos[200];

    int admTopo = 0, produtosTopo = 0, i;

    strcpy(administradores[admTopo].usuario, "biopower");
    strcpy(administradores[admTopo].senha, "123456");
    admTopo++;

    char loginSalvo[200];

    do
    {
        printf("\nEntrar como:\n");
        printf("1: Administrador\n");
        printf("2: Cliente\n");
        printf("3: Sair\n");
        printf("> ");
        scanf("%d", &menuLogin);
        system("cls");

        switch (menuLogin)
        {
        case 1:
        {
            char usuarioPedido[200], senhaPedido[200];
            printf("\nDigite o usuario: ");
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            fgets(usuarioPedido, sizeof(usuarioPedido), stdin);
            usuarioPedido[strcspn(usuarioPedido, "\n")] = '\0'; // remove \n

            printf("Digite a senha: ");
            fgets(senhaPedido, sizeof(senhaPedido), stdin);
            senhaPedido[strcspn(senhaPedido, "\n")] = '\0';
            system("cls");

            int achou = 0;
            for (i = 0; i < admTopo && !achou; i++)
            {
                if (strcmp(administradores[i].usuario, usuarioPedido) == 0 &&
                    strcmp(administradores[i].senha, senhaPedido) == 0)
                {
                    strcpy(loginSalvo, usuarioPedido);
                    sistemaAdmin(loginSalvo, produtos, &produtosTopo);
                    achou = 1;
                }
            }

            if (!achou)
            {
                printf("\nConta nao encontrada. Tente novamente!\n");
            }
            break;
        }
        case 2:
            sistemaCliente(produtos, &produtosTopo);
            break;
        case 3:
            printf("\nSaindo do sistema...\n");
            break;
        default:
            printf("\nOpcao invalida!\n");
        }
    } while (menuLogin != 3);
}

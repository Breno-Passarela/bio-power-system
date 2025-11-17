#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <windows.h>

typedef struct
{
    int dia, mes, ano;
} Dia;
typedef struct
{
    int lote, mes, ano;

} PromocaoProduto;
;

typedef struct
{
    int cod, lote, quantidade;
    char nome[200], descricao[255], laboratorio[200], tipo[100];
    float valor, desconto;
    PromocaoProduto prom;
    Dia validade;
} Produto;

typedef struct
{
    char usuario[200], senha[200];
} Administrador;

int buscaCod(FILE *ptProduto, int cod)
{
    Produto p;
    rewind(ptProduto);
    fread(&p, sizeof(Produto), 1, ptProduto);
    while (!feof(ptProduto) && p.cod != cod)
    {
        fread(&p, sizeof(Produto), 1, ptProduto);
    }
    if (!feof(ptProduto))
    {
        return ftell(ptProduto) - sizeof(Produto);
    }
    else
    {
        return -1;
    }
}

int buscaADM(FILE *ptAdm, char usuario[200])
{
    Administrador adm;
    rewind(ptAdm);
    fread(&adm, sizeof(Administrador), 1, ptAdm);
    while (!feof(ptAdm) && strcmp(adm.usuario, usuario) != 0)
    {
        fread(&adm, sizeof(Administrador), 1, ptAdm);
    }
    if (!feof(ptAdm))
    {
        return ftell(ptAdm) - sizeof(Administrador);
    }
    else
    {
        return -1;
    }
}

// Telas do software
// Menu do sistema de administrador
void sistemaAdmin(char *login, Produto *produtos, int *produtosTopo){
    FILE *ptAdm;
    Administrador adm;
    system("cls");
    printf("\nVoce selecionou o sistema de Administrador!\n");
    int menu, submenu, pos, op;
    char resp;
    char usuario[200];

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
        case 1:{
            printf("\n1: Cadastrar Administrador\n");
            printf("2: Deletar Administrador\n");
            printf("3: Editar Administrador\n");
            printf("4: Voltar\n");
            printf("> ");

            scanf("%d", &submenu);
            system("cls");
            switch (submenu){
            case 1:{
                printf("\nCadastrar Administrador em desenvolvimento\n");
                FILE *ptAdm;
                ptAdm = fopen("administradores.bin", "ab+");
                if (ptAdm == NULL)
                {
                    printf("Erro ao criar o arquivo de administradores.\n");
                    system("pause");
                }
                else
                {
                    do
                    {
                        printf("Digite o nome do novo administrador: ");fflush(stdin);
                        scanf(" %s", &adm.usuario);
                        //gets(adm.usuario);
                        pos = buscaADM(ptAdm, adm.usuario);
                        if (pos == -1)
                        {
                            printf("Digite a senha do novo administrador: ");fflush(stdin);
                            scanf(" %s", &adm.senha);
                            //gets(adm.senha);
                            fwrite(&adm, sizeof(Administrador), 1, ptAdm);
                            printf("Administrador cadastrado com sucesso!\n");
                        }
                        else
                        {
                            fseek(ptAdm, pos, 0);
                            fread(&adm, sizeof(Administrador), 1, ptAdm);
                            printf("Administrador ja existe!\n");
                        }
                        printf("Deseja cadastrar outro administrador? (s/n):\n> ");
                        scanf(" %c", &resp);
                    } while (resp == 's' || resp == 'S');
                }
                system("pause");
                fclose(ptAdm);
                break;
            }
            case 2:{
                FILE *ptAdm;
                ptAdm = fopen("administradores.bin", "rb+");
                if (ptAdm == NULL)
                {
                    printf("Erro ao abrir o arquivo de administradores.\n");
                    system("pause");
                }
                else
                {
                    printf("\nDeletar Administrador em desenvolvimento\n");
                    printf("Digite o nome do administrador a ser deletado: ");fflush(stdin);
                    scanf(" %s", &usuario);
                    if (strcmp(usuario, "/0") != 0)
                    {
                        pos = buscaADM(ptAdm, usuario);
                        if (pos == -1)
                        {
                            printf("Administrador nao encontrado!\n");
                            system("pause");
                        }
                        else
                        {
                            fseek(ptAdm, pos, 0);
                            fread(&adm, sizeof(Administrador), 1, ptAdm);
                            printf("\n---------------------------------\n");
                            printf("Administrador: %s\n", adm.usuario);
                            printf("---------------------------------\n");
                            printf("Tem certeza que deseja deletar este administrador? (s/n):\n> ");
                            scanf(" %c", &resp);
                            if (resp == 's' || resp == 'S')
                            {
                                FILE *ptTemp;
                                ptTemp = fopen("temp.bin", "wb");
                                rewind(ptAdm);
                                fread(&adm, sizeof(Administrador), 1, ptAdm);
                                while (!feof(ptAdm))
                                {
                                    if (strcmp(adm.usuario, usuario) != 0)
                                    {
                                        fwrite(&adm, sizeof(Administrador), 1, ptTemp);
                                    }
                                    fread(&adm, sizeof(Administrador), 1, ptAdm);
                                }
                                fclose(ptAdm);
                                fclose(ptTemp);
                                remove("administradores.bin");
                                rename("temp.bin", "administradores.bin");
                            }
                        }
                    }
                    printf("Administrador deletado com sucesso!\n");
                }
                break;
            }
            case 3:{
                printf("\nEditar Administrador em desenvolvimento\n");
                FILE *ptAdm;
                ptAdm = fopen("administradores.bin", "rb+");
                if (ptAdm == NULL){
                    printf("Erro ao abrir o arquivo de administradores.\n");
                    system("pause");
                }
                else{
                    printf("Digite o nome do administrador a ser editado: ");fflush(stdin);
                    scanf(" %s", adm.usuario);

                    while (strcmp(adm.usuario, "\0") != 0 ){
                        pos = buscaADM(ptAdm, adm.usuario);
                        if (pos == -1){
                            printf("Administrador nao encontrado!\n");
                            system("pause");
                        }
                        else{
                            fseek(ptAdm, pos, 0);
                            fread(&adm, sizeof(Administrador), 1, ptAdm);

                            printf("\n---------------------------------\n");
                            printf("Administrador: %s\n", adm.usuario);
                            printf("---------------------------------\n");

                            printf("Deseja alterar: ");
                            printf("\n1: Usuario");
                            printf("\n2: Senha");
                            printf("\n> ");
                            scanf("%d", &op);

                            switch (op){
                                case 1:
                                    printf("Digite o novo usuario: \n> ");
                                    fflush(stdin);
                                    scanf(" %s", adm.usuario);
                                    fseek(ptAdm, pos, 0);
                                    fwrite(&adm, sizeof(Administrador), 1, ptAdm);
                                    printf("Usuario alterado com sucesso!\n");
                                break;

                                case 2:
                                    printf("Digite a nova senha: \n> ");
                                    fflush(stdin);
                                    scanf(" %s", adm.senha);
                                    fseek(ptAdm, pos, 0);
                                    fwrite(&adm, sizeof(Administrador), 1, ptAdm);
                                    printf("Senha alterada com sucesso!\n");
                                break;
                            }
                        }
                        printf("Administrador editado com sucesso!\n");
                        system("pause");
                    }
                }
                fclose(ptAdm);
                break;
            }

            case 4:
            {
                printf("\nVoltando ao menu principal.\n");
                break;
            }
            default:
                printf("\nOpção inválida! Tente novamente.\n");
            }
            break;
        }
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

// Menu do sistema de cliente
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

// Menu do sistema de gerenciar laboratórios
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

// Menu do sistema de gerenciar tipos de produtos
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

// Menu do sistema de gerenciar categorias de produtos
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

// Menu do sistema de promoção por validade
void promocaoValidade(Produto *produtos, int produtosTopo)
{

    Produto P;
    system("cls");
    int i;

    printf("\nDigite o lote do produto:\n> ");
    scanf("%d", &P.prom.lote);
    system("cls");

    printf("\nDigite a data de hoje:\nMês(mm):\n> ");
    scanf("%d", &P.prom.mes);
    system("cls");

    printf("\nAno(aaaa):\n> ");
    scanf("%d", &P.prom.ano);
    system("cls");

    for (i = 0; i < produtosTopo; i++)
    {
        if (produtos[i].lote == P.prom.lote)
        {
            if (produtos[i].validade.ano == P.prom.ano && produtos[i].validade.mes == P.prom.mes)
            {
                printf("\nProduto %s está perto de vencer!\n", produtos[i].nome);
            }
        }
    }
}

int main()
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

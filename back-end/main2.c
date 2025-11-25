#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <windows.h>

typedef struct{
    int dia, mes, ano;
} Dia;

typedef struct{
    int lote, mes, ano;

} PromocaoProduto;

typedef struct{
    int cod, lote, quantidade;
    char nome[200], descricao[255], laboratorio[200], tipo[100];
    float valor;
    float desconto;
    PromocaoProduto prom;
    Dia validade;
} Produto;

typedef struct {
    int cod, quantidadeVendida;
    char nome[200], laboratorio[200], tipo[100], formaPagamento[20];
    float valorVenda;
    Dia venda;
} ProdutoVendido;

typedef struct{
    char usuario[200], senha[200];
} Administrador;

int buscaCodProduto(FILE *ptProduto, int cod){
    Produto p;
    rewind(ptProduto);
    fread(&p, sizeof(Produto), 1, ptProduto);
    while (!feof(ptProduto) && p.cod != cod){
        fread(&p, sizeof(Produto), 1, ptProduto);
    }
    if (!feof(ptProduto)){
        return ftell(ptProduto) - sizeof(Produto);
    }

    return -1;
}

int exibirProduto() {
    FILE *ptProduto;
    Produto pd;
    printf("\nExibir Produto\n");
    ptProduto = fopen("produtos.bin", "rb");
        if (ptProduto == NULL){
            printf("Erro ao abrir o arquivo de produtos.\n");
            system("pause");
        }else{
            printf("\nLista de Produtos:\n");
            while (fread(&pd, sizeof(Produto), 1, ptProduto) == 1){
                printf("\n---------------------------------\n");
                printf("Codigo: %d\n", pd.cod);
                printf("Produto: %s\n", pd.nome);
                printf("Descricao: %s\n", pd.descricao);
                printf("Laboratorio: %s\n", pd.laboratorio);
                printf("Tipo: %s\n", pd.tipo);
                printf("Valor: %.2f\n", pd.valor);
                printf("Desconto: %.2f\n", pd.desconto);
                printf("Lote: %d\n", pd.lote);
                printf("Validade: %d/%d/%d\n", pd.validade.dia, pd.validade.mes, pd.validade.ano);
                printf("---------------------------------\n");
            }
            fclose(ptProduto);
        }
    system("pause");
}

int buscaADM(FILE *ptAdm, char usuario[200]){
    Administrador adm;
    rewind(ptAdm);
    fread(&adm, sizeof(Administrador), 1, ptAdm);
    while (!feof(ptAdm) && strcmp(adm.usuario, usuario) != 0){
        fread(&adm, sizeof(Administrador), 1, ptAdm);
    }
    if (!feof(ptAdm)){
        return ftell(ptAdm) - sizeof(Administrador);
    }

    return -1;
}

int loginAdministrador() {
    FILE *ptAdm; 
    char usuario[200], senha[200];
    Administrador adm;

    printf("\nDigite o usuario: ");
    scanf(" %s", usuario);

    printf("Digite a senha: ");
    scanf(" %s", senha);

    ptAdm = fopen("administradores.bin", "rb");
    if (!ptAdm) {
        printf("\nNenhum administrador cadastrado!\n");
        system("pause");
        return 0;
    }

    while (fread(&adm, sizeof(Administrador), 1, ptAdm)) {
        if (strcmp(adm.usuario, usuario) == 0 && strcmp(adm.senha, senha) == 0) {
            fclose(ptAdm);
            return 1; 
        }
    }

    fclose(ptAdm);
    return 0; 
}

void criarAdminInicial() {
    FILE *ptAdm;
    Administrador adm;
    ptAdm = fopen("administradores.bin", "rb");

    if(ptAdm){ 
        fclose(ptAdm); 
        return; 
    }

    ptAdm = fopen("administradores.bin", "wb");
    if(ptAdm == NULL){
        printf("Erro ao criar o arquivo de administradores.\n");
        return;
    }else{
        strcpy(adm.usuario, "biopower");
        strcpy(adm.senha, "123456");
    
        fwrite(&adm, sizeof(Administrador), 1, ptAdm);
    }
    fclose(ptAdm);
}

// Telas do software
#include <time.h>
void sistemaAdmin(char *login, Produto *produtos, int *produtosTopo){
    FILE *ptAdm;
    FILE *ptProduto;
    FILE *ptTempProduto;
    FILE *ptTempAdm;

    Administrador adm;
    Produto pd;

    int menu, submenu, pos, op;
    int cod;

    char resp;
    char usuario[200];

    system("cls");
    printf("\nVoce selecionou o sistema de Administrador!\n");

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
            printf("4: Exibir Administrador\n");
            printf("5: Voltar\n");
            printf("> ");

            scanf("%d", &submenu);
            system("cls");
            switch (submenu){
            case 1:{
                printf("\nCadastrar Administrador\n");
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
                        printf("Digite o nome do novo administrador: ");
                        scanf(" %s", &adm.usuario);
                        //gets(adm.usuario);
                        pos = buscaADM(ptAdm, adm.usuario);
                        if (pos == -1)
                        {
                            printf("Digite a senha do novo administrador: ");
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
                ptAdm = fopen("administradores.bin", "rb+");
                if (ptAdm == NULL)
                {
                    printf("Erro ao abrir o arquivo de administradores.\n");
                    system("pause");
                }
                else
                {
                    printf("\nDeletar Administrador\n");
                    printf("Digite o nome do administrador a ser deletado: ");
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
                                ptTempAdm = fopen("temp.bin", "wb");
                                rewind(ptAdm);
                                fread(&adm, sizeof(Administrador), 1, ptAdm);
                                while (!feof(ptAdm))
                                {
                                    if (strcmp(adm.usuario, usuario) != 0)
                                    {
                                        fwrite(&adm, sizeof(Administrador), 1, ptTempAdm);
                                    }
                                    fread(&adm, sizeof(Administrador), 1, ptAdm);
                                }
                                fclose(ptAdm);
                                fclose(ptTempAdm);
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
                printf("\nEditar Administrador\n");
                ptAdm = fopen("administradores.bin", "rb+");
                if (ptAdm == NULL){
                    printf("Erro ao abrir o arquivo de administradores.\n");
                    system("pause");
                }
                else{
                    printf("Digite o nome do administrador a ser editado: ");
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
                                    
                                    scanf(" %s", adm.usuario);
                                    fseek(ptAdm, pos, 0);
                                    fwrite(&adm, sizeof(Administrador), 1, ptAdm);
                                    printf("Usuario alterado com sucesso!\n");
                                break;

                                case 2:
                                    printf("Digite a nova senha: \n> ");
                                    
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
            case 4:{
                printf("\nExibir Administrador\n");
                ptAdm = fopen("administradores.bin", "rb");
                if (ptAdm == NULL){
                    printf("Erro ao abrir o arquivo de administradores.\n");
                    system("pause");
                }else{
                    printf("\nLista de Administradores:\n");
                    while (fread(&adm, sizeof(Administrador), 1, ptAdm)){
                        printf("\n---------------------------------\n");
                        printf("Administrador: %s\n", adm.usuario);
                        printf("---------------------------------\n");
                    }
                    fclose(ptAdm);
                }
                system("pause");
                break;
            }
            case 5:{
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
            printf("5: Exibir Produto\n");
            printf("6: Controlar Estoque\n");
            printf("7: Verificar por Tipo de Produto\n");
            printf("8: Voltar para o Menu\n");
            printf("> ");
            scanf("%d", &submenu);
            system("cls");
            switch (submenu){
            case 1:
                printf("\nCadastrar Produto\n");
                ptProduto = fopen("produtos.bin", "ab+");
                if (ptProduto == NULL){
                    printf("Erro ao criar o arquivo de produtos.\n");
                    system("pause");
                }
                else{
                    do {
                        system("cls");
                        printf("Digite o codigo do produto: ");
                        scanf("%d", &pd.cod);
                        pos = buscaCodProduto(ptProduto, pd.cod);
                        if(pos == -1){
                            printf("Digite o nome do produto: ");
                            scanf(" %s", pd.nome);
                            printf("Digite a descricao do produto: ");
                            scanf(" %s", pd.descricao);
                            printf("Digite o laboratorio do produto: ");
                            scanf(" %s", pd.laboratorio);
                            printf("Digite o tipo do produto: ");
                            scanf(" %s", pd.tipo);
                            printf("Digite o valor do produto: ");
                            scanf("%f", &pd.valor);
                            printf("Digite o desconto do produto: ");
                            scanf("%f", &pd.desconto);
                            printf("Digite o lote do produto: ");
                            scanf("%d", &pd.lote);
                            printf("Digite a validade do produto (dia mes ano): ");
                            scanf("%d %d %d", &pd.validade.dia, &pd.validade.mes, &pd.validade.ano);
                            fwrite(&pd, sizeof(Produto), 1, ptProduto);
                            printf("Produto cadastrado com sucesso!\n");
                        }else{
                            fseek(ptProduto, pos, 0);
                            fread(&pd, sizeof(Produto), 1, ptProduto);
                            printf("Produto ja existe!\n");
                        }
                        printf("Deseja cadastrar outro produto? (s/n):\n> ");
                        scanf(" %c", &resp);
                    } while (resp == 's' || resp == 'S');
                }
                fclose(ptProduto);
                system("pause");
                break;
            case 2:
                printf("\nDeletar Produto\n");
                ptProduto = fopen("produtos.bin", "rb+");
                if(ptProduto == NULL){
                    printf("Erro ao abrir o arquivo de produtos.\n");
                    system("pause");
                }else{
                    system("cls");
                    printf("Digite o codigo do produto a ser deletado: ");
                    scanf("%d", &cod);
                    if(cod != 0){
                        pos = buscaCodProduto(ptProduto, cod);
                        if(pos == -1){
                            printf("Produto nao encontrado!\n");
                            system("pause");
                        }else{
                            fseek(ptProduto, pos, 0);
                            fread(&pd, sizeof(Produto), 1, ptProduto);
                            printf("\n---------------------------------\n");
                            printf("Codigo: %d\n", pd.cod);
                            printf("Produto: %s\n", pd.nome);
                            printf("Descricao: %s\n", pd.descricao);
                            printf("Laboratorio: %s\n", pd.laboratorio);
                            printf("Tipo: %s\n", pd.tipo);
                            printf("Valor: %.2f\n", pd.valor);
                            printf("Desconto: %.2f\n", pd.desconto);
                            printf("Lote: %d\n", pd.lote);
                            printf("Validade: %d/%d/%d\n", pd.validade.dia, pd.validade.mes, pd.validade.ano);
                            printf("---------------------------------\n");
                            printf("Tem certeza que deseja deletar este produto? (s/n):\n> ");
                            scanf(" %c", &resp);
                            if(resp == 's' || resp == 'S'){
                               
                                ptTempProduto = fopen("temp.bin", "wb");
                                rewind(ptProduto);
                                fread(&pd, sizeof(Produto), 1, ptProduto);
                                while(!feof(ptProduto)){
                                    if(pd.cod != cod){
                                        fwrite(&pd, sizeof(Produto), 1, ptTempProduto);
                                    }
                                    fread(&pd, sizeof(Produto), 1, ptProduto);
                                }
                                fclose(ptProduto);
                                fclose(ptTempProduto);
                                remove("produtos.bin");
                                rename("temp.bin", "produtos.bin");
                                printf("Produto deletado com sucesso!\n");
                            }
                        }
                    }
                }
                system("pause");
                break;
            case 3:
                system("cls");
                printf("\nEditar Produto\n");
                ptProduto = fopen("produtos.bin", "rb+");
                if (ptProduto == NULL){
                    printf("Erro ao abrir o arquivo de produtos.\n");
                    system("pause");
                }else{
                    printf("Digite o codigo do produto a ser editado: ");
                    scanf("%d", &pd.cod);

                    while (pd.cod != 0 ){
                        pos = buscaCodProduto(ptProduto, pd.cod);
                        if (pos == -1){
                            printf("Produto nao encontrado!\n");
                            system("pause");
                        }else{
                            fseek(ptProduto, pos, 0);
                            fread(&pd, sizeof(Produto), 1, ptProduto);

                            printf("\n---------------------------------\n");
                            printf("Codigo: %d\n", pd.cod);
                            printf("Produto: %s\n", pd.nome);
                            printf("Descricao: %s\n", pd.descricao);
                            printf("Laboratorio: %s\n", pd.laboratorio);
                            printf("Tipo: %s\n", pd.tipo);
                            printf("Valor: %.2f\n", pd.valor);
                            printf("Desconto: %.2f\n", pd.desconto);
                            printf("Lote: %d\n", pd.lote);
                            printf("Validade: %d/%d/%d\n", pd.validade.dia, pd.validade.mes, pd.validade.ano);
                            printf("---------------------------------\n");
                            printf("Deseja alterar: ");
                            printf("\n1: Nome");
                            printf("\n2: Descricao");
                            printf("\n3: Laboratorio");
                            printf("\n4: Tipo");
                            printf("\n5: Valor");
                            printf("\n6: Desconto");
                            printf("\n7: Lote");
                            printf("\n8: Validade");
                            printf("\n> ");
                            scanf("%d", &op);

                            switch(op){
                                case 1:
                                    printf("Digite o novo nome: \n> ");
                                    scanf(" %s", pd.nome);
                                    fseek(ptProduto, pos, 0);
                                    fwrite(&pd, sizeof(Produto), 1, ptProduto);
                                    printf("Nome alterado com sucesso!\n");
                                break;
                                case 2:
                                    printf("Digite a nova descricao: \n> ");
                                    scanf(" %s", pd.descricao);
                                    fseek(ptProduto, pos, 0);
                                    fwrite(&pd, sizeof(Produto), 1, ptProduto);
                                    printf("Descricao alterada com sucesso!\n");
                                break;
                                case 3:
                                    printf("Digite o novo laboratorio: \n> ");
                                    scanf(" %s", pd.laboratorio);
                                    fseek(ptProduto, pos, 0);
                                    fwrite(&pd, sizeof(Produto), 1, ptProduto);
                                    printf("Laboratorio alterado com sucesso!\n");
                                break;
                                case 4:
                                    printf("Digite o novo tipo: \n> ");
                                    scanf(" %s", pd.tipo);
                                    fseek(ptProduto, pos, 0);
                                    fwrite(&pd, sizeof(Produto), 1, ptProduto);
                                    printf("Tipo alterado com sucesso!\n");
                                break;
                                case 5:
                                    printf("Digite o novo valor: \n> ");
                                    scanf("%f", &pd.valor);
                                    fseek(ptProduto, pos, 0);
                                    fwrite(&pd, sizeof(Produto), 1, ptProduto);
                                    printf("Valor alterado com sucesso!\n");
                                break;
                                case 6:
                                    printf("Digite o novo desconto: \n> ");
                                    scanf("%f", &pd.desconto);
                                    fseek(ptProduto, pos, 0);
                                    fwrite(&pd, sizeof(Produto), 1, ptProduto);
                                    printf("Desconto alterado com sucesso!\n");
                                break;
                                case 7:
                                    printf("Digite o novo lote: \n> ");
                                    scanf("%d", &pd.lote);
                                    fseek(ptProduto, pos, 0);
                                    fwrite(&pd, sizeof(Produto), 1, ptProduto);
                                    printf("Lote alterado com sucesso!\n");
                                break;
                                case 8:
                                    printf("Digite a nova validade (dia mes ano): \n> ");
                                    scanf("%d %d %d", &pd.validade.dia, &pd.validade.mes, &pd.validade.ano);
                                    fseek(ptProduto, pos, 0);
                                    fwrite(&pd, sizeof(Produto), 1, ptProduto);
                                    printf("Validade alterada com sucesso!\n");
                                break;
                                default:
                                    printf("Opcao invalida!\n");
                                    break;
                            }
                        }
                        printf("Digite o codigo do produto a ser editado: ");
                        scanf("%d", &pd.cod);
                    }
                }
                fclose(ptProduto);
                system("pause");
                break;
            case 4:
                printf("\nVender Produto\n");
                
                // --Abrir o arquivo binario de produtos
                //     - se Produto existe (cod)
                //     - se o produto tem estoque
                //         - Criar arquivo produtosVendidos
                //             - Adicinar isso produto, vendedor, dataDeVenda, quantidade, valorTotal, valorUnitario....
                //         - Subtrair a quantidade do produto no arquivo de produtos
                //             ( exclusão
                //                 - Criar um arquivo temporarioProdutos passar todos os produtos menos o que está sendo alterado
                //                 - Depois cadastrar esse produto dnv com quantidade menor
                //                 - apaga o binario de produtos
                //                 - Renomeia o temporario para produtos 
                //             )

                exibirProduto();

                int cod, qtdVenda;

                // --Abrir o arquivo binario de produtos
                ptProduto = fopen("produtos.bin", "rb+");
                if(ptProduto == NULL) {
                    printf("Erro ao abrir produtos.bin\n");
                    system("pause");
                } else {
                    printf("Insira um codigo: ");
                    scanf("%d", &cod);
                    Produto pd;

                    // - se Produto existe (cod)
                    int pos = buscaCodProduto(ptProduto, cod);
                    if (pos == -1) {
                        printf("Código do produto inexistente\n");
                        system("pause");
                    } else {
                        //- se o produto tem estoque
                        /*
                             Fseek leva o ponteiro do arquivo na posição correta
                             SEEK_SET  
                             SEEK_CUR  
                             SEEK_END 
                        */

                        fseek(ptProduto, pos, SEEK_SET);

                        fread(&pd, sizeof(Produto), 1, ptProduto);

                        if(pd.quantidade < 1) {
                            printf("\nEsse produto não tem estoque!\n");
                            system("pause");
                        } else {
                            do {
                                printf("\nO produto possui %d unidades. Quantos deseja vender?\n", pd.quantidade);
                                scanf("%d", &qtdVenda);

                                if(pd.quantidade < qtdVenda) {
                                    printf("\nDigite uma quantidade válida!\n");
                                }
                            } while(pd.quantidade < qtdVenda);

                            ProdutoVendido pv;

                            pv.cod = pd.cod;
                            pv.quantidadeVendida = qtdVenda;
                            strcpy(pv.nome, pd.nome);
                            strcpy(pv.laboratorio, pd.laboratorio);
                            strcpy(pv.tipo, pd.tipo);
                            pv.valorVenda = (pd.valor * qtdVenda) * (1 - pd.desconto);
                            strcpy(pv.formaPagamento, ""); 

                            time_t t = time(NULL);
                            struct tm tm = *localtime(&t);
                            pv.venda.dia = tm.tm_mday;
                            pv.venda.mes = tm.tm_mon + 1;
                            pv.venda.ano = tm.tm_year + 1900;

                            FILE *ptProdutosVendidos;
                            ptProdutosVendidos = fopen("produtosVendidos.bin", "ab+");
                            if(ptProdutosVendidos == NULL) {
                                printf("Erro ao abrir produtosVendidos.bin\n");
                                system("pause");
                            } else {
                                fwrite(&pv, sizeof(ProdutoVendido), 1, ptProdutosVendidos);
                                fclose(ptProdutosVendidos);
                            }

                            pd.quantidade -= qtdVenda;

                            fseek(ptProduto, pos, SEEK_SET);
                            fwrite(&pd, sizeof(Produto), 1, ptProduto);

                            printf("\nVenda realizada com sucesso!\n");
                        }
                    }
                    fclose(ptProduto);
                    system("pause");
                }
                break;
            case 5:
                exibirProduto();
                break;
            case 6:
                controlarEstoque();
                break;
            case 7:
                verificarPorTipoProduto();
                break;
            case 8:
                printf("\nVoltando ao menu principal.\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
            }
            break;
        case 3:
            printf("\nRelatórios\n");
            printf("1 - Listar todos os produtos\n");
            printf("2 - Listar produtos por laboratorio\n");
            printf("3 - Listar produtos por tipo\n");
            printf("4 - Listar produtos com estoque baixo\n");
            printf("5 - Listar produtos em promocao\n");
            printf("6 - Listar produtos por faixa de preço\n");
            printf("7 - Relatório de vendas\n");
            printf("8 - Voltar ao menu principal\n");
            printf("> ");
            scanf("%d", &submenu);
            system("cls");

            switch (submenu){
            case 1:
                printf("\nRelatório: Todos os produtos\n");
                ptProduto = fopen("produtos.bin", "rb");
                if (ptProduto == NULL){
                    printf("Erro ao abrir o arquivo de produtos.\n");
                    system("pause");
                }else{
                    while (fread(&pd, sizeof(Produto), 1, ptProduto)){
                        printf("\n---------------------------------\n");
                        printf("Codigo: %d\n", pd.cod);
                        printf("Produto: %s\n", pd.nome);
                        printf("Descricao: %s\n", pd.descricao);
                        printf("Laboratorio: %s\n", pd.laboratorio);
                        printf("Tipo: %s\n", pd.tipo);
                        printf("Valor: %.2f\n", pd.valor);
                        printf("Desconto: %.2f\n", pd.desconto);
                        printf("Lote: %d\n", pd.lote);
                        printf("Validade: %d/%d/%d\n", pd.validade.dia, pd.validade.mes, pd.validade.ano);
                        printf("---------------------------------\n");
                    }
                    fclose(ptProduto);
                }
                system("pause");
                break;

            case 2:
                printf("\nRelatório: Produtos por laboratório\n");
                break;

            case 3:
                printf("\nRelatório: Produtos por tipo\n");
                break;

            case 4:
                printf("\nRelatório: Estoque baixo\n");
                break;

            case 5:
                printf("\nRelatório: Produtos em promoção\n");
                break;

            case 6:
                printf("\nRelatório: Faixa de preço\n");
                break;

            case 7:
                printf("\nRelatório: Vendas realizadas\n");
                // gerarRelatorioVendas();
                break;
            case 8:
                printf("\nVoltando ao menu principal...\n");
                break;

            default:
                printf("\nOpcao inválida!\n");
                
            }

            system("pause");
            break;
        case 4:
            printf("\nGerenciar laboratórios\n");
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
void sistemaCliente(Produto *produtos, int *produtosTopo){
    FILE *ptProduto;
    Produto pd;

    int menu, submenu;

    system("cls");
    printf("\nVoce selecionou o sistema de cliente!\n");

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
                ptProduto = fopen("produtos.bin", "rb");
                if (ptProduto == NULL){
                    printf("Erro ao abrir o arquivo de produtos.\n");
                    system("pause");
                }else {
                    printf("\nCatálogo de Produtos:\n");
                    while (fread(&pd, sizeof(Produto), 1, ptProduto)){
                        printf("\n---------------------------------\n");
                        printf("Codigo: %d\n", pd.cod);
                        printf("Produto: %s\n", pd.nome);
                        printf("Descricao: %s\n", pd.descricao);
                        printf("Laboratorio: %s\n", pd.laboratorio);
                        printf("Tipo: %s\n", pd.tipo);
                        printf("Valor: %.2f\n", pd.valor);
                        printf("Desconto: %.2f\n", pd.desconto);
                        printf("Lote: %d\n", pd.lote);
                        printf("Validade: %d/%d/%d\n", pd.validade.dia, pd.validade.mes, pd.validade.ano);
                        printf("---------------------------------\n");
                    }
                    fclose(ptProduto);
                }
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
void gerenciarLaboratorios(Produto *produtos){
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
            printf("\nRelatório de venda por laboratórios\n");
            system("pause");
            break;
        case 2:
            printf("\nVerificar estoque de produtos por laboratório\n");
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
            printf("\nRelatório de venda por tipo de produto\n");
            system("pause");
            break;
        case 2:
            printf("\nControle de estoque por tipo de produto\n");
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
            printf("\nRelatório de venda por categoria de produto\n");
            system("pause");
            break;
        case 2:
            printf("\nControle de estoque por categoria de produto\n");
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


void controlarEstoque() {
    FILE *ptProduto = fopen("produtos.bin", "rb");
    Produto pd;
    if (ptProduto == NULL) {
        printf("Erro ao abrir o arquivo de produtos.\n");
        system("pause");
        return;
    }

    printf("\nControle de Estoque:\n");
    int encontrou = 0;
    while (fread(&pd, sizeof(Produto), 1, ptProduto) == 1) {
        printf("---------------------------------\n");
        printf("Codigo: %d\n", pd.cod);
        printf("Produto: %s\n", pd.nome);
        printf("Quantidade em estoque: %d\n", pd.quantidade);
        printf("---------------------------------\n");
        encontrou = 1;
    }
    if (!encontrou) {
        printf("Nenhum produto cadastrado.\n");
    }
    fclose(ptProduto);
    system("pause");
}

void verificarPorTipoProduto() {
    FILE *ptProduto = fopen("produtos.bin", "rb");
    Produto pd;
    char tipoConsulta[100];

    if (ptProduto == NULL) {
        printf("Erro ao abrir o arquivo de produtos.\n");
        system("pause");
        return;
    }

    printf("\nDigite o tipo do produto a pesquisar: ");
    scanf(" %99s", tipoConsulta);

    printf("\nProdutos do tipo '%s':\n", tipoConsulta);
    int encontrou = 0;

    while (fread(&pd, sizeof(Produto), 1, ptProduto) == 1) {
        if (strcmp(pd.tipo, tipoConsulta) == 0) {
            printf("---------------------------------\n");
            printf("Codigo: %d\n", pd.cod);
            printf("Produto: %s\n", pd.nome);
            printf("Descricao: %s\n", pd.descricao);
            printf("Laboratorio: %s\n", pd.laboratorio);
            printf("Valor: %.2f\n", pd.valor);
            printf("Quantidade em estoque: %d\n", pd.quantidade);
            printf("---------------------------------\n");
            encontrou = 1;
        }
    }
    if (!encontrou) {
        printf("Nenhum produto encontrado para o tipo informado.\n");
    }
    fclose(ptProduto);
    system("pause");
}

int main(){

    criarAdminInicial(); 
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
            if (loginAdministrador()) {
                sistemaAdmin("admin", produtos, &produtosTopo);
            } else {
                printf("\nUsuario ou senha incorretos!\n");
                system("pause");
            }
            break;
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
    char cpfVenda[15];
    Dia venda;
} ProdutoVendido;

typedef struct{
    char usuario[200], senha[200];
} Administrador;

typedef struct{
    char nome[200], cpf[15], telefone[15], endereco[255], email[100];
    Dia dataCadastro;
} Cliente;

// Funções de busca de produto pelo cod
int buscaCodProduto(FILE *ptProduto, int cod){
    Produto p;
    rewind(ptProduto);
    fread(&p, sizeof(Produto), 1, ptProduto);
    while (!feof(ptProduto) && p.cod != cod){
        fread(&p, sizeof(Produto), 1, ptProduto);
    }
    if (!feof(ptProduto)){
        return ftell(ptProduto) - sizeof(Produto);
    }else{
        return -1;
    }
}

// Funções de busca de cliente pelo nome
int buscaCliente(FILE *ptClientes, char cpf[]){
    Cliente cl;
    rewind(ptClientes);
    fread(&cl, sizeof(Cliente), 1, ptClientes);
    while (!feof(ptClientes) && strcmp(cl.cpf, cpf) != 0){
        fread(&cl, sizeof(Cliente), 1, ptClientes);
    }
    if (!feof(ptClientes)){
        return ftell(ptClientes) - sizeof(Cliente);
    }else{
        return -1;
    }
}

// Funções de administrador de busca de administrador
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

void buscarVendasPorCliente(char cpfCliente[]) {
    FILE *ptProdutosVendidos;
    ProdutoVendido pv;
    int encontrou = 0;

    ptProdutosVendidos = fopen("produtosVendidos.bin", "rb");
    if (ptProdutosVendidos == NULL) {
        printf("Erro ao abrir produtosVendidos.bin\n");
        return;
    }

    printf("\nVendas: %s \n", cpfCliente);

    while (fread(&pv, sizeof(ProdutoVendido), 1, ptProdutosVendidos)) {
        
        if (strcmp(pv.cpfVenda, cpfCliente) == 0) {
            encontrou = 1;

            printf("\n------------------------------\n");
            printf("Produto: %s\n", pv.nome);
            printf("Código: %d\n", pv.cod);
            printf("Quantidade: %d\n", pv.quantidadeVendida);
            printf("Laboratório: %s\n", pv.laboratorio);
            printf("Tipo: %s\n", pv.tipo);
            printf("Valor da venda: R$ %.2f\n", pv.valorVenda);
            printf("Data: %02d/%02d/%04d\n",
                   pv.venda.dia, pv.venda.mes, pv.venda.ano);
        }
    }

    if (!encontrou) {
        printf("\nNenhuma venda encontrada para este CPF.\n");
    }

    fclose(ptProdutosVendidos);
}

void exibirProduto() {
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
                printf("Quantidade: %d\n", pd.quantidade);
                printf("Desconto: %.2f\n", pd.desconto);
                printf("Lote: %d\n", pd.lote);
                printf("Validade: %d/%d/%d\n", pd.validade.dia, pd.validade.mes, pd.validade.ano);
                printf("---------------------------------\n");
            }
            fclose(ptProduto);
        }
    system("pause");
}

int loginAdministrador() {
    FILE *ptAdm; 
    char usuario[200], senha[200];
    Administrador adm;

    printf("\nDigite o usuario: ");
    fgets(usuario, 200, stdin);

    printf("Digite a senha: ");
    fgets(senha, 200, stdin);

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

// Controle do estoque
void controlarEstoque() {
    FILE *ptProduto = fopen("produtos.bin", "rb");
    Produto pd;
    int encontrou = 0;
    
    if (ptProduto == NULL) {
        printf("Erro ao abrir o arquivo de produtos.\n");
        system("pause");
        return;
    }

    printf("\nControle de Estoque:\n");
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

// Tipo de produto
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
    fgets(tipoConsulta, 100, stdin);
    /* scanf(" %99s", tipoConsulta); */

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

// Função principal do sistema de administrador
void sistemaAdmin(char *login, Produto *produtos, int *produtosTopo){
    FILE *ptAdm;
    FILE *ptProduto;
    FILE *ptTempProduto;
    FILE *ptTempAdm;
    FILE *ptProdutosVendidos;
    FILE *ptClientes;

    Administrador adm;
    Produto pd;
    ProdutoVendido pv;
    Cliente cl;

    int menu, submenu, pos = 0, op;
    int cod;
    int qtdVenda;

    char resp;
    char usuario[200], cpfCliente[15];

    system("cls");
    printf("\nVoce selecionou o sistema de Administrador!\n");
    do{
        printf("\n1: Administradores\n");
        printf("2: Gerenciar Produtos\n");
        printf("3: Relatórios\n");
        printf("4: Gerenciar Laboratórios\n");
        printf("5: Gerenciar Clientes\n");
        printf("6: Voltar para Login\n");
        printf("> ");
        scanf("%d", &menu);
        system("cls");
        switch (menu){
            // Administradores
            case 1:{
                do{
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
                            if (ptAdm == NULL){
                                printf("Erro ao criar o arquivo de administradores.\n");
                                system("pause");
                            }
                            else{
                                do{
                                    printf("Digite o nome do novo administrador: ");
                                    fgets(adm.usuario, 200, stdin);
                                    pos = buscaADM(ptAdm, adm.usuario);
                                    if (pos == -1){
                                        printf("Digite a senha do novo administrador: ");
                                        fgets(adm.senha, 200, stdin);
                                        fwrite(&adm, sizeof(Administrador), 1, ptAdm);
                                        printf("Administrador cadastrado com sucesso!\n");
                                    }
                                    else{
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
                            if (ptAdm == NULL){
                                printf("Erro ao abrir o arquivo de administradores.\n");
                                system("pause");
                            }
                            else{
                                printf("\nDeletar Administrador\n");
                                printf("Digite o nome do administrador a ser deletado: ");
                                fgets(usuario, 200, stdin);
                                if (strcmp(usuario, "/0") != 0){
                                    pos = buscaADM(ptAdm, usuario);
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
                                        printf("Tem certeza que deseja deletar este administrador? (s/n):\n> ");
                                        scanf(" %c", &resp);
                                        if (resp == 's' || resp == 'S'){
                                            ptTempAdm = fopen("temp.bin", "wb");
                                            rewind(ptAdm);
                                            fread(&adm, sizeof(Administrador), 1, ptAdm);
                                            while (!feof(ptAdm)){
                                                if (strcmp(adm.usuario, usuario) != 0){
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
                                    printf("Administrador deletado com sucesso!\n");
                                }
                            }
                            break;
                        }
                        case 3:{
                            printf("\nEditar Administrador\n");
                            ptAdm = fopen("administradores.bin", "rb+");
                            if (ptAdm == NULL){
                                printf("Erro ao abrir o arquivo de administradores.\n");
                                system("pause");
                            } else {
                                do {
                                    printf("Digite o nome do administrador a ser editado (0 para sair): ");
                                    fgets(adm.usuario, 200, stdin);
                                    if (strcmp(adm.usuario, "0") == 0) {
                                        break;
                                    }
                                    pos = buscaADM(ptAdm, adm.usuario);
                                    if (pos == -1){
                                        printf("Administrador nao encontrado!\n");
                                    } else {
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
                                            case 1:{
                                                printf("Digite o novo usuario: \n> ");
                                                fgets(adm.usuario, 200, stdin);
                                                fseek(ptAdm, pos, 0);
                                                fwrite(&adm, sizeof(Administrador), 1, ptAdm);
                                                printf("Usuario alterado com sucesso!\n");
                                            break;
                                            }
                                            case 2:{
                                                printf("Digite a nova senha: \n> ");
                                                fgets(adm.senha, 200, stdin);
                                                fseek(ptAdm, pos, 0);
                                                fwrite(&adm, sizeof(Administrador), 1, ptAdm);
                                                printf("Senha alterada com sucesso!\n");
                                            break;
                                            }
                                        }
                                    }
                                    printf("Administrador editado com sucesso!\n");
                                    system("pause");
                                } while (1);
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
                    } 
                }while(submenu != 5);
                break;
            }
            // Gerenciar Produtos
            case 2:{
                do{
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
                        // Cadastrar Produto
                        case 1:{
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
                                        fgets(pd.nome, 200, stdin);
                                        printf("Digite a descricao do produto: ");
                                        fgets(pd.descricao, 200, stdin);
                                        printf("Digite o laboratorio do produto: ");
                                        fgets(pd.laboratorio, 200, stdin);
                                        printf("Digite o tipo do produto: ");
                                        fgets(pd.tipo, 100, stdin);
                                        printf("Digite o valor do produto: ");
                                        scanf("%f", &pd.valor);
                                        printf("Digite a quantidade do produto: ");
                                        scanf("%d", &pd.quantidade);
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
                        }
                        // Deletar Produto
                        case 2:{
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
                                        printf("Quantidade: %d\n", pd.quantidade);
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
                        }
                        // Editar Produto
                        case 3:{
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
                                        printf("Quantidade: %d\n", pd.quantidade);
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
                                        printf("\n6: Quantidade");
                                        printf("\n7: Desconto");
                                        printf("\n8: Lote");
                                        printf("\n9: Validade");
                                        printf("\n> ");
                                        scanf("%d", &op);
                                        switch(op){
                                            case 1:
                                                printf("Digite o novo nome: \n> ");
                                                fgets(pd.nome, 200, stdin);
                                                fseek(ptProduto, pos, 0);
                                                fwrite(&pd, sizeof(Produto), 1, ptProduto);
                                                printf("Nome alterado com sucesso!\n");
                                            break;
                                            case 2:
                                                printf("Digite a nova descricao: \n> ");
                                                fgets(pd.descricao, 200, stdin);
                                                fseek(ptProduto, pos, 0);
                                                fwrite(&pd, sizeof(Produto), 1, ptProduto);
                                                printf("Descricao alterada com sucesso!\n");
                                            break;
                                            case 3:
                                                printf("Digite o novo laboratorio: \n> ");
                                                fgets(pd.laboratorio, 200, stdin);
                                                fseek(ptProduto, pos, 0);
                                                fwrite(&pd, sizeof(Produto), 1, ptProduto);
                                                printf("Laboratorio alterado com sucesso!\n");
                                            break;
                                            case 4:
                                                printf("Digite o novo tipo: \n> ");
                                                fgets(pd.tipo, 100, stdin);
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
                                                printf("Digite a nova quantidade: \n> ");
                                                scanf("%d", &pd.quantidade);
                                                fseek(ptProduto, pos, 0);
                                                fwrite(&pd, sizeof(Produto), 1, ptProduto);
                                                printf("Quantidade alterada com sucesso!\n");
                                            break;
                                            case 7:
                                                printf("Digite o novo desconto: \n> ");
                                                scanf("%f", &pd.desconto);
                                                fseek(ptProduto, pos, 0);
                                                fwrite(&pd, sizeof(Produto), 1, ptProduto);
                                                printf("Desconto alterado com sucesso!\n");
                                            break;
                                            case 8:
                                                printf("Digite o novo lote: \n> ");
                                                scanf("%d", &pd.lote);
                                                fseek(ptProduto, pos, 0);
                                                fwrite(&pd, sizeof(Produto), 1, ptProduto);
                                                printf("Lote alterado com sucesso!\n");
                                            break;
                                            case 9:
                                                printf("Digite a nova validade (dia mes ano): \n> ");
                                                scanf("%d %d %d", &pd.validade.dia, &pd.validade.mes, &pd.validade.ano);
                                                fseek(ptProduto, pos, 0);
                                                fwrite(&pd, sizeof(Produto), 1, ptProduto);
                                                printf("Validade alterada com sucesso!\n");
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
                        }
                        // Vender Produto
                        case 4: {
                            ptProduto = fopen("produtos.bin", "rb+");
                            if(ptProduto == NULL) {
                                printf("Erro ao abrir produtos.bin\n");
                                system("pause");
                            }

                            ptClientes = fopen("clientes.bin", "rb");
                            if(ptClientes == NULL) {
                                printf("Erro ao abrir clientes.bin\n");
                                fclose(ptProduto);
                            }

                            printf("Digite o CPF do cliente:\n> ");
                            fgets(cpfCliente, 15, stdin);

                            pos = buscaCliente(ptClientes, cpfCliente);
                            if(pos == -1){
                                printf("Cliente não encontrado\n");
                                fclose(ptClientes);
                                fclose(ptProduto);
                                system("pause");
                            }

                            exibirProduto();

                            printf("Insira um codigo do produto:\n> ");
                            scanf("%d", &cod);

                            pos = buscaCodProduto(ptProduto, cod);
                            if (pos == -1) {
                                printf("Código do produto inexistente.\n");
                                fclose(ptClientes);
                                fclose(ptProduto);
                                system("pause");
                            }

                            fseek(ptProduto, pos, 0);
                            fread(&pd, sizeof(Produto), 1, ptProduto);

                            if (pd.quantidade < 1) {
                                printf("\nEsse produto não tem estoque!\n");
                                fclose(ptClientes);
                                fclose(ptProduto);
                                system("pause");
                            }

                            do {
                                printf("\nO produto possui %d unidades. Quantos deseja vender: ", pd.quantidade);
                                scanf("%d", &qtdVenda);

                                if (qtdVenda <= 0 || qtdVenda > pd.quantidade) {
                                    printf("\nQuantidade invalida! Digite novamente.\n");
                                }
                            } while (qtdVenda <= 0 || qtdVenda > pd.quantidade);

                            ptProdutosVendidos = fopen("produtosVendidos.bin", "ab+");
                            if (ptProdutosVendidos == NULL) {
                                printf("Erro ao abrir produtosVendidos.bin\n");
                                fclose(ptClientes);
                                fclose(ptProduto);
                            }
                            strcpy(pv.cpfVenda, cpfCliente);
                            pv.cod = pd.cod;
                            pv.quantidadeVendida = qtdVenda;
                            strcpy(pv.nome, pd.nome);
                            strcpy(pv.laboratorio, pd.laboratorio);
                            strcpy(pv.tipo, pd.tipo);
                            pv.valorVenda = (pd.valor * qtdVenda) * (1 - pd.desconto); 
                            strcpy(pv.formaPagamento, "Nao informado");

                            time_t t = time(NULL);
                            struct tm tm = *localtime(&t);
                            pv.venda.dia = tm.tm_mday;
                            pv.venda.mes = tm.tm_mon + 1;
                            pv.venda.ano = tm.tm_year + 1900;

                            fwrite(&pv, sizeof(ProdutoVendido), 1, ptProdutosVendidos);
                            fclose(ptProdutosVendidos);

                            pd.quantidade -= qtdVenda;

                            fseek(ptProduto, pos, 0);
                            fwrite(&pd, sizeof(Produto), 1, ptProduto);

                            fclose(ptClientes);
                            fclose(ptProduto);

                            printf("\nVenda realizada com sucesso!\n");
                            system("pause");
                            break;
                        }   
                        // Exibir Produto
                        case 5:{
                            exibirProduto();
                            break;
                        }
                        // Controlar Estoque
                        case 6:{
                            controlarEstoque();
                            break;
                        }
                        // Verificar por Tipo de Produto
                        case 7:{
                            verificarPorTipoProduto();
                            break;
                        }
                        // Voltar para o Menu
                        case 8:{
                            printf("\nVoltando ao menu principal.\n");
                            break;
                        }
                    }
                }while(submenu != 8);
                break;
            }
            // Relatórios
            case 3:{
                do{
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
                        case 1:{
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
                            
                        }
                        case 2:{
                            printf("\nRelatório: Produtos por laboratório\n");
                            break;
                        }
                        case 3:{
                            printf("\nRelatório: Produtos por tipo\n");
                            verificarPorTipoProduto();
                            break;
                        }
                        case 4:{
                            printf("\nRelatório: Estoque baixo\n");
                            break;
                        }
                        case 5:{
                            printf("\nRelatório: Produtos em promoção\n");
                            break;
                        }
                        case 6:{
                            printf("\nRelatório: Faixa de preço\n");
                            break;
                        }
                        case 7:{
                            printf("\nRelatório: Vendas realizadas\n");
                            printf("\nDigite o CPF do cliente para consultar vendas:\n> ");
                            /* scanf("%s", cpfCliente); */
                            fgets(cpfCliente, 15, stdin);
                            
                            buscarVendasPorCliente(cpfCliente);
                            
                            system("pause");
                            break;
                        }
                        case 8:{
                            printf("\nVoltando ao menu principal...\n");
                            break;
                        }
                        system("pause");    
                    }
                }while(submenu != 8);
                break;
            }
            // Gerenciar tipos de produtos
            case 4:{
                printf("\nGerenciar laboratórios\n");
                system("pause");
                break;
            }
            // Gerenciar clientes
            case 5:{
                ptClientes = fopen("clientes.bin", "rb");
                if (ptClientes == NULL){
                    printf("Erro ao abrir o arquivo de clientes.\n");
                    system("pause");
                }else{
                    printf("\nLista de Clientes:\n");
                    while (fread(&cl, sizeof(Cliente), 1, ptClientes)){
                        printf("\n---------------------------------\n");
                        printf("Nome: %s\n", cl.nome);
                        printf("CPF: %s\n", cl.cpf);
                        printf("Telefone: %s\n", cl.telefone);
                        printf("Endereço: %s\n", cl.endereco);
                        printf("Email: %s\n", cl.email);
                        printf("Data de Cadastro: %d/%d/%d\n", cl.dataCadastro.dia, cl.dataCadastro.mes, cl.dataCadastro.ano);
                        printf("---------------------------------\n");
                    }
                    fclose(ptClientes);
                }
                system("pause");
                break;
            }
            // Voltar para o Login
            case 6:{
                printf("\nVoltando para o login.\n");
                break;
            }
        }
    } while (menu != 6);
}

// Menu do sistema de cliente
void sistemaCliente(Produto *produtos, int *produtosTopo){
    FILE *ptProduto;
    FILE *ptProdutosVendidos;
    FILE *ptClientes;

    Produto pd;
    Cliente cliente;
    ProdutoVendido pv;

    int cod, qtdVenda;
    int pos = 0;
    int menu, submenu;
    char resp, cpfCliente[15];

    system("cls");
    printf("\nVoce selecionou o sistema de cliente!\n");

    do{
        printf("\n1: Cadastro\n");
        printf("2: Exibir produtos disponiveis\n");
        printf("3: Comprar produtos\n");
        printf("4: Ver compras realizadas\n");
        printf("5: Voltar para Login\n");
        printf("> ");
        scanf("%d", &menu);
        system("cls");

        switch (menu){
            case 1:{
                printf("\nCadastro de cliente\n");
                ptClientes = fopen("clientes.bin", "ab+");
                if (ptClientes == NULL){
                    printf("Erro ao criar o arquivo de clientes.\n");
                    system("pause");
                }else{
                    printf("Digite seu cpf: ");
                    fgets(cliente.cpf, 15, stdin);
                    pos = buscaCliente(ptClientes, cliente.cpf);
                    if(pos == -1){
                        printf("Digite seu nome: ");
                        fgets(cliente.nome, 100, stdin);
                        printf("Digite seu telefone: ");
                        fgets(cliente.telefone, 15, stdin);
                        printf("Digite seu endereco: ");
                        fgets(cliente.endereco, 100, stdin);
                        printf("Digite seu email: ");
                        fgets(cliente.email, 100, stdin);
                        time_t t = time(NULL);
                        struct tm tm = *localtime(&t);
                        cliente.dataCadastro.dia = tm.tm_mday;
                        cliente.dataCadastro.mes = tm.tm_mon + 1;
                        cliente.dataCadastro.ano = tm.tm_year + 1900;
                        fwrite(&cliente, sizeof(Cliente), 1, ptClientes);
                        printf("Cliente cadastrado com sucesso!\n");
                    }else{
                        fseek(ptClientes, pos, 0);
                        fread(&cliente, sizeof(Cliente), 1, ptClientes);
                        printf("Cliente ja existe!\n");
                    }
                    fclose(ptClientes);
                }
                system("pause");
                break;
            }
            case 2:{
                exibirProduto();
                break;
            }
            case 3: {
                ptProduto = fopen("produtos.bin", "rb+");
                if (ptProduto == NULL) {
                    printf("Erro ao abrir produtos.bin\n");
                    system("pause");
                    break;
                }
                do {
                    ptClientes = fopen("clientes.bin", "rb");
                    if (ptClientes == NULL) {
                        printf("Erro ao abrir clientes.bin\n");
                        fclose(ptProduto);
                        system("pause");
                    }
                    printf("Digite o seu CPF:\n> ");
                    fgets(cpfCliente, 15, stdin);
                    pos = buscaCliente(ptClientes, cpfCliente);
                    fclose(ptClientes);
                    if (pos == -1) {
                        printf("Cliente não encontrado!\n");
                        system("pause");
                    }
                    exibirProduto();
                    printf("Digite o código do produto que deseja comprar: ");
                    scanf("%d", &cod);
                    // Busca produto
                    pos = buscaCodProduto(ptProduto, cod);
                    if (pos == -1) {
                        printf("Codigo de produto invalido!\n");
                        system("pause");
                    }
                    // Ir até a posição correta do registro
                    fseek(ptProduto, pos, 0);
                    fread(&pd, sizeof(Produto), 1, ptProduto);
                    if (pd.quantidade < 1) {
                        printf("Produto sem estoque!\n");
                        system("pause");
                    }
                    do {
                        printf("\nO produto possui %d unidades. Quantas deseja comprar: ", pd.quantidade);
                        scanf("%d", &qtdVenda);
                        if (qtdVenda > pd.quantidade) {
                            printf("Quantidade inválida! Tente novamente.\n");
                        }
                    } while (qtdVenda > pd.quantidade);
                    // Criar arquivo de vendas
                    ptProdutosVendidos = fopen("produtosVendidos.bin", "ab");
                    if (ptProdutosVendidos == NULL) {
                        printf("Erro ao abrir o arquivo\n");
                        system("pause");
                    }
                    // Preenche struct de venda
                    strcpy(pv.cpfVenda, cpfCliente);
                    pv.cod = pd.cod;
                    pv.quantidadeVendida = qtdVenda;
                    strcpy(pv.nome, pd.nome);
                    strcpy(pv.laboratorio, pd.laboratorio);
                    strcpy(pv.tipo, pd.tipo);
                    pv.valorVenda = (pd.valor * qtdVenda) * (1 - pd.desconto);
                    time_t t = time(NULL);
                    struct tm tm = *localtime(&t);
                    pv.venda.dia = tm.tm_mday;
                    pv.venda.mes = tm.tm_mon + 1;
                    pv.venda.ano = tm.tm_year + 1900;
                    fwrite(&pv, sizeof(ProdutoVendido), 1, ptProdutosVendidos);
                    fclose(ptProdutosVendidos);
                    // Atualizar estoque
                    pd.quantidade -= qtdVenda;
                    fseek(ptProduto, pos, 0);
                    fwrite(&pd, sizeof(Produto), 1, ptProduto);
                    printf("\nCompra realizada com sucesso!\n");
                    system("pause");
                    printf("Deseja comprar outro produto? (S/N): ");
                    scanf(" %c", &resp);
                } while (resp == 'S' || resp == 's');
                fclose(ptProduto);
                break;
            }
            case 4:{
                printf("\nDigite o CPF do cliente para consultar vendas:\n> ");
                fgets(cpfCliente, 15, stdin);
                /* scanf("%s", cpfCliente); */
                buscarVendasPorCliente(cpfCliente);
                system("pause");
                break;
            }
            case 5:{
                printf("\nVoltando para o login.\n");
                break;
            }
        }
    } while (menu != 5);
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
void gerenciarTiposProdutos(Produto *produtos){
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
void gerenciarCategoriaProdutos(Produto *produtos){
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
void promocaoValidade(Produto *produtos, int produtosTopo){

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

main(){
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

    do{
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

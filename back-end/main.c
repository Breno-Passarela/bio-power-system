#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>

typedef struct {
    int dia, mes, ano;
} Dia;

typedef struct {
    int cod, lote, quantidade;
    char nome[200], descricao[255], laboratorio[200], tipo[100];
    float valor;
    float desconto;
    Dia validade;
} Produto;

typedef struct {
    int cod, quantidadeVendida;
    char nome[200], laboratorio[200], tipo[100], formaPagamento[20];
    float valorVenda;
    char cpfVenda[15];
    bool devolvido;
    Dia venda;
} ProdutoVendido;

typedef struct {
    char nome[100];
} tipoProduto;

typedef struct{
    char usuario[200], senha[200];
} Administrador;

typedef struct{
    char nome[200], cpf[15], telefone[15], endereco[255], email[100];
    Dia dataCadastro;
} Cliente;

typedef struct{
    char nome[200];
} Laboratorio;

/* ======== Utils ======== */

void limpaBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Imprimir datas no formato dd/mm/yyyy
void printData(int dia, int mes, int ano) {
    printf("%02d/%02d/%04d\n", dia, mes, ano);
}

int buscaAdministrador(FILE *arquivo, char usuario[]) {
    Administrador adm;
    long pos;

    rewind(arquivo);
    while (fread(&adm, sizeof(Administrador), 1, arquivo) == 1) {
        if (strcmp(adm.usuario, usuario) == 0) {
            pos = ftell(arquivo) - sizeof(Administrador);
            return (int)pos;
        }
    }

    return -1;
}

int buscaCliente(FILE *arquivo, char cpf[]){
    Cliente c;
    long pos;

    rewind(arquivo);
    while(fread(&c, sizeof(Cliente), 1, arquivo) == 1) {
        if(stricmp(c.cpf, cpf) == 0) {
            pos = ftell(arquivo) - sizeof(Cliente);
            return (int)pos;
        }
    }

    return -1;
}

int buscaProduto(FILE *arquivo, int cod){
    Produto p;
    long pos;

    rewind(arquivo);
    while(fread(&p, sizeof(Produto), 1, arquivo) == 1) {
        if(p.cod == cod) {
            pos = ftell(arquivo) - sizeof(Produto);
            return (int)pos;
        }
    }

    return -1;
}

int buscaTipoProduto(FILE *arquivo, char nome[]) {
    tipoProduto tp;
    long pos;

    rewind(arquivo);
    while(fread(&tp, sizeof(tipoProduto), 1, arquivo) == 1) {
        if(stricmp(tp.nome, nome) == 0) {
            pos = ftell(arquivo) - sizeof(tipoProduto);
            return (int)pos;
        }
    }

    return -1;
}

int buscaLaboratorio(FILE *arquivo, char nome[]) {
    Laboratorio lab;
    long pos;

    rewind(arquivo);
    while(fread(&lab, sizeof(Laboratorio), 1, arquivo) == 1) {
        if(stricmp(lab.nome, nome) == 0) {
            pos = ftell(arquivo) - sizeof(Laboratorio);
            return (int)pos;
        }
    }

    return -1;
}

int listarTipos(char lista[][100]) {
    FILE *arquivo;
    tipoProduto tp;
    int count = 0;

    arquivo = fopen("tiposProduto.bin", "rb");

    if(arquivo == NULL) {
        printf("Nenhum tipo de produto cadastrado!\n");
        return 0;
    }

    while(fread(&tp, sizeof(tipoProduto), 1, arquivo) == 1) {
        strcpy(lista[count], tp.nome);
        count++;
    }

    fclose(arquivo);
    return count;
}

int listarLaboratorios(char lista[][100]) {
    FILE *arquivo;
    Laboratorio lab;
    int count = 0;

    arquivo = fopen("laboratorios.bin", "rb");

    if(arquivo == NULL) {
        printf("Nenhum tipo de produto cadastrado!\n");
        return 0;
    }

    while(fread(&lab, sizeof(Laboratorio), 1, arquivo) == 1) {
        strcpy(lista[count], lab.nome);
        count++;
    }

    fclose(arquivo);
    return count;
}

int diasAproximados(Dia d) {
    return d.ano * 365 + d.mes * 30 + d.dia;
}

int diferencaDias(Dia inicio, Dia fim) {
    return diasAproximados(fim) - diasAproximados(inicio);
}

int produtoExpirado(Produto p, Dia hoje) {
    return diasAproximados(p.validade) < diasAproximados(hoje);
}

void criarAdminPadrao() {
	FILE *arquivo;
	Administrador adm;
	
	arquivo = fopen("administradores.bin", "rb");
	
	if(arquivo) {
		fclose(arquivo);
		return;
	}
	
    arquivo = fopen("administradores.bin", "wb");
	
	strcpy(adm.usuario, "biopower\n");
	strcpy(adm.senha, "123456\n");
	fwrite(&adm, sizeof(Administrador), 1, arquivo);
	
	fclose(arquivo);

}

/* ======== CRUD Administrador ======== */

void cadastrarAdministrador() {
    FILE *arquivo;
    Administrador adm;
    long pos;

    arquivo = fopen("administradores.bin", "rb+");

    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo de administradores.\n");
        system("pause");
        return;
    }

    do {
        system("cls");
        printf("======== Cadastro administrador ========\n");

        printf("\nUsuario: ");
        limpaBuffer();
        fgets(adm.usuario, 199, stdin);

        pos = buscaAdministrador(arquivo, adm.usuario);

        if (pos == -1) {
            printf("\nSenha: ");
            fgets(adm.senha, 199, stdin);

            fseek(arquivo, 0, SEEK_END);
            fwrite(&adm, sizeof(Administrador), 1, arquivo);

            printf("\n\nAdmin criado!\n");
        } else {
            printf("\nJa existe um administrador com esse usuario!\n");
        }

        printf("\n========================================\n");
        printf("Deseja continuar? [S/N]\n> ");
    } while (toupper(getche()) == 'S');

    fclose(arquivo);
}

void exibirAdministradores() {
    FILE *arquivo;
    Administrador adm;

    arquivo = fopen("administradores.bin", "rb");

    if (arquivo == NULL) {
        printf("Nenhum administrador cadastrado ou erro ao abrir arquivo.\n");
        system("pause");
        fclose(arquivo);
        return;
    }

    system("cls");
    printf("======== Administradores Cadastrados ========\n");

    while (fread(&adm, sizeof(Administrador), 1, arquivo) == 1) {
        printf("\nUsuario: %s\n", adm.usuario);
        printf("Senha: %s\n", adm.senha);
        printf("=============================================\n");
    }

    system("pause");

    fclose(arquivo);
}

void alterarAdministrador() {
    FILE *arquivo;
    Administrador adm;
    char usuarioBusca[200];
    int pos;
    char opc;

    arquivo = fopen("administradores.bin", "rb+");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo de administradores.\n");
        system("pause");
        fclose(arquivo);
        return;
    }

    do {
        system("cls");
        printf("======== Alterar Administrador ========\n");

        printf("\nUsuario atual do administrador: ");
        limpaBuffer();
        fgets(usuarioBusca, 199, stdin);

        pos = buscaAdministrador(arquivo, usuarioBusca);

        if (pos == -1) {
            printf("\nAdministrador nao encontrado!\n");
        } else {
            fseek(arquivo, pos, SEEK_SET);
            fread(&adm, sizeof(Administrador), 1, arquivo);

            printf("\nDados atuais:\n");
            printf("Usuario: %s", adm.usuario);

            printf("\nNovo usuario: ");
            fgets(adm.usuario, 199, stdin);

            printf("Nova senha: ");
            fgets(adm.senha, 199, stdin);

            fseek(arquivo, pos, SEEK_SET);
            fwrite(&adm, sizeof(Administrador), 1, arquivo);

            printf("\nAdministrador alterado com sucesso!\n");
        }

        printf("\n=======================================\n");
        printf("Deseja alterar outro? [S/N]\n> ");
        opc = toupper(getche());

    } while (opc == 'S');

    fclose(arquivo);
}

void excluirAdministrador() {
    FILE *arquivo;
    FILE *arquivoTemp;
    Administrador admTemp;
    char usuarioBusca[200];
    int pos;
    char opc;

    arquivo = fopen("administradores.bin", "rb");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo de administradores.\n");
        system("pause");
        fclose(arquivo);
        return;
    }

    do {
        system("cls");
        printf("======== Excluir administrador ========\n");

        printf("\nUsuario: ");
        limpaBuffer();
        fgets(usuarioBusca, 199, stdin);

        pos = buscaAdministrador(arquivo, usuarioBusca);

        if(pos > -1) {
            arquivoTemp = fopen("temp.bin", "wb");
            if(arquivoTemp == NULL) {
                printf("Erro no arquivo temporario\n");
                fclose(arquivo);
                system("pause");
                return;
            }

            rewind(arquivo);
            while(fread(&admTemp, sizeof(Administrador), 1, arquivo) == 1) {
                if(strcmp(admTemp.usuario, usuarioBusca) != 0) {
                    fwrite(&admTemp, sizeof(Administrador), 1, arquivoTemp);
                }
            }

            fclose(arquivoTemp);
            fclose(arquivo);

            remove("administradores.bin");
            rename("temp.bin", "administradores.bin");

            arquivo = fopen("administradores.bin", "rb");
            printf("\nAdministrador excluido!\n");
        } else {
            printf("\nAdministrador nao cadastrado!\n");
        }

        printf("\n\n=======================================\n");
        printf("Deseja continuar? [S/N]\n> ");
        opc = toupper(getche());

    } while(opc == 'S');

    fclose(arquivo);
}

/* ======== CRUD Cliente ======== */

void cadastrarCliente() {
    FILE *arquivo;
    Cliente cl;
    int pos;
    char opc;

    arquivo = fopen("clientes.bin", "ab+");

    if(arquivo == NULL) {
        printf("Erro no arquivo de clientes\n");
        system("pause");
        fclose(arquivo);
        return;
    }

    do {
        system("cls");
        printf("======== Cadastro cliente ========\n");

        printf("\nCPF: ");
        limpaBuffer();
        fgets(cl.cpf, 14, stdin);

        pos = buscaCliente(arquivo, cl.cpf);

        if(pos == -1) {
            printf("\nNome: ");
            fgets(cl.nome, 199, stdin);

            printf("Telefone: ");
            fgets(cl.telefone, 14, stdin);

            printf("Endereco: ");
            fgets(cl.endereco, 254, stdin);

            printf("Email: ");
            fgets(cl.email, 99, stdin);

            time_t t = time(NULL);
            struct tm tm_info = *localtime(&t);
            cl.dataCadastro.dia = tm_info.tm_mday;
            cl.dataCadastro.mes = tm_info.tm_mon + 1;
            cl.dataCadastro.ano = tm_info.tm_year + 1900;

            fwrite(&cl, sizeof(Cliente), 1, arquivo);
            printf("\n\nCliente criado!\n");
        } else {
            fseek(arquivo, pos, SEEK_SET);
            fread(&cl, sizeof(Cliente), 1, arquivo);
            printf("\nCliente %s ja cadastrado!", cl.cpf);
        }

        printf("\n\n==================================\n");
        printf("Deseja continuar? [S/N]\n> ");
        opc = toupper(getche());
    } while(opc == 'S');

    fclose(arquivo);
}

void exibirClientes() {
    FILE *arquivo;
    Cliente cl;

    arquivo = fopen("clientes.bin", "rb");

    if(arquivo == NULL) {
        printf("Erro no arquivo de clientes\n");
        system("pause");
        fclose(arquivo);
        return;
    }

    system("cls");
    printf("======== Exibir clientes ========\n");

    while(fread(&cl, sizeof(Cliente), 1, arquivo) == 1) {
        printf("\n================================\n");
        printf("Nome: %s", cl.nome);
        printf("CPF: %s", cl.cpf);
        printf("Telefone: %s", cl.telefone);
        printf("Endereco: %s", cl.endereco);
        printf("Email: %s", cl.email);
        printf("Data cadastro: ");
        printData(cl.dataCadastro.dia, cl.dataCadastro.mes, cl.dataCadastro.ano);
        printf("================================\n");
    }

    system("pause");
    fclose(arquivo);
}

void alterarCliente() {
    FILE *arquivo;
    Cliente cl;
    int pos;
    int opcao;
    int invalido;
    int check;
    char opc;

    arquivo = fopen("clientes.bin", "rb+");

    if(arquivo == NULL) {
        printf("Erro no arquivo de clientes\n");
        system("pause");
        fclose(arquivo);
        return;
    }

    do {
        system("cls");
        printf("======== Alterar cliente ========\n");

        printf("\nCPF: ");
        limpaBuffer();
        fgets(cl.cpf, 14, stdin);

        pos = buscaCliente(arquivo, cl.cpf);

        if(pos > -1) {
            fseek(arquivo, pos, SEEK_SET);
            fread(&cl, sizeof(Cliente), 1, arquivo);

            printf("Dados atuais\n\n");
            printf("1 - Nome: %s", cl.nome);
            printf("2 - CPF: %s", cl.cpf);
            printf("3 - Telefone: %s", cl.telefone);
            printf("4 - Endereco: %s", cl.endereco);
            printf("5 - Email: %s", cl.email);

            printf("\nO que deseja alterar? ");
            scanf("%d", &opcao);

            switch(opcao) {
                case 1:
                    printf("\nNovo nome: ");
                    limpaBuffer();
                    fgets(cl.nome, 199, stdin);
                    break;
                case 2:
                    do {
                        invalido = 0;
                        printf("\nNovo CPF: ");
                        limpaBuffer();
                        fgets(cl.cpf, 14, stdin);

                        check = buscaCliente(arquivo, cl.cpf);
                        if(check != -1 && check != pos) {
                            printf("\nCPF ja cadastrado! Escreva um novo.\n");
                            invalido = 1;
                        }
                    } while(invalido);
                    break;
                case 3:
                    printf("\nNovo telefone: ");
                    limpaBuffer();
                    fgets(cl.telefone, 14, stdin);
                    break;
                case 4:
                    printf("\nNovo endereco: ");
                    limpaBuffer();
                    fgets(cl.endereco, 254, stdin);
                    break;
                case 5:
                    printf("\nNovo email: ");
                    limpaBuffer();
                    fgets(cl.email, 99, stdin);
                    break;
                default:
                    printf("Opcao invalida!");
                    break;
            }

            fseek(arquivo, pos, SEEK_SET);
            fwrite(&cl, sizeof(Cliente), 1, arquivo);

            printf("\n\nCliente alterado!");
            system("pause");
        } else {
            printf("\nCliente nao cadastrado!");
        }

        printf("\n\n=================================\n");
        printf("Deseja continuar? [S/N]\n> ");
        opc = toupper(getche());
    } while(opc == 'S');

    fclose(arquivo);
}

void excluirCliente() {
    FILE *arquivo;
    FILE *arquivoTemp;
    Cliente cl, clTemp;
    int pos;
    char opc;

    arquivo = fopen("clientes.bin", "rb");

    if(arquivo == NULL) {
        printf("Erro no arquivo de clientes\n");
        system("pause");
        fclose(arquivo);
        return;
    }

    do {
        system("cls");
        printf("======== Excluir cliente ========\n");

        printf("\nCPF: ");
        limpaBuffer();
        fgets(cl.cpf, 14, stdin);

        pos = buscaCliente(arquivo, cl.cpf);

        if(pos > -1) {
            arquivoTemp = fopen("temp.bin", "wb");
            if(arquivoTemp == NULL) {
                printf("Erro no arquivo temporario\n");
                fclose(arquivo);
                system("pause");
                return;
            }

            rewind(arquivo);
            while(fread(&clTemp, sizeof(Cliente), 1, arquivo) == 1) {
                if(stricmp(cl.cpf, clTemp.cpf) != 0) {
                    fwrite(&clTemp, sizeof(Cliente), 1, arquivoTemp);
                }
            }

            fclose(arquivoTemp);
            fclose(arquivo);

            remove("clientes.bin");
            rename("temp.bin", "clientes.bin");

            arquivo = fopen("clientes.bin", "rb");
            printf("\nCliente excluido!\n");
        } else {
            printf("\nCliente nao cadastrado!");
        }

        printf("\n\n=================================\n");
        printf("Deseja continuar? [S/N]\n> ");
        opc = toupper(getche());
    } while(opc == 'S');

    fclose(arquivo);
}

/* ======== CRUD Tipo de Produto ======== */

void cadastrarTipoProduto() {
    FILE *arquivo;
    tipoProduto tp;
    int pos;
    char opc;

    arquivo = fopen("tiposProduto.bin", "ab+");

    if(arquivo == NULL) {
        printf("Erro ao abrir arquivo de tipos.\n");
        system("pause");
        fclose(arquivo);
        return;
    }

    do {
        system("cls");
        printf("======== Cadastro de Tipo de Produto ========\n");

        printf("\nNome do Tipo: ");
        limpaBuffer();
        fgets(tp.nome, 99, stdin);

        pos = buscaTipoProduto(arquivo, tp.nome);

        if(pos == -1) {
            fwrite(&tp, sizeof(tipoProduto), 1, arquivo);
            printf("\nTipo cadastrado com sucesso!\n");
        } else {
            printf("\nEste tipo ja existe!\n");
        }

        printf("\n=============================================\n");
        printf("Deseja continuar? [S/N]\n> ");
        opc = toupper(getche());

    } while(opc == 'S');

    fclose(arquivo);
}

void exibirTipos() {
    FILE *arquivo;
    tipoProduto tp;

    arquivo = fopen("tiposProduto.bin", "rb");

    if(arquivo == NULL) {
        printf("Erro ao abrir arquivo de tipos.\n");
        system("pause");
        fclose(arquivo);
        return;
    }

    system("cls");
    printf("======== Tipos de Produtos ========\n");

    while(fread(&tp, sizeof(tipoProduto), 1, arquivo) == 1) {
        printf("- %s", tp.nome);
    }

    printf("===================================\n");
    system("pause");

    fclose(arquivo);
}

void alterarTipoProduto() {
    FILE *arquivo;
    tipoProduto tp;
    char nomeBusca[100];
    int pos;
    char opc;

    arquivo = fopen("tiposProduto.bin", "rb+");

    if(arquivo == NULL) {
        printf("Erro ao abrir arquivo de tipos.\n");
        system("pause");
        fclose(arquivo);
        return;
    }

    do {
        system("cls");
        printf("======== Alterar Tipo de Produto ========\n");

        printf("\nNome atual do tipo: ");
        limpaBuffer();
        fgets(nomeBusca, 99, stdin);

        pos = buscaTipoProduto(arquivo, nomeBusca);

        if(pos == -1) {
            printf("\nTipo nao encontrado!\n");
        } else {
            fseek(arquivo, pos, SEEK_SET);
            fread(&tp, sizeof(tipoProduto), 1, arquivo);

            printf("\nNovo nome: ");
            fgets(tp.nome, 99, stdin);

            fseek(arquivo, pos, SEEK_SET);
            fwrite(&tp, sizeof(tipoProduto), 1, arquivo);

            printf("\nTipo alterado com sucesso!\n");
        }

        printf("\n==========================================\n");
        printf("Deseja continuar? [S/N]\n> ");
        opc = toupper(getche());

    } while(opc == 'S');

    fclose(arquivo);
}

void excluirTipoProduto() {
    FILE *arquivo;
    FILE *arquivoTemp;
    tipoProduto tpTemp;
    char nomeBusca[100];
    int pos;
    char opc;

    arquivo = fopen("tiposProduto.bin", "rb");

    if(arquivo == NULL) {
        printf("Erro no arquivo de tipos\n");
        system("pause");
        fclose(arquivo);
        return;
    }

    do {
        system("cls");
        printf("======== Excluir Tipo de Produto ========\n");

        printf("\nNome do tipo: ");
        limpaBuffer();
        fgets(nomeBusca, 99, stdin);

        pos = buscaTipoProduto(arquivo, nomeBusca);

        if(pos > -1) {
            arquivoTemp = fopen("temp.bin", "wb");

            if(arquivoTemp == NULL) {
                printf("Erro no arquivo temporario!\n");
                fclose(arquivo);
                system("pause");
                return;
            }

            rewind(arquivo);
            while(fread(&tpTemp, sizeof(tipoProduto), 1, arquivo) == 1) {
                if(stricmp(nomeBusca, tpTemp.nome) != 0) {
                    fwrite(&tpTemp, sizeof(tipoProduto), 1, arquivoTemp);
                }
            }

            fclose(arquivoTemp);
            fclose(arquivo);

            remove("tiposProduto.bin");
            rename("temp.bin", "tiposProduto.bin");

            arquivo = fopen("tiposProduto.bin", "rb");
            printf("\nTipo de produto excluido!\n");

        } else {
            printf("\nTipo nao cadastrado!\n");
        }

        printf("\n=========================================\n");
        printf("Deseja continuar? [S/N]\n> ");
        opc = toupper(getche());

    } while(opc == 'S');

    fclose(arquivo);
}

/* ======== CRUD Produtos ======== */

void cadastrarProduto() {
    FILE *arquivo;
    Produto p;
    char tipos[100][100];
    char laboratorios[100][100];
    int qtdTipos, escolha;
    int qtdLaboratorios;
    int pos;
    char opc;

    arquivo = fopen("produtos.bin", "rb+");
    if (arquivo == NULL) {
        arquivo = fopen("produtos.bin", "wb+");

        if(arquivo == NULL) {
            printf("Erro no arquivo de produtos\n");
            system("pause");
        	fclose(arquivo);
            return;
        }
    }

    do {
        system("cls");
        printf("======== Cadastro produto ========\n");

        printf("\nCodigo: ");
        scanf("%d", &p.cod);

        pos = buscaProduto(arquivo, p.cod);

        if(pos == -1) {
            printf("\nNome: ");
            limpaBuffer();
            fgets(p.nome, 199, stdin);

            printf("\nDescricao: ");
            fgets(p.descricao, 254, stdin);
            
			qtdLaboratorios = listarLaboratorios(laboratorios);
			if(qtdLaboratorios == 0) {
                printf("\nNenhum laboratorio cadastrado. Cadastre primeiro!\n");
                system("pause");
                fclose(arquivo);
                return;
            }
            
            printf("\n--- Laboratorios disponiveis ---\n");
            for(int i = 0; i < qtdLaboratorios; i++) {
                printf("%d - %s", i+1, laboratorios[i]);
            }
            
            printf("\nSelecione o laboratorio: ");
            scanf("%d", &escolha);
            
            while(escolha < 1 || escolha > qtdLaboratorios) {
                printf("\nOpcao invalida! Digite novamente: ");
                scanf("%d", &escolha);
            }

            strcpy(p.laboratorio, laboratorios[escolha-1]);

            qtdTipos = listarTipos(tipos);
            if(qtdTipos == 0) {
                printf("\nNenhum tipo cadastrado. Cadastre primeiro!\n");
                system("pause");
                fclose(arquivo);
                return;
            }

            printf("\n--- Tipos disponiveis ---\n");
            for(int i = 0; i < qtdTipos; i++) {
                printf("%d - %s", i+1, tipos[i]);
            }

            printf("\nSelecione o tipo do produto: ");
            scanf("%d", &escolha);

            while(escolha < 1 || escolha > qtdTipos) {
                printf("\nOpcao invalida! Digite novamente: ");
                scanf("%d", &escolha);
            }

            strcpy(p.tipo, tipos[escolha-1]);

            printf("\nQuantidade: ");
            scanf("%d", &p.quantidade);

            printf("\nValor: ");
            scanf("%f", &p.valor);

            printf("\nDesconto (0 caso nao tiver): ");
            scanf("%f", &p.desconto);

            printf("\n--- Validade ---\n");
            printf("Dia: ");
            scanf("%d", &p.validade.dia);
            printf("Mes: ");
            scanf("%d", &p.validade.mes);
            printf("Ano: ");
            scanf("%d", &p.validade.ano);

            fseek(arquivo, 0, SEEK_END);
            fwrite(&p, sizeof(Produto), 1, arquivo);
        } else {
            fseek(arquivo, pos, SEEK_SET);
            fread(&p, sizeof(Produto), 1, arquivo);
            printf("\nProduto %d ja cadastrado!", p.cod);
        }


        printf("\n\nProduto criado!\n");
        system("pause");

        printf("\nDeseja continuar? [S/N]\n> ");
        opc = toupper(getche());

    } while(opc == 'S');

    fclose(arquivo);
}

void exibirProduto() {
    FILE *arquivo;
    Produto p;

    arquivo = fopen("produtos.bin", "rb");

    if(arquivo == NULL) {
        printf("Erro no arquivo de produtos\n");
        system("pause");
        fclose(arquivo);
        return;
    }

    system("cls");
    printf("======== Exibir produtos ========\n");

    while(fread(&p, sizeof(Produto), 1, arquivo) == 1) {
        printf("\n================================\n");
        printf("Codigo: %d\n", p.cod);
        printf("Nome: %s", p.nome);
        printf("Descricao: %s", p.descricao);
        printf("Laboratorio: %s", p.laboratorio);
        printf("Tipo: %s", p.tipo);
        printf("Quantidade: %d\n", p.quantidade);
        printf("Valor: %.2f\n", p.valor);
        printf("Desconto: %.2f\n", p.desconto);
        printf("Validade: ");
        printData(p.validade.dia, p.validade.mes, p.validade.ano);
        printf("================================\n");
    }

    system("pause");
    fclose(arquivo);
}

void alterarProduto() {
    FILE *arquivo;
    Produto p;
    char tipos[100][100];
    int qtdTipos, escolha;
    int opcao;
    int pos;
    char opc;

    arquivo = fopen("produtos.bin", "rb+");

    if(arquivo == NULL) {
        printf("Erro no arquivo de produtos\n");
        system("pause");
        fclose(arquivo);
        return;
    }

    do {
        system("cls");
        printf("======== Alterar produto ========\n");

        printf("\nCodigo: ");
        scanf("%d", &p.cod);

        pos = buscaProduto(arquivo, p.cod);

        if(pos > -1) {
            fseek(arquivo, pos, SEEK_SET);
            fread(&p, sizeof(Produto), 1, arquivo);

            printf("\n1 - Nome: %s", p.nome);
            printf("2 - Descricao: %s", p.descricao);
            printf("3 - Laboratorio: %s", p.laboratorio);
            printf("4 - Tipo: %s", p.tipo);
            printf("5 - Quantidade: %d\n", p.quantidade);
            printf("6 - Valor: %.2f\n", p.valor);
            printf("7 - Desconto: %.2f\n", p.desconto);
            printf("8 - Validade: ");
            printData(p.validade.dia, p.validade.mes, p.validade.ano);

            printf("\nO que deseja alterar? ");
            scanf("%d", &opcao);

            switch(opcao) {
                case 1:
                    printf("\nNovo nome: ");
                    limpaBuffer();
                    fgets(p.nome, 199, stdin);
                    break;
                case 2:
                    printf("\nNova descricao: ");
                    limpaBuffer();
                    fgets(p.descricao, 254, stdin);
                    break;
                case 3:
                    printf("\nNovo laboratorio: ");
                    limpaBuffer();
                    fgets(p.laboratorio, 199, stdin);
                    break;
                case 4:
                    qtdTipos = listarTipos(tipos);

                    if(qtdTipos == 0) {
                        printf("\nNenhum tipo cadastrado!\n");
                        break;
                    }

                    printf("\n--- Tipos disponiveis ---\n");
                    for(int i = 0; i < qtdTipos; i++)
                        printf("%d - %s", i+1, tipos[i]);

                    printf("\nEscolha: ");
                    scanf("%d", &escolha);

                    while(escolha < 1 || escolha > qtdTipos) {
                        printf("Invalido. Digite novamente: ");
                        scanf("%d", &escolha);
                    }

                    strcpy(p.tipo, tipos[escolha-1]);
                    break;
                case 5:
                    printf("\nNova quantidade: ");
                    scanf("%d", &p.quantidade);
                    break;
                case 6:
                    printf("\nNovo valor: ");
                    scanf("%f", &p.valor);
                    break;
                case 7:
                    printf("\nNovo desconto: ");
                    scanf("%f", &p.desconto);
                    break;
                case 8:
                    printf("\nNovo dia: ");
                    scanf("%d", &p.validade.dia);

                    printf("Novo mes: ");
                    scanf("%d", &p.validade.mes);

                    printf("Novo ano: ");
                    scanf("%d", &p.validade.ano);
                    break;
                default:
                    printf("Opcao invalida!");
            }

            fseek(arquivo, pos, SEEK_SET);
            fwrite(&p, sizeof(Produto), 1, arquivo);

            printf("\nProduto alterado!\n");
            system("pause");

        } else {
            printf("\nProduto nao encontrado!");
        }

        printf("\nDeseja continuar? [S/N]\n> ");
        opc = toupper(getche());
    } while(opc == 'S');

    fclose(arquivo);
}

void excluirProduto() {
    FILE *arquivo;
    FILE *arquivoTemp;
    Produto pTemp;
    int cod;
    int pos;
    char opc;

    arquivo = fopen("produtos.bin", "rb");

    if(arquivo == NULL) {
        printf("Erro no arquivo de produtos\n");
        system("pause");
        fclose(arquivo);
        return;
    }

    do {
        system("cls");
        printf("======== Excluir Produto ========\n");

        printf("\nCodigo: ");
        scanf("%d", &cod);

        pos = buscaProduto(arquivo, cod);

        if(pos > -1) {
            arquivoTemp = fopen("temp.bin", "wb");

            if(arquivoTemp == NULL) {
                printf("Erro no arquivo temporario!\n");
                fclose(arquivo);
                system("pause");
                return;
            }

            rewind(arquivo);
            while(fread(&pTemp, sizeof(Produto), 1, arquivo) == 1) {
                if(pTemp.cod != cod) {
                    fwrite(&pTemp, sizeof(Produto), 1, arquivoTemp);
                }
            }

            fclose(arquivoTemp);
            fclose(arquivo);

            remove("produtos.bin");
            rename("temp.bin", "produtos.bin");

            arquivo = fopen("produtos.bin", "rb");
            printf("\nProduto excluido!\n");

        } else {
            printf("\nProduto nao cadastrado!\n");
        }

        printf("\n==================================\n");
        printf("Deseja continuar? [S/N]\n> ");
        opc = toupper(getche());

    } while(opc == 'S');

    fclose(arquivo);
}

/* ======== CRUD Laboratorios ======== */

void cadastrarLaboratorio() {
    FILE *arquivo;
    Laboratorio lab;
    int pos;
    char opc;

    arquivo = fopen("laboratorios.bin", "ab+");

    if(arquivo == NULL) {
        printf("Erro ao abrir arquivo de laboratorios.\n");
        system("pause");
        fclose(arquivo);
        return;
    }

    do {
        system("cls");
        printf("======== Cadastro de Laboratorio ========\n");

        printf("\nNome do laboratorio: ");
        limpaBuffer();
        fgets(lab.nome, 199, stdin);

        pos = buscaLaboratorio(arquivo, lab.nome);

        if(pos == -1) {
            fwrite(&lab, sizeof(Laboratorio), 1, arquivo);
            printf("\nLaboratorio cadastrado com sucesso!\n");
        } else {
            printf("\nEste laboratorio ja existe!\n");
        }

        printf("\n=========================================\n");
        printf("Deseja continuar? [S/N]\n> ");
        opc = toupper(getche());
        
    } while(opc == 'S');

    fclose(arquivo);
}

void exibirLaboratorios() {
    FILE *arquivo;
    Laboratorio lab;

    arquivo = fopen("laboratorios.bin", "rb");

    if(arquivo == NULL) {
        printf("Erro ao abrir arquivo de laboratorios.\n");
        system("pause");
        fclose(arquivo);
        return;
    }

    system("cls");
    printf("======== Laboratorios Cadastrados ========\n");

    while(fread(&lab, sizeof(Laboratorio), 1, arquivo) == 1) {
        printf("- %s", lab.nome);
    }

    printf("==========================================\n");
    system("pause");

    fclose(arquivo);
}

void alterarLaboratorio() {
    FILE *arquivo;
    Laboratorio lab;
    char nomeBusca[200];
    int pos;
    char opc;

    arquivo = fopen("laboratorios.bin", "rb+");

    if(arquivo == NULL) {
        printf("Erro ao abrir arquivo de laboratorios.\n");
        system("pause");
        fclose(arquivo);
        return;
    }

    do {
        system("cls");
        printf("======== Alterar Laboratorio ========\n");

        printf("\nNome atual do laboratorio: ");
        limpaBuffer();
        fgets(nomeBusca, 199, stdin);

        pos = buscaLaboratorio(arquivo, nomeBusca);

        if(pos == -1) {
            printf("\nLaboratorio nao encontrado!\n");
        } else {
            fseek(arquivo, pos, SEEK_SET);
            fread(&lab, sizeof(Laboratorio), 1, arquivo);

            printf("\nNovo nome: ");
            fgets(lab.nome, 199, stdin);

            fseek(arquivo, pos, SEEK_SET);
            fwrite(&lab, sizeof(Laboratorio), 1, arquivo);

            printf("\nLaboratorio alterado com sucesso!\n");
        }

        printf("\n======================================\n");
        printf("Deseja continuar? [S/N]\n> ");
        opc = toupper(getche());

    } while(opc == 'S');

    fclose(arquivo);
}

void excluirLaboratorio() {
    FILE *arquivo;
    FILE *arquivoTemp;
    Laboratorio labTemp;
    char nomeBusca[200];
    int pos;
    char opc;

    arquivo = fopen("laboratorios.bin", "rb");

    if(arquivo == NULL) {
        printf("Erro ao abrir arquivo de laboratorios.\n");
        system("pause");
        fclose(arquivo);
        return;
    }

    do {
        system("cls");
        printf("======== Excluir Laboratorio ========\n");

        printf("\nNome do laboratorio: ");
        limpaBuffer();
        fgets(nomeBusca, 199, stdin);

        pos = buscaLaboratorio(arquivo, nomeBusca);

        if(pos > -1) {
            arquivoTemp = fopen("temp.bin", "wb");

            if(arquivoTemp == NULL) {
                printf("Erro no arquivo temporario.\n");
                fclose(arquivo);
                system("pause");
                return;
            }

            rewind(arquivo);
            while(fread(&labTemp, sizeof(Laboratorio), 1, arquivo) == 1) {
                if(stricmp(nomeBusca, labTemp.nome) != 0) {
                    fwrite(&labTemp, sizeof(Laboratorio), 1, arquivoTemp);
                }
            }

            fclose(arquivoTemp);
            fclose(arquivo);

            remove("laboratorios.bin");
            rename("temp.bin", "laboratorios.bin");

            arquivo = fopen("laboratorios.bin", "rb");
            printf("\nLaboratorio excluido!\n");
        } else {
            printf("\nLaboratorio nao cadastrado!\n");
        }

        printf("\n======================================\n");
        printf("Deseja continuar? [S/N]\n> ");
        opc = toupper(getche());

    } while(opc == 'S');

    fclose(arquivo);
}

/* ======== Funcoes de Estoque / Vendas / Promocao / Descarte ======== */

void controlarEstoque() {
    FILE *ptProduto = fopen("produtos.bin", "rb");
    Produto pd;
    int encontrou = 0;
    
    if (ptProduto == NULL) {
        printf("Erro ao abrir o arquivo de produtos.\n");
        system("pause");
        return;
    }

    system("cls");
    printf("\nControle de Estoque:\n");
    while (fread(&pd, sizeof(Produto), 1, ptProduto) == 1) {
        printf("=================================\n");
        printf("Codigo: %d\n", pd.cod);
        printf("Produto: %s", pd.nome);
        printf("Quantidade em estoque: %d\n", pd.quantidade);
        printf("=================================\n");
        encontrou = 1;
    }
    if (!encontrou) {
        printf("Nenhum produto cadastrado.\n");
    }
    fclose(ptProduto);
    system("pause");
}

void exibirComprasRealizadas() {
    FILE *ptProdutosVendidos = fopen("produtosVendidos.bin", "rb");
    
    if (ptProdutosVendidos == NULL) {
        printf("Nenhuma compra registrada.\n");
        system("pause");
        return;
    }
    
    ProdutoVendido pv;
    char cpfCliente[15];

    system("cls");
    printf("\nDigite o CPF: ");
    limpaBuffer();
    fgets(cpfCliente, 14, stdin);

    printf("===== Compras de %s =====\n", cpfCliente);

    while (fread(&pv, sizeof(ProdutoVendido), 1, ptProdutosVendidos) == 1) {
        if (strcmp(pv.cpfVenda, cpfCliente) == 0) {
            printf("\nProduto: %s", pv.nome);
            printf("Quantidade: %d\n", pv.quantidadeVendida);
            printf("Valor total: %.2f\n", pv.valorVenda);
            printf("Data: %02d/%02d/%04d\n", pv.venda.dia, pv.venda.mes, pv.venda.ano);
            printf("Devolvido: %s\n", pv.devolvido ? "Sim" : "Nao");
        }
    }

    fclose(ptProdutosVendidos);
    system("pause");
}

void exibirComprasRealizadasNaoDevolvido() {
    FILE *ptProdutosVendidos = fopen("produtosVendidos.bin", "rb");
    
    if (ptProdutosVendidos == NULL) {
        printf("Nenhuma compra registrada.\n");
        system("pause");
        return;
    }
    
    ProdutoVendido pv;
    char cpfCliente[15];

    system("cls");
    printf("\nDigite o CPF: ");
    limpaBuffer();
    fgets(cpfCliente, 14, stdin);

    printf("===== Compras de %s =====\n", cpfCliente);

    while (fread(&pv, sizeof(ProdutoVendido), 1, ptProdutosVendidos) == 1) {
        if (strcmp(pv.cpfVenda, cpfCliente) == 0 && pv.devolvido) {
            printf("\nProduto: %s", pv.nome);
            printf("Quantidade: %d\n", pv.quantidadeVendida);
            printf("Valor total: %.2f\n", pv.valorVenda);
            printf("Data: %02d/%02d/%04d\n", pv.venda.dia, pv.venda.mes, pv.venda.ano);
            printf("Devolvido: %s\n", pv.devolvido ? "Sim" : "Nao");
        }
    }

    fclose(ptProdutosVendidos);
    system("pause");
}

int comprarProdutos() {
    FILE *ptProdutosVendidos, *ptProduto;
    
    Produto p;
    ProdutoVendido pv;
    char resp;
    int cod, qtdVenda, pos;
    char cpfCliente[15];

    ptProduto = fopen("produtos.bin", "rb+");
    if (ptProduto == NULL) {
        printf("Erro ao abrir produtos.bin\n");
        system("pause");
        return -1;
    }

    system("cls");
    printf("Digite o CPF do cliente: ");
    limpaBuffer();
    fgets(cpfCliente, 14, stdin);

    do {
        exibirProduto();

        printf("Digite o codigo do produto que deseja comprar: ");
        scanf("%d", &cod);

        pos = buscaProduto(ptProduto, cod);
        if (pos == -1) {
            printf("Codigo invalido!\n");
            system("pause");
            fclose(ptProduto);
            return -1;
        }

        fseek(ptProduto, pos, SEEK_SET);
        fread(&p, sizeof(Produto), 1, ptProduto);

        if (p.quantidade < 1) {
            printf("Produto sem estoque!\n");
            system("pause");
            fclose(ptProduto);
            return -1;
        }

        do {
            printf("\nO produto possui %d unidades. Quantas deseja comprar: ", p.quantidade);
            scanf("%d", &qtdVenda);

            if (qtdVenda > p.quantidade)
                printf("Quantidade invalida! Tente novamente.\n");

        } while (qtdVenda > p.quantidade);

        ptProdutosVendidos = fopen("produtosVendidos.bin", "ab");
        if (ptProdutosVendidos == NULL) {
            printf("Erro ao abrir produtosVendidos.bin\n");
            fclose(ptProduto);
            system("pause");
            return -1;
        }

        strcpy(pv.cpfVenda, cpfCliente);
        pv.cod = p.cod;
        pv.quantidadeVendida = qtdVenda;
        strcpy(pv.nome, p.nome);
        strcpy(pv.laboratorio, p.laboratorio);
        strcpy(pv.tipo, p.tipo);
        pv.valorVenda = (p.valor * qtdVenda);
        pv.devolvido = false;

        printf("\nDigite a data da compra:");
        printf("\nDia: ");
        scanf("%d", &pv.venda.dia);
        printf("Mes: ");
        scanf("%d", &pv.venda.mes);
        printf("Ano: ");
        scanf("%d", &pv.venda.ano);

        fwrite(&pv, sizeof(ProdutoVendido), 1, ptProdutosVendidos);
        fclose(ptProdutosVendidos);

        p.quantidade -= qtdVenda;
        fseek(ptProduto, pos, SEEK_SET);
        fwrite(&p, sizeof(Produto), 1, ptProduto);

        printf("\nCompra realizada com sucesso!\n");
        system("pause");

        printf("Deseja comprar outro produto? (S/N): ");
        scanf(" %c", &resp);

    } while (resp == 'S' || resp == 's');

    fclose(ptProduto);
    return 0;
}

//void formatarCpf() {
//	
//}


int devolverProdutos() {
    ProdutoVendido pv;
    Produto p;
    int cod, pos;
    char cpfCliente[15];
    bool encontrou = false;
    
    FILE *ptProdutosVendidos = fopen("produtosVendidos.bin", "rb+");
    if (ptProdutosVendidos == NULL) {
        printf("Erro ao abrir produtosVendidos.bin\n");
        system("pause");
        return -1;
    }

    FILE *ptProduto = fopen("produtos.bin", "rb+");
    if (ptProduto == NULL) {
        printf("Erro ao abrir produtos.bin\n");
        fclose(ptProdutosVendidos);
        system("pause");
        return -1;
    }
    
    
    system("cls");  
    printf("Digite o CPF do cliente: ");
    limpaBuffer();
    fgets(cpfCliente, 14, stdin);

    printf("Digite o codigo do produto que deseja devolver: ");
    scanf("%d", &cod);

    while (fread(&pv, sizeof(ProdutoVendido), 1, ptProdutosVendidos) == 1 && !encontrou) {
        if (pv.cod == cod && strcmp(pv.cpfVenda, cpfCliente) == 0 && !pv.devolvido) {       
            pv.devolvido = true;
            fseek(ptProdutosVendidos, - (long)sizeof(ProdutoVendido), SEEK_CUR);
            fwrite(&pv, sizeof(ProdutoVendido), 1, ptProdutosVendidos);

            pos = buscaProduto(ptProduto, cod);
            if (pos != -1) {
                fseek(ptProduto, pos, SEEK_SET);
                fread(&p, sizeof(Produto), 1, ptProduto);

                p.quantidade += pv.quantidadeVendida;
                fseek(ptProduto, pos, SEEK_SET);
                fwrite(&p, sizeof(Produto), 1, ptProduto);
            }

            printf("Produto devolvido com sucesso!\n");
            system("pause");
            
            encontrou = true;
        }
    }

    if (!encontrou) {
        printf("Venda nao encontrada para esse CPF/codigo ou ja devolvida.\n");
        system("pause");
    }

    fclose(ptProdutosVendidos);
    fclose(ptProduto);
    return 0;
}

void definirPromocao() {
    FILE *arquivo;
    Produto p;
    Dia hoje;
    int opcao;
    int limiteDias = 0;
    float desconto;

    time_t t;
    struct tm tm_info;
    t = time(NULL);
    tm_info = *localtime(&t);
    hoje.dia  = tm_info.tm_mday;
    hoje.mes  = tm_info.tm_mon + 1;
    hoje.ano  = tm_info.tm_year + 1900;

    system("cls");
    printf("======== Definir promocao ========\n");
    printf("Considerar produtos que vencem em ate:\n");
    printf("1 - 30 dias\n");
    printf("2 - 60 dias\n");
    printf("3 - 90 dias\n");
    printf("> ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            limiteDias = 30;
            break;
        case 2:
            limiteDias = 60;
            break;
        case 3:
            limiteDias = 90;
            break;
        default:
            printf("Opcao invalida.\n");
            system("pause");
            return;
    }

    printf("Informe o desconto (em %%): ");
    scanf("%f", &desconto);

    arquivo = fopen("produtos.bin", "rb+");
    if (arquivo == NULL) {
        printf("Erro ao abrir produtos.bin ou nenhum produto cadastrado.\n");
        system("pause");
        return;
    }

    rewind(arquivo);
    while (fread(&p, sizeof(Produto), 1, arquivo) == 1) {
        if (!produtoExpirado(p, hoje)) {
            int diasRestantes = diferencaDias(hoje, p.validade);

            if (diasRestantes >= 0 && diasRestantes <= limiteDias) {
                p.desconto = desconto;

                long pos = ftell(arquivo) - sizeof(Produto);
                fseek(arquivo, pos, SEEK_SET);
                fwrite(&p, sizeof(Produto), 1, arquivo);

                fseek(arquivo, 0, SEEK_CUR);
            }
        }
    }

    fclose(arquivo);

    arquivo = fopen("produtos.bin", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir produtos.bin para leitura.\n");
        system("pause");
        return;
    }

    system("cls");
    printf("\n======== Produtos com desconto (> 0) ========\n");

    while (fread(&p, sizeof(Produto), 1, arquivo) == 1) {
        if (p.desconto > 0.0f) {
            printf("\n=============================================\n");
            printf("Codigo: %d\n", p.cod);
            printf("Nome: %s", p.nome);
            printf("Valor: %.2f\n", p.valor);
            printf("Desconto: %.2f %%\n", p.desconto);
            printf("Validade: ");
            printData(p.validade.dia, p.validade.mes, p.validade.ano);
        }
    }

    printf("\n=============================================\n");

    fclose(arquivo);
    system("pause");
}

void descartarProdutosVencidos() {
    FILE *arquivo, *temp;
    Produto p;
    Dia hoje;
    int temVencido = 0;
    char opc;

    // Pega data de hoje
    time_t t;
    struct tm tm_info;
    t = time(NULL);
    tm_info = *localtime(&t);
    hoje.dia  = tm_info.tm_mday;
    hoje.mes  = tm_info.tm_mon + 1;
    hoje.ano  = tm_info.tm_year + 1900;

    system("cls");
    printf("======== Descarte de Produtos Vencidos ========\n");

    arquivo = fopen("produtos.bin", "rb");
    if (arquivo == NULL) {
        printf("\nNenhum produto cadastrado ou erro ao abrir produtos.bin.\n");
        system("pause");
        return;
    }

    // Primeiro: listar vencidos
    while (fread(&p, sizeof(Produto), 1, arquivo) == 1) {
        if (produtoExpirado(p, hoje)) {
            if (!temVencido) {
                printf("\nProdutos vencidos encontrados:\n");
            }
            temVencido = 1;

            printf("\n================================\n");
            printf("Codigo: %d\n", p.cod);
            printf("Nome: %s", p.nome);
            printf("Descricao: %s", p.descricao);
            printf("Laboratorio: %s", p.laboratorio);
            printf("Tipo: %s", p.tipo);
            printf("Quantidade: %d\n", p.quantidade);
            printf("Validade: ");
            printData(p.validade.dia, p.validade.mes, p.validade.ano);
            printf("================================\n");
        }
    }

    fclose(arquivo);

    if (!temVencido) {
        printf("\nNenhum produto vencido para descartar.\n");
        system("pause");
        return;
    }

    // Confirmacao
    printf("\nDeseja descartar TODOS os produtos vencidos listados? [S/N]\n> ");
    limpaBuffer();
    opc = toupper(getche());

    if (opc != 'S') {
        printf("\n\nOperacao cancelada. Nenhum produto foi descartado.\n");
        system("pause");
        return;
    }

    // Segundo passo: recriar produtos.bin sem os vencidos
    arquivo = fopen("produtos.bin", "rb");
    if (arquivo == NULL) {
        printf("\nErro ao reabrir produtos.bin.\n");
        system("pause");
        return;
    }

    temp = fopen("temp.bin", "wb");
    if (temp == NULL) {
        printf("\nErro ao criar arquivo temporario.\n");
        fclose(arquivo);
        system("pause");
        return;
    }

    while (fread(&p, sizeof(Produto), 1, arquivo) == 1) {
        if (!produtoExpirado(p, hoje)) {
            fwrite(&p, sizeof(Produto), 1, temp);
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove("produtos.bin");
    rename("temp.bin", "produtos.bin");

    printf("\nProdutos vencidos descartados com sucesso!\n");
    system("pause");
}

/* ======== Relatorios ======== */

void relatorioProdutosProximosVencimento() {
    FILE *arquivo;
    Produto p;
    Dia hoje;
    int opcao;
    int limiteDias = 0;
    char tipos[100][100];
    int qtdTipos, escolha;
    char tipoEscolhido[100];
    int encontrou = 0;

    // Data de hoje
    time_t t;
    struct tm tm_info;
    t = time(NULL);
    tm_info = *localtime(&t);
    hoje.dia  = tm_info.tm_mday;
    hoje.mes  = tm_info.tm_mon + 1;
    hoje.ano  = tm_info.tm_year + 1900;

    system("cls");
    printf("==== Relatorio de Produtos Proximo ao Vencimento ====\n");
    printf("Considerar produtos que vencem em ate:\n");
    printf("1 - 30 dias\n");
    printf("2 - 60 dias\n");
    printf("3 - 90 dias\n");
    printf("> ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            limiteDias = 30;
            break;
        case 2:
            limiteDias = 60;
            break;
        case 3:
            limiteDias = 90;
            break;
        default:
            printf("Opcao invalida.\n");
            system("pause");
            return;
    }

    // Escolher tipo de produto
    qtdTipos = listarTipos(tipos);
    if (qtdTipos == 0) {
        printf("\nNenhum tipo de produto cadastrado!\n");
        system("pause");
        return;
    }

    printf("\n--- Tipos de Produto Cadastrados ---\n");
    for (int i = 0; i < qtdTipos; i++) {
        printf("%d - %s", i + 1, tipos[i]);
    }

    printf("\nSelecione o tipo para o relatorio: ");
    scanf("%d", &escolha);

    while (escolha < 1 || escolha > qtdTipos) {
        printf("Opcao invalida! Digite novamente: ");
        scanf("%d", &escolha);
    }

    strcpy(tipoEscolhido, tipos[escolha - 1]);

    // Abre arquivo de produtos
    arquivo = fopen("produtos.bin", "rb");
    if (arquivo == NULL) {
        printf("\nErro ao abrir produtos.bin ou nenhum produto cadastrado.\n");
        system("pause");
        return;
    }

    system("cls");
    printf("==== Relatorio de Produtos Proximo ao Vencimento ====\n");
    printf("Tipo: %s", tipoEscolhido);
    printf("Periodo: ate %d dias\n\n", limiteDias);

    while (fread(&p, sizeof(Produto), 1, arquivo) == 1) {
        // Filtra pelo tipo
        if (stricmp(p.tipo, tipoEscolhido) == 0) {
            // Ignora vencidos
            if (!produtoExpirado(p, hoje)) {
                int diasRestantes = diferencaDias(hoje, p.validade);

                if (diasRestantes >= 0 && diasRestantes <= limiteDias) {
                    printf("=============================================\n");
                    printf("Codigo: %d\n", p.cod);
                    printf("Nome: %s", p.nome);
                    printf("Descricao: %s", p.descricao);
                    printf("Laboratorio: %s", p.laboratorio);
                    printf("Quantidade: %d\n", p.quantidade);
                    printf("Valor: %.2f\n", p.valor);
                    printf("Desconto: %.2f %%\n", p.desconto);
                    printf("Validade: ");
                    printData(p.validade.dia, p.validade.mes, p.validade.ano);
                    printf("Dias restantes: %d\n", diasRestantes);
                    encontrou = 1;
                }
            }
        }
    }

    if (!encontrou) {
        printf("\nNenhum produto encontrado para esse tipo dentro do periodo.\n");
    }

    printf("\n=============================================\n");
    fclose(arquivo);
    system("pause");
}

void relatorioCaixa() {
    FILE *arquivo;
    ProdutoVendido pv;
    float total = 0.0f;
    int encontrou = 0;

    arquivo = fopen("produtosVendidos.bin", "rb");

    system("cls");
    printf("======== Relatorio de Caixa ========\n");

    if (arquivo == NULL) {
        printf("\nNenhuma venda registrada ou erro ao abrir o arquivo.\n");
        system("pause");
        return;
    }

    while (fread(&pv, sizeof(ProdutoVendido), 1, arquivo) == 1) {
        // considera so vendas nao devolvidas
        if (!pv.devolvido) {
            total += pv.valorVenda;
            encontrou = 1;
        }
    }

    fclose(arquivo);

    if (!encontrou) {
        printf("\nNenhuma venda valida encontrada (todas devolvidas ou arquivo vazio).\n");
    } else {
        printf("\nTotal vendido (sem devolucoes): R$ %.2f\n", total);
    }

    printf("====================================\n");
    system("pause");
}

/* ======== Login & Sistemas ======== */

int loginAdministrador(char nome[]) {
    FILE *arquivo;
    Administrador adm;
    char usuario[200], senha[200];

    system("cls");

    printf("\nDigite o usuario: ");
    limpaBuffer();
    fgets(usuario, 199, stdin);

    printf("\nDigite a senha: ");
    fgets(senha, 199, stdin);

    arquivo = fopen("administradores.bin", "rb");
    if (arquivo == NULL) {
        printf("\nNenhum administrador cadastrado!\n");
        system("pause");
        return 0;
    }

    while(fread(&adm, sizeof(Administrador), 1, arquivo) == 1) {
        if (stricmp(adm.usuario, usuario) == 0 && stricmp(adm.senha, senha) == 0) {
            strcpy(nome, adm.usuario);
            fclose(arquivo);
            return 1; 
        }
    }

    fclose(arquivo);
    return 0; 
}

int loginCliente(char nome[]) {
    FILE *arquivo;
    Cliente cliente;
    char cpf[15];

    system("cls");

    printf("\nDigite o CPF: ");
    limpaBuffer();
    fgets(cpf, 14, stdin);

    arquivo = fopen("clientes.bin", "rb");
    if (arquivo == NULL) {
        printf("\nNenhum cliente cadastrado!\n");
        system("pause");
        return 0;
    }

    while(fread(&cliente, sizeof(Cliente), 1, arquivo) == 1) {
        if (strcmp(cliente.cpf, cpf) == 0) {
            strcpy(nome, cliente.nome);
            fclose(arquivo);
            return 1; 
        }
    }

    fclose(arquivo);
    return 0; 
}

void sistemaAdmin(char adm[]) {
    int menu, submenu;

    do {
        system("cls");

        printf("======== Administrador %s ========\n", adm);
        printf("\n1: Administradores");
        printf("\n2: Gerenciar Clientes");
        printf("\n3: Gerenciar Produtos");
        printf("\n4: Gerenciar Tipos de Produto");
        printf("\n5: Gerenciar Laboratorios");
        printf("\n6: Definir promocao de produtos proximos ao vencimento");
        printf("\n7: Descartar produtos vencidos");
        printf("\n8: Relatorios");
        printf("\n9: Voltar para login");
        printf("\n> ");
        scanf("%d", &menu);

        switch(menu) {
            case 1:
                do {
                    system("cls");
                    printf("======== Administradores ========\n");
                    printf("1: Cadastrar Administrador\n");
                    printf("2: Exibir Administradores\n");
                    printf("3: Editar Administrador\n");
                    printf("4: Excluir Administrador\n");
                    printf("5: Voltar\n");
                    printf("> ");
                    scanf("%d", &submenu);

                    switch(submenu) {
                        case 1: cadastrarAdministrador(); break;
                        case 2: exibirAdministradores(); break;
                        case 3: alterarAdministrador(); break;
                        case 4: excluirAdministrador(); break;
                        case 5:
                            printf("Voltando ao menu...\n\n");
                            system("pause");
                            break;
                        default:
                            printf("Opcao invalida!\n\n");
                            system("pause");
                            break;
                    }
                } while(submenu != 5);
                break;

            case 2:
                do {
                    system("cls");
                    printf("======== Clientes ========\n");
                    printf("1: Cadastrar Cliente\n");
                    printf("2: Exibir Clientes\n");
                    printf("3: Editar Cliente\n");
                    printf("4: Excluir Cliente\n");
                    printf("5: Voltar ao menu\n");
                    printf("> ");
                    scanf("%d", &submenu);

                    switch(submenu) {
                        case 1: cadastrarCliente(); break;
                        case 2: exibirClientes(); break;
                        case 3: alterarCliente(); break;
                        case 4: excluirCliente(); break;
                        case 5:
                            printf("Voltando ao menu...\n\n");
                            system("pause");
                            break;
                        default:
                            printf("Opcao invalida!\n\n");
                            system("pause");
                            break;
                    }
                } while(submenu != 5);
                break;
                
            case 3:
                do {
                    system("cls");
                    printf("======== Produto ========\n");
                    printf("1: Cadastrar Produto\n");
                    printf("2: Exibir Produto\n");
                    printf("3: Editar Produto\n");
                    printf("4: Excluir Produto\n");
                    printf("5: Voltar ao menu\n");
                    printf("> ");
                    scanf("%d", &submenu);

                    switch(submenu) {
                        case 1: cadastrarProduto(); break;
                        case 2: exibirProduto(); break;
                        case 3: alterarProduto(); break;
                        case 4: excluirProduto(); break;
                        case 5:
                            printf("Voltando ao menu...\n\n");
                            system("pause");
                            break;
                        default:
                            printf("Opcao invalida!\n\n");
                            system("pause");
                            break;
                    }
                } while(submenu != 5);
                break;

            case 4:
                do {
                    system("cls");
                    printf("======== Tipos de Produto ========\n");
                    printf("1: Cadastrar Tipos de Produto\n");
                    printf("2: Exibir Tipos de Produto\n");
                    printf("3: Editar Tipos de Produto\n");
                    printf("4: Excluir Tipos de Produto\n");
                    printf("5: Voltar ao menu\n");
                    printf("> ");
                    scanf("%d", &submenu);

                    switch(submenu) {
                        case 1: cadastrarTipoProduto(); break;
                        case 2: exibirTipos(); break;
                        case 3: alterarTipoProduto(); break;
                        case 4: excluirTipoProduto(); break;
                        case 5:
                            printf("Voltando ao menu...\n\n");
                            system("pause");
                            break;
                        default:
                            printf("Opcao invalida!\n\n");
                            system("pause");
                            break;
                    }
                } while(submenu != 5);
                break;

            case 5:
                do {
                    system("cls");
                    printf("======== Laboratorios ========\n");
                    printf("1: Cadastrar Laboratorios\n");
                    printf("2: Exibir Laboratorios\n");
                    printf("3: Editar Laboratorios\n");
                    printf("4: Excluir Laboratorios\n");
                    printf("5: Voltar ao menu\n");
                    printf("> ");
                    scanf("%d", &submenu);

                    switch(submenu) {
                        case 1: cadastrarLaboratorio(); break;
                        case 2: exibirLaboratorios(); break;
                        case 3: alterarLaboratorio(); break;
                        case 4: excluirLaboratorio(); break;
                        case 5:
                            printf("Voltando ao menu...\n\n");
                            system("pause");
                            break;
                        default:
                            printf("Opcao invalida!\n\n");
                            system("pause");
                            break;
                    }
                } while(submenu != 5);
                break;

            case 6:
                definirPromocao();
                break;

            case 7:
                descartarProdutosVencidos();
                break;

            case 8:
                do {
                    system("cls");
                    printf("======== Relatorios ========\n");
                    printf("1: Relatorio de Produtos Proximo ao Vencimento\n");
                    printf("2: Controle de Estoque\n");
                    printf("3: Relatorio de Caixa\n");
                    printf("4: Voltar\n");
                    printf("> ");
                    scanf("%d", &submenu);

                    switch (submenu) {
                        case 1: relatorioProdutosProximosVencimento(); break;
                        case 2: controlarEstoque(); break;
                        case 3: relatorioCaixa(); break;
                        case 4:
                            printf("Voltando ao menu do administrador...\n");
                            system("pause");
                            break;
                        default:
                            printf("Opcao invalida!\n");
                            system("pause");
                            break;
                    }
                } while (submenu != 4);
                break;

            case 9:
                printf("Voltando ao login...\n\n");
                system("pause");
                break;

            default:
                printf("Opcao invalida!");
                system("pause");
                break;
        }
    } while(menu != 9);
}

void sistemaCliente(char cliente[]) {
    int menu;

    do {
        system("cls");

        printf("======== Cliente %s ======== \n", cliente);
        printf("\n1: Exibir produtos disponiveis");
        printf("\n2: Comprar produtos");
        printf("\n3: Ver compras realizadas");
        printf("\n4: Devolver produtos");
        printf("\n5: Voltar para login\n");
        printf("> ");
        scanf("%d", &menu);
     
        switch(menu) {
            case 1:
                exibirProduto();
                break;
            case 2:
                comprarProdutos();
                break;
            case 3:
                exibirComprasRealizadas();
                break;
            case 4:
                devolverProdutos();
                break;
            case 5:
                printf("Voltando ao login...\n");
                system("pause");
                break;
            default:
                printf("Opcao invalida!");
                system("pause");
        }
    } while(menu != 5);
}

int main() {
    int menuLogin;
    char nomeAdm[200];
    char nomeCliente[200];

    // Garante que exista pelo menos um admin padrao
    criarAdminPadrao();

    do {
        system("cls");
        printf("\n======== Bio-System ========\n");
        printf("1: Administrador\n");
        printf("2: Cliente\n");
        printf("3: Sair\n");
        printf("> ");
        scanf("%d", &menuLogin);

        switch (menuLogin) {
        case 1:
            if (loginAdministrador(nomeAdm)) {
                sistemaAdmin(nomeAdm);
            } else {
                printf("\nUsuario ou senha incorretos!\n");
                system("pause");
            }
            break;
        case 2:
            //if (loginCliente(nomeCliente)) {
                sistemaCliente(nomeCliente);
            //} else {
            //    printf("\nLogin incorreto!\n");
            //    system("pause");
            //}
            break;
        case 3:
            printf("\nSaindo do sistema...\n\n");
            system("pause");
            break;
        default:
            printf("\nOpcao invalida!\n\n");
            system("pause");
            break;
        }
    } while (menuLogin != 3);

    return 0;
}

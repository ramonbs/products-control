#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

//quantidade maxima de produtos
#define MAX_PRODUTOS 9

//tamanhos das variaveis
#define NOME_DO_PRODUTO_TAM 100
#define MARCA_DO_PRODUTO_TAM 50
#define CATEGORIA_DO_PRODUTO_TAM 50
#define NOME_FORNECEDOR_TAM 100
#define CNPJ_FORNECEDOR_TAM 20

//quantidade de itens por pagina na consulta
#define MAX_PAGINA 3

//estrutura chamada data para definir o dia, mes e ano
typedef struct Data
{
    int dia, mes, ano;
} Data;

//estrutura do produto com todas as informacoes necessarias
typedef struct Produto
{
    int
        codigo_produto,
        qtd_disponivel_produto; //criacao de variaveis do tipo inteiro
    char
        nome_do_produto[NOME_DO_PRODUTO_TAM],
        marca_do_produto[MARCA_DO_PRODUTO_TAM], //string do tipo char com os seus devidos tamanhos de armazenamento
        categoria_produto[CATEGORIA_DO_PRODUTO_TAM],
        nome_fornecedor[NOME_FORNECEDOR_TAM], //string do tipo char com os seus devidos tamanhos de armazenamento
        cnpj_fornecedor[CNPJ_FORNECEDOR_TAM]; //string do tipo char com o seu devido tamanho de armazenamento
    float preco_produto;                      //criacao de variaveis do tipo inteiro
    Data fab, val;                            //variavel chamada 'd' do tipo Data (que e a struct)

} Produto;

Produto p[MAX_PRODUTOS];         //criacao do vetor p[MAX_PRODUTOS] que contera todas as informacoes da struct Produto
int produtos_ja_cadastrados = 0; //variavel de controle de tamanho

//declara a assinatura das funcoes
void acao();
char limpaStdin();
void imprimeLinha();
void Cadastrar();
void Consultar();
void Alterar();
void Copiar();

int main()
{
    setlocale(LC_ALL, "portuguese");
    system("cls");

    int opcao; //criacao da variavel 'opcao' do tipo inteiro

    //inicio da estrutura de repeticao do while (fa�a)
    do
    {
        imprimeLinha();
        acao(); //chamamento da funcao acao()
        imprimeLinha();
        printf("Digite o numero da sua opcao: \n");
        scanf("%d", &opcao); //ler uma das opcoes abaixo
        imprimeLinha();

        limpaStdin();

        //inicio da estrutura condicional switch case. Ler o valor da opcao
        switch (opcao)
        {
        case 1:
            Cadastrar();
            break; //caso seja a primeira opcao, chama a funcao Cadastrar
        case 2:
            Consultar();
            break; //caso seja a primeira opcao, chama a funcao Cadastrar
        case 3:
            Alterar();
            break; //caso seja a primeira opcao, chama a funcao Consultar
        case 4:
            Copiar();
            break;
        case 5:
            system("pause");
            break; //caso seja a quarta opcao, encerra o programa
        default:
            printf("Opcao invalida!\n\n");
            break; //se n�o for nenhuma das opcoes anteriores imprime a mensagem na tela
        }
    } while (opcao != 5); //repete a estrutura enquanto a opcao for diferente de '4'

    return 0;
}

void imprimeLinha()
{
    printf("--------------------------------\n");
}

//funcao para imprimir as opcoes oferecidas pelo sistema
void acao()
{
    printf("Opcoes:\n\n");
    printf("1 - Cadastrar\n\n");
    printf("2 - Consultar\n\n");
    printf("3 - Alterar\n\n");
    printf("4 - Copiar dados para txt\n\n");
    printf("5 - Sair\n\n");
}

//funcao utilitaria pra limpar a stdin e tornar o ultimo caractere diferente de stdin lido
char limpaStdin()
{
    char c;
    char ultimo = '\0';

    //pega todos os caracteres da stdin ate o fim dela ou ate a quebra de linha, fazendo ela "reiniciar"
    do
    {
        c = getchar();

        if (c != '\n' && c != EOF)
        {
            ultimo = c;
        }
    } while (c != '\n' && c != EOF);

    return ultimo;
}

//funcao utilitaria de alerta
void alertaSobreEnter()
{
    printf("(ATENCAO: Talvez voce precise apertar ENTER mais de uma vez)\n");
}

//funcao utilitaria para informar o formato de entrada das datas
void exemploDeData()
{
    printf("(Exemplo: Inserir \"02 02 2020\" registra a data 02/02/2020)\n");
}

//funcao utilitaria para deixar o vetor de carecteres pronto para impressao
void ajustarVetorDeCaracteres(char vetor[])
{
    int i, tamanho_do_vetor = strlen(vetor);

    for (i = 0; i < tamanho_do_vetor; i++)
    {
        if (vetor[i] == '\n')
        {
            vetor[i] = '\0';
        }
    }
}

//funcao utilitaria que procura um produto no vetor atraves do codigo do produto
//e retorna o indice do produto no vetor ou retorna -1 se nao encontrar
int acharProduto(int codigo)
{
    int i;

    for (i = 0; i < produtos_ja_cadastrados; i++)
    {
        if (p[i].codigo_produto == codigo)
        {
            break;
        }
    }

    if (i == produtos_ja_cadastrados)
        return -1;

    return i;
}

//funcao utilitaria para saber se a data e valida
int validarData(Data d)
{
    int dia = d.dia;
    int mes = d.mes;
    int ano = d.ano;

    //ano nao pode ser negativo
    if (ano < 0)
    {
        printf("Data Invalida: Ano invalido\n");
        return 0;
    }

    //mes nao pode ser negativo nem maior que 12
    if (mes < 1 || mes > 12)
    {
        printf("Data Invalida: Mes invalido\n");
        return 0;
    }

    //dia nao pode ser negativo nem maior que 31
    if (dia < 1 || dia > 31)
    {
        printf("Data Invalida: Dia invalido\n");
        return 0;
    }

    int eh_bissexto = ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0);

    if (mes == 2)
    {
        if (dia > 29 || (!eh_bissexto && dia > 28))
        {
            printf("Data Invalida: Dia invalido\n");
            return 0;
        }
    }

    if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
    {
        if (dia == 31)
        {
            printf("Data Invalida: Dia invalido\n");
            return 0;
        }
    }

    return 1;
}

//funcao utilitaria pra comparar datas, se a d1 for anterior à d2 a funcao retorna -1, se for o mesmo dia retorna 0 e se for posterior retorna 1
int compararDatas(Data d1, Data d2)
{
    if (d1.ano > d2.ano)
    {
        return 1;
    }
    else if (d1.ano < d2.ano)
    {
        return -1;
    }

    if (d1.mes > d2.mes)
    {
        return 1;
    }
    else if (d1.mes < d2.mes)
    {
        return -1;
    }

    if (d1.dia > d2.dia)
    {
        return 1;
    }
    else if (d1.dia < d2.dia)
    {
        return -1;
    }

    return 0;
}

//funcao utilitaria pra dizer pro usuario o que aconteceu com as datas
int compararDatasEMostrarErro(Data fabricacao, Data validade)
{
    int retorno = compararDatas(fabricacao, validade);

    if (retorno == 1)
    {
        printf("Erro: A data de validade e anterior a data de fabricacao\n");
    }

    return retorno;
}

//funcao Cadastrar
void Cadastrar()
{
    int i, qtdProduto; //criacao de variaveis do tipo inteiro

    Data d; //chamamento da struct Data

    system("cls");                                                                                           //limpar a tela
    printf("Digite a quantidade de produtos que deseja cadastrar:\n(Digite -1 para cancelar a operacao)\n"); //Usuario digita a quantidade
    scanf("%d", &qtdProduto);                                                                                //armazena o valor na variavel qtdProduto

    if (qtdProduto == -1)
    {
        system("cls");
        return;
    }

    //estrutura condicional para impedir cadastro de mais produtos que o permitido
    if (produtos_ja_cadastrados + qtdProduto > MAX_PRODUTOS)
    {
        printf("Voce ja cadastrou %d produtos. Voce so pode cadastrar mais %d produtos.\n",
               produtos_ja_cadastrados, MAX_PRODUTOS - produtos_ja_cadastrados);
        return;
    }

    //estrutura de repeticao 'for' que se repete de acordo com a quantidade de produto digitada pelo usuario. Contador 'i' inicializado com 0, depois incrementa mais um a cada la�o de repeti��o
    for (
        //comeca do índice 3 se ja houverem 3 produtos cadastrados e como a
        //contagem comeca de 0, essa e a posicao 4
        i = produtos_ja_cadastrados;
        //se o numero de produtos a serem inseridos for 2 e ja houverem 3
        //produtos cadastrados, o ultimo indice deve ser menor que 2+3=5, dessa
        //forma a ultima posicao a ser acessada e a p[4], que e o quinto produto
        i < (produtos_ja_cadastrados + qtdProduto);
        i++)
    {
        system("cls");

        printf("Digite os dados do produto %d \n", i + 1); //mensagem que aparece na tela

        printf("Codigo: \n");                //mensagem que aparece na tela
        scanf("%d", &(p[i].codigo_produto)); //armazena o codigo na posicao 'i' do vetor

        //se houver algum produto com o codigo registrado, reinicie o cadastro
        if (acharProduto(p[i].codigo_produto) != -1)
        {
            i--; //decrementa o valor de i para retornar ao mesmo numero no proximo loop
            printf("Erro: Codigo de produto ja registrado\n");
            system("pause");
            continue; //continua o loop e incrementa i, como definido no for
        }

        limpaStdin(); //limpa o lixo da memoria (fflush nao funciona com fgets)
        printf("Nome: ");
        alertaSobreEnter();
        fgets(p[i].nome_do_produto, NOME_DO_PRODUTO_TAM, stdin); //armazena o nome na posicao 'i' do vetor
        ajustarVetorDeCaracteres(p[i].nome_do_produto);          //tira o '\n' de dentro do vetor de caracteres para na hora de imprimir funcionar certinho

        limpaStdin();
        printf("Marca: ");
        alertaSobreEnter();
        fgets(p[i].marca_do_produto, MARCA_DO_PRODUTO_TAM, stdin); //armazena a marca na posicao 'i' do vetor
        ajustarVetorDeCaracteres(p[i].marca_do_produto);

        limpaStdin();
        printf("Categoria: ");
        alertaSobreEnter();
        fgets(p[i].categoria_produto, CATEGORIA_DO_PRODUTO_TAM, stdin); //armazena a categoria na posicao 'i' do vetor
        ajustarVetorDeCaracteres(p[i].categoria_produto);

        printf("Quantidade no estoque: \n");
        scanf("%d", &(p[i].qtd_disponivel_produto)); //armazena a quantidade na posicao 'i' do vetor

        do
        {
            printf("Data de fabricacao: ");
            exemploDeData();                                              //imprime um exemplo de data a ser inserido
            scanf("%d%d%d", &p[i].fab.dia, &p[i].fab.mes, &p[i].fab.ano); //armazena a data de fabrica��o na posicao 'i' do vetor
        } while (!validarData(p[i].fab));

        do
        {
            printf("Data de validade: ");
            exemploDeData();
            scanf("%d%d%d", &p[i].val.dia, &p[i].val.mes, &p[i].val.ano); //armazena a data de validade na posicao 'i' do vetor
        } while (!validarData(p[i].val) || compararDatasEMostrarErro(p[i].fab, p[i].val) == 1);

        printf("Preco: \n");
        scanf("%f", &p[i].preco_produto); //armazena o pre�o na posicao 'i' do vetor

        printf("\nDados do fornecedor \n");

        limpaStdin();
        printf("Nome: ");
        alertaSobreEnter();
        fgets(p[i].nome_fornecedor, NOME_FORNECEDOR_TAM, stdin); //armazena o nome do fornecedor na posicao 'i' do vetor
        ajustarVetorDeCaracteres(p[i].nome_fornecedor);

        limpaStdin();
        printf("CNPJ: ");
        alertaSobreEnter();
        fgets(p[i].cnpj_fornecedor, CNPJ_FORNECEDOR_TAM, stdin); //armazena o CNPJ na posicao 'i' do vetor
        ajustarVetorDeCaracteres(p[i].cnpj_fornecedor);

        system("cls"); //limpar a tela
    }

    produtos_ja_cadastrados += qtdProduto;
}

//função para copiar os produtos cadastrados para arquivo .txt
void copiarProdutos (Produto produto, int indice)
{
    int i;
    FILE *pont_arq; // cria variável ponteiro para o arquivo

    pont_arq = fopen("arquivo_palavra.txt", "w");//cria arquivo .txt chamado "arquivo_palavra"

    //testando se o arquivo foi realmente criado
    if(pont_arq == NULL)
    {
    printf("Erro na abertura do arquivo!");
    return 1;
    }

    //loop para percorrer e transcrever todos os produtos cadastrados para dentro do texto
    for(i=0; i<produtos_ja_cadastrados; i++){
        fprintf(pont_arq,"Produto %d\n\n", indice);
        fprintf(pont_arq,"Dados do Produto \n\n");
        fprintf(pont_arq,"Codigo: %d\n", p[i].codigo_produto);
        fprintf(pont_arq,"Nome: %s\n", p[i].nome_do_produto);
        fprintf(pont_arq,"Marca: %s\n", p[i].marca_do_produto);
        fprintf(pont_arq,"Categoria: %s\n", p[i].categoria_produto);
        fprintf(pont_arq,"No estoque: %d unidades\n", p[i].qtd_disponivel_produto);
        fprintf(pont_arq,"Fabricacao: %2d/%2d/%4d\n", p[i].fab.dia, p[i].fab.mes, p[i].fab.ano);
        fprintf(pont_arq,"Validade: %2d/%2d/%4d\n", p[i].val.dia, p[i].val.mes, p[i].val.ano);
        fprintf(pont_arq,"Preco: R$%0.2f\n\n", p[i].preco_produto);
        fprintf(pont_arq,"Dados do Fornecedor \n\n");
        fprintf(pont_arq,"Nome: %s\n\n", p[i].nome_fornecedor);
        fprintf(pont_arq,"CNPJ: %s\n\n", p[i].cnpj_fornecedor);
    }

    fclose(pont_arq);//fecha o arquivo e salva as informações
}

void mostrarProduto(Produto produto, int indice)
{
    imprimeLinha();
    printf("Produto %d\n", indice);
    imprimeLinha();
    printf("Dados do Produto \n\n");

    printf("Codigo: %d\n", produto.codigo_produto);
    printf("Nome: %s\n", produto.nome_do_produto);
    printf("Marca: %s\n", produto.marca_do_produto);
    printf("Categoria: %s\n", produto.categoria_produto);
    printf("No estoque: %d unidades\n", produto.qtd_disponivel_produto);
    printf("Fabricacao: %2d/%2d/%4d\n", produto.fab.dia, produto.fab.mes, produto.fab.ano);
    printf("Validade: %2d/%2d/%4d\n", produto.val.dia, produto.val.mes, produto.val.ano);
    printf("Preco: R$%0.2f\n", produto.preco_produto);
    imprimeLinha();
    printf("Dados do Fornecedor \n\n");

    printf("Nome: %s\n", produto.nome_fornecedor);
    printf("CNPJ: %s\n", produto.cnpj_fornecedor);
    imprimeLinha();
    putchar('\n');
}


void Copiar()
{
    system("cls");
    int i;

    //variavel para sair ou nao da funcao
    char controle = 'n';

    do
    {
        copiarProdutos(p[i], i ++); //mostra o produto

        printf("Continuar? [S/N]: ");
        controle = getchar();
        limpaStdin();

        system("pause");
        system("cls");
    } while (controle == 's' || controle == 'S');
}

void Consultar()
{
    system("cls");

    if (produtos_ja_cadastrados == 0)
    {
        imprimeLinha();
        printf("Nao ha produtos cadastrados.\n");
        imprimeLinha();
        return;
    }

    //variavel de indice de produtos
    int i;

    //variavel para controlar a pagina, comeca em -1 porque dentro do
    //do{}while() ele vai ser aumentado na primeira passada para 0
    int pagina = -1;

    //variavel para sair ou nao da funcao
    char controle = 'n';

    do
    {
        //se chegou ao fim dos itens, volta pro comeco
        if (i >= produtos_ja_cadastrados && controle != 'n')
        {
            printf("Voce ja viu todos os registros, voltando ao fim da lista...\n\n");

            //faz o valor da pagina voltar a ser -1 para ser aumentada para 0 logo em seguida
            pagina = -1;
        }

        //aumenta o numero da pagina a cada passada
        pagina++;

        imprimeLinha();
        printf("Pagina %d:\n", pagina + 1); //mostra a pagina

        //faz a paginacao
        for (
            //se a pagina for 2 e o tamanho de itens por pagina for 3,
            //o primeiro item a ser mostrado e o item p[0 + (3*1)]
            //(repare que o valor da pagina e 1 ja que a contagem comeca de 0)
            //desse modo o primeiro item a ser mostrado e o p[3], que e o quarto
            //item do vetor
            i = 0 + (MAX_PAGINA * pagina);
            //se a pagina mostra no maximo 3, mas a quantidade maxima de itens
            //no vetor for 2, ele so mostra 2
            i < produtos_ja_cadastrados && i < (MAX_PAGINA * (pagina + 1));
            i++)
        {
            mostrarProduto(p[i], i + 1); //mostra o produto
        }

        printf("Continuar? [S/N]: ");
        controle = getchar();
        limpaStdin();

        system("pause");
        system("cls");
    } while (controle == 's' || controle == 'S');
}

//funcao utilitaria que serve pra retornar verdadeiro ou falso (sim ou nao)
int simOuNao(char mensagem[])
{
    char resposta;

    printf("%s [S/N]:\n", mensagem);
    resposta = getchar();
    limpaStdin();

    if (resposta == 's' || resposta == 'S')
    {
        return 1;
    }

    return 0;
}

void Alterar()
{
    int alteracoes = 0;
    int codigo, indice = -1;

    int controle;

    system("cls");

    imprimeLinha();

    printf("Digite o codigo do produto:\n");
    scanf("%d", &codigo);
    limpaStdin();

    indice = acharProduto(codigo);

    if (indice == -1)
    {
        printf("Erro: Produto nao encontrado!\n");
        return;
    }

    mostrarProduto(p[indice], indice + 1);

    controle = simOuNao("Deseja alterar algum dado do produto?");

    if (controle == 1)
    {
        controle = simOuNao("Deseja alterar o codigo do produto?");

        if (controle == 1)
        {
            int novoCodigo;
            int podeMudar = 0;
            printf("Codigo: \n");     //mensagem que aparece na tela
            scanf("%d", &novoCodigo); //armazena o codigo na posicao 'i' do vetor
            limpaStdin();

            int outroIndice = acharProduto(novoCodigo);

            //se o indice for o mesmo mostra uma mensagem de erro e continua a operacao
            if (indice == outroIndice)
            {
                printf("Erro: O codigo inserido e o mesmo\n\n");
            }
            //se houver algum produto com o codigo registrado, cancele a operacao
            else if (outroIndice != -1)
            {
                printf("Erro: Codigo de produto ja registrado\n");
            }
            else
            {
                podeMudar = 1;
            }

            if (podeMudar == 1)
            {
                alteracoes++;
                p[indice].codigo_produto = novoCodigo;
            }
        }

        controle = simOuNao("Deseja alterar o nome do produto?");

        if (controle == 1)
        {
            printf("Nome: ");
            alertaSobreEnter();
            fgets(p[indice].nome_do_produto, NOME_DO_PRODUTO_TAM, stdin); //armazena o nome na posicao 'i' do vetor
            ajustarVetorDeCaracteres(p[indice].nome_do_produto);          //tira o '\n' de dentro do vetor de caracteres para na hora de imprimir funcionar certinho
            limpaStdin();
            alteracoes++;
        }

        controle = simOuNao("Deseja alterar a marca do produto?");

        if (controle == 1)
        {
            printf("Marca: ");
            alertaSobreEnter();
            fgets(p[indice].marca_do_produto, MARCA_DO_PRODUTO_TAM, stdin); //armazena a marca na posicao 'i' do vetor
            ajustarVetorDeCaracteres(p[indice].marca_do_produto);
            limpaStdin();
            alteracoes++;
        }

        controle = simOuNao("Deseja alterar a categoria do produto?");

        if (controle == 1)
        {
            printf("Categoria: ");
            alertaSobreEnter();
            fgets(p[indice].categoria_produto, CATEGORIA_DO_PRODUTO_TAM, stdin); //armazena a categoria na posicao 'i' do vetor
            ajustarVetorDeCaracteres(p[indice].categoria_produto);
            limpaStdin();
            alteracoes++;
        }

        controle = simOuNao("Deseja alterar a quantidade em estoque do produto?");

        if (controle == 1)
        {
            printf("Quantidade no estoque: \n");
            scanf("%d", &(p[indice].qtd_disponivel_produto)); //armazena a quantidade na posicao 'i' do vetor
            limpaStdin();
            alteracoes++;
        }

        controle = simOuNao("Deseja alterar a data de fabricacao do produto?");

        if (controle == 1)
        {
            do
            {
                printf("Data de fabricacao: ");
                exemploDeData();                                                             //imprime um exemplo de data a ser inserido
                scanf("%d%d%d", &p[indice].fab.dia, &p[indice].fab.mes, &p[indice].fab.ano); //armazena a data de fabrica��o na posicao 'i' do vetor
                limpaStdin();
            } while (!validarData(p[indice].fab));
            alteracoes++;
        }

        controle = simOuNao("Deseja alterar a data de validade do produto?");

        if (controle == 1)
        {
            do
            {
                printf("Data de validade: ");
                exemploDeData();
                scanf("%d%d%d", &p[indice].val.dia, &p[indice].val.mes, &p[indice].val.ano); //armazena a data de validade na posicao 'i' do vetor
                limpaStdin();
            } while (!validarData(p[indice].val) || compararDatasEMostrarErro(p[indice].fab, p[indice].val) == 1);
            alteracoes++;
        }

        controle = simOuNao("Deseja alterar o preco do produto?");

        if (controle == 1)
        {
            printf("Preco: \n");
            scanf("%f", &p[indice].preco_produto); //armazena o preco na posicao 'i' do vetor
            limpaStdin();
            alteracoes++;
        }
    }

    controle = simOuNao("Deseja alterar algum dado do fornecedor?");

    if (controle == 1)
    {
        controle = simOuNao("Deseja alterar o nome do fornecedor?");

        if (controle == 1)
        {
            printf("Nome: ");
            alertaSobreEnter();
            fgets(p[indice].nome_fornecedor, NOME_FORNECEDOR_TAM, stdin); //armazena o nome do fornecedor na posicao 'i' do vetor
            ajustarVetorDeCaracteres(p[indice].nome_fornecedor);
            limpaStdin();
            alteracoes++;
        }

        controle = simOuNao("Deseja alterar o CNPJ do fornecedor?");

        if (controle == 1)
        {
            printf("CNPJ: ");
            alertaSobreEnter();
            fgets(p[indice].cnpj_fornecedor, CNPJ_FORNECEDOR_TAM, stdin); //armazena o CNPJ na posicao 'i' do vetor
            ajustarVetorDeCaracteres(p[indice].cnpj_fornecedor);
            limpaStdin();
            alteracoes++;
        }
    }

    putchar('\n');

    if (alteracoes > 0)
    {
        printf("Alteracoes salvas!\n");
    }
    else
    {
        printf("Nenhuma alteracao realizada!\n");
    }
}


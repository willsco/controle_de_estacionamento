#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <math.h>
/**< Setado como constante no inicio a fim de facilitar o entendimento do código. */
#define MAXPLACA 8
/**< O PIM IV pede que sejam 20 vagas, então podemos usar a constante NUM_VAGAS para
    guardar o valor de 20 vagas e evitar ter que entrar com estes dados ao decorrer
    do processo.*/
#define NUM_VAGAS 20
/**< -------------------------------------------------------------------------------------------- */
/**< Função responsável por limpar a tela, tanto em
Windows/DOS quanto Linux e Mac OS. */
void clrscr()
{
#if defined _WIN32 || defined _WIN64
    system("cls");
#else
// linux, mac os
    system ("clear");
#endif
}
/**< Função que limpa o buffer de teclado. */
void limpaBuffer(void)
{
    char c;
    while((c = getchar()) !='\n' && c != EOF);
}
/**< Função responsável por converter hora em minutos e
retornar o total de minutos. */
int minutototal(int hora, int minuto)
{
    int T = (hora*60) + minuto;

    return T;
}
/**< Função que define o valor total para valores
de minuto maiores que 60 minutos.*/
float valorTotal(float valorhora, float valoradd, int minestadia)
{
    int UMA_HORA = 60;
    int horas = ceil((double)minestadia/(double)UMA_HORA)-1;
    float M = valorhora+(horas*valoradd);
    return M;
}
/**< -------------------------------------------------------------------------------------------- */
/**<struct responsavel por setar os conteudos de cada vetor em separado. pode ser alterado
    com adições de campos futuramente.*/
struct Vaga
{
    char placa[MAXPLACA];
    int h1, h2, m1, m2, T1, T2, totalT, posicao, regcar;
    float valorT;
};

/**< -------------------------------------------------------------------------------------------- */
/**< Início do programa. */
int main()
{
    setlocale(LC_ALL, "Portuguese"); //seta codificação para teclados baseados em português.
    struct Vaga carro[NUM_VAGAS]; //define o vetor "carro" com 20 posições alinhado ao struct.
    int opcao, i, listar, sair, box; //variáveis para índice.
    int registro = 0, regAux = 0; //variáveis de registro.
    int totalVagas=NUM_VAGAS, dataDia, dataMes, dataAno; //variaveis para data e total de vagas.
    float vlr_hora, horaadicional, vlr_horaAux = 0, somaCaixa; // guarda os valores em R$ para hora e total.
    char loc[8], escolha[2] = "n"; //String para entrada em procura de uma placa específica.
    memset(&carro, 0, sizeof(carro)); //Limpa o lixo para exibição do vetor "carro".
    struct Vaga listagem[NUM_VAGAS];//define as exibições de entradas para o vetor "listagem".
    memset(&listagem, 0, sizeof(listagem)); //Limpa o lixo para exibição do vetor "listagem".

//------------------------------------------------------------------------------------------
    clrscr(); //Chama a função que limpa a tela.
    printf("--------------------------- Configuração Inicial ------------------------\n\n"
           "Digite um valor para a HORA PADRÃO de estadia em R$.\n\tR$");
    scanf("%f", &vlr_hora); //Entrada do valor base em Reais para a hora padrão.
    limpaBuffer();
    printf("Digite um valor para a HORA ADICIONAL em R$.\n\tR$");
    scanf("%f", &horaadicional); //Entrada do valor base em Reais para a hora adicional.
    printf("Digite a data:\n");
    printf("Dia \"DD\": ");
    scanf("%d", &dataDia);
    printf("\nMês corrente \"MM\": ");
    scanf("%d", &dataMes);
    printf("\nAno corrente \"AAAA\": ");
    scanf("%d", &dataAno);
    printf("\tO valor padrão para as horas será de R$%.2f.\n"
           "\tO valor para a hora adicional será de R$%.2f.\n"
           "\tVALORES VÁLIDOS PARA %02d/%02d/%4d."
           "\n\t****** É possível alterar a hora padrão *******"
           "\n\t******* na opção (5) do menu principal. *******"
           "\n\n", vlr_hora, horaadicional, dataDia, dataMes, dataAno);
    system("pause");//Espera que o usuário entre com um comando.
    /**< O laço do{}while() será responsável por retornar para as opções sempre depois que
    uma das opções, a não ser que seja digitado o número correspondente a finalização do programa.*/
    do
    {
        clrscr(); //Chama a função que limpa a tela.

        /**< Apresenta as opções. */
        printf("------------ Bem vindo ao Controle de Estacionamento. ------------\n\n"
               "\tSelecione uma Opção:\n\n"
               "\t1 - Entrada de Veículo.\n\n"
               "\t2 - Listagem de Veículos e Vagas.\n\n"
               "\t3 - Saída de Veículo.\n\n"
               "\t4 - Movimento de Caixa.\n\n"
               "\t5 - Configurações.\n\n"
               "\t6 - Sair.\n\n\n"
               "\tDISPONÍVEIS: %02d VAGA(S).\n"
               "\tOCUPADAS: %02d VAGA(S).\n\n", totalVagas, NUM_VAGAS-totalVagas);


        /**< Pede a entrada de um comando com base na lista acima, numeros de 1 a 6. */
        printf(" Digite o número escolhido: ");
        scanf("%d", &opcao); //Guarda a opção escolhida para ser lançada no "switch".

        /**< De acordo com a opção escolhida, chama o switch e faz a exibição conforme o
        "case" numerado. Não temos um case "default" pela falta de necessidade.*/
        switch(opcao)
        {
/**< -------------------------------------------------------------------------------------------- */
        case 1: //Responsavel pela entrada de dados no vetor "carro".
            limpaBuffer();
            for (i = 0; i < NUM_VAGAS; i++)  //laço que percorre o vetor "carro".
            {

                /**< se a variavel "posicao" dentro struct "temp" contida no vetor "carro"
                for igual a nulo (0) apresentam-se as opções para entrada de placa e horas. */
                if(carro[i].posicao == 0)
                {
                    registro++;//Incrementa o contador de registros a cada registro.
                    carro[i].regcar = registro;//Atribui o valor de registro incrementado ao "regcar" no struc.
                    clrscr(); //Chama a função que limpa a tela.
                    printf("A vaga ocupada Nº'%02d'.\n\n", i+1);//Exibe a vaga onde o veículo será guardado.
                    printf("Digite a placa do veículo no formato \"AAA1111\": ");
                    scanf("%s", carro[i].placa);//Entrada da placa.
                    limpaBuffer();
                    strupr(carro[i].placa);
                    printf("Digite a hora (00 a 23)");
                    scanf("%d", &carro[i].h1);//Entrada da hora inicial.
                    limpaBuffer();
                    printf("Digite os minutos (00 a 59)");
                    scanf("%d", &carro[i].m1);//Entrada do minuto inicial.
                    limpaBuffer();

                    /**< Seta a vaga como ocupada ao final do processo. O campo "posicao"
                    da struct é setado com "1" para que durante o processo de busca não
                    seja sobrescrito e possa exibir "Vaga LIVRE na opção 2 do switch. */
                    carro[i].posicao = 1;
                    carro[i].valorT = 0;
                    totalVagas--;// Controla a quantidade de vagas exibidas DESOCUPADAS.
                    printf("Deseja imprimir o RECIBO? S/N: ");
                    scanf("%s", &escolha[2]);
                    limpaBuffer();
                    if((escolha[2] == 's') || (escolha[2] == 'S'))
                    {
                        clrscr();
                        printf("\t*********************************************************"
                               "\n\t|                    TICKET Nº%03d\t\t\t|"
                               "\n\t*********************************************************"
                               "\n\t|                  CUPOM DE ENTRADA\t\t\t|"
                               "\n\t| ESTACIONAMENTO UNIP - UNIVERSIDADE PAULISTA - PIM-IV\t|"
                               "\n\t| VALOR HORA PADRÃO: R$%.2f.\t\t\t\t|"
                               "\n\t| VALOR FRAÇÃO DE MINUTO: R$%.2f.\t\t\t|"
                               "\n\t| CNPJ: 10.299.371/0002-50\t\t\t\t|"
                               "\n\t| RODOVIA JK (BR-459), KM 107\t\t\t\t|"
                               "\n\t| BAIRRO IPIRANGA - SÃO PAULO - SP\t\t\t|"
                               "\n\t| CEP: 37.550-00\t\t\t\t\t|"
                               "\n\t| PLACA: %s\t\t\t\t\t|"
                               "\n\t| ENTRADA:\t\t\t\t\t\t|"
                               "\n\t| DIA %02d/%02d/%4d AS %02d:%02d.\t\t\t\t|"
                               "\n\t|\t\t\t\t\t\t\t|"
                               "\n\t*********************************************************\n\n",
                               carro[i].regcar,
                               vlr_hora,
                               vlr_hora/60,
                               carro[i].placa,
                               dataDia, dataMes, dataAno, carro[i].h1, carro[i].m1);
                    }
                    system("pause");
                    break;//Quebra o laço "for" finalizando a ENTRADA com sucesso.
                }
                if(totalVagas == 0)
                {
                    printf("Estacionamento CHEIO. Favor aguardar.");
                    break;
                    system("pause");
                }
            }

            break;
/**< -------------------------------------------------------------------------------------------- */
        case 2: //Responsavel pela listagem das vagas.
            clrscr(); //Chama a função que limpa a tela.
            limpaBuffer();
            printf("------------Listagem de Veículos e Vagas------------\n\n");

            for(listar = 0; listar < NUM_VAGAS; listar++) //Laço que irá percorrer o vetor.
            {
                printf("Vaga Nº %02d: ", listar+1);//Imprime na tela o número da vaga.

                /**< Se "posicao" for NULL, exibe "Vaga LiVRE". Senão, mostra a placa do carro
                que está lá. */
                if(carro[listar].posicao == 0)
                {
                    printf("Vaga LIVRE.\n");
                }
                else
                {
                    printf("%s.\tEntrou as %02d:%02d.\n", carro[listar].placa, carro[listar].h1,carro[listar].m1);
                }
            }
            printf("\nFim da listagem.\n");
            system("pause");
            break;
/**< -------------------------------------------------------------------------------------------- */
        case 3://Responsável pela saída de veículos.
            clrscr(); //Chama a função que limpa a tela.
            limpaBuffer();
            printf("------------------------ Saída de Veículo ------------------------\n");
            for(listar = 0; listar < NUM_VAGAS; listar++) //Laço que irá percorrer o vetor.
            {
                if(listar % 2 == 0)
                {
                    printf("\tVaga Nº %02d: ", listar+1);//Imprime na tela o número da vaga.

                    /**< Se "posicao" for NULL, exibe "Vaga LiVRE". Senão, mostra a placa do carro
                    que está lá. */
                    if(carro[listar].posicao == 0)
                    {
                        printf("Vaga LIVRE.\t|\t");
                    }
                    else
                    {
                        printf("%s.\t|\t", carro[listar].placa);
                    }
                }

                if(listar % 2 != 0)
                {
                    printf("Vaga Nº %02d: ", listar+1);//Imprime na tela o número da vaga.

                    /**< Se "posicao" for NULL, exibe "Vaga LiVRE". Senão, mostra a placa do carro
                    que está lá. */
                    if(carro[listar].posicao == 0)
                    {
                        printf("Vaga LIVRE.\t\n");
                    }
                    else
                    {
                        printf("%s.\t\n", carro[listar].placa);
                    }
                }
            }



            printf ("\n\nDigite o número da placa: ");
            scanf("%s", loc);//Joga o valor digitado na variável string "loc".
            for(sair=0; sair<NUM_VAGAS; sair++)//Laço que irá percorrer o vetor.
            {
                /**< Se "loc" for igual a placa do veículo, inicia-se o processo de retirada
                do veículo. */
                if(strcmp (loc, carro[sair].placa) == 0)
                {
                    printf("Registro Nº%03d.\n", carro[sair].regcar);//imprime o número de registro único.
                    printf("Placa CONFIRMADA: %s.\n", carro[sair].placa);//Confirma a placa.

                    /**< Exibe a hora de entrada específica do veículo, permite a entrada da
                    hora e minuto de saída e realiza o cálculo do total utilizando a função
                    minutototal() criada anteriomente. */
                    printf("Hora de Entrada: %02d:%02d\n", carro[sair].h1, carro[sair].m1);
                    printf("\nPor favor, digite a hora de saída (00 a 23): ");
                    scanf("%d", &carro[sair].h2);//variável auxiliar que recebe a hora de saída.
                    limpaBuffer();
                    printf("\nPor favor, digite minutos de saída (00 a 59): ");
                    scanf("%d", &carro[sair].m2);//variável auxiliar que recebe os minutos de saída.
                    limpaBuffer();
                    /**< Converte a hora de entrada em total de minutos. */
                    carro[sair].T1 = minutototal(carro[sair].h1, carro[sair].m1);
                    /**< Converte a hora de saída em minutos. */
                    carro[sair].T2 = minutototal(carro[sair].h2, carro[sair].m2);
                    /**< Subtrai o tempo final do inicial para totalizar um valor negativo ou
                    positivo em minutos. */
                    carro[sair].totalT = carro[sair].T2 - carro[sair].T1;

                    /**< Condicional que cuida da transposição da hora 0, somando o valor de
                    1440 (24*60minutos) caso o valor de totalT(tempo total) seja negativo.*/
                    if(carro[sair].totalT < 0)//Se menor que ZERO (NEGATIVO).
                    {
                        carro[sair].totalT += 1440;
                        printf("O tempo total é: %d.\n", carro[sair].totalT);
                    }
                    else//se for ZERO ou POSITIVO...
                    {
                        printf("O tempo total é: %d.\n", carro[sair].totalT);
                    }

                    /**< Condicional que define o valor a ser pago com base nos minutos de
                    estadia. Se o total de tempo for menor que 60 (00 a 59), é cobrado o
                    valor de base pré-definido.*/
                    if(carro[sair].totalT<60)//Se for MENOR que 60 minutos (0 a 59).
                    {
                        printf("Total a pagar é de R$%.2f.\n", vlr_hora);//Exibe valor padrão de hora.
                        carro[sair].valorT = vlr_hora;
                    }
                    else
                    {
                        //Usa a função valorTotal() para o valor a ser pago com base na fração de hora.
                        carro[sair].valorT = valorTotal(vlr_hora, horaadicional, carro[sair].totalT);
                        printf("O valor a pagar é de R$ %.2f.\n", carro[sair].valorT);
                    }

                    printf("Deseja imprimir o RECIBO? S/N: ");
                    scanf("%s", &escolha[2]);
                    limpaBuffer();
                    if((escolha[2] == 's') || (escolha[2] == 'S'))
                    {
                        clrscr();
                        printf("\t*********************************************************"
                               "\n\t|                    TICKET Nº%03d\t\t\t|"
                               "\n\t*********************************************************"
                               "\n\t|                  CUPOM DE RETIRADA\t\t\t|"
                               "\n\t| ESTACIONAMENTO UNIP - UNIVERSIDADE PAULISTA - PIM-IV\t|"
                               "\n\t| VALOR HORA PADRÃO: R$%.2f.\t\t\t\t|"
                               "\n\t| VALOR FRAÇÃO DE MINUTO: R$%.2f.\t\t\t|"
                               "\n\t| CNPJ: 10.299.371/0002-50\t\t\t\t|"
                               "\n\t| RODOVIA JK (BR-459), KM 107\t\t\t\t|"
                               "\n\t| BAIRRO IPIRANGA - SÃO PAULO - SP\t\t\t|"
                               "\n\t| CEP: 37.550-00\t\t\t\t\t|"
                               "\n\t| PLACA: %s\t\t\t\t\t|"
                               "\n\t| ENTRADA: %02d/%02d/%4d AS %02d:%02d.\t\t\t\t|"
                               "\n\t| SAÍDA: %02d/%02d/%4d AS %02d:%02d.\t\t\t\t|"
                               "\n\t| PERMANÊNCIA: %d MINUTOS.\t\t\t\t|"
                               "\n\t|\t\t\t\t\t\t\t|"
                               "\n\t| VALOR PAGO: R$%.2f\t\t\t\t\t|"
                               "\n\t|\t\t\t\t\t\t\t|"
                               "\n\t*********************************************************\n\n",
                               carro[sair].regcar,
                               vlr_hora,
                               vlr_hora/60,
                               carro[sair].placa,
                               dataDia, dataMes, dataAno, carro[sair].h1, carro[sair].m1,
                               dataDia, dataMes, dataAno, carro[sair].h2, carro[sair].m2,
                               carro[sair].totalT,
                               carro[sair].valorT
                              );

                    }



                    /**< Condicional responsável por colocar a vaga em posição LIVRE. Se a
                    posição estiver setada como ocupada (1), coloque-a como vazia (0).*/
                    if(carro[sair].posicao == 1)
                    {

                        /**< Copia os dados da struct "Vaga" dentro do vetor "carro"
                        e os transfere para o struct "Vaga" dentro do vetor "listagem. */

                        listagem[regAux] = carro[sair];
                        carro[sair].posicao = 0;//Seta a vaga como vazia.
                        totalVagas++;// Controla a quantidade de vagas exibidas OCUPADAS.
                        regAux++;//Incrementa o auxiliar de registro a cada saída.
                        break;//Quebra o laço "for" finalizando a RETIRADA com sucesso.
                    }
                }
            }
            system("pause");
            break;
/**< -------------------------------------------------------------------------------------------- */
        case 4: //Exibe os valores para fechamento de caixa.
            clrscr();//Chama a função que limpa a tela.
            limpaBuffer();
            somaCaixa = 0;
            printf("------------------------ Fechamento de Caixa ---------------------\n\n");
            /**< Laço for() responsável por percorrer o vetor "listagem e retornar os
            valores para exibição do fechamento de caixa. */
            for(box=0; box<regAux; box++)
            {
                //Imprime os resultados na tela de acordo com o inteiro definido na variável "regAux".
                printf(" Placa: %s | Reg.Nº:%03d | Entrada: %02d:%02d | Saída: %02d:%02d |  R$%.2f\n",
                       listagem[box].placa,
                       listagem[box].regcar,
                       listagem[box].h1, listagem[box].m1,
                       listagem[box].h2, listagem[box].m2,
                       listagem[box].valorT);

                somaCaixa += listagem[box].valorT;
            }
            printf("\nSALDO DE ENTRADAS: R$%.2f.\n\n", somaCaixa);//Imprime o SALDO TOTAL.

            system("pause");
            break;
/**< -------------------------------------------------------------------------------------------- */
        case 5: //Configura valor de hora padrão.
            clrscr(); //Chama a função que limpa a tela.
            limpaBuffer();
            printf("--------------------------- Configuração Padrão ------------------------\n\n"
                   "Digite um novo valor para a hora de estadia em R$.\n\tR$");
            scanf("%f", &vlr_horaAux); //Entrada do valor base em Reais para a hora padrão.
            limpaBuffer();
            printf("O valor atual é de R$%.2f.\n", vlr_hora);
            printf("Confirmar alteração? S/N: ");
            scanf("%s", &escolha[2]);
            limpaBuffer();
            /**< Condicional que define se o valor da hora padrão será alterado ou não
            com base na escolha do usuário. */
            if((escolha[2] == 's') || (escolha[2] == 'S'))
            {
                vlr_hora = vlr_horaAux;
                printf("\nO novo valor é de R$%.2f.\n\nAlteração confirmada!\n\n", vlr_hora);
            }
            printf("Digite um valor em REAIS para a hora ADICIONAL.\n\tR$");
            scanf("%f", &vlr_horaAux); //Entrada do valor base em Reais para a hora padrão.
            limpaBuffer();
            printf("O valor atual para hora ADICIONAL é de R$%.2f.\n", horaadicional);
            printf("Confirmar alteração? S/N: ");
            scanf("%s", &escolha[2]);
            limpaBuffer();
            /**< Condicional que define se o valor da hora padrão será alterado ou não
            com base na escolha do usuário. */
            if((escolha[2] == 's') || (escolha[2] == 'S'))
            {
                horaadicional = vlr_horaAux;
                printf("\nO novo valor é de R$%.2f.\n\nAlteração confirmada!\n\n", horaadicional);
            }
            system("pause");
            break;
/**< -------------------------------------------------------------------------------------------- */
        case 6:
            clrscr(); //Chama a função que limpa a tela.
            printf("\nO programa foi finalizado.\n\n");

/**< -------------------------------------------------------------------------------------------- */

        }
    }
    while(opcao != 6);


    return 0;
}



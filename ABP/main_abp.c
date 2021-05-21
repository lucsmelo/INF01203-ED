#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "abp.h"
#include "arquivos.h"

#define LINHAS 10000
#define PARAM 4



int main(int argc, char *argv[])
{

    setlocale(LC_ALL,"");



    clock_t start_abp, end_abp, start_relatorio, end_relatorio;


	FILE *entrada,*arq_op, *arq_low, *resultado, *saida;


    No *abp, *abp_freq;


    int num_nodo, altura, fator_b;


    double miliseconds_abp, miliseconds_relatorio;


    abp = cria();

    abp_freq = cria();



    //início do programa
    if(argc!=PARAM) //testa se números de parâmetros para chamada do programa está correto, caso contrário exibe mensagem de erro, encerrando execução com código 1
    {
        printf("Número de argumentos incoerente.\n Para fazer a chamada corretamente digite algo como: \"compararvores <entrada>.txt operacoes.txt <saida>.txt\".\n");
        return 1;
    }
    else
    {
        entrada = fopen (argv[1], "r");
        if (!entrada)
        {
            printf("Erro ao abrir o arquivo %s.",argv[1]);
            return 1;
        }

        arq_low = fopen("arq_low.txt", "w");
        arq_op = fopen (argv[2], "r"); //abre argv[2] e em seguida testa se sua abertura foi bem sucedida, caso contrário, encerra execução com código 1
        if (!arq_op)
        {
            printf("Erro ao abrir o arquivo %s.",argv[2]);
            return 1;
        }
        saida = fopen(argv[3], "w");
        resultado = fopen("resultado.txt", "w");

        //abpação da ABP com as palavras do texto argv[1]
        start_abp = clock();                                             	 //inicia a contagem do arq_lowo
        converte_low(entrada, arq_low);                                      	 //converte argv[1] para caixa baixa e exporta o resultado para arq_low.txt
        arq_low = fopen("arq_low.txt", "r");                                   	 //abre arq_low.txt para leitura
        abp = le_para_abp(arq_low);                              	 //insere palavras do arq_low.txt na ABP
        end_abp = clock();                                                		//finaliza contagem do arq_lowo
        miliseconds_abp = (double)(end_abp - start_abp) / CLOCKS_PER_SEC;	 //calcula o arq_lowo decorrido

        //realização das operações contidas em argv[2]
        start_relatorio = clock();                                             	 //inicia a contagem do arq_lowo
        num_nodo = conta_abp(abp);                                          	 //calcula número de nodos da ABP
        altura = Altura(abp);                                        	 //calcula altura da ABP
        fator_b = fator_geral(abp);                                				//calcula fator_b da ABP
        le_arq_op(arq_op, resultado, abp_freq, abp, comparacoes_relat);              	 //interpreta e realiza as operações solicitadas
        resultado = fopen("resultado.txt", "r");                          //abre resultado.txt par leitura
        end_relatorio = clock();                                                //finaliza contagem do arq_lowo
        miliseconds_relatorio = (double)(end_relatorio - start_relatorio) / CLOCKS_PER_SEC; //calcula o arq_lowo decorrido

        //abpa relatorioatório
        relatorio_abp(saida, resultado, abp, num_nodo, altura, fator_b, miliseconds_abp, miliseconds_relatorio, comparacoes_abp, comparacoes_relat);
        return 0;
    }
}

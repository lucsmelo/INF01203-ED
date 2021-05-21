#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "abp.h"
#include "arquivos.h"

#define LINHAS 10000


/**
 *OBJETIVO:
 * Retorna arquivo com os caracteres em caixa baixa e sem pontuação, usando apenas espaços entre as palavras.
 *ENTRADAS:
 * *entrada: ponteiro para o arquivo que será lido;
 * *saida: ponteiro para o arquivo de saída;
 */
void converte_low(FILE *entrada, FILE *saida)
{

    char separador[]= {" .,&*%\?!;/'@-\"$#=><()][}{:\n\t"};


    char  linha[LINHAS],*palavra;

    while (fgets(linha,LINHAS,entrada)!=NULL)         //percorre todo o arquivo lendo linha a linha
    {
        palavra = strtok (linha, separador);
            while (palavra != NULL)
            {
                fprintf(saida,"%s\n", strlwr(palavra));
                palavra = strtok (NULL, separador);
            }
    }

    fclose (saida);


    fclose (entrada);

}

/**
 * LE_PARA_ABP (No)
 * Retorna ABP contendo as palavras do arquivo lido, computando o número de comparações necessária para tal.
 *
 * FILE *entrada: ponteiro para o arquivo que será lido;
 * COMP_GER: Número de comparaçãoes executadas.
 */
No* le_para_abp(FILE *entrada)
{
    No *abp;
    abp = cria();
    char *palavra, linha[LINHAS];

    while (fgets(linha,LINHAS,entrada)!=NULL) //percorre todo o arquivo lendo linha a linha
    {
        palavra = strtok(linha, "\n");
        while (palavra != NULL)
        {
            abp = insere_abp(abp, palavra);
            palavra = strtok (NULL, "\n");
        }
    }
    fclose(entrada);
    return abp;
}

/**
 *LE_OPERAÇOES (VOID)
 *  Interpreta as operações solicitadas no arquivo de texto de entrada e chama a função de acordo, imprimindo no arquivo de saída o resultado destas operações, computando o número de comparações necessária para tal.
 *ENTRADAS:
 * OP: ponteiro para o arquivo que será lido;
 * RESULTADO: ponteiro para o arquivo de saída com o resultado das operações;
 * ABP: ABP onde serão efetuadas as operações;
 * COMP_GER: Número de comparaçãoes executadas.
 */
void le_arq_op(FILE *entrada_op, FILE *resultado, No *abp_freq, No *abp, int aux)
{
    char *string_aux, *palavra, linhas[LINHAS];
    int freq_i, freq_f;
    aux=comparacoes_relat;

    while (fgets(linhas,LINHAS,entrada_op))
    {
        string_aux = strtok(linhas, " ");
        while (string_aux != NULL)
        {
            if(strcmp(string_aux, "F") == 0 || strcmp(string_aux, "f") == 0)
            {
                palavra = strtok(NULL, "\n");
                frequencia_abp_geral(resultado, abp, palavra, comparacoes_relat);
            }
            else
				if(strcmp(string_aux, "C") == 0 || strcmp(string_aux, "c") == 0)
            {
					freq_i = atoi(strtok(NULL, " "));
					freq_f = atoi(strtok(NULL, "\n"));
					contador_abp(abp_freq, abp, freq_i, freq_f);
					imprime_abp(resultado, abp_freq, freq_i, freq_f);
            }
            string_aux = strtok(NULL, " ");
        }
    }
    fclose(entrada_op);
    fclose(resultado);
}
/********************************************************************
 * OBJETIVO:                                                        *
 * Imprime relatório final concatenando as informações obtidas.     *
 * ENTRADAS:                                                        *
 * SAIDA: Arquivo de saída com o relatório final.                   *
 * RESULTADO: Arquivo com os resultados das operações               *
 * ABP: ABP cujos resultados serão exibidos.                        *
 * NODOS: Número de nodos da ABP.                                   *
 * ALTURA: Altura da ABP.                                           *
 * FB: Fator de Balanceamento da ABP.                               *
 * MILISECONDS_GER: tempo de execução da ABP.                       *
 * MILISECONDS_REL: Tempo de execução dos resultados.               *
 * COMP_GER: Número de comparaçãoes executadas na montagem da ABP.  *
 * COMP_REL: Número de comparaçãoes executadas no cômputo dos re-   *
 *          sultados.                                               *
 ********************************************************************/
void relatorio_abp(FILE *saida, FILE *resultado, No *abp, int num_nodo, int altura, int fator_b, double miliseconds_abp,int aux1, double miliseconds_relatorio,  int aux)
{
    char string_aux;

    fprintf(saida, "**********************  ESTATÍSTICAS REFERENTES A ABP **********************\n");
    fprintf(saida, "Número de Nodos: %i\n", num_nodo);
    fprintf(saida, "Altura: %i\n", altura);
    fprintf(saida, "Fator de Balanceamento: %i\n", fator_b);
    fprintf(saida, "Comparações: %i\n", aux1);
    fprintf(saida, "Tempo de execução: %f s\n", miliseconds_abp);



    while((string_aux = fgetc(resultado)) != EOF)
        fputc(string_aux, saida);





    fprintf(saida, "\n");
    fprintf(saida, "\n");
    fprintf(saida, "\n");
    fprintf(saida, "\n");





    fprintf(saida, "**********************  ESTATÍSTICAS REFERENTES AO RELATÓRIO **********************\n");
    fprintf(saida, "Tempo de execução: %f s\n ", miliseconds_relatorio);
    fprintf(saida, "Comparações: %i\n", aux);


    fclose(saida);
    fclose(resultado);
}

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
 * Retorna arquivo com os caracteres em caixa baixa e sem pontua��o, usando apenas espa�os entre as palavras.
 *ENTRADAS:
 * *entrada: ponteiro para o arquivo que ser� lido;
 * *saida: ponteiro para o arquivo de sa�da;
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
 * Retorna ABP contendo as palavras do arquivo lido, computando o n�mero de compara��es necess�ria para tal.
 *
 * FILE *entrada: ponteiro para o arquivo que ser� lido;
 * COMP_GER: N�mero de compara��oes executadas.
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
 *LE_OPERA�OES (VOID)
 *  Interpreta as opera��es solicitadas no arquivo de texto de entrada e chama a fun��o de acordo, imprimindo no arquivo de sa�da o resultado destas opera��es, computando o n�mero de compara��es necess�ria para tal.
 *ENTRADAS:
 * OP: ponteiro para o arquivo que ser� lido;
 * RESULTADO: ponteiro para o arquivo de sa�da com o resultado das opera��es;
 * ABP: ABP onde ser�o efetuadas as opera��es;
 * COMP_GER: N�mero de compara��oes executadas.
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
 * Imprime relat�rio final concatenando as informa��es obtidas.     *
 * ENTRADAS:                                                        *
 * SAIDA: Arquivo de sa�da com o relat�rio final.                   *
 * RESULTADO: Arquivo com os resultados das opera��es               *
 * ABP: ABP cujos resultados ser�o exibidos.                        *
 * NODOS: N�mero de nodos da ABP.                                   *
 * ALTURA: Altura da ABP.                                           *
 * FB: Fator de Balanceamento da ABP.                               *
 * MILISECONDS_GER: tempo de execu��o da ABP.                       *
 * MILISECONDS_REL: Tempo de execu��o dos resultados.               *
 * COMP_GER: N�mero de compara��oes executadas na montagem da ABP.  *
 * COMP_REL: N�mero de compara��oes executadas no c�mputo dos re-   *
 *          sultados.                                               *
 ********************************************************************/
void relatorio_abp(FILE *saida, FILE *resultado, No *abp, int num_nodo, int altura, int fator_b, double miliseconds_abp,int aux1, double miliseconds_relatorio,  int aux)
{
    char string_aux;

    fprintf(saida, "**********************  ESTAT�STICAS REFERENTES A ABP **********************\n");
    fprintf(saida, "N�mero de Nodos: %i\n", num_nodo);
    fprintf(saida, "Altura: %i\n", altura);
    fprintf(saida, "Fator de Balanceamento: %i\n", fator_b);
    fprintf(saida, "Compara��es: %i\n", aux1);
    fprintf(saida, "Tempo de execu��o: %f s\n", miliseconds_abp);



    while((string_aux = fgetc(resultado)) != EOF)
        fputc(string_aux, saida);





    fprintf(saida, "\n");
    fprintf(saida, "\n");
    fprintf(saida, "\n");
    fprintf(saida, "\n");





    fprintf(saida, "**********************  ESTAT�STICAS REFERENTES AO RELAT�RIO **********************\n");
    fprintf(saida, "Tempo de execu��o: %f s\n ", miliseconds_relatorio);
    fprintf(saida, "Compara��es: %i\n", aux);


    fclose(saida);
    fclose(resultado);
}

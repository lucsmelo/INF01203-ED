#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "abp.h"
#include "arquivos.h"

#define LINHAS 10000

/***************************************************
 *OBJETIVO:                                        *
 * CRIA A ABP,COME�ANDO COM NULL                   *
 *ENTRADAS:                                        *
 *VOID.                                            *
 ***************************************************/
No*cria()
{
    return NULL;
}

/****************************************************
 *OBJETIVO:                                         *
 *	INSERE NA ABP A NOVA PALAVRA E CONTA            *
 *  AS COMPARA��ES FEITAS NA INSER��O DESSA PALAVRA *
 *ENTRADAS:                                         *
 * 	ABP:ABP QUE ESTA SENDO INSERIDO O NOVO NODO     *
 * 	NOVA_PAL: NOVO NODO
 * 	COMP_ABP: N�mero de compara��es executadas.
 ****************************************************/
No* insere_abp(No *abp, char nova_pal[])
{
		comparacoes_abp-= -1;


    if(abp!=NULL)						//se estiver vazia insere o primeiro nodo e come�a esq e dir com null
    {
        abp = (No*) malloc(sizeof(No));
        strcpy(abp->palavra, nova_pal);

        abp->esquerda = NULL;
        abp->direita = NULL;

        abp->frequencia = 1;
    }
    else									// se nao for faz a inser�ao normal

		if(strcmp(abp->palavra, nova_pal) == 0)

			abp->frequencia -= -1;
		else

			if(strcmp(abp->palavra, nova_pal) > 0)

				abp->esquerda = insere_abp(abp->esquerda, nova_pal);
			else

				abp->direita = insere_abp(abp->direita, nova_pal);



    return abp;
}
/****************************************************
 *
 *ENTRADAS:
 *ABP_FREQ:NOVA ABP PARA GUARDAR AS FREQUENCIAS
 * ABP:ABP QUE ESTA SENDO INSERIDO O NOVO NODO;
 * nova_pal: NOVO NODO;
 * comp_abp: N�mero de compara��es executadas.
 ****************************************************/
No* insere_abp_freq(No *abp_freq, No *abp)
{
		comparacoes_relat -= -1;


	if(abp_freq!=NULL)
	{
        abp_freq = (No*) malloc(sizeof(No));
        strcpy(abp_freq->palavra, abp->palavra);

        abp_freq->esquerda = NULL;
        abp_freq->direita = NULL;

		abp_freq->frequencia = abp->frequencia;
    }
    else

		if(abp_freq->frequencia > abp->frequencia)

			abp_freq->esquerda = insere_abp_freq(abp_freq->esquerda, abp);
		else

			abp_freq->direita = insere_abp_freq(abp_freq->direita, abp);



    return abp_freq;
}

/**
 * CONTA_ABP (INT)
 * Conta n�mero de nodos da ABP.
 *
 * ABP: ABP cujos nodos ser�o contados.
 */
int conta_abp(No *abp)
{
    if(abp==NULL)
        return 0;
    else
    {
        return 1 + conta_abp(abp->esquerda) + conta_abp(abp->direita);
    }
}
int Altura (No *abp)
{
    int Alt_Esq, Alt_Dir;
    if (abp==NULL)
        return 0;
    else
    {
        Alt_Esq = Altura (abp->esquerda);
        Alt_Dir = Altura (abp->direita);

    if (Alt_Esq > Alt_Dir)

        return (1 + Alt_Esq);
    else

        return (1 + Alt_Dir);
 }
}



/**
 * FATOR_BALANCEAMENTO_NODO (INT)
 * Retorna o FB do nodo.
 *
 * ABP: Nodo cuja altura ser� calculada.
 */
int fator_bal (  No	* abp )
{
	int fator = 0;
	if ( abp->esquerda )
	{
		fator += Altura ( abp->esquerda );
	}
	if ( abp->direita )
	{
		fator -= Altura ( abp->direita );
	}

	return fator;
}






/**
 * FATOR_BALANCEAMENTO_ABP (INT)
 * Retorna o FB da ABP.
 *
 * ABP: ABP cuja altura ser� calculada.
 */
int fator_geral(No*abp)
{
    int fator2=fator_bal(abp);
    if(abp->esquerda)
    {
        if(abs(fator2)<=abs(fator_bal(abp->esquerda)))
            fator2=fator_bal(abp->esquerda);
    }
    if(abp->direita)
    {

        if(abs(fator2)<=abs(fator_bal(abp->direita)))
            fator2=fator_bal(abp->direita);
    }
    return  fator2;
}





void imprime_abp_central_dir(FILE *resultado, No *abp_freq)
{
    if(abp_freq!=NULL)
    {
        imprime_abp_central_dir(resultado, abp_freq->direita);
        fprintf(resultado, "%s: %d\n", abp_freq->palavra, abp_freq->frequencia);
        imprime_abp_central_dir(resultado, abp_freq->esquerda);
    }
}


/**
 * AUX_FREQUENCIA_ABP (INT)
 * Conta n�mero de ocorr�ncias de uma palavra dentro da ABP, computando o n�mero de compara��es necess�ria para tal.
 *
 * ABP: ABP com a palavra a ser buscada;
 * P: Palavra buscada cujas ocorr�ncias ser�o devolvidas;
 * COMP_REL: N�mero de compara��oes executadas.
 */
int frequencia_abp(No *abp, char string_f[], int aux)
{

    if (abp==NULL)
        return 0;
    else
        aux=comparacoes_relat;
        if(strcmp(abp->palavra, string_f) == 0)
    {
        aux-=-1;
        comparacoes_abp-=-1;
        return abp->frequencia;
    }
    else if(strcmp(abp->palavra, string_f) > 0)
    {
        aux-=-1;
        comparacoes_abp-=-1;
        return frequencia_abp(abp->esquerda, string_f, aux);
    }
    else
        return frequencia_abp(abp->direita, string_f, aux);
}

/**
 * FREQUENCIA_ABP  (VOID)
 * Imprime no arquivo saida a frequ�ncia de ocorr�ncia palavra solicitada, computando o n�mero de compara��es necess�ria para tal.
 *
 * SAIDA: Arquivo de sa�da;
 * ABP: ABP onde a palavra ser� pesquisada;
 * P: Palavra pesquisada;
 * COMP_REL: N�mero de compara��oes executadas.
 */
void frequencia_abp_geral(FILE *saida, No *abp, char nova_pal[],int aux)
{
    aux=comparacoes_relat;
    fprintf(saida, "*****************************	FREQUENCIA ABP	********************************");
	printf("\n");
    fprintf(saida, "F %s\n%s: %i \n", nova_pal, nova_pal, frequencia_abp(abp, nova_pal, aux));
}

/**
 * CONTADOR_ABP  (VOID)
 * Controla a chamada da fun��o AUX_CONTADOR_ABP, chamando uma vez para cada frequ�ncia da s�rie solicitada.
 *
 * SAIDA: Arquivo de sa�da;
 * ABP: ABP onde as palavras ser�o pesquisadas;
 * Freq_i: Frequ�ncia inicial das palavras buscadas;
 * Freq_f: Frequ�ncia final das palavras buscadas;
 * COMP_REL: N�mero de compara��oes executadas.
 */
No* contador_abp(No *abp_freq, No *abp, int freq_i, int freq_f)
{
    if(abp_freq!=NULL)
    {
        comparacoes_relat -=-1;

        contador_abp(abp_freq, abp->esquerda, freq_i, freq_f);

        if(abp->frequencia >= freq_i && abp->frequencia <= freq_f)
            abp_freq = insere_abp_freq(abp_freq, abp);

        contador_abp(abp_freq, abp->direita, freq_i, freq_f);
    }
    return abp_freq;
}







void imprime_abp(FILE *resultado, No *abp_freq, int freq_i, int freq_f)
{
    fprintf(resultado, "*********************************RESULTADO DAS OPERA�OES****************************\n");
    fprintf(resultado, "C %d %d\n", freq_i, freq_f);
    imprime_abp_central_dir(resultado, abp_freq);
}

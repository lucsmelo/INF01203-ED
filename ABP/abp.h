#include <stdio.h>
#include<stdlib.h>
struct TNodoA{
 char palavra[47];//maior palavra tem 46
 struct TNodoA *esquerda;
 struct TNodoA *direita;
 int frequencia;
};
typedef struct TNodoA No;
int comparacoes_abp;
int comparacoes_relat;

No* cria();
int testa_abp(No *abp);
No* insere_abp(No *abp, char p[]);
No* insere_abp_freq(No *print, No *abp);


int conta_abp(No *abp);


int frequencia_abp(No *abp, char string_f[], int aux);
void frequencia_abp_geral(FILE *saida, No *abp, char nova_pal[],int aux);
No* contador_abp(No *abp_freq, No *abp, int freq_i, int freq_f);



int Altura(No *abp);


int fator_bal (  No	* abp );
int fator_geral(No*abp);
void imprime_abp_central_dir(FILE *resultado, No *abp_freq);
void imprime_abp(FILE *resultado, No *abp_freq, int freq_i, int freq_f);

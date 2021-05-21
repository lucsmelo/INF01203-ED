#define LINHAS 10000




void converte_low(FILE *entrada, FILE *saida);

No* le_para_abp(FILE *entrada);

void le_arq_op(FILE *entrada_op, FILE *resultado, No *abp_freq, No *abp, int aux);

void relatorio_abp(FILE *saida, FILE *resultado, No *abp, int num_nodo, int altura, int fator_b, double miliseconds_abp,int comp_abp, double miliseconds_relatorio,  int comp_relatorio);

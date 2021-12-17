#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{

    int m, n;

    scanf("%d", &m);
    scanf("%d", &n);

    struct localisadores {
	int linha;
	int coluna;
	int valor;
    };

    struct localisadores info[m + n];

    //limpando vetor de structs
    for (int i = 0; i < (m + n); i++) {
	    info[i].linha = 0;
	    info[i].coluna = 0;
	    info[i].valor = 0;
    }

    //numero k de componentes iniciais e inicializando matriz de comandos iniciais
    int init;
    scanf("%d", &init);
    char comando[init][6];

    //colocando valores no vetor de structs
    for (int i = 0; i < init; i++) {
	    scanf("%s", comando[i]);
	    sscanf(comando[i], "[%d,%d]", &info[i].linha, &info[i].coluna);
	    scanf("%d", &info[i].valor);
    }

    //variaveis para ordenaÃ§Ã£o inicial do vetor de structs
    int aux_linha;
    int aux_coluna;
    int aux_valor;

    //ordenaÃ§Ã£o do vetor de structs inicial
    for (int i = 0; i < init; i++) {

	    for (int j = i + 1; j < init; j++) {

	        if (info[i].linha > info[j].linha) {
		        aux_linha = info[i].linha;
		        aux_coluna = info[i].coluna;
		        aux_valor = info[i].valor;

		        info[i].linha = info[j].linha;
		        info[i].coluna = info[j].coluna;
		        info[i].valor = info[j].valor;

		        info[j].linha = aux_linha;
		        info[j].coluna = aux_coluna;
		        info[j].valor = aux_valor;
	    }
	                if (info[i].linha == info[j].linha) {
		                if (info[i].coluna > info[j].coluna) {
		                    aux_linha = info[i].linha;
		                    aux_coluna = info[i].coluna;
		                    aux_valor = info[i].valor;

		                    info[i].linha = info[j].linha;
		                    info[i].coluna = info[j].coluna;
		                    info[i].valor = info[j].valor;

		                    info[j].linha = aux_linha;
		                    info[j].coluna = aux_coluna;
		                    info[j].valor = aux_valor;
		}

	    }

	}
    }

    //variavel que vai manipular funcionamento do laÃ§o principal
    char condit;

    //variaveis para o bloco 'r'
    char rec_comando[6];
    int rec_linha = 0;
    int rec_coluna = 0;


    //variaveis para o bloco 'a'
    char comando_loop[6];
    int cont = 0;
    int lin_loop = 0;
    int col_loop = 0;
    int val_loop = 0;

    //inicio do laÃ§o principal
    while (scanf("%c", &condit) != 't') {

	//variaveis auxiliares dos comandos de recuperaÃ§Ã£o, identificaÃ§Ã£o de lotamento do vetor, e identificaÃ§Ã£o de existencia de numero igual ou nÃ£o dentro do prÃ³prio vetor
	int rec_aux = 0;
	int cheio = 0;
	int adc = 0;

	//encerra o programa
	if (condit == 't') {
	    return 0;
	}
	//recuperando o valor de um elemento
	if (condit == 'r') {

	    scanf("%s", rec_comando);
	    sscanf(rec_comando, "[%d,%d]", &rec_linha, &rec_coluna);

	    for (int i = 0; i < (init + cont); i++) {
		    if (info[i].linha == rec_linha && info[i].coluna == rec_coluna) {
		        printf("M[%d][%d] == %d\n", rec_linha, rec_coluna,
			        info[i].valor);
		            rec_aux = 1;
		}
	    }

	    if (rec_aux == 0) {
		    printf("M[%d][%d] == 0\n", rec_linha, rec_coluna);
	    }
	}
	//mudar ou adicionar um elemento
	if (condit == 'a') {

	    //entrada de valores recebida
	    scanf("%s", comando_loop);
	    scanf("%d", &val_loop);
	    sscanf(comando_loop, "[%d,%d]", &lin_loop, &col_loop);

	    //encontrando se tem alguem na msm posiÃ§Ã£o
	    //se tiver, e o valor inserido nÃ£o for zero, entÃ£o trocar os valores
	    for (int i = 0; i < (init + cont); i++) {
		        if ((info[i].linha == lin_loop) && (info[i].coluna == col_loop)) {
		            if (val_loop != 0) {
			            info[i].valor = val_loop;
		    }
		}
	    }

	    //x Ã© zero, entao devemos deletar o elemento
	    //para deletar, vamos sobrepor o elemento pelos outros elementos dentro do vetor, na intenÃ§Ã£o de jogar o elemento deletado para a ultima posiÃ§Ã£o do vetor.
	    //Jogando o elemento pra ultimo, nÃ³s zeramos as informaÃ§Ãµes dele, e fazemos um decrescimo no valor de cont (elementos adicionais do vetor)
	    //Assim o vetor nÃ£o vai contar mais o elemento e dessa forma, teremos o deletado.
	    for (int i = 0; i < (init + cont); i++) {
		    if ((info[i].linha == lin_loop) && (info[i].coluna == col_loop) && (val_loop == 0)) {
		        for (int j = i; j < (init + cont - 1); j++) {

			    info[j].linha = info[j + 1].linha;
			    info[j].coluna = info[j + 1].coluna;
			    info[j].valor = info[j + 1].valor;
		        }

		        info[init + cont - 1].linha = 0;
		        info[init + cont - 1].coluna = 0;
		        info[init + cont - 1].valor = 0;
		        cont--;
		}
	    }

	    for (int i = 0; i < (init + cont); i++) {
		    if ((info[i].linha == lin_loop) && (info[i].coluna == col_loop)) {
		        adc = 1;
		}
	    }

	    if ((init + cont) == (m + n)) {
		    cheio = 1;
	    }
	    //avisando q vetor ta chei
	    if ((adc != 1) && (val_loop != 0) && (cheio == 1)) {
		    printf("O vetor de coordenadas esta' cheio.\n");
	    }

	    else {

		//adicionando novo componente na struct
		if ((adc != 1) && (val_loop != 0) && ((init + cont) < (m + n))) {
		    info[init + cont].linha = lin_loop;
		    info[init + cont].coluna = col_loop;
		    info[init + cont].valor = val_loop;

		    cont++;
		}
	    }

	}
	//imprimindo
	if (condit == 'p') {

	    //ordenando o vetor de structs
	    int aux_linha;
	    int aux_coluna;
	    int aux_valor;

	    //algoritmo para ordenaÃ§Ã£o do vetor
	    for (int i = 0; i < (init + cont); i++) {

		for (int j = i + 1; j < (init + cont); j++) {

		    if (info[i].linha > info[j].linha) {
			    aux_linha = info[i].linha;
			    aux_coluna = info[i].coluna;
			    aux_valor = info[i].valor;

			    info[i].linha = info[j].linha;
			    info[i].coluna = info[j].coluna;
			    info[i].valor = info[j].valor;

			    info[j].linha = aux_linha;
			    info[j].coluna = aux_coluna;
			    info[j].valor = aux_valor;
		    }

		    if (info[i].linha == info[j].linha) {
			    if (info[i].coluna > info[j].coluna) {
			        aux_linha = info[i].linha;
			        aux_coluna = info[i].coluna;
			        aux_valor = info[i].valor;

			        info[i].linha = info[j].linha;
			        info[i].coluna = info[j].coluna;
			        info[i].valor = info[j].valor;

			        info[j].linha = aux_linha;
			        info[j].coluna = aux_coluna;
			        info[j].valor = aux_valor;
			}

		    }

		}
	    }

	    printf("VC: ");
	        for (int i = 0; i < (init + cont); i++) {
		        if (info[i].valor != 0) {
		            printf("(%d,%d,%d) ", info[i].linha, info[i].coluna, info[i].valor);
		}
	    }
	    printf("\n");
	}

    }
}
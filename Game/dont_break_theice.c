/**      @file: 180023098.c
 *     @author: Luiz Felipe Almeida Silva
 * @disciplina: Algoritmos e Programação de Computadores
 *
 * Implementação do jogo "Don't Break The Ice", para 2 jogadores. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int TRUE = 1, FALSE = 0;
const int PNMAX = 25, PNBUFFER = 100, PNVETORTAM = 24;
const int CICETAM = 7, MAPAX = 39, MAPAY = 19;

const char TERRABORDA = '|', TERRACIMA = '=', BGELO = '#', BGELOQ = '-', ICEBERG = '8';

void pularlinhas(int n){
    int i = 0;
	
    while(i != n){
        printf("\n");
        i++;
    }
}

void confplayers(char nome1[PNVETORTAM], char nome2[PNVETORTAM]){
	int p1ntam = 0, p1tamval = FALSE, p2ntam = 0, p2tamval = FALSE;
	int sleep(int);

	system("clear");
	printf("Bem-vindos, jogadores, à civilização de Aang! Escolham seus nomes de guerra!\n");
    printf("Jogador 1, escolha seu nome de guerra!\n");
	
	while(p1tamval == FALSE){
		fgets(nome1, PNBUFFER, stdin);
		
		/* O algoritmo abaixo serve para retirar o \n da string, causado pelo uso do fgets. Fonte: 
		https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input/2693827#2693827 */
		
		p1ntam = strlen(nome1) - 1; /* Pega o tamanho da string e volta 1 posição */
		
		if(nome1[p1ntam] == '\n'){ /* Coloca o caractere para fim de string no lugar da quebra de linha, eliminando-a. */
			nome1[p1ntam] = '\0';
		}
		
		/* Fim do Algoritmo. O mesmo Algoritmo está presente também para o Player 2.*/

        if(p1ntam > 0) {
            if (p1ntam <= PNMAX) {
                p1tamval = TRUE;
            } else {
                printf("Nome muito grande! Por favor, escolha um nome de guerra menor!\n");
            }
        }else{
            printf("Você precisa escolher um nome!\n");
        }
	}
	
	printf("\nNome de guerra do jogador 1: %s\n", nome1);
	printf("Jogador 2, escolha seu nome de guerra!\n");
	
	while(p2tamval == FALSE){
		fgets(nome2, PNBUFFER, stdin);
		
		p2ntam = strlen(nome2) - 1;
		
		if(nome2[p2ntam] == '\n'){
			nome2[p2ntam] = '\0';
		}

		if(p2ntam > 0) {
            if (p2ntam <= PNMAX) {
                p2tamval = TRUE;
            } else {
                printf("Nome muito grande! Por favor, escolha um nome de guerra menor!\n");
            }
        }else{
            printf("Você precisa escolher um nome!\n");
		}
	}
	
	printf("\nNomes de guerra escolhidos!\n\n");
	printf("Nome de guerra do Jogador 1: %s\n", nome1);
	printf("Nome de guerra do Jogador 2: %s\n", nome2);
	
	sleep(3);
}

void gerariceberg(int cice[CICETAM]){
	int x = 0, y = 0;
	
	/* Gera coordenadas X e Y aleatórias, porém, limitadas entre em 35 e 5 e 15 e 5, para que o bloco não apareça fora dos limites do mapa, ou muito colado. */
	x = 5 + rand() % 35;
	y = 5 + rand() % 15;

	/* Inferior Esquerdo */
	cice[0] = x;
	cice[1] = y;
    /* Superior Esquerdo */
	cice[2] = x;
	cice[3] = y+1;
    /* Inferior Direito */
	cice[4] = x+1;
	cice[5] = y;
    /* Superior Direito */
	cice[6] = x+1;
	cice[7] = y+1;
}

int checarcaminhos(char coord[MAPAX][MAPAY], int iceberg[CICETAM]){
    int semcaminhos = FALSE, c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0, c7 = 0, c8 = 0, c9 = 0, c10 = 0, c11 = 0, c12 = 0;
    int caminho1 = FALSE, caminho2 = FALSE, caminho3 = FALSE, caminho4= FALSE, caminho5 = FALSE, caminho6 = FALSE;
    int caminho7 = FALSE, caminho8 = FALSE, caminho9 = TRUE, caminho10 = TRUE, caminho11 = TRUE, caminho12 = TRUE;
    int ice0, ice1, ice2, ice3, ice4, ice5, ice6, ice7;
    int bordaesq = 0, bordadir = 39, bordainf = 0, bordasup = 19;
    int linha1, linha2, linha3, linha4;
    int sleep(int);

    ice0 = iceberg[0];
    ice1 = iceberg[1];
    ice2 = iceberg[2];
    ice3 = iceberg[3];
    ice4 = iceberg[4];
    ice5 = iceberg[5];
    ice6 = iceberg[6];
    ice7 = iceberg[7];

    c1 = (ice0-1);
    c2 = (ice2-1);
    c3 = (ice4+1);
    c4 = (ice6+1);
    c5 = (ice3+1);
    c6 = (ice7+1);
    c7 = (ice1-1);
    c8 = (ice5-1);

    linha1 = ice7;
    c9 = ice6+1;
    linha2 = ice3;
    c10 = ice2-1;
    linha3 = ice5;
    c11 = ice4+1;
    linha4 = ice1;
    c12 = ice0-1;

    while(c1 != bordaesq){ 
        if (coord[c1][ice1] != BGELO) {
            caminho1 = FALSE;
            break;
        }else{
            caminho1 = TRUE;
        }

        c1--;
    }

    while(c2 != bordaesq){ 
        if (coord[c2][ice3] != BGELO) {
            caminho2 = FALSE;
            break;
        }else{
            caminho2 = TRUE;
        }

        c2--;
    }

    while(c3 != bordadir){  
        if(coord[c3][ice5] != BGELO){
            caminho3 = FALSE;
            break;
        }else{
            caminho3 = TRUE;
        }

        c3++;
    }

    while(c4 != bordadir){ 
        if(coord[c4][ice7] != BGELO){
            caminho4 = FALSE;
            break;
        }else{
            caminho4 = TRUE;
        }

        c4++;
    }

    while(c5 != bordasup){ 
        if(coord[ice2][c5] != BGELO){
            caminho5 = FALSE;
            break;
        }else{
            caminho5 = TRUE;
        }

        c5++;
    }

    while(c6 != bordasup){ 
        if(coord[ice6][c6] != BGELO){
            caminho6 = FALSE;
            break;
        }else{
            caminho6 = TRUE;
        }

        c6++;
    }

    while(c7 != bordainf){ 
        if(coord[ice0][c7] != BGELO){
            caminho7 = FALSE;
            break;
        }else{
            caminho7 = TRUE;
        }

        c7--;
    }

    while(c8 != bordainf){  
        if(coord[ice4][c8] != BGELO) {
            caminho8 = FALSE;
            break;
        }else{
            caminho8 = TRUE;
        }

        c8--;
    }

    while(linha1 < bordasup){
        while(c9 < bordadir){
            if(coord[c9][linha1] == BGELOQ){
                caminho9 = FALSE;
                break;
            }

            ++c9;
            ++c9;
        }

        if(caminho9 == FALSE){
            break;
        }

        linha1++;
    }

    while(linha2 < bordasup){
        while(c10 > bordaesq){
            if(coord[c10][linha2] == BGELOQ){
                caminho10 = FALSE;
                break;
            }

            c10--;
            c10--;
        }

        if(caminho10 == FALSE){
            break;
        }

        linha2++;
    }

    while(linha3 > bordainf){
        while(c11 < bordadir){
            if(coord[c11][linha3] == BGELOQ){
                caminho11 = FALSE;
                break;
            }

            ++c11;
            ++c11;
        }

        if(caminho11 == FALSE){
            break;
        }

        linha3--;
    }

    while(linha4 > bordainf){
        while(c12 > bordaesq){
            if(coord[c12][linha4] == BGELOQ){
                caminho12 = FALSE;
                break;
            }

            c12--;
            c12--;
        }

        if(caminho12 == FALSE){
            break;
        }

        linha4--;
    }

    if((caminho1 == FALSE) && (caminho2 == FALSE) && (caminho3 == FALSE) && (caminho4 == FALSE) && (caminho5 == FALSE) && (caminho6 == FALSE) && (caminho7 == FALSE) && (caminho8 == FALSE) && (caminho9 == FALSE) && (caminho10 == FALSE) && (caminho11 == FALSE) && (caminho12 == FALSE)){
        semcaminhos = TRUE;
    }

    return semcaminhos;
}

void gerarmapa(char coord[MAPAX][MAPAY], int ice[CICETAM]){
	int icepos1, icepos2, icepos3, icepos4, icepos5, icepos6, icepos7, icepos8;
	int besq = 0, bdir = 0, bsup = 0, binf = 0, gelo = 0, lingelo = 1, limgelox = (MAPAX-1), limgeloy = (MAPAY-1), limbsupinf = (MAPAY-1);
	
	icepos1 = ice[0];
	icepos2 = ice[1];
	icepos3 = ice[2];
	icepos4 = ice[3];
	icepos5 = ice[4];
	icepos6 = ice[5];
	icepos7 = ice[6];
	icepos8 = ice[7];
	
	for(bsup = 0; bsup <= MAPAX; ++bsup){
		coord[bsup][MAPAY] = TERRACIMA;
	}
	
	for(binf = 0; binf <= MAPAX; ++binf){
		coord[binf][0] = TERRACIMA;
	}
	
	for(besq = 1; besq <= limbsupinf; ++besq){
		coord[0][besq] = TERRABORDA;
	}
	
	for(bdir = 1; bdir <= limbsupinf; ++bdir){
		coord[MAPAX][bdir] = TERRABORDA;
	}
	
	for(lingelo = 1; lingelo <= limgeloy; ++lingelo){
		for(gelo = 1; gelo <= limgelox; ++gelo){
			coord[gelo][lingelo] = BGELO;
		}
	}
	
	coord[icepos1][icepos2] = ICEBERG;
	coord[icepos3][icepos4] = ICEBERG;
	coord[icepos5][icepos6] = ICEBERG;
	coord[icepos7][icepos8] = ICEBERG;
}

void interface(char coord[MAPAX][MAPAY],char p1n[PNVETORTAM], char p2n[PNVETORTAM], int pts1, int pts2){
	int x = 0, y = MAPAY, parar = FALSE;

	system("clear");
	while(parar == FALSE) {
        for (x = 0; x <= MAPAX; ++x) {
            printf("%c", coord[x][y]);
        }

        printf(" %d", y);

        pularlinhas(1);

        --y;

        if (y < 0) {
            parar = TRUE;
        }
    }

    printf("0123456789012345678901234567890123456789\n");
	printf("0         1         2         3\n");

    pularlinhas(1);

    printf("%s: %d pontos\n", p1n, pts1);
    printf("%s: %d pontos\n", p2n, pts2);

    pularlinhas(1);
}

int probabilidade(){
	int n = 0;
	
	/* O pequeno Algoritmo abaixo serve para trabalha com as probabilidades, ele continua na função "jogo", Fonte:
	https://stackoverflow.com/questions/15843877/how-do-i-roll-for-a-25-chance-to-get-yes-or-no */
	
	/* Escolhe um número aleatório entre 1 e 4, como são 4 números, cada um deles tem 25% (1/4, ou 1 em 4) de chance de ser escolhido. */
	n = 1 + rand() % 4;
	return n;
}

int probabilidade2(){
    int n = 0;

    /* Nesse caso, a probabilidade é tratada de forma diferente, sendo menor que 75, a ação é executada. */
    n = rand() % 75;

    return n;
}

void escolherposicao(char coord[MAPAX][MAPAY], int posaleatoria, int x, int y) {
    int posvalida = FALSE;

    while(posvalida == FALSE) {
        if (posaleatoria == 1) {
            if (coord[(x)][(y + 1)] == TERRABORDA || coord[(x)][(y + 1)] == TERRACIMA ||
                coord[(x)][(y + 1)] == ICEBERG) {
                posaleatoria = 2;
                posvalida = FALSE;
            } else {
                coord[(x)][(y + 1)] = BGELOQ; /* Superior */
                posvalida = TRUE;
            }
        } else if (posaleatoria == 2) {
            if (coord[(x)][y - 1] == TERRABORDA || coord[(x)][y - 1] == TERRACIMA || coord[(x)][y - 1] == ICEBERG) {
                posaleatoria = 3;
                posvalida = FALSE;
            } else {
                coord[(x)][y - 1] = BGELOQ; /* Inferior */
                posvalida = TRUE;
            }
        } else if (posaleatoria == 3) {
            if (coord[(x - 1)][y] == TERRABORDA || coord[(x - 1)][y] == TERRACIMA ||
                coord[(x - 1)][y] == ICEBERG) {
                posaleatoria = 4;
                posvalida = FALSE;
            } else {
                coord[(x - 1)][y] = BGELOQ; /* Esquerdo */
                posvalida = TRUE;
            }
        } else if (posaleatoria == 4) {
            if (coord[(x + 1)][y] == TERRABORDA || coord[(x + 1)][y] == TERRACIMA || coord[(x + 1)][y] == ICEBERG) {
                posaleatoria = 1;
                posvalida = FALSE;
            } else {
                coord[(x + 1)][y] = BGELOQ; /* Direito */
                posvalida = TRUE;
            }
        }
    }
    coord[x][y] = BGELOQ;
}

void quebraroutrobloco(char p1[PNVETORTAM], char p2[PNVETORTAM], int player, int iceberg[CICETAM], char coord[MAPAX][MAPAY], int *ptr_pts){
    int x, y, posxcorreta = FALSE, posycorreta = FALSE, icenaoatingido = FALSE, bloconaoquebrado = FALSE;
    int ice1, ice2, ice3, ice4, ice5, ice6, ice7, ice8;
    int quebrou2blocos = 0, posaleatoria = 0;

    char x2[10], y2[10];

    ice1 = iceberg[0];
    ice2 = iceberg[1];
    ice3 = iceberg[2];
    ice4 = iceberg[3];
    ice5 = iceberg[4];
    ice6 = iceberg[5];
    ice7 = iceberg[6];
    ice8 = iceberg[7];

    printf("\nCuidado! Ao quebrar 2 blocos, as chances de quebrar um adjacente é de 75 por cento!\n");
    printf("Digite as coordenadas do bloco 2!\n");

    while ((icenaoatingido == FALSE) && (bloconaoquebrado == FALSE)) {
        printf("Coordenada X: ");

        while (posxcorreta == FALSE) {
            scanf("%s", x2);

            x = atoi(x2);

            if (x > 38 || x < 1) {
                printf("Esta posição é uma borda ou está fora do lago! Escolha outra posição para X!\n");
            } else {
                posxcorreta = TRUE;
            }
        }

        printf("Coordenada Y: ");

        while (posycorreta == FALSE) {
            scanf("%s", y2);

            y = atoi(y2);

            if (y > 18 || y < 1) {
                printf("Esta posição é uma borda ou está fora do lago! Escolha outra posição para Y!\n");
            } else {
                posycorreta = TRUE;
            }
        }

        if ((x == ice1 && y == ice2) || (x == ice3 && y == ice4) || (x == ice5 && y == ice6) ||
            (x == ice7 && y == ice8)) {
            printf("Esta posição é o Iceberg! Não pode ser quebrado, escolha outra posição!\n");
            posxcorreta = FALSE;
            posycorreta = FALSE;
        } else {
            icenaoatingido = TRUE;
        }

        if(icenaoatingido == TRUE) {
            if (coord[x][y] == BGELOQ) {
                printf("Este bloco já está quebrado! Escolha uma posição de um bloco intacto!\n");
                icenaoatingido = FALSE;
                bloconaoquebrado = FALSE;
                posxcorreta = FALSE;
                posycorreta = FALSE;
            } else {
                bloconaoquebrado = TRUE;
            }
        }
    }

    quebrou2blocos = probabilidade2();

    pularlinhas(1);
    printf("%s quebra o bloco na posição %d, %d!\n", player == 1 ? p1 : p2, x, y);

    if (quebrou2blocos < 75) {
        posaleatoria = probabilidade();

        pularlinhas(1);
        printf("Oops! O rio é perigoso!, %s quebrou um bloco adjacente!\n", player == 1 ? p1 : p2);

        escolherposicao(coord, posaleatoria, x, y);
    } else {
        coord[x][y] = BGELOQ;
    }

    *(ptr_pts) += 1;
}

void finalizarjogo(char p[PNVETORTAM], char coord[MAPAX][MAPAY], int ptsfinais){
    int x = 1, y = 1;
    int bordadir = 38, bordasup = 18;

   while(y <= bordasup){

       for(x = 1; x <= bordadir; ++x) {
           if (coord[x][y] == BGELO) {
               ptsfinais += 1;
           }
       }

       y++;
   }

   pularlinhas(1);
   printf("%s venceu o jogo! Parabéns! Pontuação: %d\n\n", p, ptsfinais);
}

void quebrarblocopara(char p1[PNVETORTAM], char p2[PNVETORTAM], int player, int iceberg[CICETAM], char coord[MAPAX][MAPAY], int *ptr_pts, int *ptr_fimdojogo, int *(ptr_pts2)){
    int escval = FALSE, escbloco = 0;
    int x, y, posxcorreta = FALSE, posycorreta = FALSE, icenaoatingido = FALSE, bloconaoquebrado = FALSE;
    int ice1, ice2, ice3, ice4, ice5, ice6, ice7, ice8;
	int quebrou2blocos = 0, posaleatoria = 0;

	char escbloco2[10], x2[10], y2[10];

	ice1 = iceberg[0];
    ice2 = iceberg[1];
    ice3 = iceberg[2];
    ice4 = iceberg[3];
    ice5 = iceberg[4];
    ice6 = iceberg[5];
    ice7 = iceberg[6];
    ice8 = iceberg[7];
	
	if(*(ptr_fimdojogo) != TRUE) {
        printf("%s deseja quebrar quantos blocos: ", player == 1 ? p1 : p2);

        while (escval == FALSE) {
            scanf("%s", escbloco2);

            escbloco = atoi(escbloco2);

            if (escbloco <= 0 || escbloco > 2) {
                if (escbloco <= 0) {
                    printf("Você precisa quebrar pelo menos um bloco!\n");
                }

                if (escbloco > 2) {
                    printf("Você só pode quebrar, no máximo, 2 blocos de gelo por vez!\n");
                }
            } else if (escbloco > 0 && escbloco <= 2) {
                escval = TRUE;
            }
        }

        pularlinhas(1);

        printf("Digite as coordenadas do bloco!\n");

        while ((icenaoatingido == FALSE) && (bloconaoquebrado == FALSE)) {
            printf("Coordenada X: ");

            while (posxcorreta == FALSE) {
                scanf("%s", x2);

                x = atoi(x2);

                if (x > 38 || x < 1) {
                    printf("Esta posição é uma borda ou não existe! Escolha outra posição para X!\n");
                } else {
                    posxcorreta = TRUE;
                }
            }

            printf("Coordenada Y: ");

            while (posycorreta == FALSE) {
                scanf("%s", y2);

                y = atoi(y2);

                if (y > 18 || y < 1) {
                    printf("Esta posição é uma borda ou não existe! Escolha outra posição para Y!\n");
                } else {
                    posycorreta = TRUE;
                }
            }

            if ((x == ice1 && y == ice2) || (x == ice3 && y == ice4) || (x == ice5 && y == ice6) ||
                (x == ice7 && y == ice8)) {
                printf("Esta posição é o Iceberg! Não pode ser quebrado, escolha outra posição!\n");
                posxcorreta = FALSE;
                posycorreta = FALSE;
            } else {
                icenaoatingido = TRUE;
            }

            if(icenaoatingido == TRUE) {
                if (coord[x][y] == BGELOQ) {
                    printf("Este bloco já está quebrado! Escolha uma posição de um bloco intacto!\n");
                    icenaoatingido = FALSE;
                    bloconaoquebrado = FALSE;
                    posxcorreta = FALSE;
                    posycorreta = FALSE;
                } else {
                    bloconaoquebrado = TRUE;
                }
            }
        }

        quebrou2blocos = probabilidade();

        pularlinhas(1);
        printf("%s quebra o bloco na posição %d, %d!\n", player == 1 ? p1 : p2, x, y);

        if (quebrou2blocos == 4) {
            posaleatoria = probabilidade();

            pularlinhas(1);
            printf("Oops! O rio é perigoso!, %s quebrou um bloco adjacente!\n", player == 1 ? p1 : p2);

            escolherposicao(coord, posaleatoria, x, y);
        } else {
            coord[x][y] = BGELOQ;
        }

        *(ptr_pts) += 1;

        if(escbloco == 2){
            quebraroutrobloco(p1, p2, player, iceberg, coord, &(*(ptr_pts)));
        }
    }
    *(ptr_fimdojogo) = checarcaminhos(coord, iceberg);

	if(*(ptr_fimdojogo) == TRUE){
	    pularlinhas(2);
        printf("%s isolou o iceberg do continente!\n", player == 1 ? p1 : p2);
        printf("Pontuação de %s: %d\n", player == 1 ? p1 : p2, *(ptr_pts));

        if(player == 1){
            finalizarjogo(p2, coord, (*(ptr_pts2)));
        }

        if(player == 2){
            finalizarjogo(p1, coord, (*(ptr_pts2)));
        }
	}
}

void jogo(char coord[MAPAX][MAPAY], char p1[PNVETORTAM], char p2[PNVETORTAM], int cice[CICETAM], int *ptr_pts1, int *ptr_pts2){
	int sleep(int);
	int fimdojogo = FALSE;
	
	while(fimdojogo == FALSE){
		interface(coord, p1, p2, *(ptr_pts1), *(ptr_pts2));

		quebrarblocopara(p1, p2, 1, cice, coord, &(*(ptr_pts1)), &fimdojogo, &(*(ptr_pts2)));

        if(fimdojogo == TRUE){
            break;
        }

		sleep(3);
		interface(coord, p1, p2, *(ptr_pts1), *(ptr_pts2));
		
		quebrarblocopara(p1, p2, 2, cice, coord, &(*(ptr_pts2)), &fimdojogo, &(*(ptr_pts1)));

        if(fimdojogo == TRUE){
            break;
        }

		sleep(3);
		interface(coord, p1, p2, *(ptr_pts1), *(ptr_pts2));
	}
}

int main(){
	char mapa[MAPAX][MAPAY];
	char p1nome[PNVETORTAM], p2nome[PNVETORTAM];
	
	int coordiceberg[CICETAM];
	int pts1 = 0, pts2 = 0;

	confplayers(p1nome, p2nome);
	gerariceberg(coordiceberg);
	gerarmapa(mapa, coordiceberg);
	jogo(mapa, p1nome, p2nome, coordiceberg, &pts1, &pts2);
	
	return 0;
}
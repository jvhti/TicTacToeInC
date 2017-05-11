#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

typedef struct{
	char x, y;
} point;

typedef struct{
	char tela[3][3];
	char jogadas;
	char jogadorAtual;
	char simboloComputador;
	char simboloJogador;
	char dificuldade;
} jogo;

void parabens(jogo *j, char res){
	bool computerWon = (res != j->simboloJogador);
	if(!computerWon)
		printf("\n\
	            ▄▄\n\
	           █░░█\n\
	           █░░█\n\
	          █░░░█\n\
	         █░░░░█\n\
	███████▄▄█░░░░░██████▄\n\
	▓▓▓▓▓▓█░░░░░░░░░░░░░░█\n\
	▓▓▓▓▓▓█░░░░░░░░░░░░░░█\n\
	▓▓▓▓▓▓█░░░░░░░░░░░░░░█\n\
	▓▓▓▓▓▓█░░░░░░░░░░░░░░█\n\
	▓▓▓▓▓▓█░░░░░░░░░░░░░░█\n\
	▓▓▓▓▓▓█████░░░░░░░░░█\n\
	██████▀    ▀▀██████▀\n");
	else{
		printf("\n\
	░░░░▄▄██▀▀▀▀▀▀▀█▄░░░░░░░\n\
	░░▄▀▀░░░░░░░░░░░░▀█▄░░░░\n\
	░█▀░░░░░░░░░░░░░░░░█▄░░░\n\
	▄█░░░▄▄▄█▄▄░░▄░░░░░░█░░░\n\
	█░░░▀██▀▀▀░██▄█░░░░░▀█░░\n\
	█░░░░░▄░░▀▄▄░░░░▄░░░░▀█░\n\
	█▀░████░░░░████░▀░░░░░█░\n\
	█░░▀███░░░░███▀░░░░░░░█▄\n\
	█░░▄░▀▀░░░░▀▀░░▄░░░░░░██\n\
	▀█░░█▀░▄▄░░█░▀▀░░░░░░░█▀\n\
	░▀█░░░░█▀▀▀▀▀▀▄░░░░░░░█░\n\
	░░█░░░█░░▄▄▄▄░▄█░░░░░▄█░\n\
	░░▀█░░██▀▀██▀▀▀█▀░░░▄█░░\n\
	░░░▀█▄░░░░░░░░▄░░░░▄█░░░\n\
	░░░░░▀▄▄▀██████░░▄█▀░░░░\n\
	░░░░░░░▀█▄▄▄▄▄▄▄█▀░░░░░░\n\
	░░░░░░░░░▄▄████▄░░░░░░░░\n");
	}
	printf("*********\nO %s venceu o jogo!\n", computerWon ? "Computador" : "Jogador");
}

void atualizarTela(jogo *j){
	int i;
	for(i = 0; i < 3; ++i)
		printf("%c|%c|%c\n", j->tela[i][0], j->tela[i][1], j->tela[i][2]);
}

char verifyWin(jogo *j){
	int y, x;
	//Horizontal
	for(y = 0; y < 3; ++y){
		if(j->tela[y][0] == j->tela[y][1] && j->tela[y][1] == j->tela[y][2] && j->tela[y][0] != '-'){
			return j->tela[y][1];
		}
	}
	//Vertical
	for(x = 0; x < 3; ++x){
		if(j->tela[0][x] == j->tela[1][x] && j->tela[1][x] == j->tela[2][x] && j->tela[0][x] != '-' ){
			return j->tela[1][x];
		}
	}
	//Diagonal
	if((j->tela[0][2] == j->tela[1][1] && j->tela[2][0] == j->tela[1][1] && j->tela[1][1] != '-')){
		return j->tela[0][2];
	}
	if(j->tela[0][0] == j->tela[1][1] && j->tela[2][2] == j->tela[1][1] && j->tela[1][1] != '-'){
		return j->tela[0][0];
	}

	return false;
}

bool isComputer(jogo *j) { return j->jogadorAtual == 1; }

bool verifyVazio(jogo *j, char l, char c){
	return j->tela[l][c] == '-';
}

bool doMove(jogo *j, char jogador, char l, char c){
	if(!verifyVazio(j, l, c)) return false;
	j->tela[l][c] = jogador;
	return true;
}

int simulateSimulation(jogo *j, point *p, int depth){
	if(depth >= 1000) return -INT_MIN;

	jogo *cJogo = malloc(sizeof(jogo));
	cJogo = memcpy(cJogo, j, sizeof(jogo));

	simulateSimulation(cJogo, p, depth + 1);
	
	free(cJogo);
}

void simulateComputer(jogo *j){
	if(j->dificuldade == 0){
		//Movimento Aleatorio
		int l, c;

		do{
			l = rand() % 3;
			c = rand() % 3;
		}while(!verifyVazio(j, l, c));
		doMove(j, j->simboloComputador, l, c);
	}else{
		point *p = malloc(sizeof(point));
		simulateSimulation(j, p, 0);
	}
	printf("Computador jogou:\n");
}

void readPlayer(jogo *j){
	int a;
	printf("Sua ação (AB): \n");
	scanf("%i", &a);

	char linha = a / 10;
	char coluna = a % 10;

	if(linha > 2 || linha < 0 || coluna > 2 || coluna < 0 || !doMove(j, j->simboloJogador, linha, coluna)){
		printf("Movimento invalido\n");
		readPlayer(j);
		return;
	}
}

void resetarJogo(jogo *j, int dificuldade){
	int i, x;
	for(i = 0; i < 3; ++i){
		for(x = 0; x < 3; ++x){
			j->tela[i][x] = '-';
		}
	}
	j->jogadas = 0;
	j->jogadorAtual = 0;

	j->simboloComputador = isComputer(j) ? 'X' : 'O';
	j->simboloJogador = !isComputer(j) ? 'X' : 'O'; 

	j->dificuldade = dificuldade;
}

int iniciarJogo(int dificuldade, int qntJogos){
	jogo *newJogo = malloc(sizeof(jogo));
	int jogosAtuais = 0;

	resetarJogo(newJogo, dificuldade);

	printf("O primeiro jogador será %s\n", isComputer(newJogo) ? "Computador" : "Você");
	while(1){
		char res = verifyWin(newJogo);
		if(res != 0){
			parabens(newJogo, res);
			break;
		}
		atualizarTela(newJogo);

		if(isComputer(newJogo)){
			simulateComputer(newJogo);
		}else{
			readPlayer(newJogo);
		}

		newJogo->jogadorAtual = isComputer(newJogo) ? 0 : 1;
	}
}

int main(){
	int dificuldade = 0, qntJogos = 1, op;
	
	menu:
	printf("1 - Nível do jogo (%s)\n", dificuldade == 0 ? "Easy" : "Hard");
	printf("2 - Qtd jogos p/ rodada (%i)\n", qntJogos);
	printf("3 - Start\n");
	printf("4 - Sair\n");

	scanf("%i", &op);
	int op2;
	switch(op){
		case 1:
			op2 = -1;
			printf("\n0 - Voltar\n");
			printf("1 - Easy\n");
			printf("2 - Hard\n");
			while(op2 != 0 && op2 != 1 && op2 != 2) scanf("%i", &op2);
			
			if(op2 != 0)
				dificuldade = op2;
			
			printf("\n\n"); goto menu;
			break;
		case 2:
			op2 = -1;
			printf("Digite uma dificuldade entre 1 e 1000\n");
			while(op2 <= 0 || op2 > 1000) scanf("%i", &op2);
			qntJogos = op2;
			printf("\n\n"); goto menu;
			break;
		case 3:
			iniciarJogo(dificuldade, qntJogos);
			break;
		case 4:
			return 0;
			break;
		default:
			printf("Opção inválida!\n");
			goto menu;
	}

	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#define TROLL_FACE 	"\n\
	    ▄▄▄▄▀▀▀▀▀▀▀▀▄▄▄▄▄▄\n\
	    █░░░░▒▒▒▒▒▒▒▒▒▒▒▒░░▀▀▄\n\
	   █░░░▒▒▒▒▒▒░░░░░░░░▒▒▒░░█\n\
	  █░░░░░░▄██▀▄▄░░░░░▄▄▄░░░█\n\
	 ▀▒▄▄▄▒░█▀▀▀▀▄▄█░░░██▄▄█░░░█\n\
	█▒█▒▄░▀▄▄▄▀░░░░░░░░█░░░▒▒▒▒▒█\n\
	█▒█░█▀▄▄░░░░░█▀░░░░▀▄░░▄▀▀▀▄▒█\n\
	 █▀▄░█▄░█▀▄▄░▀░▀▀░▄▄▀░░░░█░░█\n\
	  █░░▀▄▀█▄▄░█▀▀▀▄▄▄▄▀▀█▀██░█\n\
	   █░░██░░▀█▄▄▄█▄▄█▄████░█\n\
	    █░░░▀▀▄░█░░░█░███████░█\n\
	     ▀▄░░░▀▀▄▄▄█▄█▄█▄█▄▀░░█\n\
	       ▀▄▄░▒▒▒▒░░░░░░░░░░█\n\
	          ▀▀▄▄░▒▒▒▒▒▒▒▒▒▒░█\n\
	              ▀▄▄▄▄▄░░░░░█\n"

#define THUMBS_UP "\n\
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
	██████▀    ▀▀██████▀\n"

#define SAD_FACE "\n\
	    ▄▄██▀▀▀▀▀▀▀█▄\n\
	  ▄▀▀░░░░░░░░░░░░▀█▄\n\
	 █▀░░░░░░░░░░░░░░░░█▄\n\
	▄█░░░▄▄▄█▄▄░░▄░░░░░░█\n\
	█░░░▀██▀▀▀░██▄█░░░░░▀█\n\
	█░░░░░▄░░▀▄▄░░░░▄░░░░▀█\n\
	█▀░████░░░░████░▀░░░░░█\n\
	█░░▀███░░░░███▀░░░░░░░█▄\n\
	█░░▄░▀▀░░░░▀▀░░▄░░░░░░██\n\
	▀█░░█▀░▄▄░░█░▀▀░░░░░░░█▀\n\
	 ▀█░░░░█▀▀▀▀▀▀▄░░░░░░░█\n\
	  █░░░█░░▄▄▄▄░▄█░░░░░▄█\n\
	  ▀█░░██▀▀██▀▀▀█▀░░░▄█\n\
	   ▀█▄░░░░░░░░▄░░░░▄█\n\
	     ▀▄▄▀██████░░▄█▀\n\
	       ▀█▄▄▄▄▄▄▄█▀\n\
	         ▄▄████▄\n"


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
		printf(THUMBS_UP);
	else{
		printf(SAD_FACE);
	}
	printf("*********************************************\nO %s venceu o jogo!\n*********************************************\n", computerWon ? "Computador" : "Jogador");
}

void atualizarTela(jogo *j){
	int i;
	printf("  0|1|2\n");
	for(i = 0; i < 3; ++i)
		printf("%i %c|%c|%c\n", i, j->tela[i][0], j->tela[i][1], j->tela[i][2]);
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

bool isComputer(jogo j) {
	return j.jogadorAtual == 1;
}

bool isEmpty(jogo j, point p){
	return j.tela[p.y][p.x] == '-';
}

bool doMove(jogo *j, char jogador, point p){
	if(!isEmpty(*j, p)) return false;

	j->tela[p.y][p.x] = jogador;
	++j->jogadas;
	return true;
}

bool isOver(jogo j){
	if(j.jogadas >= 9 || verifyWin(&j) != 0)
		return true;
	return false;
}

int score(jogo j, int depth){
	char won = verifyWin(&j);

	if(won == j.simboloComputador){
		return 100 - depth;
	}else if(won == j.simboloJogador)
		return depth - 100;
	
	return 0;

}
int simulateSimulation(jogo j, point *pp, int depth, bool maximizingPlayer){
	if(depth >= 100000) return -1000;
	
	if(isOver(j)) return score(j, depth);
	
	int scores[500];
	point moves[500];
	size_t scoresLeng = 0, movesLeng = 0;
	int x, y;
	
	for(y = 0; y < 3; ++y){
		for(x = 0; x < 3; ++x){
			point p;
			p.x = x;
			p.y = y;

			if(!isEmpty(j, p)) continue;

			moves[movesLeng++] = p;
			jogo jj = j;
			doMove(&jj, isComputer(j) ? j.simboloComputador : j.simboloJogador, p);
			jj.jogadorAtual = isComputer(jj) ? 0 : 1;
			
			scores[scoresLeng++] = simulateSimulation(jj, pp, depth + 1, isComputer(jj));
		}
	}

	if(maximizingPlayer){
		int maxIndex = 0;
		for(y = 0; y < scoresLeng; ++y){
			if(scores[y] >= scores[maxIndex])
				maxIndex = y;
		}
		*pp = moves[maxIndex];
		return scores[maxIndex];
	}else{
		int minIndex = 0;
		for(y = 0; y < scoresLeng; ++y){
			if(scores[y] <= scores[minIndex])
				minIndex = y;
		}
		*pp = moves[minIndex];
		return scores[minIndex];
	}
}

void simulateComputer(jogo *j){
	point p;
	if(j->dificuldade == 0){
		do{
			p.y = rand() % 3;
			p.x = rand() % 3;
		}while(!isEmpty(*j, p));
	}else
		simulateSimulation(*j, &p, 0, true);
	
	doMove(j, j->simboloComputador, p);
	printf("Computador jogou:\n");
}

void readPlayer(jogo *j){
	int a;
	printf("Sua ação (AB): \n");
	scanf("%i", &a);
	point p;
	p.y = a / 10;
	p.x = a % 10;

	if(p.y > 2 || p.y < 0 || p.x > 2 || p.x < 0 || !doMove(j, j->simboloJogador, p)){
		printf("Movimento invalido\n");
		readPlayer(j);
		return;
	}
}

void resetarJogo(jogo *j, int dificuldade){
	int y, x;
	for(y = 0; y < 3; ++y)
		for(x = 0; x < 3; ++x)
			j->tela[y][x] = '-';

	j->jogadas = 0;
	j->jogadorAtual = rand() % 2;

	bool isComp = isComputer(*j);
	j->simboloComputador = isComp ? 'X' : 'O';
	j->simboloJogador = !isComp ? 'X' : 'O'; 

	j->dificuldade = dificuldade;
}

void velha(){
	printf(TROLL_FACE);
	printf("Deu velha! HA! HA!\n");
}

int iniciarJogo(int dificuldade, int qntJogos){
	jogo *newJogo = malloc(sizeof(jogo));
	int jogosAtuais = 0;

	resetarJogo(newJogo, dificuldade);

	printf("O primeiro jogador será %s\n", isComputer(*newJogo) ? "Computador" : "Você");
	while(1){
		char res = verifyWin(newJogo);
		if(res != 0){
			parabens(newJogo, res);
			break;
		}else if(isOver(*newJogo)){
			velha();
			break;
		}
		atualizarTela(newJogo);
		bool isComp = isComputer(*newJogo);

		if(isComp){
			simulateComputer(newJogo);
		}else{
			readPlayer(newJogo);
		}

		newJogo->jogadorAtual = isComp ? 0 : 1;
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
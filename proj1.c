/*
INTRODUCAO AOS ALGORITMOS E ESTRUTURAS DE DADOS
2016/2017 - 2 SEMESTRE
PROJETO 1

86372 ALEXANDRE GALAMBAS
86430 GUILHERME GALAMBAS
*/

// BIBLIOTECAS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// CONSTANTES

#define MAX_USERS 1000
#define MAX_MSG 10000
#define MAX_CHAR 140

// ESTRUTURAS

typedef struct {
	int id;
	char text[MAX_CHAR + 1];t
} message;

// VARIAVEIS GLOBAIS

message forum[MAX_MSG];
int pos = 0;

// COMANDOS

void command_A() {																	// ADICIONA UMA MENSAGEM

	int i=0, c;

	while( (c=getchar()) != ' ' ) {													// Le o ID do utilizador
		forum[pos].id *= 10;
		forum[pos].id += c - '0';
	}

	while( (c=getchar()) != '\n' )													// Leitura da mensagem
		forum[pos].text[i++] = c;
	forum[pos].text[i] = '\0';

	pos++;
}

void command_L() {																	// LISTA TODAS AS MENSAGENS

	printf("*TOTAL MESSAGES:%d\n", pos);											// Imprime o numero total de mensagens
	for( int i = 0; i < pos; i++ )													// Imprime todas as mensagens
		printf("%d:%s\n", forum[i].id, forum[i].text);
}

void command_U() {																	// LISTA TODAS AS MENSAGENS INTRODUZIDAS POR UM DADO UTILIZADOR

	int c, user;

	while( (c=getchar()) != '\n' ) {												// Le o ID do utilizador
		user *= 10;
		user += c - '0';
	}

	printf("*MESSAGES FROM USER:%d\n", user);										// Imprime o ID do utilizador	
	for( c=0; c < pos; c++ )														// Imprime todas as mensagens do utilizador
		if( forum[c].id == user )
			printf("%s\n", forum[c].text);
}

void command_O() {																	// LISTA AS MENSAGENS MAIS LONGAS

	static int longest = 0;															// Comprimento da(s) mensagem(s) mais longa(s)
	static int longest_pos[MAX_MSG] = {0};											// Posicao das mensagem(s) mais longa(s)
	static int longest_cnt = 0;														// Contador do numero de frases longas
	static int i=0;

	for( int text_len; i < pos; i++) {												// Encontra a posicao da(s) mensagem(s) mais longa(s)

		text_len = strlen( forum[i].text );

		if( text_len > longest ) {													// Define o comprimento da(s) mensagem(s) mais longa(s)
			longest_cnt = 0;
			longest = text_len;
			longest_pos[longest_cnt++] = i;
		}
		else if( text_len == longest )												// Guarda a posicao da(s) mensagem(s) mais longa(s)
			longest_pos[longest_cnt++] = i;
	}

	for( int j=0; j < longest_cnt; j++ )
		printf("*LONGEST SENTENCE:%d:%s\n", forum[longest_pos[j]].id, forum[longest_pos[j]].text);
}

void command_T() {																	// ESCREVE O UTILIZADOR MAIS ATIVO NA ESCRITA DE MENSAGENS

	int active_user[MAX_USERS] = {0};												// Utilizador(es) mais ativo(s)
	int active_cnt = 0;																// Contador do numero de utilizadores mais ativos
	static int num_msg[MAX_USERS] = {0};											// Numero de mensagens de cada utilizador
	static int active_msg = 0;														// Numero de mensagens do(s) utilizador(es) mais ativo(s)
	static int i=0;

	while( i < pos )																// Preenche o vetor do numero de mensagens de cada utilizador
		num_msg[forum[i++].id]++;

	for(int j=0; j < MAX_USERS; j++ ) {												// Encontra o(s) utilizador(es) mais ativo(s)

		if( num_msg[j] > active_msg ) {												// Define o(s) utilizador(es) mais ativo(s)
			active_cnt = 0;
			active_msg = num_msg[j];
			active_user[active_cnt++] = j;
		}
		else if( num_msg[j] == active_msg )											// Guarda o ID do(s) utilizador(es) mais ativo(s)
			active_user[active_cnt++] = j;
	}

	for( int k=0; k < active_cnt; k++ )
		printf("*MOST ACTIVE USER:%d:%d\n", active_user[k], num_msg[active_user[k]]);
}

void command_S() {																	// LISTA TODAS AS MESAGENS POR ORDEM ALFABETICA

	static int sorted[MAX_MSG];														// Vetor das posicoes das mensagens ordenadas alfabeticamente
	static int k=0;
	int lim = k , cmp, aux, i, j;

	while( k < pos ) {																// Atribuicao das posicoes ao vetor
		sorted[k] = k;
		k++;
	}

	for( i = lim; i < pos; i++ ) {													// Insertion sort adaptado

		aux = sorted[i];

		for( j = i-1; j >= 0; j-- ) {

			cmp = strcmp(forum[aux].text, forum[sorted[j]].text);

			if( cmp < 0 )
				sorted[j+1] = sorted[j];
			else if( cmp == 0 && forum[aux].id < forum[sorted[j]].id )
				sorted[j+1] = sorted[j];
			else break;
		}
		
		sorted[j+1] = aux;
	}

	printf("*SORTED MESSAGES:%d\n", pos);
	for( i = 0; i < pos; i++ )														// Imprime todas as mensagens
		printf("%d:%s\n", forum[sorted[i]].id, forum[sorted[i]].text);
}

void command_C() {																	// ESCREVE O NUMERO DE OCORRENCIAS DE UMA PALAVRA

	const int OUT=0, IN=1, MATCH=2;
	char  c, word[MAX_CHAR + 1];
	int i, j, k=0, len, count=0, status=OUT;

	for( i = 0; (c=getchar()) != '\n'; i++ )										// Le a palavra a procurar
		word[i] = c;
	word[i] = '\0';

	for( i = 0; i < pos; i++ ) {													// Muda de mensagem

		len = strlen(forum[i].text);

		for( j = 0; j <= len; j++ ) {												// Percorre a mensagem

			c = forum[i].text[j];

			if ( c == ';' || c == ',' || c == ' ' || c == '\t' || c == '\n' || c == '.' || c == '\0' ) {
				if( status == MATCH )
					count++;														// Adiciona uma ocorrencia
				status = OUT;
				k=0;
			}
			else if( status == OUT ) {												// Verifica se a primeira letra corresponde
				if( word[0] == c )
					status = MATCH;
				else
					status = IN;
			}
			else if( status == MATCH && word[++k] != c )							// Verifica se o resto da palavra corresponde
				status = IN;
		}
	}

	printf("*WORD %s:%d\n", word, count);
}

// PROGRAMA PRINCIPAL

int main() {

	while(1) {
		switch(getchar()) {
			case 'A':
				getchar();
				command_A();
				break;
			case 'L':
				getchar();
				command_L();
				break;
			case 'U':
				getchar();
				command_U();
				break;
			case 'O':
				getchar();
				command_O();
				break;
			case 'T':
				getchar();
				command_T();
				break;
			case 'S':
				getchar();
				command_S();
				break;
			case 'C':
				getchar();
				command_C();
				break;
			case 'X':
				printf("%d\n", pos);
				return EXIT_SUCCESS;
			default:
				getchar();
				printf("ERRO: Comando desconhecido\n");
		}
	}

	return EXIT_FAILURE;
}
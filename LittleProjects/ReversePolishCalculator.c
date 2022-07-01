#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/* atof: converte cadeia s a um double */
double a_tof(char s[])
{
	double val, pot;
	int i, sinal;

	for (i = 0; isspace(s[i]); i++)
		;
	sinal = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (pot = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		pot *= 10.0;
	}
	return sinal * val / pot;
}

#define MAXOP 100	/* tamanho maximo operando/operador */
#define NUMERO '0'	/* sinaliza que numero foi encontrado */
#define MAXVAL 100	/* profundidade max. da pilha */
#define TAMBUF 100

int pp = 0;			/* prox. posicao livre na pilha */
double val[MAXVAL];	/* pilha de valores */
char buf[TAMBUF];	/* buffer para ungetch */
int pbuf = 0;		/* próxima posicao livre em buf */

/* obtem um caractere (talvez retornado) */
int getch(void)
{
	return (pbuf > 0) ? buf[--pbuf] : getchar();
}

/* retorna caractere a entrada */
void ungetch(int c)
{
	if (pbuf > TAMBUF)
		printf("caracteres demais\n");
	else
		buf[pbuf++] = c;
}

/* obtemop: obtem prox. operador ou operando numerico */
int obtemop(char s[])
{
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (!isdigit(c) && c != '.')
		return c;	/* nao eh um numero */
	i = 0;
	if (isdigit(c))	/* agrupa a parte inteira */
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')	/* agrupa a parte fracionaria */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMERO;
}

/* empil: empilha f na pilha de valores */
void empil(double f)
{
	if (pp < MAXVAL)
		val[pp++] = f;
	else
		printf("Erro: pilha cheia %g\n", f);
}

/* desempil: retira e retorna o valor do topo da pilha */
double desempil(void)
{
	if (pp > 0)
		return val[--pp];
	else {
		printf("Erro: pilha vazia\n");
		return 0.0;
	}
}

int main()
{
	int tipo;
	double op2;
	char s[MAXOP];

	while ((tipo = obtemop(s)) != EOF) {
		switch (tipo) {
		case NUMERO:
			empil(a_tof(s));
			break;
		case '+':
			empil(desempil() + desempil());
			break;
		case '*':
			empil(desempil() * desempil());
			break;
		case '-':
			op2 = desempil();
			empil(desempil() - op2);
		case '/':
			op2 = desempil();
			if (op2 != 0.0)
				empil(desempil() - op2);
			else
				printf("erro: divisor zero\n");
			break;
		case '\n':
			printf("\t%.8g\n", desempil());
			break;
		default:
			printf("Erro: comando desconhecido %s\n", s);
			break;
		}
	}
	return 0;
}

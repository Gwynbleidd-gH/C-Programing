#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int getRandomNumber(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

enum Status
{
	CONTINUE,
	WON,
	LOST
};

int rollDice()
{
	int dice1 = getRandomNumber(1, 6);
	int dice2 = getRandomNumber(1, 6);

	int sum = dice1 + dice2;

	printf("O jogador rolou %d + %d = %d\n", dice1, dice2, sum);
	return sum;
}

int main()
{
	setlocale(LC_ALL, "portuguese");
	srand(time(NULL));

	enum Status gameStatus;
	int sum = rollDice();
	int myPoints = 0;

	switch (sum) {
	case 7:
	case 11:
		gameStatus = WON;
		break;
	case 2:
	case 3:
	case 12:
		gameStatus = LOST;
		break;
	default:
		gameStatus = CONTINUE;
		myPoints = sum;
		printf("Ponto é %d\n", myPoints);
		break; /* opcional */
	}

	while (gameStatus == CONTINUE) {
		sum = rollDice();
		if (myPoints == sum) {
			gameStatus = WON;
		}
		else if (sum == 7) {
			gameStatus = LOST;
		}
	}

	switch (gameStatus) {
	case WON:
		printf("O jogador venceu!\n");
		break;
	case LOST:
		printf("O jogador perdeu!\n");
		break;
	}

	return 0;
}

#define _CRT_SECURE_NO_WARNINGS    
#include <stdio.h>	    	   
#include <ctype.h>
#include <string.h>

void Greeting(void);
void PlayAgain(char*againPtr);
void UpperCaseWord(char word[]);
void PlayOneGame(char solution[]);
void CreateStarword(char starword[], int length);
int CheckGuess(char Guesses[], int *count);
int ReplaceStars(char solution[], char starword[], char letter);
int DidYouWin(char solution[]);

int main(void)
{
	FILE* inp;
	char decision;
	char answer[10];
	inp = fopen("words.txt", "r");
	Greeting(); //Greeting and game instructions

	do
	{
		fscanf(inp, "%s ", &answer); //Reads word from file and makes it uppercase
		UpperCaseWord(answer);

		PlayOneGame(answer); //Function that runs one game

		PlayAgain(&decision); // Determines wherther or not to play another game
	} 
	while (decision == 'Y' || decision == 'y');
	
	
	fclose(inp);
	return (0);
}

void Greeting(void)
{
	printf("Welcome to Hangman!!\n\n");
	printf("Please read the following instructions before you play.\n\n");
	printf(" - You will be presented with a word to be guessed\n");
	printf(" - Guess letters one at a time\n");
	printf(" - You can have up to six incorrect letter guesses\n");
	printf(" - You can only guess the word when you have made a correct letter guess\n");
	printf("Or when you have guessed letters incorrectly SIX times.\n\n");	
}

void PlayAgain(char*againPtr)
{
	printf("Would you like to play another round (y or n)?: ");
	scanf(" %c", againPtr);
}

void UpperCaseWord(char word[])
{
	for (int i = 0; i <= strlen(word); i++)
	{
		toupper(word[i]);
	}
}

void PlayOneGame(char solution[])
{
	int MaxGuess = 0, win = 0, count = 0, test;
	char Guesses[6], letter;
	char starword[10], lettersGuessed[6];
	int length = strlen(solution);

	CreateStarword(starword, length);

	int i = 0; 
	do
	{
		printf("\nHere are the letters guessed so far:\n\n");
		printf("%s ", starword);
		printf("%s\n", Guesses);
		printf("-------------------------------\n");
		letter = CheckGuess(Guesses,&count);
		test = ReplaceStars(solution, starword, letter);

		if (test == 1)
		{
			win = DidYouWin(solution);
		}
		else
		{
			MaxGuess++;
		}
			
	}
	while (MaxGuess < 6 && win == 0);

}

void CreateStarword(char starword[], int length)
{
	int null = length + 1;

	for (int i = 0; i <= length; i++)
	{
		starword[i] = '*';
	}
	starword[null] = '\0';
}

int CheckGuess(char Guesses[], int *count)
{
	char temp;
	printf("Guess a letter:");
	scanf("%d", &temp);
	temp = toupper(temp);

	Guesses[*count] = temp;
	*count = *count + 1;
	Guesses[*count] = '\0';

	return(temp);

}

int ReplaceStars(char solution[], char starword[], char letter)
{
	int len = strlen(solution);
	int i, rv = 0;

	for (i = 0; i < len; i++)
	{
		if (solution[i] == letter)
		{
			starword[i] = letter;
			rv = 1;
		}
		return(rv);
	}


}

int DidYouWin(char solution[])
{
	char Guess[10];
	int rv;
	printf("\nEnter a guess for the word:");
	scanf(" %s", Guess);
	UpperCaseWord(Guess);

	if (strcmp(solution, Guess) == 0)
	{
		rv = 1;
	}
	
	return(rv);
}
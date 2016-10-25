#include<iostream>
#include<string>
#include"FBullCowGame.h"

void PrintIntro();
void PlayGame();
std::string GetGuess();
bool AskToPlayAgain();
FBullCowGame BCGame; // instantiate a new game

// the entry point for our application
int main()
{
	do {
		PrintIntro();
		PlayGame();
	}
	while (AskToPlayAgain());

	return 0; // exit the application
}

// introduce the game
void PrintIntro()
{
	constexpr int WORD_LENGTH = 9;
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << WORD_LENGTH;
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

std::string GetGuess()
{
	int CurrentTry = BCGame.GetCurrentTry();
	// get a guess from the user
	std::cout << "Try "<< CurrentTry <<". Enter your guess: ";
	std::string Guess = "";
	std::getline(std::cin, Guess);
	
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again (y/n)?";
	std::string Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;
	
	return (Response[0] == 'y' || Response[0] == 'Y');
}

void PlayGame() 
{
	int MaxTries = BCGame.GetMaxTries();
	std::cout << MaxTries << std::endl;
	
	for (int i = 0; i < MaxTries; i++)
	{
		std::string Guess = GetGuess();
		std::cout << "Your guess was: " << Guess << std::endl;
		std::cout << std::endl;
	}
	return;
}
/* This is the console executable that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interacion. For game logic see the FBullCowGame class
*/

#include<iostream>
#include<string>
#include"FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game

// the entry point for our application
int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		//TODO  add a game summary
		bPlayAgain = AskToPlayAgain();
	}
	while (bPlayAgain);

	return 0; // exit the application
}

// introduce the game
void PrintIntro()
{
	constexpr int32 WORD_LENGTH = 9;
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << WORD_LENGTH;
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

FText GetGuess()
{
	int32 CurrentTry = BCGame.GetCurrentTry();
	// get a guess from the user
	std::cout << "Try "<< CurrentTry <<". Enter your guess: ";
	FText Guess = "";
	std::getline(std::cin, Guess);
	
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again (y/n)?";
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;
	
	return (Response[0] == 'y' || Response[0] == 'Y');
}

void PlayGame() 
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << MaxTries << std::endl;
	
	//TODO change from FOR to WHILE loop once we are validating tries
	for (int32 i = 0; i < MaxTries; i++)
	{
		FText Guess = GetGuess(); //TODO make loop check valid guess
		
		//submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);

		//print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << std::endl;
		std::cout << "Your guess was: " << Guess << std::endl;
		std::cout << std::endl;
	}

	//TODO summarise game

	return;
}
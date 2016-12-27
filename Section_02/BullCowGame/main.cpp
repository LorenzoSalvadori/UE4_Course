/* This is the console executable that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interacion. For game logic see the FBullCowGame class
*/

#pragma once

#include<iostream>
#include<string>
#include"FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game, which we re-use across plays

// the entry point for our application
int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		PrintGameSummary();
		bPlayAgain = AskToPlayAgain();
		std::cout << std::endl;
	}
	while (bPlayAgain);

	return 0; // exit the application
}

// introduce the game
void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do {
		// get a guess from the user
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		//check if the input is valid
		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "The word you entered is not an isogram.\n"
				<< "Isograms are words with no repeating letters.\n\n";
			break;
		case EGuessStatus::Invalid_Character:
			std::cout << "The word you entered contains invalid characters, such as"
				<< "numbers, punctuations, or other symbols.\n"
				<< "Please enter a " << BCGame.GetHiddenWordLength() << " letters isogram.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter only lowercase characters.\n\n";
			break;
		case EGuessStatus::No_Input:
			std::cout << "Input is required, please enter a "
				<< BCGame.GetHiddenWordLength() << "letters isogram.\n\n";
			break;
		default:
			//assume guess is valid
			break;
		}
	} while (Status != EGuessStatus::Ok);
	return Guess;
}

// asks to play again
bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (y/n) \n";
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;
	
	return (Response[0] == 'y' || Response[0] == 'Y');
}

// Game summary
void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Congratulations! You won! :)\n";
	}
	else
	{
		std::cout << "Sorry you are out of tries. Better luck next time. ;)\n";
	}
}

// plays a single game to completion
void PlayGame() 
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << "You have " << MaxTries << " tries.\n";
	
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();	

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << std::endl;
		std::cout << "Your guess was: " << Guess << "\n\n";
	}

	return;
}

#include "FBullCowGame.h"
using int32 = int;

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

bool FBullCowGame::IsGameWon() const
{
	return false;
}

void FBullCowGame::Reset()
{ 
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";

	MyHiddenWord = HIDDEN_WORD;
	MyMaxTries = MAX_TRIES;
	MyCurrentTry = 1;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (false) // if the guess is not an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is different than MyHiddenWord.length
	{
		return EGuessStatus::Wrong_Length;
	}
	else if (false) // if the guess is not all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (false) // if the guess contains invalid characters (numbers, punctuation, etc)
	{
		return EGuessStatus::Invalid_Character;
	}
	else if (false) // if the guess is empty
	{
		return EGuessStatus::No_Input;
	}
	else
	{
		return EGuessStatus::Ok;
	}
}

// receives a valid guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	// increment the turn number
	MyCurrentTry++;

	// setup a return variable
	FBullCowCount BullCowCount;

	int32 HiddenWordLength = MyHiddenWord.length();
	// loop through all letters in the guess
	for (int32 MHWChar = 0; MHWChar < HiddenWordLength; MHWChar++)
	{
		// compare letters against the hidden word
		for (int32 GChar = 0; GChar < HiddenWordLength; GChar++)
		{
			// if they match then
			if (MyHiddenWord.at(MHWChar) == Guess.at(GChar))
			{
				if (MHWChar == GChar)
				{ // if they're in the same place
					BullCowCount.Bulls++; // increment bulls
				}
				
				else 
				{
					BullCowCount.Cows++; // increment cows if not
				}
				
			}
		}
		
	}

	return BullCowCount;
}

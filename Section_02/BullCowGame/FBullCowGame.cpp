#include "FBullCowGame.h"
#include<map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const {	return bGameIsWon; }

void FBullCowGame::Reset()
{ 
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";

	MyHiddenWord = HIDDEN_WORD;
	MyMaxTries = MAX_TRIES;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if the guess is not an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is different than MyHiddenWord.length
	{
		return EGuessStatus::Wrong_Length;
	}
	else if (!IsLowerCase(Guess)) // if the guess is not all lowercase - TODO add function for checking if not lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (false) // if the guess contains invalid characters (numbers, punctuation, symbols) - TODO add function for checking characters
	{
		return EGuessStatus::Invalid_Character;
	}
	else if (false) // if the guess is empty - TODO add function for checking if no input
	{
		return EGuessStatus::No_Input;
	}
	else
	{
		return EGuessStatus::Ok;
	}
}

// receives a valid guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); //assuming same length as guess
	
	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)
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


	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; // setup our map

	for (auto Letter : Word) // for all letters of the word
	{
		Letter = tolower(Letter);

		// if the letter is in the map
		if (LetterSeen[Letter])
		{
			return false;  // we do NOT have an isogram
		}
		else 
		{
			LetterSeen[Letter] = true; // add the letter to the map as seen
		}
	}

	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word) // loop through letters in word
	{
		if (!islower(Letter)) // if a letter is not lowercase
		{
			return false;
		}
	}

	return true;
}

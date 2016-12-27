#pragma once

#include "FBullCowGame.h"
#include<map>

// to make syntax Unreal friendly
#define TMap std::map
using FString = std::string;
using int32 = int;

// default constructor - DO NOT REMOVE!
FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const {	return bGameIsWon; }
TMap<FString, int32> HiddenWordsDictionaryByLength{ {"quasars", 7}, {"planet", 6},{"world", 5}, {"star", 4}, {"sun", 3} };

// helper function - get maximum number of tries
int32 FBullCowGame::GetMaxTries() const 
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };

	return WordLengthToMaxTries[MyHiddenWord.length()];
}

// resets the game
void FBullCowGame::Reset()
{ 
	FString HIDDEN_WORD = "planet"; // this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

// helper function - check if guess is valid
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
	else if (!IsLowerCase(Guess)) // if the guess is not all lowercase
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
	
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			if (MyHiddenWord.at(MHWChar) == Guess.at(GChar))
			{
				if (MHWChar == GChar)
				{
					BullCowCount.Bulls++;
				}
				else 
				{
					BullCowCount.Cows++;
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

// helper function - check if isogram
bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; // setup our map

	for (auto Letter : Word)
	{
		Letter = tolower(Letter);

		if (LetterSeen[Letter])
		{
			return false;  // we do NOT have an isogram
		}
		else 
		{
			LetterSeen[Letter] = true; // add the letter to the map as seen
		}
	}

	return true;
}

// helper function - check if lower case
bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}

	return true;
}

FString FBullCowGame::ChooseHiddenWord(int32 WordLength) const
{
	// TODO - select a word from the dictionary given its length
	return FString();
}

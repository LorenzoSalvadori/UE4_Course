#include<iostream>
#include<string>

using namespace std;
void PrintIntro();
void PlayGame();
string GetGuess();
bool AskToPlayAgain();

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
	cout << "Welcome to Bulls and Cows, a fun word game.\n";
	cout << "Can you guess the " << WORD_LENGTH;
	cout << " letter isogram I'm thinking of?\n";
	cout << endl;
	return;
}

string GetGuess()
{
	// get a guess from the user
	cout << "Enter your guess: ";
	string Guess = "";
	getline(cin, Guess);

	return Guess;
}

bool AskToPlayAgain()
{
	cout << "Do you want to play again (y/n)?";
	string Response = "";
	getline(cin, Response);
	cout << endl;
	
	return (Response[0] == 'y' || Response[0] == 'Y');
}

void PlayGame() 
{
	// loop for the number of turns asking for guesses
	constexpr int NUMBER_OF_TURNS = 5;
	for (int i = 0; i < NUMBER_OF_TURNS; i++)
	{
		string Guess = GetGuess();
		cout << "Your guess was: " << Guess << endl;
		cout << endl;
	}
	return;
}
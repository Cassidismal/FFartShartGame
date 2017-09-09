/* This is the console executable, that makes use of the ShartFart class
This acts as the view in a MVC pattern, and is responsible for all user interaction. FOr game logic see FShartsAndFartsGame class
*/
#pragma once

#include <iostream>
#include <string>
#include "FFartsAndShartsGame.h"

// "using" is good practice but caution when using multiple "using namespace's" with seperate namespaces. 
// You may get a "namespace clash" if both namespaces use the same language like "cout" but define them differently

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// functions prototypes as outside a class
int main();
void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintGameSummary();
bool AskToPlayAgain();

FFartsAndShartsGame FSGame; //instantiate(create an instance of) a new game, which we re-use across plays



							// the entry point for our application
int main()
{
	bool bPlayAgain = false;

	do
	{

		PrintIntro();
		PlayGame();
		PrintGameSummary();
		bPlayAgain = AskToPlayAgain();
		std::cout << std::endl;
	} while (bPlayAgain == true);

	std::cout << std::endl;
	return 0; // exit the application
}

void PrintIntro()
{
	//TODO difficulty selection option - chump, bum, champ - affects word length and # of max tries
	std::cout << "Let's play a game, we will call it 'Farts and Sharts'. \n It's a super fun nerd...err..word game my instructors online are helping me make.\n";
	return;
}

void PlayGame()
{
	FSGame.Reset();



	std::cout << "Can you guess the " << FSGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;

	// Set Max Tries based on length of isogram 
	int32 MaxTries = FSGame.GetMaxTries();

	// loop asking for guesses while the game is NOT won
	// and there are still tries remaining
	while (!FSGame.GetIsGameWon() && FSGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		// submit valid guess to the game, and recieve counts
		FFartShartCount FartShartCount = FSGame.SubmitValidGuess(Guess);

		std::cout << "Farts = " << FartShartCount.Farts;
		std::cout << " Sharts = " << FartShartCount.Sharts << std::endl;
		std::cout << "Your guess was: " << Guess << "\n\n";




	}

	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;

	do {
		// print out current guess # and get the guess
		int32 CurrentTry = FSGame.GetCurrentTry();
		int32 MaxTries = FSGame.GetMaxTries();
		std::cout << "Guess ";
		std::cout << CurrentTry << " of " << MaxTries << std::endl;
		std::cout << "Hit me with your best shot: ";
		getline(std::cin, Guess);

		// check guess validity and inform user when they enter an invalid guess and why
		Status = FSGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Not_Isogram:
			std::cout << "\nYour guess was not an Isogram.\n \nAn isogram, or 'nonpattern word' is a logological term \nfor a word or phrase without a repeating letter.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "\nInvalid guess.\nPlease use all lowercase letters.\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "\nPlease enter a " << FSGame.GetHiddenWordLength() << " letter word. \n";
			break;
		case EGuessStatus::Not_Alpha:
			std::cout << "\nPlease use all lowercase letters a-z only, NO special characters(including spaces).\n";
		default:
			// assume the guess is valid after exhausting all checks
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

void PrintGameSummary()
{
	if (FSGame.GetIsGameWon())
	{
		std::cout << "7777777777777777777777777777777S7777777777777777S777777777777S777777777777777777\n";
		std::cout << "77777777777777777S77777777S7777S77:::~77777777777777777S777777S77777777777777777\n";
		std::cout << "777777777777777777SS77777SS777S777?:::::I777777S7777777777777S777777777777777777\n";
		std::cout << "777777777777777777S77777SS77777S77::::::::?77777S777777S7777S7777777777777777777\n";
		std::cout << "777777777777777777S777777SS777777:::::::::::7777S77777SS77777S777777777777777777\n";
		std::cout << "77777777777777777S7777777S777777:::::::::::::+7S77777777S777SS777777777777777777\n";
		std::cout << "77777777777777777777777777S77777:::::~::::::::77777777S77777SS777777777777777777\n";
		std::cout << "777777777777S77777S77777777S7777=:~~=::::::::::77777777S777SS7777777777777777777\n";
		std::cout << "7777777777777S7777777S7777777:~~~~::::::::::::~ 777777S7777SS7777777777777777777\n";
		std::cout << "7777777777777S777777S7777777~~::::::::::::::::~~:I777777777S77777S77777777777777\n";
		std::cout << "77777777777777777777S777777:::::::::::::::::~~:::::~77S777SS77777777777777777777\n";
		std::cout << "777777777777777S77777S7777?::::::::::::::~~~~:::::::77777SS77777S777777777777777\n";
		std::cout << "777777777777777777777777777:::7777:,:~~~~~:::7777:::777777S777777S77777777777777\n";
		std::cout << "77777777777777S777777S77777:I7777777~~~::::I77777 ?:77777S77777S7777777777777777\n";
		std::cout << "7777777777777SS777777777I::~7 ....77+:::::I77....777~~~ 777S77777S7777S777777777\n";
		std::cout << "777777777777777S7777777::::777....  7:::::777....777~:::7777S77777S7777777777777\n";
		std::cout << "77777777777S7777777777:::::77+....777:::::77+....I77:::::77S777777777S7777777777\n";
		std::cout << "7777777777777777S7777+:::::777....777:::::777....777:::::7SS77777S77777777777777\n";
		std::cout << "777777777S77777S77777I:::::::777,.777:::::,~777..7 7::::::7777777SS777S777777777\n";
		std::cout << "7777777777777777SS7777,::::::777777~~~~~~~~~777777:::::::77777SSS77777SS77777777\n";
		std::cout << "777777S777S777777777:~~~~~~~~~~~~=~~~~~~~~~::::::::::::~~~I77777777777S777777777\n";
		std::cout << "77777777777S777777~~~~~~~~~~~~~I7777I?+++I777777::::::~~~~::,777SS77777777777777\n";
		std::cout << "7777777S777S77777~~~~~~~~~~~~~~=777777777777777+:::,~~~~~:::::777S777S7777777777\n";
		std::cout << "77777777S77SS777=:::::~::::::::::+77777777777?:::~~~~~~:::::::~7777SS77777777777\n";
		std::cout << "77777777SS777S77~:::::::::::::::::::I777777=:::~~~~~::::::::::~77SSS777777777777\n";
		std::cout << "77777777777S7777+:::::::::::::::::::::::::::::::::::::::::::::77S777777777777777\n";
		std::cout << "7777777777777SS77::::::::::::::::::::::::::::::::::::::::::::77SS777777777777777\n";
		std::cout << "777777777777777S77I:::::::::::+++::,::::::::::::::::::::::777S777777777777777777\n";
		std::cout << "77777777777777777777777777777777777777777777777777777777777777777777777777777777\n\n";
		std::cout << "                         Congratulations you did it!! \n";
	}
	else if (!FSGame.GetIsGameWon())
	{
		std::cout << "7777777777777777777777777777777S7777777777777777S777777777777S777777777777777777\n";
		std::cout << "77777777777777777S77777777S7777S77:::~77777777777777777S777777S77777777777777777\n";
		std::cout << "777777777777777777SS77777SS777S777?:::::I777777S7777777777777S777777777777777777\n";
		std::cout << "777777777777777777S77777SS77777S77::::::::?77777S777777S7777S7777777777777777777\n";
		std::cout << "777777777777777777S777777SS777777:::::::::::7777S77777SS77777S777777777777777777\n";
		std::cout << "77777777777777777S7777777S777777:::::::::::::+7S77777777S777SS777777777777777777\n";
		std::cout << "77777777777777777777777777S77777:::::~::::::::77777777S77777SS777777777777777777\n";
		std::cout << "777777777777S77777S77777777S7777=:~~=::::::::::77777777S777SS7777777777777777777\n";
		std::cout << "7777777777777S7777777S7777777:~~~~::::::::::::~ 777777S7777SS7777777777777777777\n";
		std::cout << "7777777777777S777777S7777777~~::::::::::::::::~~:I777777777S77777S77777777777777\n";
		std::cout << "77777777777777777777S777777:::::::::::::::::~~:::::~77S777SS77777777777777777777\n";
		std::cout << "777777777777777S77777S7777?::::::::::::::~~~~:::::::77777SS77777S777777777777777\n";
		std::cout << "777777777777777777777777777:::7777:,:~~~~~:::7777:::777777S777777S77777777777777\n";
		std::cout << "77777777777777S777777S77777:I7777777~~~::::I77777 ?:77777S77777S7777777777777777\n";
		std::cout << "7777777777777SS777777777I::~7 ....77+:::::I77....777~~~ 777S77777S7777S777777777\n";
		std::cout << "777777777777777S7777777::::777....  7:::::777....777~:::7777S77777S7777777777777\n";
		std::cout << "77777777777S7777777777:::::77+....777:::::77+....I77:::::77S777777777S7777777777\n";
		std::cout << "7777777777777777S7777+:::::777....777:::::777....777:::::7SS77777S77777777777777\n";
		std::cout << "777777777S77777S77777I::::::777,.777:::::,~777..7 7:::::::7777777SS777S777777777\n";
		std::cout << "7777777777777777SS7777,::::::777777~~~~~~~~~777777:::::::77777SSS77777SS77777777\n";
		std::cout << "777777S777S777777777:~~~~~~~~~~~~=~~~~~~~~~::::::::::::~~~I77777777777S777777777\n";
		std::cout << "77777777777S777777~~~~~~~~~~~~~~~~~~7?+++I7:::::::::::~~~~::,777SS77777777777777\n";
		std::cout << "7777777S777S77777~~~~~~~~~~~~~~=777777777777777+:::,~~~~~:::::777S777S7777777777\n";
		std::cout << "77777777S77SS777=:::::~::::::7777777777777777?777~~~~~~:::::::~7777SS77777777777\n";
		std::cout << "77777777SS777S77~::::::::::::77I7777I?+++I77777777~~::::::::::~77SSS777777777777\n";
		std::cout << "77777777777S7777+:::::::::::777::::::::::::::::::77:::::::::::77S777777777777777\n";
		std::cout << "7777777777777SS77::::::::::::::::::::::::::::::::::::::::::::77SS777777777777777\n";
		std::cout << "777777777777777S77I:::::::::::+++::,::::::::::::::::::::::777S777777777777777777\n";
		std::cout << "77777777777777777777777777777777777777777777777777777777777777777777777777777777\n\n";
		std::cout << "                    Darn..looks like you're out of guesses! \n";
	}
	return;
}

bool AskToPlayAgain()
{
	std::cout << "                       Do you want to play again? (y/n) ";
	FText Response = "";
	getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
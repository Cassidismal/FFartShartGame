#pragma once 

#include "FFartsAndShartsGame.h"
#include <map>
#include <stdio.h> // needed for "rand" access
#include <time.h> // needed for a less easily predictable RNG

// to make syntax Unreal friendly
#define TMap std::map
using int32 = int;


//Getters
int32 FFartsAndShartsGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FFartsAndShartsGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FFartsAndShartsGame::GetIsGameWon() const { return bGameIsWon; }

// Sets MaxTries based on length of hidden word
int32 FFartsAndShartsGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ { 3,4 },{ 4,7 },{ 5,10 },{ 6,16 },{ 7,20 } };//TIP: can use braced initializers as opposed to "="
	return (WordLengthToMaxTries[MyHiddenWord.length()]);
}
/*
WordLengthToMaxTries[]
[MyHiddenWord.length()]
*/
FFartsAndShartsGame::FFartsAndShartsGame() { Reset(); return; } // default constructor

void FFartsAndShartsGame::Reset()
{
	//Selects a Random Number 1-5 using an RNG and then a word associated with each possible number via state machine to be fed into "HIDDEN_WORD"
	//currently having issues getting the return from this function into "HIDDEN_WORD" PLEASE HELP, I know this could be done many other ways but am very interested in using an enumeration style 'state machine'
	SelectHiddenWord();


	FString HIDDEN_WORD[] = { FFartsAndShartsGame::SelectHiddenWord()};
	//TODO FIX HIDDEN WORD, get the SelectedHiddenWord to be compatible with the FString
	// HIDDEN_WORD = FIXME;

	MyHiddenWord = HIDDEN_WORD[1];
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

FString FFartsAndShartsGame::SelectHiddenWord()
{
	FString SelectedHiddenWord;
	ERNGStatus Status = ERNGStatus::Not_Selected;

	int32 RandomNumber = MakeRandomNumber();

	do
	{
		// These MUST all be isograms!
		Status = SetRNG_Status(RandomNumber);
		switch (Status)
		{
		case ERNGStatus::Not_Selected:
			SelectedHiddenWord = "";
			break;
		case ERNGStatus::Equals_One:
			SelectedHiddenWord = "tacos";
			break;
		case ERNGStatus::Equals_Two:
			SelectedHiddenWord = "lover";
			break;
		case ERNGStatus::Equals_Three:
			SelectedHiddenWord = "thong";
			break;
		case ERNGStatus::Equals_Four:
			SelectedHiddenWord = "dream";
			break;
		case ERNGStatus::Equals_Five:
			SelectedHiddenWord = "forks";
			break;
		case ERNGStatus::Error:
			SelectedHiddenWord = "error";
		default:

			break;
		}
	} while (Status = ERNGStatus::Not_Selected);

	return SelectedHiddenWord;
}

int32 FFartsAndShartsGame::MakeRandomNumber() const
{
	int32 RandomNumber;
	// the (unsigned int) is a "cast", a downcast  and potential data loss but fine just to seed the RNG. Must do it since srand wants an unsigned int(32-bit) and time() returns time_t(probably 64bit)
	// this makes it an 'explicit cast'..admittedly none of which means alot to me at my current understanding
	srand(static_cast<unsigned int>(time(NULL))); //seed RNG based on the computer's timeclock in seconds since midnight on January 1, 1970
	RandomNumber = 1 + (rand() % 5); //get a random value 1-5
	return RandomNumber;
}

ERNGStatus FFartsAndShartsGame::SetRNG_Status(int32 RandomNumber) const
{
	if (RandomNumber == 1)
	{
		return ERNGStatus::Equals_One;
	}
	else if (RandomNumber == 2)
	{
		return ERNGStatus::Equals_Two;
	}
	else if (RandomNumber == 3)
	{
		return ERNGStatus::Equals_Three;
	}
	else if (RandomNumber == 4)
	{
		return ERNGStatus::Equals_Four;
	}
	else if (RandomNumber == 5)
	{
		return ERNGStatus::Equals_Five;
	}
	else
	{
		return ERNGStatus::Error;
	}
}


int32 FFartsAndShartsGame::GetCurrentFarts() const
{
	return 0;
}

int32 FFartsAndShartsGame::GetCurrentSharts() const
{
	return 0;
}


int32 FFartsAndShartsGame::GetCurrentLevel() //TODO increment a Score or level based on sequential correct answers and print to screen
{
	return 0;
}

EGuessStatus FFartsAndShartsGame::CheckGuessValidity(FString Guess) const
{
	if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	else if (!IsAlphaChar(Guess))
	{
		return EGuessStatus::Not_Alpha;
	}
	else if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

// recieves a VALID guess, increments turn, and returns count
FFartShartCount FFartsAndShartsGame::SubmitValidGuess(FString Guess)
{

	MyCurrentTry++;
	FFartShartCount FartShartCount;


	// loop through all letters in the hidden word
	int32 WordLength = MyHiddenWord.length(); // assuming the same length as guess



	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar)
				{
					FartShartCount.Sharts++; // increment sharts if they're in the same place
				}
				else
				{
					FartShartCount.Farts++; // Must be a fart so increment farts		
				}
			}
		}
	}
	if (FartShartCount.Sharts == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return FartShartCount;
}



bool FFartsAndShartsGame::IsIsogram(FString Word) const
{
	// compare the guess char by char against a list of all 26 letters in the alphabet
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; // setup our map
	for (auto Letter : Word) // for all letters of the word --- Range based FOR loop / p.s. "auto" is automatically putting in "char" //  loop through all the letters of the word
	{
		Letter = tolower(Letter); // handle mixed case

		if (LetterSeen[Letter]) {// if the letter is in the map
			return false; // we do NOT have an isogram
		}

		else {
			LetterSeen[Letter] = true; // add it to the map as seen
		}

	}

	return true;
}

bool FFartsAndShartsGame::IsLowercase(FString Word) const
{
	if (Word.length() <= 1) { return true; }

	for (auto Letter : Word)
	{
		if (isupper(Letter))
		{
			return false;
		}
	}
	return true;
}

bool FFartsAndShartsGame::IsAlphaChar(FString Word) const
{
	if (Word.length() <= 1) { return true; }

	for (auto Letter : Word)
	{
		if (iscntrl(Letter))
		{
			return false;
		}
		else if (isdigit(Letter))
		{
			return false;
		}
		else if (ispunct(Letter))
		{
			return false;
		}
		else if (isspace(Letter))
		{
			return false;
		}
	}
	return true;
}
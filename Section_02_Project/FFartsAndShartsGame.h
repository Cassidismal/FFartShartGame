/*
The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind
*/

#pragma once
#include <string>

// to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FFartShartCount
{
	int32 Farts = 0;
	int32 Sharts = 0;
};

// enum state machine used to select the hidden word with status selected by RNG
enum ERNGStatus
{
	Not_Selected,
	Equals_One,
	Equals_Two,
	Equals_Three,
	Equals_Four,
	Equals_Five,
	Error
};

enum  class EGuessStatus
{
	Invalid_Status,
	OK,
	Wrong_Length,
	Not_Lowercase,
	Not_Isogram,
	Not_Alpha,
};

class FFartsAndShartsGame
{
public:
	FFartsAndShartsGame(); // constructor

	void Reset();

	int32 GetCurrentTry() const;
	int32 GetMaxTries() const;
	int32 GetCurrentFarts() const;
	int32 GetCurrentSharts() const;
	int32 GetHiddenWordLength() const;
	int32 MakeRandomNumber() const;
	int32 GetCurrentLevel(); // TODO count how many words/isograms have been answered successfully

	FString SelectHiddenWord();

	bool GetIsGameWon() const;

	ERNGStatus SetRNG_Status(int32) const;
	EGuessStatus CheckGuessValidity(FString) const;

	FFartShartCount SubmitValidGuess(FString);



	// Please try and ignore for now, focus on Public interface above ^^^
private:
	// see constructor for initialisation
	int32 MyCurrentTry;

	bool bGameIsWon;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	bool IsAlphaChar(FString) const;

	FString MyHiddenWord;
};


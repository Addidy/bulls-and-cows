#pragma once
#include <string>

using int32 = int;
using FString = std::string;

// All values initialized to zero
struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; // TODO make a more rich return value.

	void Reset(); // TODO make a more rich return value.
	FBullCowCount SubmitValidGuess(FString);

private:
	int32 MyCurrentTry = 1;
	int32 MyMaxTries = 5;
	FString MyHiddenWord;
	bool bGameIsWon = false;
	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};


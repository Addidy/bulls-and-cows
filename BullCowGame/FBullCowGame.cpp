#pragma once
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() {	Reset(); } // default constructor

int32 FBullCowGame::GetCurrentTry()		const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3, 4}, {4, 7}, {5, 10}, {6, 16}, {6, 16} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset() {
	//constexpr int32 MAX_TRIES = 5;
	const FString HIDDEN_WORD = "thing";

	
	MyHiddenWord = HIDDEN_WORD;
	MyMaxTries = GetHiddenWordLength();	//MAX_TRIES;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
	if (!IsIsogram(Guess)) {											// if the guess isn't an isogram 
		return EGuessStatus::Not_Isogram;
	} else if (!IsLowerCase(Guess)) {										// if the guess isn't all lowercase, 
		return EGuessStatus::Not_Lowercase;
	} else if (GetHiddenWordLength() != Guess.length()) {	// if the guess length is wrong
		return EGuessStatus::Wrong_Length;
	} else {
		return EGuessStatus::OK;
	}
}

bool FBullCowGame::IsIsogram(FString Word) const {
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter])
			return false;
		else {
			LetterSeen[Letter] = true;
		}
	}	
	return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const {
	for (auto Letter : Word) {
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}


// recieves a VALID guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {	// loop through all letters in the hidden word
		for (int32 GChar = 0; GChar < Guess.length(); GChar++) {// compare letters against the hidden word
			if (MyHiddenWord[MHWChar] == Guess[GChar]) {		// if they match then
				if (MHWChar == GChar) {							//if they're in the same place
					BullCowCount.Bulls++;
				} else {
					BullCowCount.Cows++;
				}
			}
		}
	}
	bGameIsWon = (BullCowCount.Bulls == WordLength); // This used to be an entire if else statement... I cannot permit that
	return BullCowCount;
}

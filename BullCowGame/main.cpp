/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all 
user interaction. For game logic see the FBullCowGame class.
*/
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintBack(FText guess);
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame = FBullCowGame();

//the entry point
int main() {
	do {
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());

	return 0; //exit the application
}

void PrintIntro() {
	std::cout << "Welcome to Bulls and Cows!" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?" << std::endl;
	return;
}

void PlayGame() {
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game is NOT won
	// is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries){
		FText Guess = GetValidGuess();

		//submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		// print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls << ". Cows = " << BullCowCount.Cows << std::endl << std::endl;

		//PrintBack(Guess);
	}
	PrintGameSummary();
}

//loop continually until the user gives a valid guess
FText GetValidGuess() {
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do {
		//get a guess from the player
		std::cout << "Try " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries();
		std::cout << "Enter your guess?: ";
		std::getline(std::cin, Guess);

		EGuessStatus Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter your word all lowercase.\n\n";
			break;
		default:
			//assume guess is valid
			return Guess;
			break;
		}
	} while (Status != EGuessStatus::OK);
	return Guess;
}

void PrintBack(FText guess) {
	//repeat the guess back to them
	std::cout << "Your guess was: " << guess << std::endl << std::endl;
	return;
}

bool AskToPlayAgain(){
	std::cout << "Do you want to play again? ";
	FText response = "";
	std::getline(std::cin, response);
	return (response[0] == 'y' || response[0] == 'Y');
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "Congratulations! you Win!" << std::endl;
	} else {
		std::cout << "You Lose! Better luck next time!" << std::endl;
	}
}
// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    level = 0;

    PrintLine(TEXT("Welcome To Bull Cow Game!"));
    PrintLine(TEXT("Choose your Difficulty: "));
    PrintLine(TEXT("1. Easy\n2. Hard"));
    PrintLine(TEXT("Type 'easy' for an easy game mode or 'hard' for a challengeing game mode: "));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (level == 0)
    {
        SetDifficulty(Input);
        SetupGame(); // Setting up the game
    }
    else
    {
        if (bGameOver)
        {
            ClearScreen();
            SetupGame();
        }
        else
        {   
            ProcessGuess(Input);
        }
    }
    
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = Isograms[FMath::RandRange (0, Isograms.Num() - 1)];  
    lives = HiddenWord.Len();
    bGameOver = false;

    // Welcoming the player
    PrintLine(TEXT("Welcome To Bull Cow!"));
    PrintLine(TEXT("Guess the %d letter word!"), HiddenWord.Len());  //Magic Number Remove!
    PrintLine(TEXT("You have %d Lives"), lives);
    PrintLine(TEXT("Press Enter to to begin..."));
    // PrintLine(TEXT("The HiddenWord is %s"), *HiddenWord); //Debug Line
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    level++;
    PrintLine(TEXT("\nPress Enter to play again....."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if(Guess == HiddenWord)
    {
        PrintLine(TEXT("You Win!!"));
        EndGame();
        return;
    }

    if (HiddenWord.Len() != Guess.Len())
    {
        PrintLine(TEXT("\nSorry, try guessing again!"));
        PrintLine(TEXT("You have %i lives remaning"), lives);
        PrintLine(TEXT("\nThe Hidden word is %i letter long."), HiddenWord.Len());
        return;
    }

    if (!IsIsogram(Guess))
    {  
        PrintLine(TEXT("No repeating letters, guess again!"));
        return;
    }

    --lives;
    PrintLine(TEXT("You lost a life!"));
    PrintLine(TEXT("\nYou have %i lives remaning"), lives);
            
    if (lives <= 0)
    {        
        ClearScreen();
        PrintLine(TEXT("Sorry, You have no lives left!"));
        PrintLine(TEXT("\nThe Hidden word was: %s"), *HiddenWord);
        EndGame();
        return;
    }    

    // Show the player Bulls N Cows
    FBullCowCount Score = GetBullCows(Guess);
    PrintLine(TEXT("You Have %d Bulls & %d Cows."), Score.Bulls, Score.Cows);
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    int32 i, j,  len = Word.Len();
    
    for (i = 0; i < len-1; i++)
    {
        for(j = i+1; j < len; j++)
        {
            if (Word[i] == Word[j])
            {
                return false;
            }
        }
    }
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;

    for (FString Word : WordList)
    {
        if(bDifficulty)
        {
            if (Word.Len() >= 4 && Word.Len() <= 6 && IsIsogram(Word))
            {
                ValidWords.Emplace(Word);
            }
        }
        else
        {
            if (Word.Len() >= 7 && Word.Len() <= 9 && IsIsogram(Word))
            {
                ValidWords.Emplace(Word);
            }
        }
        
    }
    return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FBullCowCount Count;

    for (int32 i = 0; i < Guess.Len(); i++)
    {
        if (Guess[i] == HiddenWord[i])
        {
            Count.Bulls++;
            continue;
        }

        for (int32 j = 0; j < HiddenWord.Len(); j++)
        {
            if (Guess[i] == HiddenWord[j])
            {
                Count.Cows++;
                break;
            }
        }
    }
    return Count;
}

void UBullCowCartridge::SetDifficulty(const FString& Difficult)
{
    bGameOver = false;
    if (Difficult == "easy")
    {
        bDifficulty = true;
    }
    else
    {
        bDifficulty = false;
    }
    Isograms = GetValidWords(Words);
    ClearScreen();
    level = 1;
}
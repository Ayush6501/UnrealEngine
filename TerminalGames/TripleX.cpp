#include <iostream>
#include <ctime>

// Function to print the introduction
void PrintIntro(int Difficulty)
{
    std::cout << "\n\nYou are a DedSec secret agent breaking into a very secure level: " << Difficulty; 
    std::cout << " server room.\nEnter the correct code to proceed...\n";
}

// Function which plays the game and generates random number
bool PlayGame(int Difficulty)
{
    PrintIntro(Difficulty);

    const int CodeA = (rand() % (Difficulty + 1)) + Difficulty; 
    const int CodeB = (rand() % (Difficulty + 1)) + Difficulty; 
    const int CodeC = (rand() % (Difficulty + 1)) + Difficulty; 
    const int CodeSum = CodeA + CodeB + CodeC;
    const int CodeProduct = CodeA * CodeB * CodeC;

    std::cout << std::endl;
    std::cout << "\nThere are 3 numbers in the code." << std::endl;
    std::cout << "The codes add up to give: " << CodeSum << std::endl;
    std::cout << "The codes when multiplied give: " << CodeProduct << std::endl << std::endl;

    int GuessA, GuessB, GuessC;
    std::cin >> GuessA >> GuessB >> GuessC;
    std::cout << "You Entered: " << GuessA << GuessB << GuessC << std::endl;

    int GuessSum = GuessA + GuessB + GuessC;
    int GuessProduct = GuessA * GuessB * GuessC;

    if (GuessSum == CodeSum && GuessProduct == CodeProduct)
    {
        std::cout << "\n**** Well done Agent!";
        std::cout <<  " You can now proceed to the next level ****";
        return true;
    }
    else
    {
        std::cout << "\n**** Hack Failed! ";
        std::cout << "You have been caught!";
        std::cout << " TRY AGAIN! ****";
        return false;
    }
}

int main()
{
    srand(time(NULL));  //to truly randomize the code based on the device's time
    
    const int MaxDifficulty = 7;
    int LevelDifficulty = 1;
    while (LevelDifficulty <= MaxDifficulty) //loops throughout the game-run
    {
        bool bCompletion;
        bCompletion = PlayGame(LevelDifficulty);
        std::cin.clear();
        std::cin.ignore();

        if (bCompletion)
        {
            LevelDifficulty++;
        }    
    }
    std::cout << "**** Great Work Agent! You Win! Off to the next mission! ****";
    return 0;
}

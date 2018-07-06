#include <iostream>
#include <cstdlib>
using namespace std;

char guess;
string wrongs;
string corrects;
string word;
char diagram[11][15];

string words[113] = {"ACRES", "ADULT", "ADVICE", "ARRANGEMENT", "ATTEMPT", "AUTUMN",
    "BORDER", "BREEZE", "BRICK", "CALM", "CANAL", "CAST", "CHOSE", "CLAWS", "COACH",
    "CONSTANTLY", "CONTRAST", "COOKIES", "CUSTOMS", "DAMAGE", "DEEPLY", "DEPTH", "DISCUSSION",
    "DOLL", "DONKEY", "ESSENTIAL", "EXCHANGE", "EXIST", "EXPLANATION", "FACING", "FILM",
    "FINEST", "FIREPLACE", "FLOATING", "FOLKS", "FORT", "GARAGE", "GRABBED", "GRANDMOTHER",
    "HABIT", "HAPPILY", "HEADING", "HUNTER", "IMAGE", "INDEPENDENT", "INSTANT", "KIDS",
    "LABEL", "LUNGS", "MANUFACTURING", "MATHEMATICS", "MELTED", "MEMORY", "MILL", "MISSION",
    "MONKEY", "MOUNT", "MYSTERIOUS", "NEIGHBORHOOD", "NUTS", "OCCASIONALLY", "OFFICIAL",
    "OURSELVES", "PALACE", "PLATES", "POETRY", "POLICEMAN", "POSITIVE", "POSSIBLY", "PRACTICAL",
    "PRIDE", "PROMISED", "RECALL", "RELATIONSHIP", "REMARKABLE", "REQUIRE", "RHYME", "ROCKY",
    "RUBBED", "RUSH", "SALE", "SATELLITES", "SATISFIED", "SCARED", "SELECTION", "SHAKE",
    "SHAKING", "SHALLOW", "SHOUT", "SILLY", "SIMPLEST", "SLIGHT", "SLIP", "SLOPE", "SOAP",
    "SOLAR", "SPECIES", "SPIN", "STIFF", "SWUNG", "TALES", "THUMB", "TOBACCO", "TOY",
    "TRAP", "TREATED", "TUNE", "UNIVERSITY", "VAPOR", "VESSELS", "WEALTH", "WOLF", "ZOO"};

void newGame()
{
    system("clear");
    guess = ' ';
    wrongs = "";
    corrects = "";

    // randomly choose a word
    srand(time(NULL));
    int index = rand() % (sizeof(words) / sizeof(words[0]) + 1);
    word = words[index];

    // put the empty game board into the array
    for (int i = 0; i < 11; i++) {
        for (int k = 0; k < 15; k++) {

            if ((i == 0 && k > 0 && k < 9) || (i == 8 && k > 2)) {
                diagram[i][k] = '_';
            }
            else if ((i > 0 && i < 9 && k == 1) || (i == 1 && k == 8)) {
                diagram[i][k] = '|';
            }
            else if ((i == 1 && k == 2)) {
                diagram[i][k] = '/';
            }
            else if (i == 8 && k == 2) {
                diagram[i][k] = '\\';
            }
            else if (i == 10 && k < word.size()) {
                diagram[i][k] = '-';
            }
            else {
                diagram[i][k] = ' ';
            }
        }
    }
}

void drawBoard()
{
    // enter the hangman
    if (wrongs.size() >= 1)
        diagram[2][8] = 'O';
        if (wrongs.size() >= 2)
            diagram[3][8] = '|';
            if (wrongs.size() >= 3)
                diagram[2][7] = '_';
                if (wrongs.size() >= 4)
                    diagram[3][6] = '/';
                    if (wrongs.size() >= 5)
                        diagram[2][9] = '_';
                        if (wrongs.size() >= 6)
                            diagram[3][10] = '\\';
                            if (wrongs.size() >= 7)
                                diagram[4][7] = '/';
                                if (wrongs.size() >= 8)
                                    diagram[5][6] = '/';
                                    if (wrongs.size() >= 9)
                                        diagram[4][9] = '\\';
                                        if (wrongs.size() >= 10)
                                            diagram[5][10] = '\\';
                                            // you lose

    // draw everything
    for (int i = 0; i < 11; i++) {
        for (int k = 0; k < 15; k++) {
            cout << diagram[i][k];
        }
        cout << endl;
    }
}

void checkAnswer()
{
    char answer;
    // check if the player has run out of guesses
    while (wrongs.size() >= 10) {
        cout << "\nThe word was: " + word << endl;
        cout << "\nYou're dead. Would you like to play again? (Y/N) ";
        cin >> answer;
        if (answer == 'Y' || answer == 'y') {
            newGame();
            drawBoard();
        }
        else if (answer == 'N' || answer == 'n') {
            cout << "\nGoodbye!\n";
            exit(0);
        }
        else {
            system("clear");
            drawBoard();
        }
    }

    // check if the player has completed the word
    while (corrects.size() == word.size()) {
        cout << "\nYou win! Would you like to play again? (Y/N) ";
        cin >> answer;
        if (answer == 'Y' || answer == 'y') {
            newGame();
            drawBoard();
        }
        else if (answer == 'N' || answer == 'n') {
            cout << "\nGoodbye!\n";
            exit(0);
        }
        else {
            system("clear");
            drawBoard();
        }
    }
}

bool guessLetter()
{
    drawBoard();
    checkAnswer();
    cout << "\nIncorrect guesses:" << endl;
    cout << wrongs << endl;

    string guessStr;
    cout << "\nGuess a letter: ";
    cin >> guessStr;

    if (guessStr.size() == 1) {
        guess = (char)guessStr[0];
        if (islower(guess)) {
            guess = toupper(guess);
        }
    }
    else {
        system("clear");
        return false;
    }

    if (!isalpha(guess)) {
        system("clear");
        return false;
    }

    // disallow the player from guessing a letter more than once
    if (wrongs.find(guess) != string::npos || corrects.find(guess) != string::npos) {
        system("clear");
        return false;
    }

    // check if the guess is wrong or correct
    bool correct = false;
    for (int i = 0; i < word.size(); i++) {
        if (word[i] == guess) {
            diagram[10][i] = guess;
            corrects += guess;
            correct = true;
        }
    }
    if (!correct) {
        wrongs += guess;
    }

    system("clear");
    return true;
}

int main(int argc, char * argv[])
{
    newGame();

    while (true) {
        guessLetter();
    }

	return 0;
}

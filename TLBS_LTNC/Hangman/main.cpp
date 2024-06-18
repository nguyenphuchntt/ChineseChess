#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>

#define START 0
#define GOOD_GUESS 1
#define BAD_GUESS 2
#define MAX_BAD_GUESSES 7

const std::string WORD_LIST[] = {
        "angle", "ant", "apple", "arm", "army",
        "baby", "bag", "ball", "band", "basin", "basket", "bath", "bed", "bee", "bell", "berry",
        "bird", "blade", "board", "boat", "bone", "book", "boot", "bottle", "box", "boy",
        "brain", "brake", "branch", "brick", "bridge", "brush", "bucket", "bulb", "button",
        "cake", "camera", "card",  "cart", "carriage", "cat", "chain", "cheese", "chest",
        "chin", "church", "circle", "clock", "cloud", "coat", "collar", "comb", "cord",
        "cow", "cup", "curtain", "cushion",
        "dog", "door", "drain", "drawer", "dress", "drop", "ear", "egg", "engine", "eye",
        "face", "farm", "feather", "finger", "fish", "flag", "floor", "fly",
        "foot", "fork", "fowl", "frame", "garden", "girl", "glove", "goat", "gun",
        "hair", "hammer", "hand", "hat", "head", "heart", "hook", "horn", "horse",
        "hospital", "house", "island", "jewel",  "kettle", "key", "knee", "knife", "knot",
        "leaf", "leg", "library", "line", "lip", "lock",
        "map", "match", "monkey", "moon", "mouth", "muscle",
        "nail", "neck", "needle", "nerve", "net", "nose", "nut",
        "office", "orange", "oven", "parcel", "pen", "pencil", "picture", "pig", "pin",
        "pipe", "plane", "plate", "plow", "pocket", "pot", "potato", "prison", "pump",
        "rail", "rat", "receipt", "ring", "rod", "roof", "root",
        "sail", "school", "scissors", "screw", "seed", "sheep", "shelf", "ship", "shirt",
        "shoe", "skin", "skirt", "snake", "sock", "spade", "sponge", "spoon", "spring",
        "square", "stamp", "star", "station", "stem", "stick", "stocking", "stomach",
        "store", "street", "sun", "table", "tail", "thread", "throat", "thumb", "ticket",
        "toe", "tongue", "tooth", "town", "train", "tray", "tree", "trousers", "umbrella",
        "wall", "watch", "wheel", "whip", "whistle", "window", "wire", "wing", "worm",
    };
const int WORD_COUNT = sizeof(WORD_LIST) / sizeof(std::string);

const std::string chooseWord(){
    int randomIndex = rand() % WORD_COUNT;
    return WORD_LIST[randomIndex];
}

struct HangMan {
    std::string secretWord;
    std::string guessedWord;

    int badGuesses;
    int hiddenLetters;
    int status = START;

    HangMan(){
    }

    void init(const std::string& secret){
        secretWord = secret;
        guessedWord = std::string(secretWord.length(), '_');
        hiddenLetters = secretWord.length();
        badGuesses = 0;
    }

    void update(char input){
        status = BAD_GUESS;
        for (int i = 0; i < secretWord.length(); i++){
            if (guessedWord[i] == '_' && secretWord[i] == input){
                guessedWord[i] = input;
                status = GOOD_GUESS;
                hiddenLetters--;
            }
        }
        if (status == BAD_GUESS){
            badGuesses++;
        }
    }

    bool isOver() const {
        return (isWon() || isLost());
    }
    bool isWon() const {
        return hiddenLetters == 0;
    }
    bool isLost() const {
        return badGuesses >= MAX_BAD_GUESSES;
    }
    

};


char getInput(){
    char s;
    std::cout << "Make a guess: ";
    std::cin >> s;
    return s;
}
void renderGame(const HangMan& game){
    if (game.status == GOOD_GUESS){
        std::cout << "GOOD JOB!" << std::endl;
    }else if (game.status == BAD_GUESS){
        std::cout << "Oh! Incorrect!" << std::endl;
    }

    std::cout << "Bad guessed: " << game.badGuesses << std::endl;
    std::cout << "Guessed word: " << game.guessedWord << std::endl;
    
    if (game.isOver()){
        std::cout << std::endl;
        if (game.isWon()){
            std::cout << "You've won this game!";
        }else if (game.isLost()){
            std::cout << "You've lost this game!";
        }
        std::cout << std::endl;
        std::cout << "The secret word is: " << game.secretWord;
    }

}



int main(int arg, char* argv[]){
    srand(time(0));

    HangMan game;
    game.init(chooseWord());
    renderGame(game);

    do {
        char input = getInput();
        game.update(input);
        renderGame(game);

    } while (!game.isOver());

    return 0;
}
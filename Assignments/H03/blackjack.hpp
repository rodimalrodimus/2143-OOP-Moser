#include <algorithm> // std::random_shuffle
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;

const string spade = "♠";
const string diamond = "♦";
const string heart = "♥";
const string club = "♣";

const string suits[4] = {"♠", "♥", "♦", "♣"};

string Black = "0";
string Red = "1";
string Green = "2";
string Yellow = "3";
string Blue = "4";
string Purple = "5";
string Cyan = "6";
string White = "7";
string Default = "9";

void printColor(string out, int fg, int bg=9 ){
    cout<<"\033[0;3"<<fg<<";4"<<bg<<"m"<<out<<"\033[0;39;49m";
}

void gotoXY(int row,int col){
    cout<<"\033["<<row<<";"<<col<<"H";
}

struct winsize w;
struct WindowSize{
    int rows;
    int cols;

    /**
     * Uses some built in libraries to get a terminal window size.
     *      stdio.h, sys/ioctl.h, unistd.h 
     */
    WindowSize(){
        // magic happens here
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

        // place values in more readable 
        // vars here ...
        rows = w.ws_row;
        cols = w.ws_col;
    }
    
    /**
     * Guess
     */
    int termWidth(){
        return cols;
    }

    /**
     * Guess
     */
    int termHeight(){
        return rows;
    }

    /**
     * Random int between 0 and width of terminal window
     */
    int randCol(){
        return rand() % cols;
    }

    /**
     * Random int between 0 and height of terminal window
     */
    int randRow(){
        return rand() % rows;
    }
};
// Card labels (could be "Iron Man" or "Charmander" or "Elf" ... anything)
const string ranks[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

/*
   ____    _    ____  ____
  / ___|  / \  |  _ \|  _ \
 | |     / _ \ | |_) | | | |
 | |___ / ___ \|  _ <| |_| |
  \____/_/   \_\_| \_\____/
*/

class CardContainer;
class Hand;

class Card {
protected:
    int suitNum;     // value 0-3 : num index of suit
    int rank;        // 0-13      : num value of rank
    int number;      // 1-52      : unique value determines card
    int value;       // 1-14      : numeric value used for comparison
    string suitChar; // "♠", "♦", "♣", "♥"
    string rankChar; // Ace, 1 ,2 ,3 ... Q, K
    string fcolor;    // Spade=blue, Diamond=red, etc.
    string bcolor;

public:

    friend class Hand;

    Card(int);
    string Repr();
    bool operator<(const Card &);
    bool operator>(const Card &);
    bool operator==(const Card &);
    bool operator!=(const Card &);
    bool operator()(const Card &);
    friend ostream& operator<<(ostream& os, const Card& card);
    friend class CardContainer;
    int getRank(){return rank;}
    string getRankChar(){return rankChar;}
    string getSuitChar(){return suitChar;}
    string getfColor(){return fcolor;}
    string getbColor(){return bcolor;}
};



/**
 * Public : operator <<
 *
 * Description:
 *      Overload ostream and send the string representation "Repr"
 *      of the card.
 *
 *      We don't need the scope resolution operator (Card::) since
 *      this is a "friend" of card.
 *
 * Params:
 *      [ostream&] : os
 *      [Card]     : obj
 *
 * Returns:
 *      [ostream&]
 */
ostream& operator <<(ostream& os,const Card& card){
    os<<"\033[0;3"<<card.fcolor<<";4"<<card.bcolor<<"m";
    os << "┌────┐\n";
    os<< "│";
    if (card.rank != 9) {
        os<< " ";
    }
    os<< card.rankChar << " " << card.suitChar << "│\n";
    os<< "└────┘";
    os<<"\033[0;39;49m";
    
    return os;
}

/**
     * Public : Card
     *
     * Description:
     *      Represents a single card in a deck of cards to include a
     *      value along with rank and suit. We are assuming a standard
     *      card type in a deck of playing cards.
     *
     * Params:
     *      int :  value from 0 - 51 that represents a card in a deck.
     *
     * Returns:
     *      None
     */
Card::Card(int num) {
    number = num;
    suitNum = number / 13;
    suitChar = suits[suitNum];
    fcolor = to_string(1+ rand() % 7);
    bcolor = "9";
    rank = number % 13;
    rankChar = ranks[rank];
}


bool Card::operator<(const Card &rhs) {
    return this->rank < rhs.rank;
}

bool Card::operator>(const Card &rhs) {
  cout << this->rank << ">" << rhs.rank << endl;
    return this->rank > rhs.rank;
}

bool Card::operator==(const Card &rhs) {
    return this->rank == rhs.rank;
}

bool Card::operator!=(const Card &rhs) {
    return this->rank != rhs.rank;
}

bool Card::operator()(const Card &rhs) {
    return (this->rank < rhs.rank);
}



/*
   ____    _    ____  ____   ____ ___  _   _ _____  _    ___ _   _ _____ ____
  / ___|  / \  |  _ \|  _ \ / ___/ _ \| \ | |_   _|/ \  |_ _| \ | | ____|  _ \
 | |     / _ \ | |_) | | | | |  | | | |  \| | | | / _ \  | ||  \| |  _| | |_) |
 | |___ / ___ \|  _ <| |_| | |__| |_| | |\  | | |/ ___ \ | || |\  | |___|  _ <
  \____/_/   \_\_| \_\____/ \____\___/|_| \_| |_/_/   \_\___|_| \_|_____|_| \_\
*/

class CardContainer {
protected:
    vector<Card *> Cards;
    int RandomIndex();
    struct CardCompare {
        bool operator()(Card *l, Card *r) {
            return *l < *r;
        }
    };
    int rows;
    int cols;

public:
    CardContainer();
    CardContainer(int);
    void Add(Card *);
    bool isEmpty();
    void Order();
    Card *Remove();
    void Reset();
    void Shuffle();
    int Size();
    friend ostream& operator<<(ostream& os, const CardContainer& cards);
};

ostream& operator <<(ostream& os,const CardContainer& c){
    for(int i=0;i<c.Cards.size();i++){
        os<<"\033[0;3"<<c.Cards[i]->getfColor()<<";4"<<c.Cards[i]->getbColor()<<"m";
        os << "┌────┐";
        os<<"\033[0;39;49m";
    }
    os << endl;
    for(int i=0;i<c.Cards.size();i++){
        os<<"\033[0;3"<<c.Cards[i]->getfColor()<<";4"<<c.Cards[i]->getbColor()<<"m";
        os<< "│";
        if (c.Cards[i]->getRank() != 9) {
            os<< " ";
        }
        os<< c.Cards[i]->getRankChar() << " " << c.Cards[i]->getSuitChar() << "│";
        os<<"\033[0;39;49m";
    }
    os << endl;
    for(int i=0;i<c.Cards.size();i++){
        os<<"\033[0;3"<<c.Cards[i]->getfColor()<<";4"<<c.Cards[i]->getbColor()<<"m";
        os<< "└────┘";
        os<<"\033[0;39;49m";
    }   
    os << endl;
    
    return os;
}

CardContainer::CardContainer() {
    cout<<"in cardcontainer constructor"<<endl;
    rows = 1;
    cols = 4;
}

CardContainer::CardContainer(int numCards) {
    cout<<"in cardcontainer overloaded constructor"<<endl;
    rows = 1;
    cols = 4;
    for (int i = 0; i < numCards; i++) {
        Cards.push_back(new Card(i));
    }
}

void CardContainer::Add(Card *card) {
    // check if card already in container?
    // allow go over 52 ??

    Cards.push_back(card);
    //currentCount = Cards.size();
}

bool CardContainer::isEmpty() {
    return Cards.empty();
}

void CardContainer::Order() {
    sort(Cards.begin(), Cards.end(), CardCompare());
}

Card *CardContainer::Remove() {
    Card *temp = Cards.back();
    Cards.pop_back();
    return temp;
}

void CardContainer::Reset() {
    for (int i = 0; i < Cards.size() - 1; i++) {
        delete Cards[i];
        Cards[i] = new Card(i);
    }
}

void CardContainer::Shuffle() {
    for (int i = 0; i < Cards.size() - 1; i++) {
        int j = i + rand() % (Cards.size() - i);
        swap(Cards[i], Cards[j]);
    }
}

int CardContainer::Size() {
    return Cards.size();
}

/*
  ____  _____ ____ _  __
 |  _ \| ____/ ___| |/ /
 | | | |  _|| |   | ' /
 | |_| | |__| |___| . \
 |____/|_____\____|_|\_\
*/

class Deck : public CardContainer {
protected:
    int deckSize;

public:
    Deck();
    Deck(int);
    Card *Draw();
};

Deck::Deck() : CardContainer(52) {
    deckSize = 52;
}

Deck::Deck(int size) : CardContainer(size) {
    deckSize = size;
}

Card *Deck::Draw() {
    Card *temp = Cards.back();
    Cards.pop_back();
    return temp;
}


/*
  _   _    _    _   _ ____
 | | | |  / \  | \ | |  _ \
 | |_| | / _ \ |  \| | | | |
 |  _  |/ ___ \| |\  | |_| |
 |_| |_/_/   \_\_| \_|____/
*/
class Hand : public CardContainer {
protected:
public:
    Hand();
    void Print();
    int Size(){
        return Cards.size();
    }
    void Sort();
};

Hand::Hand(){

}

//recreated Sort
void Hand::Sort(){
for(int i=0;i<Size()-1;i++){
  bool repeat = false;                    //run again?
    if (Cards[i]->rank>Cards[i+1]->rank){ //comparison
      Card* temp = Cards[i];              //swap
      Cards[i] = Cards[i+1];
      Cards[i+1] = temp;
      repeat = true;                      //makes it run again
  }
  if (repeat){
    Sort();                               //calls sort again if needed
  }}}

void Hand::Print() {
    return;
}

class Player {
protected:
    string name;
    Hand* hand;
    double bank;
    double bet;
public:
    Player(){
        hand = new Hand();
    }
    double getBet(){
        return bet;
    }
};

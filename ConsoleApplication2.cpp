#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

// Card structure
struct Card {
    string suit;
    string rank;
    int value;
};

// Function to create a deck of cards
vector<Card> createDeck() {
    vector<Card> deck;
    string suits[] = { "Spades", "Hearts", "Diamonds", "Clubs" };
    string ranks[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };

    for (const auto& suit : suits) {
        for (const auto& rank : ranks) {
            int value = atoi(rank.c_str());
            if (rank == "Jack" || rank == "Queen" || rank == "King") {
                value = 10;
            }
            else if (rank == "Ace") {
                value = 11;
            }
            deck.push_back({ suit, rank, value });
        }
    }

    return deck;
}

// Function to shuffle the deck of cards
void shuffleDeck(vector<Card>& deck) {
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < deck.size(); ++i) {
        int j = rand() % deck.size();
        swap(deck[i], deck[j]);
    }
}

// Function to calculate the total value of a hand
int calculateHandValue(const vector<Card>& hand) {
    int totalValue = 0;
    int numAces = 0;

    for (const auto& card : hand) {
        totalValue += card.value;
        if (card.rank == "Ace") {
            numAces++;
        }
    }

    while (totalValue > 21 && numAces > 0) {
        totalValue -= 10;
        numAces--;
    }

    return totalValue;
}

// Function to display a player's hand
void displayHand(const vector<Card>& hand) {
    for (const auto& card : hand) {
        cout << card.rank << " of " << card.suit << endl;
    }
    cout << "Total value: " << calculateHandValue(hand) << "\n\n";
}

int main() {
    vector<Card> deck = createDeck();
    shuffleDeck(deck);

    vector<Card> playerHand;
    vector<Card> dealerHand;

    // Initial deal
    playerHand.push_back(deck.back());
    deck.pop_back();
    dealerHand.push_back(deck.back());
    deck.pop_back();
    playerHand.push_back(deck.back());
    deck.pop_back();
    dealerHand.push_back(deck.back());
    deck.pop_back();

    // Player's turn
    cout << "Player's Hand:" << endl;
    displayHand(playerHand);

    while (calculateHandValue(playerHand) < 21) {
        cout << "Do you want to hit (h) or stand (s)? ";
        char choice;
        cin >> choice;

        if (choice == 'h') {
            playerHand.push_back(deck.back());
            deck.pop_back();
            cout << "Player's Hand:" << endl;
            displayHand(playerHand);
        }
        else if (choice == 's') {
            break;
        }
    }

    // Dealer's turn
    cout << "Dealer's Hand:" << endl;
    displayHand(dealerHand);

    while (calculateHandValue(dealerHand) < 17) {
        dealerHand.push_back(deck.back());
        deck.pop_back();
        cout << "Dealer's Hand:" << endl;
        displayHand(dealerHand);
    }
    // Determine the winner
    int playerValue = calculateHandValue(playerHand);
    int dealerValue = calculateHandValue(dealerHand);

    cout << "Player's Hand:" << endl;
    displayHand(playerHand);
    cout << "Dealer's Hand:" << endl;
    displayHand(dealerHand);

    cout << "===============" << endl;
    if (playerValue > 21) {
        cout << "Player busts. Dealer wins!" << endl;
    }
    else if (dealerValue > 21) {
        cout << "Dealer busts. Player wins!" << endl;
    }
    else if (playerValue == dealerValue) {
        cout << "It's a tie!" << endl;
    }
    else if (playerValue > dealerValue) {
        cout << "Player wins!" << endl;
    }
    else {
        cout << "Dealer wins!" << endl;
    }
    cout << "===============" << endl;

    return 0;
}

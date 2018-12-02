#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "deck.h"
#include "card.h"
#include <time.h>

int shuffle()
{
	char suitArray[4] = {'S', 'H', 'C', 'D'};
	char rankArray[13] = {'2', '3', '4', '5', '6', '7', '8', '9', '0', 'J', 'Q', 'K', 'A'};
    // Used "0" to represent a rank of 10
	// Populating array of cards

	for (int i = 0; i < 52; i++){
		deck_instance.list[i].suit = suitArray[i%4];
		deck_instance.list[i].rank = rankArray[i%13];
   		//printf("%c%c\n", deck_instance.list[i].rank, deck_instance.list[i].suit);
 	}
	deck_instance.top_card = 0;
 	srand(time(NULL));
	struct card temp;

    // Shuffling array of cards
	for (int i = 0; i < 52; i++){
	    int random = (rand() % 52);
	   	temp = deck_instance.list[random];
   		deck_instance.list[random] = deck_instance.list[i];
   		deck_instance.list[i] = temp;
	}
}

/*
 * Function: deal_player_cards
 * ---------------------------
 *  Deal 7 random cards to the player specified in the function.
 *  Remove the dealt cards from the deck. 
 *
 *  target: pointer to the player to be dealt cards
 *
 *  returns: 0 if no error, and non-zero on error
 */
int deal_player_cards(struct player* target)
{
	srand(time(NULL));
    // Set random card from deck_instance list = first hand card "top"
	//int random = (rand() % 51);
	target->card_list.top = deck_instance.list[deck_instance.top_card];
	target->card_list.next = NULL;
	deck_instance.top_card++;
	
	// set current hand = the current card list that contains top and pointer to next hand
	struct hand *current = (&target->card_list);
	//top_card = 0;
	for (int i = 0 ; i < 6; i++){
		struct hand* nextHand = (struct hand *) malloc(sizeof(struct hand));	// malloc for nextHand pointer
		nextHand->next = NULL;
		nextHand->top = deck_instance.list[deck_instance.top_card];						// Assignment of random card from deck to next hand's top
		current->next = nextHand;
		current = (current->next);
		deck_instance.top_card++;
    }
	target->hand_size = (size_t) 7;
}

/*
 * Function: next_card
 * -------------------
 *  Return a pointer to the top card on the deck.
 *  Removes that card from the deck. 
 *
 *  returns: pointer to the top card on the deck.
 */
struct card* next_card()
{
	if(deck_instance.top_card == 52){
		struct card* noCard = (struct card*) malloc(sizeof(struct card));
		return noCard;
	}
	deck_instance.top_card++;
	return &deck_instance.list[deck_instance.top_card-1];
}

/*
 * Function: size
 * --------------
 *  Return the number of cards left in the current deck.
 *
 *  returns: number of cards left in the deck.
 */
size_t deck_size( ){
	return (sizeof(deck_instance.list) - sizeof(struct card) * deck_instance.top_card) / 
	(sizeof(struct card));
}

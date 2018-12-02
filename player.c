#include <stdlib.h>
#include "player.h"
#include "deck.h"
/* int main(){
	struct player* play = (struct player*) malloc(sizeof(struct player));
	struct player* play2 = (struct player*) malloc(sizeof(struct player));
	shuffle();
	deal_player_cards(play);
	deal_player_cards(play2);
	struct card* toAdd1 = &deck_instance.list[deck_instance.top_card];
	printf("card to add: %c%c", toAdd1->rank, toAdd1->suit);
	add_card(play, toAdd1);

	struct hand* current = (&play->card_list);

	while (current != NULL){
		printf("whole hand: %c%c\n", current->top.rank, current->top.suit);
		current = current->next;
	}
	
	struct hand* toRemoveHand = (&play->card_list);
	toRemoveHand = toRemoveHand->next;
	toRemoveHand = toRemoveHand->next;
    //struct card* toRemove = &toRemoveHand->top;
	//remove_card(play, toRemove);
	
	//printf("Card to remove: %c%c\n", toRemove->rank, toRemove->suit);
	//remove_card(play, toRemove);
    struct hand* current1 = (&play->card_list);
	struct card* rank1 = (struct card*)malloc(sizeof(struct card));
    rank1->rank = '2';
    rank1->suit = 'S';
    struct card* rank2 = (struct card*)malloc(sizeof(struct card));
    rank2->rank = '2';
    rank2->suit = 'H';
    struct card* rank3 = (struct card*)malloc(sizeof(struct card));
    rank3->rank = '2';
    rank3->suit = 'D';
    struct card* rank4 = (struct card*)malloc(sizeof(struct card));
    rank4->rank = '2';
    rank4->suit = 'C';

	add_card(play, rank1);
    add_card(play, rank2);
	add_card(play, rank3);
	add_card(play, rank4);

	while (current1 != NULL){
		printf("whole hand  %c%c\n", current1->top.rank, current1->top.suit);
		current1 = current1->next;
	}

	printf("Rank that was removed! %c\n", check_add_book(play));
	printf("%d\n\n", strlen(play->book));
	
	current1 = (&play->card_list);
    printf("Hand after removing the book: \n");

	while (current1 != NULL){
		printf("whole hand  %c%c\n", current1->top.rank, current1->top.suit);
		current1 = current1->next;
	}

	transfer_cards(play, play2, '3');

	printf("PLAYER RESET: \n");
	reset_player(play);
	current1 = &play->card_list;
	while (current1 != NULL){
		printf("whole hand  %c%c\n", current1->top.rank, current1->top.suit);
		current1 = current1->next;
	}
	printf("Size of book: %d\n", strlen(play->book));
	printf("Size of hand: %d\n", play->hand_size);


//	char a = 'K';
//	printf("search output: %d", search(play, a));
//	printf("rank to play: %c", computer_play(play));
//  user_play(play);

} */

int add_card(struct player* target, struct card* new_card)
{
	struct hand* current = (&target->card_list);
	struct hand* toAdd = (struct hand*) malloc(sizeof(struct hand));
	toAdd->top = (*new_card);
	toAdd->next = NULL;
	
	if(current->top.rank == ' ' && current->top.suit == ' '){
		//Indicates empty hand, add to empty hand
		target->card_list = (*toAdd);
		return 0;
	}
	
	while(current->next != NULL) {
		current = current->next;
	}

	current->next = (toAdd);
	return 0;
}

int remove_card(struct player* target, struct card* old_card)
{
	struct hand* current = (&target->card_list);
	struct hand* previousCard = NULL;;

	if (current == NULL)
		return 0;
	if (current->top.rank == old_card->rank && current->top.suit == old_card->suit 
	&& current->next == NULL){
	//Means that this is the last card of the hand to remove, want to add a card with 
	//rank value ' ',  must handle this case in add.
		struct hand* emptyHand = (struct hand*)malloc(sizeof(struct hand));
		struct card* emptyCard = (struct card*)malloc(sizeof(struct card));
		emptyCard->rank = ' ';
		emptyCard->suit = ' ';
		emptyHand->top = (*emptyCard);
		emptyHand->next = NULL;
		target->card_list = (*emptyHand);
		//printf("GETS HERE\n");
		return 0;
	}
	if(current->top.rank == old_card->rank && current->top.suit == old_card->suit){
		target->card_list = (*current->next);
		return 0;
	}

	while (current->next != NULL){
		if (current->next->top.rank == old_card->rank && current->next->top.suit
		== old_card->suit){
			current->next = current->next->next;
			return 0;
		}
		current = current->next;
	}
	return 1;
}

char check_add_book(struct player* target){
	char ranks[13] = {'2','3','4','5','6','7','8','9','0','J','Q','K','A'};
	struct hand* current = &target->card_list;
    char rankToRemove = ' ';

	for (int i = 0; i < 13; i++){
		int rankCounter = 0;
		current = &target->card_list;
		while (current != NULL){
			if (ranks[i] == current->top.rank){
				rankCounter++;
				//printf("BOOKED METHOD MATCH: card: %c%c, count: %d", current->top.rank,
				//current->top.suit, rankCounter);
			}
			if(rankCounter == 4){
        		rankToRemove = ranks[i];
			}
			current = current->next;
		}
	}
	
    if(rankToRemove != ' '){
    	current = &target->card_list;


		int index = strlen(target->book);
		target->book[index] = rankToRemove;
		while(current != NULL){
			if(current->top.rank == rankToRemove){
				remove_card(target, &current->top);
			}
			current = current->next;
		}
    }
	//printf("CHECKADDBOOK: %c%c", target->card_list.top.rank, target->card_list.top.suit);
	if(target->card_list.top.rank == rankToRemove){
		remove_card(target, &target->card_list.top);
	}

    return rankToRemove;
}

int search(struct player* target, char rank){
	struct hand* current = (&target->card_list);

	while (current != NULL){
		if (current->top.rank == rank)
			return 1;
		if (current->top.rank != rank)
			current = current->next;
	}

	return 0;
}

int transfer_cards(struct player* src, struct player* dest, char rank){

	struct hand* current = &src->card_list;
	int count = 0;
	while(current != NULL){
		if(current->top.rank == rank){
			count++;
			src->hand_size--;
			dest->hand_size++;
			add_card(dest, &current->top);
			remove_card(src, &current->top);
		}
		current = current->next;
	}
	return count;
}

int game_over(struct player* target){
	if(strlen(target->book) == 7)
		return 1;
	else
		return 0;
}

int reset_player(struct player* target){
	struct hand* newHand = (struct hand*)malloc(sizeof(struct hand));
	target->card_list = (*newHand);
	for(int i = 0; i < 7; i++){
		target->book[i] = '\0';
	}
	//memcpy(target->book, newBook, 0);
	target->hand_size = (size_t) 0;
}

char computer_play(struct player* target){
	char rankArray[13] = {'2','3','4','5','6','7','8','9','0','J','Q','K','A'};
	srand(time(NULL));

	while(1){
		int random = rand() % 13;
		char rankToPlay = rankArray[random];
		struct hand* current = &target->card_list;

		while (current != NULL){
			if (current->top.rank == rankToPlay){
				printf("Player 2's turn, enter a Rank: %c\n", rankToPlay);
				return rankToPlay;
			}
			current = current->next;
		}
	}
}

char user_play(struct player* target){
	char r;
	while(1){
		printf("Player 1's turn, enter a Rank: ");
		scanf("%s", &r);

		if (search(target, r) == 1){
			return r;
		} else {
			printf("Error - must have at least one card from rank to play \n");
		}
	}
}


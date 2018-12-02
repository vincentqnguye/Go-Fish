#include <stdio.h>
#include <string.h>
#include "deck.h"
#include "player.h"
#include "card.h"

//#include "deck.c"

int main(int args, char* argv[]) 
{
	//fprintf(stdout, "Put your code here.");
	int running = 1;
	struct player* user = (struct player*)malloc(sizeof(struct player));
	struct player* computer = (struct player*)malloc(sizeof(struct player));
	//playerTurn 0 is player 1's turn, 1 if player 2's
	int playerTurn = 0;
	int turnTaken = 0;
	shuffle();
	printf("Shuffling deck...\n");
	deal_player_cards(user);
	deal_player_cards(computer);
	
	/*printf("Players hand:");
	struct hand* temp2 = &user->card_list;
	while(temp2 != NULL){
		printf("%c%c ", temp2->top.rank, temp2->top.suit);
		temp2 = temp2->next;
	}
	printf("\nClearing hand: ");
	temp2 = &user->card_list;
	struct card* tmpcard = &temp2->top;
	remove_card(user, tmpcard);
	tmpcard = &temp2->top;
	remove_card(user, tmpcard);
	tmpcard = &temp2->top;
	remove_card(user, tmpcard);
	tmpcard = &temp2->top;
	remove_card(user, tmpcard);
	tmpcard = &temp2->top;
	remove_card(user, tmpcard);
	tmpcard = &temp2->top;
	remove_card(user, tmpcard);
	tmpcard = &temp2->top;
	remove_card(user, tmpcard);

	struct card* newcard2 = (struct card*)malloc(sizeof(struct card));
	newcard2->rank = '5';
	newcard2->suit = 'D';
	add_card(user, newcard2);
	struct card* newcard3 = (struct card*)malloc(sizeof(struct card));
	newcard3->rank = '5';
	newcard3->suit = 'H';
	add_card(user, newcard3);
	struct card* newcard4 = (struct card*)malloc(sizeof(struct card));
	newcard4->rank = '5';
	newcard4->suit = 'S';
	add_card(user, newcard4);
	struct card* newcard5 = (struct card*)malloc(sizeof(struct card));
	newcard5->rank = '5';
	newcard5->suit = 'C';
	add_card(computer, newcard5);
	
	temp2 = &computer->card_list;
	while(temp2 != NULL){
		printf("%c%c ", temp2->top.rank, temp2->top.suit);
		temp2 = temp2->next;
	}*/
	
	while(running == 1){

	printf("Player 1's Hand - ");
	struct hand* temp = &user->card_list;
	while(temp != NULL){
		printf("%c%c ", temp->top.rank, temp->top.suit);
		temp = temp->next;
	}
	printf("\n");

	//Print player 1's book
	printf("Player 1's Book - ");
	for(int i = 0; i < strlen(user->book); i++){
		printf("%c ", user->book[i]);
	}
	printf("\n");

	//Print player 2's book
	printf("Player 2's Book - ");
	for(int i = 0; i < strlen(computer->book); i++){
		printf("%c ", computer->book[i]);
	}
	printf("\n");

	//CHECK IF GAME OVER
	if(game_over(user) == 1 || game_over(computer) == 1){
		running = 0;
	}

	if(running == 0){
		if(strlen(user->book) == 7){
			printf("Player 1 Wins! %d-%d\n\n", strlen(user->book), strlen(computer->book));
		} else {
			printf("Player 2 Wins! %d-%d\n\n", strlen(computer->book), strlen(user->book));
		}
		printf("Do you want to play again [Y/N]: ");
		char answer;
		scanf("%s", &answer);
		if(answer == 'Y' || answer == 'y'){
			running = 1;
			reset_player(user);
			reset_player(computer);
			shuffle();
			deal_player_cards(user);
			deal_player_cards(computer);
			continue;
		} else {
			continue;
		}
	}
	

	//TURN OF FIRST PLAYER
	if(playerTurn == 0 && turnTaken == 0){
	turnTaken = 1;
	char userPlayed = user_play(user);
	if(search(computer, userPlayed) == 1){
		temp = &computer->card_list;
		printf("\t- Player 2 has ");
		while(temp != NULL){
			if(temp->top.rank == userPlayed){
				printf("%c%c ", temp->top.rank, temp->top.suit);
			}
			temp = temp->next;
		}
		printf("\n");

		temp = &user->card_list;
		printf("\t- Player 1 has ");
		while(temp != NULL){
			if(temp->top.rank == userPlayed){
				printf("%c%c ", temp->top.rank, temp->top.suit);
			}
			temp = temp->next;
		}
		printf("\n");

		int trans = transfer_cards(computer, user, userPlayed);
		//printf("TRANSFERED CARDS COUNT: %d", trans);

		char bookChar = check_add_book(user);
		//printf("BOOKED CHAR: %c", bookChar);
		if(bookChar == ' '){
		//Doesn't book
		//Computers turn now.
		printf("\n");
		playerTurn = 1;
		} else {
			printf("\t- Player 1 books %c\n", bookChar);
			printf("\t- Player 1 gets another turn\n");
			playerTurn = 0;
		}

	} else {
		printf("\t- Player 2 has no %c's\n", userPlayed);
		if(deck_instance.top_card == 52){
			printf("\t- Unable to deal cards, deck empty\n");
		} else {
		struct card* newCard = next_card();
		add_card(user, newCard);
		printf("\t- Go Fish, Player 1 draws %c%c\n", newCard->rank, newCard->suit);
		char bookedChar = check_add_book(user);
		if(bookedChar != ' '){
			printf("\t- Player 1 books %c because of drawn card\n", bookedChar);
		}
		}
		printf("\t- Player 2's turn\n");
		playerTurn = 1;
	}
	if(user->card_list.top.rank == ' ' && user->card_list.top.suit == ' '){
		printf("\t- Player 1 is out of cards, draw\n");
		struct card* newCard = next_card();
		add_card(user, newCard);
	}
	printf("\n");
	
	}//End if playerTurn = 0
	

	//TURN OF SECOND PLAYER
	if(playerTurn == 1 && turnTaken == 0){
		turnTaken = 1;
		char compPlayed = computer_play(computer);
		if(search(user, compPlayed) == 1){
		temp = &user->card_list;
		printf("\t- Player 1 has ");
		while(temp != NULL){
			if(temp->top.rank == compPlayed){
				printf("%c%c ", temp->top.rank, temp->top.suit);
			}
			temp = temp->next;
		}
		printf("\n");

		temp = &computer->card_list;
		printf("\t- Player 2 has ");
		while(temp != NULL){
			if(temp->top.rank == compPlayed){
				printf("%c%c ", temp->top.rank, temp->top.suit);
			}
			temp = temp->next;
		}
		printf("\n");

		int trans = transfer_cards(user, computer, compPlayed);
		//printf("TRANSFERED CARDS COUNT: %d", trans);

		char bookChar = check_add_book(computer);
		//printf("BOOKED CHAR: %c", bookChar);
		if(bookChar == ' '){
		//Doesn't book
		//Computers turn now.
		playerTurn = 0;
		} else {
			printf("\t- Player 2 books %c\n", bookChar);
			printf("\t- Player 2 gets another turn\n");
			playerTurn = 1;
		}

	} else {
		printf("\t- Player 1 has no %c's\n", compPlayed);
		if(deck_instance.top_card == 52){
			printf("\t- Unable to deal cards, deck empty\n");
		} else {
		struct card* newCard = next_card();
		add_card(computer, newCard);
		printf("\t- Go Fish, Player 2 draws a new card\n");
		char bookedChar = check_add_book(computer);
		if(bookedChar != ' '){
			printf("\t- Player 2 books %c because of drawn card\n", bookedChar);
		}
		}
		printf("\t- Player 1's turn\n");
		playerTurn = 0;
	}
	
	if(computer->card_list.top.rank == ' ' && computer->card_list.top.suit == ' '){
		printf("Player 2 is out of cards, draw\n");
		struct card* newCard = next_card();
		add_card(computer, newCard);
	}
	printf("\n");
	}//End if player turn 1

	turnTaken = 0;

}

	
}

#include"header.h"

int main(void)
{

	const char *suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };
	const char *face[13] = { "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
	int deck[4][13] = { 0 };
	int count_card[13] = { 0 };

	int p1_cardnum[5] = { 0 };
	Card p1_hand[5] = { 0 };
	Card p2_hand[5] = { 0 };

	char redraw = '\0';
	int num_cards = 0;
	int rank_player = 0, player_high=0;
	int rank_computer = 0, computer_high=0;
	int round = 0;

	srand((unsigned)time(NULL));


	printf("You know the rules... Game Start!\n");
	system("pause");
	system("cls");
	

	while (round < 10)
	{
		initialize_deck(deck);
		shuffle(deck);
		printf("Deck shuffled\n");
		system("pause");
		system("cls");

		//player hand
		deal(deck, face, suit, 1, 5, p1_hand, 0);
		display_hand(p1_hand, face, suit);// , 0, 0);

		putchar('\n');




		//computer hand
		deal(deck, face, suit, 6, 10, p2_hand, 0);



		//player redraw
		printf("Would you like to redraw any cards?  Y/N\n");
		scanf(" %c", &redraw);
		while (redraw != 'y' && redraw != 'n' && redraw != 'Y' && redraw != 'N')
		{
			printf("invalid entry, try again\n");
			scanf(" %c", &redraw);
		}
		if (redraw == 'y' || redraw == 'Y')
		{
			redraw_hand(p1_hand, deck, 0, face, suit);
		}

		display_hand(p1_hand, face, suit);
		system("pause");


	//	rank_player = determine_rank(p1_hand);
		//printf("%d\n", rank_player);
		//system("pause");


		//computer deck eval
		rank_computer = determine_rank(p2_hand);
		if (rank_computer == 0)
		{
			computer_redraw(p2_hand, deck, face, suit, 3, 0);
		}
		else if (rank_computer == 1 || rank_computer==2)
		{
			computer_redraw(p2_hand, deck, face, suit, 2, 0);

		}
		else if (rank_computer == 3)
		{
			computer_redraw(p2_hand, deck, face, suit, 1, 0);

		}
		system("cls");
		printf("Computer deck evaluated.\n");
		system("pause");
		system("cls");



		//player redraw
		display_hand(p1_hand, face, suit);
		putchar('\n');
		printf("Would you like to redraw any cards?  Y/N\n");
		scanf(" %c", &redraw);
		while (redraw != 'y' && redraw != 'n' && redraw != 'Y' && redraw != 'N')
		{
			printf("invalid entry, try again\n");
			scanf(" %c", &redraw);
		}
		if (redraw == 'y' || redraw == 'Y')
		{
			redraw_hand(p1_hand, deck, 15, face, suit);
		}

		display_hand(p1_hand, face, suit);
		system("pause");








		//cpu eval
		rank_computer = determine_rank(p2_hand);
		if (rank_computer == 0)
		{
			computer_redraw(p2_hand, deck, face, suit, 3, 6);
		}
		else if (rank_computer == 1 || rank_computer == 2)
		{
			computer_redraw(p2_hand, deck, face, suit, 2, 6);

		}
		else if (rank_computer == 3)
		{
			computer_redraw(p2_hand, deck, face, suit, 1, 6);

		}




		//determine winning hand
		rank_player = determine_rank(p1_hand);
		rank_computer = determine_rank(p2_hand);

		putchar('\n');
		printf("Computer hand:\n");
		display_hand(p2_hand, face, suit);
		putchar('\n');
		system("pause");
		system("cls");

		if (rank_player > rank_computer)
		{
			printf("Player win\n");
		}
		else if (rank_computer > rank_player)
		{
			printf("Computer win\n");
		}
		else
		{
			player_high = determine_high(p1_hand);
			computer_high = determine_high(p2_hand);

			if (player_high > computer_high)
				printf("Player win\n");
			else if (computer_high > player_high)
				printf("Computer win\n");
			else
				printf("A tie I guess\n");
		}
		system("pause");
		++round;
	}
	printf("You made it through 10 rounds. END\n");

	return 0;
}
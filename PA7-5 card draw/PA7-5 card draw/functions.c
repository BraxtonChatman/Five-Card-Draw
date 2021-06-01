#include"header.h"

void shuffle(int deck[][13])
{
	int row = 0, column = 0, card = 0;

	for (card = 1; card <= 52; card++)
	{
		do
		{
			row = rand() % 4;
			column = rand() % 13;
		} while (deck[row][column] != 0);

		deck[row][column] = card;
	}
}

void initialize_deck(int deck[][13])
{
	int row_index = 0, col_index = 0;
	while (row_index < 4)
	{
		for (col_index=0;col_index < 13;++col_index)
		{
			deck[row_index][col_index] = 0;
		}
		++row_index;
	}
}

void deal(const int deck[][13], const char *face[], const char *suit[], int start, int end, Card hand[], int passed_index)
{
	int row = 0, column = 0, card = 0;

	for (card = start; card <= end; card++)
	{
		for (row = 0; row <= 3; row++)
		{
			for (column = 0; column <= 12; column++)
			{
				if (deck[row][column] == card)
				{
					//printf("%5s of %-8s%c", face[column], suit[row], card % 2 == 0 ? '\n' : '\t');
					hand[card-start+passed_index].face_index = column;
					hand[card-start+passed_index].suit_index = row;
				}
			}
		}
	}
}

void display_hand(Card hand[], const char *face[], const char *suit[])//, int start, int end)
{
	int index = 0;
	while (index < 5)
	{
		printf("card%d: %5s of %-8s\n", index+1, face[hand[index].face_index], suit[hand[index].suit_index]);
		++index;
	}
}

void redraw_hand(Card hand[], int deck[][13], int start_mod, char *face[], char *suit[])
{
	int index = 0;
	int response[5] = { -1,-1,-1,-1,-1 };
	int start = 11 + start_mod;

	while (index < 5)
	{
		printf("Would you like to redraw card%d? 1:yes, 0:no\n", index + 1);
		while (response[index] != 1 && response[index] != 0)
		{
			scanf("%d", &response[index]);
		}
		++index;
	}
	for (index = 0; index < 5; ++index)
	{
		if (response[index] == 1)
		{
			deal(deck, face, suit, start, start, hand,index);
			++start;
		}
	}

}

void computer_redraw(Card hand[], int deck[][13], char *face[], char *suit[], int how_many, int start_mod)
{
	int x_array[5] = { 0 };
	int x=0, x1 = 0, x2 = 0, x3 = 0;
	int index = 0;
	int start = start_mod + 30;

	if (how_many == 1)
	{
		x1 = rand() % 5;
		x_array[x1] = 1;
	}

	else if (how_many == 2)
	{
		x1 = rand() % 5;
		x2 = rand() % 5;
		while (x2 == x1)
		{
			x2 = rand() % 5;
		}
		x_array[x1] = 1;
		x_array[x2] = 1;

	}

	else if (how_many == 3)
	{
		x1 = rand() % 5;
		x2 = rand() % 5;
		x3 = rand() % 5;
		while (x2 == x1)
		{
			x2 = rand() % 5;
		}
		while (x3 == x2 || x3 == x1)
		{
			x3 = rand() % 5;
		}
		x_array[x1] = 1;
		x_array[x2] = 1;
		x_array[x3] = 1;


	}
	for (index = 0; index < 5; ++index)
	{
		if (x_array[index] == 1)
		{
			deal(deck, face, suit, start, start, hand, index);
			++start;
		}
	}
}


//int is_pair(Card hand[])
//{
//	int x = 0, index1 = 0, index2 = 0, n1 = 0, n2 = 0;
//	while (index1 < 5 && x == 0)
//	{
//		n1 = hand[index1].face_index;
//		for (index2 = (index1+1); index2 < 5; ++index2)
//		{
//			n2 = hand[index2].face_index;
//			if (n1 == n2)
//				x = 1;
//		}
//		++index1;
//	}
//	return x;
//}

int is_pair(int count[])
{
	int index = 0, x = 0;
	while (index < 13)
	{
		if (count[index] > 1)
			x = 1;
		++index;
	}
	return x;
}

int is_two_pair(int count[])
{
	int pairs = 0;
	int index = 0, x = 0;
	while (index < 13)
	{
		if (count[index] > 1)
			++pairs;
		++index;
	}
	if (pairs >= 2)
		x = 1;
	return x;
}

int is_three_kind(int count[])
{
	int index = 0, x = 0;
	while (index < 13)
	{
		if (count[index] > 2)
			x = 1;
		++index;
	}
	return x;
}

int is_four_kind(int count[])
{
	int index = 0, x = 0;
	while (index < 13)
	{
		if (count[index] > 3)
			x = 1;
		++index;
	}
	return x;
}

int is_flush(Card hand[])
{
	int x = 0;
	if (hand[0].suit_index == hand[1].suit_index && hand[1].suit_index == hand[2].suit_index && hand[2].suit_index == hand[3].suit_index && hand[3].suit_index == hand[4].suit_index)
		x = 1;
	return x;
}

int is_straight(Card hand[])
{
	int max_num = 0, max_index = 0;
	int index = 0, passes = 0, temp=0;
	int x = 0;


	for (passes = 0; passes < 4; ++passes)
	{
		max_num = hand[0].face_index;
		max_index = 0;

		for (index = 0; index < (5 - passes); ++index)
		{

			if (max_num < hand[index].face_index)
			{
				max_num = hand[index].face_index;
				max_index = index;
			}

		}
		temp = hand[max_index].face_index;
		hand[max_index].face_index = hand[4 - passes].face_index;
		hand[4 - passes].face_index = temp;

	}
	int n1 = hand[0].face_index, n2 = hand[1].face_index, n3 = hand[2].face_index, n4 = hand[3].face_index, n5 = hand[4].face_index;
	if (n1 + 1 == n2 && n2 + 1 == n3 && n3 + 1 == n4 && n4 + 1 == n5)
		x = 1;
	return x;
}

void count_cards(Card hand[], int count[])
{
	int count_cleaner_index = 0;
	while (count_cleaner_index < 13)
	{
		count[count_cleaner_index] = 0;
		count_cleaner_index++;
	}
	int index = 0;
	while (index < 5)
	{
		count[hand[index].face_index]++;
		++index;
	}
}

int is_full_house(int count[])
{
	int x = 0;
	if (is_three_kind(count) == 1 && is_two_pair(count) == 1)
		x = 1;
	return x;
}

int is_straight_flush(Card hand[])
{
	int x = 0;
	if (is_flush(hand) == 1 && is_straight(hand) == 1)
		x = 1;
	return x;
}

int determine_rank(Card hand[])
{
	int count[13] = { 0 };

	count_cards(hand, count);

	int rank = 0;
	if (is_pair(count) == 1)
		rank = 1;
	if (is_two_pair(count) == 1)
		rank = 2;
	if (is_three_kind(count) == 1)
		rank = 3;
	if (is_straight(hand) == 1)
		rank = 4;
	if (is_flush(hand) == 1)
		rank = 5;
	if (is_full_house(count) == 1)
		rank = 6;
	if (is_four_kind(count) == 1)
		rank = 7;
	if (is_straight_flush(hand) == 1)
		rank = 8;
	return rank;
	//i probably should have done else ifs in the reverse order here, but what's done is done

}

int determine_high(Card hand[])
{
	int high = 0;
	int index = 1;
	high = hand[0].face_index;
	while (index < 5)
	{
		if (high < hand[index].face_index)
			high = hand[index].face_index;
		++index;
	}
	return high;
}
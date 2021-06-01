#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct card{
	int face_index;
	int suit_index;
}Card;

void shuffle(int deck[][13]);
void deal(const int deck[][13], const char *face[], const char *suit[], int start, int end, Card hand[], int passed_index);
void display_hand(Card hand[], const char *face[], const char *suit[]);//, int start, int end);
void redraw_hand(Card hand[], int deck[][13],int start_mod, char *face[], char *suit[]);
int is_pair(int count[]);
int is_three_kind(int count[]);
int is_two_pair(int count[]);
int is_four_kind(int count[]);
int is_flush(Card hand[]);
int is_straight(Card hand[]);
int is_full_house(int count[]);
int is_straight_flush(Card hand[]);
void count_cards(Card hand[], int count[]);
int determine_rank(Card hand[]);
int determine_high(Card hand[]);
void computer_redraw(Card hand[], int deck[][13], char *face[], char *suit[], int how_many, int start_mod);
void initialize_deck(int deck[][13]);
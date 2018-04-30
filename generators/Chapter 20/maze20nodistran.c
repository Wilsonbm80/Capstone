/* although this maze has a few path that are only one way, there are multiple loops with multiple ways to go - solves itself */
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include "convert3.h"
#define GENERAL_MIDI_ON 1
#define PROGRAM_NUMBERS_ON 1

#define LENGTH 19  /* must be odd and no bigger than 81 */
#define WIDTH  19  /* must be odd and no bigger than 25 */
#define TRUE 1
#define FALSE 0
char maze[LENGTH][WIDTH];
char initial_maze[LENGTH][WIDTH];
struct board
{
 int sop;
 int bass;
};
struct board musicboard[19][19]; 
char ans;
int free_space;
int loc_x;
int loc_y;
int available_path = TRUE;
int win = FALSE;
int trans = 0;
int turns = 0;
void copy_to_initial(void);
void copy_from_initial(void);
void setup(void);
void test_for_free_o(void);
void change_next_z(void);
void test_for_next_z(void);
void join_new_z(void);
void clear_up_maze(void);
void place_you(void);
void place_exit(void);
void move_you(void);
void check_for_win(void);
void solve_maze(void);
void put_more_spaces_in(void);
void solve_mult_maze(void);
void setup_musicboard(void);
int main(void)
{
time_t t;
srand((unsigned) time(&t));
open_midfiles ();
#if GENERAL_MIDI_ON
  general_midi ();
#endif
  srand ((unsigned) time (&t));
  play (48 * 2 * 4, 152 - 16, 100, 0);  // Handshake 
  program_number[0] = 8;  // 8 is bells
  program_number[1] = 73; // 73 is flute
  program_number[2] = 0;  // 0 = piano (for emergency)
  program_number[3] = 0;  
  program_number[4] = 0;
  program_number[5] = 0;
  program_number[6] = 0;
  program_number[7] = 0;
  program_setup ();
play (48 * 2 * 4, 152 - 16, 100, 0);	/* Handshake */
setup();
setup_musicboard();


do
{
test_for_next_z();
if (available_path == TRUE)
do
{
change_next_z();
test_for_next_z();
}while (available_path == TRUE);
test_for_free_o();
if (free_space == TRUE)
join_new_z();
test_for_free_o();
}while(free_space == TRUE);
clear_up_maze();
put_more_spaces_in();
place_you();
place_exit();
copy_to_initial();
do
{
move_you();
check_for_win();
}while (win == FALSE );
play(0,144,musicboard[16][16].sop,127);
play(0,145,musicboard[16][16].bass,127);
play(60,152-16,100,0);
play(0,144-16,musicboard[16][16].sop,0);
play(0,145-16,musicboard[16][16].bass,0);
close_midfiles();
return(0);	
}


void setup_musicboard(void)
{

musicboard[2][2].sop = 21 + 36 + trans;
musicboard[2][2].bass = 21 + 36 + trans;
musicboard[3][2].sop = 23 + 36 + trans;
musicboard[3][2].bass = 21 + 36 + trans;
musicboard[4][2].sop = 24 + 36 + trans;
musicboard[4][2].bass = 21 + 36 + trans;
musicboard[5][2].sop = 26 + 36 + trans;
musicboard[5][2].bass = 21 + 36 + trans;
musicboard[6][2].sop = 28 + 36 + trans;
musicboard[6][2].bass = 21 + 36 + trans;
musicboard[7][2].sop = 30 + 36 + trans;
musicboard[7][2].bass = 21 + 36 + trans;
musicboard[8][2].sop = 32 + 36 + trans;
musicboard[8][2].bass = 21 + 36 + trans;
musicboard[9][2].sop = 21 + 48 + trans;
musicboard[9][2].bass = 21 + 36 + trans;
musicboard[10][2].sop = 23 + 48+ trans;
musicboard[10][2].bass = 21 + 36 + trans;
musicboard[11][2].sop = 24  + 48 + trans;
musicboard[11][2].bass = 21 + 36 + trans;
musicboard[12][2].sop = 26 + 48 + trans;
musicboard[12][2].bass = 21 + 36+ trans;
musicboard[13][2].sop = 28 + 48+ trans;
musicboard[13][2].bass = 21 + 36+ trans;
musicboard[14][2].sop = 30 + 48+ trans;
musicboard[14][2].bass = 21 + 36+ trans;
musicboard[15][2].sop = 32 + 48+ trans;
musicboard[15][2].bass = 21 + 36+ trans;
musicboard[16][2].sop = 33 + 48+ trans;
musicboard[16][2].bass = 21 + 36+ trans;

musicboard[2][3].sop = 21 + 36+ trans;
musicboard[2][3].bass = 23 + 36+ trans;
musicboard[3][3].sop = 23 + 36+ trans;
musicboard[3][3].bass = 23 + 36+ trans;
musicboard[4][3].sop = 24 + 36+ trans;
musicboard[4][3].bass = 23 + 36+ trans;
musicboard[5][3].sop = 26 + 36+ trans;
musicboard[5][3].bass = 23 + 36+ trans;
musicboard[6][3].sop = 28 + 36+ trans;
musicboard[6][3].bass = 23 + 36+ trans;
musicboard[7][3].sop = 30 + 36+ trans;
musicboard[7][3].bass = 23 + 36+ trans;
musicboard[8][3].sop = 32 + 36+ trans;
musicboard[8][3].bass = 23 + 36+ trans;
musicboard[9][3].sop = 21 + 48+ trans;
musicboard[9][3].bass = 23 + 36+ trans;
musicboard[10][3].sop = 23 + 48+ trans;
musicboard[10][3].bass = 23 + 36+ trans;
musicboard[11][3].sop = 24  + 48+ trans;
musicboard[11][3].bass = 23 + 36+ trans;
musicboard[12][3].sop = 26 + 48+ trans;
musicboard[12][3].bass = 23 + 36+ trans;
musicboard[13][3].sop = 28 + 48+ trans;
musicboard[13][3].bass = 23 + 36+ trans;
musicboard[14][3].sop = 30 + 48+ trans;
musicboard[14][3].bass = 23 + 36+ trans;
musicboard[15][3].sop = 32 + 48+ trans;
musicboard[15][3].bass = 23 + 36+ trans;
musicboard[16][3].sop = 33 + 48+ trans;
musicboard[16][3].bass = 23 + 36+ trans;

musicboard[2][4].sop = 21 + 36+ trans;
musicboard[2][4].bass = 24 + 36+ trans;
musicboard[3][4].sop = 23 + 36+ trans;
musicboard[3][4].bass = 24 + 36+ trans;
musicboard[4][4].sop = 24 + 36+ trans;
musicboard[4][4].bass = 24 + 36+ trans;
musicboard[5][4].sop = 26 + 36+ trans;
musicboard[5][4].bass = 24 + 36+ trans;
musicboard[6][4].sop = 28 + 36+ trans;
musicboard[6][4].bass = 24 + 36+ trans;
musicboard[7][4].sop = 30 + 36+ trans;
musicboard[7][4].bass = 24 + 36+ trans;
musicboard[8][4].sop = 32 + 36+ trans;
musicboard[8][4].bass = 24 + 36+ trans;
musicboard[9][4].sop = 21 + 48+ trans;
musicboard[9][4].bass = 24 + 36+ trans;
musicboard[10][4].sop = 23 + 48+ trans;
musicboard[10][4].bass = 24 + 36+ trans;
musicboard[11][4].sop = 24  + 48+ trans;
musicboard[11][4].bass = 24 + 36+ trans;
musicboard[12][4].sop = 26 + 48+ trans;
musicboard[12][4].bass = 24 + 36+ trans;
musicboard[13][4].sop = 28 + 48+ trans;
musicboard[13][4].bass = 24 + 36+ trans;
musicboard[14][4].sop = 30 + 48+ trans;
musicboard[14][4].bass = 24 + 36+ trans;
musicboard[15][4].sop = 32 + 48+ trans;
musicboard[15][4].bass = 24 + 36+ trans;
musicboard[16][4].sop = 33 + 48+ trans;
musicboard[16][4].bass = 24 + 36+ trans;


musicboard[2][5].sop = 21 + 36+ trans;
musicboard[2][5].bass = 26 + 36+ trans;
musicboard[3][5].sop = 23 + 36+ trans;
musicboard[3][5].bass = 26 + 36+ trans;
musicboard[4][5].sop = 24 + 36+ trans;
musicboard[4][5].bass = 26 + 36+ trans;
musicboard[5][5].sop = 26 + 36+ trans;
musicboard[5][5].bass = 26 + 36+ trans;
musicboard[6][5].sop = 28 + 36+ trans;
musicboard[6][5].bass = 26 + 36+ trans;
musicboard[7][5].sop = 30 + 36+ trans;
musicboard[7][5].bass = 26 + 36+ trans;
musicboard[8][5].sop = 32 + 36+ trans;
musicboard[8][5].bass = 26 + 36+ trans;
musicboard[9][5].sop = 21 + 48+ trans;
musicboard[9][5].bass = 26 + 36+ trans;
musicboard[10][5].sop = 23 + 48+ trans;
musicboard[10][5].bass = 26 + 36+ trans;
musicboard[11][5].sop = 24  + 48+ trans;
musicboard[11][5].bass = 26 + 36+ trans;
musicboard[12][5].sop = 26 + 48+ trans;
musicboard[12][5].bass = 26 + 36+ trans;
musicboard[13][5].sop = 28 + 48+ trans;
musicboard[13][5].bass = 26 + 36+ trans;
musicboard[14][5].sop = 30 + 48+ trans;
musicboard[14][5].bass = 26 + 36+ trans;
musicboard[15][5].sop = 32 + 48+ trans;
musicboard[15][5].bass = 26 + 36+ trans;
musicboard[16][5].sop = 33 + 48+ trans;
musicboard[16][5].bass = 26 + 36+ trans;

musicboard[2][6].sop = 21 + 36+ trans;
musicboard[2][6].bass = 28 + 36+ trans;
musicboard[3][6].sop = 23 + 36+ trans;
musicboard[3][6].bass = 28 + 36+ trans;
musicboard[4][6].sop = 24 + 36+ trans;
musicboard[4][6].bass = 28 + 36+ trans;
musicboard[5][6].sop = 26 + 36+ trans;
musicboard[5][6].bass = 28 + 36+ trans;
musicboard[6][6].sop = 28 + 36+ trans;
musicboard[6][6].bass = 28 + 36+ trans;
musicboard[7][6].sop = 30 + 36+ trans;
musicboard[7][6].bass = 28 + 36+ trans;
musicboard[8][6].sop = 32 + 36+ trans;
musicboard[8][6].bass = 28 + 36+ trans;
musicboard[9][6].sop = 21 + 48+ trans;
musicboard[9][6].bass = 28 + 36+ trans;
musicboard[10][6].sop = 23 + 48+ trans;
musicboard[10][6].bass = 28 + 36+ trans;
musicboard[11][6].sop = 24  + 48+ trans;
musicboard[11][6].bass = 28 + 36+ trans;
musicboard[12][6].sop = 26 + 48+ trans;
musicboard[12][6].bass = 28 + 36+ trans;
musicboard[13][6].sop = 28 + 48+ trans;
musicboard[13][6].bass = 28 + 36+ trans;
musicboard[14][6].sop = 30 + 48+ trans;
musicboard[14][6].bass = 28 + 36+ trans;
musicboard[15][6].sop = 32 + 48+ trans;
musicboard[15][6].bass = 28 + 36+ trans;
musicboard[16][6].sop = 33 + 48+ trans;
musicboard[16][6].bass = 28 + 36+ trans;


musicboard[2][7].sop = 21 + 36+ trans;
musicboard[2][7].bass = 30 + 36+ trans;
musicboard[3][7].sop = 23 + 36+ trans;
musicboard[3][7].bass = 30 + 36+ trans;
musicboard[4][7].sop = 24 + 36+ trans;
musicboard[4][7].bass = 30 + 36+ trans;
musicboard[5][7].sop = 26 + 36+ trans;
musicboard[5][7].bass = 30 + 36+ trans;
musicboard[6][7].sop = 28 + 36+ trans;
musicboard[6][7].bass = 30 + 36+ trans;
musicboard[7][7].sop = 30 + 36+ trans;
musicboard[7][7].bass = 30 + 36+ trans;
musicboard[8][7].sop = 32 + 36+ trans;
musicboard[8][7].bass = 30 + 36+ trans;
musicboard[9][7].sop = 21 + 48+ trans;
musicboard[9][7].bass = 30 + 36+ trans;
musicboard[10][7].sop = 23 + 48+ trans;
musicboard[10][7].bass = 30 + 36+ trans;
musicboard[11][7].sop = 24  + 48+ trans;
musicboard[11][7].bass = 30 + 36+ trans;
musicboard[12][7].sop = 26 + 48+ trans;
musicboard[12][7].bass = 30 + 36+ trans;
musicboard[13][7].sop = 28 + 48+ trans;
musicboard[13][7].bass = 30 + 36+ trans;
musicboard[14][7].sop = 30 + 48+ trans;
musicboard[14][7].bass = 30 + 36+ trans;
musicboard[15][7].sop = 32 + 48+ trans;
musicboard[15][7].bass = 30 + 36+ trans;
musicboard[16][7].sop = 33 + 48+ trans;
musicboard[16][7].bass = 30 + 36+ trans;


musicboard[2][8].sop = 21 + 36+ trans;
musicboard[2][8].bass = 32 + 36+ trans;
musicboard[3][8].sop = 23 + 36+ trans;
musicboard[3][8].bass = 32 + 36+ trans;
musicboard[4][8].sop = 24 + 36+ trans;
musicboard[4][8].bass = 32 + 36+ trans;
musicboard[5][8].sop = 26 + 36+ trans;
musicboard[5][8].bass = 32 + 36+ trans;
musicboard[6][8].sop = 28 + 36+ trans;
musicboard[6][8].bass = 32 + 36+ trans;
musicboard[7][8].sop = 30 + 36+ trans;
musicboard[7][8].bass = 32 + 36+ trans;
musicboard[8][8].sop = 32 + 36+ trans;
musicboard[8][8].bass = 32 + 36+ trans;
musicboard[9][8].sop = 21 + 48+ trans;
musicboard[9][8].bass = 32 + 36+ trans;
musicboard[10][8].sop = 23 + 48+ trans;
musicboard[10][8].bass = 32 + 36+ trans;
musicboard[11][8].sop = 24  + 48+ trans;
musicboard[11][8].bass = 32 + 36+ trans;
musicboard[12][8].sop = 26 + 48+ trans;
musicboard[12][8].bass = 32 + 36+ trans;
musicboard[13][8].sop = 28 + 48+ trans;
musicboard[13][8].bass = 32 + 36+ trans;
musicboard[14][8].sop = 30 + 48+ trans;
musicboard[14][8].bass = 32 + 36+ trans;
musicboard[15][8].sop = 32 + 48+ trans;
musicboard[15][8].bass = 32 + 36+ trans;
musicboard[16][8].sop = 33 + 48+ trans;
musicboard[16][8].bass = 32 + 36+ trans;


musicboard[2][9].sop = 21 + 36+ trans;
musicboard[2][9].bass = 21 + 48+ trans;
musicboard[3][9].sop = 23 + 36+ trans;
musicboard[3][9].bass = 21 + 48+ trans;
musicboard[4][9].sop = 24 + 36+ trans;
musicboard[4][9].bass = 21 + 48+ trans;
musicboard[5][9].sop = 26 + 36+ trans;
musicboard[5][9].bass = 21 + 48+ trans;
musicboard[6][9].sop = 28 + 36+ trans;
musicboard[6][9].bass = 21 + 48+ trans;
musicboard[7][9].sop = 30 + 36+ trans;
musicboard[7][9].bass = 21 + 48+ trans;
musicboard[8][9].sop = 32 + 36+ trans;
musicboard[8][9].bass = 21 + 48+ trans;
musicboard[9][9].sop = 21 + 48+ trans;
musicboard[9][9].bass = 21 + 48+ trans;
musicboard[10][9].sop = 23 + 48+ trans;
musicboard[10][9].bass = 21 + 48+ trans;
musicboard[11][9].sop = 24  + 48+ trans;
musicboard[11][9].bass = 21 + 48+ trans;
musicboard[12][9].sop = 26 + 48+ trans;
musicboard[12][9].bass = 21 + 48+ trans;
musicboard[13][9].sop = 28 + 48+ trans;
musicboard[13][9].bass = 21 + 48+ trans;
musicboard[14][9].sop = 30 + 48+ trans;
musicboard[14][9].bass = 21 + 48+ trans;
musicboard[15][9].sop = 32 + 48+ trans;
musicboard[15][9].bass = 21 + 48+ trans;
musicboard[16][9].sop = 33 + 48+ trans;
musicboard[16][9].bass = 21 + 48+ trans;


musicboard[2][10].sop = 21 + 36+ trans;
musicboard[2][10].bass = 23 + 48+ trans;
musicboard[3][10].sop = 23 + 36+ trans;
musicboard[3][10].bass = 23 + 48+ trans;
musicboard[4][10].sop = 24 + 36+ trans;
musicboard[4][10].bass = 23 + 48+ trans;
musicboard[5][10].sop = 26 + 36+ trans;
musicboard[5][10].bass = 23 + 48+ trans;
musicboard[6][10].sop = 28 + 36+ trans;
musicboard[6][10].bass = 23 + 48+ trans;
musicboard[7][10].sop = 30 + 36+ trans;
musicboard[7][10].bass = 23 + 48+ trans;
musicboard[8][10].sop = 32 + 36+ trans;
musicboard[8][10].bass = 23 + 48+ trans;
musicboard[9][10].sop = 21 + 48+ trans;
musicboard[9][10].bass = 23 + 48+ trans;
musicboard[10][10].sop = 23 + 48+ trans;
musicboard[10][10].bass = 23 + 48+ trans;
musicboard[11][10].sop = 24  + 48+ trans;
musicboard[11][10].bass = 23 + 48+ trans;
musicboard[12][10].sop = 26 + 48+ trans;
musicboard[12][10].bass = 23 + 48+ trans;
musicboard[13][10].sop = 28 + 48+ trans;
musicboard[13][10].bass = 23 + 48+ trans;
musicboard[14][10].sop = 30 + 48+ trans;
musicboard[14][10].bass = 23 + 48+ trans;
musicboard[15][10].sop = 32 + 48+ trans;
musicboard[15][10].bass = 23 + 48+ trans;
musicboard[16][10].sop = 33 + 48+ trans;
musicboard[16][10].bass = 23 + 48+ trans;


musicboard[2][11].sop = 21 + 36+ trans;
musicboard[2][11].bass = 24 + 48+ trans;
musicboard[3][11].sop = 23 + 36+ trans;
musicboard[3][11].bass = 24 + 48+ trans;
musicboard[4][11].sop = 24 + 36+ trans;
musicboard[4][11].bass = 24 + 48+ trans;
musicboard[5][11].sop = 26 + 36+ trans;
musicboard[5][11].bass = 24 + 48+ trans;
musicboard[6][11].sop = 28 + 36+ trans;
musicboard[6][11].bass = 24 + 48+ trans;
musicboard[7][11].sop = 30 + 36+ trans;
musicboard[7][11].bass = 24 + 48+ trans;
musicboard[8][11].sop = 32 + 36+ trans;
musicboard[8][11].bass = 24 + 48+ trans;
musicboard[9][11].sop = 21 + 48+ trans;
musicboard[9][11].bass = 24 + 48+ trans;
musicboard[10][11].sop = 23 + 48+ trans;
musicboard[10][11].bass = 24 + 48+ trans;
musicboard[11][11].sop = 24  + 48+ trans;
musicboard[11][11].bass = 24 + 48+ trans;
musicboard[12][11].sop = 26 + 48+ trans;
musicboard[12][11].bass = 24 + 48+ trans;
musicboard[13][11].sop = 28 + 48+ trans;
musicboard[13][11].bass = 24 + 48+ trans;
musicboard[14][11].sop = 30 + 48+ trans;
musicboard[14][11].bass = 24 + 48+ trans;
musicboard[15][11].sop = 32 + 48+ trans;
musicboard[15][11].bass = 24 + 48+ trans;
musicboard[16][11].sop = 33 + 48+ trans;
musicboard[16][11].bass = 24 + 48+ trans;


musicboard[2][12].sop = 21 + 36+ trans;
musicboard[2][12].bass = 26 + 48+ trans;
musicboard[3][12].sop = 23 + 36+ trans;
musicboard[3][12].bass = 26 + 48+ trans;
musicboard[4][12].sop = 24 + 36+ trans;
musicboard[4][12].bass = 26 + 48+ trans;
musicboard[5][12].sop = 26 + 36+ trans;
musicboard[5][12].bass = 26 + 48+ trans;
musicboard[6][12].sop = 28 + 36+ trans;
musicboard[6][12].bass = 26 + 48+ trans;
musicboard[7][12].sop = 30 + 36+ trans;
musicboard[7][12].bass = 26 + 48+ trans;
musicboard[8][12].sop = 32 + 36+ trans;
musicboard[8][12].bass = 26 + 48+ trans;
musicboard[9][12].sop = 21 + 48+ trans;
musicboard[9][12].bass = 26 + 48+ trans;
musicboard[10][12].sop = 23 + 48+ trans;
musicboard[10][12].bass = 26 + 48+ trans;
musicboard[11][12].sop = 24  + 48+ trans;
musicboard[11][12].bass = 26 + 48+ trans;
musicboard[12][12].sop = 26 + 48+ trans;
musicboard[12][12].bass = 26 + 48+ trans;
musicboard[13][12].sop = 28 + 48+ trans;
musicboard[13][12].bass = 26 + 48+ trans;
musicboard[14][12].sop = 30 + 48+ trans;
musicboard[14][12].bass = 26 + 48+ trans;
musicboard[15][12].sop = 32 + 48+ trans;
musicboard[15][12].bass = 26 + 48+ trans;
musicboard[16][12].sop = 33 + 48+ trans;
musicboard[16][12].bass = 26 + 48+ trans;


musicboard[2][13].sop = 21 + 36+ trans;
musicboard[2][13].bass = 28 + 48+ trans;
musicboard[3][13].sop = 23 + 36+ trans;
musicboard[3][13].bass = 28 + 48+ trans;
musicboard[4][13].sop = 24 + 36+ trans;
musicboard[4][13].bass = 28 + 48+ trans;
musicboard[5][13].sop = 26 + 36+ trans;
musicboard[5][13].bass = 28 + 48+ trans;
musicboard[6][13].sop = 28 + 36+ trans;
musicboard[6][13].bass = 28 + 48+ trans;
musicboard[7][13].sop = 30 + 36+ trans;
musicboard[7][13].bass = 28 + 48+ trans;
musicboard[8][13].sop = 32 + 36+ trans;
musicboard[8][13].bass = 28 + 48+ trans;
musicboard[9][13].sop = 21 + 48+ trans;
musicboard[9][13].bass = 28 + 48+ trans;
musicboard[10][13].sop = 23 + 48+ trans;
musicboard[10][13].bass = 28 + 48+ trans;
musicboard[11][13].sop = 24  + 48+ trans;
musicboard[11][13].bass = 28 + 48+ trans;
musicboard[12][13].sop = 26 + 48+ trans;
musicboard[12][13].bass = 28 + 48+ trans;
musicboard[13][13].sop = 28 + 48+ trans;
musicboard[13][13].bass = 28 + 48+ trans;
musicboard[14][13].sop = 30 + 48+ trans;
musicboard[14][13].bass = 28 + 48+ trans;
musicboard[15][13].sop = 32 + 48+ trans;
musicboard[15][13].bass = 28 + 48+ trans;
musicboard[16][13].sop = 33 + 48+ trans;
musicboard[16][13].bass = 28 + 48+ trans;


musicboard[2][14].sop = 21 + 36+ trans;
musicboard[2][14].bass = 30 + 48+ trans;
musicboard[3][14].sop = 23 + 36+ trans;
musicboard[3][14].bass = 30 + 48+ trans;
musicboard[4][14].sop = 24 + 36+ trans;
musicboard[4][14].bass = 30 + 48+ trans;
musicboard[5][14].sop = 26 + 36+ trans;
musicboard[5][14].bass = 30 + 48+ trans;
musicboard[6][14].sop = 28 + 36+ trans;
musicboard[6][14].bass = 30 + 48+ trans;
musicboard[7][14].sop = 30 + 36+ trans;
musicboard[7][14].bass = 30 + 48+ trans;
musicboard[8][14].sop = 32 + 36+ trans;
musicboard[8][14].bass = 30 + 48+ trans;
musicboard[9][14].sop = 21 + 48+ trans;
musicboard[9][14].bass = 30 + 48+ trans;
musicboard[10][14].sop = 23 + 48+ trans;
musicboard[10][14].bass = 30 + 48+ trans;
musicboard[11][14].sop = 24  + 48+ trans;
musicboard[11][14].bass = 30 + 48+ trans;
musicboard[12][14].sop = 26 + 48+ trans;
musicboard[12][14].bass = 30 + 48+ trans;
musicboard[13][14].sop = 28 + 48+ trans;
musicboard[13][14].bass = 30 + 48+ trans;
musicboard[14][14].sop = 30 + 48+ trans;
musicboard[14][14].bass = 30 + 48+ trans;
musicboard[15][14].sop = 32 + 48+ trans;
musicboard[15][14].bass = 30 + 48+ trans;
musicboard[16][14].sop = 33 + 48+ trans;
musicboard[16][14].bass = 30 + 48+ trans;


musicboard[2][15].sop = 21 + 36+ trans;
musicboard[2][15].bass = 32 + 48+ trans;
musicboard[3][15].sop = 23 + 36+ trans;
musicboard[3][15].bass = 32 + 48+ trans;
musicboard[4][15].sop = 24 + 36+ trans;
musicboard[4][15].bass = 32 + 48+ trans;
musicboard[5][15].sop = 26 + 36+ trans;
musicboard[5][15].bass = 32 + 48+ trans;
musicboard[6][15].sop = 28 + 36+ trans;
musicboard[6][15].bass = 32 + 48+ trans;
musicboard[7][15].sop = 30 + 36+ trans;
musicboard[7][15].bass = 32 + 48+ trans;
musicboard[8][15].sop = 32 + 36+ trans;
musicboard[8][15].bass = 32 + 48+ trans;
musicboard[9][15].sop = 21 + 48+ trans;
musicboard[9][15].bass = 32 + 48+ trans;
musicboard[10][15].sop = 23 + 48+ trans;
musicboard[10][15].bass = 32 + 48+ trans;
musicboard[11][15].sop = 24  + 48+ trans;
musicboard[11][15].bass = 32 + 48+ trans;
musicboard[12][15].sop = 26 + 48+ trans;
musicboard[12][15].bass = 32 + 48+ trans;
musicboard[13][15].sop = 28 + 48+ trans;
musicboard[13][15].bass = 32 + 48+ trans;
musicboard[14][15].sop = 30 + 48+ trans;
musicboard[14][15].bass = 32 + 48+ trans;
musicboard[15][15].sop = 32 + 48+ trans;
musicboard[15][15].bass = 32 + 48+ trans;
musicboard[16][15].sop = 33 + 48+ trans;
musicboard[16][15].bass = 32 + 48+ trans;



musicboard[2][16].sop = 21 + 36+ trans;
musicboard[2][16].bass = 33 + 48+ trans;
musicboard[3][16].sop = 23 + 36+ trans;
musicboard[3][16].bass = 33 + 48+ trans;
musicboard[4][16].sop = 24 + 36+ trans;
musicboard[4][16].bass = 33 + 48+ trans;
musicboard[5][16].sop = 26 + 36+ trans;
musicboard[5][16].bass = 33 + 48+ trans;
musicboard[6][16].sop = 28 + 36+ trans;
musicboard[6][16].bass = 33 + 48+ trans;
musicboard[7][16].sop = 30 + 36+ trans;
musicboard[7][16].bass = 33 + 48+ trans;
musicboard[8][16].sop = 32 + 36+ trans;
musicboard[8][16].bass = 33 + 48+ trans;
musicboard[9][16].sop = 21 + 48+ trans;
musicboard[9][16].bass = 33 + 48+ trans;
musicboard[10][16].sop = 23 + 48+ trans;
musicboard[10][16].bass = 33 + 48+ trans;
musicboard[11][16].sop = 24  + 48+ trans;
musicboard[11][16].bass = 33 + 48+ trans;
musicboard[12][16].sop = 26 + 48+ trans;
musicboard[12][16].bass = 33 + 48+ trans;
musicboard[13][16].sop = 28 + 48+ trans;
musicboard[13][16].bass = 33 + 48+ trans;
musicboard[14][16].sop = 30 + 48+ trans;
musicboard[14][16].bass = 33 + 48+ trans;
musicboard[15][16].sop = 32 + 48+ trans;
musicboard[15][16].bass = 33 + 48+ trans;
musicboard[16][16].sop = 33 + 48+ trans;
musicboard[16][16].bass = 33 + 48+ trans;
}





void copy_to_initial(void)
{
int i,j;
for (i = 0; i < LENGTH; ++i)


for (j = 0; j < WIDTH; ++j)
initial_maze[i][j] = maze[i][j];
}
void copy_from_initial(void)
{
int i,j;
for (i = 0; i < LENGTH; ++i)
for (j = 0; j < WIDTH; ++j)
if (maze[i][j] != 'E' )
maze[i][j] = initial_maze[i][j];
}
void solve_mult_maze(void)
{
int x,y;
int count;
int goal_attained = 0;
int direction;
int done;
do
{
solve_maze();
maze[2][2] = 'E';
x = 2; y = 2;
++turns;  
if (turns > 5)
  trans = -3;
if (turns > 3)
  trans = 10;
if (turns > 15)
  trans = 7;
if (turns > 20)
  trans = 3;
if (turns > 25)
  trans = 0;
setup_musicboard();                                   
do{
do{
done = 0;
direction = rand()%(4);
if (direction == 0)
{
if (maze[x-1][y] == ' ')
{
--x;
done = 1;
}
}
else if (direction == 1)
{
if (maze[x][y-1] == ' ')
{
--y;
done  = 1;
}
}
else if (direction == 2)
{
if (maze[x+1][y] == ' ')
{
++x;
done = 1;
}
}
else if (direction == 3)
{
if (maze[x][y+1] == ' ')
{
++y;
done = 1;
}
}
}while (done == 0);
count = 0;
if (maze[x-1][y] == 'E')
++count;
if (maze[x+1][y] == 'E')
++count;
if (maze[x][y+1] == 'E')
++count;
if (maze[x][y-1] == 'E')
++count;
if (count > 1)
maze[x][y] = 'X';
else
 {maze[x][y] = 'E';  
  play(0,144,musicboard[x][y].sop,127);
  play(0,145,musicboard[x][y].bass,127);
  play ((rand () % (2) + 1) * 48, 152 - 16, 100, 0);
  play(0,144-16,musicboard[x][y].sop,0);
  play(0,145-16,musicboard[x][y].bass,0);
 }  
}while (maze[x][y] == 'E' && !(x == LENGTH-3 && y == WIDTH-4)
&& !(x == LENGTH-4 && y == WIDTH-3)  );
if ( (x == LENGTH-3 && y == WIDTH-4) || (x == LENGTH-4 &&
y == WIDTH -3))
goal_attained = 1;
}while(goal_attained == 0);
}

void put_more_spaces_in(void)
{
int i;
int x,y;
for (i = 0; i < 800; ++i)
{
x = rand()%(LENGTH-4)+2;
y = rand()%(WIDTH-4)+2;
if (x%2 == 0 && y%2 == 1)
maze[x][y] = ' ';
}
}
void solve_maze(void)
{
int local_counter;
int global_counter;
int i,j;
for (i = 0; i < LENGTH; ++i)
for (j = 0; j < WIDTH; ++j)
if (maze[i][j] == 'E')
maze[i][j] = ' ';
place_you();
do
{
global_counter = 0;
for (i = 0; i < LENGTH; ++i)
for (j = 0; j < WIDTH; ++j)
{
local_counter = 0;
if (maze[i][j] == ' ')
{
if (maze[i+1][j] == 'X')
++local_counter;
if (maze[i - 1][j] == 'X')
++local_counter;
if (maze[i][j + 1] == 'X')
++local_counter;
if (maze[i][j - 1] == 'X')
++local_counter;
if (local_counter > 2)
{
maze[i][j] = 'X';
}
if (local_counter > 2) global_counter = local_counter;
}/* end of if */
}/* end of for */
}while(global_counter > 2);
}
void check_for_win(void)
{
if (maze[LENGTH-4][WIDTH-3] == 'E' || maze[LENGTH-3][WIDTH-4] == 'E')
win = TRUE;
}
void place_you(void)
{
loc_x = 2;
loc_y = 2;
maze[loc_x][loc_y] = 'E';
}
void place_exit(void)
{
maze[LENGTH-3][WIDTH-3] = 'D';
}
void move_you(void)
{
solve_mult_maze();
copy_from_initial();
}
void clear_up_maze(void)
{
int i,j;
for (i = 0; i < LENGTH; ++i)
for (j = 0; j < WIDTH; ++j)
if (maze[i][j] == 'Z') maze[i][j] = ' ';
}
void join_new_z(void)
{
int x,y;
int found;
do
{
x = rand()%(LENGTH);
y = rand()%(WIDTH);
found = 0;
if (maze[x][y] == 'o')
{
if (maze[x-2][y] == 'Z')
{
maze[x-1][y] = 'Z';
maze[x][y] = 'Z';
loc_x = x;
loc_y = y;
found = 1;
}
else if  (maze[x+2][y] == 'Z')
{
maze[x+1][y] = 'Z';
maze[x][y] = 'Z';
loc_x = x;
loc_y = y;
found = 1;
}
else if (maze[x][y-2] == 'Z')
{
maze[x][y-1] = 'Z';
maze[x][y] = 'Z';
loc_x = x;
loc_y = y;
found = 1;
}
else if (maze[x][y+2] == 'Z')
{
maze[x][y+1] = 'Z';
maze[x][y] = 'Z';
loc_x = x;
loc_y = y;
found = 1;
}
}
}while(found == FALSE);
}
void test_for_next_z(void)
{
available_path =  FALSE;
if ( maze[loc_x - 2][loc_y] == 'o' ||
maze[loc_x + 2][loc_y] == 'o' ||
maze[loc_x][loc_y-2] == 'o' ||
maze[loc_x][loc_y+2] == 'o')
available_path = TRUE;
}
void change_next_z(void)
{
int x,y;
int direction;
int temp_loc_x;
int temp_loc_y;
do
{
direction = rand()%(4);
temp_loc_x = loc_x;
temp_loc_y = loc_y;
if (direction == 0)
temp_loc_x = loc_x - 2;
else if (direction == 1)
temp_loc_x = loc_x + 2;
else if (direction == 2)
temp_loc_y = loc_y - 2;
else if (direction == 3)
temp_loc_y = loc_y + 2;
}while (maze[temp_loc_x][temp_loc_y] != 'o');
if (direction == 0)
{
maze[loc_x-1][loc_y] = 'Z';
maze[temp_loc_x][loc_y] = 'Z';
}
else if (direction == 1)
{
maze[loc_x+1][loc_y] = 'Z';
maze[temp_loc_x][loc_y] = 'Z';
}
else if (direction == 2)
{
maze[loc_x][loc_y - 1] = 'Z';
maze[loc_x][temp_loc_y] = 'Z';
}
else if (direction == 3)
{
maze[loc_x][loc_y + 1] = 'Z';
maze[loc_x][temp_loc_y] = 'Z';
}
for (x = -1; x < 2; ++x)
for (y = -1; y < 2; ++y)
if (maze[loc_x + x][loc_y + y] != 'Z')
maze[loc_x + x][loc_y + y]  =  'X';
loc_x = temp_loc_x;
loc_y = temp_loc_y;
}
void test_for_free_o(void)
{
int i,j;
free_space = FALSE;
for (j = 0; j < WIDTH; ++j)
for (i = 0; i < LENGTH; ++i)
if (maze[i][j] == 'o')
free_space = TRUE;
}
void setup(void)
{
int x;
int i;
int j;
for (j = 0; j < WIDTH; ++j)
for (i = 0; i < LENGTH; ++i)
{
if (j%2==1||i%2==1)
maze[i][j] = '.';
else maze[i][j] = 'o';
}
for (x = 0; x < LENGTH; ++x)
{
maze[x][0] = 'X';
maze[x][1] = 'X';
musicboard[x][0].sop = 0;
musicboard[x][0].bass = 0;
musicboard[x][1].sop = 0;
musicboard[x][1].bass = 0;
}
for (x = 0; x < LENGTH; ++x)
{
maze[x][WIDTH - 1] = 'X';
maze[x][WIDTH - 2] = 'X';
musicboard[x][WIDTH - 1].sop = 0;
musicboard[x][WIDTH - 1].bass = 0;
musicboard[x][WIDTH - 2].sop = 0;
musicboard[x][WIDTH - 2].bass = 0;
}
for (x = 0; x < WIDTH; ++x)
{
maze[0][x] = 'X';
maze[1][x] = 'X';
musicboard[x][WIDTH - 1].sop = 0;
musicboard[x][WIDTH - 1].bass = 0;
musicboard[x][WIDTH - 2].sop = 0;
musicboard[x][WIDTH - 2].sop = 0;
}
for (x = 0; x < WIDTH; ++x)
{
maze[LENGTH - 1][x] = 'X';
maze[LENGTH - 2][x] = 'X';
musicboard[LENGTH - 1][x].sop = 0;
musicboard[LENGTH - 1][x].bass = 0;
musicboard[LENGTH - 2][x].sop = 0;
musicboard[LENGTH - 2][x].bass = 0;
}
loc_x = 2; loc_y = 2;
maze[loc_x][loc_y] = 'Z';
}
 

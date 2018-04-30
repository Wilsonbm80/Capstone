//lifemusic.c
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<curses.h>
#include "convert3.h"
#define GENERAL_MIDI_ON 1
#define PROGRAM_NUMBERS_ON 1
#define LENGTH  12   // playing area is 10 by 10 with border on all 4 sides  
#define WIDTH   12  //  

struct location
{
int i;
int j;
};
struct location player;

int tempi;
int tempj;
int matrix[10][10] ={ 
                      {12,13,14,15,16,17,18,19,20,21},  
                      {22,23,24,25,26,27,28,29,30,31},
                      {32,33,34,35,36,37,38,39,40,41},
                      {42,43,44,45,46,47,48,49,50,51},
                      {52,53,54,55,56,57,58,59,60,61},
                      {62,63,64,65,66,67,68,69,70,71},
                      {72,73,74,75,76,77,78,79,80,81},
                      {82,83,84,85,86,87,88,89,90,91},
                      {92,93,94,95,96,97,98,99,100,101},
                      {102,103,104,105,106,107,108,109,110,111},  
                   };
int rh = 0;
int ch = 0;
char board[LENGTH][WIDTH];
char board1[LENGTH][WIDTH];
char tempboard[LENGTH][WIDTH];
int number;
int counter;
int success;
int kbhit(void);
void display(void);
void display1(void);
void setup(void);
void initialize_board1(void);
void clearboard(void);
void cleartempboard(void);
void count_neighbors_and_generate(void);
void copy_tempboard_back_to_board(void);
void intro(void);
void place_xs(void);
void choice();
void randomly(void);
void cut_off_all_sounds(void);
int main(void)
{
int i,j;
time_t t;
srand((unsigned)time(&t)); 
/*
 open_midfiles ();
#if GENERAL_MIDI_ON
  general_midi ();
#endif
  srand ((unsigned) time (&t));
  play (48 * 2 * 4, 152 - 16, 100, 0);	// Handshake 
  program_number[0] = 8;  // 8 is best (bells)
  program_number[1] = 46; // 46 is harp
  program_number[2] = 73; // 73 is flute

  program_number[3] = 0;  // 0 = piano
  program_number[4] = 0;
  program_number[5] = 0;
  program_number[6] = 0;
  program_number[7] = 0;
  program_setup ();
 */ 

initscr();
start_color();
init_pair(1,COLOR_YELLOW,COLOR_BLACK);
attrset(COLOR_PAIR(1));
attron(A_BOLD);
curs_set(0);
noecho();
intro();
clear();
setup();
clearboard();
cleartempboard();
clear();


/*
for (i = 0; i < 10; ++i)
{
  for (j = 0; j < 10; ++j) 
  {
   play(0,144,matrix[i][j],100);
   play(150,152-16,60,0);
   play(0,144-16,matrix[i][j],0);
  }
}
*/

choice();
open_midfiles ();
clear(); // ?
#if GENERAL_MIDI_ON
  general_midi ();
#endif
  srand ((unsigned) time (&t));
  play (48 * 2 * 4, 152 - 16, 100, 0);  // Handshake 
  program_number[0] = 8;  // 8 is best (bells)
  program_number[1] = 46; // 46 is harp
  program_number[2] = 73; // 73 is flute

  program_number[3] = 0;  // 0 = piano
  program_number[4] = 0;
  program_number[5] = 0;
  program_number[6] = 0;
  program_number[7] = 0;
  program_setup ();
do
{
count_neighbors_and_generate();
clearboard();
copy_tempboard_back_to_board();
cleartempboard();
display1();
printw("\n");
refresh();
attrset(COLOR_PAIR(1));
attron(A_BOLD);
printw("\npress key any to exit");
refresh(); 
napms(200); //getch();
}while (!kbhit());       //(1);    
getch();
endwin();
//play_procedure(); 
cut_off_all_sounds(); 
close_midfiles();
return (1);
}


void choice(void)
{
char ans;
attrset(COLOR_PAIR(1));
attron(A_BOLD);
printw("You must choose if you want to place the objects, or\n");
printw("if you want it chosen randomly.\n");
printw("press the key r for random and p to place the objects.\n");
refresh();
ans = getch();
if (ans == 'r')
{
randomly();
display();
}
else 
{
clear();
attrset(COLOR_PAIR(1));
attron(A_BOLD);
printw("This is the way you place objects, if you choose to do it this way.\n");
printw("You move by up=u, down=d, left=l, right=r\n");  
printw("Move the plus sign around with the arrow keys. When you wish to\n");
printw("place an x there, press lower case x key.\n");
printw("If you make a mistake and want to take it away, press lower case e key.\n");
printw("Put as many as you wish\n");
printw("when you wish the game of life to begin, press lower case g key.\n");
printw("Now press enter to begin. WRITE THESE INSTRUCTIONS DOWN.\n");
refresh();
getch();
clear();
display();
place_xs();
}
}

void cut_off_all_sounds(void)
{
  int i,j;
for (i = 0; i < 10; ++i) 
 for (j = 0; j < 10; ++j)
   {
    play(0,144-16,matrix[i][j],0);
    play(0,145-16,matrix[i][j],0);
    play(0,146-16,matrix[i][j],0);
    play(0,147-16,matrix[i][j],0);
   }
}


void initialize_board1(void)
{
int i,j; 
for (i = 0; i < LENGTH; ++i) 
 for (j = 0; j < WIDTH; ++j)
   board1[i][j] = ' ';
}



void place_xs(void)
{
char ans;
int i,j;
move(tempj,tempi);
printw("+");
refresh();
do{
tempj = player.j;
tempi = player.i;
do{
ans = getch();
if (ans == 'd' && tempj != WIDTH -2)
tempj = tempj + 1;
else if (ans == 'u'  && tempj != 1)
tempj = tempj -1;
else if  (ans == 'l' && tempi != 1)
tempi = tempi - 1;
else if  (ans == 'r' && tempi != LENGTH - 2)
tempi = tempi + 1;
if (ans != 'x' )
display();
for (j = 0; j < WIDTH; ++j)
for (i = 0; i < LENGTH; ++i)
{
if (j == tempj && i == tempi)
{
move(j,i);
printw("+");
}
}
}while (ans != 'x' && ans != 'g' && ans != 'e' );
player.i = tempi;
player.j = tempj;
if (ans == 'x' )
board[player.i][player.j] = 'x';
if (ans == 'e')
board[player.i][player.j] = ' ';
clear();
display();
}while (ans != 'g');
}











void randomly(void)
{
int i;
for (i = 0; i < 48; ++i)
{
player.i = rand()%(10)+1;
player.j = rand()%(10)+1;
board[player.i][player.j] = 'x';
}
}
int kbhit(void)
{
nodelay(stdscr,TRUE);
noecho();
ch = getch();
if (ch == ERR)
rh = FALSE;
else 
{
rh = TRUE;
ungetch(ch);
} 
return(rh);
}


void intro(void)
{
attrset(COLOR_PAIR(1));
attron(A_BOLD);
printw("THIS IS THE GAME OF LIFE\n");
printw("Now press enter to begin.\n");
refresh();
getch();
}
void copy_tempboard_back_to_board(void)
{
int i,j;
for (i = 1; i < LENGTH-1; ++i)
for (j = 1; j < WIDTH-1; ++j)
board[i][j] = tempboard[i][j];
}


void count_neighbors_and_generate(void)
{
int i,j;
int count;
for (i = 2; i < LENGTH - 2;  ++i)
for (j = 2; j < WIDTH - 2; ++j)
{
count = 0;
if (board[i-1][j-1] == 'x') ++count;
if (board[i-1][j] == 'x') ++count;
if (board[i-1][j+1] == 'x') ++count;
if (board[i][j-1] == 'x') ++count;
if (board[i][j+1] == 'x') ++count;
if (board[i+1][j-1] == 'x') ++count;
if (board[i+1][j]   == 'x') ++count;
if (board[i+1][j+1] == 'x') ++count;
if  (count == 3) tempboard[i][j] = 'x';
if  (count >= 4) tempboard[i][j] = ' ';
if (board[i][j] == 'x'  && count == 2) tempboard[i][j] = 'x';
if (board[i][j] == 'x'  && count == 3) tempboard[i][j] = 'x';
}
// now for the four wrap around procedures 
for (i=1; i < LENGTH-2; ++i)
{
count = 0;
if (board[i-1][WIDTH-2] == 'x') ++count;
if (board[i][WIDTH-2] == 'x')   ++count;
if  (board[i+1][WIDTH-2] =='x')   ++count;
if (board[i-1][1] == 'x') ++count;
if (board[i+1][1] == 'x') ++count;
if (board[i-1][2] == 'x') ++count;
if (board[i][2] == 'x') ++count;
if (board[i+1][2] == 'x') ++count;
if  (count == 3) tempboard[i][1] = 'x';
if  (count >= 4) tempboard[i][1] = ' ';
if (board[i][1] == 'x'  && count == 2) tempboard[i][1] = 'x';
if (board[i][1] == 'x'  && count == 3) tempboard[i][1] = 'x';
}
for (i = 1;i < LENGTH - 2; ++i)
{
count =0;
if (board[i-1][WIDTH-3] == 'x') ++count;
if (board[i][WIDTH-3] =='x') ++count;
if (board[i+1][WIDTH-3]== 'x') ++count;
if (board[i-1][WIDTH-2] == 'x') ++count;
if (board[i+1][WIDTH-2] == 'x') ++count;
if  (board[i-1][1] == 'x') ++count;
if  (board[i][1] == 'x') ++count;
if  (board[i+1][1] == 'x') ++count;
if  (count == 3) tempboard[i][WIDTH-2] = 'x';
if  (count >= 4) tempboard[i][WIDTH-2] = ' ';
if (board[i][WIDTH-2] == 'x'  && count == 2)
tempboard[i][WIDTH-2] = 'x';
if (board[i][WIDTH-2] == 'x'  && count == 3)
tempboard[i][WIDTH-2] = 'x';
}
for (i=1; i < WIDTH-2; ++i)
{
count = 0;
if (board[LENGTH-2][i-1] == 'x') ++count;
if (board[LENGTH-2][i] == 'x') ++count;
if (board[LENGTH-2][i+1] == 'x') ++count;
if (board[1][i-1] == 'x') ++count;
if (board[1][i+1] == 'x') ++count;
if (board[2][i-1] == 'x') ++count;
if  (board[2][i] == 'x') ++count;
if (board[2][i+1] == 'x') ++count;
if  (count == 3) tempboard[1][i] = 'x';
if  (count >= 4) tempboard[1][i] = ' ';
if (board[1][i] == 'x'  && count == 2)
tempboard[1][i] = 'x';
if (board[1][i] == 'x'  && count == 3)
tempboard[1][i] = 'x';
}
for (i = 1;i < WIDTH - 2; ++i)
{
count =0;
if (board[LENGTH-3][i-1] == 'x') ++count;
if (board[LENGTH-3][i] == 'x') ++count;
if (board[LENGTH-3][i + 1] == 'x') ++count;
if (board[LENGTH-2][i-1] == 'x') ++count;
if (board[LENGTH-2][i+1] == 'x') ++count;
if (board[1][i-1] == 'x') ++count;
if (board[1][i] == 'x') ++count;
if (board[1][i+1] == 'x') ++ count;
if  (count == 3) tempboard[LENGTH-2][i] = 'x';
if  (count >= 4) tempboard[LENGTH-2][i] = ' ';
if (board[LENGTH-2][i] == 'x'  && count == 2)
tempboard[LENGTH-2][i] = 'x';
if (board[LENGTH-2][i] == 'x'  && count == 3)
tempboard[LENGTH-2][i] = 'x';
}

count =0;
if (board[LENGTH-2][1] == 'x') ++count;
if (board[LENGTH-2][WIDTH-2] == 'x') ++count;
if (board[LENGTH-2][WIDTH-3] == 'x') ++count;
if (board[1][WIDTH-3] == 'x') ++count;
if (board[1][1] == 'x') ++count;
if (board[2][WIDTH-3] == 'x') ++count;
if (board[2][WIDTH-2] == 'x') ++count;
if (board[2][1] == 'x') ++ count;
if  (count == 3) tempboard[1][WIDTH-2] = 'x';
if  (count >= 4) tempboard[1][WIDTH-2] = ' ';
if (board[1][WIDTH-2] == 'x'  && count == 2)
tempboard[1][WIDTH-2] = 'x';
if (board[1][WIDTH-2] == 'x'  && count == 3)
tempboard[1][WIDTH-2] = 'x';


count =0;
if (board[LENGTH-2][2] == 'x') ++count;
if (board[LENGTH-2][1] == 'x') ++count;
if (board[LENGTH-2][WIDTH-2] == 'x') ++count;
if (board[1][2] == 'x') ++count;
if (board[1][WIDTH-2] == 'x') ++count;
if (board[2][WIDTH-2] == 'x') ++count;
if (board[2][1] == 'x') ++count;
if (board[2][2] == 'x') ++ count;
if  (count == 3) tempboard[1][1] = 'x';
if  (count >= 4) tempboard[1][1] = ' ';
if (board[1][1] == 'x'  && count == 2)
tempboard[1][1] = 'x';
if (board[1][1] == 'x'  && count == 3)
tempboard[1][1] = 'x';


count =0;
if (board[LENGTH-3][2] == 'x') ++count;
if (board[LENGTH-3][1] == 'x') ++count;
if (board[LENGTH-3][WIDTH-2] == 'x') ++count;
if (board[LENGTH-2][2] == 'x') ++count;
if (board[LENGTH-2][WIDTH-2] == 'x') ++count;
if (board[1][2] == 'x') ++count;
if (board[1][1] == 'x') ++count;
if (board[1][WIDTH-2] == 'x') ++ count;
if  (count == 3) tempboard[LENGTH-2][1] = 'x';
if  (count >= 4) tempboard[LENGTH-2][1] = ' ';
if (board[LENGTH-2][1] == 'x'  && count == 2)
tempboard[LENGTH-2][1] = 'x';
if (board[LENGTH-2][1] == 'x'  && count == 3)
tempboard[LENGTH-2][1] = 'x';



count =0;
if (board[LENGTH-3][1] == 'x') ++count;
if (board[LENGTH-3][WIDTH-2] == 'x') ++count;
if (board[LENGTH-3][WIDTH-3] == 'x') ++count;
if (board[LENGTH-2][1] == 'x') ++count;
if (board[LENGTH-2][WIDTH-3] == 'x') ++count;
if (board[1][1] == 'x') ++count;
if (board[1][WIDTH-2] == 'x') ++count;
if (board[1][WIDTH-3] == 'x') ++ count;
if  (count == 3) tempboard[LENGTH-2][WIDTH-2] = 'x';
if  (count >= 4) tempboard[LENGTH-2][WIDTH-2] = ' ';
if (board[LENGTH-2][WIDTH-2] == 'x'  && count == 2)
tempboard[LENGTH-2][WIDTH-2] = 'x';
if (board[LENGTH-2][WIDTH-2] == 'x'  && count == 3)
tempboard[LENGTH-2][WIDTH-2] = 'x';
}
void setup(void)
{
int i;
int j;
for (j = 0; j < WIDTH; ++j)
for (i = 0; i < LENGTH; ++i)
board[i][j] = ' '; 
for (i = 0; i < LENGTH; ++i)
board[i][0] = 'X';
for (i = 0; i < LENGTH; ++i)
board[i][WIDTH - 1] = 'X';
for (i = 0; i < WIDTH; ++i)
board[0][i] = 'X';
for (i = 0; i < WIDTH; ++i)
board[LENGTH - 1][i] = 'X';
for (j = 0; j < WIDTH; ++j)
for (i = 0; i < LENGTH; ++i)
tempboard[i][j] = board[i][j];
}
void clearboard(void)
{
int i,j;
for (j = 1; j < WIDTH-1; ++j)
for (i = 1; i < LENGTH-1; ++i)
board[i][j] = ' ';
}
void cleartempboard(void)
{
int i,j;
for (j = 1; j < WIDTH-1; ++j)
for (i = 1; i < LENGTH-1; ++i)
tempboard[i][j] = ' ';
}

void display(void)
{
  int i,j;
  int count_notes = 0;
  move(0,0);
  for (j = 0; j < WIDTH;++j)
    for (i = 0; i < LENGTH; ++i)
    {
    if (board[i][j] == 'x')
     ++count_notes; 
    move(j,i);
    attrset(COLOR_PAIR(1));
    attron(A_BOLD);
    printw("%c",board[i][j]);   
    refresh();
   }   
}




void display1(void)
{
  int i,j;
  int count_notes = 0;
  move(0,0);
  for (j = 0; j < WIDTH;++j)
    for (i = 0; i < LENGTH; ++i)
    {
    if (board[i][j] == 'x')
     ++count_notes; 
    move(j,i);
    attrset(COLOR_PAIR(1));
    attron(A_BOLD);
    printw("%c",board[i][j]);   
    refresh();
   }   

/*for (i = 0; i < LENGTH; ++i)
{
  for (j = 0; j < WIDTH; ++j) 
  {
   if (board[i][j] == 'x') {
    play(0,144,matrix[i-1][j-1],100);
    play(150,152-16,60,0);
    play(0,144-16,matrix[i-1][j-1],0);
   }
  }
}
*/

 for (j = 0; j < WIDTH;++j)
     for (i = 0; i < LENGTH; ++i)
   if (board[i][j] == 'x' && board1[i][j] != board[i][j])
    { 
     play(0,144,matrix[i-1][j-1],60);
     play(0,145,matrix[i-1][j-1],60);
     play(0,146,matrix[i-1][j-1],60);
     play(0,147,matrix[i-1][j-1],60); 
    }       
   if (count_notes > 55) count_notes = 55; 
       play(120 - count_notes*2,152-16,60,0);

 for (j = 0; j < WIDTH;++j)
     for (i = 0; i < LENGTH; ++i)
  if (board[i][j] == ' ')
   {
    play(0,144-16,matrix[i-1][j-1],0);
    play(0,145-16,matrix[i-1][j-1],0);
    play(0,146-16,matrix[i-1][j-1],0);
    play(0,147-16,matrix[i-1][j-1],0);
   }

 for (j = 0; j < WIDTH;++j)
for (i = 0; i < LENGTH; ++i)
  board1[i][j] = board[i][j];

}



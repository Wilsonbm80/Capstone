//rowlifemus1.c
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
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
int matrix[10][10];
int prime[12];
int inversion[12];
int rowmatrix[12][12];
int rowmatrix1[12][12];
int xnumber;
int xcounter;
int xsuccess;
char board[LENGTH][WIDTH];
char board1[LENGTH][WIDTH];
char tempboard[LENGTH][WIDTH];
int number;
int counter;
int success;
void display(void);
void display1(void);
void setup(void);
void initialize_board1(void);
void clearboard(void);
void cleartempboard(void);
void count_neighbors_and_generate(void);
void copy_tempboard_back_to_board(void);
void choice();
void randomly(void);
void cut_off_all_sounds(void);
void makerowmatrix1(void);
void makematrix(void);

int main(void)
{
int i;
time_t t;
srand((unsigned)time(&t)); 
setup();
clearboard();
cleartempboard();
makerowmatrix1();
makematrix();
choice();
open_midfiles ();
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
for (i = 0; i < 50; ++i)
{
count_neighbors_and_generate();
clearboard();
copy_tempboard_back_to_board();
cleartempboard();
display1();
}    
cut_off_all_sounds(); 
close_midfiles();
return (0);
}



void makematrix()
{
int i,j;
for (j = 0; j < 10; ++j) 
  for (i = 0; i < 10; ++i)
    matrix[i][j] = rowmatrix1[i][j] + (j+1)*12; 
}



void choice(void)
{
randomly();
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

void makerowmatrix1(void)
	{
	 int i,j,k;
	 
         
	 int factor_to_add,factor_to_add1;
        
        xnumber = 0; // set first note to 0           
        xcounter = 0;
        prime[xcounter] = xnumber;
        ++xcounter;
      do
        { 
         xsuccess = 1;
         xnumber =  rand()%12;
         for (i = 0; i < xcounter; ++i)
            {
             if (prime[i] == xnumber)
                {
                 xsuccess = 0;
                 }
         }  
      if(xsuccess == 1)
        {
         prime[xcounter] = xnumber;
         xcounter++;
        }
  }while(xsuccess == 0 || xcounter < 12);
        factor_to_add = 12 - prime[0];   /* set first note to 0 */
         for (i = 0; i < 12; ++i)
            prime[i] = (prime[i] + factor_to_add)%12;
         for (i = 0; i < 12; ++i)
            inversion[i] = (12 - prime[i])%12;
         for (i = 0; i < 12; ++i)
          rowmatrix[i][0] = prime[i];
         for (i = 0; i < 12; ++i)
          rowmatrix[0][i] = inversion[i];
        for (j = 1; j < 12; ++j)
          for (i = 1; i < 12; ++i)
        rowmatrix[i][j] = (rowmatrix[i][0] + rowmatrix[0][j]) %12;
        factor_to_add1 = 12 - factor_to_add;
        for (j = 0; j < 12; ++j)
          for (i = 0; i < 12; ++i)
             rowmatrix1[i][j] = (rowmatrix[i][j]+ factor_to_add1)%12;       
  
}


void randomly(void)
{
int i;
for (i = 0; i < 24; ++i)
{
player.i = rand()%(10)+1; // local area
player.j = rand()%(10)+1;
board[player.i][player.j] = 'x';
}
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
  for (j = 0; j < WIDTH;++j)
    for (i = 0; i < LENGTH; ++i)
    {
    if (board[i][j] == 'x')
     ++count_notes; 
    }   
}




void display1(void)
{
  int i,j;
  int count_notes = 0;
  for (j = 0; j < WIDTH;++j)
    for (i = 0; i < LENGTH; ++i)
    {
    if (board[i][j] == 'x')
     ++count_notes;     
   }   

/*

for (i = 0; i < LENGTH; ++i)      // this function is no good   LEAVE IT COMMENTED OUT 
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



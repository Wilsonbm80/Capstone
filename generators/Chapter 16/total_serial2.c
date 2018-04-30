#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "convert3.h"
#define GENERAL_MIDI_ON 1
#define PROGRAM_NUMBERS_ON 1

int prime[12] = {0,2,1,4,5,3,10,9,11,8,6,7}; 
int retrograde[12] = {7,6,8,11,9,10,3,5,4,1,2,0};
int retrogradeinversion[12] =  {5,6,4,1,3,2,9,7,8,11,10,12};
int inversion[12] = {12,10,11,8,7,9,2,3,1,4,6,5};

int prime_rhythm[12] =               {1,3,2,  2,1,3,  2,3,1,  3,1,2};
int retrograde_rhythm[12] =          {2,1,3,  1,3,2,  3,1,2,  2,3,1};
int retrogradeinversion_rhythm[12] = {2,3,1,  3,1,2,  1,3,2,  2,1,3};
int inversion_rhythm[12] =                  {3,1,2,  2,3,1,  2,1,3,  1,3,2};  



int p_rhythm_notes[24] =  {0,2,2,2,1,1,    4,4,5,3,3,3,    10,10,9,9,9,11,   8,8,8,6,7,7};
int r_rhythm_notes[24] =  {7,7,6,8,8,8,   11,9,9,9,10,10,  3,3,3,5,4,4,   1,1,2,2,2,0};
int ri_rhythm_notes[24] = {5,5,5,6,6,4,          1,1,1,3,2,2,      9,7,7,7,8,8,   11,11,10,12,12,12};
int i_rhythm_notes[24] =  {12,12,12,10,11,11,     8,8,7,7,7,9,       2,2,3,1,1,1,    4,6,6,6,5,5};
// new number plays pitch - when it changes old note cuts off and new note is played


int soprano_active;
int alto_active;
int tenor_active;
int bass_active;
int rhythm_counter;


int channel[8] = { 144, 145, 146, 147, 148, 149, 150, 151 };

int transposefactor1;
int transposefactor2;
int transposefactor3;
int transposefactor4;

int rhythm_counter = 0;
int old_pnote, new_pnote, old_rinote, new_rinote, old_rnote, new_rnote,
  old_inote, new_inote;



/* trichord rhythms: P = 1,3,2; R = 2,3,2: Let 4 = constant to get inversion. 
                     then I = 4-1=3, 4-3=1, 4-2=2; therefore RI = 2,1,3;

of row below and in program (0,7,4,1,10,5,6,9,2,3,8,11)
Row can be broken into four trichords each. 
Then Row P = P,RI,R,I trichords
and  Row I = I,R,RI,P trichords
and Row  R = RI,P,I,R trichords
and Row RI = R,I,P,RI trichords
thus rhythm derived for each row by the trichords. 
*/

/* trichordal combinatorial at P-0,I-1,R-0,RI-1
   and P-0,I-9,R-0,RI-9 
   Each P,I,R,RI that starts on C is different 
   0  7  4  1 10  5  6  9  2  3  8 11
  0C  G  E  C# A# F  F# A  D  D# G# B  
  5F  C  A  F# D# A# B  D  G  G# C# E  
  8G# D# C  A  F# C# D  F  A# B  E  G  
 11B  F# D# C  A  E  F  G# C# D  G  A# 
  2D  A  F# D# C  G  G# B  E  F  A# C# 
  7G  D  B  G# F  C  C# E  A  A# D# F# 
  6F# C# A# G  E  B  C  D# G# A  D  F  
  3D# A# G  E  C# G# A  C  F  F# B  D  
 10A# F  D  B  G# D# E  G  C  C# F# A  
  9A  E  C# A# G  D  D# F# B  C  F  G# 
  4E  B  G# F  D  A  A# C# F# G  C  D# 
  1C# G# F  D  B  F# G  A# D# E  A  C  
*/


/*
    trichordal combinatorial at P0,I3,R6,RI9
     P0=RI3, R3=I3    
   0  4  2  9  5  7  8 10  6  1 11  3
  0C  E  D  A  F  G  G# A# F# C# B  D# 
  8G# C  A# F  C# D# E  F# D  A  G  B  
 10A# D  C  G  D# F  F# G# E  B  A  C# 
  3D# G  F  C  G# A# B  C# A  E  D  F# 
  7G  B  A  E  C  D  D# F  C# G# F# A# 
  5F  A  G  D  A# C  C# D# B  F# E  G# 
  4E  G# F# C# A  B  C  D  A# F  D# G  
  2D  F# E  B  G  A  A# C  G# D# C# F  
  6F# A# G# D# B  C# D  E  C  G  F  A  
 11B  D# C# G# E  F# G  A  F  C  A# D  
  1C# F  D# A# F# G# A  B  G  D  C  E  
  9A  C# B  F# D  E  F  G  D# A# G# C  
*/


/*
  A good row - Trichoral 4 voice combinatorial at P-0,I-5,R-0,RI-0
  All forms of the rows that start on C are different.  

   0  2  1  4  5  3 10  9 11  8  6  7
  0C  D  C# E  F  D# A# A  B  G# F# G  
 10A# C  B  D  D# C# G# G  A  F# E  F  
 11B  C# C  D# E  D  A  G# A# G  F  F# 
  8G# A# A  C  C# B  F# F  G  E  D  D# 
  7G  A  G# B  C  A# F  E  F# D# C# D  
  9A  B  A# C# D  C  G  F# G# F  D# E  
  2D  E  D# F# G  F  C  B  C# A# G# A  
  3D# F  E  G  G# F# C# C  D  B  A  A# 
  1C# D# D  F  F# E  B  A# C  A  G  G# 
  4E  F# F  G# A  G  D  C# D# C  A# B  
  6F# G# G  A# B  A  E  D# F  D  C  C# 
  5F  G  F# A  A# G# D# D  E  C# B  C  

*/

/*
  Webern's row
   0 11  3  4  8  7  9  5  6  1  2 10
  0C  B  D# E  G# G  A  F  F# C# D  A# 
  1C# C  E  F  A  G# A# F# G  D  D# B  
  9A  G# C  C# F  E  F# D  D# A# B  G  
  8G# G  B  C  E  D# F  C# D  A  A# F# 
  4E  D# G  G# C  B  C# A  A# F  F# D  
  5F  E  G# A  C# C  D  A# B  F# G  D# 
  3D# D  F# G  B  A# C  G# A  E  F  C# 
  7G  F# A# B  D# D  E  C  C# G# A  F  
  6F# F  A  A# D  C# D# B  C  G  G# E  
 11B  A# D  D# G  F# G# E  F  C  C# A  
 10A# A  C# D  F# F  G  D# E  B  C  G# 
  2D  C# F  F# A# A  B  G  G# D# E  C  
*/

// kirk > picard 

void play_procedure (void);

int main (void)
{
  int i;
  int random_number;
  time_t t;
  open_midfiles ();
#if GENERAL_MIDI_ON
  general_midi ();
#endif
  srand ((unsigned) time (&t));
  play (48 * 2 * 4, 152 - 16, 100, 0);	/* Handshake */
  program_number[0] = 73;	//flute       
  program_number[1] = 14;	//tubular bells
  program_number[2] = 71;	//clarinet
  program_number[3] = 42;	//cello 
  program_number[4] = 0;
  program_number[5] = 0;
  program_number[6] = 0;
  program_number[7] = 0;
  program_setup ();
  play_procedure ();
  close_midfiles ();
  return (1);
}

void play_procedure (void)
{
  int i, j;
  for (j = 0; j < 20; ++j)
    {
      rhythm_counter = 0;
      new_pnote = p_rhythm_notes[rhythm_counter];
      new_rnote = r_rhythm_notes[rhythm_counter];
      new_inote = i_rhythm_notes[rhythm_counter];
      new_rinote = ri_rhythm_notes[rhythm_counter];
      transposefactor1 = 65 + (rand () % 12) + 6;
      transposefactor2 = 55 + (rand () % 12) + 6;
      transposefactor3 = 45 + (rand () % 12) + 6;
      transposefactor4 = 35 + (rand () % 12) + 6;

      play (0, 144, new_pnote + transposefactor1, 127);
      play (0, 145, new_rnote + transposefactor2, 127);
      play (0, 146, new_rinote + transposefactor3, 127);
      play (0, 147, new_inote + transposefactor4, 127);
      for (i = 1; i < 24; ++i)
	{
	  old_pnote = new_pnote;
	  old_rnote = new_rnote;
	  old_inote = new_inote;
	  old_rinote = new_rinote;
	  ++rhythm_counter;
	  if (rhythm_counter == 24)
	    rhythm_counter = 0;

	  play (100, 152 - 16, 100, 0);
	  new_pnote = p_rhythm_notes[rhythm_counter];
	  new_rnote = r_rhythm_notes[rhythm_counter];
	  new_rinote = ri_rhythm_notes[rhythm_counter];
	  new_inote = i_rhythm_notes[rhythm_counter];
	  if (new_pnote != old_pnote)
	    {
	      play (0, 144 - 16, old_pnote + transposefactor1, 0);
	      play (0, 144, new_pnote + transposefactor1, 127);
	    }
	  if (new_rnote != old_rnote)
	    {
	      play (0, 145 - 16, old_rnote + transposefactor2, 0);
	      play (0, 145, new_rnote + transposefactor2, 127);
	    }
	  if (new_inote != old_inote)
	    {
	      play (0, 147 - 16, old_inote + transposefactor4, 0);
	      play (0, 147, new_inote + transposefactor4, 127);
	    }
	  if (new_rinote != old_rinote)
	    {
	      play (0, 146 - 16, old_rinote + transposefactor3, 0);
	      play (0, 146, new_rinote + transposefactor3, 127);
	    }


	}
      play (100, 152 - 16, 100, 0);
      old_pnote = new_pnote;
      old_rnote = new_rnote;
      old_inote = new_inote;
      old_rinote = new_rinote;
      play (0, 144 - 16, old_pnote + transposefactor1, 0);
      play (0, 145 - 16, old_rnote + transposefactor2, 0);
      play (0, 147 - 16, old_inote + transposefactor4, 0);
      play (0, 146 - 16, old_rinote + transposefactor3, 0);

    }
}

//medieval.c
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "convert3.h"
#define D4 62
#define Eb4 63
#define E4 64
#define F4 65
#define Fs4 66
#define G4 67
#define Ab4 68
#define A4 69
#define Bb4 70
#define B4 71
#define C5 72
#define Cs5 73
#define D5 74
#define Eb5 75
#define E5 76
#define F5 77
#define Fs5 78
#define G5 79
#define RHYTHM_NUM 4
#define EVENT 3
#define TONIC 3
#define MODETYPE  6
#define PITCHES  8
#define RHYTHMPATTERN 4
int rhythmarray_a[RHYTHMPATTERN];
int rhythmarray1_a[RHYTHMPATTERN];
int rhythmarray_b[RHYTHMPATTERN];
int rhythmarray1_b[RHYTHMPATTERN];
int rhythmarray_c[RHYTHMPATTERN];
int rhythmarray1_c[RHYTHMPATTERN];
int note, tempnote;
int random_variable;
int counter;
int found;
int pitch, typemode;
int rhythmic_pattern_a[4];
int entire_rhythm_a[12];
int rhythmic_pattern_b[4];
int entire_rhythm_b[12];
int rhythmic_pattern_c[4];
int entire_rhythm_c[12];
int total_notes_a;
int total_notes_b;
int total_notes_c;
int complete_a[12];
int complete_b[12];
int complete_c[12];











int mode[6][11] = { {D4, E4, Fs4, G4, A4, B4, C5, D5},	/* (where G4, the 3rd element (counting 0) = the Tonic */
{D4, E4, F4, G4, A4, Bb4, C5, D5},	/* (where G4, the 3rd element (counting 0) = the Tonic */
{D4, Eb4, F4, G4, Ab4, Bb4, C5, D5},	/* (where G4, the 3rd element (counting 0) = the Tonic */
{D4, E4, Fs4, G4, A4, B4, Cs5, D5},	/* (where G4, the 3rd element (counting 0) = the Tonic */
{D4, E4, F4, G4, A4, B4, C5, D5},	/* (where G4, the 3rd element (counting 0) = the Tonic */
{D4, Eb4, F4, G4, A4, Bb4, C5, D5}
};				/* (where G4, the 3rd element (counting 0) = the Tonic */



int rhythmic_mode[RHYTHM_NUM][EVENT] = { {1, 0, 1,},
                                         {1, 1, 0,},
                                         {1, 1, 1,},
                                         {1, 0, 0,}
                                       };


int melody_maxa[20];		/* Form of Virelai of Trouveres (4 measures of 3 eighth notes = one phrase where last measure is 4th rhythmic mode */
				   /* First phrase = a, then b, then c, c', a', b', a'', b''   NEED 4 complete measures of 3/8 */
				   /* "a" section =  random rhythmic mode of any of first three in any measure, first measure beings on tonic and last measure = 4th rhythmic mode */
				   /* "b" section =  random rhythmic mode of any of first three in any measure, except last measure ends on Tonic AND last measure = 4th rhythmic mode */
				   /* "c" section = random rhythmic mode of any of first four in any measure, and last note = 4th rhythmic mode, also first and last notes same */



int melody_maxb[20];
int melody_maxc[20];



void make_melody (void);
void make_rhythm (void);
void section_a (void);
void section_b (void);
void section_c (void);
void put_melody_into_rhythm (void);
void playmusic (void);



int main (void)
{
  int i;
  int rhythmic_pattern_a[4];
  int rhythmic_pattern_b[4];
  int rhythmic_pattern_c[4];
  time_t t;
  srand ((unsigned) time (&t));
  open_midfiles ();
  general_midi ();
  typemode = rand () % (MODETYPE);
  program_number[0] = 68;	/*oboe */
  program_number[1] = 74;	/*bottle_flute */
  program_number[2] = 0;
  program_number[3] = 0;
  program_number[4] = 0;
  program_number[5] = 0;
  program_number[6] = 0;
  program_number[7] = 0;
  program_setup ();

  play (48 * 2 * 4, 152 - 16, 100, 0);	/* Handshake */
  section_a ();
  section_b ();
  section_c ();
  make_melody ();
  put_melody_into_rhythm ();

  playmusic ();
  close_midfiles ();
  return (1);
}

void make_melody (void)
{
  int i;
  int secondarytonic;
  note = TONIC;

  counter = 0;
  melody_maxa[counter] = mode[typemode][note];
  do
    {
      random_variable = rand () % (100);
      found = 0;
      if (random_variable < 40)
	tempnote = note + 1;
      else if (random_variable < 80)
	tempnote = note - 1;
      else if (random_variable < 88)
	tempnote = note + 2;
      else if (random_variable < 96)
	tempnote = note - 2;
      else
	tempnote = note;
      if (tempnote > -1 && tempnote < 8)
	found = 1;
      if (found == 1)
	{
	  note = tempnote;
	  ++counter;
	  melody_maxa[counter] = mode[typemode][note];
	}
    }
  while (counter < total_notes_a - 1);

  note = rand () % (8);
  counter = 0;
  melody_maxb[counter] = mode[typemode][note];
  do
    {
      random_variable = rand () % (100);
      found = 0;
      if (random_variable < 40)
	tempnote = note + 1;
      else if (random_variable < 80)
	tempnote = note - 1;
      else if (random_variable < 88)
	tempnote = note + 2;
      else if (random_variable < 96)
	tempnote = note - 2;
      else
	tempnote = note;
      if (tempnote > -1 && tempnote < 8)
	found = 1;
      if (found == 1)
	{
	  note = tempnote;
	  ++counter;
	  melody_maxb[counter] = mode[typemode][note];
	}
    }
  while (counter < total_notes_b - 1);

  note = TONIC;
  melody_maxb[total_notes_b - 1] = mode[typemode][TONIC];


  note = rand () % (8);
  secondarytonic = note;
  counter = 0;
  melody_maxc[counter] = mode[typemode][note];
  do
    {
      random_variable = rand () % (100);
      found = 0;
      if (random_variable < 40)
	tempnote = note + 1;
      else if (random_variable < 80)
	tempnote = note - 1;
      else if (random_variable < 88)
	tempnote = note + 2;
      else if (random_variable < 96)
	tempnote = note - 2;
      else
	tempnote = note;
      if (tempnote > -1 && tempnote < 8)
	found = 1;
      if (found == 1)
	{
	  note = tempnote;
	  ++counter;
	  melody_maxc[counter] = mode[typemode][note];
	}
    }
  while (counter < total_notes_c - 1);

  note = TONIC;
  melody_maxc[total_notes_c - 1] = mode[typemode][secondarytonic];
}

void section_a (void)
{
  int subtotal = 0;
  int i;
  rhythmic_pattern_a[0] = rand () % (3);
  rhythmic_pattern_a[1] = rand () % (3);
  rhythmic_pattern_a[2] = rand () % (3);
  rhythmic_pattern_a[3] = 3;
  for (i = 0; i < 3; ++i)
    {
      if (rhythmic_mode[rhythmic_pattern_a[0]][i] == 1)
	++subtotal;
    }
  for (i = 0; i < 3; ++i)
    {
      if (rhythmic_mode[rhythmic_pattern_a[1]][i] == 1)
	++subtotal;
    }
  for (i = 0; i < 3; ++i)
    {
      if (rhythmic_mode[rhythmic_pattern_a[2]][i] == 1)
	++subtotal;
    }
  for (i = 0; i < 3; ++i)
    {
      if (rhythmic_mode[rhythmic_pattern_a[3]][i] == 1)
	++subtotal;
    }
  total_notes_a = subtotal;
  for (i = 0; i < 3; ++i)
    entire_rhythm_a[i] = rhythmic_mode[rhythmic_pattern_a[0]][i];
  for (i = 3; i < 6; ++i)
    entire_rhythm_a[i] = rhythmic_mode[rhythmic_pattern_a[1]][i - 3];
  for (i = 6; i < 9; ++i)
    entire_rhythm_a[i] = rhythmic_mode[rhythmic_pattern_a[2]][i - 6];
  for (i = 9; i < 12; ++i)
    entire_rhythm_a[i] = rhythmic_mode[rhythmic_pattern_a[3]][i - 9];
}

void section_b (void)
{
  int subtotal = 0;
  int i;
  rhythmic_pattern_b[0] = rand () % (3);
  rhythmic_pattern_b[1] = rand () % (3);
  rhythmic_pattern_b[2] = rand () % (3);
  rhythmic_pattern_b[3] = 3;
  for (i = 0; i < 3; ++i)
    {
      if (rhythmic_mode[rhythmic_pattern_b[0]][i] == 1)
	++subtotal;
      if (rhythmic_mode[rhythmic_pattern_b[1]][i] == 1)
	++subtotal;
      if (rhythmic_mode[rhythmic_pattern_b[2]][i] == 1)
	++subtotal;
      if (rhythmic_mode[rhythmic_pattern_b[3]][i] == 1)
	++subtotal;
    }
  total_notes_b = subtotal;
  for (i = 0; i < 3; ++i)
    entire_rhythm_b[i] = rhythmic_mode[rhythmic_pattern_b[0]][i];
  for (i = 3; i < 6; ++i)
    entire_rhythm_b[i] = rhythmic_mode[rhythmic_pattern_b[1]][i - 3];
  for (i = 6; i < 9; ++i)
    entire_rhythm_b[i] = rhythmic_mode[rhythmic_pattern_b[2]][i - 6];
  for (i = 9; i < 12; ++i)
    entire_rhythm_b[i] = rhythmic_mode[rhythmic_pattern_b[3]][i - 9];
}

void section_c (void)
{
  int subtotal = 0;
  int i;
  rhythmic_pattern_c[0] = rand () % (3);
  rhythmic_pattern_c[1] = rand () % (3);
  rhythmic_pattern_c[2] = rand () % (3);
  rhythmic_pattern_c[3] = 3;
  for (i = 0; i < 3; ++i)
    {
      if (rhythmic_mode[rhythmic_pattern_c[0]][i] == 1)
	++subtotal;
      if (rhythmic_mode[rhythmic_pattern_c[1]][i] == 1)
	++subtotal;
      if (rhythmic_mode[rhythmic_pattern_c[2]][i] == 1)
	++subtotal;
      if (rhythmic_mode[rhythmic_pattern_c[3]][i] == 1)
	++subtotal;
    }
  total_notes_c = subtotal;
  for (i = 0; i < 3; ++i)
    entire_rhythm_c[i] = rhythmic_mode[rhythmic_pattern_c[0]][i];
  for (i = 3; i < 6; ++i)
    entire_rhythm_c[i] = rhythmic_mode[rhythmic_pattern_c[1]][i - 3];
  for (i = 6; i < 9; ++i)
    entire_rhythm_c[i] = rhythmic_mode[rhythmic_pattern_c[2]][i - 6];
  for (i = 9; i < 12; ++i)
    entire_rhythm_c[i] = rhythmic_mode[rhythmic_pattern_c[3]][i - 9];
}

void put_melody_into_rhythm (void)
{
  /* what you need  - entire_rhythm_c, entire_rhythm_b, entire_rhythm_a, melodymaxa,melodymaxb,melodymaxc, complete_a, complete_b, complete_c - remember 4 measures of 6 beats each section */
  int i;
  counter = 0;
  for (i = 0; i < 12; ++i)
    if (entire_rhythm_a[i] == 1)
      {
	complete_a[i] = melody_maxa[counter];
	++counter;
      }
    else
      complete_a[i] = 0;


  counter = 0;
  for (i = 0; i < 12; ++i)
    if (entire_rhythm_b[i] == 1)
      {
	complete_b[i] = melody_maxb[counter];
	++counter;
      }
    else
      complete_b[i] = 0;


  counter = 0;
  for (i = 0; i < 12; ++i)
    if (entire_rhythm_c[i] == 1)
      {
	complete_c[i] = melody_maxc[counter];
	++counter;
      }
    else
      complete_c[i] = 0;
}



void playmusic (void)
{
  int i;
  int previous_note = complete_a[0];
  int current_note = complete_a[0];



  for (i = 0; i < 12; ++i)
    {
      if (complete_a[i] == 0)

	play(48,152-16,100,0);
      else
	{
	  current_note = complete_a[i];
	  play (0, 144 - 16, previous_note, 0);
	  play (0, 144, current_note, 127);
	  if (i == 0)
	    {
	      play (0, 145, complete_a[0] - 12, 127);
	      play (0, 145, complete_a[0] - 12 + 7, 127);
	    }
	  if (i == 9)
	    {
	      play (0, 145 - 16, complete_a[0] - 12, 0);
	      play (0, 145 - 16, complete_a[0] - 12 + 7, 0);
	      play (0, 145, complete_a[9] - 12, 127);
	      play (0, 145, complete_a[9] - 12 + 7, 127);
	    }
	  play(48,152-16,100,0);
	  previous_note = current_note;
	}
    }
/* after the loop */
  play (0, 145 - 16, complete_a[9] - 12, 0);
  play (0, 145 - 16, complete_a[9] - 12 + 7, 0);
  play (0, 144 - 16, current_note, 0);

  previous_note = complete_b[0];
  current_note = complete_b[0];

  for (i = 0; i < 12; ++i)
    {
      if (complete_b[i] == 0)

	play(48,152-16,100,0);
      else
	{
	  current_note = complete_b[i];
	  play (0, 144 - 16, previous_note, 0);
	  play (0, 144, current_note, 127);
	  if (i == 0)
	    {
	      play (0, 145, complete_b[0] - 12, 127);
	      play (0, 145, complete_b[0] - 12 + 7, 127);
	    }
	  if (i == 9)
	    {
	      play (0, 145 - 16, complete_b[0] - 12, 0);
	      play (0, 145 - 16, complete_b[0] - 12 + 7, 0);
	      play (0, 145, complete_b[9] - 12, 127);
	      play (0, 145, complete_b[9] - 12 + 7, 127);
	    }
          play(48,152-16,100,0);
	  previous_note = current_note;
	}
    }
/* after the loop */
  play (0, 144 - 16, current_note, 0);
  play (0, 145 - 16, complete_b[9] - 12, 0);
  play (0, 145 - 16, complete_b[9] - 12 + 7, 0);

  previous_note = complete_c[0];
  current_note = complete_c[0];
  for (i = 0; i < 12; ++i)
    {
      if (complete_c[i] == 0)

	play(48,152-16,100,0);
      else
	{
	  current_note = complete_c[i];
	  play (0, 144 - 16, previous_note, 0);
	  play (0, 144, current_note, 127);
	  if (i == 0)
	    {
	      play (0, 145, complete_c[0] - 12, 127);
	      play (0, 145, complete_c[0] - 12 + 7, 127);
	    }
	  if (i == 9)
	    {
	      play (0, 145 - 16, complete_c[0] - 12, 0);
	      play (0, 145 - 16, complete_c[0] - 12 + 7, 0);
	      play (0, 145, complete_c[9] - 12, 127);
	      play (0, 145, complete_c[9] - 12 + 7, 127);
	    }
          play(48,152-16,100,0);
	  previous_note = current_note;
	}
    }
/* after the loop */
  play (0, 144 - 16, current_note, 0);
  play (0, 145 - 16, complete_c[9] - 12, 0);
  play (0, 145 - 16, complete_c[9] - 12 + 7, 0);

  previous_note = complete_c[0];
  current_note = complete_c[0];
  for (i = 0; i < 12; ++i)
    {
      if (complete_c[i] == 0)

	play(48,152-16,100,0);
      else
	{
	  current_note = complete_c[i];
	  play (0, 144 - 16, previous_note, 0);
	  play (0, 144, current_note, 127);
	  if (i == 0)
	    {
	      play (0, 145, complete_c[0] - 12, 127);
	      play (0, 145, complete_c[0] - 12 + 7, 127);
	    }
	  if (i == 9)
	    {
	      play (0, 145 - 16, complete_c[0] - 12, 0);
	      play (0, 145 - 16, complete_c[0] - 12 + 7, 0);
	      play (0, 145, complete_c[9] - 12, 127);
	      play (0, 145, complete_c[9] - 12 + 7, 127);
	    }
	  play(48,152-16,100,0);
	  previous_note = current_note;
	}
    }
/* after the loop */
  play (0, 144 - 16, current_note, 0);
  play (0, 145 - 16, complete_c[9] - 12, 0);
  play (0, 145 - 16, complete_c[9] - 12 + 7, 0);

  previous_note = complete_a[0];
  current_note = complete_a[0];

  for (i = 0; i < 12; ++i)
    {
      if (complete_a[i] == 0)

	play(48,152-16,100,0);
      else
	{
	  current_note = complete_a[i];
	  play (0, 144 - 16, previous_note, 0);
	  play (0, 144, current_note, 127);
	  if (i == 0)
	    {
	      play (0, 145, complete_a[0] - 12, 127);
	      play (0, 145, complete_a[0] - 12 + 7, 127);
	    }
	  if (i == 9)
	    {
	      play (0, 145 - 16, complete_a[0] - 12, 0);
	      play (0, 145 - 16, complete_a[0] - 12 + 7, 0);
	      play (0, 145, complete_a[9] - 12, 127);
	      play (0, 145, complete_a[9] - 12 + 7, 127);
	    }
	  play(48,152-16,100,0);
	  previous_note = current_note;
	}
    }
/* after the loop */
  play (0, 145 - 16, complete_a[9] - 12, 0);
  play (0, 145 - 16, complete_a[9] - 12 + 7, 0);
  play (0, 144 - 16, current_note, 0);

  previous_note = complete_b[0];
  current_note = complete_b[0];

  for (i = 0; i < 12; ++i)
    {
      if (complete_b[i] == 0)

	play(48,152-16,100,0);
      else
	{
	  current_note = complete_b[i];
	  play (0, 144 - 16, previous_note, 0);
	  play (0, 144, current_note, 127);
	  if (i == 0)
	    {
	      play (0, 145, complete_b[0] - 12, 127);
	      play (0, 145, complete_b[0] - 12 + 7, 127);
	    }
	  if (i == 9)
	    {
	      play (0, 145 - 16, complete_b[0] - 12, 0);
	      play (0, 145 - 16, complete_b[0] - 12 + 7, 0);
	      play (0, 145, complete_b[9] - 12, 127);
	      play (0, 145, complete_b[9] - 12 + 7, 127);
	    }
	  play(48,152-16,100,0);
	  previous_note = current_note;
	}
    }
/* after the loop */
  play (0, 144 - 16, current_note, 0);
  play (0, 145 - 16, complete_b[9] - 12, 0);
  play (0, 145 - 16, complete_b[9] - 12 + 7, 0);

  previous_note = complete_a[0];
  current_note = complete_a[0];

  for (i = 0; i < 12; ++i)
    {
      if (complete_a[i] == 0)

	play(48,152-16,100,0);
      else
	{
	  current_note = complete_a[i];
	  play (0, 144 - 16, previous_note, 0);
	  play (0, 144, current_note, 127);
	  if (i == 0)
	    {
	      play (0, 145, complete_a[0] - 12, 127);
	      play (0, 145, complete_a[0] - 12 + 7, 127);
	    }
	  if (i == 9)
	    {
	      play (0, 145 - 16, complete_a[0] - 12, 0);
	      play (0, 145 - 16, complete_a[0] - 12 + 7, 0);
	      play (0, 145, complete_a[9] - 12, 127);
	      play (0, 145, complete_a[9] - 12 + 7, 127);
	    }
	  play(48,152-16,100,0);
	  previous_note = current_note;
	}
    }
/* after the loop */
  play (0, 145 - 16, complete_a[9] - 12, 0);
  play (0, 145 - 16, complete_a[9] - 12 + 7, 0);
  play (0, 144 - 16, current_note, 0);

  previous_note = complete_b[0];
  current_note = complete_b[0];

  for (i = 0; i < 12; ++i)
    {
      if (complete_b[i] == 0)

	play(48,152-16,100,0);
      else
	{
	  current_note = complete_b[i];
	  play (0, 144 - 16, previous_note, 0);
	  play (0, 144, current_note, 127);
	  if (i == 0)
	    {
	      play (0, 145, complete_b[0] - 12, 127);
	      play (0, 145, complete_b[0] - 12 + 7, 127);
	    }
	  if (i == 9)
	    {
	      play (0, 145 - 16, complete_b[0] - 12, 0);
	      play (0, 145 - 16, complete_b[0] - 12 + 7, 0);
	      play (0, 145, complete_b[9] - 12, 127);
	      play (0, 145, complete_b[9] - 12 + 7, 127);
	    }
	  play(48,152-16,100,0);
	  previous_note = current_note;
	}
    }
/* after the loop */
  play (0, 144 - 16, current_note, 0);
  play (0, 145 - 16, complete_b[9] - 12, 0);
  play (0, 145 - 16, complete_b[9] - 12 + 7, 0);

}

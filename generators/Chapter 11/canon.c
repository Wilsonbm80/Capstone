/* canon.c - produces 4 voice canon with 3 voice rhythm parts  */
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "convert3.h"
#define PATTERNLENGTH 3
#define INTERVAL 3
#define NUM_VOICES 4
#define RHYTHMPATTERN 6
#define RHYTHMPATTERN1 7
#define RHYTHMPATTERN2 8
#define GENERAL_MIDI_ON 1
#define PROGRAM_NUMBERS_ON 1
#define PERCUSSION_SECTION_ON 1
int scale[128];
int notes[128];
int rhythmarray[RHYTHMPATTERN];
int rhythmarray1[RHYTHMPATTERN1];
int rhythmarray2[RHYTHMPATTERN2];
int rhythmmarker;
int rhythmmarker1;
int rhythmmarker2;
int notelength;
int noteindex;
int num_patterns;
int notes_in_patterns;
int melody[100];
int canon[8][100];
int canon1[8][100];
int transposefactor;
void makerhythmiccanon (void);
void setup (void);
void makemelody (void);
void makecanon (int timedelay);
void playcanon (void);
void canonicsection (void);
int main (void)
{
  time_t t;
  open_midfiles ();
#if GENERAL_MIDI_ON
  general_midi ();
#endif
  srand ((unsigned) time (&t));
  program_number[0] = 48;
  program_number[1] = 88;
  program_number[2] = 48;
  program_number[3] = 88;
  program_number[4] = 0;
  program_number[5] = 0;
  program_number[6] = 0;
  program_number[7] = 0;
  program_setup ();
  play (48 * 2 * 4, 152 - 16, 100, 0);	/* Handshake */
  do
    {
      setup ();
    }
  while (num_patterns < NUM_VOICES);
  canonicsection ();
  close_midfiles ();
  return (1);
}

void setup (void)
{
  int i;
  int pattern[PATTERNLENGTH];
  int scalecounter;
  for (i = 0; i < 128; ++i)
    {
      scale[i] = 128;
      notes[i] = 128;
    }
  notelength = 0;
/*  for (i = 0; i < PATTERNLENGTH; ++i) 
pattern[i] = rand()%(INTERVAL) + 1; */
  rhythmmarker = 0;
  rhythmmarker1 = 0;
  rhythmmarker2 = 0;
/* This will make the scale sound Egyptian. */
/* Make sure PATTERNLENGTH is set to 4 */
/* pattern[0] = 1; 
pattern[1] = 3; 
pattern[2] = 1; 
pattern[3] = 2;  */
/*  To make it Petatonic try this. */
/* First you will make the PATTERNLENGTH set to 3 */
  pattern[0] = 2;
  pattern[1] = 3;
  pattern[2] = 2;

/* For a different scale each time the program is run try this */
/*  for (i = 0; i < PATTERNLENGTH; ++i) 
		 pattern[i] = rand()%(INTERVAL) + 1; */
  scalecounter = 0;
  scale[scalecounter] = 1;
  do
    {
      for (i = 0; i < PATTERNLENGTH; ++i)
	{
	  scalecounter = scalecounter + pattern[i];
	  if (scalecounter < 128)
	    scale[scalecounter] = 1;
	}
      for (i = PATTERNLENGTH - 2; i >= 0; --i)
	{
	  scalecounter = scalecounter + pattern[i];
	  if (scalecounter < 128)
	    scale[scalecounter] = 1;
	}
    }
  while (scalecounter < 128);
  for (i = 0; i < 128; ++i)
    {
      if (scale[i] == 1)
	{
	  notes[notelength] = i;
	  ++notelength;
	}
    }
  transposefactor = notes[PATTERNLENGTH * 2 - 1];
  num_patterns = notelength / (PATTERNLENGTH * 2 - 1);
  notes_in_patterns = PATTERNLENGTH * 2 - 1;
}

void makemelody (void)
{
  int i;
  int beginning_of_pattern;
  int direction;
  int temp = 0;
  beginning_of_pattern = 0;
  noteindex = beginning_of_pattern + rand () % (notes_in_patterns);
  melody[0] = -1;		/* first note not played */
  for (i = 1; i < 100; ++i)
    {
      direction = rand () % (6);
      if (direction <= 2)
	{
	  if (temp == -1)
	    {
	      if (rand () % (2))
		(temp = -1);
	      else
		(temp = 0);
	    }
	  else if (noteindex - 1 < beginning_of_pattern)
	    noteindex = beginning_of_pattern + rand () % (notes_in_patterns);
	  else
	    --noteindex;
	}
      else if (direction == 3)
	{
	  temp = 0;
	  if (noteindex == beginning_of_pattern + notes_in_patterns - 1)
	    --noteindex;
	  else
	    ++noteindex;
	}
      else if (direction == 4)
	(temp = -1);
      else if (direction == 5)
	{
	  noteindex = noteindex;
	  temp = 0;
	}
      if (temp == -1)
	melody[i] = -1;
      else
	melody[i] = notes[noteindex];
    }
}

void makecanon (int timedelay)
{
  int i, j, k;
  int transpose[8];
  int duplicate;
  int randomconstant;
  for (i = 0; i < RHYTHMPATTERN; ++i)
    rhythmarray[i] = rand () % (timedelay);
  for (i = 0; i < RHYTHMPATTERN1; ++i)
    rhythmarray1[i] = rand () % (timedelay);
  for (i = 0; i < RHYTHMPATTERN2; ++i)
    rhythmarray2[i] = rand () % (timedelay);
  randomconstant = rand () % (12);
/*so each section will be in different 'key'*/
  for (i = 0; i < NUM_VOICES; ++i)
    {
      do
	{
	  duplicate = 0;
	  transpose[i] = (rand () % (NUM_VOICES) + num_patterns / 2
			  - NUM_VOICES / 2) * transposefactor +
	    randomconstant;
	  for (j = 0; j < i; ++j)
	    if (transpose[i] == transpose[j])
	      duplicate = 1;
	}
      while (duplicate);
    }
  for (j = 0; j < NUM_VOICES; ++j)
    for (i = 0; i < 100; ++i)
      canon[j][i] = -1;
  for (j = 0; j < NUM_VOICES; ++j)
    for (i = 0; i < 100; ++i)
      {
	k = i + timedelay * j;
	if (k < 100)
	  if (melody[i] != -1)
	    canon[j][k] = melody[i] + transpose[j];
	  else
	    canon[j][k] = -1;
      }
}

void makerhythmiccanon (void)
{
  int i, j, k, l, randomnumber, count;
  for (i = 0; i < 100; ++i)
    for (j = 0; j < NUM_VOICES; ++j)
      canon1[j][i] = -1;
  count = 0;
  for (l = 0; l < 25; ++l)
    {
      randomnumber = rand () % (40) + 50;
      for (k = 0; k < 5; ++k)
	for (i = randomnumber; i < randomnumber + rand () % (5) + 5; ++i)
	  {
	    for (j = 0; j < NUM_VOICES; ++j)
	      if (count < 100)
		canon1[j][count] = canon[j][(i + j + k) % 100];
	    ++count;
	  }
    }
}

void playcanon (void)
{
  int i, j;
  int temp;
  for (i = 0; i < 99; ++i)
    {
      for (j = 0; j < NUM_VOICES; ++j)
	{
	  if (canon[j][i + 1] == -1 && canon[j][i] != -1)
	    {
	      play (0, 144 + j - 16, canon[j][i], 0);
	    }
	  if (canon[j][i + 1] > -1 && canon[j][i] > -1 &&
	      canon[j][i + 1] != canon[j][i])
	    {
	      if (canon[j][i] > 20 && canon[j][i] < 100)
		play (0, 144 + j - 16, canon[j][i], 100);
	      if (canon[j][i + 1] > 20 && canon[j][i + 1] < 100)
		play (0, 144 + j, canon[j][i + 1], 100);
	    }
	}
      temp = 24;
#if PERCUSSION_SECTION_ON
      if (rhythmarray[rhythmmarker] == 1)
	{
	  play (0, 153, 60, 100);
	  play (24, 152 - 16, 1, 0);
	  play (0, 153 - 16, 60, 0);
	  temp = 0;
	}
      ++rhythmmarker;
      if (rhythmmarker == RHYTHMPATTERN)
	rhythmmarker = 0;
      if (rhythmarray[rhythmmarker] == 1)
	play (0, 153, 60, 100);
      if (rhythmarray1[rhythmmarker1] == 1)
	play (0, 153, 62, 100);
      if (rhythmarray2[rhythmmarker2] == 1)
	play (0, 153, 64, 100);
#endif
      play (24 + temp, 152 - 16, 1, 0);
#if PERCUSSION_SECTION_ON
      if (rhythmarray[rhythmmarker] == 1)
	play (0, 153 - 16, 60, 0);
      if (rhythmarray1[rhythmmarker1] == 1)
	play (0, 153 - 16, 62, 0);
      if (rhythmarray2[rhythmmarker2] == 1)
	play (0, 153 - 16, 64, 0);
#endif
      ++rhythmmarker;
      if (rhythmmarker == RHYTHMPATTERN)
	rhythmmarker = 0;
      ++rhythmmarker1;
      if (rhythmmarker1 == RHYTHMPATTERN1)
	rhythmmarker1 = 0;
      ++rhythmmarker2;
      if (rhythmmarker2 == RHYTHMPATTERN2)
	rhythmmarker2 = 0;
    }
  for (j = 0; j < NUM_VOICES; ++j)
    if (canon[j][99] != -1)
      play (0, 144 + j - 16, canon[j][99], 0);
}

void canonicsection (void)
{
  int timedelay;
  int i;
  makemelody ();
  for (i = 8; i > 2; i = i - 2)
/* REMEMBER timedelay MUST be 2 or greater for 
random function to work in the play function */
    {
      timedelay = i;
      makecanon (timedelay);
      makerhythmiccanon ();
      playcanon ();
      playcanon ();
    }
}

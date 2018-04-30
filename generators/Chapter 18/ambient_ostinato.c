//ambient_ostinato.c
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "convert3.h"
#define GENERAL_MIDI_ON 1
#define PROGRAM_NUMBERS_ON 1
#define F3 53
#define TONIC 53
int chords[3] = { TONIC, TONIC + 3, TONIC + 7 };
int minor_scale[8] =
  { TONIC + 12, TONIC + 12 + 2, TONIC + 12 + 3, TONIC + 12 + 5,
TONIC + 12 + 7, TONIC + 12 + 8, TONIC + 12 + 10, TONIC + 12 + 12 };
int array0[8];
// kirk > picard 
int channel[8] = { 144, 145, 146, 147, 148, 149, 150, 151 };

int transposefactor;
int melody[8];
void changing_order_minor_scale (void);
void play_procedure1 (void);
int
main (void)
{
  int i;
  int success;
  int random_number;
  int temp_transposefactor;

  time_t t;
  open_midfiles ();
#if GENERAL_MIDI_ON
  general_midi ();
#endif
  srand ((unsigned) time (&t));
  play (48 * 2 * 4, 152 - 16, 100, 0);	/* Handshake */
  program_number[0] = 48;	/* strings */
  program_number[1] = 14;	/* tubular bells */
  program_number[2] = 0;
  program_number[3] = 0;
  program_number[4] = 0;
  program_number[5] = 0;
  program_number[6] = 0;
  program_number[7] = 0;
  program_setup ();
  changing_order_minor_scale ();
  transposefactor = 0;
  play_procedure1 ();
  for (i = 0; i < 12; ++i)
    {
      do
	{
	  success = 0;
	  int up = rand () % 2;
	  if (up)
	    temp_transposefactor = (rand () % 3) + 1;
	  else
	    temp_transposefactor = (rand () % 3) - 3;
	  if (transposefactor + temp_transposefactor < 6
	      && transposefactor + temp_transposefactor > -6)
	    success = 1;
	}
      while (success == 0);
      transposefactor = temp_transposefactor + transposefactor;
      play_procedure1 ();
    }
  transposefactor = 0;
  play_procedure1 ();
  close_midfiles ();
  return (1);
}

void
changing_order_minor_scale (void)
{
// THIS IS TO CHANGE THE INDEX SO EACH NUMBER IS ASSIGNED A UNIQUE NUMBER DIFFERENT, RANDOM ASSIGNMENT EACH TIME 
  int number;
  int counter = 0;
  int success;
  int i;
  number = rand () % 8;
  array0[counter] = number;
  ++counter;
  do
    {
      success = 1;
      number = rand () % 8;
      for (i = 0; i < counter; ++i)
	{
	  if (array0[i] == number)
	    {
	      success = 0;
	    }
	}
      if (success == 1)
	{
	  array0[counter] = number;
	  counter++;
	}
    }
  while (success == 0 || counter < 8);
  for (i = 0; i < 8; ++i)
    melody[i] = minor_scale[array0[i]];
}

void
play_procedure1 (void)
{
  int i;
  for (i = 0; i < 3; ++i)
    play (0, 144, chords[i] + transposefactor, 100);	// strings for chords   
  for (i = 0; i < 8; ++i)
    {
      play (0, 145, (melody[i]), 127);
      play (120, 152 - 16, 100, 0);
      play (0, 145 - 16, (melody[i]), 0);
    }
  for (i = 0; i < 3; ++i)
    play (0, 144 - 16, chords[i] + transposefactor, 0);	// turn off chords 
}

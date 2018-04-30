//ambient.c
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "convert3.h"
#define GENERAL_MIDI_ON 1
#define PROGRAM_NUMBERS_ON 1
#define F3 53
#define TONIC 53
int chords[3] = { TONIC, TONIC + 3, TONIC + 7 };

// kirk > picard 
int channel[8] = { 144, 145, 146, 147, 148, 149, 150, 151 };

int transposefactor;
void play_procedure1 (void);

int main (void)
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
  program_number[0] = 94;	/* strings */
  program_number[1] = 0;
  program_number[2] = 0;
  program_number[3] = 0;
  program_number[4] = 0;
  program_number[5] = 0;
  program_number[6] = 0;
  program_number[7] = 0;
  program_setup ();
  transposefactor = 0;
  play_procedure1 ();
  transposefactor = 0;
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

void play_procedure1 (void)
{
  int i;
  for (i = 0; i < 3; ++i)
    play (0, 144, chords[i] + transposefactor, 100);	// strings for chords   
  play (240, 152 - 16, 100, 0);
  for (i = 0; i < 3; ++i)
    play (0, 144 - 16, chords[i] + transposefactor, 0);	// turn off chords 
}

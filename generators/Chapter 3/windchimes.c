/* windchimes.c */
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "convert3.h"
#define GENERAL_MIDI_ON 1
#define PROGRAM_NUMBERS_ON 1
#define LYDIAN_SCALE 0
#define PENTATONIC_SCALE 1
#define WHOLE_TONE_SCALE 2
int lydian[] =
  { 40 - 12, 42 - 12, 44 - 12, 46 - 12, 47 - 12, 49 - 12, 51 - 12, 52 - 12 };
int pentatonic[] = { 40 - 12, 42 - 12, 44 - 12, 47 - 12, 49 - 12, 52 - 12 };
int whole_tone[] =
  { 40 - 18, 42 - 18, 44 - 18, 46 - 18, 48 - 18, 50 - 18, 52 - 18 };
int program_number[8];
void play_notes (void);

int main (void)
{
  time_t t;
  open_midfiles ();
  srand ((unsigned) time (&t));
  open_midfiles ();
#if GENERAL_MIDI_ON
  general_midi ();
#endif
  play (48 * 2 * 4, 152 - 16, 100, 0);	/* Handshake */
  play_notes ();
  close_midfiles ();
  return (1);
}

void play_notes ()
{
  int counter;
  int volume = 127;
  int note[8];
  int octave;
  int i, j[8];
  int channel[10] = { 144, 145, 146, 147, 148, 149, 150, 151, 151, 151 };
/* need as many channel arrays as layers */
  program_number[0] = 9;
  program_number[1] = 9;
  program_number[2] = 9;
  program_number[3] = 9;
  program_number[4] = 9;
  program_number[5] = 9;
  program_number[6] = 9;
  program_number[7] = 9;
#if PROGRAM_NUMBERS_ON
  program_setup ();
#endif
  counter = 0;
  do
    {
      for (i = 0; i < 7; ++i)
	{
	  note[i] = rand () % 6;
	  octave = 24;
	  note[i] = (pentatonic[note[i]]) + octave;
	  j[i] = rand () % 8;
	  play (0, channel[j[i]], note[i], volume);
	  play (rand () % (1500) + 1, 152 - 16, 60, 0);
	}
      play (200, 152 - 16, 60, 0);
      for (i = 0; i < 7; ++i)
	play (0, channel[j[i]] - 16, note[i], 0);
      ++counter;
    }
  while (counter < 7);
  counter = 0;
  do
    {
      for (i = 0; i < 7; ++i)
	{
	  note[i] = rand () % 7;
	  octave = 24;
	  note[i] = (whole_tone[note[i]]) + octave;
	  j[i] = rand () % 8;
	  play (0, channel[j[i]], note[i], volume);
	  play (rand () % (200) + 1, 152 - 16, 60, 0);
	}
      play (200, 152 - 16, 60, 0);
      for (i = 0; i < 7; ++i)
	play (0, channel[j[i]] - 16, note[i], 0);
      ++counter;
    }
  while (counter < 7);
  do
    {
      for (i = 0; i < 7; ++i)
	{
	  note[i] = rand () % 6;
	  octave = 24;
	  note[i] = (pentatonic[note[i]]) + octave;
	  j[i] = rand () % 8;
	  play (0, channel[j[i]], note[i], volume);
	  play (rand () % (1300) + 1, 152 - 16, 60, 0);
	}
      play (200, 152 - 16, 60, 0);
      for (i = 0; i < 7; ++i)
	play (0, channel[j[i]] - 16, note[i], 0);
      ++counter;
    }
  while (counter < 7);
  counter = 0;
  do
    {
      for (i = 0; i < 7; ++i)
	{
	  note[i] = rand () % 8;
	  octave = 24;
	  note[i] = (lydian[note[i]]) + octave;
	  j[i] = rand () % 8;
	  play (0, channel[j[i]], note[i], volume);
	  play (rand () % (2000) + 1, 152 - 16, 60, 0);
	}
      play (200, 152 - 16, 60, 0);
      for (i = 0; i < 7; ++i)
	play (0, channel[j[i]] - 16, note[i], 0);
      ++counter;
    }
  while (counter < 7);
}

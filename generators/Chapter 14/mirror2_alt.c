/* mirror2_alt.c - produces mirror structures one note added in the scale for a added symmetry and serial chords produced from the scale */
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "convert3.h"
#define PATTERNLENGTH 3
#define INTERVALS 4
#define LENGTH_OF_PIECE 1000
#define SPEED_OF_PIECE 24
#define DENSITY_OF_NOTES  5	/* 2 is max, 3 is less, etc. */
#define PROGRAM_NUMBERS 1
#define NUM_CHANNELS 8		/* 8 is max */
#define GENERAL_MIDI_ON 1
#define PROGRAM_NUMBERS_ON 1
int nodes[128];
int generated_notes[128];
int active_nodes[128];
int prime[128][8];
int retrograde[128][8];
int inversion[128][8];
int retrograde_inversion[128][8];
int primarynode;
int scale[128];
int notes[128];
int notelength;
int noteindex;
void setup (void);
void clear (int array[128]);
void makemelody (void);
void chords_crystalgrowth (void);
void crystalgrowth (void);

int main (void)
{
  time_t t;
  open_midfiles ();
#if GENERAL_MIDI_ON
  general_midi ();
#endif
  srand ((unsigned) time (&t));
  setup ();
  crystalgrowth ();
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
      scale[i] = 0;
      nodes[i] = 0;
      generated_notes[i] = 0;
      active_nodes[i] = 0;
      notes[i] = 0;
    }
  notelength = 0;
  primarynode = 128;
/* for different scales each time it is run */
  for (i = 0; i < PATTERNLENGTH; ++i)
    pattern[i] = rand () % (INTERVALS) + 1;
  scalecounter = 0;
  scale[scalecounter] = 1;
  nodes[0] = 1;
  do
    {
      for (i = 0; i < PATTERNLENGTH; ++i)
	{
	  scalecounter = scalecounter + pattern[i];
	  if (scalecounter < 128)
	    scale[scalecounter] = 1;
	}
      for (i = PATTERNLENGTH - 1; i >= 0; --i)
	{
	  scalecounter = scalecounter + pattern[i];
	  if (scalecounter < 128)
	    scale[scalecounter] = 1;
	}
      if (scalecounter < 128)
	nodes[scalecounter] = 1;
    }
  while (scalecounter < 128);
  for (i = 0; i < 128; ++i)
    if (scale[i] == 1)
      {
	notes[notelength] = i;
	++notelength;
      }
}

void clear (int array[128])
{
  int i;
  for (i = 0; i < 128; ++i)
    array[i] = 0;
}

void makemelody (void)
{
  int direction;
  direction = rand () % (2);
  if (direction == 0)
    {
      if (noteindex + 1 < notelength)
	noteindex = noteindex + 1;
      else
	noteindex = noteindex - 1;
    }
  if (direction == 1)
    {
      if (noteindex - 1 > 0)
	noteindex = noteindex - 1;
      else
	noteindex = noteindex + 1;
    }
}

void chords_crystalgrowth (void)
{
  int i;
  int k;
  int j;
  int relationship;
  int note;
  noteindex = notelength / 2;
  for (k = 0; k < 128; ++k)
    for (i = 0; i < 8; ++i)
      {
	prime[k][i] = 0;
	inversion[k][i] = 0;
	retrograde[k][i] = 0;
	retrograde_inversion[k][i] = 0;
      }
  do
    {
      makemelody ();
      note = notes[noteindex];
      if (nodes[note] == 1)
	primarynode = note;
    }
  while (primarynode != note);
  for (j = 0; j < 128; ++j)
    if (nodes[j] == 1)
      active_nodes[j] = rand () % (2) + 1;
  for (i = 0; i < 8; ++i)
    {
      makemelody ();
      note = notes[noteindex];
      relationship = abs (primarynode - note);
      clear (generated_notes);
      for (k = 0; k < 128; ++k)
	{
	  if (active_nodes[k] == 1)
	    if (k - relationship >= 0)
	      generated_notes[k - relationship] = 1;
	  if (active_nodes[k] == 2)
	    if (k + relationship < 128)
	      generated_notes[k + relationship] = 1;
	}
      if (rand () % (3) > 0)
	{
	  for (k = 0; k < 128; ++k)
	    if (generated_notes[k] == 1)
	      if (k > 20 && k < 100)
		{
		  prime[k][i] = 1;
		  retrograde[k][7 - i] = 1;
		}
	}
      else
	{
	  for (k = 0; k < 128; ++k)
	    if (generated_notes[k] == 1)
	      if (k > 20 && k < 100)
		{
		  inversion[k][i] = 1;
		  retrograde_inversion[k][7 - i] = 1;
		}
	}
      if (nodes[note] == 1 && note != primarynode)
	{
	  primarynode = note;
	  clear (active_nodes);
	  for (j = 0; j < 128; ++j)
	    if (nodes[j] == 1)
	      active_nodes[j] = rand () % (2) + 1;
	}
    }
}

void crystalgrowth (void)
{
  int i;
  int k;
  int j;
  int relationship;
  int note;
  int present_channel;
  int newpitches = 0;
  int temp_chords[128][8];
  int active = 0;
  int reset = 0;
  int chordset;
  int chord_counter;
  static int channel[8] = { 144, 145, 146, 146, 146, 146, 147, 148 };
  program_number[0] = 0;
  program_number[1] = 0;
  program_number[2] = 0;
  program_number[3] = 0;
  program_number[4] = 0;
  program_number[5] = 0;
  program_number[6] = 0;
  program_number[7] = 0;
  program_setup ();
  play (48 * 2 * 4, 152 - 16, 100, 0);	/* Handshake */
  noteindex = notelength / 2;
  chords_crystalgrowth ();
  do
    {
      makemelody ();
      note = notes[noteindex];
      if (nodes[note] == 1)
	primarynode = note;
    }
  while (primarynode != note);
  for (j = 0; j < 128; ++j)
    if (nodes[j] == 1)
      active_nodes[j] = rand () % (DENSITY_OF_NOTES) + 1;
  for (k = 0; k < NUM_CHANNELS; ++k)
    channel[k] = rand () % (NUM_CHANNELS) + 144;
  chord_counter = 0;
  for (i = 0; i < LENGTH_OF_PIECE; ++i)
    {
      makemelody ();
      note = notes[noteindex];
      relationship = abs (primarynode - note);
      clear (generated_notes);
      for (k = 0; k < 128; ++k)
	{
	  if (active_nodes[k] == 1)
	    if (k - relationship >= 0)
	      generated_notes[k - relationship] = 1;
	  if (active_nodes[k] == 2)
	    if (k + relationship < 128)
	      generated_notes[k + relationship] = 1;
	}
      if (active == 0)
	if (rand () % (15) == 1)
	  {
	    if (rand () % (4) == 1)
	      chords_crystalgrowth ();
	    chordset = rand () % (2);	/* should be rand()%(4) */
	    for (k = 0; k < 128; ++k)
	      for (j = 0; j < 8; ++j)
		{
		  if (chordset == 0)
		    temp_chords[k][j] = prime[k][j];
		  else if (chordset == 1)
		    temp_chords[k][j] = retrograde[k][j];
		  else if (chordset == 2)
		    temp_chords[k][j] = inversion[k][j];
		  else if (chordset == 3)
		    temp_chords[k][j] = retrograde_inversion[k][j];
		}
	    active = 1;
	    reset = 0;
	  }
      for (k = 0; k < 128; ++k)
	{
	  if (generated_notes[k] == 1)
	    {
	      if (k + newpitches > 20 && k + newpitches < 100)
		{
		  present_channel = (k + newpitches) % NUM_CHANNELS;
		  play (0, channel[present_channel], k + newpitches, 75);
		}
	    }
	}
      for (k = 0; k < 128; ++k)
	if (active == 1 && temp_chords[k][chord_counter % 8] == 1)
	  if (k > 20 && k < 100)
	    play (0, 144, k, 127);
      play (1 * SPEED_OF_PIECE, 152 - 16, 100, 0);
      for (k = 0; k < 128; ++k)
	if (active == 1 && temp_chords[k][chord_counter % 8] == 1)
	  if (k > 20 && k < 100)
	    play (0, 144 - 16, k, 0);
      if (active == 1 && reset == 0 && chord_counter % 8 > 0)
	reset = 1;
      if (reset == 1 && chord_counter % 8 == 0)
	{
	  active = 0;
	  reset = 0;
	}
      ++chord_counter;
      for (k = 0; k < 128; ++k)
	if (active == 1 && temp_chords[k][chord_counter % 8] == 1)
	  if (k > 20 && k < 100)
	    play (0, 144, k, 127);
      if (rand () % (2) == 1)
	play (1 * SPEED_OF_PIECE, 152 - 16, 100, 0);
      for (k = 0; k < 128; ++k)
	if (active == 1 && temp_chords[k][chord_counter % 8] == 1)
	  if (k > 20 && k < 100)
	    play (0, 144 - 16, k, 0);
      if (active == 1 && reset == 0 && chord_counter % 8 > 0)
	reset = 1;
      if (reset == 1 && chord_counter % 8 == 0)
	{
	  active = 0;
	  reset = 0;
	}
      ++chord_counter;
      for (k = 0; k < 128; ++k)
	{
	  if (generated_notes[k] == 1)
	    if (k + newpitches > 20 && k + newpitches < 100)
	      {
		present_channel = ((k + newpitches) % NUM_CHANNELS);
		play (0, channel[present_channel] - 16, k + newpitches, 0);
	      }
	}
      if (nodes[note] == 1 && note != primarynode)
	{
	  for (k = 0; k < NUM_CHANNELS; ++k)
	    channel[k] = rand () % (NUM_CHANNELS) + 144;
	  newpitches = rand () % (12) - 6;
	  primarynode = note;
	  clear (active_nodes);
	  for (j = 0; j < 128; ++j)
	    if (nodes[j] == 1)
	      active_nodes[j] = rand () % (DENSITY_OF_NOTES) + 1;
	}
    }
}

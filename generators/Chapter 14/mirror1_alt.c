/* mirror1_alt.c - produces mirror structures one note added in the scale for a added symmetry */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "convert3.h"
#define PATTERNLENGTH 3
#define INTERVALS 3
#define LENGTH_OF_PIECE 1000
#define SPEED_OF_PIECE 24
#define DENSITY_OF_NOTES  2	/* 2 is max, 3 is less, etc. */
#define PROGRAM_NUMBERS_ON 1
#define GENERAL_MIDI_ON 1
#define NUM_CHANNELS 8		/* 8 is max */
int nodes[128];
int generated_notes[128];
int active_nodes[128];
int primarynode;
int scale[128];
int notes[128];
int notelength;
int noteindex;
void setup (void);
void clear (int array[128]);
void makemelody (void);
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
  for (i = 0; i < PATTERNLENGTH; ++i)
    {
      pattern[i] = rand () % (INTERVALS) + 1;
    }
  scalecounter = 0;
  scale[scalecounter] = 1;
  nodes[0] = 1;
/* sets up the pattern, then the next code sets up 
the reflection of the pattern, then patterns, 
reflection, etc.  for the entire length of the scale. 
notes not played are represented as 0, 
notes played are represetend as 1. Hence there are lots 
of empty spaces in the array 	*/
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
	{
	  nodes[scalecounter] = 1;
	  if (nodes[scalecounter] == 1)
	    {
/*   fprintf(stdprn,"node at "); 
     fprintit(scalecounter); 
     fprintf(stdprn,"\n");  */
	    }
	}
    }
  while (scalecounter < 128);
/* gets rid of the empty spaces and make an array only of the notes played 
also sets up the length of notelength */
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
/* makes melody and makes sure will not exceed the notelength  limits */
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

void crystalgrowth (void)
{
  int i;
  int k;
  int j;
  int relationship;
  int note;
  int present_channel;
  int newpitches = 0;
  static int channel[8] = { 144, 145, 146, 146, 146, 146, 147, 148 };
  program_number[0] = 0;
  program_number[1] = 0;
  program_number[2] = 0;
  program_number[3] = 0;
  program_number[4] = 0;
  program_number[5] = 0;
  program_number[6] = 0;
  program_number[7] = 0;
#if PROGRAM_NUMBERS_ON
  program_setup ();
#endif
  play (48 * 2 * 4, 152 - 16, 100, 0);	/* Handshake */
  noteindex = notelength / 2;	/* starts melody in the middle of the notes */
/* lets note wander around until a primary node is found */
  do
    {
      makemelody ();
      note = notes[noteindex];
      if (nodes[note] == 1)
	primarynode = note;
    }
  while (primarynode != note);
/* some active nodes will be given the value 1, in whieh case it 
will make a negative reflection, value 2 will give a postive reflection, 
anything else will not reflect.  See below code */
  for (j = 0; j < 128; ++j)
    if (nodes[j] == 1)
      active_nodes[j] = rand () % (DENSITY_OF_NOTES) + 1;
/* only select channels are used in passage of music */
  /*     for (k = 0; k < NUM_CHANNELS; ++k) 
     channel[k] = rand()%(NUM_CHANNELS) + 144; */
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
      for (k = 0; k < 128; ++k)
	if (generated_notes[k] == 1)
	  {
/* newpitches is a trasposing factor. see below */
	    if (k + newpitches > 20 && k + newpitches < 100)
	      {
/* sets up certain channels for each seperate note. make it interesting */
/* present_channel = (k+newpitches)%NUM_CHANNELS; */
		if (k + newpitches < 30 && k + newpitches > 19)
		  present_channel = 151;
		if (k + newpitches < 40 && k + newpitches > 29)
		  present_channel = 150;
		if (k + newpitches < 50 && k + newpitches > 39)
		  present_channel = 149;
		if (k + newpitches < 60 && k + newpitches > 49)
		  present_channel = 148;
		if (k + newpitches < 70 && k + newpitches > 59)
		  present_channel = 147;
		if (k + newpitches < 80 && k + newpitches > 69)
		  present_channel = 146;
		if (k + newpitches < 90 && k + newpitches > 79)
		  present_channel = 145;
		if (k + newpitches < 100 && k + newpitches > 89)
		  present_channel = 144;
		play (0, present_channel, k + newpitches, 100);
	      }
	  }
      play ((rand () % (2) + 1) * SPEED_OF_PIECE, 152 - 16, 100, 0);
      for (k = 0; k < 128; ++k)
	if (generated_notes[k] == 1)
	  if (k + newpitches > 20 && k + newpitches < 100)
	    {
/*  present_channel = ((k+newpitches)%NUM_CHANNELS); */
	      if (k + newpitches < 30 && k + newpitches > 19)
		present_channel = 151;
	      if (k + newpitches < 40 && k + newpitches > 29)
		present_channel = 150;
	      if (k + newpitches < 50 && k + newpitches > 39)
		present_channel = 149;
	      if (k + newpitches < 60 && k + newpitches > 49)
		present_channel = 148;
	      if (k + newpitches < 70 && k + newpitches > 59)
		present_channel = 147;
	      if (k + newpitches < 80 && k + newpitches > 69)
		present_channel = 146;
	      if (k + newpitches < 90 && k + newpitches > 79)
		present_channel = 145;
	      if (k + newpitches < 100 && k + newpitches > 89)
		present_channel = 144;
	      play (0, present_channel - 16, k + newpitches, 0);
	    }
      if (nodes[note] == 1 && note != primarynode)
	{
/*	for (k = 0; k < NUM_CHANNELS; ++k) 
channel[k] = rand()%(NUM_CHANNELS) + 144; */
	  newpitches = rand () & (12) - 6;	/* transpose factor */
	  primarynode = note;
	  clear (active_nodes);
	  /* change the active notes */
	  for (j = 0; j < 128; ++j)
	    if (nodes[j] == 1)
	      active_nodes[j] = rand () % (DENSITY_OF_NOTES) + 1;
	}
    }
}

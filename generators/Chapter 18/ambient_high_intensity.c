
//ambient_high_intensity.c
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "convert3.h"
#define GENERAL_MIDI_ON 1
#define PROGRAM_NUMBERS_ON 1

#define F3 53
#define TONIC 53



#define MINOR 0
#define MAJOR 1

// kirk > picard 
int channel[8] = { 144, 145, 146, 147, 148, 149, 150, 151 };

int transposefactor;
int tempo;
int volume;
int sound[3];
int sounds[5];
int mode;
int note;
int index_number;
int chordsbassminor[5];
int chordsbassmajor[5];
int percussive_rhythms1[8];
int percussive_rhythms2[8];
int percussive_rhythms3[8];
int percussive_rhythms4[8];
int percussive_rhythms5[8];
int rhythm[5][8] = { {2, 2, 0, 0, 0, 0, 0, 0},	//0    .  
{3, 1, 4, 0, 0, 0, 0, 0},	//1 
{1, 0, 0, 0, 0, 0, 0, 0},	//2 
{2, 0, 0, 0, 0, 0, 0, 0},	//3 
{4, 0, 0, 0, 0, 0, 0, 0}};     //4     TONIC CADENCE Total =  [5][8] 


int rhythm_events[5];
int melody[5][8];
int chords[5][3];
int chords_scale[5][5];
int choose_chords_pitch (void);
int choose_non_harmonic_pitch (void);
void set_up_rhythm_events (void);
void makeminorchords (int note);
void makeminorscale (int note);
void make_percussive_rhythms (void);
void play_percussive_rhythms (void);
void quality_function_minor_key (void);
void quality_function_major_key (void);
void procedure1 (void);
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
  tempo = 48;
  play (48 * 2 * 4, 152 - 16, 100, 0);	/* Handshake */
  program_number[0] = 48;	/* strings */
  program_number[1] = 73;	/* flute */
  program_number[2] = 0;	/* piano */
  program_number[3] = 80;	/* square wave */
  program_number[4] = 6;	/* xylophone = 13 and 6 is harpsichord */
  program_number[5] = 47;	/* 14 = tubular bell; 47 = timpani */
  program_number[6] = 57;	/* Trombone */
  program_number[7] = 72;	/* Piccolo */
  program_setup ();
  set_up_rhythm_events ();
  make_percussive_rhythms ();
  note = TONIC;
//  printf ("%d ", TONIC);
  transposefactor = 0;
  index_number = 0;
  procedure1 ();
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
      note = TONIC + transposefactor;
//      printf ("%d ", note);
      if (rand () % 2 == 0)
	index_number = 3;
      else
	index_number = 2;
      procedure1 ();
      play_procedure1 ();
    }
  note = TONIC;
//  printf ("%d ", TONIC);
  transposefactor = 0;
  index_number = 4;
  procedure1 ();
  play_procedure1 ();
  close_midfiles ();
  return (1);
}






void
set_up_rhythm_events (void)
{
  int i, j, count;
  for (i = 0; i < 5; ++i)
    {
      count = 0;
      for (j = 0; j < 8; ++j)
	{
	  if (rhythm[i][j] > 0)
	    count = count + 1;
	}
      rhythm_events[i] = count;
    }
}


void
make_percussive_rhythms (void)
{
  int j;
  int random_number;
  for (j = 0; j < 8; ++j)
    {
      random_number = rand () % 3;
      if (random_number == 0)
	percussive_rhythms1[j] = 1;
      else
	percussive_rhythms1[j] = 0;
    }
  for (j = 0; j < 8; ++j)
    {
      random_number = rand () % 3;
      if (random_number == 0)
	percussive_rhythms2[j] = 1;
      else
	percussive_rhythms2[j] = 0;
    }
  for (j = 0; j < 8; ++j)
    {
      random_number = rand () % 3;
      if (random_number == 0)
	percussive_rhythms3[j] = 1;
      else
	percussive_rhythms3[j] = 0;
    }
  for (j = 0; j < 8; ++j)
    {
      random_number = rand () % 3;
      if (random_number == 0)
	percussive_rhythms4[j] = 1;
      else
	percussive_rhythms4[j] = 0;
    }
  for (j = 0; j < 8; ++j)
    {
      random_number = rand () % 3;
      if (random_number == 0)
	percussive_rhythms5[j] = 1;
      else
	percussive_rhythms5[j] = 0;
    }



}

void
play_percussive_rhythms (void)
{
  int j;
  for (j = 0; j < 8; ++j)
    {
      if (percussive_rhythms1[j] == 1)
	play (0, 149, 60, 127);
      if (percussive_rhythms2[j] == 1)
	play (0, 153, 49, 100);
      if (percussive_rhythms3[j] == 1)
	play (0, 153, 56, 127);
      if (percussive_rhythms4[j] == 1)
	play (0, 153, 65, 127);
      if (percussive_rhythms5[j] == 1)
	play (0, 153, 77, 127);

      play (24, 152 - 16, 100, 0);

      if (percussive_rhythms1[j] == 1)
	play (0, 149 - 16, 60, 0);
      if (percussive_rhythms2[j] == 1)
	play (0, 153 - 16, 49, 0);
      if (percussive_rhythms3[j] == 1)
	play (0, 153 - 16, 56, 0);
      if (percussive_rhythms4[j] == 1)
	play (0, 153 - 16, 65, 0);
      if (percussive_rhythms5[j] == 1)
	play (0, 153 - 16, 77, 0);


    }
}


void
makeminorchords (int note)
{
  sound[0] = note;
  sound[1] = sound[0] + 3;
  sound[2] = sound[0] + 7;
}

void
makeminorscale (int note)
{
  sounds[0] = note;
  sounds[1] = sounds[0] + 2;
  sounds[2] = sounds[0] + 3;
  sounds[3] = sounds[0] + 5;
  sounds[4] = sounds[0] + 7;
}





int
choose_chords_pitch (void)
{
  int x;
  int y;
  x = rand () % 3;
  if (x == 0)
    y = sounds[0];
  else if (x == 1)
    y = sounds[2];
  else if (x == 2)
    y = sounds[4];
  return (y);
}



int
choose_non_harmonic_pitch (void)
{
  int x;
  int y;
  x = rand () % 2;
  if (x == 0)
    y = sounds[1];
  else if (x == 1)
    y = sounds[3];
  return (y);
}


void
procedure1 (void)
{
  int i;
  int counter;
  makeminorscale (note + 12);
  makeminorchords (note);
  chords[index_number][0] = sound[0];
  chords[index_number][1] = sound[1];
  chords[index_number][2] = sound[2];
  chords_scale[index_number][0] = sounds[0];
  chords_scale[index_number][1] = sounds[1];
  chords_scale[index_number][2] = sounds[2];
  chords_scale[index_number][3] = sounds[3];
  chords_scale[index_number][4] = sounds[4];

  counter = 0;
  for (i = 0; i < rhythm_events[index_number]; ++i)
    {
      if (counter % 2 == 0)
	melody[index_number][i] = choose_chords_pitch ();
      else
	melody[index_number][i] = choose_non_harmonic_pitch ();
      counter = counter + rhythm[index_number][i];
    }
}








void
play_procedure1 (void)
{
  int i;
  int j;
  for (i = 0; i < 3; ++i)
    play (0, 144, (chords[index_number][i]), 100);	// strings for chords   
  play (0, 147, (chords[index_number][0]) - 12, 100);	// square wave
  play (0, 150, (chords[index_number][0]) - 12, 100);	// trombone 
  for (i = 0; i < rhythm_events[index_number]; ++i)
    {
      play (0, 145, (melody[index_number][i]), 127);
      play (0, 150, (melody[index_number][i]) + 12, 127);
      play (0, 151, (melody[index_number][i]) + 12, 127);
      for (j = 0; j < rhythm[index_number][i]; ++j)
	play_percussive_rhythms ();
      play (0, 145 - 16, (melody[index_number][i]), 0);
      play (0, 150 - 16, (melody[index_number][i]) + 12, 0);
      play (0, 151 - 16, (melody[index_number][i]) + 12, 0);
    }
  for (i = 0; i < 3; ++i)
    play (0, 144 - 16, (chords[index_number][i]), 0);	// turn off chords 
  play (0, 147 - 16, (chords[index_number][0]) - 12, 0);	// square wave
  play (0, 150 - 16, (chords[index_number][0]) - 12, 0);	// trombone
}

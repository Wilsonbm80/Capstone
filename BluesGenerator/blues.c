/* blues.c */
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "convert3.h"
#define TONIC 0
#define SUBDOMINANT 5
#define DOMINANT 7
#define MAJOR_MINOR 0
#define MAJOR_MAJOR 3
#define MINOR_MINOR 4
#define BEGINNING_PITCH  48
#define LOWER_MELODIC_RANGE 70
#define UPPER_MELODIC_RANGE 86
#define NEW_RANGE 15
#define BEATS_PER_MEASURE  4
#define TOTAL_CHORDS  48
/*1 measures times  12 phrases times 4 for 16th notes */
#define GENERAL_MIDI_ON 1
#define PROGRAM_NUMBERS_ON 1
struct sounds
{
  int scale_degree;
  int sound[4];
};
struct sounds chords_I;
struct sounds chords_IV;
struct sounds chords_V;
int chordrhythm[BEATS_PER_MEASURE * 2][4];
int tempo;
int transposefactor;
int layer[5][TOTAL_CHORDS * BEATS_PER_MEASURE];
void make_rhythm (int rhythmarray1[], int rhythmarray2[]);
void initialize_layers (void);
void make_chordrhythm (void);
int copy_progression_to_layers (struct sounds chords, int layer_start);
void make_skeleton_melody (int melody[]);
void copy_melody_to_another (int melody[], int melody1[]);
void add_nonharmonic_tones (int melody[], int melody1[]);
void add_sustaining_tones (int melody[]);
int copy_melody_to_layers (int melody[], int layer_start);
void final_measure (int final_melody[]);
void play_layers (void);
int main (void)
{
  int layer_start;
  int melody1a[BEATS_PER_MEASURE * 4];
  int melody1b[BEATS_PER_MEASURE * 4];
  int melody1c[BEATS_PER_MEASURE * 4];
  int melody1d[BEATS_PER_MEASURE * 4];
  int melody2a[BEATS_PER_MEASURE * 4];
  int melody2b[BEATS_PER_MEASURE * 4];
  int melody2c[BEATS_PER_MEASURE * 4];
  int melody2d[BEATS_PER_MEASURE * 4];
  int final_melody[BEATS_PER_MEASURE * 4];
  time_t t;
  srand ((unsigned) time (&t));
  transposefactor = 0;
  chords_I.sound[0] = TONIC + BEGINNING_PITCH + transposefactor;
  chords_I.sound[1] = chords_I.sound[0] + 10 + transposefactor;
  chords_I.sound[2] = chords_I.sound[0] + 16 + transposefactor;
  chords_I.sound[3] = chords_I.sound[0] + 21 + transposefactor;
  chords_IV.sound[0] = SUBDOMINANT + BEGINNING_PITCH + transposefactor;
  chords_IV.sound[1] = chords_IV.sound[0] + 4 + transposefactor;
  chords_IV.sound[2] = chords_IV.sound[0] + 10 + transposefactor;
  chords_IV.sound[3] = chords_IV.sound[0] + 14 + transposefactor;
  chords_V.sound[0] = DOMINANT + BEGINNING_PITCH + transposefactor;
  chords_V.sound[1] = chords_V.sound[0] + 4 + transposefactor;
  chords_V.sound[2] = chords_V.sound[0] + 10 + transposefactor;
  chords_V.sound[3] = chords_V.sound[0] + 14 + transposefactor;
  open_midfiles ();
#if GENERAL_MIDI_ON
  general_midi ();
#endif
  tempo = 48;
  initialize_layers ();
  make_chordrhythm ();
  make_skeleton_melody (melody1a);
  make_skeleton_melody (melody2a);
  add_nonharmonic_tones (melody1a, melody1b);
  add_nonharmonic_tones (melody1b, melody1c);
  add_nonharmonic_tones (melody1c, melody1d);
  add_nonharmonic_tones (melody2a, melody2b);
  add_nonharmonic_tones (melody2b, melody2c);
  add_nonharmonic_tones (melody2c, melody2d);
  final_measure (final_melody);
  add_sustaining_tones (melody1a);
  add_sustaining_tones (melody1b);
  layer_start = 0;
  layer_start = copy_progression_to_layers (chords_I, layer_start);
  layer_start = copy_progression_to_layers (chords_I, layer_start);
  layer_start = copy_progression_to_layers (chords_I, layer_start);
  layer_start = copy_progression_to_layers (chords_I, layer_start);
  layer_start = copy_progression_to_layers (chords_IV, layer_start);
  layer_start = copy_progression_to_layers (chords_IV, layer_start);
  layer_start = copy_progression_to_layers (chords_I, layer_start);
  layer_start = copy_progression_to_layers (chords_I, layer_start);
  layer_start = copy_progression_to_layers (chords_V, layer_start);
  layer_start = copy_progression_to_layers (chords_IV, layer_start);
  layer_start = copy_progression_to_layers (chords_I, layer_start);
/*layer_start*/ copy_progression_to_layers (chords_I, layer_start);
  layer_start = 0;
  layer_start = copy_melody_to_layers (melody1a, layer_start);
  layer_start = copy_melody_to_layers (melody2a, layer_start);
  layer_start = copy_melody_to_layers (melody1b, layer_start);
  layer_start = copy_melody_to_layers (melody2b, layer_start);
  layer_start = copy_melody_to_layers (melody1c, layer_start);
  layer_start = copy_melody_to_layers (melody2c, layer_start);
  layer_start = copy_melody_to_layers (melody1d, layer_start);
  layer_start = copy_melody_to_layers (melody2d, layer_start);
  layer_start = copy_melody_to_layers (melody1a, layer_start);
  layer_start = copy_melody_to_layers (melody2d, layer_start);
  layer_start = copy_melody_to_layers (melody1d, layer_start);
/*layer_start*/ copy_melody_to_layers (final_melody, layer_start);
  play_layers ();
  close_midfiles ();
  return (1);
}

void initialize_layers (void)
{
  int i;
  int j;
  for (i = 0; i < TOTAL_CHORDS * BEATS_PER_MEASURE; ++i)
    for (j = 0; j < 5; ++j)
      layer[j][i] = -1;
}

void make_chordrhythm (void)
{
  int i;
  int j;
  int temp[BEATS_PER_MEASURE * 2];
  for (i = 0; i < BEATS_PER_MEASURE * 2; ++i)
    chordrhythm[i][0] = rand () % (5);	/* makes root rhythm */
  chordrhythm[0][0] = 1;	/* make sure root   starts each measure */
  for (i = 0; i < BEATS_PER_MEASURE * 2; ++i)
    temp[i] = rand () % (3);	/* makes chord rhythm */
  for (j = 1; j < 4; ++j)
    for (i = 0; i < BEATS_PER_MEASURE * 2; ++i)
      chordrhythm[i][j] = temp[i];
}

int copy_progression_to_layers (struct sounds chords, int layer_start)
 /* makes each chord at beginning of the measure and 
    tied the number of beats times four so that melody 
    and arpeggiated bass may be added to layers */
{
  int k, m;
  /* copy harmonic progression to layers */
  k = layer_start;
  {
    for (m = 0; m < BEATS_PER_MEASURE * 2; ++m)
      {
	if (chordrhythm[m][0] == 1)
	  layer[1][k] = chords.sound[0] - 12;	/* octave lower */
	if (chordrhythm[m][1] == 1)
	  layer[2][k] = chords.sound[1];
	if (chordrhythm[m][2] == 1)
	  layer[3][k] = chords.sound[2];
	if (chordrhythm[m][3] == 1)
	  layer[4][k] = chords.sound[3];
	++k;
	if (chordrhythm[m][0] == 1)
	  layer[1][k] = chords.sound[0] + 128 - 12;
	if (chordrhythm[m][1] == 1)
	  layer[2][k] = chords.sound[1] + 128;
	if (chordrhythm[m][2] == 1)
	  layer[3][k] = chords.sound[2] + 128;
	if (chordrhythm[m][3] == 1)
	  layer[4][k] = chords.sound[3] + 128;
	++k;
      }
  }
  return (k);
}

void make_skeleton_melody (int melody[])
/* makes a skeleton melody no more that the number of 
 beats per measure, but probably much less. 
 */
{
  int note;
  int i;
  int found;
  int previous;
  int new_range = 0;
  for (i = 0; i < BEATS_PER_MEASURE * 4; ++i)
    melody[i] = -1;
  do
    {
      note = rand () % (UPPER_MELODIC_RANGE - LOWER_MELODIC_RANGE)
	+ LOWER_MELODIC_RANGE + new_range;
      if (note % 12 == (TONIC % 12) ||
	  note % 12 == ((TONIC + 3) % 12) ||
	  note % 12 == ((TONIC + 3 + 2) % 12) ||
	  note % 12 == ((TONIC + 3 + 2 + 2) % 12) ||
	  note % 12 == ((TONIC + 3 + 2 + 2 + 3) % 12) ||
	  note % 12 == ((TONIC + 3 + 2 + 2 + 3 + 2) % 12))
	found = 1;
      else
	found = 0;
    }
  while (!found);
  previous = note;
  melody[0] = note + transposefactor;
  for (i = 1; i < BEATS_PER_MEASURE * 4; ++i)
    {
      if (i % BEATS_PER_MEASURE == 0 || rand () % (3) == 1)
	{
	  do
	    {
	      note = rand () % (UPPER_MELODIC_RANGE - LOWER_MELODIC_RANGE)
		+ LOWER_MELODIC_RANGE + new_range;
	      if (note % 12 == (TONIC % 12) ||
		  note % 12 == ((TONIC + 3) % 12) ||
		  note % 12 == ((TONIC + 3 + 2) % 12) ||
		  note % 12 == ((TONIC + 3 + 2 + 2) % 12) ||
		  note % 12 == ((TONIC + 3 + 2 + 2 + 3) % 12) ||
		  note % 12 == ((TONIC + 3 + 2 + 2 + 3 + 2) % 12))
		found = 1;
	      else
		found = 0;
	      if (abs (previous - note) > 7)
		found = 0;
	    }
	  while (!found);
	  previous = note;
	  melody[i] = note + transposefactor;
	}
    }
}

void final_measure (int final_melody[])
{
  int note, found, i;
  do
    {
      note = rand () % (UPPER_MELODIC_RANGE - LOWER_MELODIC_RANGE)
	+ LOWER_MELODIC_RANGE;
      if (note % 12 == TONIC % 12)
	found = 1;
      else
	found = 0;
    }
  while (!found);
  final_melody[0] = note;
  for (i = 1; i < BEATS_PER_MEASURE * 4; ++i)
    final_melody[i] = note + 128;
}

void copy_melody_to_another (int melody[], int melody1[])
{
  int i;
  for (i = 0; i < BEATS_PER_MEASURE * 4; ++i)
    melody1[i] = melody[i];
}

void add_nonharmonic_tones (int melody[], int melody1[])
{
  int i;
  copy_melody_to_another (melody, melody1);
  for (i = 0; i < BEATS_PER_MEASURE * 4; ++i)
    if (melody1[i] >= 0 && melody1[i] < 127 && melody[i - 1] == -1
	&& rand () % (2))
      melody1[i - 1] = melody1[i] - 1;
}

void add_sustaining_tones (int melody[])
{
  int i;
  for (i = 1; i < BEATS_PER_MEASURE * 4; ++i)
    {
      if (melody[i] == -1)
	{
	  if (melody[i - 1] > 127)
	    melody[i] = melody[i - 1];
	  else
	    melody[i] = melody[i - 1] + 128;
	}
    }
}

int copy_melody_to_layers (int melody[], int layer_start)
/* copies each  note  to three more 
so that a harmonic bass of four notes to one 
melody note may be possible */
{
  int i;
  int k = layer_start;
  for (i = 0; i < BEATS_PER_MEASURE * 4; ++i)
    {
      layer[0][k] = melody[i];
      ++k;
    }
  return (k);
}

void play_layers (void)
{
/* -1 represents a silence. 128 + note means that note is tied */
  static int previous_note[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
  int current_note[10];
  int i, j;
  int volume = 127;
  static int channel[8] = { 144, 145, 146, 146, 146, 147, 147, 147 };
/* need as many channel arrays as layers */
/* however  there are actually only 8 layers */
  program_number[0] = 74;
  program_number[1] = 68;
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
  for (i = 0; i < TOTAL_CHORDS * BEATS_PER_MEASURE; ++i)
    {
      for (j = 0; j < 5; ++j)
	{
	  current_note[j] = layer[j][i];
	  if (previous_note[j] >= 0 &&
	      previous_note[j] <= 127 && current_note[j] == -1)
	    play (0, channel[j] - 16, previous_note[j], 100);
	  else if (previous_note[j] >= 0 && current_note[j] >= 0
		   && previous_note[j] <= 127 && current_note[j] <= 127)
	    play (0, channel[j] - 16, previous_note[j], 0);
	  else if (previous_note[j] >= 128 && current_note[j] == -1)
	    play (0, channel[j] - 16, previous_note[j] - 128, 0);
	  else if (previous_note[j] >= 128 && current_note[j] >= 0
		   && current_note[j] <= 127)
	    play (0, channel[j] - 16, previous_note[j] - 128, 0);
	  previous_note[j] = layer[j][i];
	}			/* end of j loop */
      for (j = 0; j < 5; ++j)
	{
	  current_note[j] = layer[j][i];
	  if (previous_note[j] == -1 && current_note[j] >= 0
	      && current_note[j] <= 127)
	    play (0, channel[j], current_note[j], volume);
	  else if (previous_note[j] >= 0 && current_note[j] >= 0 &&
		   previous_note[j] <= 127 && current_note[j] <= 127)
	    play (0, channel[j], current_note[j], volume);
	  else if (previous_note[j] >= 128 && current_note[j] >= 0
		   && current_note[j] <= 127)
	    play (0, channel[j], current_note[j], volume);
	  previous_note[j] = layer[j][i];
	}			/* end of second loop */
      play (tempo, 152 - 16, 100, 0);
    }				/* end of i loop */
  for (j = 0; j < 5; ++j)
    {
      if (current_note[j] != -1)
	{
	  if (current_note[j] > 127)
	    current_note[j] = current_note[j] - 128;
	  play (0, channel[j] - 16, current_note[j], 0);
	}
    }
}

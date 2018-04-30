/* counterpoint.c         
the comments for printf and printit helps to understand 
the code but is of course not necessary*/
/* in fact the last code shows the composition finished*/
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "convert3.h"
#define GENERAL_MIDI_ON 1
#define PROGRAM_NUMBERS_ON 1
#define TRUE 1
#define FALSE 0
#define BASS 0
#define ALTO 1
#define SOPRANO 2
int fflush (FILE * stream);
int bass_scale_array[6] = { 44, 46, 48, 50, 51, 53 };
int alto_scale_array[6] = { 55, 56, 58, 60, 62, 63 };
int soprano_scale_array[6] = { 65, 67, 68, 70, 72, 74 };	/* 1337 */
int consonances_in_bass_to_upper[6] = { 0, 3, 4, 7, 8, 9 };
int consonances_in_upper[8] = { 0, 3, 4, 5, 6, 7, 8, 9 };
int dissonances_in_bass_to_upper[6] = { 1, 2, 5, 6, 10, 11 };
int dissonances_in_upper[4] = { 1, 2, 10, 11 };
int scale_array[20] =
  { 43, 44, 46, 48, 50, 51, 53, 55, 56, 58, 60, 62, 63, 65, 67, 68, 70, 72,
74, 75 };
int bass_melody[12 * 4];
int two_beat_bass_melody[ /*2*12  24 half notes = */ 24];
int two_beat_bass_melody1[ /*2*12  24 half notes = */ 24];
int alto_melody[12 * 4];
int two_beat_alto_melody[24];
int two_beat_alto_melody1[24];
int soprano_melody[12 * 4];	/* 12 measures of 4 possible quarter notes  */
int two_beat_soprano_melody[24];
int two_beat_soprano_melody1[24];
int four_beat_soprano_melody[48];
int four_beat_soprano_melody1[48];
int four_beat_alto_melody[48];
int four_beat_alto_melody1[48];
int four_beat_bass_melody[48];
int four_beat_bass_melody1[48];
int first_bass;
int first_soprano;
int first_alto;
int second_bass;
int second_alto;
int second_soprano;
int third_alto;
int third_bass;
int third_soprano;
int fourth_alto;
int fourth_bass;
int fourth_soprano;
int previous_note;
int current_note;
int first_main_beat;
int second_main_beat;
int bailout;
int do_again;
int found_bass = 0;
int found_alto = 0;
int found_soprano = 0;
int note_bass_counter = 0;
int note_alto_counter = 0;
int note_soprano_counter = 0;
int bass_preperation = 0;
int bass_suspension = 0;
int bass_resolution = 0;
int bass_scale_array_index = 0;
int alto_scale_array_index = 0;
int soprano_scale_array_index = 0;
int alto_preperation = 0;
int alto_suspension = 0;
int alto_resolution = 0;
int soprano_preperation = 0;
int soprano_suspension = 0;
int soprano_resolution = 0;
int bass_preperation_found = 0;
int alto_preperation_found = 0;
int soprano_preperation_found = 0;
int temp_bass_melody[24];
int temp_alto_melody[24];
int temp_soprano_melody[24];
int smallest_number[3];
int smallest_number_index = 0;
void four_beat_layout (void);
void melodic_rules_for_half_note_cantus_firmus (void);
void melodic_harmonic_rules_for_alto (void);
void melodic_harmonic_rules_for_soprano (void);
void copy_chords_to_four_beats (void);
void add_passing_tones_and_other_quarters (void);
void add_more_passing_tones (void);
void play_counterpoint (void);
void rewrite_with_suspensions (void);
int main (void)
{
  int i;
  char ans;
  time_t t;
  open_midfiles ();
#if GENERAL_MIDI_ON
  general_midi ();
#endif
  srand ((unsigned) time (&t));
  program_number[0] = 73;
  program_number[1] = 73;
  program_number[2] = 73;
  program_number[3] = 73;
  program_number[4] = 0;
  program_number[5] = 0;
  program_number[6] = 0;
  program_number[7] = 0;
  program_setup ();
  play (48 * 2 * 4, 152 - 16, 100, 0);	/* Handshake */
  do
    {
      do_again = 0;
      melodic_rules_for_half_note_cantus_firmus ();
      melodic_harmonic_rules_for_alto ();
      melodic_harmonic_rules_for_soprano ();
    }
  while (do_again == 1);
/*for (i = 0; i < 12; ++i) 
{ 
printit(two_beat_soprano_melody[i]); 
if (i%2 == 1) printf("| "); 
} 
printf("\n"); 
for (i = 0; i < 12; ++i) 
{ 
printit(two_beat_alto_melody[i]); 
if (i%2 == 1) printf("| "); 
} 
printf("\n"); 
for (i = 0; i < 12; ++i) 
{ 
printit(two_beat_bass_melody[i]); 
if (i%2 == 1) printf("| "); 
} 
printf("\n"); 
printf("\n"); 
for (i = 12; i < 24; ++i) 
{ 
printit(two_beat_soprano_melody[i]); 
if (i%2 == 1) printf("| "); 
} 
printf("\n"); 
for (i = 12; i < 24; ++i) 
{ 
printit(two_beat_alto_melody[i]); 
if (i%2 == 1) printf("| "); 
} 
printf("\n"); 
for (i = 12; i < 24; ++i) 
{ 
printit(two_beat_bass_melody[i]); 
if (i%2 == 1) printf("| "); 
} 
printf("\n"); 
printf("Now add suspensions\n"); 
*/
  rewrite_with_suspensions ();
  copy_chords_to_four_beats ();
  add_passing_tones_and_other_quarters ();
  add_more_passing_tones ();
/*printf("THE FINAL RESULT\n\n\n"); */
  four_beat_layout ();
/*
scanf("%c", &ans); 
fflush(stdin); */
  play_counterpoint ();
  close_midfiles ();
  return (1);
}

void melodic_rules_for_half_note_cantus_firmus (void)
{
  /* int bass_scale_array[] ={44,46,48,50,51,53}  */
  char ans;
  int random_note;
  int array_marker;
  int previous_array_marker;
  int note_counter = 0;
  two_beat_bass_melody[0] = 48;
  current_note = 48;
  previous_array_marker = 3;
  previous_note = current_note;
  do
    {
      do
	{
	  if (previous_array_marker > 0 && rand () % (100) < 50)
	    {
	      array_marker = previous_array_marker - 1;
	      random_note = bass_scale_array[array_marker];
	    }
	  else if (previous_array_marker < 5 && rand () % (100) < 65)
	    {
	      array_marker = previous_array_marker + 2;
	      random_note = bass_scale_array[array_marker];
	    }
	  else if (previous_array_marker > 1 && rand () % (100) < 80)
	    {
	      array_marker = previous_array_marker - 2;
	      random_note = bass_scale_array[array_marker];
	    }
	  else
	    {
	      array_marker = rand () % (6);
	      random_note = bass_scale_array[array_marker];
	    }
	}
      while (abs (previous_note - random_note) == 6 || abs (previous_note - random_note) > 7 || abs (previous_note - random_note == 0));	/* avoid the tritone */
      previous_note = random_note;
      previous_array_marker = array_marker;
      ++note_counter;
      two_beat_bass_melody[note_counter] = random_note;
    }
  while (note_counter < 23);
  two_beat_bass_melody[20] = 48;	/* avoid tritone to next note */
  two_beat_bass_melody[21] = 50;
  two_beat_bass_melody[22] = 48;
  two_beat_bass_melody[23] = 48;
}

void melodic_harmonic_rules_for_alto (void)
{
/* consonances_in_bass_to_upper[] = {0,3,4,7,8,9}; */
/* dissonances_in_bass_to_upper[] = {1,2,5,6,10,11}; */
/*  alto_scale_array[] =          {55,56,58,60,62,63}; */
/* bass_scale_array[] ={44,46,48,50,51,53}  */
  int i;
  char ans;
  int green_light;
  int random_note;
  int note_counter = 0;
  two_beat_alto_melody[0] = 60;
  previous_note = 60;
  ++note_counter;
  do
    {
      do
	{
	  green_light = 0;
	  random_note = alto_scale_array[rand () % (6)];
	  for (i = 0; i < 6; ++i)
	    if (((random_note - two_beat_bass_melody[note_counter]) % 12) ==
		consonances_in_bass_to_upper[i])
	      green_light = 1;
	  if (((previous_note -
		two_beat_bass_melody[note_counter - 1]) % 12 == 7)
	      && ((random_note - two_beat_bass_melody[note_counter]) % 12 ==
		  7) && (previous_note != random_note))
	    green_light = 0;	/* wts */
	  if (((previous_note -
		two_beat_bass_melody[note_counter - 1]) % 12 == 0)
	      && ((random_note - two_beat_bass_melody[note_counter]) % 12 ==
		  0) && (previous_note != random_note))
	    green_light = 0;
	}
      while ((abs (previous_note - random_note) == 6) || (green_light == 0) ||
	     (abs (previous_note - random_note) > 7));
/* avoid the melodic tritone and harmonic dissonances */
      two_beat_alto_melody[note_counter] = random_note;
      ++note_counter;
      previous_note = random_note;
    }
  while (note_counter < 20);
  two_beat_alto_melody[20] = 57;
  two_beat_alto_melody[21] = 59;
  two_beat_alto_melody[22] = 60;
  two_beat_alto_melody[23] = 60;
}

void melodic_harmonic_rules_for_soprano (void)
{
/* bass_scale_array[] = {46,48,50,51,53}; */
/* alto_scale_array[] =          {56,58,60,62,63}; */
/* soprano_scale_array[] =       {65,67,68,70,72}; */
/* consonances_in_bass_to_upper[] = {0,3,4,7,8,9};    */
/* consonances_in_upper[]         = {0,3,4,5,6,7,8,9};  */
/* dissonances_in_bass_to_upper[] = {1,2,5,6,10,11};  */
/* dissonances_in_upper[]         = {1,2,10,11};    */
  int i;
  char ans;
  int green_light;
  int green_light1;
  int random_note;
  int note_counter = 0;
  two_beat_soprano_melody[0] = 67;
  previous_note = 67;
  ++note_counter;
  do
    {
      bailout = 0;
      do
	{
	  green_light = 0;
	  green_light1 = 0;
	  random_note = soprano_scale_array[rand () % (6)];
	  for (i = 0; i < 6; ++i)
	    if (((random_note - two_beat_bass_melody[note_counter]) % 12) ==
		consonances_in_bass_to_upper[i])
	      green_light = 1;
	  for (i = 0; i < 8; ++i)
	    if (((random_note - two_beat_alto_melody[note_counter]) % 12) ==
		consonances_in_upper[i])
	      green_light1 = 1;
	  if (((previous_note -
		two_beat_bass_melody[note_counter - 1]) % 12 == 7)
	      && ((random_note - two_beat_bass_melody[note_counter]) % 12 ==
		  7) && (previous_note != random_note))
	    green_light = 0;
	  if (((previous_note -
		two_beat_bass_melody[note_counter - 1]) % 12 == 0)
	      && ((random_note - two_beat_bass_melody[note_counter]) % 12 ==
		  0) && (previous_note != random_note))
	    green_light = 0;
	  if (((previous_note -
		two_beat_alto_melody[note_counter - 1]) % 12 == 7)
	      && ((random_note - two_beat_alto_melody[note_counter]) % 12 ==
		  7) && (previous_note != random_note))
	    green_light = 0;
	  if (((previous_note -
		two_beat_alto_melody[note_counter - 1]) % 12 == 0)
	      && ((random_note - two_beat_alto_melody[note_counter]) % 12 ==
		  0) && (previous_note != random_note))
	    green_light = 0;
	  ++bailout;
	}
      while (((abs (previous_note - random_note) == 6) || (green_light == 0) || (green_light1 == 0) || (abs (previous_note - random_note) > 7)) && (bailout < 100));	/* avoid the melodic tritone and harmonic dissonances */
      if (bailout >= 100)
	{
/*printf("bailout reached\n");*/
	  do_again = 1;
	}
      two_beat_soprano_melody[note_counter] = random_note;
/*printf("bass = %d, alto = %d, sop = %d\n", two_beat_bass_melody[note_counter], 
two_beat_alto_melody[note_counter], two_beat_soprano_melody[note_counter]); */
      ++note_counter;
      previous_note = random_note;
    }
  while (note_counter < 20);
  two_beat_soprano_melody[20] = 63;
  two_beat_soprano_melody[21] = 65;
  two_beat_soprano_melody[22] = 63;
  two_beat_soprano_melody[23] = 63;
}

void rewrite_with_suspensions (void)
{
  int i;
  int temp_bass_melody2[24];
  int temp_soprano_melody2[24];
  int temp_alto_melody2[24];
  int temp_smallest_number;
  char ans;
  for (i = 0; i < 24; ++i)
    {
      temp_bass_melody[i] = two_beat_bass_melody[i];
      temp_alto_melody[i] = two_beat_alto_melody[i];
      temp_soprano_melody[i] = two_beat_soprano_melody[i];
    }

  for (i = 0; i < 24; ++i)
    {
      temp_bass_melody2[i] = temp_bass_melody[i];
      temp_alto_melody2[i] = temp_alto_melody[i];
      temp_soprano_melody2[i] = temp_soprano_melody[i];
    }
  note_bass_counter = 0;
  note_alto_counter = 0;
  note_soprano_counter = 0;
  do
    {
      do
	{
	  ++note_bass_counter;
	  ++note_alto_counter;
	  ++note_soprano_counter;
	  found_bass = 0;
	  found_alto = 0;
	  found_soprano = 0;
	  if ((note_bass_counter % 2) == 1)
	    {
/*printf("inside bass loop\n");*/
	      for (i = 0; i < 6; ++i)
		if (temp_bass_melody[note_bass_counter] ==
		    bass_scale_array[i])
		  bass_scale_array_index = i;
	      if (bass_scale_array_index > 0)
		{
		  if (temp_bass_melody[note_bass_counter + 1] ==
		      bass_scale_array[bass_scale_array_index - 1])
		    {
		      bass_preperation =
			bass_scale_array[bass_scale_array_index];
		      bass_suspension =
			bass_scale_array[bass_scale_array_index];
		      bass_resolution =
			bass_scale_array[bass_scale_array_index - 1];
		      if ((temp_alto_melody[note_alto_counter + 1] -
			   temp_bass_melody[note_bass_counter]) % 12 != 10
			  && (temp_alto_melody[note_alto_counter + 1] -
			      temp_bass_melody[note_bass_counter]) % 12 != 11
			  && (temp_soprano_melody[note_soprano_counter + 1] -
			      temp_bass_melody[note_bass_counter]) % 12 != 10
			  && (temp_soprano_melody[note_soprano_counter + 1] -
			      temp_bass_melody[note_bass_counter]) % 12 != 11)
			{
			  found_bass = 1;
/*
printf("bass found\n"); 
printf("bass_suspension = %d\n", bass_suspension); 
printf("note_bass_counter = %d\n", note_bass_counter); 
*/
			  temp_smallest_number = note_bass_counter;
/*printf("Suspension is "); printit(temp_bass_melody[temp_smallest_number]); */
			  for (i = 0; i < note_bass_counter + 1; ++i)
			    temp_bass_melody2[i] = temp_bass_melody[i];
			  i = temp_smallest_number;
			  temp_bass_melody2[i] = temp_bass_melody[i];
			  temp_bass_melody2[i + 1] = temp_bass_melody[i];
			  temp_bass_melody2[i + 2] = temp_bass_melody[i + 1];
			  for (i = temp_smallest_number; i < 20; ++i)
			    temp_bass_melody2[i + 3] =
			      temp_bass_melody[i + 2];
			  temp_bass_melody2[20] = 48;
			  temp_bass_melody2[21] = 50;
			  temp_bass_melody2[22] = 48;
			  temp_bass_melody2[23] = 48;
			  for (i = 0; i < temp_smallest_number; ++i)
			    temp_soprano_melody2[i] = temp_soprano_melody[i];
			  i = temp_smallest_number;
			  temp_soprano_melody2[i] = temp_soprano_melody[i];
			  temp_soprano_melody2[i + 1] =
			    temp_soprano_melody[i + 1];
			  temp_soprano_melody2[i + 2] =
			    temp_soprano_melody[i + 2];
			  for (i = temp_smallest_number; i < 20; ++i)
			    temp_soprano_melody2[i + 2] =
			      temp_soprano_melody[i + 1];
			  temp_soprano_melody2[20] = 63;
			  temp_soprano_melody2[21] = 65;
			  temp_soprano_melody2[22] = 63;
			  temp_soprano_melody2[23] = 63;
			  for (i = 0; i < temp_smallest_number; ++i)
			    temp_alto_melody2[i] = temp_alto_melody[i];
			  i = temp_smallest_number;
			  temp_alto_melody2[i] = temp_alto_melody[i];
			  temp_alto_melody2[i + 1] = temp_alto_melody[i + 1];
			  temp_alto_melody2[i + 2] = temp_alto_melody[i + 2];
			  for (i = temp_smallest_number; i < 20; ++i)
			    temp_alto_melody2[i + 2] =
			      temp_alto_melody[i + 1];
			  temp_alto_melody2[20] = 57;
			  temp_alto_melody2[21] = 59;
			  temp_alto_melody2[22] = 60;
			  temp_alto_melody2[23] = 60;
			  for (i = 0; i < 24; ++i)
			    temp_bass_melody[i] = temp_bass_melody2[i];
			  for (i = 0; i < 24; ++i)
			    temp_alto_melody[i] = temp_alto_melody2[i];
			  for (i = 0; i < 24; ++i)
			    temp_soprano_melody[i] = temp_soprano_melody2[i];
/*printf("\n"); 
for (i = 0; i < 12; ++i) 
{ 
printit(temp_soprano_melody[i]); 
if (i%2 == 1) printf("| "); 
} 
printf("\n"); 
for (i = 0; i < 12; ++i) 
{ 
printit(temp_alto_melody[i]); 
if (i%2 == 1) printf("| "); 
} 
printf("\n"); 
for (i = 0; i < 12; ++i) 
{ 
printit(temp_bass_melody[i]); 
if (i%2 == 1) printf("| "); 
} 
printf("\n"); 
printf("\n"); 
for (i = 12; i < 24; ++i) 
{ 
printit(temp_soprano_melody[i]); 
if (i%2 == 1) printf("| "); 
} 
printf("\n"); 
for (i = 12; i < 24; ++i) 
{ 
printit(temp_alto_melody[i]); 
if (i%2 == 1) printf("| "); 
} 
printf("\n"); 
for (i = 12; i < 24; ++i) 
{ 
printit(temp_bass_melody[i]); 
if (i%2 == 1) printf("| "); 
} 
printf("\n"); 
scanf("%c", &ans); 
fflush(stdin); 
*/
			  for (i = 0; i < 24; ++i)
			    temp_bass_melody[i] = temp_bass_melody2[i];
			  for (i = 0; i < 24; ++i)
			    temp_alto_melody[i] = temp_alto_melody2[i];
			  for (i = 0; i < 24; ++i)
			    temp_soprano_melody[i] = temp_soprano_melody2[i];
			}
		    }
		}
	    }
	  if (found_bass == 0 && (note_alto_counter % 2) == 1)
	    {
/*printf("inside alto loop note_alto_counter = %d\n",note_alto_counter); */
	      for (i = 0; i < 6; ++i)
		if (temp_alto_melody[note_alto_counter] ==
		    alto_scale_array[i])
		  alto_scale_array_index = i;
	      if (alto_scale_array_index > 0)
		{
		  if (temp_alto_melody[note_alto_counter + 1] ==
		      alto_scale_array[alto_scale_array_index - 1])
		    {
		      alto_preperation =
			alto_scale_array[alto_scale_array_index];
		      alto_suspension =
			alto_scale_array[alto_scale_array_index];
		      alto_resolution =
			alto_scale_array[alto_scale_array_index - 1];
		      if ((temp_alto_melody[note_alto_counter + 1] -
			   temp_bass_melody[note_bass_counter]) % 12 != 2
			  && (temp_soprano_melody[note_soprano_counter + 1] -
			      temp_alto_melody[note_alto_counter]) % 12 != 10
			  && (temp_soprano_melody[note_soprano_counter + 1] -
			      temp_alto_melody[note_alto_counter]) % 12 != 11)
			{
			  found_alto = 1;
/*printf("found alto\n"); 
printf("alto_suspension = %d\n", alto_suspension); 
printf("note_alto_counter = %d\n", note_alto_counter); */
			  temp_smallest_number = note_alto_counter;
			  for (i = 0; i < note_alto_counter + 1; ++i)
			    temp_alto_melody2[i] = temp_alto_melody[i];
			  i = temp_smallest_number;
			  temp_alto_melody2[i] = temp_alto_melody[i];
			  temp_alto_melody2[i + 1] = temp_alto_melody[i];
			  temp_alto_melody2[i + 2] = temp_alto_melody[i + 1];
			  for (i = temp_smallest_number; i < 20; ++i)
			    temp_alto_melody2[i + 3] =
			      temp_alto_melody[i + 2];
			  temp_alto_melody2[20] = 57;
			  temp_alto_melody2[21] = 59;
			  temp_alto_melody2[22] = 60;
			  temp_alto_melody2[23] = 60;
			  for (i = 0; i < temp_smallest_number; ++i)
			    temp_soprano_melody2[i] = temp_soprano_melody[i];
			  i = temp_smallest_number;
			  temp_soprano_melody2[i] = temp_soprano_melody[i];
			  temp_soprano_melody2[i + 1] =
			    temp_soprano_melody[i + 1];
			  temp_soprano_melody2[i + 2] =
			    temp_soprano_melody[i + 2];
			  for (i = temp_smallest_number; i < 20; ++i)
			    temp_soprano_melody2[i + 2] =
			      temp_soprano_melody[i + 1];
			  temp_soprano_melody2[20] = 63;
			  temp_soprano_melody2[21] = 65;
			  temp_soprano_melody2[22] = 63;
			  temp_soprano_melody2[23] = 63;
			  for (i = 0; i < temp_smallest_number; ++i)
			    temp_bass_melody2[i] = temp_bass_melody[i];
			  i = temp_smallest_number;
			  temp_bass_melody2[i] = temp_bass_melody[i];
			  temp_bass_melody2[i + 1] = temp_bass_melody[i + 1];
			  temp_bass_melody2[i + 2] = temp_bass_melody[i + 2];
			  for (i = temp_smallest_number; i < 20; ++i)
			    temp_bass_melody2[i + 2] =
			      temp_bass_melody[i + 1];
			  temp_bass_melody2[20] = 48;
			  temp_bass_melody2[21] = 50;
			  temp_bass_melody2[22] = 48;
			  temp_bass_melody2[23] = 48;
			  for (i = 0; i < 24; ++i)
			    temp_bass_melody[i] = temp_bass_melody2[i];
			  for (i = 0; i < 24; ++i)
			    temp_alto_melody[i] = temp_alto_melody2[i];
			  for (i = 0; i < 24; ++i)
			    temp_soprano_melody[i] = temp_soprano_melody2[i];
/*printf("\n"); 
for (i = 0; i < 12; ++i) 
{ 
printit(temp_soprano_melody[i]); 
if (i%2 == 1) printf("| "); 
} 
printf("\n"); 
for (i = 0; i < 12; ++i) 
{ 
printit(temp_alto_melody[i]); 
if (i%2 == 1) printf("| "); 
} 
printf("\n"); 
for (i = 0; i < 12; ++i) 
{ 
printit(temp_bass_melody[i]); 
if (i%2 == 1) printf("| "); 
} 
printf("\n"); 
printf("\n"); 
for (i = 12; i < 24; ++i) 
{ 
printit(temp_soprano_melody[i]); 
if (i%2 == 1) printf("| "); 
} 
printf("\n"); 
for (i = 12; i < 24; ++i) 
{ 
printit(temp_alto_melody[i]); 
if (i%2 == 1) printf("| "); 
} 
printf("\n"); 
for (i = 12; i < 24; ++i) 
{ 
printit(temp_bass_melody[i]); 
if (i%2 == 1) printf("| "); 
} 
printf("\n"); 
scanf("%c", &ans); 
fflush(stdin); 
*/
			  for (i = 0; i < 24; ++i)
			    temp_bass_melody[i] = temp_bass_melody2[i];
			  for (i = 0; i < 24; ++i)
			    temp_alto_melody[i] = temp_alto_melody2[i];
			  for (i = 0; i < 24; ++i)
			    temp_soprano_melody[i] = temp_soprano_melody2[i];
			}
		    }
		}
	    }
	  if (found_bass == 0 && found_alto == 0
	      && (note_soprano_counter % 2) == 1)
	    {
/*printf("inside soprano loop note_soprano_counter = %d\n",note_soprano_counter); */
	      for (i = 0; i < 6; ++i)
		if (temp_soprano_melody[note_soprano_counter] ==
		    soprano_scale_array[i])
		  soprano_scale_array_index = i;
	      if (soprano_scale_array_index > 0)
		{
		  if (temp_soprano_melody[note_soprano_counter + 1] ==
		      soprano_scale_array[soprano_scale_array_index - 1])
		    {
		      soprano_preperation =
			soprano_scale_array[soprano_scale_array_index];
		      soprano_suspension =
			soprano_scale_array[soprano_scale_array_index];
		      soprano_resolution =
			soprano_scale_array[soprano_scale_array_index - 1];
		      if ((temp_soprano_melody[note_soprano_counter + 1] -
			   temp_bass_melody[note_bass_counter]) % 12 != 2
			  && (temp_soprano_melody[note_soprano_counter + 1] -
			      temp_alto_melody[note_alto_counter]) % 12 != 2)
			{
			  found_soprano = 1;
/*
printf("found soprano\n"); 
printf("soprano_suspension = %d\n", soprano_suspension); 
printf("note_soprano_counter = %d\n", note_soprano_counter); 
*/
			  temp_smallest_number = note_soprano_counter;
			  for (i = 0; i < note_soprano_counter + 1; ++i)
			    temp_soprano_melody2[i] = temp_soprano_melody[i];
			  i = temp_smallest_number;
			  temp_soprano_melody2[i] = temp_soprano_melody[i];
			  temp_soprano_melody2[i + 1] =
			    temp_soprano_melody[i];
			  temp_soprano_melody2[i + 2] =
			    temp_soprano_melody[i + 1];
			  for (i = temp_smallest_number; i < 20; ++i)
			    temp_soprano_melody2[i + 3] =
			      temp_soprano_melody[i + 2];
			  temp_soprano_melody2[20] = 63;
			  temp_soprano_melody2[21] = 65;
			  temp_soprano_melody2[22] = 63;
			  temp_soprano_melody2[23] = 63;
			  for (i = 0; i < temp_smallest_number; ++i)
			    temp_alto_melody2[i] = temp_alto_melody[i];
			  i = temp_smallest_number;
			  temp_alto_melody2[i] = temp_alto_melody[i];
			  temp_alto_melody2[i + 1] = temp_alto_melody[i + 1];
			  temp_alto_melody2[i + 2] = temp_alto_melody[i + 2];
			  for (i = temp_smallest_number; i < 20; ++i)
			    temp_alto_melody2[i + 2] =
			      temp_alto_melody[i + 1];
			  temp_alto_melody2[20] = 57;
			  temp_alto_melody2[21] = 59;
			  temp_alto_melody2[22] = 60;
			  temp_alto_melody2[23] = 60;
			  for (i = 0; i < temp_smallest_number; ++i)
			    temp_bass_melody2[i] = temp_bass_melody[i];
			  i = temp_smallest_number;
			  temp_bass_melody2[i] = temp_bass_melody[i];
			  temp_bass_melody2[i + 1] = temp_bass_melody[i + 1];
			  temp_bass_melody2[i + 2] = temp_bass_melody[i + 2];
			  for (i = temp_smallest_number; i < 20; ++i)
			    temp_bass_melody2[i + 2] =
			      temp_bass_melody[i + 1];
			  temp_bass_melody2[20] = 48;
			  temp_bass_melody2[21] = 50;
			  temp_bass_melody2[22] = 48;
			  temp_bass_melody2[23] = 48;
			  for (i = 0; i < 24; ++i)
			    temp_bass_melody[i] = temp_bass_melody2[i];
			  for (i = 0; i < 24; ++i)
			    temp_alto_melody[i] = temp_alto_melody2[i];
			  for (i = 0; i < 24; ++i)
			    temp_soprano_melody[i] = temp_soprano_melody2[i];
/*
printf("\n"); 
for (i = 0; i < 12; ++i) 
{ 
printit(temp_soprano_melody[i]); 
if (i%2 == 1) printf("| "); 
} 
printf("\n"); 
for (i = 0; i < 12; ++i) 
{ 
printit(temp_alto_melody[i]); 
if (i%2 == 1) printf("| "); 
} 
printf("\n"); 
for (i = 0; i < 12; ++i) 
{ 
printit(temp_bass_melody[i]); 
if (i%2 == 1) printf("| "); 
} 
printf("\n"); 
printf("\n"); 
for (i = 12; i < 24; ++i) 
{ 
printit(temp_soprano_melody[i]); 
if (i%2 == 1) printf("| "); 
} 
printf("\n"); 
for (i = 12; i < 24; ++i) 
{ 
printit(temp_alto_melody[i]); 
if (i%2 == 1) printf("| "); 
} 
printf("\n"); 
for (i = 12; i < 24; ++i) 
{ 
printit(temp_bass_melody[i]); 
if (i%2 == 1) printf("| "); 
} 
printf("\n"); 
scanf("%c", &ans); 
fflush(stdin); 
*/
			  for (i = 0; i < 24; ++i)
			    temp_bass_melody[i] = temp_bass_melody2[i];
			  for (i = 0; i < 24; ++i)
			    temp_alto_melody[i] = temp_alto_melody2[i];
			  for (i = 0; i < 24; ++i)
			    temp_soprano_melody[i] = temp_soprano_melody2[i];
			}
		    }
		}
	    }
	}
      while (found_bass == 0 && note_bass_counter < 19);
      if (found_bass == 0)
	{
	  note_bass_counter = 21;
/*printf("note_bass_counter = %d\n", note_bass_counter); */
	}
    }
  while (note_bass_counter < 20);
/* end of do-while started at beginning of function */
/*printf("\nfinal bass suspension pattern\n\n"); */
  for (i = 0; i < 24; ++i)
    {
      temp_soprano_melody[i] = temp_soprano_melody2[i];
      temp_alto_melody[i] = temp_alto_melody2[i];
      temp_bass_melody[i] = temp_bass_melody2[i];
    }
/*
for (i = 0; i < 12; ++i) 
{ 
printit(temp_soprano_melody[i]); 
if (i%2 == 1) printf("| "); 
} 
printf("\n"); 
for (i = 0; i < 12; ++i) 
{ 
printit(temp_alto_melody[i]); 
if (i%2 == 1) printf("| "); 
} 
printf("\n"); 
for (i = 0; i < 12; ++i) 
{ 
printit(temp_bass_melody[i]); 
if (i%2 == 1) printf("| "); 
} 
printf("\n"); 
printf("\n"); 
for (i = 12; i < 24; ++i) 
{ 
printit(temp_soprano_melody[i]); 
if (i%2 == 1) printf("| "); 
} 
printf("\n"); 
for (i = 12; i < 24; ++i) 
{ 
printit(temp_alto_melody[i]); 
if (i%2 == 1) printf("| "); 
} 
printf("\n"); 
for (i = 12; i < 24; ++i) 
{ 
printit(temp_bass_melody[i]); 
if (i%2 == 1) printf("| "); 
} 
printf("\n"); 
scanf("%c", &ans); 
fflush(stdin); 
/*
/* 
 for (i = 0; i < 24; ++i) 
{ 
play(0,147,temp_bass_melody[i],127); 
play(0,146,temp_alto_melody[i],127); 
play(0,145,temp_soprano_melody[i],127); 
play(200,144 - 16, 60, 0); 
play(0,147-16,temp_bass_melody[i],0); 
play(0,146-16,temp_alto_melody[i],0); 
play(0,145-16,temp_soprano_melody[i],0); 
} 
*/
}

void copy_chords_to_four_beats (void)
{
  char ans;
  int i, j;
  for (i = 0; i < 48; ++i)
    {
      four_beat_soprano_melody[i] = 12;
      four_beat_soprano_melody1[i] = 12;
      four_beat_alto_melody[i] = 12;
      four_beat_alto_melody1[i] = 12;
      four_beat_bass_melody[i] = 12;
      four_beat_bass_melody1[i] = 12;
    }

  for (i = 0; i < 24; ++i)
    {
      two_beat_soprano_melody[i] = temp_soprano_melody[i];
      two_beat_alto_melody[i] = temp_alto_melody[i];
      two_beat_bass_melody[i] = temp_bass_melody[i];
    }
  i = 0;
  j = 0;
  do
    {
      four_beat_soprano_melody[i] = two_beat_soprano_melody[j];
      four_beat_alto_melody[i] = two_beat_alto_melody[j];
      four_beat_bass_melody[i] = two_beat_bass_melody[j];
      i = i + 2;
      j = j + 1;
    }
  while (j < 24);
/*
printf("\n"); 
printf("four beat counterpoint without passing tones\n"); 
for (i = 0; i < 12; ++i) 
{ 
printit(four_beat_soprano_melody[i]); 
if ((i+1)%4 == 0) printf("| "); 
} 
printf("\n"); 
for (i = 0; i < 12; ++i) 
{ 
printit(four_beat_alto_melody[i]); 
if ((i+1)%4 == 0) printf("| "); 
} 
printf("\n"); 
for (i = 0; i < 12; ++i) 
{ 
printit(four_beat_bass_melody[i]); 
if ((i+1)%4 == 0) printf("| "); 
} 
printf("\n"); 
printf("\n"); 
for (i = 12; i < 24; ++i) 
{ 
printit(four_beat_soprano_melody[i]); 
if ((i+1)%4 == 0) printf("| "); 
} 
printf("\n"); 
for (i = 12; i < 24; ++i) 
{ 
printit(four_beat_alto_melody[i]); 
if ((i+1)%4 == 0) printf("| "); 
} 
printf("\n"); 
for (i = 12; i < 24; ++i) 
{ 
printit(four_beat_bass_melody[i]); 
if ((i+1)%4 == 0) printf("| "); 
} 
printf("\n"); 
printf("\n"); 
for (i = 24; i < 36; ++i) 
{ 
printit(four_beat_soprano_melody[i]); 
if ((i+1)%4 == 0) printf("| "); 
} 
printf("\n"); 
for (i = 24; i < 36; ++i) 
{ 
printit(four_beat_alto_melody[i]); 
if ((i+1)%4 == 0) printf("| "); 
} 
printf("\n"); 
for (i = 24; i < 36; ++i) 
{ 
printit(four_beat_bass_melody[i]); 
if ((i+1)%4 == 0) printf("| "); 
} 
printf("\n"); 
printf("\n"); 
for (i = 36; i < 48; ++i) 
{ 
printit(four_beat_soprano_melody[i]); 
if ((i+1)%4 == 0) printf("| "); 
} 
printf("\n"); 
for (i = 36; i < 48; ++i) 
{ 
printit(four_beat_alto_melody[i]); 
if ((i+1)%4 == 0) printf("| "); 
} 
printf("\n"); 
for (i = 36; i < 48; ++i) 
{ 
printit(four_beat_bass_melody[i]); 
if ((i+1)%4 == 0) printf("| "); 
} 
printf("\n"); 
printf("\n"); 
scanf("%c", &ans); 
fflush(stdin); 
*/
}

void add_passing_tones_and_other_quarters (void)
{
  int i;
  int temp;
  int random_number;
  char ans;
  int beginning_of_measure_bass_note, second_half_bass_note,
    next_measure_bass_note, next_measure_second_half_bass_note;
  int beginning_of_measure_alto_note, second_half_alto_note,
    next_measure_alto_note, next_measure_second_half_alto_note;
  int beginning_of_measure_soprano_note, second_half_soprano_note,
    next_measure_soprano_note, next_measure_second_half_soprano_note;
  int first_bass, second_bass, third_bass, fourth_bass,
    first_alto, second_alto, third_alto, fourth_alto,
    first_soprano, second_soprano, third_soprano, fourth_soprano;
  for (i = 0; i < 48; ++i)
    {
      four_beat_soprano_melody1[i] = four_beat_soprano_melody[i];
      four_beat_alto_melody1[i] = four_beat_alto_melody[i];
      four_beat_bass_melody1[i] = four_beat_bass_melody[i];
    }
  note_bass_counter = 0;
  note_alto_counter = 0;
  note_soprano_counter = 0;
  do
    {
      do
	{
	  found_bass = 0;
	  found_alto = 0;
	  found_soprano = 0;
	  if ((note_bass_counter % 4) == 0)
	    {
/*printf("\nnote_bass_counter = %d\n", note_bass_counter); */
	      for (i = 0; i < 20; ++i)
		if (four_beat_bass_melody[note_bass_counter] ==
		    scale_array[i])
		  beginning_of_measure_bass_note = i;
/*
printf("beginning_of_measure_bass_note = %d ",beginning_of_measure_bass_note); 
printf("bass note is "); printit(scale_array[beginning_of_measure_bass_note]); 
*/
	      first_bass = four_beat_bass_melody[note_bass_counter];
/*
printf("first_bass = %d  ",first_bass); 
printit(first_bass); 
printf("\n"); 
*/
	      for (i = 0; i < 20; ++i)
		if (four_beat_soprano_melody[note_soprano_counter] ==
		    scale_array[i])
		  beginning_of_measure_soprano_note = i;
/*printf("beginning_of_measure_soprano_note = %d \n ",beginning_of_measure_soprano_note);*/
	      first_soprano = four_beat_soprano_melody[note_soprano_counter];
/*printf("first_soprano = %d ",first_soprano); 
printit(first_soprano); 
printf("\n"); 
*/
	      for (i = 0; i < 20; ++i)
		if (four_beat_alto_melody[note_alto_counter] ==
		    scale_array[i])
		  beginning_of_measure_alto_note = i;
/*
printf("beginning_of_measure_alto_note = %d \n ",beginning_of_measure_alto_note); 
*/
	      first_alto = four_beat_alto_melody[note_alto_counter];
/*
printf("first_alto = %d ",first_alto); 
printit(first_alto); 
printf("\n"); 
*/
	      for (i = 0; i < 20; ++i)
		if (four_beat_bass_melody[note_bass_counter + 2] ==
		    scale_array[i])
		  second_half_bass_note = i;
/*printf("second_half_bass_note =  %d \n ", second_half_bass_note); */
	      second_bass = four_beat_bass_melody[note_bass_counter + 2];
/*printf("second_bass = %d  ",second_bass); 
printit(second_bass); 
printf("\n"); */
	      for (i = 0; i < 20; ++i)
		if (four_beat_soprano_melody[note_soprano_counter + 2] ==
		    scale_array[i])
		  second_half_soprano_note = i;
/*printf("second_half_soprano_note =  %d \n ", second_half_soprano_note); */
	      second_soprano =
		four_beat_soprano_melody[note_soprano_counter + 2];
/*printf("second_soprano = %d  ",second_soprano); 
printit(second_soprano); 
printf("\n"); */
	      for (i = 0; i < 20; ++i)
		if (four_beat_alto_melody[note_alto_counter + 2] ==
		    scale_array[i])
		  second_half_alto_note = i;
/*printf("second_half_alto_note =  %d \n ", second_half_alto_note); */
	      second_alto = four_beat_alto_melody[note_alto_counter + 2];
/*printf("second_alto = %d  ",second_alto); 
printit(second_alto); 
printf("\n"); */
	      for (i = 0; i < 20; ++i)
		if (four_beat_bass_melody[note_bass_counter + 4] ==
		    scale_array[i])
		  next_measure_bass_note = i;
/*printf("next_measure_bass_note = %d \n ", next_measure_bass_note); */
	      third_bass = four_beat_bass_melody[note_bass_counter + 4];
/*printf("third_bass = %d  ",third_bass); 
printit(third_bass); 
printf("\n"); */
	      for (i = 0; i < 20; ++i)
		if (four_beat_soprano_melody[note_soprano_counter + 4] ==
		    scale_array[i])
		  next_measure_soprano_note = i;
/*printf("next_measure_soprano_note = %d \n ", next_measure_soprano_note); */
	      third_soprano =
		four_beat_soprano_melody[note_soprano_counter + 4];
/*printf("third_soprano = %d  ",third_soprano); 
printit(third_soprano); 
printf("\n"); */
	      for (i = 0; i < 20; ++i)
		if (four_beat_alto_melody[note_alto_counter + 4] ==
		    scale_array[i])
		  next_measure_alto_note = i;
/*printf("next_measure_alto_note = %d \n ", next_measure_alto_note);*/
	      third_alto = four_beat_alto_melody[note_alto_counter + 4];
/*printf("third_alto = %d  ",third_alto); 
printit(third_alto); 
printf("\n");*/
	      for (i = 0; i < 20; ++i)
		if (four_beat_bass_melody[note_bass_counter + 6] ==
		    scale_array[i])
		  next_measure_second_half_bass_note = i;
/*printf("next_measure_second_half_bass_note = %d \n ", 
next_measure_second_half_bass_note);*/
	      fourth_bass = four_beat_bass_melody[note_bass_counter + 6];
/*printf("fourth_bass = %d  ",fourth_bass); 
printit(fourth_bass); 
printf("\n"); */
	      for (i = 0; i < 20; ++i)
		if (four_beat_soprano_melody[note_soprano_counter + 6] ==
		    scale_array[i])
		  next_measure_second_half_soprano_note = i;
/*printf("next_measure_second_half_soprano_note = %d \n ", 
next_measure_second_half_soprano_note); */
	      fourth_soprano =
		four_beat_soprano_melody[note_soprano_counter + 6];
/*printf("fourth_soprano = %d  ",fourth_soprano); 
printit(fourth_soprano); 
printf("\n"); */
	      for (i = 0; i < 20; ++i)
		if (four_beat_alto_melody[note_alto_counter + 6] ==
		    scale_array[i])
		  next_measure_second_half_alto_note = i;
/*printf("next_measure_second_half_alto_note = %d \n ", 
next_measure_second_half_alto_note); */
	      fourth_alto = four_beat_alto_melody[note_alto_counter + 6];
/*printf("fourth_alto = %d  ",fourth_alto); 
printit(fourth_alto); 
printf("\n"); */
	      if ((beginning_of_measure_soprano_note ==
		   second_half_soprano_note)
		  && (second_half_soprano_note == next_measure_soprano_note)
		  && (next_measure_soprano_note - 1 ==
		      next_measure_second_half_soprano_note))
		{
/*printf("section 1\n");                                                              
printf("FOUND A SOPRANO NEIGHBOR TONE\n"); */
		  random_number = rand () % (2);
		  if (random_number == 0)
		    temp = beginning_of_measure_soprano_note + 1;
		  else
		    temp = beginning_of_measure_soprano_note - 1;
		  if ((((scale_array[temp] -
			 scale_array[beginning_of_measure_bass_note]) % 12 ==
			7)
		       &&
		       ((scale_array[second_half_soprano_note] -
			 scale_array[second_half_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[temp] -
			 scale_array[beginning_of_measure_bass_note]) % 12 ==
			12)
		       &&
		       ((scale_array[second_half_soprano_note] -
			 scale_array[second_half_bass_note]) % 12 == 12))
		      ||
		      (((scale_array[temp] -
			 scale_array[beginning_of_measure_alto_note]) % 12 ==
			7)
		       &&
		       ((scale_array[second_half_soprano_note] -
			 scale_array[second_half_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[temp] -
			 scale_array[beginning_of_measure_alto_note]) % 12 ==
			12)
		       &&
		       ((scale_array[second_half_soprano_note] -
			 scale_array[second_half_alto_note]) % 12 == 12)))
		    {
/*printf("SOPRANO PARALLEL FIFTH OR OCTAVE because temp = "); 
printit(scale_array[temp]); 
scanf("%c", &ans); 
fflush(stdin); */
		    }
		  else
		    {
/*printf("no parallels\n");*/
		      four_beat_soprano_melody[note_soprano_counter + 1] =
			scale_array[temp];
		      four_beat_layout ();
		    }
		}
	      else
		if ((beginning_of_measure_alto_note == second_half_alto_note)
		    && (second_half_alto_note == next_measure_alto_note)
		    && (next_measure_alto_note - 1 ==
			next_measure_second_half_alto_note))
		{
/*printf("section 2\n"); 
printf("FOUND AN ALTO NEIGHBOR TONE\n"); */
		  random_number = rand () % (2);
		  if (random_number == 0)
		    temp = beginning_of_measure_alto_note + 1;
		  else
		    temp = beginning_of_measure_alto_note - 1;
		  if ((((scale_array[temp] -
			 scale_array[beginning_of_measure_bass_note]) % 12 ==
			7)
		       &&
		       ((scale_array[second_half_alto_note] -
			 scale_array[second_half_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[temp] -
			 scale_array[beginning_of_measure_bass_note]) % 12 ==
			12)
		       &&
		       ((scale_array[second_half_alto_note] -
			 scale_array[second_half_bass_note]) % 12 == 12))
		      ||
		      (((scale_array[beginning_of_measure_soprano_note] -
			 scale_array[temp]) % 12 == 7)
		       &&
		       ((scale_array[second_half_soprano_note] -
			 scale_array[second_half_alto_note]) % 12 == 7))
		      ||
		      (((scale_array[beginning_of_measure_soprano_note] -
			 scale_array[temp]) % 12 == 12)
		       &&
		       ((scale_array[second_half_soprano_note] -
			 scale_array[second_half_alto_note]) % 12 == 12)))
		    {
/*printf("PARALLEL FIFTHS OR OCTAVES\n"); 
printit(scale_array[temp]); 
scanf("%c", &ans); 
fflush(stdin); */
		    }
		  else
		    {
/*printf("no  parallels\n"); */
		      four_beat_alto_melody[note_alto_counter + 1] =
			scale_array[temp];
		      four_beat_layout ();
		    }
		}
	      else
		if ((beginning_of_measure_bass_note == second_half_bass_note)
		    && (second_half_bass_note == next_measure_bass_note)
		    && (next_measure_bass_note - 1 ==
			next_measure_second_half_bass_note))
		{
/*printf("section 3\n"); 
printf("FOUND BASS NEIGHBOR TONE\n"); */
		  random_number = rand () % (2);
		  if (random_number == 0)
		    temp = beginning_of_measure_bass_note + 1;
		  else
		    temp = beginning_of_measure_bass_note - 1;
		  if ((((scale_array[beginning_of_measure_alto_note] -
			 scale_array[temp]) % 12 == 7)
		       &&
		       ((scale_array[second_half_alto_note] -
			 scale_array[second_half_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[beginning_of_measure_alto_note] -
			 scale_array[temp]) % 12 == 12)
		       &&
		       ((scale_array[second_half_alto_note] -
			 scale_array[second_half_bass_note]) % 12 == 12))
		      ||
		      (((scale_array[beginning_of_measure_soprano_note] -
			 scale_array[temp]) % 12 == 7)
		       &&
		       ((scale_array[second_half_soprano_note] -
			 scale_array[second_half_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[beginning_of_measure_soprano_note] -
			 scale_array[temp]) % 12 == 12)
		       &&
		       ((scale_array[second_half_soprano_note] -
			 scale_array[second_half_bass_note]) % 12 == 12)))
		    {
/*printf("BASS PARALLEL FIFTHS OR OCTAVES\n"); 
printit(scale_array[temp]); 
scanf("%c", &ans); 
fflush(stdin); */
		    }
		  else
		    {
/*printf("no parallels\n"); */
		      four_beat_bass_melody[note_bass_counter + 1] =
			scale_array[temp];
		      four_beat_layout ();
		    }
		}
	      else if (second_half_soprano_note + 2 ==
		       next_measure_soprano_note)
		{
/*printf("section 4\n"); 
printf("FOUND A SOPRANO PASSING TONE ON THE THIRD BEAT\n"); */
		  temp = second_half_soprano_note + 1;
		  if ((((scale_array[temp] -
			 scale_array[second_half_bass_note]) % 12 == 7)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[temp] -
			 scale_array[second_half_bass_note]) % 12 == 12)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_bass_note]) % 12 == 12))
		      ||
		      (((scale_array[temp] -
			 scale_array[second_half_alto_note]) % 12 == 7)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_alto_note]) % 12 == 7))
		      ||
		      (((scale_array[temp] -
			 scale_array[second_half_alto_note]) % 12 == 12)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_alto_note]) % 12 == 12)))
		    {
/*printf("SOPRANO PARALLEL FIFTH OR OCTAVE because temp = "); 
printit(scale_array[temp]); 
scanf("%c", &ans); 
fflush(stdin); */
		    }
		  else
		    {
/*printf("no parallels\n"); */
		      four_beat_soprano_melody[note_soprano_counter + 3] =
			scale_array[temp];
		      four_beat_layout ();
		    }
		}
	      else if (second_half_soprano_note - 2 ==
		       next_measure_soprano_note)
		{
/*printf("section 5\n"); 
printf("FOUND A SOPRANO PASSING TONE ON THE THIRD BEAT\n"); */
		  temp = second_half_soprano_note - 1;
		  if ((((scale_array[temp] -
			 scale_array[second_half_bass_note]) % 12 == 7)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[temp] -
			 scale_array[second_half_bass_note]) % 12 == 12)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_bass_note]) % 12 == 12))
		      ||
		      (((scale_array[temp] -
			 scale_array[second_half_alto_note]) % 12 == 7)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_alto_note]) % 12 == 7))
		      ||
		      (((scale_array[temp] -
			 scale_array[second_half_alto_note]) % 12 == 12)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_alto_note]) % 12 == 12)))
		    {
/*printf("SOPRANO PARALLEL FIFTH OR OCTAVE because temp = "); 
printit(scale_array[temp]); 
scanf("%c", &ans); 
fflush(stdin); */
		    }
		  else
		    {
/*printf("no  parallels\n"); */
		      four_beat_soprano_melody[note_soprano_counter + 3] =
			scale_array[temp];
		      four_beat_layout ();
		    }
		}
	      else if (second_half_alto_note + 2 == next_measure_alto_note)
		{
/*printf("section 6\n"); 
printf("FOUND A ALTO PASSING TONE ON THE THIRD BEAT\n"); */
		  temp = second_half_alto_note + 1;
		  if ((((scale_array[second_half_soprano_note] -
			 scale_array[temp]) % 12 == 7)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_alto_note]) % 12 == 7))
		      ||
		      (((scale_array[second_half_soprano_note] -
			 scale_array[temp]) % 12 == 12)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_alto_note]) % 12 == 12))
		      ||
		      (((scale_array[temp] - second_half_bass_note) % 12 == 7)
		       &&
		       ((scale_array[next_measure_alto_note] -
			 scale_array[next_measure_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[temp] - second_half_bass_note) % 12 ==
			12)
		       &&
		       ((scale_array[next_measure_alto_note] -
			 scale_array[next_measure_bass_note]) % 12 == 12)))
		    {
/*printf("ALTO PARALLEL FIFTH OR OCTAVE because temp = "); 
printit(scale_array[temp]); 
scanf("%c", &ans); 
fflush(stdin); */
		    }
		  else
		    {
/*printf("no parallels\n"); */
		      four_beat_alto_melody[note_alto_counter + 3] =
			scale_array[temp];
		      four_beat_layout ();
		    }
		}
	      else if (second_half_alto_note - 2 == next_measure_alto_note)
		{
/*printf("section 7\n"); 
printf("FOUND A ALTO PASSING TONE ON THE THIRD BEAT\n"); */
		  temp = second_half_alto_note - 1;
		  if ((((scale_array[second_half_soprano_note] -
			 scale_array[temp]) % 12 == 7)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_alto_note]) % 12 == 7))
		      ||
		      (((scale_array[second_half_soprano_note] -
			 scale_array[temp]) % 12 == 12)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_alto_note]) % 12 == 12))
		      ||
		      (((scale_array[temp] - second_half_bass_note) % 12 == 7)
		       &&
		       ((scale_array[next_measure_alto_note] -
			 scale_array[next_measure_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[temp] - second_half_bass_note) % 12 ==
			12)
		       &&
		       ((scale_array[next_measure_alto_note] -
			 scale_array[next_measure_bass_note]) % 12 == 12)))
		    {
/*printf("ALTO PARALLEL FIFTH OR OCTAVE because temp = "); 
printit(scale_array[temp]); 
scanf("%c", &ans); 
fflush(stdin); */
		    }
		  else
		    {
/*printf("no parallels\n"); */
		      four_beat_alto_melody[note_alto_counter + 3] =
			scale_array[temp];
		      four_beat_layout ();
		    }
		}
	      else if (second_half_bass_note + 2 == next_measure_bass_note)
		{
/*printf("section 8\n"); 
printf("FOUND A BASS PASSING TONE ON THE THIRD BEAT\n"); */
		  temp = second_half_bass_note + 1;
		  if ((((scale_array[second_half_soprano_note] -
			 scale_array[temp]) % 12 == 7)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[second_half_soprano_note] -
			 scale_array[temp]) % 12 == 12)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_bass_note]) % 12 == 12))
		      ||
		      (((scale_array[second_half_alto_note] -
			 scale_array[temp]) % 12 == 7)
		       &&
		       ((scale_array[next_measure_alto_note] -
			 scale_array[next_measure_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[second_half_alto_note] -
			 scale_array[temp]) % 12 == 12)
		       &&
		       ((scale_array[next_measure_alto_note] -
			 scale_array[next_measure_bass_note]) % 12 == 12)))
		    {
/*printf("BASS PARALLEL FIFTH OR OCTAVE because temp = "); 
printit(scale_array[temp]); 
scanf("%c", &ans); 
fflush(stdin); */
		    }
		  else
		    {
/*printf("no parallels\n"); */
		      four_beat_bass_melody[note_bass_counter + 3] =
			scale_array[temp];
		      four_beat_layout ();
		    }
		}
	      else if (second_half_bass_note - 2 == next_measure_bass_note)
		{
/*printf("section 9\n"); 
printf("FOUND A BASS PASSING TONE ON THE THIRD BEAT\n"); */
		  temp = second_half_bass_note - 1;
		  if ((((scale_array[second_half_soprano_note] -
			 scale_array[temp]) % 12 == 7)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[second_half_soprano_note] -
			 scale_array[temp]) % 12 == 12)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_bass_note]) % 12 == 12))
		      ||
		      (((scale_array[second_half_alto_note] -
			 scale_array[temp]) % 12 == 7)
		       &&
		       ((scale_array[next_measure_alto_note] -
			 scale_array[next_measure_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[second_half_alto_note] -
			 scale_array[temp]) % 12 == 12)
		       &&
		       ((scale_array[next_measure_alto_note] -
			 scale_array[next_measure_bass_note]) % 12 == 12)))
		    {
/*printf("BASS PARALLEL FIFTH OR OCTAVE because temp = "); 
printit(scale_array[temp]); 
scanf("%c", &ans); 
fflush(stdin); */
		    }
		  else
		    {
/*printf("no parallels\n"); */
		      four_beat_bass_melody[note_bass_counter + 3] =
			scale_array[temp];
		      four_beat_layout ();
		    }
		}
	      else if ((second_half_soprano_note == next_measure_soprano_note)
		       && (next_measure_soprano_note - 1 !=
			   next_measure_second_half_soprano_note))
		{
/*printf("section 10\n"); 
printf("FOUND SOPRANO NEIGHBOR TONE ON SECOND HALF OF MEASURE \n"); */
		  random_number = rand () % (2);
		  if (random_number == 0)
		    temp = second_half_soprano_note + 1;
		  else
		    temp = second_half_soprano_note - 1;
		  if ((((scale_array[temp] -
			 scale_array[second_half_bass_note]) % 12 == 7)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[temp] -
			 scale_array[second_half_bass_note]) % 12 == 12)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_bass_note]) % 12 == 12))
		      ||
		      (((scale_array[temp] -
			 scale_array[second_half_alto_note]) % 12 == 7)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_alto_note]) % 12 == 7))
		      ||
		      (((scale_array[temp] -
			 scale_array[second_half_alto_note]) % 12 == 12)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_alto_note]) % 12 == 12)))
		    {
/*printf("SOPRANO PARALLEL FIFTH OR OCTAVE because temp = "); 
printit(scale_array[temp]); 
scanf("%c", &ans); 
fflush(stdin); */
		    }
		  else
		    {
/*printf("no parallels\n"); */
		      four_beat_soprano_melody[note_soprano_counter + 3] =
			scale_array[temp];
		      four_beat_layout ();
		    }
		}
	      else if ((second_half_alto_note == next_measure_alto_note) &&
		       (next_measure_alto_note - 1 !=
			next_measure_second_half_alto_note))
		{
/*printf("section 11\n"); 
printf("ALTO NEIGHBOR TONE ON SECOND HALF OF MEASURE\n"); */
		  random_number = rand () % (2);
		  if (random_number == 0)
		    temp = second_half_alto_note + 1;
		  else
		    temp = second_half_alto_note - 1;
		  if ((((scale_array[temp] -
			 scale_array[second_half_bass_note]) % 12 == 7)
		       &&
		       ((scale_array[next_measure_alto_note] -
			 scale_array[next_measure_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[temp] -
			 scale_array[second_half_bass_note]) % 12 == 12)
		       &&
		       ((scale_array[next_measure_alto_note] -
			 scale_array[next_measure_bass_note]) % 12 == 12))
		      ||
		      (((scale_array[second_half_soprano_note] -
			 scale_array[temp]) % 12 == 7)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_alto_note]) % 12 == 7))
		      ||
		      (((scale_array[second_half_soprano_note] -
			 scale_array[temp]) % 12 == 12)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_alto_note]) % 12 == 12)))
		    {
/*printf("ALTO PARALLEL FIFTH OR OCTAVE because temp = "); 
printit(scale_array[temp]); 
scanf("%c", &ans); 
fflush(stdin); */
		    }
		  else
		    {
/*printf("no parallels\n"); */
		      four_beat_alto_melody[note_alto_counter + 3] =
			scale_array[temp];
		      four_beat_layout ();
		    }
		}
	      else if ((second_half_bass_note == next_measure_bass_note) &&
		       (next_measure_bass_note - 1 !=
			next_measure_second_half_bass_note))
		{
/*
printf("section 12\n"); 
printf("next_measure_bass_note - 1 = %d\n",next_measure_bass_note-1); 
printf("next_measure_second_half_bass_note = %d\n",next_measure_second_half_bass_note); 
printf("BASS NEIGHBOR TONES ON SECOND HALF OF MEASURE\n"); */
		  random_number = rand () % (2);
		  if (random_number == 0)
		    temp = second_half_bass_note + 1;
		  else
		    temp = second_half_bass_note - 1;
		  if ((((scale_array[second_half_soprano_note] -
			 scale_array[temp]) % 12 == 7)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[second_half_soprano_note] -
			 scale_array[temp]) % 12 == 12)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_bass_note]) % 12 == 12))
		      ||
		      (((scale_array[second_half_alto_note] -
			 scale_array[temp]) % 12 == 7)
		       &&
		       ((scale_array[next_measure_alto_note] -
			 scale_array[next_measure_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[second_half_alto_note] -
			 scale_array[temp]) % 12 == 12)
		       &&
		       ((scale_array[next_measure_alto_note] -
			 scale_array[next_measure_bass_note]) % 12 == 12)))
		    {
/*
printf("BASS PARALLEL FIFTH OR OCTAVE because temp = "); 
printit(scale_array[temp]); 
scanf("%c", &ans); 
fflush(stdin); 
*/
		    }
		  else
		    {
/*printf("no parallels\n");*/
		      four_beat_bass_melody[note_bass_counter + 3] =
			scale_array[temp];
		      four_beat_layout ();
		    }
		}
/*
scanf("%c", &ans); 
fflush(stdin); 
*/
	    }
	  ++note_bass_counter;
	  ++note_alto_counter;
	  ++note_soprano_counter;
	}
      while (found_bass == 0 && note_bass_counter < 19 * 2);
      if (found_bass == 0)
	{
	  note_bass_counter = 21 * 2;
/*printf("note_bass_counter = %d\n", note_bass_counter); */
	}
    }
  while (note_bass_counter < 20 * 2);
/* end of do-while started at beginning of function */
  four_beat_layout ();
}

void four_beat_layout (void)
{
  int i;
  char ans;
/*printf("\n"); 
for (i = 0; i < 12; ++i) 
{ 
printit(four_beat_soprano_melody[i]); 
if ((i+1)%4 == 0) printf("| "); 
} 
printf("\n"); 
for (i = 0; i < 12; ++i) 
{ 
printit(four_beat_alto_melody[i]); 
if ((i+1)%4 == 0) printf("| "); 
} 
printf("\n"); 
for (i = 0; i < 12; ++i) 
{ 
printit(four_beat_bass_melody[i]); 
if ((i+1)%4 == 0) printf("| "); 
} 
printf("\n"); 
printf("\n"); 
for (i = 12; i < 24; ++i) 
{ 
printit(four_beat_soprano_melody[i]); 
if ((i+1)%4 == 0) printf("| "); 
} 
printf("\n"); 
for (i = 12; i < 24; ++i) 
{ 
printit(four_beat_alto_melody[i]); 
if ((i+1)%4 == 0) printf("| "); 
} 
printf("\n"); 
for (i = 12; i < 24; ++i) 
{ 
printit(four_beat_bass_melody[i]); 
if ((i+1)%4 == 0) printf("| "); 
} 
printf("\n"); 
printf("\n"); 
for (i = 24; i < 36; ++i) 
{ 
printit(four_beat_soprano_melody[i]); 
if ((i+1)%4 == 0) printf("| "); 
} 
printf("\n"); 
for (i = 24; i < 36; ++i) 
{ 
printit(four_beat_alto_melody[i]); 
if ((i+1)%4 == 0) printf("| "); 
} 
printf("\n"); 
for (i = 24; i < 36; ++i) 
{ 
printit(four_beat_bass_melody[i]); 
if ((i+1)%4 == 0) printf("| "); 
} 
printf("\n"); 
printf("\n"); 
for (i = 36; i < 48; ++i) 
{ 
printit(four_beat_soprano_melody[i]); 
if ((i+1)%4 == 0) printf("| "); 
} 
printf("\n"); 
for (i = 36; i < 48; ++i) 
{ 
printit(four_beat_alto_melody[i]); 
if ((i+1)%4 == 0) printf("| "); 
} 
printf("\n"); 
for (i = 36; i < 48; ++i) 
{ 
printit(four_beat_bass_melody[i]); 
if ((i+1)%4 == 0) printf("| "); 
} 
printf("\n"); 
printf("\n"); 
*/
}

void add_more_passing_tones (void)
{
  int i;
  int temp;
  int random_number;
  char ans;
  int beginning_of_measure_bass_note, second_half_bass_note,
    next_measure_bass_note, next_measure_second_half_bass_note;
  int beginning_of_measure_alto_note, second_half_alto_note,
    next_measure_alto_note, next_measure_second_half_alto_note;
  int beginning_of_measure_soprano_note, second_half_soprano_note,
    next_measure_soprano_note, next_measure_second_half_soprano_note;
  int first_bass, second_bass, third_bass, fourth_bass,
    first_alto, second_alto, third_alto,
    fourth_alto, first_soprano, second_soprano, third_soprano, fourth_soprano;
  for (i = 0; i < 48; ++i)
    {
      four_beat_soprano_melody1[i] = four_beat_soprano_melody[i];
      four_beat_alto_melody1[i] = four_beat_alto_melody[i];
      four_beat_bass_melody1[i] = four_beat_bass_melody[i];
    }
  note_bass_counter = 0;
  note_alto_counter = 0;
  note_soprano_counter = 0;
  do
    {
      do
	{
	  found_bass = 0;
	  found_alto = 0;
	  found_soprano = 0;
	  if ((note_bass_counter % 4) == 0)
	    {
/*printf("\nnote_bass_counter = %d\n", note_bass_counter); */
	      for (i = 0; i < 20; ++i)
		if (four_beat_bass_melody[note_bass_counter] ==
		    scale_array[i])
		  beginning_of_measure_bass_note = i;
/*printf("beginning_of_measure_bass_note = %d ",beginning_of_measure_bass_note); 
printf("bass note is "); printit(scale_array[beginning_of_measure_bass_note]); */
	      first_bass = four_beat_bass_melody[note_bass_counter];
/*printf("first_bass = %d  ",first_bass); 
printit(first_bass); 
printf("\n"); */
	      for (i = 0; i < 20; ++i)
		if (four_beat_soprano_melody[note_soprano_counter] ==
		    scale_array[i])
		  beginning_of_measure_soprano_note = i;
/*printf("beginning_of_measure_soprano_note = %d \n ",beginning_of_measure_soprano_note); */
	      first_soprano = four_beat_soprano_melody[note_soprano_counter];
/*printf("first_soprano = %d ",first_soprano); 
printit(first_soprano); 
printf("\n"); */
	      for (i = 0; i < 20; ++i)
		if (four_beat_alto_melody[note_alto_counter] ==
		    scale_array[i])
		  beginning_of_measure_alto_note = i;
/*printf("beginning_of_measure_alto_note = %d \n ",beginning_of_measure_alto_note); */
	      first_alto = four_beat_alto_melody[note_alto_counter];
/*printf("first_alto = %d ",first_alto); 
printit(first_alto); 
printf("\n"); */
	      for (i = 0; i < 20; ++i)
		if (four_beat_bass_melody[note_bass_counter + 2] ==
		    scale_array[i])
		  second_half_bass_note = i;
/*
printf("second_half_bass_note =  %d \n ", second_half_bass_note); */
	      second_bass = four_beat_bass_melody[note_bass_counter + 2];
/*
printf("second_bass = %d  ",second_bass); 
printit(second_bass); 
printf("\n"); */
	      for (i = 0; i < 20; ++i)
		if (four_beat_soprano_melody[note_soprano_counter + 2] ==
		    scale_array[i])
		  second_half_soprano_note = i;
/*printf("second_half_soprano_note =  %d \n ", second_half_soprano_note); */
	      second_soprano =
		four_beat_soprano_melody[note_soprano_counter + 2];
/*printf("second_soprano = %d  ",second_soprano); 
printit(second_soprano); 
printf("\n"); */
	      for (i = 0; i < 20; ++i)
		if (four_beat_alto_melody[note_alto_counter + 2] ==
		    scale_array[i])
		  second_half_alto_note = i;
/*printf("second_half_alto_note =  %d \n ", second_half_alto_note); */
	      second_alto = four_beat_alto_melody[note_alto_counter + 2];
/*printf("second_alto = %d  ",second_alto); 
printit(second_alto); 
printf("\n"); */
	      for (i = 0; i < 20; ++i)
		if (four_beat_bass_melody[note_bass_counter + 4] ==
		    scale_array[i])
		  next_measure_bass_note = i;
/*printf("next_measure_bass_note = %d \n ", next_measure_bass_note); */
	      third_bass = four_beat_bass_melody[note_bass_counter + 4];
/*printf("third_bass = %d  ",third_bass); 
printit(third_bass); 
printf("\n"); */
	      for (i = 0; i < 20; ++i)
		if (four_beat_soprano_melody[note_soprano_counter + 4] ==
		    scale_array[i])
		  next_measure_soprano_note = i;
/*printf("next_measure_soprano_note = %d \n ", next_measure_soprano_note); */
	      third_soprano =
		four_beat_soprano_melody[note_soprano_counter + 4];
/*printf("third_soprano = %d  ",third_soprano); 
printit(third_soprano); 
printf("\n"); */
	      for (i = 0; i < 20; ++i)
		if (four_beat_alto_melody[note_alto_counter + 4] ==
		    scale_array[i])
		  next_measure_alto_note = i;
/*printf("next_measure_alto_note = %d \n ", next_measure_alto_note); */
	      third_alto = four_beat_alto_melody[note_alto_counter + 4];
/*printf("third_alto = %d  ",third_alto); 
printit(third_alto); 
printf("\n"); */
	      for (i = 0; i < 20; ++i)
		if (four_beat_bass_melody[note_bass_counter + 6] ==
		    scale_array[i])
		  next_measure_second_half_bass_note = i;
/*printf("next_measure_second_half_bass_note = %d \n ", next_measure_second_half_bass_note); */
	      fourth_bass = four_beat_bass_melody[note_bass_counter + 6];
/*printf("fourth_bass = %d  ",fourth_bass); 
printit(fourth_bass); 
printf("\n"); */
	      for (i = 0; i < 20; ++i)
		if (four_beat_soprano_melody[note_soprano_counter + 6] ==
		    scale_array[i])
		  next_measure_second_half_soprano_note = i;
/*printf("next_measure_second_half_soprano_note = %d \n ", next_measure_second_half_soprano_note); */
	      fourth_soprano =
		four_beat_soprano_melody[note_soprano_counter + 6];
/*printf("fourth_soprano = %d  ",fourth_soprano); 
printit(fourth_soprano); 
printf("\n"); */
	      for (i = 0; i < 20; ++i)
		if (four_beat_alto_melody[note_alto_counter + 6] ==
		    scale_array[i])
		  next_measure_second_half_alto_note = i;
/*printf("next_measure_second_half_alto_note = %d \n ", next_measure_second_half_alto_note); */
	      fourth_alto = four_beat_alto_melody[note_alto_counter + 6];
/*printf("fourth_alto = %d  ",fourth_alto); 
printit(fourth_alto); 
printf("\n"); */
	      if (second_half_soprano_note + 2 == next_measure_soprano_note
		  && four_beat_soprano_melody[note_soprano_counter + 3] == 12
/* 12 is my construct for a quarter rest */
		  && four_beat_alto_melody[note_alto_counter + 3] == 12
		  && four_beat_bass_melody[note_bass_counter + 3] == 12)
		{
/*printf("FOUND A PASSING TONE ON THE THIRD BEAT\n"); */
		  temp = second_half_soprano_note + 1;
		  if ((((scale_array[temp] -
			 scale_array[second_half_bass_note]) % 12 == 7)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[temp] -
			 scale_array[second_half_bass_note]) % 12 == 12)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_bass_note]) % 12 == 12))
		      ||
		      (((scale_array[temp] -
			 scale_array[second_half_alto_note]) % 12 == 7)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_alto_note]) % 12 == 7))
		      ||
		      (((scale_array[temp] -
			 scale_array[second_half_alto_note]) % 12 == 12)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_alto_note]) % 12 == 12)))
		    {
/*printf("SOPRANO PARALLEL FIFTH OR OCTAVE because temp = "); 
printit(scale_array[temp]); 
scanf("%c", &ans); 
fflush(stdin);  */
		    }
		  else
		    {
/*printf("no parallels\n"); */
		      four_beat_soprano_melody[note_soprano_counter + 3] =
			scale_array[temp];
		      four_beat_layout ();
		    }
		}
	      if (second_half_soprano_note - 2 == next_measure_soprano_note
		  && four_beat_soprano_melody[note_soprano_counter + 3] == 12
		  && four_beat_alto_melody[note_alto_counter + 3] == 12
		  && four_beat_bass_melody[note_bass_counter + 3] == 12)
		{
/*printf("FOUND A PASSING TONE ON THE THIRD BEAT\n");*/
		  temp = second_half_soprano_note - 1;
		  if ((((scale_array[temp] -
			 scale_array[second_half_bass_note]) % 12 == 7)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[temp] -
			 scale_array[second_half_bass_note]) % 12 == 12)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_bass_note]) % 12 == 12))
		      ||
		      (((scale_array[temp] -
			 scale_array[second_half_alto_note]) % 12 == 7)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_alto_note]) % 12 == 7))
		      ||
		      (((scale_array[temp] -
			 scale_array[second_half_alto_note]) % 12 == 12)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_alto_note]) % 12 == 12)))
		    {
/*printf("SOPRANO PARALLEL FIFTH OR OCTAVE because temp = "); 
printit(scale_array[temp]); 
scanf("%c", &ans); 
fflush(stdin); */
		    }
		  else
		    {
/*printf("no  parallels\n"); */
		      four_beat_soprano_melody[note_soprano_counter + 3] =
			scale_array[temp];
		      four_beat_layout ();
		    }
		}
	      else if (second_half_alto_note + 2 == next_measure_alto_note
		       && four_beat_soprano_melody[note_soprano_counter +
						   3] == 12
		       && four_beat_alto_melody[note_alto_counter + 3] == 12
		       && four_beat_bass_melody[note_bass_counter + 3] == 12)
		{
/*printf("FOUND A PASSING TONE ON THE THIRD BEAT\n"); */
		  temp = second_half_alto_note + 1;
		  if ((((scale_array[second_half_soprano_note] -
			 scale_array[temp]) % 12 == 7)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_alto_note]) % 12 == 7))
		      ||
		      (((scale_array[second_half_soprano_note] -
			 scale_array[temp]) % 12 == 12)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_alto_note]) % 12 == 12))
		      ||
		      (((scale_array[temp] -
			 scale_array[second_half_bass_note]) % 12 == 7)
		       &&
		       ((scale_array[next_measure_alto_note] -
			 scale_array[next_measure_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[temp] -
			 scale_array[second_half_bass_note]) % 12 == 12)
		       &&
		       ((scale_array[next_measure_alto_note] -
			 scale_array[next_measure_bass_note]) % 12 == 12)))
		    {
/*printf("ALTO PARALLEL FIFTH OR OCTAVE because temp = "); 
printit(scale_array[temp]); 
scanf("%c", &ans); 
fflush(stdin); */
		    }
		  else
		    {
/*printf("no parallels\n"); */
		      four_beat_alto_melody[note_alto_counter + 3] =
			scale_array[temp];
		      four_beat_layout ();
		    }
		}
	      else if (second_half_alto_note - 2 == next_measure_alto_note
		       && four_beat_soprano_melody[note_soprano_counter +
						   3] == 12
		       && four_beat_alto_melody[note_alto_counter + 3] == 12
		       && four_beat_bass_melody[note_bass_counter + 3] == 12)
		{
/*printf("FOUND A PASSING TONE ON THE THIRD BEAT\n"); */
		  temp = second_half_alto_note - 1;
		  if ((((scale_array[second_half_soprano_note] -
			 scale_array[temp]) % 12 == 7)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_alto_note]) % 12 == 7))
		      ||
		      (((scale_array[second_half_soprano_note] -
			 scale_array[temp]) % 12 == 12)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_alto_note]) % 12 == 12))
		      ||
		      (((scale_array[temp] -
			 scale_array[second_half_bass_note]) % 12 == 7)
		       &&
		       ((scale_array[next_measure_alto_note] -
			 scale_array[next_measure_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[temp] -
			 scale_array[second_half_bass_note]) % 12 == 12)
		       &&
		       ((scale_array[next_measure_alto_note] -
			 scale_array[next_measure_bass_note]) % 12 == 12)))
		    {
/*printf("ALTO PARALLEL FIFTH OR OCTAVE because temp = "); 
printit(scale_array[temp]); 
scanf("%c", &ans); 
fflush(stdin);  */
		    }
		  else
		    {
/*printf("no parallels\n"); */
		      four_beat_alto_melody[note_alto_counter + 3] =
			scale_array[temp];
		      four_beat_layout ();
		    }
		}
	      else if (second_half_bass_note + 2 == next_measure_bass_note
		       && four_beat_soprano_melody[note_soprano_counter +
						   3] == 12
		       && four_beat_alto_melody[note_alto_counter + 3] == 12
		       && four_beat_bass_melody[note_bass_counter + 3] == 12)
		{
/*printf("FOUND A PASSING TONE ON THE THIRD BEAT\n"); */
		  temp = second_half_bass_note + 1;
		  if ((((scale_array[second_half_soprano_note] -
			 scale_array[temp]) % 12 == 7)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[second_half_soprano_note] -
			 scale_array[temp]) % 12 == 12)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_bass_note]) % 12 == 12))
		      ||
		      (((scale_array[second_half_alto_note] -
			 scale_array[temp]) % 12 == 7)
		       &&
		       ((scale_array[next_measure_alto_note] -
			 scale_array[next_measure_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[second_half_alto_note] -
			 scale_array[temp]) % 12 == 12)
		       &&
		       ((scale_array[next_measure_alto_note] -
			 scale_array[next_measure_bass_note]) % 12 == 12)))
		    {
/*
printf("BASS PARALLEL FIFTH OR OCTAVE because temp = "); 
printit(scale_array[temp]); 
scanf("%c", &ans); 
fflush(stdin); 
*/
		    }
		  else
		    {
/*printf("no parallels\n"); */
		      four_beat_bass_melody[note_bass_counter + 3] =
			scale_array[temp];
		      four_beat_layout ();
		    }
		}
	      else if (second_half_bass_note - 2 == next_measure_bass_note
		       && four_beat_soprano_melody[note_soprano_counter +
						   3] == 12
		       && four_beat_alto_melody[note_alto_counter + 3] == 12
		       && four_beat_bass_melody[note_bass_counter + 3] == 12)
		{
/*printf("FOUND A PASSING TONE ON THE THIRD BEAT\n"); */
		  temp = second_half_bass_note - 1;
		  if ((((scale_array[second_half_soprano_note] -
			 scale_array[temp]) % 12 == 7)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[second_half_soprano_note] -
			 scale_array[temp]) % 12 == 12)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_bass_note]) % 12 == 12))
		      ||
		      (((scale_array[second_half_alto_note] -
			 scale_array[temp]) % 12 == 7)
		       &&
		       ((scale_array[next_measure_alto_note] -
			 scale_array[next_measure_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[second_half_alto_note] -
			 scale_array[temp]) % 12 == 12)
		       &&
		       ((scale_array[next_measure_alto_note] -
			 scale_array[next_measure_bass_note]) % 12 == 12)))
		    {
/*printf("BASS PARALLEL FIFTH OR OCTAVE because temp = "); 
printit(scale_array[temp]); 
scanf("%c", &ans); 
fflush(stdin); */
		    }
		  else
		    {
/*printf("no parallels\n"); */
		      four_beat_bass_melody[note_bass_counter + 3] =
			scale_array[temp];
		      four_beat_layout ();
		    }
		}
	      else if ((second_half_soprano_note == next_measure_soprano_note)
		       && (next_measure_soprano_note - 1 !=
			   next_measure_second_half_soprano_note)
		       && four_beat_soprano_melody[note_soprano_counter +
						   3] == 12
		       && four_beat_alto_melody[note_alto_counter + 3] == 12
		       && four_beat_bass_melody[note_bass_counter + 3] == 12)
		{
/*printf("FOUND SOPRANO NEIGHBOR TONE ON SECOND HALF OF MEASURE \n"); */
		  random_number = rand () % (2);
		  if (random_number == 0)
		    temp = second_half_soprano_note + 1;
		  else
		    temp = second_half_soprano_note - 1;
		  if ((((scale_array[temp] -
			 scale_array[second_half_bass_note]) % 12 == 7)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[temp] -
			 scale_array[second_half_bass_note]) % 12 == 12)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_bass_note]) % 12 == 12))
		      ||
		      (((scale_array[temp] -
			 scale_array[second_half_alto_note]) % 12 == 7)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_alto_note]) % 12 == 7))
		      ||
		      (((scale_array[temp] -
			 scale_array[second_half_alto_note]) % 12 == 12)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_alto_note]) % 12 == 12)))
		    {
/*printf("SOPRANO PARALLEL FIFTH OR OCTAVE because temp = "); 
printit(scale_array[temp]); 
scanf("%c", &ans); 
fflush(stdin); 
*/
		    }
		  else
		    {
/*printf("no parallels\n"); */
		      four_beat_soprano_melody[note_soprano_counter + 3] =
			scale_array[temp];
		      four_beat_layout ();
		    }
		}
	      else if ((second_half_alto_note == next_measure_alto_note) &&
		       (next_measure_alto_note - 1 !=
			next_measure_second_half_alto_note)
		       && four_beat_soprano_melody[note_soprano_counter +
						   3] == 12
		       && four_beat_alto_melody[note_alto_counter + 3] == 12
		       && four_beat_bass_melody[note_bass_counter + 3] == 12)
		{
/*printf("ALTO NEIGHBOR TONE ON SECOND HALF OF MEASURE\n"); */
		  random_number = rand () % (2);
		  if (random_number == 0)
		    temp = second_half_alto_note + 1;
		  else
		    temp = second_half_alto_note - 1;
		  if ((((scale_array[temp] -
			 scale_array[second_half_bass_note]) % 12 == 7)
		       &&
		       ((scale_array[next_measure_alto_note] -
			 scale_array[next_measure_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[temp] -
			 scale_array[second_half_bass_note]) % 12 == 12)
		       &&
		       ((scale_array[next_measure_alto_note] -
			 scale_array[next_measure_bass_note]) % 12 == 12))
		      ||
		      (((scale_array[second_half_soprano_note] -
			 scale_array[temp]) % 12 == 7)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_alto_note]) % 12 == 7))
		      ||
		      (((scale_array[second_half_soprano_note] -
			 scale_array[temp]) % 12 == 12)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_alto_note]) % 12 == 12)))
		    {
/*printf("ALTO PARALLEL FIFTH OR OCTAVE because temp = "); 
printit(scale_array[temp]); 
scanf("%c", &ans); 
fflush(stdin); */
		    }
		  else
		    {
/*printf("no parallels\n"); */
		      four_beat_alto_melody[note_alto_counter + 3] =
			scale_array[temp];
		      four_beat_layout ();
		    }
		}
	      else if ((second_half_bass_note == next_measure_bass_note) &&
		       (next_measure_bass_note - 1 !=
			next_measure_second_half_bass_note)
		       && four_beat_soprano_melody[note_soprano_counter +
						   3] == 12
		       && four_beat_alto_melody[note_alto_counter + 3] == 12
		       && four_beat_bass_melody[note_bass_counter + 3] == 12)
		{
/* printf("BASS NEIGHBOR TONES ON SECOND HALF OF MEASURE\n"); */
		  random_number = rand () % (2);
		  if (random_number == 0)
		    temp = second_half_bass_note + 1;
		  else
		    temp = second_half_bass_note - 1;
		  if ((((scale_array[second_half_soprano_note] -
			 scale_array[temp]) % 12 == 7)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[second_half_soprano_note] -
			 scale_array[temp]) % 12 == 12)
		       &&
		       ((scale_array[next_measure_soprano_note] -
			 scale_array[next_measure_bass_note]) % 12 == 12))
		      ||
		      (((scale_array[second_half_alto_note] -
			 scale_array[temp]) % 12 == 7)
		       &&
		       ((scale_array[next_measure_alto_note] -
			 scale_array[next_measure_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[second_half_alto_note] -
			 scale_array[temp]) % 12 == 12)
		       &&
		       ((scale_array[next_measure_alto_note] -
			 scale_array[next_measure_bass_note]) % 12 == 12)))
		    {
/*printf("BASS PARALLEL FIFTH OR OCTAVE because temp = "); 
printit(scale_array[temp]); 
scanf("%c", &ans); 
fflush(stdin); 
*/
		    }
		  else
		    {
/*printf("no parallels\n"); */
		      four_beat_bass_melody[note_bass_counter + 3] =
			scale_array[temp];
		      four_beat_layout ();
		    }
		}
	      else if (four_beat_soprano_melody[note_soprano_counter + 3] !=
		       12
		       && four_beat_bass_melody[note_bass_counter + 3] == 12
		       && four_beat_alto_melody[note_alto_counter + 3] == 12
		       && four_beat_soprano_melody[note_soprano_counter +
						   1] == 12
		       && four_beat_bass_melody[note_bass_counter + 1] == 12
		       && four_beat_alto_melody[note_alto_counter + 1] == 12
		       && four_beat_soprano_melody[note_soprano_counter] ==
		       four_beat_soprano_melody[note_soprano_counter + 2])
		{
		  random_number = rand () % (2);
		  if (random_number == 0)
		    temp = beginning_of_measure_soprano_note + 1;
		  else
		    temp = beginning_of_measure_soprano_note - 1;
/*printf("NOW ADDING SOPRANO NEIGHBOR NOTE ON FIRST HALF\n"); */
		  if ((((scale_array[temp] -
			 scale_array[beginning_of_measure_bass_note]) % 12 ==
			7)
		       &&
		       ((scale_array[second_half_soprano_note] -
			 scale_array[second_half_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[temp] -
			 scale_array[beginning_of_measure_bass_note]) % 12 ==
			12)
		       &&
		       ((scale_array[second_half_soprano_note] -
			 scale_array[second_half_bass_note]) % 12 == 12))
		      ||
		      (((scale_array[temp] -
			 scale_array[beginning_of_measure_alto_note]) % 12 ==
			7)
		       &&
		       ((scale_array[second_half_soprano_note] -
			 scale_array[second_half_alto_note]) % 12 == 7))
		      ||
		      (((scale_array[temp] -
			 scale_array[beginning_of_measure_alto_note]) % 12 ==
			12)
		       &&
		       ((scale_array[second_half_soprano_note] -
			 scale_array[second_half_alto_note]) % 12 == 12)))
		    {
/*printf("SOPRANO PARALLEL FIFTH OR OCTAVE because temp = "); 
printit(scale_array[temp]); 
scanf("%c", &ans); 
fflush(stdin); 
*/
		    }
		  else
		    {
/*printf("HERE IS THE NEW CODE _ WE HAVE A WINNER  no parallels\n");*/
		      four_beat_soprano_melody[note_soprano_counter + 1] =
			scale_array[temp];
		      four_beat_layout ();
		    }
		}
	      else if (four_beat_alto_melody[note_alto_counter + 3] != 12 &&
		       four_beat_bass_melody[note_bass_counter + 3] == 12 &&
		       four_beat_soprano_melody[note_soprano_counter + 3] ==
		       12
		       && four_beat_soprano_melody[note_soprano_counter +
						   1] == 12
		       && four_beat_bass_melody[note_bass_counter + 1] == 12
		       && four_beat_alto_melody[note_alto_counter + 1] == 12
		       && four_beat_alto_melody[note_alto_counter] ==
		       four_beat_alto_melody[note_alto_counter + 2])
		{
		  random_number = rand () % (2);
		  if (random_number == 0)
		    temp = beginning_of_measure_alto_note + 1;
		  else
		    temp = beginning_of_measure_alto_note - 1;
/*printf("NOW ADDING ALTO NEIGHBOR NOTE ON FIRST HALF\n"); */
		  if ((((scale_array[beginning_of_measure_soprano_note] -
			 scale_array[temp]) % 12 == 7)
		       &&
		       ((scale_array[second_half_soprano_note] -
			 scale_array[second_half_alto_note]) % 12 == 7))
		      ||
		      (((scale_array[beginning_of_measure_soprano_note] -
			 scale_array[temp]) % 12 == 12)
		       &&
		       ((scale_array[second_half_soprano_note] -
			 scale_array[second_half_alto_note]) % 12 == 12))
		      ||
		      (((scale_array[temp] -
			 scale_array[beginning_of_measure_bass_note]) % 12 ==
			7)
		       &&
		       ((scale_array[second_half_alto_note] -
			 scale_array[second_half_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[temp] -
			 scale_array[beginning_of_measure_bass_note]) % 12 ==
			12)
		       &&
		       ((scale_array[second_half_alto_note] -
			 scale_array[second_half_bass_note]) % 12 == 12)))
		    {
/*printf("ALTO PARALLEL FIFTH OR OCTAVE because temp = "); 
printit(scale_array[temp]); 
scanf("%c", &ans); 
fflush(stdin); 
*/
		    }
		  else
		    {
/*printf("HERE IS THE NEW CODE _ WE HAVE A WINNER  no parallels\n"); */
		      four_beat_alto_melody[note_alto_counter + 1] =
			scale_array[temp];
		      four_beat_layout ();
		    }
		}
	      else if (four_beat_bass_melody[note_bass_counter + 3] != 12 &&
		       four_beat_alto_melody[note_alto_counter + 3] == 12 &&
		       four_beat_soprano_melody[note_soprano_counter + 3] ==
		       12
		       && four_beat_soprano_melody[note_soprano_counter +
						   1] == 12
		       && four_beat_bass_melody[note_bass_counter + 1] == 12
		       && four_beat_alto_melody[note_alto_counter + 1] == 12
		       && four_beat_bass_melody[note_bass_counter] ==
		       four_beat_bass_melody[note_bass_counter + 2])
		{
		  random_number = rand () % (2);
		  if (random_number == 0)
		    temp = beginning_of_measure_bass_note + 1;
		  else
		    temp = beginning_of_measure_bass_note - 1;
/*printf("NOW ADDING BASS NEIGHBOR NOTE ON FIRST HALF\n"); */
		  if ((((scale_array[beginning_of_measure_soprano_note] -
			 scale_array[temp]) % 12 == 7)
		       &&
		       ((scale_array[second_half_soprano_note] -
			 scale_array[second_half_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[beginning_of_measure_soprano_note] -
			 scale_array[temp]) % 12 == 12)
		       &&
		       ((scale_array[second_half_soprano_note] -
			 scale_array[second_half_bass_note]) % 12 == 12))
		      ||
		      (((scale_array[beginning_of_measure_alto_note] -
			 scale_array[temp]) % 12 == 7)
		       &&
		       ((scale_array[second_half_alto_note] -
			 scale_array[second_half_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[beginning_of_measure_alto_note] -
			 scale_array[temp]) % 12 == 12)
		       &&
		       ((scale_array[second_half_alto_note] -
			 scale_array[second_half_bass_note]) % 12 == 12)))
		    {
/*
printf("BASS PARALLEL FIFTH OR OCTAVE because temp = "); 
printit(scale_array[temp]); 
scanf("%c", &ans); 
fflush(stdin); 
*/
		    }
		  else
		    {
/*printf("HERE IS THE NEW CODE _ WE HAVE A WINNER  no parallels\n"); */
		      four_beat_bass_melody[note_bass_counter + 1] =
			scale_array[temp];
		      four_beat_layout ();
		    }
		}
	      else if (four_beat_soprano_melody[note_soprano_counter + 3] !=
		       12
		       && four_beat_bass_melody[note_bass_counter + 3] == 12
		       && four_beat_alto_melody[note_alto_counter + 3] == 12
		       && four_beat_soprano_melody[note_soprano_counter +
						   1] == 12
		       && four_beat_bass_melody[note_bass_counter + 1] == 12
		       && four_beat_alto_melody[note_alto_counter + 1] == 12
		       && beginning_of_measure_soprano_note + 2 ==
		       second_half_soprano_note)
		{
		  temp = beginning_of_measure_soprano_note + 1;
/* printf("NOW ADDING SOPRANO PASSING NOTE ON FIRST HALF\n"); */
		  if ((((scale_array[temp] -
			 scale_array[beginning_of_measure_bass_note]) % 12 ==
			7)
		       &&
		       ((scale_array[second_half_soprano_note] -
			 scale_array[second_half_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[temp] -
			 scale_array[beginning_of_measure_bass_note]) % 12 ==
			12)
		       &&
		       ((scale_array[second_half_soprano_note] -
			 scale_array[second_half_bass_note]) % 12 == 12))
		      ||
		      (((scale_array[temp] -
			 scale_array[beginning_of_measure_alto_note]) % 12 ==
			7)
		       &&
		       ((scale_array[second_half_soprano_note] -
			 scale_array[second_half_alto_note]) % 12 == 7))
		      ||
		      (((scale_array[temp] -
			 scale_array[beginning_of_measure_alto_note]) % 12 ==
			12)
		       &&
		       ((scale_array[second_half_soprano_note] -
			 scale_array[second_half_alto_note]) % 12 == 12)))
		    {
/*printf("SOPRANO PARALLEL FIFTH OR OCTAVE because temp = "); 
printit(scale_array[temp]); 
scanf("%c", &ans);               
fflush(stdin); */
		    }
		  else
		    {
/* printf("HERE IS THE NEW CODE _ WE HAVE A WINNER  no parallels\n"); */
		      four_beat_soprano_melody[note_soprano_counter + 1] =
			scale_array[temp];
		      four_beat_layout ();
		    }
		}
	      else if (four_beat_soprano_melody[note_soprano_counter + 3] !=
		       12
		       && four_beat_bass_melody[note_bass_counter + 3] == 12
		       && four_beat_alto_melody[note_alto_counter + 3] == 12
		       && four_beat_soprano_melody[note_soprano_counter +
						   1] == 12
		       && four_beat_bass_melody[note_bass_counter + 1] == 12
		       && four_beat_alto_melody[note_alto_counter + 1] == 12
		       && beginning_of_measure_soprano_note - 2 ==
		       second_half_soprano_note)
		{
		  temp = beginning_of_measure_soprano_note - 1;
/*printf("NOW ADDING SOPRANO PASSING NOTE ON FIRST HALF\n"); */
		  if ((((scale_array[temp] -
			 scale_array[beginning_of_measure_bass_note]) % 12 ==
			7)
		       &&
		       ((scale_array[second_half_soprano_note] -
			 scale_array[second_half_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[temp] -
			 scale_array[beginning_of_measure_bass_note]) % 12 ==
			12)
		       &&
		       ((scale_array[second_half_soprano_note] -
			 scale_array[second_half_bass_note]) % 12 == 12))
		      ||
		      (((scale_array[temp] -
			 scale_array[beginning_of_measure_alto_note]) % 12 ==
			7)
		       &&
		       ((scale_array[second_half_soprano_note] -
			 scale_array[second_half_alto_note]) % 12 == 7))
		      ||
		      (((scale_array[temp] -
			 scale_array[beginning_of_measure_alto_note]) % 12 ==
			12)
		       &&
		       ((scale_array[second_half_soprano_note] -
			 scale_array[second_half_alto_note]) % 12 == 12)))
		    {
/*printf("SOPRANO PARALLEL FIFTH OR OCTAVE because temp = "); 
printit(scale_array[temp]); 
scanf("%c", &ans); 
fflush(stdin); */
		    }
		  else
		    {
/*printf("HERE IS THE NEW CODE _ WE HAVE A WINNER  no parallels\n"); */
		      four_beat_soprano_melody[note_soprano_counter + 1] =
			scale_array[temp];
		      four_beat_layout ();
		    }
		}
	      else if (four_beat_alto_melody[note_alto_counter + 3] != 12 &&
		       four_beat_bass_melody[note_bass_counter + 3] == 12 &&
		       four_beat_soprano_melody[note_soprano_counter + 3] ==
		       12
		       && four_beat_soprano_melody[note_soprano_counter +
						   1] == 12
		       && four_beat_bass_melody[note_bass_counter + 1] == 12
		       && four_beat_alto_melody[note_alto_counter + 1] == 12
		       && beginning_of_measure_alto_note + 2 ==
		       second_half_alto_note)
		{
		  temp = beginning_of_measure_alto_note + 1;
/*printf("NOW ADDING ALTO PASSING NOTE ON FIRST HALF\n"); */
		  if ((((scale_array[beginning_of_measure_soprano_note] -
			 scale_array[temp]) % 12 == 7)
		       &&
		       ((scale_array[second_half_soprano_note] -
			 scale_array[second_half_alto_note]) % 12 == 7))
		      ||
		      (((scale_array[beginning_of_measure_soprano_note] -
			 scale_array[temp]) % 12 == 12)
		       &&
		       ((scale_array[second_half_soprano_note] -
			 scale_array[second_half_alto_note]) % 12 == 12))
		      ||
		      (((scale_array[temp] -
			 scale_array[beginning_of_measure_bass_note]) % 12 ==
			7)
		       &&
		       ((scale_array[second_half_alto_note] -
			 scale_array[second_half_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[temp] -
			 scale_array[beginning_of_measure_bass_note]) % 12 ==
			12)
		       &&
		       ((scale_array[second_half_alto_note] -
			 scale_array[second_half_bass_note]) % 12 == 12)))
		    {
/*printf("ALTO PARALLEL FIFTH OR OCTAVE because temp = "); 
printit(scale_array[temp]); 
scanf("%c", &ans); 
fflush(stdin); */
		    }
		  else
		    {
/*printf("HERE IS THE NEW CODE _ WE HAVE A WINNER  no parallels\n"); */
		      four_beat_alto_melody[note_alto_counter + 1] =
			scale_array[temp];
		      four_beat_layout ();
		    }
		}
	      else if (four_beat_alto_melody[note_alto_counter + 3] != 12 &&
		       four_beat_bass_melody[note_bass_counter + 3] == 12 &&
		       four_beat_soprano_melody[note_soprano_counter + 3] ==
		       12
		       && four_beat_soprano_melody[note_soprano_counter +
						   1] == 12
		       && four_beat_bass_melody[note_bass_counter + 1] == 12
		       && four_beat_alto_melody[note_alto_counter + 1] == 12
		       && beginning_of_measure_alto_note - 2 ==
		       second_half_alto_note)
		{
		  temp = beginning_of_measure_alto_note - 1;
/*printf("NOW ADDING ALTO PASSING NOTE ON FIRST HALF\n"); */
		  if ((((scale_array[beginning_of_measure_soprano_note] -
			 scale_array[temp]) % 12 == 7)
		       &&
		       ((scale_array[second_half_soprano_note] -
			 scale_array[second_half_alto_note]) % 12 == 7))
		      ||
		      (((scale_array[beginning_of_measure_soprano_note] -
			 scale_array[temp]) % 12 == 12)
		       &&
		       ((scale_array[second_half_soprano_note] -
			 scale_array[second_half_alto_note]) % 12 == 12))
		      ||
		      (((scale_array[temp] -
			 scale_array[beginning_of_measure_bass_note]) % 12 ==
			7)
		       &&
		       ((scale_array[second_half_alto_note] -
			 scale_array[second_half_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[temp] -
			 scale_array[beginning_of_measure_bass_note]) % 12 ==
			12)
		       &&
		       ((scale_array[second_half_alto_note] -
			 scale_array[second_half_bass_note]) % 12 == 12)))
		    {
/*printf("ALTO PARALLEL FIFTH OR OCTAVE because temp = "); 
printit(scale_array[temp]); 
scanf("%c", &ans); 
fflush(stdin); 
*/
		    }
		  else
		    {
/*printf("HERE IS THE NEW CODE _ WE HAVE A WINNER  no parallels\n");*/
		      four_beat_alto_melody[note_alto_counter + 1] =
			scale_array[temp];
		      four_beat_layout ();
		    }
		}
	      else if (four_beat_bass_melody[note_bass_counter + 3] != 12 &&
		       four_beat_alto_melody[note_alto_counter + 3] == 12 &&
		       four_beat_soprano_melody[note_soprano_counter + 3] ==
		       12
		       && four_beat_soprano_melody[note_soprano_counter +
						   1] == 12
		       && four_beat_bass_melody[note_bass_counter + 1] == 12
		       && four_beat_alto_melody[note_alto_counter + 1] == 12
		       && beginning_of_measure_bass_note + 2 ==
		       second_half_bass_note)
		{
		  temp = beginning_of_measure_bass_note + 1;
/*printf("NOW ADDING BASS PASSING NOTE ON FIRST HALF\n"); */
		  if ((((scale_array[beginning_of_measure_soprano_note] -
			 scale_array[temp]) % 12 == 7)
		       &&
		       ((scale_array[second_half_soprano_note] -
			 scale_array[second_half_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[beginning_of_measure_soprano_note] -
			 scale_array[temp]) % 12 == 12)
		       &&
		       ((scale_array[second_half_soprano_note] -
			 scale_array[second_half_bass_note]) % 12 == 12))
		      ||
		      (((scale_array[beginning_of_measure_alto_note] -
			 scale_array[temp]) % 12 == 7)
		       &&
		       ((scale_array[second_half_alto_note] -
			 scale_array[second_half_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[beginning_of_measure_alto_note] -
			 scale_array[temp]) % 12 == 12)
		       &&
		       ((scale_array[second_half_alto_note] -
			 scale_array[second_half_bass_note]) % 12 == 12)))
		    {
/*
printf("BASS PARALLEL FIFTH OR OCTAVE because temp = "); 
printit(scale_array[temp]); 
scanf("%c", &ans); 
fflush(stdin); */
		    }
		  else
		    {
/*printf("HERE IS THE NEW CODE _ WE HAVE A WINNER  no parallels\n"); */
		      four_beat_bass_melody[note_bass_counter + 1] =
			scale_array[temp];
		      four_beat_layout ();
		    }
		}
	      else if (four_beat_bass_melody[note_bass_counter + 3] != 12 &&
		       four_beat_alto_melody[note_alto_counter + 3] == 12 &&
		       four_beat_soprano_melody[note_soprano_counter + 3] ==
		       12
		       && four_beat_soprano_melody[note_soprano_counter +
						   1] == 12
		       && four_beat_bass_melody[note_bass_counter + 1] == 12
		       && four_beat_alto_melody[note_alto_counter + 1] == 12
		       && beginning_of_measure_bass_note - 2 ==
		       second_half_bass_note)
		{
		  temp = beginning_of_measure_bass_note - 1;
/*printf("NOW ADDING BASS PASSING NOTE ON FIRST HALF\n"); */
		  if ((((scale_array[beginning_of_measure_soprano_note] -
			 scale_array[temp]) % 12 == 7)
		       &&
		       ((scale_array[second_half_soprano_note] -
			 scale_array[second_half_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[beginning_of_measure_soprano_note] -
			 scale_array[temp]) % 12 == 12)
		       &&
		       ((scale_array[second_half_soprano_note] -
			 scale_array[second_half_bass_note]) % 12 == 12))
		      ||
		      (((scale_array[beginning_of_measure_alto_note] -
			 scale_array[temp]) % 12 == 7)
		       &&
		       ((scale_array[second_half_alto_note] -
			 scale_array[second_half_bass_note]) % 12 == 7))
		      ||
		      (((scale_array[beginning_of_measure_alto_note] -
			 scale_array[temp]) % 12 == 12)
		       &&
		       ((scale_array[second_half_alto_note] -
			 scale_array[second_half_bass_note]) % 12 == 12)))
		    {
/*printf("BASS PARALLEL FIFTH OR OCTAVE because temp = "); 
printit(scale_array[temp]); 
scanf("%c", &ans); 
fflush(stdin); */
		    }
		  else
		    {
/*printf("HERE IS THE NEW CODE _ WE HAVE A WINNER  no parallels\n"); */
		      four_beat_bass_melody[note_bass_counter + 1] =
			scale_array[temp];
		      four_beat_layout ();
		    }
		}
/*scanf("%c", &ans); 
fflush(stdin); */
	    }
	  ++note_bass_counter;
	  ++note_alto_counter;
	  ++note_soprano_counter;
	}
      while (found_bass == 0 && note_bass_counter < 19 * 2);
      if (found_bass == 0)
	{
	  note_bass_counter = 21 * 2;
/*printf("note_bass_counter = %d\n", note_bass_counter); */
	}
    }
  while (note_bass_counter < 20 * 2);
/* end of do-while started at beginning of function */
}

void play_counterpoint (void)
{
  int i;
  char ans;
  int transposefactor = 0;	/*  5 - rand()%(5); */
  for (i = 1; i < 48; ++i)
    {
      if (four_beat_bass_melody[i] == 12)
	four_beat_bass_melody[i] = four_beat_bass_melody[i - 1];
      if (four_beat_alto_melody[i] == 12)
	four_beat_alto_melody[i] = four_beat_alto_melody[i - 1];
      if (four_beat_soprano_melody[i] == 12)
	four_beat_soprano_melody[i] = four_beat_soprano_melody[i - 1];
    }
/*printf("HERE IS THE NEW ARRAY FOR PLAYING\n"); */
  four_beat_layout ();
/*scanf("%c", &ans); 
fflush(stdin); */
  play (0, 147, four_beat_bass_melody[0] + transposefactor, 127);
  play (0, 146, four_beat_alto_melody[0] + transposefactor, 127);
  play (0, 145, four_beat_soprano_melody[0] + transposefactor, 127);
  play (48 * 2, 144 - 16, 60, 0);
  for (i = 1; i < 48; ++i)
/* starts on second eighth note unit of measure, and moves to end */
    {
      if ((i % 4 == 0)
	  && (four_beat_soprano_melody[i - 1] == four_beat_soprano_melody[i])
	  && (four_beat_soprano_melody[i] != four_beat_soprano_melody[i + 1]))
	{
	  play (0, 145 - 16,
		four_beat_soprano_melody[i - 1] + transposefactor, 0);
	  play (0, 145, four_beat_soprano_melody[i] + transposefactor, 127);
	}
      else if ((i % 4 == 0)
	       && (four_beat_soprano_melody[i - 2] ==
		   four_beat_soprano_melody[i - 1])
	       && (four_beat_soprano_melody[i - 1] ==
		   four_beat_soprano_melody[i])
	       && (four_beat_soprano_melody[i] ==
		   four_beat_soprano_melody[i + 1])
	       && (four_beat_soprano_melody[i + 1] ==
		   four_beat_soprano_melody[i + 2]))
	{
	  play (0, 145 - 16,
		four_beat_soprano_melody[i - 1] + transposefactor, 0);
	  play (0, 145, four_beat_soprano_melody[i] + transposefactor, 127);
	}
      else if (four_beat_soprano_melody[i] != four_beat_soprano_melody[i - 1])
	{
	  play (0, 145 - 16,
		four_beat_soprano_melody[i - 1] + transposefactor, 0);
	  play (0, 145, four_beat_soprano_melody[i] + transposefactor, 127);
	}
      if ((i % 4 == 0)
	  && (four_beat_alto_melody[i - 1] == four_beat_alto_melody[i])
	  && (four_beat_alto_melody[i] != four_beat_alto_melody[i + 1]))
	{
	  play (0, 146 - 16, four_beat_alto_melody[i - 1] + transposefactor,
		0);
	  play (0, 146, four_beat_alto_melody[i] + transposefactor, 127);
	}
      else if ((i % 4 == 0)
	       && (four_beat_alto_melody[i - 2] ==
		   four_beat_alto_melody[i - 1])
	       && (four_beat_alto_melody[i - 1] == four_beat_alto_melody[i])
	       && (four_beat_alto_melody[i] == four_beat_alto_melody[i + 1])
	       && (four_beat_alto_melody[i + 1] ==
		   four_beat_alto_melody[i + 2]))
	{
	  play (0, 146 - 16, four_beat_alto_melody[i - 1] + transposefactor,
		0);
	  play (0, 146, four_beat_alto_melody[i] + transposefactor, 127);
	}
      else if (four_beat_alto_melody[i] != four_beat_alto_melody[i - 1])
	{
	  play (0, 146 - 16, four_beat_alto_melody[i - 1] + transposefactor,
		0);
	  play (0, 146, four_beat_alto_melody[i] + transposefactor, 127);
	}
      if ((i % 4 == 0)
	  && (four_beat_bass_melody[i - 1] == four_beat_bass_melody[i])
	  && (four_beat_bass_melody[i] != four_beat_bass_melody[i + 1]))
	{
	  play (0, 147 - 16, four_beat_bass_melody[i - 1] + transposefactor,
		0);
	  play (0, 147, four_beat_bass_melody[i] + transposefactor, 127);
	}
      else if ((i % 4 == 0)
	       && (four_beat_bass_melody[i - 2] ==
		   four_beat_bass_melody[i - 1])
	       && (four_beat_bass_melody[i - 1] == four_beat_bass_melody[i])
	       && (four_beat_bass_melody[i] == four_beat_bass_melody[i + 1])
	       && (four_beat_bass_melody[i + 1] ==
		   four_beat_bass_melody[i + 2]))
	{
	  play (0, 147 - 16, four_beat_bass_melody[i - 1] + transposefactor,
		0);
	  play (0, 147, four_beat_bass_melody[i] + transposefactor, 127);
	}
      else if (four_beat_bass_melody[i] != four_beat_bass_melody[i - 1])
	{
	  play (0, 147 - 16, four_beat_bass_melody[i - 1] + transposefactor,
		0);
	  play (0, 147, four_beat_bass_melody[i] + transposefactor, 127);
	}
      play (48 * 2, 144 - 16, 60, 0);
    }
  play (0, 145 - 16, four_beat_soprano_melody[47] + transposefactor, 0);
  play (0, 146 - 16, four_beat_alto_melody[47] + transposefactor, 0);
  play (0, 147 - 16, four_beat_bass_melody[47] + transposefactor, 0);
}

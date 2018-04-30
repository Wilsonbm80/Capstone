/*   motivic.c
This uses 20th and 21st century devices, as well as ideas based on 
Indian (Hindustan) rhythms, medieval isorhythm,isomelody, 
parallelism,polychord with triad and quartal chords, 
chromatic third relationships and atonal operations. 
Motives are 4 different notes by random except
for one case where the motive is extended to a fifth note. 
Atonal operations are performed on the motives; the 
inversion, the retrograde, and retrograde inversion and 
of course transposition. In addition the motive may be 
in mixed order in secondary motives. Chords may appear 
as be major or minor using 1st, 3rd or 5th of chord using
a common note of motive, if in bass, in open wide position; if
above motive, closed, narrow position. Chords may be related by
real parallelism in which every note of the motive determines the
chord. Or chords may be in a chromatic third relationship with
each other, with no relationship to the motive except first chord.
Chords may also be polychords with notes of one of the motive
forms being 5th of chord in soprano and 1st of other motive
form the chord in bass. The Polychords may be major chords
(for brighness) or quartal chords. Chords may also be constructed
from the motive or any form of the motive. Silence and Unision
Harmonies, esp. at the beginning of a 'section' should not
be underestimated. 'Sections' are varied by mixing the order
of different types of sections randomly. A vary important part
is the use of rhythm. Single generated drum beats may be a part
of the measure, or overlapping patterns of 5 beats with 6 beats
with 7 beats with 8 beats, until all beats come together, as in
the Indian Tihai. The rhythmic ostinatos change frequently. 
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "convert3.h"
#define GENERAL_MIDI_ON 1
#define PROGRAM_NUMBERS_ON 1
#define RHYTHMPATTERN 5
#define RHYTHMPATTERN1 6
#define RHYTHMPATTERN2 7
#define RHYTHMPATTERN3 8
// kirk > picard 
int sopsound[3];
int basssound[3];
int ostinato[28];
int random_rhythm[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
int channel[8] = { 144, 145, 146, 147, 148, 149, 149, 149 };

int transposefactor;
int tempo;
int volume;
int motive[4];
int inversion[4];
int retrograde[4];
int retroinver[4];
int mixedmotive1[4];
int mixedmotive2[4];
int mixedmotive3[4];
int mixedinversion1[4];
int mixedinversion2[4];
int mixedinversion3[4];
int motivenewnote[5];
int sound[3];			/* for triads or quartal chords */
int sounds1[4];			/* for motive types */
int sounds2[4];			/* once for each voice channel */
int sounds3[4];
int sounds4[4];
int rhythmarray[RHYTHMPATTERN];
int rhythmarray1[RHYTHMPATTERN1];
int rhythmarray2[RHYTHMPATTERN2];
int rhythmarray3[RHYTHMPATTERN3];
int rhythmmarker;
int rhythmmarker1;
int rhythmmarker2;
int rhythmmarker3;
void loadnotes (void);
void operations_on_motives (void);
void makeminortreble (int note);
void makemajortreble (int note);
void makemajorbass (int note);
void makeminormiddle (int note);
void makeminorbass (int note);
void makequartalbass (int note);
void makequartaltreble (int note);
void chromthirdmintomaj (int note);
void chromthirdmintomin (int note);
void chromthirdmajtomin (int note);
void chromthirdmajtomaj (int note);
void makerhythmicpattern (void);
void playrhythmicarray (void);
void playrhythmicarray1 (void);
void playrhythmicarray2 (void);
void playrhythmicarray3 (void);
void playrhythmicarray3a (void);
void playrhythmicarray3b (void);
void playrhythmicarray3c (void);
void playrhythmicarray3d (void);
void playrhythmicarray4 (void);
void ostinatorhythmpart1 (void);
void ostinatorhythmpart2 (void);
void ostinatorhythmpart3 (void);
void ostinatorhythmpart4 (void);
void procedure1 (void);
/* beginning of motive */
void procedure2 (void);
/* short silence */
void procedure3 (void);
/* motive modified */
void procedure3a (void);
/* motive with sustaining low note
and secondary modified motive */
void procedure3b (void);
/* motive in sixths with sustaining 
low note and secondary modified
motive and drum rhythm */
void procedure3c (void);
/* motive in first inversion chords
with sustaining low note and secondary
modified motive transposed higher */
void procedure3d (void);
/* motive with secondary motive in 
sixths with sustaining low note
and drums transposed higher still */
void procedure3e (void);
/* retrograde inversion in sixths
with low sustaining note with 
secondary motive and drums 
transposed higher still */
void procedure3f (void);
/* simple motive with drums */
void procedure3g (void);
/* simple retrograde with drums */
void procedure3h (void);
/* wide variety of techniques from above */
void procedure3i (void);
/* retrograde and motive together, 
one high, one low */
void procedure4 (void);
/* longer silence */
void procedure5 (void);
/* inversion motive */
void procedure6 (void);
/* mixed motive */
void procedure7 (void);
/* different mixed motive */
void procedure9 (void);
/* addes new note to motive */
void procedure10 (void);
/* plays only the new note */
void procedure11 (void);
/* play a broken harp accompaniment 
melody under slow flute melody */
void procedure12 (void);
/* minor chord put to rhythmic pattern repeated */
void procedure13 (void);
/* series of chormatic third relationships */
void procedure14a (void);
/* four note motive combined with 
five note motive repeated make two 
ostinatos out of phase */
void procedure14b (void);
/* same as above but faster */
void procedure14c (void);
/* same as 14a but with inversion */
void procedure14d (void);
/* same as above but faster */
void procedure14e (void);
/* same as above but with motive */
void procedure15 (void);
/* motive and retrograde inversion together*/
void procedure15a (void);
/* procedure 15 but in  polychords (triads) */
void procedure15b (void);
/* procedure 15 but in polyquartalchords  */
void procedure15c (void);
/* procedure 15 but but in polychords (triads) again  */
void procedure15z (void);
/* long silence */
void procedure15_1 (void);
/* motive  and retrograde inversion together */
void procedure15a_1 (void);
/* polychords with 4 ostinato drums of different lenghts */
void procedure15b_1 (void);
/* quartalchords with 2 ostinato 
motives of 4 and 5 overlapping */
void procedure15c_1 (void);
/* basically the same as procedure15a_1 */
void procedure15z_1 (void);
/* silence */
void procedure16 (void);
/* same but with new note and its retrograde */
void procedure16a (void);
/* similar to 15a */
void procedure16b (void);
/* similar to 15b */
void procedure16c (void);
/* similar to 15c */
void procedure16z (void);
/* very long silence */
void procedure16_1 (void);
/* motive and its retrograde */
void procedure16a_1 (void);
/* similar to 15a_1 */
void procedure16b_1 (void);
/* similar to 15b_1 */
void procedure16c_1 (void);
/* similar to 15c_1 */
void procedure16z_1 (void);
/* very long silence */
void procedure17 (void);
/* two single voices mixed */
void subprocedure18 (void);
/* making the atonal form from the motive, 
plus mixed notes of motive, and the 
5 note motive with the new note */
void procedure18 (void);
/* rising with motive forms as parellel 
first inversion chords (parallelism) 
with low sustained note of each motive   */
void procedure18a (void);
/* rising motive forms as solo melody 
with minor chord sustained as the first, 
or third, or fifth note of the chord 
being the first note of the motive */
void procedure19 (void);
/* good close of piece - all 
instruments on retrogradeinversion  
slow and loud */
void procedure20 (void);
/* rhythmic section  with all drums 
playing overlapping ostinato rhythms 
plus piano playing motive notes 
when osinatos come together */

int main (void)
{
  int i, op;
  time_t t;
  open_midfiles ();
#if GENERAL_MIDI_ON
  general_midi ();
#endif
  srand ((unsigned) time (&t));
  transposefactor = 1;
  tempo = 48;
  loadnotes ();
  operations_on_motives ();
  subprocedure18 ();
  makerhythmicpattern ();
  play (48 * 2 * 4, 152 - 16, 100, 0);	/* Handshake */
  program_number[0] = 73;
  program_number[1] = 46;
  program_number[2] = 61;
  program_number[3] = 48;
  program_number[4] = 0;
  program_number[5] = 0;
  program_number[6] = 0;
  program_number[7] = 0;
  program_setup ();

  for (i = 0; i < 100; ++i)
    {
      op = rand () % 41;
      if (op == 0)
	procedure1 ();
      if (op == 1)
	procedure3 ();
      if (op == 2)
	procedure3a ();
      if (op == 3)
	procedure3b ();
      if (op == 4)
	procedure3c ();
      if (op == 5)
	procedure3d ();
      if (op == 6)
	procedure3e ();
      if (op == 7)
	procedure3f ();
      if (op == 8)
	procedure3g ();
      if (op == 9)
	procedure3h ();
      if (op == 10)
	procedure3i ();
      if (op == 11)
	procedure18 ();
      if (op == 12)
	procedure4 ();
      if (op == 13)
	procedure5 ();
      if (op == 14)
	procedure6 ();
      if (op == 15)
	procedure7 ();
      if (op == 16)
	procedure9 ();
      if (op == 17)
	procedure10 ();
      if (op == 18)
	procedure11 ();
      if (op == 19)
	procedure12 ();
      if (op == 20)
	procedure13 ();
      if (op == 21)
	procedure14a ();
      if (op == 22)
	procedure14b ();
      if (op == 23)
	procedure14c ();
      if (op == 24)
	procedure14d ();
      if (op == 25)
	procedure14e ();
      if (op == 26)
	procedure15 ();
      if (op == 27)
	procedure15a ();
      if (op == 28)
	procedure15b ();
      if (op == 29)
	procedure15c ();
      if (op == 30)
	procedure15z ();
      if (op == 31)
	procedure16 ();
      if (op == 32)
	procedure16a ();
      if (op == 33)
	procedure16b ();
      if (op == 34)
	procedure16c ();
      if (op == 35)
	procedure16z ();
      if (op == 36)
	procedure17 ();
      if (op == 37)
	procedure18 ();
      if (op == 38)
	procedure18a ();
      if (op == 39)
	procedure19 ();
      if (op == 40)
	procedure20 ();
    }

  close_midfiles ();
  return (1);
}

void procedure1 (void)
{
  int i;
  subprocedure18 ();
  for (i = 0; i < 4; ++i)
    {
      play (0, channel[0], motive[i] + 60, 50);
      play (tempo * 4, 152 - 16, 100, 0);
      play (0, channel[0] - 16, motive[i] + 60, 0);
    }
  play (tempo * 4, 152 - 16, 100, 0);
  for (i = 0; i < 4; ++i)
    {
      play (0, channel[0], motive[i] + 60 + 12, 50);
      play (tempo, 152 - 16, 100, 0);
      play (0, channel[0] - 16, motive[i] + 60 + 12, 0);
    }
  for (i = 0; i < 4; ++i)
    {
      play (0, channel[0], motive[i] + 60 + 12 + 12, 50);
      play (tempo / 4, 152 - 16, 100, 0);
      play (0, channel[0] - 16, motive[i] + 60 + 12 + 12, 0);
    }
}

void procedure2 (void)
{
  play (tempo * 2, 152 - 16, 100, 0);
}

void procedure3 (void)
{
  int i;
  subprocedure18 ();
  for (i = 0; i < 4; ++i)
    {
      play (0, channel[0], inversion[i] + 60 + 12, 50);
      play (tempo, 152 - 16, 100, 0);
      play (0, channel[0] - 16, inversion[i] + 60 + 12, 0);
    }
  for (i = 0; i < 4; ++i)
    {
      play (0, channel[3], inversion[i] + 24, 90);
      playrhythmicarray ();
      play (0, channel[3] - 16, inversion[i] + 24, 0);
    }
}

void procedure3a (void)
{
  int i;
  subprocedure18 ();
  play (0, channel[3], motive[0] + 24, 70);
  play (0, channel[0], motive[0] + 60, 40);
  for (i = 0; i < 4; ++i)
    {
      play (0, channel[3], sounds1[i] + 48, 35);
      play (32 * 2, 152 - 16, 100, 0);
      play (0, channel[3] - 16, sounds1[i] + 48, 0);
    }
  play (0, channel[0] - 16, motive[0] + 60, 0);
  play (0, channel[0], motive[1] + 60, 40);
  for (i = 0; i < 4; ++i)
    {
      play (0, channel[3], sounds1[i] + 48, 35);
      play (32 * 2, 152 - 16, 100, 0);
      play (0, channel[3] - 16, sounds1[i] + 48, 0);
    }
  play (0, channel[0] - 16, motive[1] + 60, 0);
  play (0, channel[0], motive[2] + 60, 40);
  for (i = 0; i < 4; ++i)
    {
      play (0, channel[3], sounds1[i] + 48, 35);
      play (32 * 2, 152 - 16, 100, 0);
      play (0, channel[3] - 16, sounds1[i] + 48, 0);
    }
  play (0, channel[0] - 16, motive[2] + 60, 0);
  play (0, channel[0], motive[3] + 60, 40);
  for (i = 0; i < 4; ++i)
    {
      play (0, channel[3], sounds1[i] + 48, 35);
      play (32 * 2, 152 - 16, 100, 0);
      play (0, channel[3] - 16, sounds1[i] + 48, 0);
    }
  play (0, channel[0] - 16, motive[3] + 60, 0);
  play (0, channel[3] - 16, motive[0] + 24, 0);
}

void procedure3b (void)
{
  int i;
  procedure3a ();
  subprocedure18 ();
  play (0, channel[3], motive[0] + 24, 70);
  play (0, channel[0], motive[0] + 60 + 12, 40);
  play (0, channel[0], motive[0] + 60 + 12 - 9, 40);
  for (i = 0; i < 4; ++i)
    {
      play (0, channel[3], sounds1[i] + 48, 35);
      if (i == 0)
	playrhythmicarray3a ();
      else if (i == 1)
	playrhythmicarray3b ();
      else if (i == 2)
	playrhythmicarray3c ();
      else if (i == 3)
	playrhythmicarray3d ();
      play (0, channel[3] - 16, sounds1[i] + 48, 0);
    }
  play (0, channel[0] - 16, motive[0] + 60 + 12, 0);
  play (0, channel[0] - 16, motive[0] + 60 + 12 - 9, 0);
  play (0, channel[0], motive[1] + 60 + 12, 40);
  play (0, channel[0], motive[1] + 60 + 12 - 9, 40);
  for (i = 0; i < 4; ++i)
    {
      play (0, channel[3], sounds1[i] + 48, 35);
      if (i == 0)
	playrhythmicarray3a ();
      else if (i == 1)
	playrhythmicarray3b ();
      else if (i == 2)
	playrhythmicarray3c ();
      else if (i == 3)
	playrhythmicarray3d ();
      play (0, channel[3] - 16, sounds1[i] + 48, 0);
    }
  play (0, channel[0] - 16, motive[1] + 60 + 12, 0);
  play (0, channel[0] - 16, motive[1] + 60 + 12 - 9, 0);
  play (0, channel[0], motive[2] + 60 + 12, 40);
  play (0, channel[0], motive[2] + 60 + 12 - 9, 40);
  for (i = 0; i < 4; ++i)
    {
      play (0, channel[3], sounds1[i] + 48, 35);
      if (i == 0)
	playrhythmicarray3a ();
      else if (i == 1)
	playrhythmicarray3b ();
      else if (i == 2)
	playrhythmicarray3c ();
      else if (i == 3)
	playrhythmicarray3d ();
      play (0, channel[3] - 16, sounds1[i] + 48, 0);
    }
  play (0, channel[0] - 16, motive[2] + 60 + 12, 0);
  play (0, channel[0] - 16, motive[2] + 60 + 12 - 9, 0);
  play (0, channel[0], motive[3] + 60 + 12, 40);
  play (0, channel[0], motive[3] + 60 + 12 - 9, 40);
  for (i = 0; i < 4; ++i)
    {
      play (0, channel[3], sounds1[i] + 48, 35);
      if (i == 0)
	playrhythmicarray3a ();
      else if (i == 1)
	playrhythmicarray3b ();
      else if (i == 2)
	playrhythmicarray3c ();
      else if (i == 3)
	playrhythmicarray3d ();
      play (0, channel[3] - 16, sounds1[i] + 48, 0);
    }
  play (0, channel[0] - 16, motive[3] + 60 + 12, 0);
  play (0, channel[0] - 16, motive[3] + 60 + 12 - 9, 0);
  play (0, channel[3] - 16, motive[0] + 24, 0);
}

void procedure3c (void)
{
  int i;
  procedure3a ();
  procedure3b ();
  subprocedure18 ();
  play (0, channel[3], motive[0] + 24 + 2, 70);
  play (0, channel[0], motive[0] + 60 + 12 + 2, 40);
  play (0, channel[0], motive[0] + 60 + 12 - 9 + 2, 40);
  for (i = 0; i < 4; ++i)
    {
      play (0, channel[3], sounds1[i] + 48 + 2, 35);
      play (32 * 2, 152 - 16, 100, 0);
      play (0, channel[3] - 16, sounds1[i] + 48 + 2, 0);
    }
  play (0, channel[0] - 16, motive[0] + 60 + 12 + 2, 0);
  play (0, channel[0] - 16, motive[0] + 60 + 12 - 9 + 2, 0);
  play (0, channel[0], motive[1] + 60 + 12 + 2, 40);
  play (0, channel[0], motive[1] + 60 + 12 - 9 + 2, 40);
  for (i = 0; i < 4; ++i)
    {
      play (0, channel[3], sounds1[i] + 48 + 2, 35);
      play (32 * 2, 152 - 16, 100, 0);
      play (0, channel[3] - 16, sounds1[i] + 48 + 2, 0);
    }
  play (0, channel[0] - 16, motive[1] + 60 + 12 + 2, 0);
  play (0, channel[0] - 16, motive[1] + 60 + 12 - 9 + 2, 0);
  play (0, channel[0], motive[2] + 60 + 12 + 2, 40);
  play (0, channel[0], motive[2] + 60 + 12 - 9 + 2, 40);
  for (i = 0; i < 4; ++i)
    {
      play (0, channel[3], sounds1[i] + 48 + 2, 35);
      play (32 * 2, 152 - 16, 100, 0);
      play (0, channel[3] - 16, sounds1[i] + 48 + 2, 0);
    }
  play (0, channel[0] - 16, motive[2] + 60 + 12 + 2, 0);
  play (0, channel[0] - 16, motive[2] + 60 + 12 - 9 + 2, 0);
  play (0, channel[0], motive[3] + 60 + 12 + 2, 40);
  play (0, channel[0], motive[3] + 60 + 12 - 9 + 2, 40);
  for (i = 0; i < 4; ++i)
    {
      play (0, channel[3], sounds1[i] + 48 + 2, 35);
      play (32 * 2, 152 - 16, 100, 0);
      play (0, channel[3] - 16, sounds1[i] + 48 + 2, 0);
    }
  play (0, channel[0] - 16, motive[3] + 60 + 12 + 2, 0);
  play (0, channel[0] - 16, motive[3] + 60 + 12 - 9 + 2, 0);
  play (0, channel[3] - 16, motive[0] + 24 + 2, 0);
}

void procedure3d (void)
{
  int i, j, p;
  subprocedure18 ();
  procedure3a ();
  procedure3b ();
  procedure3c ();
  subprocedure18 ();
  for (p = 0; p < 2; ++p)
    {
      play (0, channel[3], motive[0] + 24 + 3, 80);
      for (j = 0; j < 4; ++j)
	{
	  play (0, channel[0], motive[j] + 60 + 12 + 3, 50);
	  play (0, channel[0], motive[j] + 60 + 12 - 9 + 3, 50);
	  for (i = 0; i < 4; ++i)
	    {
	      play (0, channel[3], sounds1[i] + 48 + 3, 40);
	      if (i == 0)
		playrhythmicarray3a ();
	      else if (i == 1)
		playrhythmicarray3b ();
	      else if (i == 2)
		playrhythmicarray3c ();
	      else if (i == 3)
		playrhythmicarray3d ();
	      play (0, channel[3] - 16, sounds1[i] + 48 + 3, 0);
	    }
	  play (0, channel[0] - 16, motive[j] + 60 + 12 + 3, 0);
	  play (0, channel[0] - 16, motive[j] + 60 + 12 - 9 + 3, 0);
	}
      play (0, channel[3] - 16, motive[0] + 24 + 3, 0);
    }
}

void procedure3e (void)
{
  int i;
  subprocedure18 ();
  play (0, channel[3], retroinver[0] + 24 + 4, 80);
  play (0, channel[0], retroinver[0] + 60 + 12 + 4, 50);
  play (0, channel[0], retroinver[0] + 60 + 12 - 9 + 4, 50);
  for (i = 0; i < 4; ++i)
    {
      play (0, channel[3], sounds1[i] + 48 + 4, 40);
      if (i == 0)
	playrhythmicarray3a ();
      else if (i == 1)
	playrhythmicarray3b ();
      else if (i == 2)
	playrhythmicarray3c ();
      else if (i == 3)
	playrhythmicarray3d ();
      play (0, channel[3] - 16, sounds1[i] + 48 + 4, 0);
    }
  play (0, channel[0] - 16, retroinver[0] + 60 + 12 + 4, 0);
  play (0, channel[0] - 16, retroinver[0] + 60 + 12 - 9 + 4, 0);
  play (0, channel[0], retroinver[1] + 60 + 12 + 4, 50);
  play (0, channel[0], retroinver[1] + 60 + 12 - 9 + 4, 50);
  for (i = 0; i < 4; ++i)
    {
      play (0, channel[3], sounds1[i] + 48 + 4, 40);
      if (i == 0)
	playrhythmicarray3a ();
      else if (i == 1)
	playrhythmicarray3b ();
      else if (i == 2)
	playrhythmicarray3c ();
      else if (i == 3)
	playrhythmicarray3d ();
      play (0, channel[3] - 16, sounds1[i] + 48 + 4, 0);
    }
  play (0, channel[0] - 16, retroinver[1] + 60 + 12 + 4, 0);
  play (0, channel[0] - 16, retroinver[1] + 60 + 12 - 9 + 4, 0);
  play (0, channel[0], retroinver[2] + 60 + 12 + 4, 50);
  play (0, channel[0], retroinver[2] + 60 + 12 - 9 + 4, 50);
  for (i = 0; i < 4; ++i)
    {
      play (0, channel[3], sounds1[i] + 48 + 4, 40);
      if (i == 0)
	playrhythmicarray3a ();
      else if (i == 1)
	playrhythmicarray3b ();
      else if (i == 2)
	playrhythmicarray3c ();
      else if (i == 3)
	playrhythmicarray3d ();
      play (0, channel[3] - 16, sounds1[i] + 48 + 4, 0);
    }
  play (0, channel[0] - 16, retroinver[2] + 60 + 12 + 4, 0);
  play (0, channel[0] - 16, retroinver[2] + 60 + 12 - 9 + 4, 0);
  play (0, channel[0], retroinver[3] + 60 + 12 + 4, 50);
  play (0, channel[0], retroinver[3] + 60 + 12 - 9 + 4, 50);
  for (i = 0; i < 4; ++i)
    {
      play (0, channel[3], sounds1[i] + 48 + 4, 40);
      if (i == 0)
	playrhythmicarray3a ();
      else if (i == 1)
	playrhythmicarray3b ();
      else if (i == 2)
	playrhythmicarray3c ();
      else if (i == 3)
	playrhythmicarray3d ();
      play (0, channel[3] - 16, sounds1[i] + 48 + 4, 0);
    }
  play (0, channel[0] - 16, retroinver[3] + 60 + 12 + 4, 0);
  play (0, channel[0] - 16, retroinver[3] + 60 + 12 - 9 + 4, 0);
  play (0, channel[3] - 16, retroinver[0] + 24 + 4, 0);
  procedure3a ();
}

void playrhythmicarray (void)
{
  int m;
  for (m = 0; m < RHYTHMPATTERN; ++m)
    {
      if (rhythmarray[m] == 0)
	play (0, 153, 60, 100);
      play (48 * 2, 152 - 16, 100, 0);
      if (rhythmarray[m] == 0)
	play (0, 153 - 16, 60, 0);
    }
}

void playrhythmicarray1 (void)
{
  int m;
  for (m = 0; m < RHYTHMPATTERN1; ++m)
    {
      if (rhythmarray1[m] == 0)
	play (0, 153, 64, 100);
      play (48 * 2, 152 - 16, 100, 0);
      if (rhythmarray1[m] == 0)
	play (0, 153 - 16, 64, 0);
    }
}

void playrhythmicarray2 (void)
{
  int m;
  for (m = 0; m < RHYTHMPATTERN2; ++m)
    {
      if (rhythmarray2[m] == 0)
	play (0, 153, 50, 100);
      play (48 * 2, 152 - 16, 100, 0);
      if (rhythmarray2[m] == 0)
	play (0, 153 - 16, 50, 0);
    }
}

void playrhythmicarray3 (void)
{
  int m;
  for (m = 0; m < RHYTHMPATTERN3; ++m)
    {
      if (rhythmarray3[m] == 0)
	play (0, 153, 62, 100);
      play (48 * 2, 152 - 16, 100, 0);
      if (rhythmarray3[m] == 0)
	play (0, 153 - 16, 62, 0);
    }
}

void playrhythmicarray3a (void)
{
  int m;
  for (m = 0; m < RHYTHMPATTERN3 - 6; ++m)
    {
      if (rhythmarray3[m] == 0)
	play (0, 153, 62, 100);
      play (24, 152 - 16, 100, 0);
      if (rhythmarray3[m] == 0)
	play (0, 153 - 16, 62, 0);
    }
}

void playrhythmicarray3b (void)
{
  int m;
  for (m = 2; m < RHYTHMPATTERN3 - 4; ++m)
    {
      if (rhythmarray3[m] == 0)
	play (0, 153, 62, 100);
      play (24, 152 - 16, 100, 0);
      if (rhythmarray3[m] == 0)
	play (0, 153 - 16, 62, 0);
    }
}

void playrhythmicarray3c (void)
{
  int m;
  for (m = 4; m < RHYTHMPATTERN3 - 6; ++m)
    {
      if (rhythmarray3[m] == 0)
	play (0, 153, 62, 100);
      play (24, 152 - 16, 100, 0);
      if (rhythmarray3[m] == 0)
	play (0, 153 - 16, 62, 0);
    }
}

void playrhythmicarray3d (void)
{
  int m;
  for (m = 6; m < RHYTHMPATTERN3; ++m)
    {
      if (rhythmarray3[m] == 0)
	play (0, 153, 62, 100);
      play (24, 152 - 16, 100, 0);
      if (rhythmarray3[m] == 0)
	play (0, 153 - 16, 62, 0);
    }
}

void procedure3f (void)
{
  int p;
  for (p = 0; p < 4; ++p)
    {
      play (0, channel[3], motive[p] + 24, 80);
      playrhythmicarray ();
      play (0, channel[3] - 16, motive[p] + 24, 0);
    }
}

void procedure3g (void)
{
  int p;
  for (p = 0; p < 4; ++p)
    {
      play (0, channel[3], retrograde[p] + 24, 80);
      playrhythmicarray1 ();
      play (0, channel[3] - 16, retrograde[p] + 24, 0);
    }
}

void procedure3h (void)
{
  int p, j, i;
  for (j = 0; j < 4; ++j)
    {
      play (0, channel[2], motive[j] + 32, 127);
      for (p = 0; p < 4; ++p)
	{
	  play (0, channel[3], retrograde[p] + 72, 80);
	  for (i = 0; i < 4; ++i)
	    {
	      play (0, channel[4], sounds1[i] + 48, 100);
	      if (i == 0)
		playrhythmicarray3a ();
	      else if (i == 1)
		playrhythmicarray3b ();
	      else if (i == 2)
		playrhythmicarray3c ();
	      else if (i == 3)
		playrhythmicarray3d ();
	      play (0, channel[4] - 16, sounds1[i] + 48, 0);
	    }
	  play (0, channel[3] - 16, retrograde[p] + 72, 0);
	}
      play (0, channel[2] - 16, motive[j] + 32, 0);
    }
  for (j = 0; j < 4; ++j)
    {
      play (0, channel[2], motive[j] + 32 + 2, 127);
      for (p = 0; p < 4; ++p)
	{
	  play (0, channel[3], retrograde[p] + 72 + 2, 80);
	  for (i = 0; i < 4; ++i)
	    {
	      play (0, channel[4], sounds1[i] + 48 + 2, 100);
	      if (i == 0)
		playrhythmicarray3a ();
	      else if (i == 1)
		playrhythmicarray3b ();
	      else if (i == 2)
		playrhythmicarray3c ();
	      else if (i == 3)
		playrhythmicarray3d ();
	      play (0, channel[4] - 16, sounds1[i] + 48 + 2, 0);
	    }
	  play (0, channel[3] - 16, retrograde[p] + 72 + 2, 0);
	}
      play (0, channel[2] - 16, motive[j] + 32 + 2, 0);
    }
  for (j = 0; j < 4; ++j)
    {
      play (0, channel[2], motive[j] + 32 + 2 + 2, 127);
      for (p = 0; p < 4; ++p)
	{
	  play (0, channel[3], retrograde[p] + 72 + 2 + 2, 80);
	  for (i = 0; i < 4; ++i)
	    {
	      play (0, channel[4], sounds1[i] + 48 + 2 + 2, 100);
	      if (i == 0)
		playrhythmicarray3a ();
	      else if (i == 1)
		playrhythmicarray3b ();
	      else if (i == 2)
		playrhythmicarray3c ();
	      else if (i == 3)
		playrhythmicarray3d ();
	      play (0, channel[4] - 16, sounds1[i] + 48 + 2 + 2, 0);
	    }
	  play (0, channel[3] - 16, retrograde[p] + 72 + 2 + 2, 0);
	}
    }
  procedure2 ();
  procedure2 ();
  playrhythmicarray3a ();
  playrhythmicarray3b ();
  playrhythmicarray3c ();
  playrhythmicarray3d ();
  procedure14d ();
  procedure14e ();
  for (j = 0; j < 4; ++j)
    play (0, channel[2] - 16, motive[j] + 32 + 2 + 2, 0);
}

void procedure3i (void)
{
  int p;
  for (p = 0; p < 4; ++p)
    {
      play (0, channel[3], retrograde[p] + 72, 80);
      play (0, channel[3], motive[p] + 24, 80);
      playrhythmicarray3 ();
      play (0, channel[3] - 16, retrograde[p] + 72, 0);
      play (0, channel[3] - 16, motive[p] + 24, 0);
    }
}

void procedure4 (void)
{
  play (tempo * 4, 152 - 16, 100, 0);
}

void procedure5 (void)
{
  int i;
  for (i = 0; i < 4; ++i)
    {
      play (0, channel[2], inversion[i] + 32, 127);
      playrhythmicarray4 ();
      play (0, channel[2] - 16, inversion[i] + 32, 0);
    }
}

void procedure6 (void)
{
  int i, j, p;
  procedure3i ();
  procedure5 ();
  for (p = 0; p < 4; ++p)
    {
      subprocedure18 ();
      for (i = 0; i < 4; ++i)
	{
	  subprocedure18 ();
	  play (0, channel[3], inversion[i] + 72, 100);
	  play (0, channel[3], retroinver[i] + 32, 100);
	  for (j = 0; j < 4; ++j)
	    {
	      play (0, channel[3], sounds1[j] + 48, 100);
	      play (48, 152 - 16, 100, 0);
	      play (0, channel[3] - 16, sounds1[j] + 48, 0);
	    }
	  play (0, channel[3] - 16, inversion[i] + 72, 0);
	  play (0, channel[3] - 16, retroinver[i] + 32, 0);
	}
    }
}

void procedure7 (void)
{
  int i, j, p;
  procedure5 ();
  for (p = 0; p < 4; ++p)
    {
      subprocedure18 ();
      for (i = 0; i < 4; ++i)
	{
	  subprocedure18 ();
	  play (0, channel[3], motive[i] + 72, 90);
	  play (0, channel[3], motive[i] + 72 - 5, 90);
	  play (0, channel[3], motive[i] + 72 - 9, 90);
	  for (j = 0; j < 4; ++j)
	    {
	      play (0, channel[1], sounds1[j] + 60, 80);
	      play (0, channel[4], sounds1[j] + 60, 80);
	      play (48, 152 - 16, 100, 0);
	      play (0, channel[1] - 16, sounds1[j] + 60, 0);
	      play (0, channel[4] - 16, sounds1[j] + 60, 0);
	    }
	  play (0, channel[3] - 16, motive[i] + 72, 0);
	  play (0, channel[3] - 16, motive[i] + 72 - 5, 0);
	  play (0, channel[3] - 16, motive[i] + 72 - 9, 0);
	}
    }
}

void procedure9 (void)
{
  int i, j;
  for (j = 0; j < 2; ++j)
    {
      for (i = 0; i < 5; ++i)
	{
	  play (0, channel[2], motivenewnote[i] + 60, 100);
	  play (tempo * 2, 152 - 16, 100, 0);
	  play (0, channel[2] - 16, motivenewnote[i] + 60, 0);
	}
    }
}

void procedure10 (void)
{
  play (0, channel[3], motivenewnote[2] + 24, 127);
  procedure9 ();
  play (0, channel[3] - 16, motivenewnote[2] + 24, 0);
}

void procedure11 (void)
{
  int i, j, p;
  for (j = 0; j < 4; ++j)
    {
      play (0, channel[0], motive[j] + 60, 60);
      for (i = 0; i < 4; ++i)
	{
	  play (0, channel[1], inversion[i] + 48, 50);
	  play (tempo * 2, 152 - 16, 100, 0);
	  play (0, channel[1] - 16, inversion[i] + 48, 0);
	}
      play (0, channel[0] - 16, motive[j] + 60, 0);
    }
  for (j = 0; j < 4; ++j)
    {
      play (0, channel[0], motive[j] + 60, 60);
      for (i = 0; i < 4; ++i)
	{
	  play (0, channel[1], retroinver[i] + 48, 50);
	  play (tempo, 152 - 16, 100, 0);
	  play (0, channel[1] - 16, retroinver[i] + 48, 0);
	}
      play (0, channel[0] - 16, motive[j] + 60, 0);
    }
  for (j = 0; j < 4; ++j)
    {
      play (0, channel[0], motive[j] + 60 + transposefactor * 2, 60);
      for (i = 0; i < 4; ++i)
	{
	  play (0, channel[1], inversion[i] + 48 + transposefactor * 2, 50);
	  play (tempo, 152 - 16, 100, 0);
	  play (0, channel[1] - 16, inversion[i] + 48 + transposefactor * 2,
		0);
	}
      play (0, channel[0] - 16, motive[j] + 60 + transposefactor * 2, 0);
    }
  for (j = 0; j < 4; ++j)
    {
      play (0, channel[0], motive[j] + 60 + transposefactor * 3, 60);
      for (i = 0; i < 4; ++i)
	{
	  play (0, channel[1], inversion[i] + 48 + transposefactor * 3, 60);
	  play (tempo, 152 - 16, 100, 0);
	  play (0, channel[1] - 16, inversion[i] + 48 + transposefactor * 3,
		0);
	}
      play (0, channel[0] - 16, motive[j] + 60 + transposefactor * 3, 0);
    }
  for (j = 0; j < 5; ++j)
    {
      play (0, channel[0], motivenewnote[j] + 60 + transposefactor * 4, 60);
      for (i = 0; i < 5; ++i)
	{
	  play (0, channel[1], motivenewnote[i] + 48 + transposefactor * 4,
		50);
	  play (tempo, 152 - 16, 100, 0);
	  play (0, channel[1] - 16,
		motivenewnote[i] + 48 + transposefactor * 4, 0);
	}
      play (0, channel[0] - 16, motivenewnote[j] + 60 + transposefactor * 4,
	    0);
    }
  for (j = 0; j < 5; ++j)
    {
      play (0, channel[0], motivenewnote[j] + 60 + transposefactor * 6, 60);
      for (i = 0; i < 5; ++i)
	{
	  play (0, channel[1], motivenewnote[i] + 48 + transposefactor * 6,
		60);
	  play (tempo, 152 - 16, 100, 0);
	  play (0, channel[1] - 16,
		motivenewnote[i] + 48 + transposefactor * 6, 0);
	}
      play (0, channel[0] - 16, motivenewnote[j] + 60 + transposefactor * 6,
	    0);
    }
  for (p = 0; p < 4; ++p)
    {
      for (j = 0; j < 4; ++j)
	{
	  subprocedure18 ();
	  play (0, channel[0], motive[j] + 60 - p, 60);
	  for (i = 0; i < 4; ++i)
	    {
	      play (0, channel[1], sounds1[i] + 48 - p, 60);
	      play (tempo, 152 - 16, 100, 0);
	      play (0, channel[1] - 16, sounds1[i] + 48 - p, 0);
	    }
	  play (0, channel[0] - 16, motive[j] + 60 - p, 0);
	}
    }
  for (j = 0; j < 4; ++j)
    {
      play (0, channel[0], retrograde[j] + 60, 60);
      for (i = 0; i < 4; ++i)
	{
	  play (0, channel[1], retrograde[i] + 48, 50);
	  play (tempo, 152 - 16, 100, 0);
	  play (0, channel[1] - 16, retrograde[i] + 48, 0);
	}
      play (0, channel[0] - 16, retrograde[j] + 60, 0);
    }
  for (p = 0; p < 3; ++p)
    {
      for (j = 0; j < 4; ++j)
	{
	  play (0, channel[0], motive[j] + 60, 60);
	  for (i = 0; i < 4; ++i)
	    {
	      play (0, channel[1], motive[i] + 48, 60);
	      play (tempo, 152 - 16, 100, 0);
	      play (0, channel[1] - 16, motive[i] + 48, 0);
	    }
	  play (0, channel[0] - 16, motive[j] + 60, 0);
	}
    }
}

void procedure12 (void)
{
  int i;
  for (i = 0; i < 8; ++i)
    random_rhythm[i] = rand () % 2;
  makeminorbass ((rand () % 12) + 30);
  for (i = 0; i < 8; ++i)
    {
      if (random_rhythm[i] == 1)
	{
	  play (0, channel[3], sound[0], 126);
	  play (0, channel[3], sound[1], 126);
	  play (0, channel[3], sound[2], 126);
	  play (tempo - 8, 152 - 16, 100, 0);
	  play (0, channel[3] - 16, sound[0], 0);
	  play (0, channel[3] - 16, sound[1], 0);
	  play (0, channel[3] - 16, sound[2], 0);
	}
      else
	play (tempo - 8, 152 - 16, 100, 0);
    }
  for (i = 0; i < 8; ++i)
    {
      if (random_rhythm[i] == 1)
	{
	  play (0, channel[3], sound[0], 126);
	  play (0, channel[3], sound[1], 126);
	  play (0, channel[3], sound[2], 126);
	  play (tempo - 8, 152 - 16, 100, 0);
	  play (0, channel[3] - 16, sound[0], 0);
	  play (0, channel[3] - 16, sound[1], 0);
	  play (0, channel[3] - 16, sound[2], 0);
	}
      else
	play (tempo - 8, 152 - 16, 100, 0);
    }
  play (tempo * 4, 152 - 16, 100, 0);
  for (i = 0; i < 8; ++i)
    random_rhythm[i] = rand () % 2;
  makeminorbass ((rand () % 12) + 30);
  for (i = 0; i < 8; ++i)
    {
      if (random_rhythm[i] == 1)
	{
	  play (0, channel[3], sound[0], 126);
	  play (0, channel[3], sound[1], 126);
	  play (0, channel[3], sound[2], 126);
	  play (tempo - 8, 152 - 16, 100, 0);
	  play (0, channel[3] - 16, sound[0], 0);
	  play (0, channel[3] - 16, sound[1], 0);
	  play (0, channel[3] - 16, sound[2], 0);
	}
      else
	play (tempo - 8, 152 - 16, 100, 0);
    }
  for (i = 0; i < 8; ++i)
    {
      if (random_rhythm[i] == 1)
	{
	  play (0, channel[3], sound[0], 126);
	  play (0, channel[3], sound[1], 126);
	  play (0, channel[3], sound[2], 126);
	  play (tempo - 8, 152 - 16, 100, 0);
	  play (0, channel[3] - 16, sound[0], 0);
	  play (0, channel[3] - 16, sound[1], 0);
	  play (0, channel[3] - 16, sound[2], 0);
	}
      else
	play (tempo - 8, 152 - 16, 100, 0);
    }
  play (tempo * 4, 152 - 16, 100, 0);
  for (i = 0; i < 8; ++i)
    random_rhythm[i] = rand () % 2;
  makeminorbass ((rand () % 12) + 30);
  for (i = 0; i < 8; ++i)
    {
      if (random_rhythm[i] == 1)
	{
	  play (0, channel[3], sound[0], 126);
	  play (0, channel[3], sound[1], 126);
	  play (0, channel[3], sound[2], 126);
	  play (tempo - 8, 152 - 16, 100, 0);
	  play (0, channel[3] - 16, sound[0], 0);
	  play (0, channel[3] - 16, sound[1], 0);
	  play (0, channel[3] - 16, sound[2], 0);
	}
      else
	play (tempo - 8, 152 - 16, 100, 0);
    }
  for (i = 0; i < 8; ++i)
    {
      if (random_rhythm[i] == 1)
	{
	  play (0, channel[3], sound[0], 126);
	  play (0, channel[3], sound[1], 126);
	  play (0, channel[3], sound[2], 126);
	  play (tempo - 8, 152 - 16, 100, 0);
	  play (0, channel[3] - 16, sound[0], 0);
	  play (0, channel[3] - 16, sound[1], 0);
	  play (0, channel[3] - 16, sound[2], 0);
	}
      else
	play (tempo - 8, 152 - 16, 100, 0);
    }
  play (tempo * 4, 152 - 16, 100, 0);
}

void procedure13 (void)
{
  int i;
  for (i = 0; i < 4; ++i)
    {
      makemajorbass ((rand () % 12) + 60);
      {
	play (0, channel[3], sound[0], 50);
	play (0, channel[3], sound[1], 50);
	play (0, channel[3], sound[2], 50);
	play (tempo * 2, 152 - 16, 100, 0);
	play (0, channel[3] - 16, sound[0], 0);
	play (0, channel[3] - 16, sound[1], 0);
	play (0, channel[3] - 16, sound[2], 0);
      }
      chromthirdmajtomin (sound[0]);
      {
	play (0, channel[2], sound[0], 70);
	play (0, channel[2], sound[1], 70);
	play (0, channel[2], sound[2], 70);
	play (tempo * 2, 152 - 16, 100, 0);
	play (0, channel[2] - 16, sound[0], 0);
	play (0, channel[2] - 16, sound[1], 0);
	play (0, channel[2] - 16, sound[2], 0);
      }
      chromthirdmintomin (sound[0]);
      {
	play (0, channel[3], sound[0], 90);
	play (0, channel[3], sound[1], 90);
	play (0, channel[2], sound[2], 90);
	play (tempo * 2, 152 - 16, 100, 0);
	play (0, channel[3] - 16, sound[0], 0);
	play (0, channel[3] - 16, sound[1], 0);
	play (0, channel[2] - 16, sound[2], 0);
      }
      chromthirdmintomin (sound[0]);
      {
	play (0, channel[2], sound[0], 110);
	play (0, channel[2], sound[1], 110);
	play (0, channel[3], sound[2], 110);
	play (tempo * 2, 152 - 16, 100, 0);
	play (0, channel[2] - 16, sound[0], 0);
	play (0, channel[2] - 16, sound[1], 0);
	play (0, channel[3] - 16, sound[2], 0);
      }
    }
}

void procedure14a (void)
{
  int i;
  for (i = 0; i < 4 * 5; ++i)
    {
      play (0, channel[0], motivenewnote[i % 5] + 60 + 12, 100);
      play (0, channel[1], motive[i % 4] + 60, 100);
      play (tempo / 2, 152 - 16, 100, 0);
      play (0, channel[0] - 16, motivenewnote[i % 5] + 60 + 12, 0);
      play (0, channel[1] - 16, motive[i % 4] + 60, 0);
    }
}

void procedure14b (void)
{
  int i;
  for (i = 0; i < 40; ++i)
    {
      play (0, channel[0], motivenewnote[i % 5] + 60, 100);
      play (0, channel[1], motive[i % 4] + 60 + 12, 100);
      play (tempo / 2, 152 - 16, 100, 0);
      play (0, channel[0] - 16, motivenewnote[i % 5] + 60, 0);
      play (0, channel[1] - 16, motive[i % 4] + 60 + 12, 0);
    }
}

void procedure14c (void)
{
  int i;
  for (i = 0; i < 20; ++i)
    {
      play (0, channel[0], motivenewnote[i % 5] + 60 + 12, 100);
      play (0, channel[1], inversion[i % 4] + 48, 100);
      play (tempo, 152 - 16, 100, 0);
      play (0, channel[0] - 16, motivenewnote[i % 5] + 60 + 12, 0);
      play (0, channel[1] - 16, inversion[i % 4] + 48, 0);
    }
}

void procedure14d (void)
{
  int i;
  for (i = 0; i < 20; ++i)
    {
      play (0, channel[1], motivenewnote[i % 5] + 60 + 12, 100);
      play (0, channel[0], inversion[i % 4] + 48, 100);
      play (tempo / 2, 152 - 16, 100, 0);
      play (0, channel[1] - 16, motivenewnote[i % 5] + 60 + 12, 0);
      play (0, channel[0] - 16, inversion[i % 4] + 48, 0);
    }
}

void procedure14e (void)
{
  int i;
  for (i = 0; i < 20; ++i)
    {
      play (0, channel[0], motivenewnote[i % 5] + 60, 100);
      play (0, channel[1], motive[i % 4] + 60 + 12, 100);
      play (tempo / 2, 152 - 16, 100, 0);
      play (0, channel[0] - 16, motivenewnote[i % 5] + 60, 0);
      play (0, channel[1] - 16, motive[i % 4] + 60 + 12, 0);
    }
}

void procedure15 (void)
{
  int i;
  for (i = 0; i < 4; ++i)
    {
      play (0, channel[2], motive[i] + 36, 90);
      play (0, channel[3], retroinver[i] + 72, 90);
      play (tempo * 4, 152 - 16, 100, 0);
      play (0, channel[2] - 16, motive[i] + 36, 0);
      play (0, channel[3] - 16, retroinver[i] + 72, 0);
    }
}

void procedure15z (void)
{
  play (tempo * 4 * 2, 152 - 16, 0, 100);
}

void procedure15a (void)
{
  int i;
  for (i = 0; i < 4; ++i)
    {
      makemajorbass (motive[i] + 36);
      play (0, channel[3], sound[0], 90);
      play (0, channel[3], sound[1], 90);
      play (0, channel[3], sound[2], 90);
      makemajortreble (retroinver[i] + 72);
      play (0, channel[0], sound[0], 90);
      play (0, channel[0], sound[1], 90);
      play (0, channel[0], sound[2], 90);
      play (tempo * 6, 152 - 16, 100, 0);
      makemajorbass (motive[i] + 36);
      play (0, channel[3] - 16, sound[0], 0);
      play (0, channel[3] - 16, sound[1], 0);
      play (0, channel[3] - 16, sound[2], 0);
      makemajortreble (retroinver[i] + 72);
      play (0, channel[0] - 16, sound[0], 0);
      play (0, channel[0] - 16, sound[1], 0);
      play (0, channel[0] - 16, sound[2], 0);
    }
}

void procedure15b (void)
{
  int i;
  for (i = 0; i < 4; ++i)
    {
      makequartalbass (motive[i] + 36);
      play (0, channel[2], sound[0], 90);
      play (0, channel[2], sound[1], 90);
      play (0, channel[2], sound[2], 90);
      makequartaltreble (retroinver[i] + 72);
      play (0, channel[3], sound[0], 90);
      play (0, channel[3], sound[1], 90);
      play (0, channel[3], sound[2], 90);
      play (tempo * 3, 152 - 16, 100, 0);
      makequartalbass (motive[i] + 36);
      play (0, channel[2] - 16, sound[0], 0);
      play (0, channel[2] - 16, sound[1], 0);
      play (0, channel[2] - 16, sound[2], 0);
      makequartaltreble (retroinver[i] + 72);
      play (0, channel[3] - 16, sound[0], 0);
      play (0, channel[3] - 16, sound[1], 0);
      play (0, channel[3] - 16, sound[2], 0);
    }
}

void procedure15c (void)
{
  int i;
  for (i = 0; i < 4; ++i)
    {
      makemajorbass (motive[i] + 36);
      play (0, channel[3], sound[0], 90);
      play (0, channel[3], sound[1], 90);
      play (0, channel[3], sound[2], 90);
      makemajortreble (retroinver[i] + 72);
      play (0, channel[0], sound[0], 90);
      play (0, channel[0], sound[1], 90);
      play (0, channel[0], sound[2], 90);
      play (tempo, 152 - 16, 100, 0);
      makemajorbass (motive[i] + 36);
      play (0, channel[3] - 16, sound[0], 0);
      play (0, channel[3] - 16, sound[1], 0);
      play (0, channel[3] - 16, sound[2], 0);
      makemajortreble (retroinver[i] + 72);
      play (0, channel[0] - 16, sound[0], 0);
      play (0, channel[0] - 16, sound[1], 0);
      play (0, channel[0] - 16, sound[2], 0);
    }
}

void procedure15_1 (void)
{
  int i;
  for (i = 0; i < 4; ++i)
    {
      play (0, channel[2], motive[i] + 36, 90);
      play (0, channel[3], retroinver[i] + 72, 90);
      play (tempo * 4, 152 - 16, 100, 0);
      play (0, channel[2] - 16, motive[i] + 36, 0);
      play (0, channel[3] - 16, retroinver[i] + 72, 0);
    }
}

void procedure15z_1 (void)
{
  play (tempo * 4 * 2, 152 - 16, 0, 100);
}

void procedure15a_1 (void)
{
  int i;
  for (i = 0; i < 4; ++i)
    {
      makemajorbass (motive[i] + 36);
      play (0, channel[3], sound[0], 90);
      play (0, channel[3], sound[1], 90);
      play (0, channel[3], sound[2], 90);
      makemajortreble (retroinver[i] + 72);
      play (0, channel[0], sound[0], 90);
      play (0, channel[0], sound[1], 90);
      play (0, channel[0], sound[2], 90);
      if (i == 0)
	ostinatorhythmpart1 ();
      if (i == 1)
	ostinatorhythmpart2 ();
      if (i == 2)
	ostinatorhythmpart3 ();
      if (i == 3)
	ostinatorhythmpart4 ();
      makemajorbass (motive[i] + 36);
      play (0, channel[3] - 16, sound[0], 0);
      play (0, channel[3] - 16, sound[1], 0);
      play (0, channel[3] - 16, sound[2], 0);
      makemajortreble (retroinver[i] + 72);
      play (0, channel[0] - 16, sound[0], 0);
      play (0, channel[0] - 16, sound[1], 0);
      play (0, channel[0] - 16, sound[2], 0);
    }
}

void procedure15b_1 (void)
{
  int i;
  for (i = 0; i < 4; ++i)
    {
      makequartalbass (motive[i] + 36);
      play (0, channel[2], sound[0], 90);
      play (0, channel[2], sound[1], 90);
      play (0, channel[2], sound[2], 90);
      makequartaltreble (retroinver[i] + 72);
      play (0, channel[3], sound[0], 90);
      play (0, channel[3], sound[1], 90);
      play (0, channel[3], sound[2], 90);
      if (i == 0)
	procedure14a ();
      if (i == 1)
	procedure14b ();
      if (i == 2)
	procedure14c ();
      if (i == 3)
	procedure14d ();
      makequartalbass (motive[i] + 36);
      play (0, channel[2] - 16, sound[0], 0);
      play (0, channel[2] - 16, sound[1], 0);
      play (0, channel[2] - 16, sound[2], 0);
      makequartaltreble (retroinver[i] + 72);
      play (0, channel[3] - 16, sound[0], 0);
      play (0, channel[3] - 16, sound[1], 0);
      play (0, channel[3] - 16, sound[2], 0);
    }
}

void procedure15c_1 (void)
{
  int i;
  for (i = 0; i < 4; ++i)
    {
      makemajorbass (motive[i] + 36);
      play (0, channel[3], sound[0], 90);
      play (0, channel[3], sound[1], 90);
      play (0, channel[3], sound[2], 90);
      makemajortreble (retroinver[i] + 72);
      play (0, channel[0], sound[0], 90);
      play (0, channel[0], sound[1], 90);
      play (0, channel[0], sound[2], 90);
      if (i == 0)
	ostinatorhythmpart1 ();
      if (i == 1)
	ostinatorhythmpart2 ();
      if (i == 2)
	ostinatorhythmpart3 ();
      if (i == 3)
	ostinatorhythmpart4 ();
      makemajorbass (motive[i] + 36);
      play (0, channel[3] - 16, sound[0], 0);
      play (0, channel[3] - 16, sound[1], 0);
      play (0, channel[3] - 16, sound[2], 0);
      makemajortreble (retroinver[i] + 72);
      play (0, channel[0] - 16, sound[0], 0);
      play (0, channel[0] - 16, sound[1], 0);
      play (0, channel[0] - 16, sound[2], 0);
    }
}

void procedure16_1 (void)
{
  int i;
  for (i = 0; i < 4; ++i)
    {
      play (0, channel[3], motive[i] + 36, 90);
      play (0, channel[0], retrograde[i] + 72, 90);
      play (tempo * 4, 152 - 16, 100, 0);
      play (0, channel[3] - 16, motive[i] + 36, 0);
      play (0, channel[0] - 16, retrograde[i] + 72, 0);
    }
}

void procedure16z_1 (void)
{
  play (tempo * 4 * 2, 152 - 16, 0, 100);
}

void procedure16a_1 (void)
{
  int i;
  procedure16_1 ();
  procedure16z_1 ();
  for (i = 0; i < 4; ++i)
    {
      makemajorbass (motive[i] + 36);
      play (0, channel[2], sound[0], 90);
      play (0, channel[2], sound[1], 90);
      play (0, channel[2], sound[2], 90);
      makemajortreble (retrograde[i] + 72);
      play (0, channel[3], sound[0], 90);
      play (0, channel[3], sound[1], 90);
      play (0, channel[3], sound[2], 90);
      if (i == 0)
	ostinatorhythmpart1 ();
      if (i == 1)
	ostinatorhythmpart2 ();
      if (i == 2)
	ostinatorhythmpart3 ();
      if (i == 3)
	ostinatorhythmpart4 ();
      makemajorbass (motive[i] + 36);
      play (0, channel[2] - 16, sound[0], 0);
      play (0, channel[2] - 16, sound[1], 0);
      play (0, channel[2] - 16, sound[2], 0);
      makemajortreble (retrograde[i] + 72);
      play (0, channel[3] - 16, sound[0], 0);
      play (0, channel[3] - 16, sound[1], 0);
      play (0, channel[3] - 16, sound[2], 0);
    }
}

void procedure16b_1 (void)
{
  int i;
  for (i = 0; i < 4; ++i)
    {
      makequartalbass (inversion[i] + 36);
      play (0, channel[3], sound[0], 90);
      play (0, channel[3], sound[1], 90);
      play (0, channel[2], sound[2], 90);
      makequartaltreble (retroinver[i] + 72);
      play (0, channel[0], sound[0], 90);
      play (0, channel[0], sound[1], 90);
      play (0, channel[3], sound[2], 90);
      if (i == 0)
	procedure14a ();
      if (i == 1)
	procedure14b ();
      if (i == 2)
	procedure14c ();
      if (i == 3)
	procedure14d ();
      makequartalbass (inversion[i] + 36);
      play (0, channel[3] - 16, sound[0], 0);
      play (0, channel[3] - 16, sound[1], 0);
      play (0, channel[2] - 16, sound[2], 0);
      makequartaltreble (retroinver[i] + 72);
      play (0, channel[0] - 16, sound[0], 0);
      play (0, channel[0] - 16, sound[1], 0);
      play (0, channel[3] - 16, sound[2], 0);
    }
}

void procedure16c_1 (void)
{
  int i;
  for (i = 0; i < 4; ++i)
    {
      makemajorbass (retroinver[i] + 36);
      play (0, channel[3], sound[0], 90);
      play (0, channel[2], sound[1], 90);
      play (0, channel[3], sound[2], 90);
      makemajortreble (inversion[i] + 72);
      play (0, channel[0], sound[0], 90);
      play (0, channel[3], sound[1], 90);
      play (0, channel[0], sound[2], 90);
      if (i == 0)
	ostinatorhythmpart1 ();
      if (i == 1)
	ostinatorhythmpart2 ();
      if (i == 2)
	ostinatorhythmpart3 ();
      if (i == 3)
	ostinatorhythmpart4 ();
      makemajorbass (retroinver[i] + 36);
      play (0, channel[3] - 16, sound[0], 0);
      play (0, channel[2] - 16, sound[1], 0);
      play (0, channel[3] - 16, sound[2], 0);
      makemajortreble (inversion[i] + 72);
      play (0, channel[0] - 16, sound[0], 0);
      play (0, channel[3] - 16, sound[1], 0);
      play (0, channel[0] - 16, sound[2], 0);
    }
}

void procedure16 (void)
{
  int i;
  for (i = 0; i < 4; ++i)
    {
      play (0, channel[3], motive[i] + 36, 90);
      play (0, channel[0], retrograde[i] + 72, 90);
      play (tempo * 4, 152 - 16, 100, 0);
      play (0, channel[3] - 16, motive[i] + 36, 0);
      play (0, channel[0] - 16, retrograde[i] + 72, 0);
    }
}

void procedure16z (void)
{
  play (tempo * 4 * 2, 152 - 16, 0, 100);
}

void procedure16a (void)
{
  int i;
  procedure16 ();
  procedure16z ();
  for (i = 0; i < 4; ++i)
    {
      makemajorbass (motive[i] + 36);
      play (0, channel[2], sound[0], 90);
      play (0, channel[2], sound[1], 90);
      play (0, channel[2], sound[2], 90);
      makemajortreble (retrograde[i] + 72);
      play (0, channel[3], sound[0], 90);
      play (0, channel[3], sound[1], 90);
      play (0, channel[3], sound[2], 90);
      play (tempo * 6, 152 - 16, 100, 0);
      makemajorbass (motive[i] + 36);
      play (0, channel[2] - 16, sound[0], 0);
      play (0, channel[2] - 16, sound[1], 0);
      play (0, channel[2] - 16, sound[2], 0);
      makemajortreble (retrograde[i] + 72);
      play (0, channel[3] - 16, sound[0], 0);
      play (0, channel[3] - 16, sound[1], 0);
      play (0, channel[3] - 16, sound[2], 0);
    }
}

void procedure16b (void)
{
  int i;
  for (i = 0; i < 4; ++i)
    {
      makequartalbass (inversion[i] + 36);
      play (0, channel[3], sound[0], 90);
      play (0, channel[3], sound[1], 90);
      play (0, channel[2], sound[2], 90);
      makequartaltreble (retroinver[i] + 72);
      play (0, channel[0], sound[0], 90);
      play (0, channel[0], sound[1], 90);
      play (0, channel[3], sound[2], 90);
      play (tempo * 3, 152 - 16, 100, 0);
      makequartalbass (inversion[i] + 36);
      play (0, channel[3] - 16, sound[0], 0);
      play (0, channel[3] - 16, sound[1], 0);
      play (0, channel[2] - 16, sound[2], 0);
      makequartaltreble (retroinver[i] + 72);
      play (0, channel[0] - 16, sound[0], 0);
      play (0, channel[0] - 16, sound[1], 0);
      play (0, channel[3] - 16, sound[2], 0);
    }
}

void procedure16c (void)
{
  int i;
  for (i = 0; i < 4; ++i)
    {
      makemajorbass (retroinver[i] + 36);
      play (0, channel[3], sound[0], 90);
      play (0, channel[2], sound[1], 90);
      play (0, channel[3], sound[2], 90);
      makemajortreble (inversion[i] + 72);
      play (0, channel[0], sound[0], 90);
      play (0, channel[3], sound[1], 90);
      play (0, channel[0], sound[2], 90);
      play (tempo, 152 - 16, 100, 0);
      makemajorbass (retroinver[i] + 36);
      play (0, channel[3] - 16, sound[0], 0);
      play (0, channel[2] - 16, sound[1], 0);
      play (0, channel[3] - 16, sound[2], 0);
      makemajortreble (inversion[i] + 72);
      play (0, channel[0] - 16, sound[0], 0);
      play (0, channel[3] - 16, sound[1], 0);
      play (0, channel[0] - 16, sound[2], 0);
    }
}

void procedure17 (void)
{
  int i;
  for (i = 0; i < 4; ++i)
    {
      play (0, channel[1], mixedmotive2[i] + 60 - 12, 70);
      play (0, channel[0], mixedmotive1[i] + 60, 70);
      play (tempo * 4, 152 - 16, 100, 0);
      play (0, channel[1] - 16, mixedmotive2[i] + 60 - 12, 0);
      play (0, channel[0] - 16, mixedmotive1[i] + 60, 0);
    }
}

void subprocedure18 (void)
{
  int i;
  int temp1;
  int temp2;
  int temp3;
  int temp4;
  temp1 = (rand () % (9));
  temp2 = (rand () % (9));
  temp3 = (rand () % (9));
  temp4 = (rand () % (9));
  if (temp1 == 0)
    for (i = 0; i < 4; ++i)
      sounds1[i] = motive[i];
  if (temp1 == 1)
    for (i = 0; i < 4; ++i)
      sounds1[i] = retrograde[i];
  if (temp1 == 2)
    for (i = 0; i < 4; ++i)
      sounds1[i] = mixedmotive1[i];
  if (temp1 == 3)
    for (i = 0; i < 4; ++i)
      sounds1[i] = mixedmotive2[i];
  if (temp1 == 4)
    for (i = 0; i < 4; ++i)
      sounds1[i] = mixedmotive3[i];
  if (temp1 == 5)
    for (i = 0; i < 4; ++i)
      sounds1[i] = mixedmotive3[i];
  if (temp1 == 6)
    {
      sounds1[0] = motivenewnote[0];
      sounds1[1] = motivenewnote[1];
      sounds1[2] = motivenewnote[2];
      sounds1[3] = motivenewnote[4];
    }
  if (temp1 == 7)
    {
      sounds1[0] = motivenewnote[0];
      sounds1[1] = motivenewnote[1];
      sounds1[2] = motivenewnote[3];
      sounds1[3] = motivenewnote[4];
    }
  if (temp1 == 8)
    {
      sounds1[0] = motivenewnote[0];
      sounds1[1] = motivenewnote[2];
      sounds1[2] = motivenewnote[3];
      sounds1[3] = motivenewnote[4];
    }
  if (temp2 == 0)
    for (i = 0; i < 4; ++i)
      sounds2[i] = motive[i];
  if (temp2 == 1)
    for (i = 0; i < 4; ++i)
      sounds2[i] = retrograde[i];
  if (temp2 == 2)
    for (i = 0; i < 4; ++i)
      sounds2[i] = mixedmotive1[i];
  if (temp2 == 3)
    for (i = 0; i < 4; ++i)
      sounds2[i] = mixedmotive2[i];
  if (temp2 == 4)
    for (i = 0; i < 4; ++i)
      sounds2[i] = mixedmotive3[i];
  if (temp2 == 5)
    for (i = 0; i < 4; ++i)
      sounds2[i] = mixedmotive3[i];
  if (temp2 == 6)
    {
      sounds2[0] = motivenewnote[0];
      sounds2[1] = motivenewnote[1];
      sounds2[2] = motivenewnote[2];
      sounds2[3] = motivenewnote[4];
    }
  if (temp2 == 7)
    {
      sounds2[0] = motivenewnote[0];
      sounds2[1] = motivenewnote[1];
      sounds2[2] = motivenewnote[3];
      sounds2[3] = motivenewnote[4];
    }
  if (temp2 == 8)
    {
      sounds2[0] = motivenewnote[0];
      sounds2[1] = motivenewnote[2];
      sounds2[2] = motivenewnote[3];
      sounds2[3] = motivenewnote[4];
    }
  if (temp3 == 0)
    for (i = 0; i < 4; ++i)
      sounds3[i] = motive[i];
  if (temp3 == 1)
    for (i = 0; i < 4; ++i)
      sounds3[i] = retrograde[i];
  if (temp3 == 2)
    for (i = 0; i < 4; ++i)
      sounds3[i] = mixedmotive1[i];
  if (temp3 == 3)
    for (i = 0; i < 4; ++i)
      sounds3[i] = mixedmotive2[i];
  if (temp3 == 4)
    for (i = 0; i < 4; ++i)
      sounds3[i] = mixedmotive3[i];
  if (temp3 == 5)
    for (i = 0; i < 4; ++i)
      sounds3[i] = mixedmotive3[i];
  if (temp3 == 6)
    {
      sounds3[0] = motivenewnote[0];
      sounds3[1] = motivenewnote[1];
      sounds3[2] = motivenewnote[2];
      sounds3[3] = motivenewnote[4];
    }
  if (temp3 == 7)
    {
      sounds3[0] = motivenewnote[0];
      sounds3[1] = motivenewnote[1];
      sounds3[2] = motivenewnote[3];
      sounds3[3] = motivenewnote[4];
    }
  if (temp3 == 8)
    {
      sounds3[0] = motivenewnote[0];
      sounds3[1] = motivenewnote[2];
      sounds3[2] = motivenewnote[3];
      sounds3[3] = motivenewnote[4];
    }
  if (temp4 == 0)
    for (i = 0; i < 4; ++i)
      sounds4[i] = motive[i];
  if (temp4 == 1)
    for (i = 0; i < 4; ++i)
      sounds4[i] = retrograde[i];
  if (temp4 == 2)
    for (i = 0; i < 4; ++i)
      sounds4[i] = mixedmotive1[i];
  if (temp4 == 3)
    for (i = 0; i < 4; ++i)
      sounds4[i] = mixedmotive2[i];
  if (temp4 == 4)
    for (i = 0; i < 4; ++i)
      sounds4[i] = mixedmotive3[i];
  if (temp4 == 5)
    for (i = 0; i < 4; ++i)
      sounds4[i] = mixedmotive3[i];
  if (temp4 == 6)
    {
      sounds4[0] = motivenewnote[0];
      sounds4[1] = motivenewnote[1];
      sounds4[2] = motivenewnote[2];
      sounds4[3] = motivenewnote[4];
    }
  if (temp4 == 7)
    {
      sounds4[0] = motivenewnote[0];
      sounds4[1] = motivenewnote[1];
      sounds4[2] = motivenewnote[3];
      sounds4[3] = motivenewnote[4];
    }
  if (temp4 == 8)
    {
      sounds4[0] = motivenewnote[0];
      sounds4[1] = motivenewnote[2];
      sounds4[2] = motivenewnote[3];
      sounds4[3] = motivenewnote[4];
    }
}

void procedure18 (void)
{
  int i;
  int k;
  makeminorbass (motive[0] + 48);
  play (0, channel[3], sound[0], 40);
  play (0, channel[3], sound[1], 40);
  play (0, channel[3], sound[2], 40);
  play (0, channel[3], motive[0] + 36, 48);
  for (i = 0; i < 4; ++i)
    {
      play (0, channel[0], motive[i] + 60, 40);
      play (0, channel[0], motive[i] + 60 - 5, 40);
      play (0, channel[0], motive[i] + 60 - 9, 40);
      play (tempo * 4, 152 - 16, 100, 0);
      play (0, channel[0] - 16, motive[i] + 60, 0);
      play (0, channel[0] - 16, motive[i] + 60 - 5, 0);
      play (0, channel[0] - 16, motive[i] + 60 - 9, 0);
      if (i == 0)
	{
	  play (0, channel[3] - 16, sound[0], 0);
	  play (0, channel[3] - 16, sound[1], 0);
	  play (0, channel[3] - 16, sound[2], 0);
	}
    }
  play (0, channel[3] - 16, motive[0] + 36, 0);
  for (k = 0; k < 18; ++k)
    {
      int i;
      int temp4;
      subprocedure18 ();
      temp4 = rand () % 3;
      if (temp4 == 0)
	makeminorbass (sounds1[0] + 48 + k);
      else if (temp4 == 1)
	makeminormiddle (sounds1[0] + 48 + k);
      else
	makeminortreble (sounds1[0] + k + 48);
      play (0, channel[3], sounds1[0] + 36 + k, 60 + k * 2);
      play (0, channel[3], sound[0], 40 + k * 2);
      play (0, channel[3], sound[1], 40 + k * 2);
      play (0, channel[3], sound[2], 40 + k * 2);
      for (i = 0; i < 4; ++i)
	{
	  play (0, channel[0], sounds1[i] + 60 + k, 40 + k * 2);
	  play (0, channel[0], sounds1[i] + 60 - 5 + k, 40 + k * 2);
	  play (0, channel[0], sounds1[i] + 60 - 9 + k, 40 + k * 2);
	  play (tempo * 4, 152 - 16, 100, 0);
	  play (0, channel[0] - 16, sounds1[i] + k + 60, 0);
	  play (0, channel[0] - 16, sounds1[i] + 60 - 5 + k, 40 + k * 2);
	  play (0, channel[0] - 16, sounds1[i] + 60 - 9 + k, 0);
	  if (i == 0)
	    {
	      play (0, channel[3] - 16, sound[0], 0);
	      play (0, channel[3] - 16, sound[1], 0);
	      play (0, channel[3] - 16, sound[2], 0);
	    }
	}
      play (0, channel[3] - 16, sounds1[0] + 36 + k, 0);
    }
  for (k = 0; k < 4; ++k)
    {
      makeminorbass (motive[0] + 48);
      play (0, channel[3], sound[0], 40);
      play (0, channel[3], sound[1], 40);
      play (0, channel[3], sound[2], 40);
      play (0, channel[3], motive[0] + 36, 48);
      for (i = 0; i < 4; ++i)
	{
	  play (0, channel[0], motive[i] + 60, 40);
	  play (0, channel[0], motive[i] + 60 - 5, 40);
	  play (0, channel[0], motive[i] + 60 - 9, 40);
	  play (tempo * 4, 152 - 16, 100, 0);
	  play (0, channel[0] - 16, motive[i] + 60, 0);
	  play (0, channel[0] - 16, motive[i] + 60 - 5, 0);
	  play (0, channel[0] - 16, motive[i] + 60 - 9, 0);
	  if (i == 0)
	    {
	      play (0, channel[3] - 16, sound[0], 0);
	      play (0, channel[3] - 16, sound[1], 0);
	      play (0, channel[3] - 16, sound[2], 0);
	    }
	}
      play (0, channel[3] - 16, motive[0] + 36, 0);
    }
  makeminorbass (retrograde[0] + 48);
  play (0, channel[3], sound[0], 40);
  play (0, channel[3], sound[1], 40);
  play (0, channel[3], sound[2], 40);
  play (0, channel[3], retrograde[0] + 36, 48);
  for (i = 0; i < 4; ++i)
    {
      play (0, channel[0], retrograde[i] + 60, 40);
      play (0, channel[0], retrograde[i] + 60 - 5, 40);
      play (0, channel[0], retrograde[i] + 60 - 9, 40);
      play (tempo * 4, 152 - 16, 100, 0);
      play (0, channel[0] - 16, retrograde[i] + 60, 0);
      play (0, channel[0] - 16, retrograde[i] + 60 - 5, 0);
      play (0, channel[0] - 16, retrograde[i] + 60 - 9, 0);
      if (i == 0)
	{
	  play (0, channel[3] - 16, sound[0], 0);
	  play (0, channel[3] - 16, sound[1], 0);
	  play (0, channel[3] - 16, sound[2], 0);
	}
    }
  play (0, channel[3] - 16, retrograde[0] + 36, 0);
  makemajorbass (motive[0] + 48);
  play (0, channel[3], sound[0], 40);
  play (0, channel[3], sound[1], 40);
  play (0, channel[3], sound[2], 40);
  play (0, channel[3], motive[0] + 36, 48);
  play (0, channel[0], motive[0] + 60, 40);
  play (0, channel[0], motive[0] + 60 - 5, 40);
  play (0, channel[0], motive[0] + 60 - 8, 40);
  play (tempo * 4 * 4, 152 - 16, 100, 0);
  play (0, channel[0] - 16, motive[0] + 60, 0);
  play (0, channel[0] - 16, motive[0] + 60 - 5, 0);
  play (0, channel[0] - 16, motive[0] + 60 - 8, 0);
  play (0, channel[3] - 16, motive[0] + 36, 0);
  play (0, channel[3] - 16, sound[0], 0);
  play (0, channel[3] - 16, sound[1], 0);
  play (0, channel[3] - 16, sound[2], 0);
}

void procedure18a (void)
{
  int i;
  int k;
  makeminorbass (motive[0] + 48);
  play (0, channel[3], sound[0], 40);
  play (0, channel[3], sound[1], 40);
  play (0, channel[3], sound[2], 40);
  for (i = 0; i < 4; ++i)
    {
      play (0, channel[0], motive[i] + 60, 40);
      play (tempo * 4, 152 - 16, 100, 0);
      play (0, channel[0] - 16, motive[i] + 60, 0);
    }
  play (0, channel[3] - 16, sound[0], 0);
  play (0, channel[3] - 16, sound[1], 0);
  play (0, channel[3] - 16, sound[2], 0);
  for (k = 0; k < 24; ++k)
    {
      int temp4;
      subprocedure18 ();
      temp4 = rand () % 3;
      if (temp4 == 0)
	makeminorbass (sounds1[0] + 48 + k);
      else if (temp4 == 1)
	makeminormiddle (sounds1[0] + 48 + k);
      else
	makeminortreble (sounds1[0] + k + 48);
      play (0, channel[3], sound[0], 40 + k * 2);
      play (0, channel[3], sound[1], 40 + k * 2);
      play (0, channel[3], sound[2], 40 + k * 2);
      for (i = 0; i < 4; ++i)
	{
	  play (0, channel[0], sounds1[i] + 60 + k, 40 + k * 2);
	  play (tempo * 4, 152 - 16, 100, 0);
	  play (0, channel[0] - 16, sounds1[i] + k + 60, 0);
	}
      play (0, channel[3] - 16, sound[0], 40 + k * 2);
      play (0, channel[3] - 16, sound[1], 40 + k * 2);
      play (0, channel[3] - 16, sound[2], 40 + k * 2);
    }
  for (k = 0; k < 4; ++k)
    {
      makeminorbass (motive[0] + 48);
      play (0, channel[3], sound[0], 40);
      play (0, channel[3], sound[1], 40);
      play (0, channel[3], sound[2], 40);
      for (i = 0; i < 4; ++i)
	{
	  play (0, channel[0], motive[i] + 60, 40);
	  play (tempo * 4, 152 - 16, 100, 0);
	  play (0, channel[0] - 16, motive[i] + 60, 0);
	}
      play (0, channel[3] - 16, sound[0], 0);
      play (0, channel[3] - 16, sound[1], 0);
      play (0, channel[3] - 16, sound[2], 0);
    }
  makeminorbass (retrograde[0] + 48);
  play (0, channel[3], sound[0], 40);
  play (0, channel[3], sound[1], 40);
  play (0, channel[3], sound[2], 40);
  for (i = 0; i < 4; ++i)
    {
      play (0, channel[0], retrograde[i] + 60, 40);
      play (tempo * 4, 152 - 16, 100, 0);
      play (0, channel[0] - 16, retrograde[i] + 60, 0);
    }
  play (0, channel[3] - 16, sound[0], 0);
  play (0, channel[3] - 16, sound[1], 0);
  play (0, channel[3] - 16, sound[2], 0);
  makemajorbass (motive[0] + 48);
  play (0, channel[3], sound[0], 40);
  play (0, channel[3], sound[1], 40);
  play (0, channel[3], sound[2], 40);
  play (0, channel[0], motive[0] + 60, 40);
  play (tempo * 4 * 4, 152 - 16, 100, 0);
  play (0, channel[0] - 16, motive[0] + 60, 0);
  play (0, channel[3] - 16, sound[0], 0);
  play (0, channel[3] - 16, sound[1], 0);
  play (0, channel[3] - 16, sound[2], 0);
}

void procedure19 (void)		/*the close of the piece */
{
  int i;
  for (i = 0; i < 4; ++i)
    {
      play (0, channel[0], retroinver[i] + 60, 127);
      play (0, channel[1], retroinver[i] + 72, 127);
      play (0, channel[2], retroinver[i] + 24, 127);
      play (0, channel[3], retroinver[i] + 60 + 24, 127);
      play (tempo * 4, 152 - 16, 100, 0);
      play (0, channel[0] - 16, retroinver[i] + 60, 0);
      play (0, channel[1] - 16, retroinver[i] + 72, 0);
      play (0, channel[2] - 16, retroinver[i] + 24, 0);
      play (0, channel[3] - 16, retroinver[i] + 60 + 24, 0);
    }
}

void ostinatorhythmpart1 (void)
{
  /* 5*6*7*8 = 1680. So in 4 rhythmparts 1600 to 1620, 
     1621 to 1640, 1641 to 1660, 1661 to  1681. */
  int m;
  makerhythmicpattern ();
  rhythmmarker = 0;
  rhythmmarker1 = 4;
  rhythmmarker2 = 4;
  rhythmmarker3 = 0;
  for (m = 1600; m < 1621; ++m)
    {
      if (rhythmmarker + 1 == RHYTHMPATTERN)
	{
	  play (0, channel[4], motive[0] + 12, 50);
	  play (0, channel[4], motive[0] + 24, 50);
	  play (0, channel[4], motive[0] + 36, 50);
	  play (0, channel[4], motive[0] + 48, 50);
	  play (0, channel[4], motive[0] + 60, 50);
	  play (0, channel[4], motive[0] + 72, 50);
	}
      if (rhythmmarker1 + 1 == RHYTHMPATTERN1)
	{
	  play (0, channel[4], motive[1] + 12, 50);
	  play (0, channel[4], motive[1] + 24, 50);
	  play (0, channel[4], motive[1] + 36, 50);
	  play (0, channel[4], motive[1] + 48, 50);
	  play (0, channel[4], motive[1] + 60, 50);
	  play (0, channel[4], motive[1] + 72, 50);
	}
      if (rhythmmarker2 + 1 == RHYTHMPATTERN2)
	{
	  play (0, channel[4], motive[2] + 12, 50);
	  play (0, channel[4], motive[2] + 24, 50);
	  play (0, channel[4], motive[2] + 36, 50);
	  play (0, channel[4], motive[2] + 48, 50);
	  play (0, channel[4], motive[2] + 60, 50);
	  play (0, channel[4], motive[2] + 72, 50);
	}
      if (rhythmmarker3 + 1 == RHYTHMPATTERN3)
	{
	  play (0, channel[4], motive[3] + 12, 50);
	  play (0, channel[4], motive[3] + 24, 50);
	  play (0, channel[4], motive[3] + 36, 50);
	  play (0, channel[4], motive[3] + 48, 50);
	  play (0, channel[4], motive[3] + 60, 50);
	  play (0, channel[4], motive[3] + 72, 50);
	}
      if (rhythmarray[rhythmmarker] == 0)
	play (0, 153, 60, 100);
      if (rhythmarray1[rhythmmarker1] == 0)
	play (0, 153, 64, 100);
      if (rhythmarray2[rhythmmarker2] == 0)
	play (0, 153, 50, 127);
      if (rhythmarray3[rhythmmarker3] == 0)
	play (0, 153, 62, 127);
      play (32, 152 - 16, 100, 0);
      if (rhythmarray[rhythmmarker] == 0)
	play (0, 153 - 16, 60, 0);
      if (rhythmarray1[rhythmmarker1] == 0)
	play (0, 153 - 16, 64, 0);
      if (rhythmarray2[rhythmmarker2] == 0)
	play (0, 153 - 16, 36, 0);
      if (rhythmarray3[rhythmmarker3] == 0)
	play (0, 153 - 16, 62, 0);
      if (rhythmmarker + 1 == RHYTHMPATTERN)
	{
	  play (0, channel[4] - 16, motive[0] + 12, 0);
	  play (0, channel[4] - 16, motive[0] + 24, 0);
	  play (0, channel[4] - 16, motive[0] + 36, 0);
	  play (0, channel[4] - 16, motive[0] + 48, 0);
	  play (0, channel[4] - 16, motive[0] + 60, 0);
	  play (0, channel[4] - 16, motive[0] + 72, 0);
	}
      if (rhythmmarker1 + 1 == RHYTHMPATTERN1)
	{
	  play (0, channel[4] - 16, motive[1] + 12, 0);
	  play (0, channel[4] - 16, motive[1] + 24, 0);
	  play (0, channel[4] - 16, motive[1] + 36, 0);
	  play (0, channel[4] - 16, motive[1] + 48, 0);
	  play (0, channel[4] - 16, motive[1] + 60, 0);
	  play (0, channel[4] - 16, motive[1] + 72, 0);
	}
      if (rhythmmarker2 + 1 == RHYTHMPATTERN2)
	{
	  play (0, channel[4] - 16, motive[2] + 12, 0);
	  play (0, channel[4] - 16, motive[2] + 24, 0);
	  play (0, channel[4] - 16, motive[2] + 36, 0);
	  play (0, channel[4] - 16, motive[2] + 48, 0);
	  play (0, channel[4] - 16, motive[2] + 60, 0);
	  play (0, channel[4] - 16, motive[2] + 72, 0);
	}
      if (rhythmmarker3 + 1 == RHYTHMPATTERN3)
	{
	  play (0, channel[4] - 16, motive[3] + 12, 0);
	  play (0, channel[4] - 16, motive[3] + 24, 0);
	  play (0, channel[4] - 16, motive[3] + 36, 0);
	  play (0, channel[4] - 16, motive[3] + 48, 0);
	  play (0, channel[4] - 16, motive[3] + 60, 0);
	  play (0, channel[4] - 16, motive[3] + 72, 0);
	}
      ++rhythmmarker;
      if (rhythmmarker == RHYTHMPATTERN)
	rhythmmarker = 0;
      ++rhythmmarker1;
      if (rhythmmarker1 == RHYTHMPATTERN1)
	rhythmmarker1 = 0;
      ++rhythmmarker2;
      if (rhythmmarker2 == RHYTHMPATTERN2)
	rhythmmarker2 = 0;
      ++rhythmmarker3;
      if (rhythmmarker3 == RHYTHMPATTERN3)
	rhythmmarker3 = 0;
    }
}

void ostinatorhythmpart2 (void)
{
/* 5*6*7*8 = 1680. So in 4 rhythmparts 1600 to 1620, 
1621 to 1640, 1641 to 1660, 1661 to  1681. */
  int m;
  makerhythmicpattern ();
  rhythmmarker = 1;
  rhythmmarker1 = 1;
  rhythmmarker2 = 4;
  rhythmmarker3 = 5;
  for (m = 1621; m < 1641; ++m)
    {
      if (rhythmmarker + 1 == RHYTHMPATTERN)
	{
	  play (0, channel[4], motive[0] + 12, 50);
	  play (0, channel[4], motive[0] + 24, 50);
	  play (0, channel[4], motive[0] + 36, 50);
	  play (0, channel[4], motive[0] + 48, 50);
	  play (0, channel[4], motive[0] + 60, 50);
	  play (0, channel[4], motive[0] + 72, 50);
	}
      if (rhythmmarker1 + 1 == RHYTHMPATTERN1)
	{
	  play (0, channel[4], motive[1] + 12, 50);
	  play (0, channel[4], motive[1] + 24, 50);
	  play (0, channel[4], motive[1] + 36, 50);
	  play (0, channel[4], motive[1] + 48, 50);
	  play (0, channel[4], motive[1] + 60, 50);
	  play (0, channel[4], motive[1] + 72, 50);
	}
      if (rhythmmarker2 + 1 == RHYTHMPATTERN2)
	{
	  play (0, channel[4], motive[2] + 12, 50);
	  play (0, channel[4], motive[2] + 24, 50);
	  play (0, channel[4], motive[2] + 36, 50);
	  play (0, channel[4], motive[2] + 48, 50);
	  play (0, channel[4], motive[2] + 60, 50);
	  play (0, channel[4], motive[2] + 72, 50);
	}
      if (rhythmmarker3 + 1 == RHYTHMPATTERN3)
	{
	  play (0, channel[4], motive[3] + 12, 50);
	  play (0, channel[4], motive[3] + 24, 50);
	  play (0, channel[4], motive[3] + 36, 50);
	  play (0, channel[4], motive[3] + 48, 50);
	  play (0, channel[4], motive[3] + 60, 50);
	  play (0, channel[4], motive[3] + 72, 50);
	}
      if (rhythmarray[rhythmmarker] == 0)
	play (0, 153, 60, 100);
      if (rhythmarray1[rhythmmarker1] == 0)
	play (0, 153, 64, 100);
      if (rhythmarray2[rhythmmarker2] == 0)
	play (0, 153, 50, 127);
      if (rhythmarray3[rhythmmarker3] == 0)
	play (0, 153, 62, 127);
      play (32, 152 - 16, 100, 0);
      if (rhythmarray[rhythmmarker] == 0)
	play (0, 153 - 16, 60, 0);
      if (rhythmarray1[rhythmmarker1] == 0)
	play (0, 153 - 16, 64, 0);
      if (rhythmarray2[rhythmmarker2] == 0)
	play (0, 153 - 16, 36, 0);
      if (rhythmarray3[rhythmmarker3] == 0)
	play (0, 153 - 16, 62, 0);
      if (rhythmmarker + 1 == RHYTHMPATTERN)
	{
	  play (0, channel[4] - 16, motive[0] + 12, 0);
	  play (0, channel[4] - 16, motive[0] + 24, 0);
	  play (0, channel[4] - 16, motive[0] + 36, 0);
	  play (0, channel[4] - 16, motive[0] + 48, 0);
	  play (0, channel[4] - 16, motive[0] + 60, 0);
	  play (0, channel[4] - 16, motive[0] + 72, 0);
	}
      if (rhythmmarker1 + 1 == RHYTHMPATTERN1)
	{
	  play (0, channel[4] - 16, motive[1] + 12, 0);
	  play (0, channel[4] - 16, motive[1] + 24, 0);
	  play (0, channel[4] - 16, motive[1] + 36, 0);
	  play (0, channel[4] - 16, motive[1] + 48, 0);
	  play (0, channel[4] - 16, motive[1] + 60, 0);
	  play (0, channel[4] - 16, motive[1] + 72, 0);
	}
      if (rhythmmarker2 + 1 == RHYTHMPATTERN2)
	{
	  play (0, channel[4] - 16, motive[2] + 12, 0);
	  play (0, channel[4] - 16, motive[2] + 24, 0);
	  play (0, channel[4] - 16, motive[2] + 36, 0);
	  play (0, channel[4] - 16, motive[2] + 48, 0);
	  play (0, channel[4] - 16, motive[2] + 60, 0);
	  play (0, channel[4] - 16, motive[2] + 72, 0);
	}
      if (rhythmmarker3 + 1 == RHYTHMPATTERN3)
	{
	  play (0, channel[4] - 16, motive[3] + 12, 0);
	  play (0, channel[4] - 16, motive[3] + 24, 0);
	  play (0, channel[4] - 16, motive[3] + 36, 0);
	  play (0, channel[4] - 16, motive[3] + 48, 0);
	  play (0, channel[4] - 16, motive[3] + 60, 0);
	  play (0, channel[4] - 16, motive[3] + 72, 0);
	}
      ++rhythmmarker;
      if (rhythmmarker == RHYTHMPATTERN)
	rhythmmarker = 0;
      ++rhythmmarker1;
      if (rhythmmarker1 == RHYTHMPATTERN1)
	rhythmmarker1 = 0;
      ++rhythmmarker2;
      if (rhythmmarker2 == RHYTHMPATTERN2)
	rhythmmarker2 = 0;
      ++rhythmmarker3;
      if (rhythmmarker3 == RHYTHMPATTERN3)
	rhythmmarker3 = 0;
    }
}

void ostinatorhythmpart3 (void)
{
/* 5*6*7*8 = 1680. So in 4 rhythmparts 1600 to 1620, 
1621 to 1640, 1641 to 1660, 1661 to  1681. */
/* MUST HAVE OSTINATORHYTHMPART2 PRECEDING IT */
  int m;
  makerhythmicpattern ();
  rhythmmarker = 1;
  rhythmmarker1 = 3;
  rhythmmarker2 = 3;
  rhythmmarker3 = 1;
  for (m = 1641; m < 1661; ++m)
    {
      if (rhythmmarker + 1 == RHYTHMPATTERN)
	{
	  play (0, channel[4], motive[0] + 12, 50);
	  play (0, channel[4], motive[0] + 24, 50);
	  play (0, channel[4], motive[0] + 36, 50);
	  play (0, channel[4], motive[0] + 48, 50);
	  play (0, channel[4], motive[0] + 60, 50);
	  play (0, channel[4], motive[0] + 72, 50);
	}
      if (rhythmmarker1 + 1 == RHYTHMPATTERN1)
	{
	  play (0, channel[4], motive[1] + 12, 50);
	  play (0, channel[4], motive[1] + 24, 50);
	  play (0, channel[4], motive[1] + 36, 50);
	  play (0, channel[4], motive[1] + 48, 50);
	  play (0, channel[4], motive[1] + 60, 50);
	  play (0, channel[4], motive[1] + 72, 50);
	}
      if (rhythmmarker2 + 1 == RHYTHMPATTERN2)
	{
	  play (0, channel[4], motive[2] + 12, 50);
	  play (0, channel[4], motive[2] + 24, 50);
	  play (0, channel[4], motive[2] + 36, 50);
	  play (0, channel[4], motive[2] + 48, 50);
	  play (0, channel[4], motive[2] + 60, 50);
	  play (0, channel[4], motive[2] + 72, 50);
	}
      if (rhythmmarker3 + 1 == RHYTHMPATTERN3)
	{
	  play (0, channel[4], motive[3] + 12, 50);
	  play (0, channel[4], motive[3] + 24, 50);
	  play (0, channel[4], motive[3] + 36, 50);
	  play (0, channel[4], motive[3] + 48, 50);
	  play (0, channel[4], motive[3] + 60, 50);
	  play (0, channel[4], motive[3] + 72, 50);
	}
      if (rhythmarray[rhythmmarker] == 0)
	play (0, 153, 60, 100);
      if (rhythmarray1[rhythmmarker1] == 0)
	play (0, 153, 64, 100);
      if (rhythmarray2[rhythmmarker2] == 0)
	play (0, 153, 50, 127);
      if (rhythmarray3[rhythmmarker3] == 0)
	play (0, 153, 62, 127);
      play (32, 152 - 16, 100, 0);
      if (rhythmarray[rhythmmarker] == 0)
	play (0, 153 - 16, 60, 0);
      if (rhythmarray1[rhythmmarker1] == 0)
	play (0, 153 - 16, 64, 0);
      if (rhythmarray2[rhythmmarker2] == 0)
	play (0, 153 - 16, 36, 0);
      if (rhythmarray3[rhythmmarker3] == 0)
	play (0, 153 - 16, 62, 0);
      if (rhythmmarker + 1 == RHYTHMPATTERN)
	{
	  play (0, channel[4] - 16, motive[0] + 12, 0);
	  play (0, channel[4] - 16, motive[0] + 24, 0);
	  play (0, channel[4] - 16, motive[0] + 36, 0);
	  play (0, channel[4] - 16, motive[0] + 48, 0);
	  play (0, channel[4] - 16, motive[0] + 60, 0);
	  play (0, channel[4] - 16, motive[0] + 72, 0);
	}
      if (rhythmmarker1 + 1 == RHYTHMPATTERN1)
	{
	  play (0, channel[4] - 16, motive[1] + 12, 0);
	  play (0, channel[4] - 16, motive[1] + 24, 0);
	  play (0, channel[4] - 16, motive[1] + 36, 0);
	  play (0, channel[4] - 16, motive[1] + 48, 0);
	  play (0, channel[4] - 16, motive[1] + 60, 0);
	  play (0, channel[4] - 16, motive[1] + 72, 0);
	}
      if (rhythmmarker2 + 1 == RHYTHMPATTERN2)
	{
	  play (0, channel[4] - 16, motive[2] + 12, 0);
	  play (0, channel[4] - 16, motive[2] + 24, 0);
	  play (0, channel[4] - 16, motive[2] + 36, 0);
	  play (0, channel[4] - 16, motive[2] + 48, 0);
	  play (0, channel[4] - 16, motive[2] + 60, 0);
	  play (0, channel[4] - 16, motive[2] + 72, 0);
	}
      if (rhythmmarker3 + 1 == RHYTHMPATTERN3)
	{
	  play (0, channel[4] - 16, motive[3] + 12, 0);
	  play (0, channel[4] - 16, motive[3] + 24, 0);
	  play (0, channel[4] - 16, motive[3] + 36, 0);
	  play (0, channel[4] - 16, motive[3] + 48, 0);
	  play (0, channel[4] - 16, motive[3] + 60, 0);
	  play (0, channel[4] - 16, motive[3] + 72, 0);
	}
      ++rhythmmarker;
      if (rhythmmarker == RHYTHMPATTERN)
	rhythmmarker = 0;
      ++rhythmmarker1;
      if (rhythmmarker1 == RHYTHMPATTERN1)
	rhythmmarker1 = 0;
      ++rhythmmarker2;
      if (rhythmmarker2 == RHYTHMPATTERN2)
	rhythmmarker2 = 0;
      ++rhythmmarker3;
      if (rhythmmarker3 == RHYTHMPATTERN3)
	rhythmmarker3 = 0;
    }
}

void ostinatorhythmpart4 (void)
{
/* 5*6*7*8 = 1680. +1 begins repeats ostinato. 
So in 4 rhythmparts 1600 to 1620, 1621 to 1640,
1641 to 1660, 1661 to  1681.  
MUST HAVE OSTINATORHYTHMPART3 PRECEDING IT */
  int m;
  makerhythmicpattern ();
  rhythmmarker = 1;
  rhythmmarker1 = 5;
  rhythmmarker2 = 2;
  rhythmmarker3 = 5;
  for (m = 1661; m < 1681; ++m)
    {
      if (rhythmmarker + 1 == RHYTHMPATTERN)
	{
	  play (0, channel[4], motive[0] + 12, 50);
	  play (0, channel[4], motive[0] + 24, 50);
	  play (0, channel[4], motive[0] + 36, 50);
	  play (0, channel[4], motive[0] + 48, 50);
	  play (0, channel[4], motive[0] + 60, 50);
	  play (0, channel[4], motive[0] + 72, 50);
	}
      if (rhythmmarker1 + 1 == RHYTHMPATTERN1)
	{
	  play (0, channel[4], motive[1] + 12, 50);
	  play (0, channel[4], motive[1] + 24, 50);
	  play (0, channel[4], motive[1] + 36, 50);
	  play (0, channel[4], motive[1] + 48, 50);
	  play (0, channel[4], motive[1] + 60, 50);
	  play (0, channel[4], motive[1] + 72, 50);
	}
      if (rhythmmarker2 + 1 == RHYTHMPATTERN2)
	{
	  play (0, channel[4], motive[2] + 12, 50);
	  play (0, channel[4], motive[2] + 24, 50);
	  play (0, channel[4], motive[2] + 36, 50);
	  play (0, channel[4], motive[2] + 48, 50);
	  play (0, channel[4], motive[2] + 60, 50);
	  play (0, channel[4], motive[2] + 72, 50);
	}
      if (rhythmmarker3 + 1 == RHYTHMPATTERN3)
	{
	  play (0, channel[4], motive[3] + 12, 50);
	  play (0, channel[4], motive[3] + 24, 50);
	  play (0, channel[4], motive[3] + 36, 50);
	  play (0, channel[4], motive[3] + 48, 50);
	  play (0, channel[4], motive[3] + 60, 50);
	  play (0, channel[4], motive[3] + 72, 50);
	}
      if (rhythmarray[rhythmmarker] == 0)
	play (0, 153, 60, 100);
      if (rhythmarray1[rhythmmarker1] == 0)
	play (0, 153, 64, 100);
      if (rhythmarray2[rhythmmarker2] == 0)
	play (0, 153, 50, 127);
      if (rhythmarray3[rhythmmarker3] == 0)
	play (0, 153, 62, 127);
      play (32, 152 - 16, 100, 0);
      if (rhythmarray[rhythmmarker] == 0)
	play (0, 153 - 16, 60, 0);
      if (rhythmarray1[rhythmmarker1] == 0)
	play (0, 153 - 16, 64, 0);
      if (rhythmarray2[rhythmmarker2] == 0)
	play (0, 153 - 16, 36, 0);
      if (rhythmarray3[rhythmmarker3] == 0)
	play (0, 153 - 16, 62, 0);
      if (rhythmmarker + 1 == RHYTHMPATTERN)
	{
	  play (0, channel[4] - 16, motive[0] + 12, 0);
	  play (0, channel[4] - 16, motive[0] + 24, 0);
	  play (0, channel[4] - 16, motive[0] + 36, 0);
	  play (0, channel[4] - 16, motive[0] + 48, 0);
	  play (0, channel[4] - 16, motive[0] + 60, 0);
	  play (0, channel[4] - 16, motive[0] + 72, 0);
	}
      if (rhythmmarker1 + 1 == RHYTHMPATTERN1)
	{
	  play (0, channel[4] - 16, motive[1] + 12, 0);
	  play (0, channel[4] - 16, motive[1] + 24, 0);
	  play (0, channel[4] - 16, motive[1] + 36, 0);
	  play (0, channel[4] - 16, motive[1] + 48, 0);
	  play (0, channel[4] - 16, motive[1] + 60, 0);
	  play (0, channel[4] - 16, motive[1] + 72, 0);
	}
      if (rhythmmarker2 + 1 == RHYTHMPATTERN2)
	{
	  play (0, channel[4] - 16, motive[2] + 12, 0);
	  play (0, channel[4] - 16, motive[2] + 24, 0);
	  play (0, channel[4] - 16, motive[2] + 36, 0);
	  play (0, channel[4] - 16, motive[2] + 48, 0);
	  play (0, channel[4] - 16, motive[2] + 60, 0);
	  play (0, channel[4] - 16, motive[2] + 72, 0);
	}
      if (rhythmmarker3 + 1 == RHYTHMPATTERN3)
	{
	  play (0, channel[4] - 16, motive[3] + 12, 0);
	  play (0, channel[4] - 16, motive[3] + 24, 0);
	  play (0, channel[4] - 16, motive[3] + 36, 0);
	  play (0, channel[4] - 16, motive[3] + 48, 0);
	  play (0, channel[4] - 16, motive[3] + 60, 0);
	  play (0, channel[4] - 16, motive[3] + 72, 0);
	}
      ++rhythmmarker;
      if (rhythmmarker == RHYTHMPATTERN)
	rhythmmarker = 0;
      ++rhythmmarker1;
      if (rhythmmarker1 == RHYTHMPATTERN1)
	rhythmmarker1 = 0;
      ++rhythmmarker2;
      if (rhythmmarker2 == RHYTHMPATTERN2)
	rhythmmarker2 = 0;
      ++rhythmmarker3;
      if (rhythmmarker3 == RHYTHMPATTERN3)
	rhythmmarker3 = 0;
    }
}

void playrhythmicarray4 (void)
{
/* 5*6*7*8 = 1680. +1 begins repeats ostinato. So in 4  1661 to  1681. */
  int m;
  rhythmmarker = 1;
  rhythmmarker1 = 5;
  rhythmmarker2 = 2;
  rhythmmarker3 = 5;
  for (m = 1661; m < 1681; ++m)
    {
      if (rhythmarray[rhythmmarker] == 0)
	play (0, 153, 60, 100);
      if (rhythmarray1[rhythmmarker1] == 0)
	play (0, 153, 64, 100);
      if (rhythmarray2[rhythmmarker2] == 0)
	play (0, 153, 50, 127);
      if (rhythmarray3[rhythmmarker3] == 0)
	play (0, 153, 62, 127);
      play (32, 152 - 16, 100, 0);
      if (rhythmarray[rhythmmarker] == 0)
	play (0, 153 - 16, 60, 0);
      if (rhythmarray1[rhythmmarker1] == 0)
	play (0, 153 - 16, 64, 0);
      if (rhythmarray2[rhythmmarker2] == 0)
	play (0, 153 - 16, 36, 0);
      if (rhythmarray3[rhythmmarker3] == 0)
	play (0, 153 - 16, 62, 0);
      ++rhythmmarker;
      if (rhythmmarker == RHYTHMPATTERN)
	rhythmmarker = 0;
      ++rhythmmarker1;
      if (rhythmmarker1 == RHYTHMPATTERN1)
	rhythmmarker1 = 0;
      ++rhythmmarker2;
      if (rhythmmarker2 == RHYTHMPATTERN2)
	rhythmmarker2 = 0;
      ++rhythmmarker3;
      if (rhythmmarker3 == RHYTHMPATTERN3)
	rhythmmarker3 = 0;
    }
}

void procedure20 (void)
{
  int m;
  rhythmmarker = 0;
  rhythmmarker1 = 4;
  rhythmmarker2 = 4;
  rhythmmarker3 = 0;
  makerhythmicpattern ();
  for (m = 1600; m < 5 * 6 * 7 * 8 + 1; ++m)
/* for (m = 0; m < 1600; ++m)*/
    {
      if (rhythmmarker + 1 == RHYTHMPATTERN)
	{
	  play (0, channel[4], motive[0] + 12, 50);
	  play (0, channel[4], motive[0] + 24, 50);
	  play (0, channel[4], motive[0] + 36, 50);
	  play (0, channel[4], motive[0] + 48, 50);
	  play (0, channel[4], motive[0] + 60, 50);
	  play (0, channel[4], motive[0] + 72, 50);
	}
      if (rhythmmarker1 + 1 == RHYTHMPATTERN1)
	{
	  play (0, channel[4], motive[1] + 12, 50);
	  play (0, channel[4], motive[1] + 24, 50);
	  play (0, channel[4], motive[1] + 36, 50);
	  play (0, channel[4], motive[1] + 48, 50);
	  play (0, channel[4], motive[1] + 60, 50);
	  play (0, channel[4], motive[1] + 72, 50);
	}
      if (rhythmmarker2 + 1 == RHYTHMPATTERN2)
	{
	  play (0, channel[4], motive[2] + 12, 50);
	  play (0, channel[4], motive[2] + 24, 50);
	  play (0, channel[4], motive[2] + 36, 50);
	  play (0, channel[4], motive[2] + 48, 50);
	  play (0, channel[4], motive[2] + 60, 50);
	  play (0, channel[4], motive[2] + 72, 50);
	}
      if (rhythmmarker3 + 1 == RHYTHMPATTERN3)
	{
	  play (0, channel[4], motive[3] + 12, 50);
	  play (0, channel[4], motive[3] + 24, 50);
	  play (0, channel[4], motive[3] + 36, 50);
	  play (0, channel[4], motive[3] + 48, 50);
	  play (0, channel[4], motive[3] + 60, 50);
	  play (0, channel[4], motive[3] + 72, 50);
	}
      if (rhythmarray[rhythmmarker] == 0)
	play (0, 153, 60, 100);
      if (rhythmarray1[rhythmmarker1] == 0)
	play (0, 153, 64, 100);
      if (rhythmarray2[rhythmmarker2] == 0)
	play (0, 153, 50, 127);
      if (rhythmarray3[rhythmmarker3] == 0)
	play (0, 153, 62, 127);
      play (32, 152 - 16, 100, 0);
      if (rhythmarray[rhythmmarker] == 0)
	play (0, 153 - 16, 60, 0);
      if (rhythmarray1[rhythmmarker1] == 0)
	play (0, 153 - 16, 64, 0);
      if (rhythmarray2[rhythmmarker2] == 0)
	play (0, 153 - 16, 36, 0);
      if (rhythmarray3[rhythmmarker3] == 0)
	play (0, 153 - 16, 62, 0);
      if (rhythmmarker + 1 == RHYTHMPATTERN)
	{
	  play (0, channel[4] - 16, motive[0] + 12, 0);
	  play (0, channel[4] - 16, motive[0] + 24, 0);
	  play (0, channel[4] - 16, motive[0] + 36, 0);
	  play (0, channel[4] - 16, motive[0] + 48, 0);
	  play (0, channel[4] - 16, motive[0] + 60, 0);
	  play (0, channel[4] - 16, motive[0] + 72, 0);
	}
      if (rhythmmarker1 + 1 == RHYTHMPATTERN1)
	{
	  play (0, channel[4] - 16, motive[1] + 12, 0);
	  play (0, channel[4] - 16, motive[1] + 24, 0);
	  play (0, channel[4] - 16, motive[1] + 36, 0);
	  play (0, channel[4] - 16, motive[1] + 48, 0);
	  play (0, channel[4] - 16, motive[1] + 60, 0);
	  play (0, channel[4] - 16, motive[1] + 72, 0);
	}
      if (rhythmmarker2 + 1 == RHYTHMPATTERN2)
	{
	  play (0, channel[4] - 16, motive[2] + 12, 0);
	  play (0, channel[4] - 16, motive[2] + 24, 0);
	  play (0, channel[4] - 16, motive[2] + 36, 0);
	  play (0, channel[4] - 16, motive[2] + 48, 0);
	  play (0, channel[4] - 16, motive[2] + 60, 0);
	  play (0, channel[4] - 16, motive[2] + 72, 0);
	}
      if (rhythmmarker3 + 1 == RHYTHMPATTERN3)
	{
	  play (0, channel[4] - 16, motive[3] + 12, 0);
	  play (0, channel[4] - 16, motive[3] + 24, 0);
	  play (0, channel[4] - 16, motive[3] + 36, 0);
	  play (0, channel[4] - 16, motive[3] + 48, 0);
	  play (0, channel[4] - 16, motive[3] + 60, 0);
	  play (0, channel[4] - 16, motive[3] + 72, 0);
	}
      ++rhythmmarker;
      if (rhythmmarker == RHYTHMPATTERN)
	rhythmmarker = 0;
      ++rhythmmarker1;
      if (rhythmmarker1 == RHYTHMPATTERN1)
	rhythmmarker1 = 0;
      ++rhythmmarker2;
      if (rhythmmarker2 == RHYTHMPATTERN2)
	rhythmmarker2 = 0;
      ++rhythmmarker3;
      if (rhythmmarker3 == RHYTHMPATTERN3)
	rhythmmarker3 = 0;
    }
}

void makerhythmicpattern (void)
{
  int i;
  for (i = 0; i < RHYTHMPATTERN; ++i)
    rhythmarray[i] = rand () % (2);
  for (i = 0; i < RHYTHMPATTERN1; ++i)
    rhythmarray1[i] = rand () % (2);
  for (i = 0; i < RHYTHMPATTERN2; ++i)
    rhythmarray2[i] = rand () % (2);
  for (i = 0; i < RHYTHMPATTERN3; ++i)
    rhythmarray3[i] = rand () % (2);
}

void makeminorbass (int note)
{
  sound[0] = note;
  sound[1] = sound[0] + 3 + 12;
  sound[2] = sound[0] + 7;
}

void makeminormiddle (int note)
{
  sound[0] = note - 3;
  sound[1] = note;
  sound[2] = note + 4;
}

void makeminortreble (int note)
{
  sound[0] = note;
  sound[1] = sound[0] - 4;
  sound[2] = sound[0] - 7;
}

void makemajorbass (int note)
{
  sound[0] = note;
  sound[1] = sound[0] + 4 + 12;
  sound[2] = sound[0] + 7;
}

void makemajortreble (int note)
{
  sound[0] = note;
  sound[1] = sound[0] - 3;
  sound[2] = sound[0] - 7;
}

void makequartalbass (int note)
{
  sound[0] = note;
  sound[1] = sound[0] + 5;
  sound[2] = sound[1] + 5;
}

void makequartaltreble (int note)
{
  sound[0] = note;
  sound[1] = sound[0] - 5;
  sound[2] = sound[1] - 5;
}

void chromthirdmajtomaj (int note)
{
  int x;
  x = rand () % 4;
  if (x == 0)
    {
      sound[0] = note + 3;	/* root of new chord-make this one major   
				   THE 'note' REFERS TO PREVIOUS CHORD ROOT */
      sound[1] = note + 3 + 4;
      sound[2] = note + 3 + 7;
    }
  else if (x == 1)
    {
      sound[0] = note + 4;	/* root of new chord-can only be major */
      sound[1] = note + 4 + 4;
      sound[2] = note + 4 + 7;
    }
  else if (x == 2)
    {
      sound[0] = note - 3;	/* root of new chord-can only be major */
      sound[1] = note - 3 + 4;
      sound[2] = note - 3 + 7;
    }
  else if (x == 3)
    {
      sound[0] = note - 4;	/* root of new chord-make this one major */
      sound[1] = note - 4 + 4;
      sound[2] = note - 4 + 7;
    }
}

void chromthirdmajtomin (int note)
{
  int x;
  x = rand () % 2;
  if (x == 0)
    {
      sound[0] = note + 3;	/* root of new chord-make this one minor */
      sound[1] = note + 3 + 3;
      sound[2] = note + 3 + 7;
    }
  else if (x == 1)
    {
      sound[0] = note - 4;	/* root of new chord - make this one minor */
      sound[1] = note - 4 + 3;
      sound[2] = note - 4 + 7;
    }
}

void chromthirdmintomin (int note)
{
  int x;
  x = rand () % 4;
  if (x == 0)
    {
      sound[0] = note + 3;	/* root of new chord-make this one minor */
/*THE 'note REFERS TO PREVIOUS CHORD ROOT!*/
      sound[1] = note + 3 + 3;
      sound[2] = note + 3 + 7;
    }
  else if (x == 1)
    {
      sound[0] = note + 4;	/* root of new chord-make this one minor */
      sound[1] = note + 4 + 3;
      sound[2] = note + 4 + 7;
    }
  else if (x == 2)
    {
      sound[0] = note - 3;	/* root of new chord-make this one minor */
      sound[1] = note - 3 + 3;
      sound[2] = note - 3 + 7;
    }
  else if (x == 3)
    {
      sound[0] = note - 4;	/* root of new chord-make this one minor */
      sound[1] = note - 4 + 3;
      sound[2] = note - 4 + 7;
    }
}

void chromthirdmintomaj (int note)
{
  int x;
  x = rand () % 2;
  if (x == 0)
    {
      sound[0] = note + 4;	/* root of new chord-can only be major */
      sound[1] = note + 4 + 4;
      sound[2] = note + 4 + 7;
    }
  else if (x == 1)
    {
      sound[0] = note - 3;	/* root of new chord-can only be major */
      sound[1] = note - 3 + 4;
      sound[2] = note - 3 + 7;
    }
}

void loadnotes (void)
{
  do
    {
      motive[0] = rand () % 12;
      motive[1] = rand () % 12;
      motive[2] = rand () % 12;
      motive[3] = rand () % 12;
    }
  while
    (motive[0] == motive[1] || motive[0] == motive[2] ||
     motive[0] == motive[3] ||
     motive[1] == motive[2] || motive[1] == motive[3] ||
     motive[2] == motive[3]);
}

void operations_on_motives (void)
{
  int x;
  int i;
  for (i = 0; i < 4; ++i)
    inversion[i] = 12 - motive[i];
  retrograde[0] = motive[3];
  retrograde[1] = motive[2];
  retrograde[2] = motive[1];
  retrograde[3] = motive[0];
  retroinver[0] = inversion[3];
  retroinver[1] = inversion[2];
  retroinver[2] = inversion[1];
  retroinver[3] = inversion[0];
  do
    {
      x = rand () % 12;
    }
  while (x == motive[0] || x == motive[1] ||
	 x == motive[2] || x == motive[3]);
  motivenewnote[0] = motive[0];
  motivenewnote[1] = motive[1];
  motivenewnote[2] = motive[2];
  motivenewnote[3] = motive[3];
  motivenewnote[4] = x;
  mixedmotive1[0] = motive[1];
  mixedmotive1[1] = motive[2];
  mixedmotive1[2] = motive[3];
  mixedmotive1[3] = motive[0];
  mixedmotive2[0] = motive[2];
  mixedmotive2[1] = motive[3];
  mixedmotive2[2] = motive[0];
  mixedmotive2[3] = motive[1];
  mixedmotive3[0] = motive[3];
  mixedmotive3[1] = motive[0];
  mixedmotive3[2] = motive[1];
  mixedmotive3[3] = motive[2];
  mixedinversion1[0] = inversion[1];
  mixedinversion1[1] = inversion[2];
  mixedinversion1[2] = inversion[3];
  mixedinversion1[3] = inversion[0];
  mixedinversion2[0] = inversion[2];
  mixedinversion2[1] = inversion[3];
  mixedinversion2[2] = inversion[0];
  mixedinversion2[3] = inversion[1];
  mixedinversion3[0] = inversion[3];
  mixedinversion3[1] = inversion[0];
  mixedinversion3[2] = inversion[1];
  mixedinversion3[3] = inversion[2];
}

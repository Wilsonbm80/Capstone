/* PianoMinFolk.c */
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "convert3.h"
#define TONIC 0
#define MEDIANT 3
#define SUBDOMINANT 5
#define DOMINANT 7
#define SUBMEDIANT 8
#define SUBTONIC 10
#define MAJOR 0
#define MINOR 1
#define BEGINNING_PITCH  48
#define LOWER_MELODIC_RANGE 70
#define UPPER_MELODIC_RANGE 86
#define LOWER_ARPEGGIO_RANGE 46 
#define UPPER_ARPEGGIO_RANGE 57 
#define ABOVE 0
#define BELOW 1
#define BEATS_PER_MEASURE  4
#define MEASURES 4
#define TOTAL_CHORDS  64
/*128 = 4 measures times  16 phrases times 2 for eighth notes*/
#define GENERAL_MIDI_ON 1
#define PROGRAM_NUMBERS_ON 1
struct sounds
{
  int scale_degree;
  int quality;
  int sound[3];
};
struct sounds chords_a[MEASURES];
struct sounds chords_b[MEASURES];
struct sounds chords_c[MEASURES];
struct sounds chords_d[MEASURES];
struct sounds chords_inversion_a[MEASURES];
struct sounds chords_inversion_b[MEASURES];
struct sounds chords_inversion_c[MEASURES];
struct sounds chords_inversion_d[MEASURES];
int layer[5][TOTAL_CHORDS * BEATS_PER_MEASURE];
int transposefactor;
int tempo;
int scale_array[9 * 8];
int find_quality (int scale_degree);
void makechords (int quality, int sound[]);
int progression_logic (int current_note);
void make_progression_a_chords (int current_note);
void make_progression_b_chords (int current_note);
void make_progression_c_chords (int current_note);
void make_progression_d_chords (int current_note);
int copy_progression_to_layers (struct sounds chords[], int layer_start);
void make_rhythm (int rhythmarray1[], int rhythmarray2[]);
void initialize_layers (void);
void setup_arpeggio_patterns (int pattern_a[], int pattern_a_prime[],
			      int pattern_b[], int pattern_new_b[],
			      int pattern_c[], int pattern_c_prime[],
			      int pattern_d[], int pattern_d_prime[]);
void make_arpeggiated_bass (int pattern[],
			    struct sounds chords[], int arpeggio[]);
void make_arpeggiated_bass1 (int pattern[],
          struct sounds chords[], int arpeggio[]);
int copy_arpeggio_to_layers (int arpeggio[], int layer_start);
void make_skeleton_melody (struct sounds chords[], int melody[]);
int find_nonharmonic_tone (int harmonic_tone, int position);
void add_non_harmonic_tones (int melody[]);
void add_sustaining_tones (int melody[]);
int copy_melody_to_layers (int melody[], int layer_start);
void copy_melody_to_another (int melody[], int melody1[]);
void add_non_harmonic_tones_arpeggio (int arpeggio[]);
void play_layers (void);
void make_scale_array (void);


int main (void)
{
  int layer_start;
  int melody_a[MEASURES * BEATS_PER_MEASURE];
  int melody_a_prime[MEASURES * BEATS_PER_MEASURE];
  int melody_b[MEASURES * BEATS_PER_MEASURE];
  int melody_new_b[MEASURES * BEATS_PER_MEASURE];
  int melody_c[MEASURES * BEATS_PER_MEASURE];
  int melody_c_prime[MEASURES * BEATS_PER_MEASURE];
  int melody_d[MEASURES * BEATS_PER_MEASURE];
  int melody_d_prime[MEASURES * BEATS_PER_MEASURE];
  int first_key;
  int second_key;
  int arpeggio_a[MEASURES * BEATS_PER_MEASURE * 2];
  int arpeggio_a_prime[MEASURES * BEATS_PER_MEASURE * 2];
  int arpeggio_b[MEASURES * BEATS_PER_MEASURE * 2];
  int arpeggio_new_b[MEASURES * BEATS_PER_MEASURE * 2];
  int arpeggio_c[MEASURES * BEATS_PER_MEASURE * 2];
  int arpeggio_c_prime[MEASURES * BEATS_PER_MEASURE * 2];
  int arpeggio_d[MEASURES * BEATS_PER_MEASURE * 2];
  int arpeggio_d_prime[MEASURES * BEATS_PER_MEASURE * 2];
  int pattern_a[BEATS_PER_MEASURE * 2];
  int pattern_a_prime[BEATS_PER_MEASURE * 2];
  int pattern_b[BEATS_PER_MEASURE * 2];
  int pattern_new_b[BEATS_PER_MEASURE * 2];
  int pattern_c[BEATS_PER_MEASURE * 2];
  int pattern_c_prime[BEATS_PER_MEASURE * 2];
  int pattern_d[BEATS_PER_MEASURE * 2];
  int pattern_d_prime[BEATS_PER_MEASURE * 2];
  time_t t;
  open_midfiles ();
#if GENERAL_MIDI_ON
  general_midi ();
#endif
  srand ((unsigned) time (&t));
  transposefactor = 0;
  tempo = 48;
  first_key = transposefactor;
  second_key = first_key + 7;
  initialize_layers ();
  transposefactor = first_key;
  make_progression_a_chords (DOMINANT);
  make_progression_b_chords (TONIC);
  transposefactor = second_key;
  make_progression_c_chords (DOMINANT);
  make_progression_d_chords (TONIC);
  make_skeleton_melody (chords_a, melody_a);
  copy_melody_to_another (melody_a, melody_a_prime);
  make_skeleton_melody (chords_b, melody_b);
  make_skeleton_melody (chords_b, melody_new_b);
  make_skeleton_melody (chords_c, melody_c);
  copy_melody_to_another (melody_c, melody_c_prime);
  make_skeleton_melody (chords_d, melody_d);
  make_skeleton_melody (chords_d, melody_d_prime);
  transposefactor = first_key;
  make_scale_array ();
  add_non_harmonic_tones (melody_a);
  add_non_harmonic_tones (melody_a);
  add_sustaining_tones (melody_a);
  add_non_harmonic_tones (melody_a_prime);
  add_non_harmonic_tones (melody_a_prime);
  add_sustaining_tones (melody_a_prime);
  add_non_harmonic_tones (melody_b);
  add_non_harmonic_tones (melody_b);
  add_sustaining_tones (melody_b);
  add_non_harmonic_tones (melody_new_b);
  add_non_harmonic_tones (melody_new_b);
  add_sustaining_tones (melody_new_b);
  transposefactor = second_key;
  make_scale_array ();
  add_non_harmonic_tones (melody_c);
  add_non_harmonic_tones (melody_c);
  add_sustaining_tones (melody_c);
  add_non_harmonic_tones (melody_c_prime);
  add_non_harmonic_tones (melody_c_prime);
  add_sustaining_tones (melody_c_prime);
  add_non_harmonic_tones (melody_d);
  add_non_harmonic_tones (melody_d);
  add_sustaining_tones (melody_d);
  add_non_harmonic_tones (melody_d_prime);
  add_non_harmonic_tones (melody_d_prime);
  add_sustaining_tones (melody_d_prime);
  setup_arpeggio_patterns (pattern_a, pattern_a_prime, pattern_b,
			   pattern_new_b, pattern_c, pattern_c_prime,
			   pattern_d, pattern_d_prime);

  transposefactor = first_key;
  make_scale_array ();
  make_arpeggiated_bass (pattern_a, chords_inversion_a, arpeggio_a);
  make_arpeggiated_bass (pattern_a_prime, chords_inversion_a, arpeggio_a_prime);
  add_non_harmonic_tones_arpeggio (arpeggio_a_prime);
  make_arpeggiated_bass (pattern_b, chords_inversion_b, arpeggio_b);
  make_arpeggiated_bass (pattern_new_b, chords_inversion_b, arpeggio_new_b);
  add_non_harmonic_tones_arpeggio (arpeggio_new_b);
  transposefactor = second_key;
  make_scale_array ();
  make_arpeggiated_bass1 (pattern_c, chords_inversion_c, arpeggio_c);
  make_arpeggiated_bass1 (pattern_c_prime, chords_inversion_c, arpeggio_c_prime);
  add_non_harmonic_tones_arpeggio (arpeggio_c_prime);
  make_arpeggiated_bass1 (pattern_d, chords_inversion_d, arpeggio_d);
  make_arpeggiated_bass1 (pattern_d_prime, chords_inversion_d, arpeggio_d_prime);
  add_non_harmonic_tones (arpeggio_d_prime);
  layer_start = 0;
  layer_start = copy_arpeggio_to_layers (arpeggio_a, layer_start);
  layer_start = copy_arpeggio_to_layers (arpeggio_b, layer_start);
  layer_start = copy_arpeggio_to_layers (arpeggio_a_prime, layer_start);
  layer_start = copy_arpeggio_to_layers (arpeggio_new_b, layer_start);
  layer_start = copy_arpeggio_to_layers (arpeggio_c_prime, layer_start);
  layer_start = copy_arpeggio_to_layers (arpeggio_d_prime, layer_start);
  layer_start = copy_arpeggio_to_layers (arpeggio_a, layer_start);
 /*layer_start = */ copy_arpeggio_to_layers (arpeggio_new_b, layer_start);
  layer_start = 0;
  layer_start = copy_melody_to_layers (melody_a, layer_start);
  layer_start = copy_melody_to_layers (melody_b, layer_start);
  layer_start = copy_melody_to_layers (melody_a_prime, layer_start);
  layer_start = copy_melody_to_layers (melody_new_b, layer_start);
  layer_start = copy_melody_to_layers (melody_c, layer_start);
  layer_start = copy_melody_to_layers (melody_d, layer_start);
  layer_start = copy_melody_to_layers (melody_a, layer_start);
 /*layer_start = */ copy_melody_to_layers (melody_new_b, layer_start);
  layer_start = 0;
  layer_start = copy_progression_to_layers (chords_inversion_a, layer_start);
  layer_start = copy_progression_to_layers (chords_inversion_b, layer_start);
  layer_start = copy_progression_to_layers (chords_inversion_a, layer_start);
  layer_start = copy_progression_to_layers (chords_inversion_b, layer_start);
  layer_start = copy_progression_to_layers (chords_inversion_c, layer_start);
  layer_start = copy_progression_to_layers (chords_inversion_d, layer_start);
  layer_start = copy_progression_to_layers (chords_inversion_a, layer_start);
 /*layer_start = */ copy_progression_to_layers (chords_inversion_b, layer_start);
  play (48 * 2 * 4, 152 - 16, 100, 0);	/* Handshake */
  play_layers ();
  close_midfiles ();
  return (1);
}

int find_quality (int scale_degree)
{
  int quality;
  switch (scale_degree)
    {
    case TONIC:
      quality = MINOR;
      break;
    case MEDIANT:
      quality = MAJOR;
      break;
    case SUBDOMINANT:
      quality = MINOR;
      break;
    case DOMINANT:
      quality = MINOR;
      break;
    case SUBTONIC:
      quality = MAJOR;
      break;
    }
  return (quality);
}

void makechords (int quality, int sound[])
{
  switch (quality)
    {
    case MAJOR:
      sound[1] = sound[0] + 4;
      sound[2] = sound[0] + 7;
      break;
    case MINOR:
      sound[1] = sound[0] + 3;
      sound[2] = sound[0] + 7;
      break;
    }
}

int progression_logic (int current_note)
{
  int next_note;
  int choice;
  if (current_note == TONIC)
    {
      choice = rand () % (2);
      if (choice == 0)
	next_note = DOMINANT;
      else if (choice == 1)
	next_note = SUBTONIC;
    }
  else if (current_note == SUBTONIC)
    {
      choice = rand () % (3);
      if (choice == 0)
	next_note = MEDIANT;
      else if (choice == 1)
	next_note = TONIC;
      else if (choice == 2)
	next_note = SUBMEDIANT;
    }
  else if (current_note == MEDIANT)
    {
      choice = rand () % (4);
      if (choice == 0)
	next_note = DOMINANT;
      else if (choice == 1)
	next_note = SUBDOMINANT;
      else if (choice == 2)
	next_note = SUBTONIC;
      else if (choice == 3)
	next_note = TONIC;
    }
  else if (current_note == SUBDOMINANT)
    {
      choice = rand () % (4);
      if (choice == 0)
	next_note = SUBMEDIANT;
      else if (choice == 1)
	next_note = DOMINANT;
      else if (choice == 2)
	next_note = MEDIANT;
      else if (choice == 3)
	next_note = TONIC;
    }
  else if (current_note == DOMINANT)
    {
      choice = rand () % (4);
      if (choice == 0)
	next_note = SUBTONIC;
      else if (choice == 1)
	next_note = TONIC;
      else if (choice == 2)
	next_note = SUBMEDIANT;
      else if (choice == 3)
	next_note = SUBDOMINANT;
    }
  else if (current_note == SUBMEDIANT)
    {
      choice = rand () % (3);
      if (choice == 0)
	next_note = DOMINANT;
      else if (choice == 1)
	next_note = TONIC;
      else if (choice == 2)
	next_note = MEDIANT;
    }
  return (next_note);
}

void make_progression_a_chords (int current_note)
/* this progression always starts on the tonic chord */
{
  int quality;
  int sound[3];
  int i = 0;
  int j;
  struct sounds temp[MEASURES];
/* makes a progression backwards from the current note
then recopies it so the progression works to the current note
which is actually the last note */
  quality = find_quality (current_note);
  sound[0] = current_note + BEGINNING_PITCH + transposefactor;
  makechords (quality, sound);
  temp[i].scale_degree = current_note;
  temp[i].quality = quality;
  for (j = 0; j < 3; ++j)
    temp[i].sound[j] = sound[j];
  for (i = 1; i < MEASURES; ++i)
    {
      current_note = progression_logic (current_note);
      quality = find_quality (current_note);
      sound[0] = current_note + BEGINNING_PITCH + transposefactor;
      makechords (quality, sound);
      temp[i].scale_degree = current_note;
      temp[i].quality = quality;
      for (j = 0; j < 3; ++j)
	temp[i].sound[j] = sound[j];
    }
  for (i = 0; i < MEASURES; ++i)
    {
      chords_a[MEASURES - 1 - i].scale_degree = temp[i].scale_degree;
      chords_a[MEASURES - 1 - i].quality = temp[i].quality;
      for (j = 0; j < 3; ++j)
	chords_a[MEASURES - 1 - i].sound[j] = temp[i].sound[j];
    }
/* now make first measure of phrase the TONIC chord */
  chords_a[0].scale_degree = TONIC;
  chords_a[0].quality = MINOR;
  sound[0] = BEGINNING_PITCH + transposefactor;
  makechords (MINOR, sound);
  for (j = 0; j < 3; ++j)
    chords_a[0].sound[j] = sound[j];
  
  for (i = 0; i < MEASURES; ++i)
       if (chords_a[i].sound[0] - BEGINNING_PITCH == TONIC)
         {
          chords_inversion_a[i].sound[0] = chords_a[i].sound[0];
          chords_inversion_a[i].sound[1] = chords_a[i].sound[1];
          chords_inversion_a[i].sound[2] = chords_a[i].sound[2]; 
         } 
         else if (chords_a[i].sound[0] - BEGINNING_PITCH == SUBTONIC)
         {
          chords_inversion_a[i].sound[0] = chords_a[i].sound[0] - 12;
          chords_inversion_a[i].sound[1] = chords_a[i].sound[1] - 12;
          chords_inversion_a[i].sound[2] = chords_a[i].sound[2] - 12;
         }
         else if (chords_a[i].sound[0] - BEGINNING_PITCH == MEDIANT)
         {
          chords_inversion_a[i].sound[0] = chords_a[i].sound[0];
          chords_inversion_a[i].sound[1] = chords_a[i].sound[1];
          chords_inversion_a[i].sound[2] = chords_a[i].sound[2] - 12;
        }
        else if (chords_a[i].sound[0] - BEGINNING_PITCH == SUBDOMINANT)
         {
          chords_inversion_a[i].sound[0] = chords_a[i].sound[0];
          chords_inversion_a[i].sound[1] = chords_a[i].sound[1];
          chords_inversion_a[i].sound[2] = chords_a[i].sound[2] - 12;
        }
        else if (chords_a[i].sound[0] - BEGINNING_PITCH == DOMINANT)
         {
          chords_inversion_a[i].sound[0] = chords_a[i].sound[0];
          chords_inversion_a[i].sound[1] = chords_a[i].sound[1] - 12;
          chords_inversion_a[i].sound[2] = chords_a[i].sound[2] - 12;
        }
        else if (chords_a[i].sound[0] - BEGINNING_PITCH == SUBMEDIANT)
         {
          chords_inversion_a[i].sound[0] = chords_a[i].sound[0] + 12 - 12;
          chords_inversion_a[i].sound[1] = chords_a[i].sound[1] - 12;
          chords_inversion_a[i].sound[2] = chords_a[i].sound[2] - 12;
        }
  }

void make_progression_b_chords (int current_note)
/* this progression always starts on the tonic chord */
{
  int quality;
  int sound[3];
  int i = 0;
  int j;
  struct sounds temp[MEASURES];
/* makes a progression backwards from the current note
then recopies it so the progression works to the current note
which is actually the last note */
  quality = find_quality (current_note);
  sound[0] = current_note + BEGINNING_PITCH + transposefactor;
  makechords (quality, sound);
  temp[i].scale_degree = current_note;
  temp[i].quality = quality;
  for (j = 0; j < 3; ++j)
    temp[i].sound[j] = sound[j];
  for (i = 1; i < MEASURES; ++i)
    {
      current_note = progression_logic (current_note);
      quality = find_quality (current_note);
      sound[0] = current_note + BEGINNING_PITCH + transposefactor;
      makechords (quality, sound);
      temp[i].scale_degree = current_note;
      temp[i].quality = quality;
      for (j = 0; j < 3; ++j)
	temp[i].sound[j] = sound[j];
    }
  for (i = 0; i < MEASURES; ++i)
    {
      chords_b[MEASURES - 1 - i].scale_degree = temp[i].scale_degree;
      chords_b[MEASURES - 1 - i].quality = temp[i].quality;
      for (j = 0; j < 3; ++j)
	chords_b[MEASURES - 1 - i].sound[j] = temp[i].sound[j];
    }

  for (i = 0; i < MEASURES; ++i)
       if (chords_b[i].sound[0] - BEGINNING_PITCH == TONIC)
         {
          chords_inversion_b[i].sound[0] = chords_b[i].sound[0];
          chords_inversion_b[i].sound[1] = chords_b[i].sound[1];
          chords_inversion_b[i].sound[2] = chords_b[i].sound[2]; 
         } 
         else if (chords_b[i].sound[0] - BEGINNING_PITCH == SUBTONIC)
         {
          chords_inversion_b[i].sound[0] = chords_b[i].sound[0] - 12;
          chords_inversion_b[i].sound[1] = chords_b[i].sound[1] - 12;
          chords_inversion_b[i].sound[2] = chords_b[i].sound[2] - 12;
         }
         else if (chords_b[i].sound[0] - BEGINNING_PITCH == MEDIANT)
         {
          chords_inversion_b[i].sound[0] = chords_b[i].sound[0];
          chords_inversion_b[i].sound[1] = chords_b[i].sound[1];
          chords_inversion_b[i].sound[2] = chords_b[i].sound[2] - 12;
        }
        else if (chords_b[i].sound[0] - BEGINNING_PITCH == SUBDOMINANT)
         {
          chords_inversion_b[i].sound[0] = chords_b[i].sound[0];
          chords_inversion_b[i].sound[1] = chords_b[i].sound[1];
          chords_inversion_b[i].sound[2] = chords_b[i].sound[2] - 12;
        }
        else if (chords_b[i].sound[0] - BEGINNING_PITCH == DOMINANT)
         {
          chords_inversion_b[i].sound[0] = chords_b[i].sound[0];
          chords_inversion_b[i].sound[1] = chords_b[i].sound[1] - 12;
          chords_inversion_b[i].sound[2] = chords_b[i].sound[2] - 12;
        }
        else if (chords_b[i].sound[0] - BEGINNING_PITCH == SUBMEDIANT)
         {
          chords_inversion_b[i].sound[0] = chords_b[i].sound[0] + 12 - 12 ;
          chords_inversion_b[i].sound[1] = chords_b[i].sound[1] -12;
          chords_inversion_b[i].sound[2] = chords_b[i].sound[2] -12;
        }  
}

void make_progression_c_chords (int current_note)
/* this progression always starts on the tonic chord */
{
  int quality;
  int sound[3];
  int i = 0;
  int j;
  struct sounds temp[MEASURES];
/* makes a progression backwards from the current note
then recopies it so the progression works to the current note
which is actually the last note */
  quality = find_quality (current_note);
  sound[0] = current_note + BEGINNING_PITCH + transposefactor;
  makechords (quality, sound);
  temp[i].scale_degree = current_note;
  temp[i].quality = quality;
  for (j = 0; j < 3; ++j)
    temp[i].sound[j] = sound[j];
  for (i = 1; i < MEASURES; ++i)
    {
      current_note = progression_logic (current_note);
      quality = find_quality (current_note);
      sound[0] = current_note + BEGINNING_PITCH + transposefactor;
      makechords (quality, sound);
      temp[i].scale_degree = current_note;
      temp[i].quality = quality;
      for (j = 0; j < 3; ++j)
	temp[i].sound[j] = sound[j];
    }
  for (i = 0; i < MEASURES; ++i)
    {
      chords_c[MEASURES - 1 - i].scale_degree = temp[i].scale_degree;
      chords_c[MEASURES - 1 - i].quality = temp[i].quality;
      for (j = 0; j < 3; ++j)
	chords_c[MEASURES - 1 - i].sound[j] = temp[i].sound[j];
    }
/* now make first measure of phrase the TONIC chord */
  chords_c[0].scale_degree = TONIC;
  chords_c[0].quality = MINOR;
  sound[0] = BEGINNING_PITCH + transposefactor;
  makechords (MINOR, sound);
  for (j = 0; j < 3; ++j)
    chords_c[0].sound[j] = sound[j];

     for (i = 0; i < MEASURES; ++i)
       if (chords_c[i].sound[0] - BEGINNING_PITCH - transposefactor == TONIC)
         {
          chords_inversion_c[i].sound[0] = chords_c[i].sound[0];
          chords_inversion_c[i].sound[1] = chords_c[i].sound[1];
          chords_inversion_c[i].sound[2] = chords_c[i].sound[2]; 
         } 
         else if (chords_c[i].sound[0] - BEGINNING_PITCH - transposefactor == SUBTONIC)
         {
          chords_inversion_c[i].sound[0] = chords_c[i].sound[0] - 12;
          chords_inversion_c[i].sound[1] = chords_c[i].sound[1] - 12;
          chords_inversion_c[i].sound[2] = chords_c[i].sound[2] - 12;
         }
         else if (chords_c[i].sound[0] - BEGINNING_PITCH - transposefactor == MEDIANT)
         {
          chords_inversion_c[i].sound[0] = chords_c[i].sound[0];
          chords_inversion_c[i].sound[1] = chords_c[i].sound[1];
          chords_inversion_c[i].sound[2] = chords_c[i].sound[2] - 12;
        }
        else if (chords_c[i].sound[0] - BEGINNING_PITCH - transposefactor == SUBDOMINANT)
         {
          chords_inversion_c[i].sound[0] = chords_c[i].sound[0];
          chords_inversion_c[i].sound[1] = chords_c[i].sound[1];
          chords_inversion_c[i].sound[2] = chords_c[i].sound[2] - 12;
        }
        else if (chords_c[i].sound[0] - BEGINNING_PITCH - transposefactor == DOMINANT)
         {
          chords_inversion_c[i].sound[0] = chords_c[i].sound[0];
          chords_inversion_c[i].sound[1] = chords_c[i].sound[1] - 12;
          chords_inversion_c[i].sound[2] = chords_c[i].sound[2] - 12;
        }
        else if (chords_c[i].sound[0] - BEGINNING_PITCH - transposefactor == SUBMEDIANT)
         {
          chords_inversion_c[i].sound[0] = chords_c[i].sound[0] + 12 - 12;
          chords_inversion_c[i].sound[1] = chords_c[i].sound[1] - 12;
          chords_inversion_c[i].sound[2] = chords_c[i].sound[2] - 12;
        }  

}

void make_progression_d_chords (int current_note)
/* this progression always starts on the tonic chord */
{
  int quality;
  int sound[3];
  int i = 0;
  int j;
  struct sounds temp[MEASURES];
/* makes a progression backwards from the current note
then recopies it so the progression works to the current note
which is actually the last note */
  quality = find_quality (current_note);
  sound[0] = current_note + BEGINNING_PITCH + transposefactor;
  makechords (quality, sound);
  temp[i].scale_degree = current_note;
  temp[i].quality = quality;
  for (j = 0; j < 3; ++j)
    temp[i].sound[j] = sound[j];
  for (i = 1; i < MEASURES; ++i)
    {
      current_note = progression_logic (current_note);
      quality = find_quality (current_note);
      sound[0] = current_note + BEGINNING_PITCH + transposefactor;
      makechords (quality, sound);
      temp[i].scale_degree = current_note;
      temp[i].quality = quality;
      for (j = 0; j < 3; ++j)
	temp[i].sound[j] = sound[j];
    }
  for (i = 0; i < MEASURES; ++i)
    {
      chords_d[MEASURES - 1 - i].scale_degree = temp[i].scale_degree;
      chords_d[MEASURES - 1 - i].quality = temp[i].quality;
      for (j = 0; j < 3; ++j)
	chords_d[MEASURES - 1 - i].sound[j] = temp[i].sound[j];
    }

  for (i = 0; i < MEASURES; ++i)
       if (chords_d[i].sound[0] - BEGINNING_PITCH - transposefactor == TONIC)
         {
          chords_inversion_d[i].sound[0] = chords_d[i].sound[0];
          chords_inversion_d[i].sound[1] = chords_d[i].sound[1];
          chords_inversion_d[i].sound[2] = chords_d[i].sound[2]; 
         } 
         else if (chords_d[i].sound[0] - BEGINNING_PITCH - transposefactor == SUBTONIC)
         {
          chords_inversion_d[i].sound[0] = chords_d[i].sound[0] - 12;
          chords_inversion_d[i].sound[1] = chords_d[i].sound[1] - 12;
          chords_inversion_d[i].sound[2] = chords_d[i].sound[2] - 12;
         }
         else if (chords_d[i].sound[0] - BEGINNING_PITCH - transposefactor == MEDIANT)
         {
          chords_inversion_d[i].sound[0] = chords_d[i].sound[0];
          chords_inversion_d[i].sound[1] = chords_d[i].sound[1];
          chords_inversion_d[i].sound[2] = chords_d[i].sound[2] - 12;
        }
        else if (chords_d[i].sound[0] - BEGINNING_PITCH - transposefactor == SUBDOMINANT)
         {
          chords_inversion_d[i].sound[0] = chords_d[i].sound[0];
          chords_inversion_d[i].sound[1] = chords_d[i].sound[1];
          chords_inversion_d[i].sound[2] = chords_d[i].sound[2] - 12;
        }
        else if (chords_d[i].sound[0] - BEGINNING_PITCH - transposefactor == DOMINANT)
         {
          chords_inversion_d[i].sound[0] = chords_d[i].sound[0];
          chords_inversion_d[i].sound[1] = chords_d[i].sound[1] - 12;
          chords_inversion_d[i].sound[2] = chords_d[i].sound[2] - 12;
        }
        else if (chords_d[i].sound[0] - BEGINNING_PITCH - transposefactor == SUBMEDIANT)
         {
          chords_inversion_d[i].sound[0] = chords_d[i].sound[0] + 12 - 12;
          chords_inversion_d[i].sound[1] = chords_d[i].sound[1] - 12;
          chords_inversion_d[i].sound[2] = chords_d[i].sound[2] - 12;
        }  
  
}

void initialize_layers (void)
{
  int i;
  int j;
  for (i = 0; i < TOTAL_CHORDS * BEATS_PER_MEASURE; ++i)
    for (j = 0; j < 5; ++j)
      layer[j][i] = -1;
}

int copy_progression_to_layers (struct sounds chords[], int layer_start)
/* makes each chord at beginning of the measure and
tied the number of beats times two so that melody
and arpeggiated bass may be added to layers */
{
  int i, j, k, m;
/* copy harmonic progression (k=2 to 5) to layers */
  k = layer_start;
  for (i = 0; i < MEASURES; ++i)
    {
      for (j = 1; j < 4; ++j)
	layer[j][k] = chords[i].sound[j - 1];
      ++k;
      for (m = 0; m < BEATS_PER_MEASURE * 2 - 1; ++m)
	{
	  for (j = 1; j < 4; ++j)
	    layer[j][k] = chords[i].sound[j - 1] + 128;
	  ++k;
	}
    }
  return (k);
}

void setup_arpeggio_patterns (int pattern_a[], int pattern_a_prime[],
       int pattern_b[], int pattern_new_b[],
       int pattern_c[], int pattern_c_prime[],
       int pattern_d[], int pattern_d_prime[])
{
  int i;
  for (i = 0; i < BEATS_PER_MEASURE * 2; ++i)
    {
      pattern_a[i] = -1;
      pattern_a_prime[i] = -1;
      pattern_b[i] = -1;
      pattern_new_b[i] = -1;
      pattern_c[i] = -1;
      pattern_c_prime[i] = -1;
      pattern_d[i] = -1;
      pattern_d_prime[i] = -1;
    }  
  for (i = 2; i < (BEATS_PER_MEASURE * 2) - 1; ++i)
    {
      pattern_a[i] = rand () % (7) - 4;
      pattern_a_prime[i] = rand () % (10) - 7;
      pattern_b[i] = rand () % (7) - 4;
      pattern_new_b[i] = rand () % (9) - 6;
      pattern_c[i] = rand () % (7) - 4;
      pattern_c_prime[i] = rand () % (9) - 6;
      pattern_d[i] = rand () % (7) - 4;
      pattern_d_prime[i] = rand () % (8) - 5;      
    }
}

void make_arpeggiated_bass (int pattern[], struct sounds chords[], int arpeggio[])
{
  int note, k, i, m, j, found;
  int temp[3][MEASURES * BEATS_PER_MEASURE * 2];
  int pattern_counter = 0;
/* -1 ior lower is silence; 0 is chords.sound[0] etc */
  k = 0;
  for (i = 0; i < MEASURES; ++i)
    for (m = 0; m < (BEATS_PER_MEASURE * 2); ++m)
      {
  for (j = 0; j < 3; ++j)
    temp[j][k] = chords[i].sound[j];
  ++k;
      }
  for (i = 0; i < MEASURES * BEATS_PER_MEASURE * 2; ++i)
    arpeggio[i] = -1;
  for (i = 0; i < (MEASURES * BEATS_PER_MEASURE * 2); ++i)    // why is i start with 1 ????? because of adding a previous nonharmonic tone?
    {
      note = -1;
      if (pattern[pattern_counter] > -1)
  do
    {
      note = rand () % (UPPER_ARPEGGIO_RANGE - LOWER_ARPEGGIO_RANGE)
        + LOWER_ARPEGGIO_RANGE;
      if (note % 12 == (temp[pattern[pattern_counter]][i]) % 12)
        found = 1;
      else
        found = 0;
    }
  while (!found);
      arpeggio[i] = note;
      ++pattern_counter;
      if (pattern_counter == BEATS_PER_MEASURE * 2)
  pattern_counter = 0;
    }
}

void make_arpeggiated_bass1 (int pattern[], struct sounds chords[], int arpeggio[])
{
  int note, k, i, m, j, found;
  int temp[3][MEASURES * BEATS_PER_MEASURE * 2];
  int pattern_counter = 0;
/* -1 ior lower is silence; 0 is chords.sound[0] etc */
  k = 0;
  for (i = 0; i < MEASURES; ++i)
    for (m = 0; m < (BEATS_PER_MEASURE * 2); ++m)
      {
  for (j = 0; j < 3; ++j)
    temp[j][k] = chords[i].sound[j];
  ++k;
      }
  for (i = 0; i < MEASURES * BEATS_PER_MEASURE * 2; ++i)
    arpeggio[i] = -1;
  for (i = 0; i < (MEASURES * BEATS_PER_MEASURE * 2); ++i)    // why is i start with 1 ????? because of adding a previous nonharmonic tone?
    {
      note = -1;
      if (pattern[pattern_counter] > -1)
  do
    {
      note = (rand () % (UPPER_ARPEGGIO_RANGE - LOWER_ARPEGGIO_RANGE)
        + LOWER_ARPEGGIO_RANGE) + DOMINANT;
      if (note % 12 == (temp[pattern[pattern_counter]][i]) % 12)
        found = 1;
      else
        found = 0;
    }
  while (!found);
      arpeggio[i] = note;
      ++pattern_counter;
      if (pattern_counter == BEATS_PER_MEASURE * 2)
  pattern_counter = 0;
    }
}

int copy_arpeggio_to_layers (int arpeggio[], int layer_start)
{
  int i;
  int k = layer_start;
  for (i = 0; i < MEASURES * BEATS_PER_MEASURE * 2; ++i)
    {
      layer[4][k] = arpeggio[i];
      ++k;
    }
  return (k);
}

void make_skeleton_melody (struct sounds chords[], int melody[])
/* makes a skeleton melody no more that the number of
beats per measure, but probably much less. The
first of every measure is a chord tone */
{
  int note;
  int i, j, k, m;
  int found;
  int previous;
  int temp[3][MEASURES * BEATS_PER_MEASURE];
  k = 0;
  for (i = 0; i < MEASURES; ++i)
    for (m = 0; m < BEATS_PER_MEASURE; ++m)
      {
	for (j = 0; j < 3; ++j)
	  temp[j][k] = chords[i].sound[j];
	++k;
      }
  for (i = 0; i < MEASURES * BEATS_PER_MEASURE; ++i)
    melody[i] = -1;
  do
    {
      note = rand () % (UPPER_MELODIC_RANGE - LOWER_MELODIC_RANGE)
	+ LOWER_MELODIC_RANGE;
      if (note % 12 == (temp[0][0]) % 12 ||
	  note % 12 == (temp[1][0]) % 12 || note % 12 == (temp[2][0]) % 12)
	found = 1;
      else
	found = 0;
    }
  while (!found);
  previous = note;
  melody[0] = note;
  for (i = 1; i < MEASURES * BEATS_PER_MEASURE; ++i)
    {
      if (i % BEATS_PER_MEASURE == 0 || rand () % (3) == 1)
	{
	  do
	    {
	      note = rand () % (UPPER_MELODIC_RANGE - LOWER_MELODIC_RANGE)
		+ LOWER_MELODIC_RANGE;
	      if (note % 12 == (temp[0][i]) % 12 ||
		  note % 12 == (temp[1][i]) % 12 ||
		  note % 12 == (temp[2][i]) % 12)
		found = 1;
	      else
		found = 0;
	      if (abs (previous - note) > 9)
		found = 0;
	    }
	  while (!found);
	  previous = note;
	  melody[i] = note;
	}
    }
  /* this makes the last measure one sustained melody note */
  for (i = ((MEASURES - 1) * BEATS_PER_MEASURE) + 1;
       i < MEASURES * BEATS_PER_MEASURE; ++i)
    melody[i] = melody[(MEASURES - 1) * BEATS_PER_MEASURE] + 128;
}

void copy_melody_to_another (int melody[], int melody1[])
{
  int i;
  for (i = 0; i < MEASURES * BEATS_PER_MEASURE; ++i)
    melody1[i] = melody[i];
}

void make_scale_array (void)
{
  int aeolian[] = { 2, 1, 2, 2, 1, 2, 2 };
  int mode_marker = 0;
  int i;
  scale_array[0] = TONIC + transposefactor;
  for (i = 0; i < ((9 * 8) - 2); ++i)
    {
      scale_array[i + 1] = scale_array[i] + aeolian[mode_marker];
      ++mode_marker;
      if (mode_marker == 7)
	mode_marker = 0;
    }
}

int find_nonharmonic_tone (int harmonic_tone, int position)
{
  int non_harmonic_tone;
  int i = 0;
  int found = 0;
  do
    {
      ++i;
      if (scale_array[i] == harmonic_tone)
	found = 1;
    }
  while (found == 0);
  if (position == BELOW)
    non_harmonic_tone = scale_array[i - 1];
  else if (position == ABOVE)
    non_harmonic_tone = scale_array[i + 1];
  return (non_harmonic_tone);
}

void add_non_harmonic_tones (int melody[])
{
  int i;
  int nonharmonic_type;
  int nonharmonic_tone;
  for (i = 1; i < MEASURES * BEATS_PER_MEASURE; ++i)
    {
      if (melody[i] >= 0 && melody[i] <= 127 &&
	  melody[i - 1] == -1 && rand () % (2))
	{
	  nonharmonic_type = rand () % (2);
	  if (nonharmonic_type == 0)
	    nonharmonic_tone = find_nonharmonic_tone (melody[i], ABOVE);
	  else if (nonharmonic_type == 1)
	    nonharmonic_tone = find_nonharmonic_tone (melody[i], BELOW);
	  melody[i - 1] = nonharmonic_tone;
	}
    }
}

void add_sustaining_tones (int melody[])
{
  int i;
  for (i = 1; i < MEASURES * BEATS_PER_MEASURE; ++i)
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
/* copies each  note  to two tied notes int the layer
so that a harmonic bass of two notes to one melody
melody note may be possible */
{
  int i;
  int k = layer_start;
  for (i = 0; i < MEASURES * BEATS_PER_MEASURE; ++i)
    {
      layer[0][k] = melody[i];
      ++k;
      if (melody[i] == -1)
	layer[0][k] = -1;
      else if (melody[i] >= 0 && melody[i] <= 127)
	layer[0][k] = melody[i] + 128;
      else if (melody[i] >= 128)
	layer[0][k] = melody[i];
      ++k;
    }
  return (k);
}

void add_non_harmonic_tones_arpeggio (int arpeggio[])
{
  int i;
  int nonharmonic_type;
  int nonharmonic_tone;
  for (i = 1; i < MEASURES * BEATS_PER_MEASURE * 2; ++i)
    {
      if (arpeggio[i] >= 0 && arpeggio[i] <= 127 && arpeggio[i - 1] == -1)
	{
	  nonharmonic_type = rand () % (2);
	  if (nonharmonic_type == 0)
	    nonharmonic_tone = find_nonharmonic_tone (arpeggio[i], ABOVE);
	  else if (nonharmonic_type == 1)
	    nonharmonic_tone = find_nonharmonic_tone (arpeggio[i], BELOW);
	  arpeggio[i - 1] = nonharmonic_tone;
	}
    }
}

void play_layers (void)
{
  /* -1 represents a silence. 128 + note means that note is tied */
  static int previous_note[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
  int current_note[10];
  int i, j;
  int volume;
  int coda_slowdown = 0;
  static int channel[8] = { 144, 146, 146, 146, 145, 147, 147, 147 };
/* need as many channel arrays as layers */
  program_number[0] = 68;
  program_number[1] = 7;
  program_number[2] = 88;
  program_number[3] = 0;
  program_number[4] = 0;
  program_number[5] = 0;
  program_number[6] = 0;
  program_number[7] = 0;
#if PROGRAM_NUMBERS_ON
  program_setup ();
#endif
  for (i = 0; i < TOTAL_CHORDS * BEATS_PER_MEASURE; ++i)
    {
      if (i == BEATS_PER_MEASURE * 2 * MEASURES)
	    {
	      program_number[0] = 71;
        #if PROGRAM_NUMBERS_ON
	      program_setup ();
        #endif
	    }
     if (i == BEATS_PER_MEASURE * 2 * MEASURES * 2)
	{
	  program_number[0] = 68;
#if PROGRAM_NUMBERS_ON
	  program_setup ();
#endif
	}
  if (i == BEATS_PER_MEASURE * 2 * MEASURES *  3)
	{
	  program_number[0] = 71;
#if PROGRAM_NUMBERS_ON
	  program_setup ();
#endif
	}
  else if (i == BEATS_PER_MEASURE * 2 * MEASURES * 4)
	{
	  program_number[0] = 74;
#if PROGRAM_NUMBERS_ON
	  program_setup ();
#endif
	}
  else if (i == BEATS_PER_MEASURE * 2 * MEASURES * 5)
	{
	  program_number[0] = 75;
#if PROGRAM_NUMBERS_ON
	  program_setup ();
#endif
	}
  else if (i == BEATS_PER_MEASURE * 2 * MEASURES * 6)
	{
	  program_number[0] = 74;
#if PROGRAM_NUMBERS_ON
	  program_setup ();
#endif
	}
  else if (i == BEATS_PER_MEASURE * 2 * MEASURES * 7)
	{
	  program_number[0] = 68;
#if PROGRAM_NUMBERS_ON
	  program_setup ();
#endif
	}
  else if (i == BEATS_PER_MEASURE * 2 * MEASURES * 8)
	{
	  program_number[0] = 71;
#if PROGRAM_NUMBERS_ON
	  program_setup ();
#endif
	}
	coda_slowdown = tempo;
      for (j = 0; j < 5; ++j)
	{
	  current_note[j] = layer[j][i];
	  if (previous_note[j] >= 0 &&
	      previous_note[j] <= 127 && current_note[j] == -1)
	    play (0, channel[j] - 16, previous_note[j], 0);
	  else if (previous_note[j] >= 0 && current_note[j] >= 0 &&
		   previous_note[j] <= 127 && current_note[j] <= 127)
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
	  volume = 127;
	  current_note[j] = layer[j][i];
	  if (previous_note[j] == -1 && current_note[j] >= 0 &&
	      current_note[j] <= 127)
	    play (0, channel[j], current_note[j], volume);
	  else if (previous_note[j] >= 0 && current_note[j] >= 0 &&
		   previous_note[j] <= 127 && current_note[j] <= 127)
	    play (0, channel[j], current_note[j], volume);
	  else if (previous_note[j] >= 128 && current_note[j] >= 0
		   && current_note[j] <= 127)
	    play (0, channel[j], current_note[j], volume);
	  previous_note[j] = layer[j][i];
	}			/* end of second loop */
    play (tempo /*+ coda_slowdown*/, 152 - 16, 100, 0);
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

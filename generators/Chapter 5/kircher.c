/*kircher.c*/
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "convert3.h"
#define GENERAL_MIDI_ON 1
#define PROGRAM_NUMBERS_ON 1
#define PITCH_LENGTH 7
#define NUMBER_VOICES 4
#define ALTERNATES 20
#define PHRASES_OF_VOICES 4
#define RHYTHMIC_PATTERNS 9
#define RHYTHMIC_UNITS 7
#define DOTTED_WHOLE 12
#define WHOLE 8
#define DOTTED_HALF 6
#define HALF 4
#define DOTTED_QUARTER 3
#define QUARTER 2
#define EIGHTH  1
#define C2  36
#define Cs2 37
#define Db2 37
#define D2  38
#define Ds2 39
#define Eb2 39
#define E2  40
#define F2  41
#define Fs2 42
#define Gb2 42
#define G2  43
#define Gs2 44
#define Ab2 44
#define A2  45
#define As2 46
#define Bb2 46
#define B2  47
#define C3  48
#define Cs3 49
#define Db3 49
#define D3  50
#define Ds3 51
#define Eb3 51
#define E3  52
#define F3  53
#define Fs3 54
#define Gb3 54
#define G3  55
#define Gs3 56
#define Ab3 56
#define A3  57
#define As3 58
#define Bb3 58
#define B3  59
#define C4  60
#define Cs4 61
#define Db4 61
#define D4  62
#define Ds4 63
#define Eb4 63
#define E4  64
#define F4  65
#define Fs4 66
#define Gb4 66
#define G4  67
#define Gs4 68
#define Ab4 68
#define A4  69
#define As4 70
#define Bb4 70
#define B4  71
#define C5  72
#define Cs5 73
#define Db5 73
#define D5  74
#define Ds5 75
#define Eb5 75
#define E5  76
#define F5  77
#define Fs5 78
#define Gb5 78
#define G5  79
#define Gs5 80
#define Ab5 80
#define A5  81
#define As5 82
#define Bb5 82
#define B5  83
#define C6  84
#define MODETYPE 4
#define VOICES 4
#define PITCHES 8
void roll_the_dice_baby (void);
int mode[MODETYPE][VOICES][PITCHES] = { {{C5, D5, Eb5, F5, G5, A5, B5, C6},	/*Dorian */
					 {C4, D4, Eb4, F4, G4, A4, B4, C5},
					 {C3, D3, Eb3, F3, G3, A3, B3, C4},
					 {C2, D2, Eb2, F2, G2, A2, B2, C3}},
{{C5, D5, Eb5, F5, G5, Ab5, Bb5, C6},	/* Phrygian */
 {C4, D4, Eb4, F4, G4, Ab4, Bb4, C5},
 {C3, D3, Eb3, F3, G3, Ab3, Bb3, C4},
 {C2, D2, Eb2, F2, G2, Ab2, Bb2, C3}},
{{C5, D5, E5, Fs5, G5, A5, B5, C6},	/* Lydian */
 {C4, D4, E4, Fs4, G4, A4, B4, C5},
 {C3, D3, E3, Fs3, G3, A3, B3, C4},
 {C2, D2, E2, Fs2, G2, A2, B2, C3}},
{{C5, D5, E5, F5, G5, A5, Bb5, C6},	/* Mixolydian */
 {C4, D4, E4, F4, G4, A4, Bb4, C5},
 {C3, D3, E3, F3, G3, A3, Bb3, C4},
 {C2, D2, E2, F2, G2, A2, Bb2, C3}}
};
int rhythm_anakreontic[RHYTHMIC_PATTERNS][RHYTHMIC_UNITS] =
  { {WHOLE, DOTTED_WHOLE, HALF, HALF, HALF, WHOLE, WHOLE},
{HALF, WHOLE, WHOLE, WHOLE, HALF, WHOLE, WHOLE},
{HALF, QUARTER, QUARTER, QUARTER, QUARTER, HALF, WHOLE},
{HALF, DOTTED_QUARTER, EIGHTH, DOTTED_QUARTER, EIGHTH, HALF, WHOLE},
{HALF, WHOLE, HALF, HALF, HALF, WHOLE, WHOLE},
{WHOLE, DOTTED_HALF, QUARTER, QUARTER, QUARTER, HALF, WHOLE},
{QUARTER, HALF, QUARTER, QUARTER, QUARTER, HALF, WHOLE},
{QUARTER, EIGHTH, EIGHTH, QUARTER, QUARTER, HALF, HALF},
{QUARTER, QUARTER, QUARTER, DOTTED_HALF, QUARTER, WHOLE, WHOLE}
};
int
  pitch_anakreontic[PHRASES_OF_VOICES][ALTERNATES][NUMBER_VOICES]
  [PITCH_LENGTH] = { {{{5, 5, 5, 4, 3, 2, 3},
		       {7, 7, 8, 6, 5, 5, 5},
		       {2, 3, 3, 8, 8, 7, 8},
		       {5, 3, 8, 4, 8, 5, 8}},
		      {{3, 3, 2, 8, 8, 7, 8},
		       {8, 8, 7, 6, 6, 5, 5},
		       {5, 5, 5, 3, 4, 2, 3},
		       {8, 8, 5, 6, 4, 5, 1}},
		      {{5, 5, 5, 5, 5, 5, 5},
		       {8, 8, 8, 8, 7, 8, 8},
		       {3, 3, 3, 3, 2, 3, 3},
		       {8, 8, 8, 8, 5, 1, 1}},
		      {{5, 5, 6, 5, 3, 2, 3},
		       {7, 7, 8, 8, 8, 7, 8},
		       {2, 2, 4, 5, 5, 5, 5},
		       {5, 5, 4, 3, 1, 5, 1}},
		      {{3, 3, 4, 5, 4, 2, 3},
		       {8, 8, 7, 7, 6, 5, 5},
		       {5, 5, 4, 3, 8, 7, 8},
		       {1, 1, 2, 3, 4, 5, 1}},
		      {{3, 3, 4, 5, 4, 2, 3},
		       {8, 8, 7, 7, 6, 5, 5},
		       {5, 5, 4, 3, 8, 7, 8},
		       {1, 1, 2, 3, 4, 5, 1}},
		      {{5, 5, 5, 4, 3, 2, 3},
		       {8, 7, 8, 6, 5, 5, 5},
		       {3, 2, 3, 8, 8, 7, 8},
		       {1, 5, 3, 4, 1, 5, 1}},
		      {{3, 3, 2, 8, 6, 5, 5},
		       {5, 5, 5, 3, 4, 2, 3},
		       {8, 8, 7, 8, 8, 7, 8},
		       {1, 1, 5, 6, 4, 5, 1}},
		      {{3, 4, 5, 4, 3, 2, 3},
		       {5, 6, 5, 7, 8, 7, 8},
		       {8, 8, 8, 2, 5, 5, 5},
		       {1, 4, 5, 2, 1, 5, 1}},
		      {{5, 5, 5, 4, 3, 2, 3},
		       {7, 7, 8, 6, 5, 5, 5},
		       {2, 3, 3, 8, 8, 7, 8},
		       {5, 3, 1, 4, 1, 5, 1}},
		      {{3, 2, 3, 8, 3, 2, 3},
		       {5, 5, 5, 6, 5, 5, 5},
		       {8, 7, 8, 8, 8, 7, 8},
		       {1, 5, 3, 4, 1, 5, 1}},
		      {{3, 4, 5, 4, 3, 2, 3},
		       {5, 6, 5, 7, 8, 7, 8},
		       {8, 8, 8, 2, 5, 5, 5},
		       {1, 4, 3, 2, 1, 5, 1}},
		      {{5, 6, 5, 4, 3, 2, 3},
		       {8, 8, 7, 6, 5, 5, 5},
		       {3, 3, 3, 8, 8, 7, 8},
		       {8, 6, 3, 4, 1, 5, 1}},
		      {{3, 2, 8, 7, 6, 5, 5},
		       {8, 7, 6, 5, 4, 2, 3},
		       {5, 5, 3, 3, 8, 7, 8},
		       {1, 5, 6, 3, 4, 5, 1}},
		      {{8, 2, 4, 5, 6, 5, 5},
		       {5, 7, 8, 7, 8, 7, 8},
		       {3, 4, 8, 2, 4, 2, 3},
		       {8, 7, 6, 5, 4, 5, 1}},
		      {{8, 8, 7, 6, 5, 5, 5},
		       {5, 6, 5, 4, 3, 2, 3},
		       {3, 3, 3, 8, 8, 7, 8},
		       {8, 6, 3, 4, 1, 5, 1}},
		      {{5, 6, 5, 4, 3, 2, 3},
		       {8, 8, 7, 6, 5, 5, 5},
		       {3, 3, 3, 8, 8, 7, 8},
		       {1, 6, 3, 4, 1, 5, 1}},
		      {{3, 4, 5, 4, 3, 2, 3},
		       {5, 6, 5, 7, 8, 7, 8},
		       {8, 8, 8, 2, 5, 5, 5},
		       {1, 4, 3, 2, 1, 5, 1}},
		      {{3, 4, 5, 4, 3, 2, 3},
		       {5, 6, 5, 7, 8, 7, 8},
		       {8, 8, 8, 2, 5, 5, 5},
		       {1, 4, 3, 2, 1, 5, 1}},
		      {{5, 5, 5, 4, 3, 2, 3},
		       {8, 7, 7, 6, 5, 5, 5},
		       {3, 2, 3, 8, 8, 7, 8},
		       {1, 4, 3, 4, 1, 5, 1}}}, 
                       /*THIS IS PHRASE TWO */
                     {{{3, 3, 2, 8, 7, 7, 7},
                       {8, 8, 7, 6, 5, 4, 5},
                       {5, 5, 4, 3, 3, 2, 3},
                       {8, 8, 5, 6, 3, 7, 3}},
                      {{5, 5, 4, 3, 2, 2, 2},
                       {7, 7, 7, 5, 7, 6, 7},
                       {3, 3, 2, 3, 5, 4, 5},
                       {3, 3, 7, 8, 5, 2, 5}},
                      {{3, 3, 2, 8, 7, 6, 5},
                       {8, 8, 7, 6, 5, 4, 5},
                       {5, 5, 5, 3, 3, 8, 3},
                       {8, 8, 5, 6, 3, 4, 3}},
                      {{5, 5, 4, 4, 3, 2, 2}, 
                       {7, 7, 8, 2, 8, 6, 7},
                       {2, 2, 8, 5, 5, 4, 5},
                       {5, 5, 6, 7, 8, 2, 5}},
                      {{2, 3, 2, 8, 7, 6, 7},
                       {7, 8, 7, 5, 5, 4, 5},
                       {5, 5, 4, 3, 2, 2, 2},
                       {5, 1, 2, 3, 5, 2, 5}},
                      {{2, 3, 2, 8, 7, 6, 7},
                       {7, 8, 7, 5, 5, 4, 5},
                       {5, 5, 4, 3, 2, 2, 2},
                       {5, 1, 2, 3, 5, 2, 5}},
                      {{3, 3, 3, 3, 3, 4, 3},
                       {7, 7, 7, 7, 7, 7, 7},
                       {5, 5, 5, 5, 5, 2, 2},
                       {3, 3, 3, 3, 3, 7, 7}},
                      {{3, 3, 2, 8, 7, 6, 7},
                       {7, 7, 7, 5, 5, 4, 5},
                       {5, 5, 4, 3, 2, 2, 2},
                       {3, 3, 7, 8, 5, 2, 5}},
                      {{5, 5, 4, 3, 2, 4, 2},
                       {7, 7, 7, 8, 2, 8, 7},
                       {3, 3, 4, 5, 5, 8, 5},
                       {3, 3, 2, 8, 7, 6, 5}},
                      {{5, 5, 4, 3, 3, 2, 3},
                       {7, 8, 2, 7, 8, 7, 7},
                       {5, 5, 6, 5, 4, 4, 5},
                       {3, 3, 4, 5, 6, 7, 3}},
                      {{3, 4, 3, 3, 6, 5, 4},
                       {8, 8, 7, 8, 8, 8, 6},
                       {5, 6, 5, 1, 4, 3, 4},
                       {1, 4, 5, 6, 4, 1, 4}},
                      {{7, 3, 2, 8, 7, 6, 7},
                       {5, 8, 7, 5, 5, 4, 5},
                       {2, 5, 4, 3, 2, 2, 2},
                       {5, 1, 2, 3, 5, 2, 5}},
                      {{3, 3, 2, 2, 8, 2, 2},
                       {8, 8, 7, 6, 5, 6, 7},
                       {5, 5, 5, 4, 5, 4, 5},
                       {1, 1, 5, 2, 3, 2, 5}},
                      {{3, 4, 3, 8, 8, 8, 8},
                       {8, 8, 7, 6, 6, 5, 6},
                       {5, 6, 5, 3, 4, 3, 4},
                       {8, 4, 5, 6, 4, 1, 4}},
                      {{2, 3, 2, 8, 7, 6, 7},
                       {7, 8, 7, 5, 5, 4, 5},
                       {5, 5, 4, 3, 2, 2, 2},
                       {5, 1, 2, 3, 5, 2, 5}},
                      {{2, 3, 4, 5, 5, 4, 5},
                       {7, 8, 7, 7, 7, 6, 7},
                       {5, 5, 4, 3, 2, 2, 2},
                       {5, 1, 2, 3, 5, 2, 5}},
                      {{3, 3, 2, 2, 8, 2, 2},
                       {5, 5, 5, 4, 5, 4, 5},
                       {8, 8, 7, 6, 5, 6, 7},
                       {1, 1, 5, 2, 3, 2, 5}},
                      {{3, 4, 4, 5, 5, 4, 3},
                       {8, 8, 8, 7, 7, 6, 5},
                       {5, 1, 1, 2, 3, 1, 1},
                       {8, 6, 6, 5, 3, 4, 1}},
                      {{8, 2, 4, 5, 6, 5, 5},
                       {5, 7, 8, 7, 8, 7, 8},
                       {3, 4, 1, 2, 4, 2, 3},
                       {8, 7, 6, 5, 4, 5, 1}},
                      {{2, 3, 2, 8, 7, 6, 7},
                       {7, 8, 7, 5, 5, 4, 5},
                       {5, 5, 4, 3, 2, 2, 2},
                       {5, 1, 2, 3, 5, 2, 5}}},
                      /*THIS IS PHRASE THREE */
                     {{{5, 5, 5, 3, 5, 4, 5},	
                       {8, 8, 7, 8, 7, 7, 7},
                       {3, 3, 2, 8, 3, 2, 3},
                       {8, 8, 5, 6, 3, 7, 3}},
                      {{5, 5, 4, 3, 2, 8, 7},
                       {7, 7, 7, 5, 5, 3, 5},
                       {3, 3, 2, 8, 7, 8, 2},
                       {3, 3, 7, 8, 5, 6, 5}},
                      {{5, 5, 4, 3, 3, 2, 3},
                       {7, 7, 2, 7, 8, 7, 7},
                       {5, 5, 6, 5, 4, 4, 5},
                       {3, 3, 4, 5, 6, 7, 3}},
                      {{3, 6, 5, 3, 6, 5, 4},
                       {8, 8, 7, 8, 8, 8, 6},
                       {5, 4, 2, 8, 4, 3, 4},
                       {8, 4, 5, 6, 4, 8, 4}},
                      {{5, 5, 5, 4, 3, 2, 3},
                       {7, 7, 7, 7, 5, 7, 7},
                       {3, 3, 3, 2, 3, 4, 5},
                       {3, 3, 3, 7, 8, 7, 3}},
                      {{5, 5, 5, 3, 3, 2, 3},
                       {8, 8, 7, 8, 7, 7, 7},
                       {3, 3, 2, 1, 5, 4, 5},
                       {8, 8, 5, 6, 3, 7, 3}},
                      {{5, 5, 4, 3, 2, 4, 2},
                       {7, 7, 7, 8, 2, 8, 7},
                       {3, 3, 4, 5, 5, 8, 5},
                       {3, 3, 2, 1, 7, 6, 5}},
                      {{2, 2, 2, 2, 2, 8, 7},
                       {7, 7, 7, 7, 7, 5, 5},
                       {4, 4, 4, 4, 4, 3, 2},
                       {7, 7, 7, 7, 7, 8, 5}},
                      {{3, 4, 3, 8, 8, 8, 8},
                       {8, 8, 7, 6, 6, 5, 6},
                       {5, 6, 5, 3, 4, 3, 4},
                       {8, 4, 5, 6, 4, 8, 4}},
                      {{3, 3, 2, 8, 7, 6, 5},
                       {8, 8, 7, 6, 5, 4, 5},
                       {5, 5, 5, 5, 3, 8, 3},
                       {8, 8, 5, 6, 3, 4, 3}},
                      {{5, 5, 5, 4, 3, 6, 5},
                       {8, 8, 2, 8, 7, 8, 8},
                       {3, 3, 2, 4, 5, 1, 3},
                       {8, 8, 7, 6, 5, 4, 1}},
                      {{8, 8, 2, 3, 3, 4, 3},
                       {5, 5, 7, 8, 7, 8, 8},
                       {3, 3, 4, 1, 5, 6, 5},
                       {8, 8, 7, 6, 5, 4, 1}},
                      {{3, 4, 3, 3, 2, 8, 8},
                       {8, 8, 7, 8, 7, 5, 6},
                       {5, 6, 5, 4, 4, 3, 4},
                       {8, 4, 5, 6, 7, 8, 4}},
                      {{8, 8, 2, 3, 3, 4, 3},
                       {5, 5, 7, 8, 7, 8, 8},
                       {3, 3, 4, 1, 5, 6, 5},
                       {8, 8, 7, 6, 5, 4, 1}},
                      {{3, 2, 8, 6, 8, 7, 8},
                       {8, 7, 5, 4, 3, 5, 5},
                       {5, 4, 3, 1, 1, 2, 3},
                       {1, 2, 3, 4, 6, 5, 1}},
                      {{2, 3, 2, 8, 7, 6, 7},
                       {7, 8, 7, 5, 5, 4, 5},
                       {5, 5, 4, 3, 2, 2, 2},
                       {5, 1, 2, 3, 5, 2, 5}},
                      {{8, 8, 2, 8, 8, 7, 8},
                       {5, 6, 7, 5, 5, 5, 5},
                       {3, 4, 4, 3, 3, 2, 3},
                       {1, 4, 2, 3, 1, 5, 1}},
                      {{5, 6, 5, 4, 3, 2, 3},
                       {8, 8, 7, 6, 5, 5, 5},
                       {3, 3, 3, 8, 8, 7, 8},
                       {8, 6, 3, 4, 1, 5, 1}},
                      {{8, 8, 2, 8, 8, 7, 8},
                       {5, 6, 7, 5, 5, 5, 5},
                       {3, 4, 4, 3, 3, 2, 3},
                       {8, 4, 2, 3, 1, 5, 1}},
                      {{3, 2, 8, 6, 8, 7, 8},
                       {8, 7, 6, 5, 4, 5, 5},
                       {5, 4, 3, 8, 8, 2, 3},
                       {1, 2, 3, 4, 6, 5, 1}}},
                       /* THIS IS PHRASE FOUR */
                     {{{8, 8, 8, 2, 3, 2, 3},	
                       {6, 6, 5, 7, 8, 7, 8},
                       {4, 4, 5, 4, 5, 5, 5},
                       {4, 4, 3, 2, 1, 5, 1}},
                      {{5, 5, 5, 4, 3, 2, 3},
                       {7, 7, 7, 6, 5, 5, 5},
                       {3, 3, 3, 8, 8, 7, 8},
                       {3, 3, 3, 4, 1, 5, 1}},
                      {{7, 7, 7, 6, 8, 7, 8},
                       {5, 5, 5, 4, 3, 5, 5},
                       {3, 3, 3, 8, 8, 2, 3},
                       {3, 3, 3, 4, 6, 5, 1}},
                      {{5, 5, 4, 4, 3, 2, 3},
                       {7, 7, 6, 6, 5, 5, 5},
                       {2, 2, 2, 8, 8, 7, 8},
                       {5, 5, 2, 4, 1, 5, 1}},
                      {{3, 2, 8, 7, 6, 5, 5},
                       {8, 7, 6, 5, 4, 2, 3},
                       {5, 5, 3, 3, 8, 7, 8},
                       {8, 5, 6, 3, 4, 5, 1}},
                      {{3, 4, 5, 4, 3, 4, 3},
                       {8, 8, 8, 8, 8, 8, 8},
                       {5, 6, 5, 6, 5, 6, 5},
                       {1, 4, 3, 4, 1, 4, 1}},
                      {{8, 8, 8, 2, 3, 2, 3},
                       {6, 6, 5, 7, 8, 7, 8},
                       {8, 8, 3, 4, 5, 5, 5},
                       {4, 4, 3, 2, 1, 5, 1}},
                      {{3, 2, 8, 6, 8, 7, 8},
                       {8, 7, 5, 4, 3, 5, 5},
                       {5, 4, 3, 8, 8, 2, 3},
                       {1, 2, 3, 4, 6, 5, 1}},
                      {{8, 3, 4, 5, 4, 2, 3},
                       {6, 8, 7, 7, 6, 5, 5},
                       {4, 5, 4, 3, 8, 7, 8},
                       {4, 1, 2, 3, 4, 5, 1}},
                      {{8, 8, 8, 2, 3, 2, 3},
                       {6, 6, 5, 7, 8, 7, 8},
                       {8, 8, 3, 4, 5, 5, 5},
                       {4, 4, 3, 2, 1, 5, 1}},
                      {{5, 4, 4, 3, 3, 2, 3},
                       {8, 6, 7, 8, 8, 7, 8},
                       {3, 8, 2, 5, 5, 5, 5},
                       {1, 4, 2, 3, 1, 5, 1}},
                      {{4, 3, 4, 5, 4, 2, 3},
                       {8, 8, 7, 7, 6, 5, 5},
                       {6, 5, 4, 3, 8, 7, 8},
                       {4, 1, 2, 3, 4, 5, 1}},
                      {{3, 2, 8, 6, 8, 7, 8},
                       {8, 7, 5, 4, 3, 5, 5},
                       {5, 4, 3, 8, 8, 2, 3},
                       {1, 2, 3, 4, 6, 5, 1}},
                      {{3, 4, 5, 4, 8, 7, 8},
                       {8, 7, 7, 6, 3, 5, 5},
                       {5, 4, 3, 8, 8, 2, 3},
                       {1, 2, 3, 4, 6, 5, 1}},
                      {{3, 2, 8, 6, 8, 7, 8},
                       {8, 7, 5, 4, 3, 5, 5},
                       {5, 4, 3, 8, 8, 2, 3},
                       {1, 2, 3, 4, 6, 5, 1}},
                      {{5, 5, 4, 5, 5, 5, 5},
                       {8, 7, 8, 7, 8, 7, 8},
                       {3, 2, 8, 2, 3, 2, 3},
                       {8, 5, 6, 5, 1, 5, 1}},
                      {{3, 4, 5, 4, 8, 7, 8},
                       {8, 7, 7, 6, 3, 5, 5},
                       {5, 4, 3, 8, 8, 2, 3},
                       {1, 2, 3, 4, 6, 5, 1}},
                      {{3, 4, 5, 4, 3, 4, 3},
                       {8, 8, 8, 8, 8, 8, 8},
                       {5, 6, 5, 6, 5, 6, 5},
                       {1, 4, 3, 4, 1, 4, 1}},
                      {{4, 3, 4, 5, 4, 2, 3},
                       {8, 8, 7, 7, 6, 5, 5},
                       {6, 5, 4, 3, 8, 7, 8},
                       {4, 1, 2, 3, 4, 5, 1}},
                      {{5, 6, 5, 4, 3, 2, 3},
                       {8, 8, 7, 6, 5, 5, 5},
                       {3, 3, 3, 8, 8, 7, 8},
                       {8, 6, 3, 4, 1, 5, 1}}}
};

/* numbers in soprano can interchange 
with alto and tenor, and etc. */
/* bass always in bass */
int order_of_upper_voices[6][3] = { {0, 1, 2},
                                    {0, 2, 1},
                                    {1, 0, 2},
                                    {1, 2, 0},
                                    {2, 0, 1},
                                    {2, 1, 0}
                                  };

void roll_the_dice_baby ();

int main (void)
{
  time_t t;
  open_midfiles ();
#if GENERAL_MIDI_ON
  general_midi ();
#endif
  srand ((unsigned) time (&t));
  play (48 * 2 * 4, 152 - 16, 100, 0);	/* Handshake */
  roll_the_dice_baby ();
  close_midfiles ();
  return (1);
}

void roll_the_dice_baby (void)
{
  int j;
  int m;
  int n;
  int k;
  int i;
  int p;
  int q;
  int tempo = 40;
  int channel[8] = { 144, 145, 146, 147, 148, 148, 148, 148 };
/* need as many channel arrays as layers */
  program_number[0] = 74;
  program_number[1] = 74;
  program_number[2] = 74;
  program_number[3] = 44;
  program_number[4] = 0;
  program_number[5] = 0;
  program_number[6] = 0;
  program_number[7] = 0;
  program_setup ();
  m = rand () % (MODETYPE);
  for (p = 0; p < 4; ++p)
    {
      j = rand () % 6;		/* order of upper voices */
      order_of_upper_voices[j][3];	/* access one at a time [j][0] [j][1] [j][2] */
      n = rand () % (RHYTHMIC_PATTERNS);
      k = rand () % ALTERNATES;
      printf ("we are using the mode %d for the entire piece\n", m + 1);
      printf ("where 1 = C Scale with Eb, 2 = C Scale with Eb Ab Bb,\n");
      printf ("3 = C scale with F#, 4 = C scale with Bb\n");
      printf ("the order of voices is %d \n ", j + 1);
      printf
	("where 1 is SAT, 2 is STA, 3 is AST, 4 is ATS, 5 is TSA, 5 is TAS\n");
      printf ("this is the %d  phrase, using %d  alternate\n", p + 1, k + 1);
      printf ("this is the rhythmic variations using %d\n", n + 1);
      printf ("where 1 = WHOLE,DOTTED_WHOLE,HALF,HALF,HALF,WHOLE,WHOLE\n");
      printf ("and 2 = HALF,WHOLE,WHOLE,WHOLE,HALF,WHOLE,WHOLE\n");
      printf ("and 3 = HALF,QUARTER,QUARTER,QUARTER,QUARTER,HALF,WHOLE\n");
      printf
	("and 4 = HALF,DOTTED_QUARTER,EIGHTH,DOTTED_QUARTER,EIGHTH,HALF,WHOLE\n");
      printf ("and 5 = HALF,WHOLE,HALF,HALF,HALF,WHOLE,WHOLE\n");
      printf
	("and 6 = WHOLE,DOTTED_HALF,QUARTER,QUARTER,QUARTER,HALF,WHOLE\n");
      printf ("and 7 = QUARTER,HALF,QUARTER,QUARTER,QUARTER,HALF,WHOLE\n");
      printf ("and 8 = QUARTER,EIGHTH,EIGHTH,QUARTER,QUARTER,HALF,HALF\n");
      printf
	("and 9 = QUARTER,QUARTER,QUARTER,DOTTED_HALF,QUARTER,WHOLE,WHOLE\n");
      for (i = 0; i < PITCH_LENGTH; ++i)
	{
	  printf ("%d  %d  %d  %d\n",
		  0, 144, mode[m][0][pitch_anakreontic
				     [p][k][order_of_upper_voices[j][0]][i] -
				     1], 100);
	  printf ("%d  %d  %d  %d\n", 0, 144,
		  mode[m][1][pitch_anakreontic[p][k]
			     [order_of_upper_voices[j][1]][i] - 1], 100);
	  printf ("%d  %d  %d  %d\n", 0, 144,
		  mode[m][2][pitch_anakreontic[p][k]
			     [order_of_upper_voices[j][2]][i] - 1], 100);
	  printf ("%d  %d  %d  %d\n", 0, 144,
		  mode[m][3][pitch_anakreontic[p][k][3][i] - 1], 100);
	  printf ("%d   hold for this length\n ", rhythm_anakreontic[n][i] * tempo);	/* ,152 - 16, 100,0); */
	  printf ("%d  %d  %d  %d\n",
		  0, 144 - 16, mode[m][0][pitch_anakreontic
					  [p][k][order_of_upper_voices[j][0]]
					  [i] - 1], 0);
	  printf ("%d  %d  %d  %d\n", 0, 144 - 16,
		  mode[m][1][pitch_anakreontic[p][k]
			     [order_of_upper_voices[j][1]][i] - 1], 0);
	  printf ("%d  %d  %d  %d\n", 0, 144 - 16,
		  mode[m][2][pitch_anakreontic[p][k]
			     [order_of_upper_voices[j][2]][i] - 1], 0);
	  printf ("%d  %d  %d  %d\n", 0, 144 - 16,
		  mode[m][3][pitch_anakreontic[p][k][3][i] - 1], 0);
	}
      printf ("NOW FOR THE NEXT PHRASE\n");
      for (i = 0; i < PITCH_LENGTH; ++i)
	{
	  play (0, 144, mode[m][0][pitch_anakreontic
				   [p][k][order_of_upper_voices[j][0]][i] -
				   1], 100);
	  play (0, 145,
		mode[m][1][pitch_anakreontic[p][k]
			   [order_of_upper_voices[j][1]][i] - 1], 100);
	  play (0, 146,
		mode[m][2][pitch_anakreontic[p][k]
			   [order_of_upper_voices[j][2]][i] - 1], 100);
	  play (0, 147, mode[m][3][pitch_anakreontic[p][k][3][i] - 1], 100);
	  play ((rhythm_anakreontic[n][i]) * tempo, 152 - 16, 100, 0);
	  play (0, 144 - 16, mode[m][0][pitch_anakreontic
					[p][k][order_of_upper_voices[j][0]][i]
					- 1], 0);
	  play (0, 145 - 16,
		mode[m][1][pitch_anakreontic[p][k]
			   [order_of_upper_voices[j][1]][i] - 1], 0);
	  play (0, 146 - 16,
		mode[m][2][pitch_anakreontic[p][k]
			   [order_of_upper_voices[j][2]][i] - 1], 0);
	  play (0, 147 - 16, mode[m][3][pitch_anakreontic[p][k][3][i] - 1],
		0);
	}
    }
}

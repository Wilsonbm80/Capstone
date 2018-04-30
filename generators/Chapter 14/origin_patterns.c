/* windchimes.c */
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "convert3.h"
#define GENERAL_MIDI_ON 1
#define PROGRAM_NUMBERS_ON 1

int pattern1of3[7] =
  {83,80,77,73,69,66,63};
int pattern2of3[7] = {83,79,76,73,69,65,62};
int pattern3of3[7] = {83,79,75,72,69,65,61};
int scale_ascending[17] =  {55,58,59,61,62,63,65,66,69,72,73,75,76,77,79,80,83};
int scale_descending[17] = {83,80,79,77,76,75,73,72,69,66,65,63,62,61,59,58,55};
int scale_middle_up[9] =     {69,72,73,75,76,77,79,80,83};
int scale_middle_down[9] =   {69,66,65,63,62,61,59,58,55}; 
int scale_bottom_to_middle[9] = {55,58,59,61,62,63,65,66,69};
int scale_top_to_middle[9] = {83,80,79,77,76,75,73,72,69};

int primary_bass_triad[3] = {39,46,55};
int secondary_bass_triad[3] = {37,45,53};

int partial_pattern_secondary[7] =  {82,79,75,71,68,65,61}; 

int treble_chords1[3] = {65,68,71};
int treble_chords2[3] = {66,69,73};
int treble_chords3[3] = {67,71,75};
int treble_chords4[3] = {69,73,76};
int treble_chords5[3] = {71,74,77};
int treble_chords6[3] = {72,75,79};
int treble_chords7[3] = {73,77,81};
int treble_chords8[3] = {75,79,82};
int program_number[8];
int channel[8] = { 144, 145, 146, 147, 148, 149, 149, 149 };

  
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
#if PROGRAM_NUMBERS_ON
  program_setup ();
#endif  
  program_number[0] = 73;
  program_number[1] = 46;
  program_number[2] = 61;
  program_number[3] = 48;
  program_number[4] = 0;
  program_number[5] = 0;
  program_number[6] = 0;
  program_number[7] = 0;
  program_setup ();  
  play (48 * 2 * 4, 152 - 16, 100, 0);	/* Handshake */
  play_notes();
  close_midfiles ();
  return (1);
}

void play_notes(void)
{
 int i;
  for (i = 0; i < 3; ++i)
    play(0,147,primary_bass_triad[i],50);
  for (i = 0; i < 7; ++i)
  {
    play(0,145,pattern1of3[i],100);
    play(80,152-16,60,0);
    play(0,145-16,pattern1of3[i],0);
   }
    for (i = 0; i < 7; ++i)
  {
    play(0,145,pattern2of3[i],100);
    play(80,152-16,60,0);
    play(0,145-16,pattern2of3[i],0);
   }
    for (i = 0; i < 7; ++i)
  {
    play(0,145,pattern3of3[i],100);
    play(80,152-16,60,0);
    play(0,145-16,pattern3of3[i],0);
   }
  for (i = 0; i < 14; ++i)
  {
    play(0,145,scale_descending[i],100);
    play(20,152-16,60,0);
    play(0,145-16,scale_descending[i],0);
   } 
   
   play(100,152-16,60,0);

   for (i = 0; i < 3; ++i)
    play(0,144,treble_chords1[i],70); 
   play(200,152-16,60,0);
   for (i = 0; i < 3; ++i)
    play(0,144-16,treble_chords1[i],0);
     
    for (i = 0; i < 3; ++i)
    play(0,144,treble_chords2[i],70); 
   play(200,152-16,60,0);
   for (i = 0; i < 3; ++i)
    play(0,144-16,treble_chords2[i],0); 

    for (i = 0; i < 3; ++i)
    play(0,144,treble_chords3[i],70); 
   play(200,152-16,60,0);
   for (i = 0; i < 3; ++i)
    play(0,144-16,treble_chords3[i],0);
  
     for (i = 0; i < 3; ++i)
    play(0,144,treble_chords4[i],70); 
   play(200,152-16,60,0);
   for (i = 0; i < 3; ++i)
    play(0,144-16,treble_chords4[i],0);

     for (i = 0; i < 3; ++i)
    play(0,144,treble_chords5[i],70); 
   play(200,152-16,60,0);
   for (i = 0; i < 3; ++i)
    play(0,144-16,treble_chords5[i],0);

     for (i = 0; i < 3; ++i)
    play(0,144,treble_chords6[i],70); 
   play(200,152-16,60,0);
   for (i = 0; i < 3; ++i)
    play(0,144-16,treble_chords6[i],0);


     for (i = 0; i < 3; ++i)
    play(0,144,treble_chords7[i],70); 
   play(200,152-16,60,0);
   for (i = 0; i < 3; ++i)
    play(0,144-16,treble_chords7[i],0);

     for (i = 0; i < 3; ++i)
    play(0,144,treble_chords8[i],80); 
   play(200,152-16,60,0);
   for (i = 0; i < 3; ++i)
    play(0,144-16,treble_chords8[i],0);

  for (i = 0; i < 3; ++i)
    play(0,147-16,primary_bass_triad[i],0);    


  
   for (i = 0; i < 3; ++i)
    play(0,147,secondary_bass_triad[i],50);

    for (i = 0; i < 7; ++i)
  {
    play(0,145,partial_pattern_secondary[i],100);
    play(80,152-16,60,0);
    play(0,145-16,partial_pattern_secondary[i],0);
   }

 for (i = 0; i < 3; ++i)
    play(0,147-16,secondary_bass_triad[i],0);

 for (i = 0; i < 3; ++i)
    play(0,147,primary_bass_triad[i],50);

  for (i = 0; i < 3; ++i)
    play(0,144,treble_chords8[i],80); 
   play(400,152-16,60,0);
 for (i = 0; i < 3; ++i)
    play(0,144-16,treble_chords8[i],0);
  
   for (i = 0; i < 3; ++i)
    play(0,147-16,primary_bass_triad[i],0);

  for (i = 0; i < 17; ++ i)
    {
     play(0,145,scale_ascending[i],90);
     play(0,144,scale_descending[i],90);
     play(20,152-16,60,0);
     play(0,145-16,scale_ascending[i],0);
     play(0,144-16,scale_descending[i],0); 
    } 

for (i = 0; i < 9; ++ i)
    {
     play(0,145,scale_middle_up[i],90);
     play(0,144,scale_middle_down[i],90);
     play(20,152-16,60,0);
     play(0,145-16,scale_middle_up[i],0);
     play(0,144-16,scale_middle_down[i],0);
     } 
for (i = 0; i < 9; ++ i)
    {
     play(0,145,scale_bottom_to_middle[i],90);
     play(0,144,scale_top_to_middle[i],90); 
     play(20,152-16,60,0);
     play(0,145-16,scale_bottom_to_middle[i],0);
     play(0,144-16,scale_top_to_middle[i],0);
    } 
for (i = 0; i < 9; ++ i)
    {
    play(0,145,scale_middle_up[i],90);
    play(0,144,scale_middle_down[i],90);
    play(0,145,scale_bottom_to_middle[i],90);
    play(0,144,scale_top_to_middle[i],90);
    play(20,152-16,60,0);
    play(0,145-16,scale_middle_up[i],0);
    play(0,144-16,scale_middle_down[i],0);
    play(0,145-16,scale_bottom_to_middle[i],0);
    play(0,144-16,scale_top_to_middle[i],0);
    } 

    for (i = 0; i < 3; ++i)
      play(0,147,primary_bass_triad[i],50);

    play(0,144,pattern1of3[4],80);
    play(60,152-16,60,0);
    play(0,144-16,pattern1of3[4],0);
    
    play(0,144,pattern1of3[3],80);
    play(60,152-16,60,0);
    play(0,144-16,pattern1of3[3],0);

    play(0,144,pattern1of3[2],80);
    play(60,152-16,60,0);
    play(0,144-16,pattern1of3[2],0); 

    play(0,144,pattern1of3[1],80);
    play(60,152-16,60,0);
    play(0,144-16,pattern1of3[1],0);

    play(0,144,pattern1of3[0],80);
    play(60,152-16,60,0);
    play(0,144-16,pattern1of3[0],0); 

    play(300,152-16,60,0);

     for (i = 0; i < 3; ++i)
      play(0,147-16,primary_bass_triad[i],0);


 


  
 
}


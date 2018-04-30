#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "convert3.h"
#define GENERAL_MIDI_ON 1
#define PROGRAM_NUMBERS_ON 1


int prime[12]; 
int retrograde[12];
int retrogradeinversion[12];
int inversion[12];

int prime_rhythm[12];
int retrograde_rhythm[12];
int retrogradeinversion_rhythm[12];
int inversion_rhythm[12];  
int prime_full[78];
int inversion_full[78];
int retrograde_full[78];
int retrogradeinversion_full[78];



int soprano_active;
int alto_active;
int tenor_active;
int bass_active;
int rhythm_counter;


int channel[8] = { 144, 145, 146, 147, 148, 149, 150, 151 };
int transposefactor1;
int transposefactor2;
int transposefactor3;
int transposefactor4;
int old_p;
int new_p;
int old_r;
int new_r;
int old_i;
int new_i;
int old_ri;
int new_ri;

int transposefactor1;
int transposefactor2;
int transposefactor3;
int transposefactor4; 


// kirk > picard 

void play_procedure(void);
void make_random_primepitch_row(void);
void make_random_primerhythm_row(void);
void make_retrograde(void);
void make_inversion(void);
void make_retrogradeinversion(void); 
void make_retrograde_rhythm(void);
void make_inversion_rhythm(void); 
void make_retrogradeinversion_rhythm(void); 
void show_rhythm(void);
void show_pitches(void);
void make_prime_full(void);
void make_retrograde_full(void);
void make_inversion_full(void);
void make_retrogradeinversion_full(void);



int main (void)
{
  int i;
  time_t t;
  open_midfiles ();
#if GENERAL_MIDI_ON
  general_midi ();
#endif
  srand ((unsigned) time (&t));
  play (48 * 2 * 4, 152 - 16, 100, 0);	/* Handshake */
  program_number[0] = 73;	//flute 
  program_number[1] = 14;	//tubular bells
  program_number[2] = 71;	//clarinet
  program_number[3] = 42;	//cello 
  program_number[4] = 0;
  program_number[5] = 0;
  program_number[6] = 0;
  program_number[7] = 0;
  program_setup ();
  make_random_primepitch_row();
  make_random_primerhythm_row();
  make_retrograde();
  make_inversion();
  make_retrogradeinversion();
  make_retrograde_rhythm();
  make_inversion_rhythm();
  make_retrogradeinversion_rhythm();
  
  make_prime_full();
  make_retrograde_full();
  make_inversion_full();
  make_retrogradeinversion_full();

  
// show_rhythm();
// show_pitches();
  play_procedure(); 
  close_midfiles();
  return (1);
}







void make_random_primepitch_row(void)
 {
  int number;
  int counter;
  int success;
  int i;
    
  number = rand()%12;           
  counter = 0;
  prime[counter] = number;
  ++counter;
  
  do
  { 
   success = 1;
   number =  rand()%12;
   for (i = 0; i < counter; ++i)
     {
      if (prime[i] == number)
         {
          success = 0;
          }
      }  
      if(success == 1)
        {
         prime[counter] = number;
         counter++;
        }
  }while(success == 0 || counter < 12);

  //  for (i = 0; i < 12; ++i)
  //    printf("%d ",prime[i]);   
            
}



void make_retrograde(void)
 {
  int i;
  for (i = 0; i < 12; ++i)
   retrograde[i] = prime[11-i];
  }

void make_inversion(void)
  {
   int i;
   for (i = 0; i < 12; ++i)
    inversion[i] = 12 - prime[i];
   }

void make_retrogradeinversion(void)  
  {
   int i;
   for (i = 0; i < 12; ++i)
     retrogradeinversion[i] = inversion[11-i];
   }

void make_retrograde_rhythm(void)
 {
  int i;
  for (i = 0; i < 12; ++i)
   retrograde_rhythm[i] =  prime_rhythm[11 - i];
  }

void make_inversion_rhythm(void)
  {
   int i;
   for (i = 0; i < 12; ++i)
    inversion_rhythm[i] = 13 - prime_rhythm[i];
   }

void make_retrogradeinversion_rhythm(void)  
  {
   int i;
   for (i = 0; i < 12; ++i)
     retrogradeinversion_rhythm[i] = inversion_rhythm[11 - i];
   }



void make_random_primerhythm_row(void)       
{
  int number;
  int counter;
  int success;
  int i;
  int prime_rhythm1[12]; 
  number = rand()%12;           
  counter = 0;
  prime_rhythm[counter] = number;
  ++counter;
  do
    { 
     success = 1;
     number =  rand()%12;
     for (i = 0; i < counter; ++i)
        {
          if (prime_rhythm[i] == number)
           {
            success = 0;
           }
        }  
    if(success == 1)
      {
       prime_rhythm[counter] = number;
       counter++;
      }
 }while(success == 0 || counter < 12);
    
    for (i = 0; i < 12; ++i)
     {
      prime_rhythm1[i] = prime_rhythm[i]+1;
      prime_rhythm[i] = prime_rhythm1[i];
     }        
}
       
void  show_rhythm(void)
  {
   int i;
   printf("Prime Rhythm\n");
   for (i = 0; i < 12; ++i)
    printf("%d ",prime_rhythm[i]);
   printf("\n"); 
   printf("Inversion Rhythm\n");
   for (i = 0; i < 12; ++i)
    printf("%d ",inversion_rhythm[i]);
   printf("\n");  
   printf("Retrograde Rhythm\n");
   for (i = 0; i < 12; ++i)
    printf("%d ",retrograde_rhythm[i]);
   printf("\n");  
     
   printf("Retrograde_Inversion Rhythm\n");
   for (i = 0; i < 12; ++i)
    printf("%d ",retrogradeinversion_rhythm[i]);
   printf("\n");       
  }
 
void  show_pitches(void)
  {
   int i;

   printf("Prime Pitches\n");
   for (i = 0; i < 12; ++i)
    printf("%d ",prime[i]);
   printf("\n"); 
   printf("Inversion Pitches\n");
   for (i = 0; i < 12; ++i)
    printf("%d ",inversion[i]);
   printf("\n");     
   printf("Retrograde Pitches\n");
   for (i = 0; i < 12; ++i)
    printf("%d ",retrograde[i]);
   printf("\n");       
   printf("Retrograde_Inversion Pitches\n");
   for (i = 0; i < 12; ++i)
    printf("%d ",retrogradeinversion[i]);
   printf("\n");      
  }



void make_prime_full(void)
 {
  int i,j;
  int pitch;
  int number_of_times;
  int marker_end = 0;
  int marker_start = 0; 
  for (i = 0; i < 12; ++i)
   {
     number_of_times = prime_rhythm[i];
     pitch = prime[i];
     marker_end = marker_end + number_of_times;
    
     for (j = marker_start; j < marker_end; ++j)
       prime_full[j] = pitch;
     marker_start = marker_end;
    }
 /*  printf("MAKE_PRIME_FULL = \n");
   for (i = 0; i < 78; ++i)
      printf("%d  ",prime_full[i]); */
  }


void make_retrograde_full(void)
 {
  int i,j;
  int pitch;
  int number_of_times;
  int marker_end = 0;
  int marker_start = 0; 
  for (i = 0; i < 12; ++i)
   {
     number_of_times = retrograde_rhythm[i];
     pitch = retrograde[i];
     marker_end = marker_end + number_of_times;
    
     for (j = marker_start; j < marker_end; ++j)
       retrograde_full[j] = pitch;
     marker_start = marker_end;
    }
 /*  printf("MAKE_RETROGRADE_FULL = \n");
   for (i = 0; i < 78; ++i)
      printf("%d  ",retrograde_full[i]); */
  }


void make_inversion_full(void)
 {
  int i,j;
  int pitch;
  int number_of_times;
  int marker_end = 0;
  int marker_start = 0; 
  for (i = 0; i < 12; ++i)
   {
     number_of_times = inversion_rhythm[i];
     pitch = inversion[i];
     marker_end = marker_end + number_of_times;
    
     for (j = marker_start; j < marker_end; ++j)
       inversion_full[j] = pitch;
     marker_start = marker_end;
    }
 /*   printf("MAKE_INVERSION_FULL = \n");
   for (i = 0; i < 78; ++i)
      printf("%d  ",inversion_full[i]); */
  }


void make_retrogradeinversion_full(void)
 {
  int i,j;
  int pitch;
  int number_of_times;
  int marker_end = 0;
  int marker_start = 0; 
  for (i = 0; i < 12; ++i)
   {
     number_of_times = retrogradeinversion_rhythm[i];
     pitch = retrogradeinversion[i];
     marker_end = marker_end + number_of_times;
    
     for (j = marker_start; j < marker_end; ++j)
       retrogradeinversion_full[j] = pitch;
     marker_start = marker_end;
    }
    /*  printf("MAKE_RETROGRADEINVERSION_FULL = \n");
          for (i = 0; i < 78; ++i)
      printf("%d  ",retrogradeinversion_full[i]); */
  }






void play_procedure(void)
{
 
  int i,j; 
for (j = 0; j < 20; ++j)
 {
  transposefactor1 = 60 +  (rand () % 12) + 6;
  transposefactor2 = 55 + (rand () % 12) + 6;
  transposefactor3 = 45 + (rand () % 12) + 6;
  transposefactor4 = 35 + (rand () % 12) + 6; 
   
     i = 0;
     new_p = prime_full[i];
     play(0,144,new_p+transposefactor1,127);
     new_r = retrograde_full[i];
     play(0,145,new_r+transposefactor2,127);
     new_i = inversion_full[i];  
     play(0,146,new_i+transposefactor3,127);
     new_ri = retrogradeinversion_full[i];
     play(0,147,new_ri+transposefactor4,127);
     play (60, 152 - 16, 100, 0);
     old_p = new_p; 
     old_r = new_r;    
     old_i = new_i;
     old_ri = new_ri; 
     
     for (i = 1; i < 78; ++i) 
      {
        new_p = prime_full[i];
        new_r = retrograde_full[i];
        new_i = inversion_full[i];
        new_ri = retrogradeinversion_full[i];

        if (new_p != old_p)
        {
	      play (0, 144 - 16, old_p + transposefactor1, 0);
	      play (0, 144, new_p + transposefactor1, 127);
	 }
	  if (new_r != old_r)
	  {
	      play (0, 145 - 16, old_r + transposefactor2, 0);
	      play (0, 145, new_r + transposefactor2, 127);
	   }
	  if (new_i != old_i)
	   {
	      play (0, 146 - 16, old_i + transposefactor3, 0);
	      play (0, 146, new_i + transposefactor3, 127);
	   }
	  if (new_ri != old_ri)
	   {
	      play (0, 147 - 16, old_ri + transposefactor4, 0);
	      play (0, 147, new_ri + transposefactor4, 127);
	    }
          play (60, 152 - 16, 100, 0);
        old_p = new_p; 
        old_r = new_r;    
        old_i = new_i;
        old_ri = new_ri;
        }
      play (0, 144 - 16, old_p + transposefactor1, 0);
      play (0, 145 - 16, old_r + transposefactor2, 0);
      play (0, 146 - 16, old_i + transposefactor3, 0);
      play (0, 147 - 16, old_ri + transposefactor4, 0);
   }
} 



























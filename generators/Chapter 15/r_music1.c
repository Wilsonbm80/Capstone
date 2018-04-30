/* r_music1.c */
/* randoms*it.c  written on Dec 31, 2011 * /
/* totally? random music, in honor of John Cage, in three movements: first movement varied duration; second movement slow duration and soft; thrid movement fast and loud */
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "convert3.h"

int channel[8] = { 144, 145, 146, 147, 148, 149, 150, 151 };

/* need as many channel arrays as layers */
int volume[7];
int pitch[7];
int duration[7];
int counter[7];
int program_number[8];
void play_notes (void);
void make_new_voice (int i);
void make_new_voice1 (int i);
void make_new_voice2 (int i);
void set_up_program_number (void);

int main (void)
{
  int i;
  time_t t;
  open_midfiles ();
  srand ((unsigned) time (&t));
  open_midfiles ();
  general_midi ();
  play (48 * 2 * 4, 152 - 16, 100, 0);	/* Handshake */
  set_up_program_number ();
  for (i = 0; i < 7; ++i)
    make_new_voice (i);
  play_notes ();
  close_midfiles ();
  return (1);
}

void set_up_program_number (void)
{
  int i;
  for (i = 0; i < 8; ++i)
    program_number[i] = rand () % (126) + 1;
  program_setup ();
}

void play_notes ()
{
  int j, i;
  for (j = 0; j < 12000; ++j)
    {
      for (i = 0; i < 7; ++i)
	if (counter[i] == 0)
	  play (0, channel[i], pitch[i], volume[i]);
      play (1, 152 - 16, 100, 0);	/* wait */
      for (i = 0; i < 7; ++i)
	{
	  ++counter[i];
	  if (counter[i] == duration[i])
	    {
	      play (0, channel[i] - 16, pitch[i], 0);
	      make_new_voice (i);
	    }
	}
    }
  for (i = 0; i < 7; ++i)
    play (0, channel[i] - 16, pitch[i], volume[i]);
  for (i = 0; i < 7; ++i)
    make_new_voice1 (i);
  for (j = 0; j < 12000; ++j)
    {
      for (i = 0; i < 7; ++i)
	if (counter[i] == 0)
	  play (0, channel[i], pitch[i], volume[i]);
      play (1, 152 - 16, 100, 0);	/* wait */
      for (i = 0; i < 7; ++i)
	{
	  ++counter[i];
	  if (counter[i] == duration[i])
	    {
	      play (0, channel[i] - 16, pitch[i], 0);
	      make_new_voice1 (i);
	    }
	}
    }
  for (i = 0; i < 7; ++i)
    play (0, channel[i] - 16, pitch[i], volume[i]);
  for (i = 0; i < 7; ++i)
    make_new_voice2 (i);
  for (j = 0; j < 12000; ++j)
    {
      for (i = 0; i < 7; ++i)
	if (counter[i] == 0)
	  play (0, channel[i], pitch[i], volume[i]);
      play (1, 152 - 16, 100, 0);	/* wait */
      for (i = 0; i < 7; ++i)
	{
	  ++counter[i];
	  if (counter[i] == duration[i])
	    {
	      play (0, channel[i] - 16, pitch[i], 0);
	      make_new_voice2 (i);
	    }
	}
    }
  for (i = 0; i < 7; ++i)
    play (0, channel[i] - 16, pitch[i], volume[i]);
}

void make_new_voice (int i)
{
  if (i == 0)
    {
      volume[i] = rand () % (126) + 1;
      pitch[i] = rand () % (126) + 1;
      duration[i] = rand () % (3000) + 1;
      program_number[i] = rand () % (126) + 1;
      program_setup ();
      counter[i] = 0;
    }
  else if (i == 1)
    {
      volume[i] = rand () % (126) + 1;
      pitch[i] = rand () % (126) + 1;
      duration[i] = rand () % (500) + 1;
      program_number[i] = rand () % (126) + 1;
      program_setup ();
      counter[i] = 0;
    }
  else if (i == 2)
    {
      volume[i] = rand () % (126) + 1;
      pitch[i] = rand () % (126) + 1;
      duration[i] = rand () % (2000) + 1;
      program_number[i] = rand () % (126) + 1;
      program_setup ();
      counter[i] = 0;
    }
  else if (i == 3)
    {
      volume[i] = rand () % (126) + 1;
      pitch[i] = rand () % (126) + 1;
      duration[i] = rand () % (750) + 1;
      program_number[i] = rand () % (126) + 1;
      program_setup ();
      counter[i] = 0;
    }
  else if (i == 4)
    {
      volume[i] = rand () % (126) + 1;
      pitch[i] = rand () % (126) + 1;
      duration[i] = rand () % (40) + 1;
      program_number[i] = rand () % (126) + 1;
      program_setup ();
      counter[i] = 0;
    }
  else if (i == 5)
    {
      volume[i] = rand () % (126) + 1;
      pitch[i] = rand () % (126) + 1;
      duration[i] = rand () % (10) + 1;
      program_number[i] = rand () % (126) + 1;
      program_setup ();
      counter[i] = 0;
    }
  else if (i == 6)
    {
      volume[i] = rand () % (126) + 1;
      pitch[i] = rand () % (126) + 1;
      duration[i] = rand () % (5) + 1;
      program_number[i] = rand () % (126) + 1;
      program_setup ();
      counter[i] = 0;
    }
}

void make_new_voice1 (int i)
{
  if (i == 0)
    {
      volume[i] = 60;
      pitch[i] = rand () % (126) + 1;
      duration[i] = 4000;
      program_number[i] = rand () % (126) + 1;
      program_setup ();
      counter[i] = 0;
    }
  else if (i == 1)
    {
      volume[i] = 50;
      pitch[i] = rand () % (126) + 1;
      duration[i] = 5009;
      program_number[i] = rand () % (126) + 1;
      program_setup ();
      counter[i] = 0;
    }
  else if (i == 2)
    {
      volume[i] = 40;
      pitch[i] = rand () % (126) + 1;
      duration[i] = 6000;
      program_number[i] = rand () % (126) + 1;
      program_setup ();
      counter[i] = 0;
    }
  else if (i == 3)
    {
      volume[i] = 50;
      pitch[i] = rand () % (126) + 1;
      duration[i] = 8000;
      program_number[i] = rand () % (126) + 1;
      program_setup ();
      counter[i] = 0;
    }
  else if (i == 4)
    {
      volume[i] = 60;
      pitch[i] = rand () % (126) + 1;
      duration[i] = 70;
      program_number[i] = rand () % (126) + 1;
      program_setup ();
      counter[i] = 0;
    }
  else if (i == 5)
    {
      volume[i] = 40;
      pitch[i] = rand () % (126) + 1;
      duration[i] = 699;
      program_number[i] = rand () % (126) + 1;
      program_setup ();
      counter[i] = 0;
    }
  else if (i == 6)
    {
      volume[i] = 30;
      pitch[i] = rand () % (126) + 1;
      duration[i] = 1000;
      program_number[i] = rand () % (126) + 1;
      program_setup ();
      counter[i] = 0;
    }
}

void make_new_voice2 (int i)
{
  if (i == 0)
    {
      volume[i] = 126;
      pitch[i] = rand () % (126) + 1;
      duration[i] = rand () % (25) + 1;
      program_number[i] = rand () % (126) + 1;
      program_setup ();
      counter[i] = 0;
    }
  else if (i == 1)
    {
      volume[i] = 126;
      pitch[i] = rand () % (126) + 1;
      duration[i] = rand () % (50) + 1;
      program_number[i] = rand () % (126) + 1;
      program_setup ();
      counter[i] = 0;
    }
  else if (i == 2)
    {
      volume[i] = 126;
      pitch[i] = rand () % (126) + 1;
      duration[i] = rand () % (10) + 1;
      program_number[i] = rand () % (126) + 1;
      program_setup ();
      counter[i] = 0;
    }
  else if (i == 3)
    {
      volume[i] = 126;
      pitch[i] = rand () % (126) + 1;
      duration[i] = rand () % (10) + 1;
      program_number[i] = rand () % (126) + 1;
      program_setup ();
      counter[i] = 0;
    }
  else if (i == 4)
    {
      volume[i] = 126;
      pitch[i] = rand () % (126) + 1;
      duration[i] = rand () % (15) + 1;
      program_number[i] = rand () % (126) + 1;
      program_setup ();
      counter[i] = 0;
    }
  else if (i == 5)
    {
      volume[i] = 126;
      pitch[i] = rand () % (126) + 1;
      duration[i] = rand () % (10) + 1;
      program_number[i] = rand () % (126) + 1;
      program_setup ();
      counter[i] = 0;
    }
  else if (i == 6)
    {
      volume[i] = 126;
      pitch[i] = rand () % (126) + 1;
      duration[i] = rand () % (15) + 1;
      program_number[i] = rand () % (126) + 1;
      program_setup ();
      counter[i] = 0;
    }
}

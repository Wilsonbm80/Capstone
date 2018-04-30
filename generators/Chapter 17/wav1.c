//wav1.c
#include <stdio.h>       /* in Ubuntu 12.04, compile by gcc wav1.c -o wav -lm */ 
#include <stdlib.h>      /* then execute program by ./wav */ 
#include <math.h>        /* this will make a program that demonstrates how to combine frequencies of sine tones */ 
                         /* you may comment out some and just have one frequencies, or change or add more */

// Unity > KDE > Gnome
FILE *fp2; FILE *fp1;
void convertlong(unsigned long int number, int byte[4]);
void play(signed int v);
void change_to_wav_format(void);
unsigned long int place = 0UL;
int main(void)
 {
  double x;
  double x1, x2, x3;
  int i1,i2,i3;/* max is 32767, min is -32768 */
  int j;
  fp1 =  fopen("tempfile","wb");
/* produces approximately low D, next A (highter) next ~C (+octave) */

  for (j = 0; j < 1000; ++j)                     /* this gives the length of the wave, but the increments below with also change that as well as frequency */     
    for (x = 0.00; x < (3.14159*2); x = x + .01) /* one complete wave form, detailed at increments of .01 */
    {
     x1 = (sin(x*2))*2000;                 /* 2 changes the frequency and 10000 changes the amplitude */
     if (x1 < 32767.0 && x1 > -32768.0)
       i1 = (int)(x1);
     else i1 = (int)(0);
 //    i1 = 0; 
          x2 = (sin(x*3))*10000;           /* same */
     if (x2 < 32767.0 && x2 > -32768.0)
       i2 = (int)(x2);
     else i2 = (int)(0); 
 //     i2 = 0;
     x3 = (sin(x*7))*10000; 
     if (x3 < 32767.0 && x3 > -32768.0)    /* same */
       i3 = (int)(x3);
     else i3 = (int)(0);
 //       i3 = 0;   
     if ((i1 + i2 + i3) < 32767 && (i1 + i2 + i3) > -32768)
       {
        printf(" %d ",i1+i2+i3);
        play(i1 + i2 + i3);                   /* add for the resultant wave */
       }
     }
     
fclose(fp1);
change_to_wav_format();
return (1);
}



void play(signed int v)
  {

   unsigned short int temp1,temp2;
   signed int number = v;

   temp1 = (short int) number;
   temp1 = (temp1 >> 8);
   temp2 = (short int) number;
   temp2 = (temp2 << 8);
   temp2 = (temp2 >> 8);
   fwrite(&temp2,1,1,fp1);
   ++place;
   fwrite(&temp1,1,1,fp1);
   ++place;
   }

void change_to_wav_format(void)
  {
   int temp;
   int i;
   int byte[4];
   fp2 = fopen("wave.wav","wb");
   temp = 82; /* R */
   fwrite(&temp,1,1,fp2);
   temp = 73; /* I */
   fwrite(&temp,1,1,fp2);
   temp = 70; /* F */
   fwrite(&temp,1,1,fp2);
   temp = 70; /* F */
   fwrite(&temp,1,1,fp2);
   convertlong(place + 36,byte);
   fwrite(&byte[3],1,1,fp2);
   fwrite(&byte[2],1,1,fp2);
   fwrite(&byte[1],1,1,fp2);
   fwrite(&byte[0],1,1,fp2);
   temp = 87;
   fwrite(&temp,1,1,fp2); /* W */
   temp = 65;
   fwrite(&temp,1,1,fp2); /* A */
   temp = 86;
   fwrite(&temp,1,1,fp2); /* V */
   temp = 69;
   fwrite(&temp,1,1,fp2); /* E */
   temp = 102;
   fwrite(&temp,1,1,fp2); /* f */
   temp = 109;
   fwrite(&temp,1,1,fp2); /* m */
   temp = 116;
   fwrite(&temp,1,1,fp2); /* t */
   temp = 32;
   fwrite(&temp,1,1,fp2);  /*   */
   temp = 16;
   fwrite(&temp,1,1,fp2); /* length of bytes to follow written backwards  */
   temp = 0;
   fwrite(&temp,1,1,fp2);
   temp = 0;
   fwrite(&temp,1,1,fp2);
   temp = 0;
   fwrite(&temp,1,1,fp2);
   temp = 1;
   fwrite(&temp,1,1,fp2);  /* mono Wav (written backwards */
   temp = 0;
   fwrite(&temp,1,1,fp2);
   temp = 1;
   fwrite(&temp,1,1,fp2);  /* one channel used (written backwards */
   temp = 0;
   fwrite(&temp,1,1,fp2);
   temp = 0x44; 
   fwrite(&temp,1,1,fp2); /* sample rate */
   temp =  0xAC; 
   fwrite(&temp,1,1,fp2);
   temp = 0;
   fwrite(&temp,1,1,fp2);
   temp = 0;
   fwrite(&temp,1,1,fp2);
   temp = 0x88;
   fwrite(&temp,1,1,fp2); /* bytes/second */
   temp = 0x58;
   fwrite(&temp,1,1,fp2);
   temp = 0x01;
   fwrite(&temp,1,1,fp2);
   temp = 0x00;
   fwrite(&temp,1,1,fp2);
   temp = 2;
   fwrite(&temp,1,1,fp2); /* bytes per sample */
   temp = 0;
   fwrite(&temp,1,1,fp2);
   temp = 16;
   fwrite(&temp,1,1,fp2); /* bits per sample */
   temp = 0;
   fwrite(&temp,1,1,fp2);
   temp = 100;
   fwrite(&temp,1,1,fp2); /* d */
   temp = 97;
   fwrite(&temp,1,1,fp2);  /* a */
   temp = 116;
   fwrite(&temp,1,1,fp2); /* t */
   temp = 97;
   fwrite(&temp,1,1,fp2);  /* a */
   convertlong(place,byte);
   fwrite(&byte[3],1,1,fp2);
   fwrite(&byte[2],1,1,fp2);
   fwrite(&byte[1],1,1,fp2);
   fwrite(&byte[0],1,1,fp2);
   fp1 = fopen("tempfile","rb");
   do
    {
     fread(&i,1,1,fp1);
     if (!feof(fp1)) fwrite(&i,1,1,fp2);
    } while (!feof(fp1));
  fclose(fp1);
  fclose(fp2);
 }


void  convertlong(unsigned long int number, int byte[4])
 {
  unsigned long int temp;
  temp = number;
  temp = temp >> 8*3;
  byte[0] = (unsigned short int)temp;

  temp = number;
  temp =  temp << 8;
  temp = temp >> 8*3;
  byte[1] = (unsigned short int)temp;

  temp = number;
  temp = temp << 8*2;
  temp = temp >> 8*3;
  byte[2] = (unsigned short int)temp;

  temp = number;
  temp = temp << 8*3;
  temp = temp >> 8*3;
  byte[3] = (unsigned short int)temp;
 }


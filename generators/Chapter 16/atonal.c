//atonal.c
#include <stdio.h>
#include <stdlib.h>


void loadnotes(int notes[13]);
void bubblesort(int notes[13]);
void loserepeats(int notes[13]);
void primeform(int notes[13]);
void copy(int notes[13], int temp[13]);
void permutation(int notes[13],int temp[13]);
int  compare_prime_inversion(int prime[13],int inversion[13]);
void requirement1(int temp[13],int temp1[13],int best[13], int numnotes);
void requirement2(int best[13],int temp1[13], int numnotes);
void comparenotes(int notes[13]);
void makeinversion(int notes[13],int inversion[13]);

void main(void)
	{

    int notes[13],inversion[13];
	 int i,answer;
         char answer2[20];
	 loadnotes(notes);
	 makeinversion(notes,inversion);
	 system("clear");
	 printf("ORIGINAL NOTES = ");
		for (i = 0; i < notes[12]; ++i)
		  printf("%d ",notes[i]);
	 printf(" INVERSION OF ORIGINAL NOTES = ");
	  for (i = 0; i < inversion[12]; ++i)
		  printf("%d ",inversion[i]);
	 printf("\n");
	 bubblesort(notes);
	 bubblesort(inversion);
	 printf("ASCENDING ORDER = ");
	 for (i = 0; i < notes[12]; ++i)
	  printf("%d ",notes[i]);
	 printf(" ASCENDING ORDER OF INVERSION = ");
	 for (i = 0; i < inversion[12]; ++i)
		printf("%d ",inversion[i]);
	 printf("\n");
	 loserepeats(notes);
	 loserepeats(inversion);
	 printf("WITH NO REPEATS OF PRIME = ");
	 for (i = 0; i < notes[12]; ++i)
		printf("%d ",notes[i]);
	 printf("  WITH NO REPEATS OF INVERSION = ");
	 for (i = 0; i < inversion[12]; ++i)
		printf("%d ",inversion[i]);
	 printf("\n");
	 primeform(notes);
	 primeform(inversion);
	 printf("PRIME ORDER = ");
	 for (i = 0; i < notes[12]; ++i)
		printf("%d ",notes[i]);
	 printf(" PRIME ORDER OF INVERSION = ");
	 for (i = 0; i < inversion[12]; ++i)
		printf("%d ",inversion[i]);
	 printf("\n PRIME PERMUTATIONS = ");
	 comparenotes(notes);
	 printf("\n INVERSION PERMUTATIONS = ");
	 comparenotes(inversion);
	 printf("\n\n");
	 answer = compare_prime_inversion(notes,inversion);
	 if (answer == -1)
		{
		 for (i = 0; i < inversion[12]; ++i)
			printf("%d ",inversion[i]);
		}
		 else
		{
		 for (i = 0; i < notes[12]; ++i)
			printf("%d ",notes[i]);
		}
         //gets(answer2);
         //printf("Press Enter\n");
 }



void loadnotes(int notes[13])
  {
	char answer[80], answer1[80];
	int counter = 0;
	notes[12] = 0;
	do {
		 system("clear");
                 printf("if DONE enter 'z' and <enter. Warning-no error checks-garbage in garbage out!\n");
		 printf("else Enter letter name lower case (without # or b's) of note %d and <enter>\n",counter+1);
		 
		 gets(answer);
		 switch(answer[0])
		 {
		  case 'c':
			notes[counter] = 0;
			break;
		  case 'd':
			 notes[counter] = 2;
			 break;
		  case 'e':
			 notes[counter] = 4;
			 break;
		  case 'f':
			 notes[counter] = 5;
			 break;
		  case 'g':
			 notes[counter] = 7;
			 break;
		  case 'a':
			 notes[counter] = 9;
			 break;
		  case 'b':
			 notes[counter] = 11;
			 break;
		  case 'z':
			 notes[12] = counter;
          break;
			  }
			if (answer[0] != 'z')
		  {
			printf("\n\n");
			printf("Now enter whether the note %c is sharp, flat, or natural\n",answer[0]);
			printf("Enter 's', 'f', or 'n' for natural and then <enter>'\n");
			gets(answer1);
			switch(answer1[0])
			  {
				case 's':
				 ++notes[counter];
				 if (notes[counter] == 12) notes[counter] = 0;
				 break;
				case 'f':
				  --notes[counter];
				  if (notes[counter] == -1) notes[counter] = 11;
				  break;
				case 'n':
				 break;
				 }
				 ++counter;
			 }

			  }while (counter<12 && answer[0] != 'z');
			notes[12] = counter;
	}


void bubblesort(int notes[13])
  {
	int i,j,temp;
	for (i = 0; i < notes[12] - 1; ++i)
	  for (j = i + 1; j < notes[12]; ++j)
		 if (notes[i] > notes[j])
		 {
		  temp = notes[i];
		  notes[i] = notes[j];
		  notes[j] = temp;
		 }
  }


void  loserepeats(int notes[13])
	 {
	  int i;
	  int counter;
	  if (notes[12] > 1)
		  {
			counter = 1;
			for (i = 1; i < notes[12]; ++i)
			  if (notes[i] != notes[counter-1])
		{
		 notes[counter] = notes[i];
		 ++counter;
	  }
		 }
	  else counter = notes[12];
	notes[12] = counter;
	}

void	primeform(int notes[13])
	  {
		int i;
		int trans;
		trans = notes[0];
		for (i = 0; i < notes[12]; ++i)
		  {
			notes[i] = notes[i] - trans;
			if (notes[i] < 0) notes[i] = notes[i] + 12;
			}
	  }


void  copy(int notes[13], int temp[13])
	{
	 int i;
	 for (i = 0; i < 13; ++i)
	  temp[i] = notes[i];
	 }



void permutation(int notes[13], int temp[13])
  {
	int i;
	if (notes[12] > 1)
		 {
			for (i = 0; i < notes[12]-1; ++i)
			  temp[i] = notes[i+1];
			temp[notes[12]-1] = notes[0];
		  }
			else temp[0] = notes[0];
		 temp[12] = notes[12];
  }

int compare_prime_inversion(int prime[13], int inversion[13])
	{
	  int i = 1;
	  int success = 0;
	  int numnotes = prime[12];
	  int best;
	  if (prime[numnotes-1]-prime[0]>inversion[numnotes-1]-inversion[0])
		 {
		  printf("INVERSION is the best\n");
		  best = -1;
		 }
	  else if (prime[numnotes-1] - prime[0] ==
				  inversion[numnotes-1]-inversion[0])
				  {
				  while (success == 0 && i < numnotes - 1)
					{
					 if (prime[i] - prime[0] > inversion[i] - inversion[0])
					  {
						success = 1;
						printf("INVERSION is the best\n");
					best = -1;
						  }
							++i;
				}
			 if (success == 0)
			  {
				printf("ORGINAL is the best\n");
				best = 1;
				}
			 }
			else
				{
				 printf("ORIGINAL is the best\n");
				 best = 1;
				 }
			return(best);
		 }


void	 requirement1(int temp[13], int temp1[13], int best[13], int numnotes)
	 {
	  permutation(temp,temp1);
	  primeform(temp1);
	  if (best[numnotes - 1] - best[0] > temp1[numnotes-1] - temp1[0])
		 copy(temp1,best);
		else if (best[numnotes - 1] - best[0] == temp1[numnotes-1] - temp1[0])
		  requirement2(best,temp1,numnotes);
		copy(temp1,temp);
	 }

void  requirement2(int best[13], int temp1[13], int numnotes)
	 {
	  int i = 1;
	  int success = 0;
	  while (success == 0 && i < numnotes - 1)
	  {
		if (best[i] - best[0] > temp1[i] - temp1[0])
			{
			 success = 1;
			 copy(temp1,best);
			}
		 ++i;
		}
	 }

void comparenotes(int notes[13])
	{
	 int i,j,temp[13],temp1[13],best[13];
	 int numnotes = notes[12];
	 copy(notes,temp);
	 copy(notes,best);
	 printf("Here are the rest of the permutations\n");
	 for (i = 1; i < numnotes; ++i)
		{
		 requirement1(temp,temp1,best,numnotes);
		  for (j = 0; j < numnotes; ++j)
			printf("%d ",temp[j]);
		  printf("\n");
	  }
	printf("best\n");
	 for (i = 0; i < numnotes; ++i)
	 printf("%d ",best[i]);
	for (i = 0; i < numnotes; ++i)
	  notes[i] = best[i];
 }

void makeinversion(int notes[13], int inversion[13])
	{
	 int i, temp;
	 for (i = 0; i < 12; ++i)
		{
		 temp = 12 - notes[i];
		 if (temp == 12) temp = 0;
		 inversion[i] = temp;
		}
	  inversion[12] = notes[12];
	}











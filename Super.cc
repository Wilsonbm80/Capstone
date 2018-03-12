#include <iostream>

class Gen
{

	int measures;	//total measures in a song
	int bpm;	//beats per measure, not per minute
	int duration;	//length of a note
	int instrument; //instrument/channel to be played 
	int pitch;	//pitch of a note
	int volume;	//volume of a note

	virtual void playNote(){}
	virtual void playMeasure(){}

};

class QuarterGen : Gen
{

	//generate 4 notes per measure, one beat per note

	int bpm = 4; //beats per measure, not minute
	int measures=4;
	int pitch = 88;
	int volume = 127;
	int duration = 1;
	int instrument = 60;
	
	public:
	void playNote()
	{
		std::cout << duration << instrument << pitch << volume << "\n";
	}

	void playMeasure()
	{
		for(int i=0 ; i < bpm ; i+=duration)
		{
			playNote();
		}
	}


};

class HalfGen : Gen
{

	//4 notes per measure, two beat per note

	int bpm = 4; //beats per measure, not minute
	int measures=4;
	int pitch = 99;
	int volume = 127;
	int duration = 2;
	int instrument = 60;

	public:
	void playNote()
	{
		std::cout << duration << instrument << pitch << volume << "\n";
	}

	void playMeasure()
	{
		for(int i=0 ; i < bpm ; i+=duration)
		{
			playNote();
		}
	}

};

int main()
{
	QuarterGen qg;
	HalfGen hg;
	int currentSong = 0; //0 for qg, 1 for hg
	for(int i=0 ; i<4 ; i++)
	{
		switch (currentSong)
		{
			case 0:
				qg.playMeasure();
				break;
			case 1:			
				hg.playMeasure();
				break;
			default:
				return 1;
		}
		currentSong++;
		if (currentSong>1)
			currentSong = 0;
	}
}





# Capstone

Author: Brenton Wilson

Purpose: create music based upon multiple genres/styles. Generically this means merge two or more midi files 
in a way that results in an output midi file that is of both inputs' genres.

Three complete algorithms for 2-midi-file merges have been created in this repo. They can each be called from the shell script: "midimerge.sh".

./midimerge.sh <Merge_Algorithm_Tag> <InputSong#1> <InputSong#2>

Example:

./midimerge.sh 1 folkSong.mid bluesSong.mid

(1)Random Midi Merge generates a list of note_on timestamps that will be played by one output song (no note_ons matching that timestamp will play from the other). Then, the second song adds all note_ons that do not have a timestamp contained in the random list.

(2)Sequential Midi Merge - Order: Add 4 note_ons from the first song, the 4 from the other, then four from the first... This uses a Python zip to skip instruction at the same position in the file (eg: instruction (or row) # 4).

(3)Sequential Midi Merge - Time: Add 4 note_ons from the first song, the 4 from the other, then four from the first... This uses a Python zip to skip instruction at the same position in the file (eg: instruction (or row) # 4). This is constrained further by only allowing the next note to be played if it is of an equal or later time than the last note.

This work is constrained by requiring the midi files to have only one "Track". There is not currently an abundance of user input/customizability, but this could easily be modified.

Credit: 
1) Algorithmic Computer Music by Dr. John Francis - Creative Commons License.
	I am using this work as a starting place for generating music, of a genre, as a midi file.

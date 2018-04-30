# -*- coding: utf-8 -*-
"""
Created on Sat Apr  7 16:56:19 2018

@author: stick
"""

import re
import sys
import copy
from heapq import heappush, heappop

import random

#$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
fileNameList = []
i = 1
#@@@@@@@@@@@@@@@@@@@@@@@@@
#while(i<=numSongs):
#    fileName = input("Enter the name of file "+str(i)+": ")
#    fileNameList.append(fileName)
#    i+=1

#hardcoded values for testing
#@@@@@@@@@@@@@@@@@@@@@@@@@@@!
numSongs = 2
fileNameList = [str(sys.argv[1]),str(sys.argv[2])]

fileList = []
for x in fileNameList:
    fileList.append(open(x,"r"))

#hardcorded for 2
folkLines = [re.split(', ',line.rstrip()) for line in fileList[0]]
bluesLines = [re.split(", ",line.rstrip()) for line in fileList[1]]

#blues = []
#for line in fileList[0]:
#    blues.append(line)
#folk = []
#for line in fileList[0]:
#    folk.append(line)
#print(blues)

#@@@@@@@@@@@@@@@@@@@@@@@
#outName = input("Enter output file name: ")
outName = "output.csv"
output = open(outName,"w")

#minLength = len(folkLines)
##generic min @@@@@@@@@@@@@@@@@@
##for file in fileList:
##    if(len(file)<min):
##        min=len(file)
#if(len(bluesLines)<minLength):
#    minLength = len(bluesLines)
#
#
#fileToRead = 0 #index for current file being output
#required header
output.write("0, 0, Header, 0, 1, 96\n1, 0, Start_track\n1, 0, System_exclusive, 5, 126, 127, 9, 1, 247\n")
output.write("1, 0, Program_c, 0, 74\n1, 0, Program_c, 1, 68\n1, 0, Program_c, 2, 0\n1, 0, Program_c, 3, 0\n")
output.write("1, 0, Program_c, 4, 0\n1, 0, Program_c, 5, 0\n1, 0, Program_c, 6, 0\n1, 0, Program_c, 7, 0\n")
counter = 0 #keep track of what line we have read up to

#beatCounter = 0
#lastBeatPos = 0

#measure = int(folkLines[0][5])
#print(measure)

#$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

#mid1 = [[1,0,"header",0,0,0],[1,1,"on",1,50,127],[1,2,"off",2,51,0],[1,5,"on",1,52,127],[1,6,"off",1,52,0],[1,6,"end",0,0,0],[1,0,"footer",0,0,0]]
#mid2 = [[1,0,"header",0,0,0],[1,2,"on",2,60,127],[1,2,"on",1,60,127],[1,3,"off",1,60,0],[1,4,"off",2,60,0],[1,6,"on",1,62,127],[1,7,"off",1,62,0],[1,7,"end",0,0,0],[1,0,"footer",0,0,0]]
#min1 = 6

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#tmp1 = max(folkLines, key=lambda x: x[1])[1]
#
#tmp2 = max(bluesLines, key=lambda x: x[1])[1]

#max1 = 7

 

#if(tmp1>tmp2):
#
#    min2=tmp2
#
#    max2=tmp1
#
#else:
#
#    min2=tmp1
#
#    max2=tmp2
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
min2, max2 = 9600, 25728
 

#print(min2)

#print(max2)

#print()

 

#out1 = [[1,0,"header",0,0,0]]

 

heap = []

 

time1 = 0

 

#beatAmount = 1*4 #1/quarter note, 4 quarter notes per "slice"


#print()



omid = []

iCount = 0
playA = True
time = 0
for anote, bnote in zip(folkLines,bluesLines):
    if(playA):
        anote[1] = int(anote[1])
        if(anote[2]=="Note_on_c" and anote[1]>=time):
            time = anote[1]
            anote[1] = str(anote[1])
            omid.append(anote)
            iCount+=1
    else:
        bnote[1] = int(bnote[1])
        if(bnote[2]=="Note_on_c" and bnote[1]>=time):
            time = bnote[1]
            bnote[1] = str(bnote[1])
            omid.append(bnote)
            iCount+=1
    if(iCount>3):
        iCount = 0
        if(playA):
            playA = False
        else:
            playA = True
            

            
    #    if (item[2]=="Note_on_c" and (int(item[1]) in l)):
#        str(item[1])
#        omid.append(item)
#        aCount+=1
#    else:
#        str(item[1])


 

omid.sort(key=lambda x: int(x[1]))
#for i in omid:
#    print(i)
#print(omid)

#print()

endTime=0

for item in omid:

    time1 = item[1]

    while((heap) and (min(heap)[0]<=int(time1))):
        iCount = 0
        for i in heappop(heap)[1]:
            if(iCount == 1):
                endTime = i
            iCount+=1
            output.write(str(i))
            output.write(", ")
        output.write("\n")
    for i in item:
        output.write(i)
        output.write(", ")
    output.write("\n")

    tmp=copy.copy(list(item))
    time1copy=copy.copy(time1)
    #PROBLEM HERE
    #print(tmp)
    tmp[1]= (random.randint(1,4)*96)+int(time1copy)

    #print(tmp[1])

    tmp[2]="Note_off_c"

    heappush(heap,(tmp[1],tmp))

    #endTime=eval('item[1]+item[3]')

while((heap)):
    iCount = 0
    for i in heappop(heap)[1]:
        if(iCount == 1):
            endTime = i
        iCount+=1
        output.write(str(i))
        output.write(", ")
    output.write("\n")

output.write("1, "+str(endTime)+", End_track\n") #do this, or use max2??

output.write("0, 0, End_of_file")

for x in fileList:
    x.close()
output.close()

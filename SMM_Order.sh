#!/bin/bash

./midicsv-1.1/midicsv $1 songA.csv
./midicsv-1.1/midicsv $2 songB.csv

python3.6 Seq_Merge_Mk2_Order.py "songA.csv" "songB.csv"

./midicsv-1.1/csvmidi output.csv mix.mid

rm songA.csv
rm songB.csv
rm output.csv


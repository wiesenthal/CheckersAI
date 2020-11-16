#!/bin/bash
exploration=$1
moveTime=$2
tieWeight=$3
filename="results.txt"
numTies=`grep "Tie" $filename | wc -l`
numWins=`grep "1" $filename | wc -l`
numLosses=`grep "2" $filename | wc -l`
numSegfaults=`grep "-" $filename | wc -l`
total=`echo "scale=4; $numTies + $numWins + $numLosses" | bc`


tiePercent=$((100*$numTies/$total))
winPercent=$((100*$numWins/$total))
lossPercent=$((100*$numLosses/$total))

echo "exploration=$exploration; moveTime=$moveTime; tieWeight=$tieWeight"
echo "Ties: $tiePercent%"
echo "Wins: $winPercent%"
echo "Losses: $lossPercent%"
echo "number of segmentation faults: $numSegfaults"
echo
cat results.txt

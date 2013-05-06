#!/bin/bash
# Describes a form and gives a poem with that form
CMND="./ezrhyme ../data/sentence-pronounce.kch"
# Choose one random line
RCMND="shuf -n 1"
# Line of 8 syllables, ending with OW syllable
R_1='8\ OW'
# Line of 10 syllables, ending with EY syllable
R_2='10\ EY'

# the poem form
eval $CMND ${R_1} | eval $RCMND;
eval $CMND ${R_2} | eval $RCMND;
eval $CMND ${R_1} | eval $RCMND;
eval $CMND ${R_1} | eval $RCMND;
eval $CMND ${R_1} | eval $RCMND;
eval $CMND ${R_2} | eval $RCMND;
eval $CMND ${R_1} | eval $RCMND;
eval $CMND ${R_1} | eval $RCMND;
eval $CMND ${R_2} | eval $RCMND;
eval $CMND ${R_1} | eval $RCMND;
eval $CMND ${R_2} | eval $RCMND;
eval $CMND ${R_2} | eval $RCMND;
eval $CMND ${R_2} | eval $RCMND;
eval $CMND ${R_1} | eval $RCMND;
eval $CMND ${R_2} | eval $RCMND;
eval $CMND ${R_1} | eval $RCMND;

exit 0;


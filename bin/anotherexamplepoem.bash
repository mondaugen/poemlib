#!/bin/bash
# Describes a form and gives a poem with that form
CMND="./ezrhyme ../data/sentence-pronounce.kch"
RCMND="shuf -n 1"
R_1='8\ OW'
R_2='10\ EY'

# the poem
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


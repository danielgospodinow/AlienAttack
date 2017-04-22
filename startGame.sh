#!/bin/bash

#
rm AlienAttack
#

EXEC_FILE="AlienAttack"

if [ ! -f $EXEC_FILE ]; then
  make clean
  make
fi

./$EXEC_FILE

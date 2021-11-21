#!/bin/bash

#First test
SOURCE="asdlljasnkfasjfn"
REGEX="(as[d-g]+).*(as[i-k]+)"
SUB="==\1==\2=="

IDEAL=`echo $SOURCE | sed -E "s/$REGEX/$SUB/"`
RESULT=`./esub "$REGEX" "$SUB" "$SOURCE"`
if [[ $IDEAL != $RESULT ]]; then
	echo "First test failed"
	exit -1
fi

#Second test
SOURCE="asdlljasnkfasjfn"
REGEX="(as[d-g]+).*(as[i-k]+)"
SUB="\3==\1==\2=="

RESULT=`./esub "$REGEX" "$SUB" "$SOURCE" 2>&1`
if [[ $RESULT != "Nonexistent pocket number 3" ]]; then
	echo "Second test failed"
	exit -1
fi

#Third test
SOURCE="asdlljasnkfasjfn"
REGEX="(as[d-g]+).*(as[i-k]+)"
SUB="\x==\1==\2=="
RESULT=`./esub "$REGEX" "$SUB" "$SOURCE" 2>&1`
if [[ $RESULT != "Bad escaped character 'x' in substitution string in position 2" ]]; then
	echo "Third test failed"
	exit -1
fi

echo "Tests passed"
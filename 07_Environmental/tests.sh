#!/bin/bash


IDEAL=($(md5sum rhasher))
RESULT=($(echo "MD5 rhasher" | ./rhasher))
if [[ ${IDEAL[0]} != $RESULT ]] && [[ ${IDEAL[0]} != ${RESULT[2]} ]]; then
	echo "md5 test failed"
	exit -1
fi

IDEAL=($(sha1sum rhasher))
RESULT=($(echo "SHA1 rhasher" | ./rhasher))
if [[ ${IDEAL[0]} != $RESULT ]] && [[ ${IDEAL[0]} != ${RESULT[2]} ]]; then
	echo "sha1 test failed"
	exit -1
fi

echo "Tests passed"
#!/bin/sh

INFILE="a.txt"
OUTFILE="b.txt"

cp test_source.txt $INFILE
strace -e fault=openat:when=3:error=ENOENT ./move $INFILE $OUTFILE
STATUS=$?
if [ $STATUS -ne 2 ]; then
	echo "INFILE_OPEN_ERROR (ENOENT) test FAILED"
	exit -1
fi && rm -f $OUTFILE && echo

cp test_source.txt $INFILE
strace -e fault=openat:when=3:error=EACCES ./move $INFILE $OUTFILE
STATUS=$?
if [ $STATUS -ne 2 ] || [ ! -f $INFILE ]; then
	echo "INFILE_OPEN_ERROR (EACCES) test FAILED"
	exit -1
fi && rm -f $OUTFILE && echo 

cp test_source.txt $INFILE
strace -e fault=openat:when=4:error=ENOENT ./move $INFILE $OUTFILE
STATUS=$?
if [ $STATUS -ne 4 ] || [ ! -f $INFILE ]; then
	echo "OUTFILE_OPEN_ERROR (ENOENT) test FAILED"
	exit -1
fi && rm -f $OUTFILE && echo

cp test_source.txt $INFILE
strace -e fault=openat:when=4:error=EACCES ./move $INFILE $OUTFILE
STATUS=$?
if [ $STATUS -ne 4 ] || [ ! -f $INFILE ]; then
	echo "OUTFILE_OPEN_ERROR (EACCES) test FAILED"
	exit -1
fi && rm -f $OUTFILE && echo

cp test_source.txt $INFILE
strace -e fault=close:when=4:error=EPERM ./move $INFILE $OUTFILE
STATUS=$?
if [ $STATUS -ne 6 ] || [ ! -f $INFILE ]; then
	echo "OUTFILE_CLOSE_ERROR (EPERM) test FAILED"
	exit -1
fi && rm -f $OUTFILE && echo

cp test_source.txt $INFILE
strace -e fault=close:when=3:error=EPERM ./move $INFILE $OUTFILE
STATUS=$?
if [ $STATUS -ne 3 ] || [ ! -f $INFILE ]; then
	echo "INFILE_CLOSE_ERROR (EPERM) test FAILED"
	exit -1
fi && rm -f $OUTFILE && echo

cp test_source.txt $INFILE
strace -e fault=unlink:when=1:error=EACCES -e fault=read:when=3:error=EPERM ./move $INFILE $OUTFILE
STATUS=$?
if [ $STATUS -ne 11 ] || [ ! -f $INFILE ]; then
	echo "OUTFILE_REMOVE_ERROR (EACCES) test FAILED"
	exit -1
fi && rm -f $OUTFILE && echo

cp test_source.txt $INFILE
strace -e fault=unlink:error=EACCES ./move $INFILE $OUTFILE
STATUS=$?
if [ $STATUS -ne 10 ] || [ ! -f $INFILE ]; then
	echo "INFILE_REMOVE_ERROR (EACCES) test FAILED"
	exit -1
fi && rm -f $OUTFILE && echo

cp test_source.txt $INFILE
./move $INFILE $INFILE
STATUS=$?
if [ $STATUS -ne 1 ] || [ ! -f $INFILE ]; then
	echo "SAME_FILE_ERROR test FAILED"
	exit -1
fi && rm -f $OUTFILE && echo

cp test_source.txt $INFILE
strace -e fault=read:when=3:error=EPERM ./move $INFILE $OUTFILE
STATUS=$?
if [ $STATUS -ne 5 ] || [ ! -f $INFILE ] || [ -f $OUTFILE ]; then
	echo "READ_WRITE_ERROR (read EPERM) test FAILED"
	exit -1
fi && rm -f $OUTFILE && echo

cp test_source.txt $INFILE
strace -e fault=write:when=1:error=EPERM ./move $INFILE $OUTFILE
STATUS=$?
if [ $STATUS -ne 5 ] || [ ! -f $INFILE ] || [ -f $OUTFILE ]; then
	echo "READ_WRITE_ERROR (write EPERM) test FAILED"
	exit -1
fi && rm -f $OUTFILE && echo

cp test_source.txt PROTECTED_$INFILE
LD_PRELOAD=`pwd`/protect_lib.so ./move PROTECTED_$INFILE $OUTFILE
STATUS=$?
if [ $STATUS -ne 10 ] || [ ! -f $INFILE ] || [ ! -f $OUTFILE ]; then #move.c should return INFILE_REMOVE_ERROR here
	echo "LD_PRELOAD test failed"
	exit -1
fi && rm -f $OUTFILE && echo

echo "ALL TESTS PASSED"

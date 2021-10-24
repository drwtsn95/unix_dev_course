range: range.c
	gcc range.c -o range -g -O0

test: range
	gdb --command=scenario_1.gdb ./range | grep @@@ | sed s/@@@// > gdb_result_1.txt
	cmp gdb_result_1.txt result_1.txt

	gdb  --command=scenario_2.gdb ./range | grep @@@ | sed s/@@@// > gdb_result_2.txt
	cmp gdb_result_2.txt result_2.txt
clean: 
	rm -rf gdb_result_1.txt gdb_result_2.txt range

set $j = 1

break 29 if $j >= 28 & $j++ <= 35
	command 1
	printf "@@@%d %d %d %d\n", start, end, step, i
	continue
end

run -100 100 3 > /dev/null

quit
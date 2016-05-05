#!\bin\sh

#configurable value for the test_runs counter.
test_runs=5

count=0

#check if the log file exists or not.
if [ -f overall.log ]
then
	rm overall.log
fi

while [ "$count" -lt "$test_runs" ]
do		
	make -f Makefile_1.3 exec >> overall.log
	exit_code=$?
	echo Exit code : $exit_code

	error=$(grep -q "Error" overall.log && echo $?)
	if [ "$exit_code" != 0 ]
	then
		echo "Error found"
	fi
	count=`expr $count + 1`
done

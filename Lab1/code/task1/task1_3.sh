#!\bin\sh

#configurable value for the test_runs counter.
test_runs=10

count=0

#check if the log file exists or not.
if [ -f overall_1_3.log ]
then
	rm overall_1_3.log
fi

while [ "$count" -lt "$test_runs" ]
do		
	make exec_1_3 >> overall_1_3.log
	exit_code=$?
	error=$(grep -q "Error" overall_1_3.log )
	if [ "$exit_code" != 0 ]
	then
		echo "Error found"
	fi
	count=`expr $count + 1`
done

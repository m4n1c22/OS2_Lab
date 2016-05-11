#!\bin\sh

#configurable value for the test_runs counter.
test_runs=10
error_count=0
success_count=0
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
		error_count=`expr $error_count + 1`
	fi
	count=`expr $count + 1`
done
success_count=`expr $test_runs - $error_count`
echo Program executed $test_runs times with $error_count erroneous executions and $success_count successful executions

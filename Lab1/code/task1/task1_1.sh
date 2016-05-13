#!\bin\sh

#configurable value for the test_runs counter.
test_runs=5
error_count=0
success_count=0
count=0

exitfn () {
    trap SIGINT              
    make clean
    exit                    
}

trap "exitfn" INT            # Set up SIGINT trap to call function.

#check if the log file exists or not.
if [ -f overall.log ]
then
	rm overall.log
fi

while [ "$count" -lt "$test_runs" ]
do		
	make exec >> overall.log
	exit_code=$?
	echo Exit code : $exit_code
	error=$(grep -q "Error" overall.log)
	if [ "$exit_code" != 0 ]
	then
		echo "Error found"
		error_count=`expr $error_count + 1`
	fi
	count=`expr $count + 1`
done
make clean
success_count=`expr $test_runs - $error_count`
echo Program executed $test_runs times with $error_count erroneous executions and $success_count successful executions

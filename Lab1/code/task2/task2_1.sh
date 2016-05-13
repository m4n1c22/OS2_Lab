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
if [ -f server_task2_1.log ]
then
	rm server_task2_1.log
fi

while [ "$count" -lt "$test_runs" ]
do		
	make server_exec_task2_1 >> server_task2_1.log
	
	error=$(grep -q "Error" server_task2_1.log && echo $?)
	if [ "$error" = 0 ]
	then
		echo "Error found"
		error_count=`expr $error_count + 1`
	fi
	count=`expr $count + 1`
done
make clean
success_count=`expr $test_runs - $error_count`
echo Program executed $test_runs times with $error_count erroneous executions and $success_count successful executions

#!\bin\sh

#configurable value for the test_runs counter.
test_runs=10
error_count=0
success_count=0
count=0
#Definition of the interrupt handler routine. Invoked when Ctrl+c/z is encountered.
exitfn () {
    trap SIGINT              
    make clean
    exit                    
}

trap "exitfn" INT            # Set up SIGINT trap to call function.

#check if the log file exists or not.
if [ -f overall_1_3.log ]
then
	rm overall_1_3.log
fi

while [ "$count" -lt "$test_runs" ]
do		
	make exec_1_3 2>&1 | tee -a overall_1_3.log
	count=`expr $count + 1`
done
make clean
error_count=$(grep -c "Error:Testing Task1 Failed." overall_1_3.log)
success_count=`expr $test_runs - $error_count`
echo Program executed $test_runs times with $error_count erroneous executions and $success_count successful executions

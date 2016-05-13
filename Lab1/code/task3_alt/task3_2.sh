#!\bin\sh

#configurable value for the test_runs counter.
test_runs=5
error_count=0
success_count=0
count=0

exitfn () {
    trap SIGINT              
    kill $CLIENT_PID
    rm -r requests
    make clean
    exit                    
}

trap "exitfn" INT            # Set up SIGINT trap to call function.


make comp_server_task3_1
make comp_client_task3_1
#check if the log file exists or not.
if [ -f server_task3_1.log ]
then
	rm server_task3_1.log
fi

while [ "$count" -lt "$test_runs" ]
do		
	#check if the requests folder exists or not.
	if [ -d requests ]
	then
		rm -r requests
	fi
	mkdir requests
	./client_task3_1.bin > client_task3_1.log &
	CLIENT_PID=$!
	./server_task3_1.bin -n 5 -f 50 >> server_task3_1.log
	error=$(grep -q "Error" server_task3_1.log && echo $?)
	if [ "$error" = 0 ]
	then
		echo "Error found"
		error_count=`expr $error_count + 1`
	fi
	count=`expr $count + 1`
	kill $CLIENT_PID
done
rm -r requests
make clean
success_count=`expr $test_runs - $error_count`
echo Program executed $test_runs times with $error_count erroneous executions and $success_count successful executions



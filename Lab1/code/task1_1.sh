#!\bin\sh
test_runs=5
count=0
while [ "$count" -lt "$test_runs" ]
do		
	make exec
	count=`expr $count + 1`
done
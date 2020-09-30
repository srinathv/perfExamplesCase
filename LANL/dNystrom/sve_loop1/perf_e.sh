

if [ -z "$1" ]
  event=0008 #instructions retired
else
  event=${1}
fi

for i in {1 .. 10}
do
  perf -e r${event} ./a.out > tmp.txt
  grep r0 tmp.txt >> r${event}.perf.txt
done 

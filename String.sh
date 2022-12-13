str=$1
length_str=${#str}
substr=$2
length_substr=${#substr}
count=0

for ((  i=0; i<length_str; i++ ))
do
    temp=${str:i:length_substr}
    if [ $temp == $substr ]
    then
        count=$((count+1))
    fi
done


echo "String = $1"
echo "Sub-string = $2"
echo "Count = $count"

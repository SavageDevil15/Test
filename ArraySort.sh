echo "Enter Array Size = "
read size

echo "Enter Array Elements = "
for (( i=0; i<$size; i++))
do
    read input
    array[$i]=$input
done

echo "Array Elements Are : ${array[@]}"

echo "Ascending Order = "
for(( i=0; i<$size; i++ ))
do
    for(( j=$i; j<$size; j++ ))
    do
        if [ ${array[$i]} -gt ${array[$j]} ]
        then
            temp=${array[$i]}
            array[$i]=${array[$j]}
            array[$j]=$temp
        fi
    done
done
echo ${array[@]}

echo "Descending Order = "
for(( i=0; i<$size; i++ ))
do
    for(( j=$i; j<$size; j++ ))
    do
        if [ ${array[$i]} -lt ${array[$j]} ]
        then
            temp=${array[$i]}
            array[$i]=${array[$j]}
            array[$j]=$temp
        fi
    done
done
echo ${array[@]}
echo "Enter a number = "
read num

flag=0
for (( i=2; i<=$num/2; i++ ))
do
    if [ $((num % i)) -eq 0 ]
    then
        echo "$num is not a prime number"
        flag=1
        break
    fi
done

if [ $flag -eq 0 ]
then
    echo "$num is a prime number"
fi

reverse=0
while [ $num -ne 0 ]
do
    remainder=$(expr $num % 10)
    reverse=$(expr $reverse \* 10)
    reverse=$(expr $reverse + $remainder)
    num=$(expr $num / 10)
done
echo "Reverse = $reverse"
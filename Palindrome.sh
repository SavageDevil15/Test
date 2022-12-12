echo "Enter a number = "
read num

temp=$num
reverse=0
while [ $num -ne 0 ]
do
    remainder=$(expr $num % 10)
    reverse=$(expr $reverse \* 10)
    reverse=$(expr $reverse + $remainder)
    num=$(expr $num / 10)
done

if [ $temp -eq $reverse ]
then
    echo "$temp is a palindrome"
else
    echo "$temp is not a palindrome"
fi

echo "Reverse = $reverse"


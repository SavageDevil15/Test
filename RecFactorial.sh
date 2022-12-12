function factorial()
{
    local=$1
    if (( local<=2 ))
    then
        echo $local
    else
        f=$((local -1))
        f=$(factorial $f)
        f=$((f*local))
        echo $f
    fi
}

echo "Enter a number = "
read num

if [ $num -eq 0 ]
then
    echo "Factorial (Recursive) = 1"
else
    factorial $num
fi
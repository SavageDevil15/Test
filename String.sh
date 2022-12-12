echo "String = $1"
echo "Sub-string = $2"

echo $1 | grep -o "$2" | wc -l


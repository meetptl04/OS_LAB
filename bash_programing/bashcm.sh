# #!/bin/bash
# num=10
# echo $num
# s=VIT
# echo "Welcome to $s"
# # read x
# # echo "This is $x"
# NAME[0]="MEET"
# NAME[1]="ALPESH"

# echo "First index : ${NAME[0]}"
# # Calculate the sum of two integers with pre initialize values
# # in a shell script

# a=10
# b=20

# sum=$(( $a + $b ))

# echo "Sum is: $sum"


#!/bin/bash
read x
l=${#x}
echo $l
y=""
for ((i=l-1; i>=0; i--)); do
y="${y}${x:i:1}"
done
if [ "$y" = "$x" ]
then
echo "Given string is palindrome"
else
echo "Given string is not a palindrome"
fi
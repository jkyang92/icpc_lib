#!/bin/bash

echo "The following lines are too long:"
for file in `cat ./files.lst`
do
    awk "{if (length(\$0) > 90) print \"$file:\",\$0 }" < $file;
done

echo "There are tabs in the following lines:"
for file in `cat ./files.lst`
do
    awk "{if(\$0 ~ /\t/) print \"$file:\",\$0 }" < $file;
done

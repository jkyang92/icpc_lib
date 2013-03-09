#!/bin/sh


for file in `cat ./files.lst`
do
sed 's/[\t]/    /g' < "$file" > "$file.new"
diff "$file" "$file.new" > /dev/null || (mv "$file" "$file.old" && cp "$file.new" "$file");
rm "$file.new";
done
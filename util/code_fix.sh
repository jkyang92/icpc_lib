#!/bin/sh


for file in `cat ./files.lst`
do
sed 's/[\t]/    /' < "$file" > "$file.new"
diff "$file" "$file.new" > /dev/null || (mv "$file" "$file.old" && mv "$file.new" "$file");
rm "$file.new";
done
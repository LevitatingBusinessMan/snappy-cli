set -e

source ./test/assert.sh
make
DIR=$(mktemp -d)

#STDIN
cat ./test/dagon | ./snappy --output=$DIR/out -
assert "./snappy -d $DIR/out" "$(cat ./test/dagon)"

#FILE
./snappy --output=$DIR/out ./test/dagon
assert "./snappy -d $DIR/out" "$(cat ./test/dagon)"

#BIG STDIN
cat $(yes ./test/dagon | head -n 100) | ./snappy --output=$DIR/out -
assert "./snappy -d $DIR/out" "$(cat $(yes ./test/dagon | head -n 100))"

assert_end examples

rm -r $DIR

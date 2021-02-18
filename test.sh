FAILURE=0

assert() {
	local name="$1"
	local command="$2"
	local expected="$3"

	local start=$(date +%s%N)
	local actual=$(eval $command)
	local end=$(date +%s%N)

	local time=$((($end - $start)/1000000))


	if [ "$expected" == "$actual" ]; then
		echo -e "\e[32mTest '${name}' ran succesfully (${time}ms)\e[0m"
	else
		FAILURE=1
		echo -e "\e[31mTest '${name}' failed\e[0m"
	fi
}

set -e

make
DIR=$(mktemp -d)
echo

#STDIN
cat ./test/dagon | ./snappy --output=$DIR/out -
assert "STDIN" "./snappy -d $DIR/out" "$(cat ./test/dagon)"
echo

#FILE
./snappy --output=$DIR/out ./test/dagon
assert "FILE" "./snappy -d $DIR/out" "$(cat ./test/dagon)"
echo

#BIG STDIN
cat $(yes ./test/dagon | head -n 100) | ./snappy --output=$DIR/out -
assert "BIG STDIN" "./snappy -d $DIR/out" "$(cat $(yes ./test/dagon | head -n 100))"
echo

rm -r $DIR

exit $FAILURE

#!/bin/bash

files="$@"

node_from_path(){
	echo \"$(realpath --relative-to=. $1 | sed "s/\.[hc]$//;s/\.cpp$//")\"
}

echo "strict digraph dependency_graph {"
echo "ratio=fill"
echo "size=\"16,12\""

for file in $files; do
	node=$(node_from_path $file)
	[[ $file =~ ".test.cpp" ]] && echo "${node} [shape=box]"
	#(for include_path in `/usr/local/bin/g++-7.1.0.exe $file -I/cygdrive/c/local/boost_1_64_0 -E -H 2>&1 |grep "^\. [^/]"|sed "s/^\. //"`; do node_from_path $include_path; done)|sed "s@.*@${node} -> \0@"
	(for include_path in `g++ $file -std=c++17 -fconcepts -E -H 2>&1 >/dev/null |grep "^\. [^/]"|sed "s/^\. //"`; do node_from_path $include_path; done)|sed "s@.*@${node} -> \0@"
done

groups=$((for file in $files; do node_from_path $(dirname $file); done)|sort|uniq)
for group in $groups; do
	subgraph=$(echo $group | sed "s,^\"\(.*\)\"$,cluster_\1,;s,/,_,g;s,\.,root,")
	echo "subgraph ${subgraph} {"
	for file in $files; do
		node=$(node_from_path $file)
		[[ $(node_from_path $(dirname $file)) == $group ]] && echo "${node}"
	done
	echo "}"
done

echo "}"


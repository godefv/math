#!/bin/bash

module_graph=0
if [[ $1 == "--modules" ]]; then
	module_graph=1
	shift
fi

files="$@"

node_from_path(){
	if [[ $module_graph == 0 ]]; then
		echo \"$(realpath --relative-to=. $1 | sed "s/\.[hc]$//;s/\.cpp$//")\"
	else
		echo \"$(realpath --relative-to=. $1 | sed "s,/.*,,")\"
	fi
}

echo "strict digraph dependency_graph {"

for file in $files; do
	node=$(node_from_path $file)
	[[ $file =~ ".test.cpp" && $module_graph == 0 ]] && echo "${node} [shape=box]"
	(for include_path in `g++ $file -std=c++17 -fconcepts -I. -E -H 2>&1 >/dev/null |grep "^\. [^/]"|sed "s/^\. //"`; do dependancy=$(node_from_path $include_path); [[ $dependancy != $node ]] && echo $dependancy; done)|sed "s@.*@${node} -> \0@"
done

if [[ $module_graph == 0 ]]; then
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
fi

echo "}"


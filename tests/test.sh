#!/bin/bash
cd "$(dirname "$(realpath "$0")")";

BOLD="\e[1m"
GREEN="\e[32m"
RED="\e[31m"
END="\e[m"
ERROR_STR="${RED}ERROR${END}"
START_STAT="${GREEN}${BOLD}[START ]${END}"
OK_STAT="${GREEN}${BOLD}[    OK]${END}"
FAIL_STAT="${RED}${BOLD}[  FAIL]${END}"
VALGRIND_LOG="valgrind.log"
DEFAULT_OUT="output.txt"
VALGRIND_EXE=""

function list_tests
{
	printf '%s\n' "${test_names[@]}"
}

function find_best_test_match
{
	local best_match=""
	local best_match_score="0.0"
	local score
	for test in ${test_names[@]}
	do
		score=$(fstrcmp "$test" "$test_to_run")
		if [ $(bc <<< "$score > $best_match_score") -eq 1 ]
		then
			best_match_score=$score
			best_match=$test
		fi
	done
	echo "$best_match"
}

function run_single_test
{
	local test_found
	for test in ${test_names[@]}
	do
		if [[ "$test" == "$test_to_run" ]]
		then
			test_found=$test_to_run
		fi
	done
	if [[ -z $test_found ]]
	then
		test_found=$(find_best_test_match)
	fi
	$test_found
}

function count_error
{
	((error_count++))
}

function exec_pipex
{
	PATH="$pathvar" $VALGRIND_EXE $pipex_exe "in/$file1" "$cmd1" "out/$file2" 2>"out/$errfile" >"out/$outfile"
	out_retval=$?
	if [[ ! -z "$VALGRIND_EXE" ]] && cat $VALGRIND_LOG | grep -q ERROR
	then 
	printf "${ERROR_STR}: Leaks detected\n"
	cat $VALGRIND_LOG
	count_error
	fi
}

function exec_bash
{
	PATH="$pathvar" <"in/$file1" $cmd1 >"ref/$file2" 2>"ref/$errfile"
	ref_retval=$?
}

function exec_pipex_and_bash
{
	exec_pipex
	exec_bash
}

function expect_file_match {
	if ! cmp -s "out/$1" "ref/$1"
	then
		count_error
		printf "${ERROR_STR}: $1 does not match reference:\n"
		diff -u "ref/$1" "out/$1"
	fi
}

function expect_file_match_unordered {
	if ! cmp -s <(sort "out/$1") <(sort "ref/$1")
	then
		count_error
		printf "${ERROR_STR}: $1 does not match reference in any line order:\n"
		diff -u "ref/$1" "out/$1"
	fi
}

function expect_retval_match {
	if (( ! $out_retval != ! $ref_retval ))
	then
		count_error
		printf "${ERROR_STR}: return value does not match reference:\nexpected: $ref_retval\n  actual: $out_retval\n"
	fi
}

function expect_pipex_eq_bash_behavior {
	expect_file_match_unordered "$errfile"
	expect_file_match "$file2"
	expect_stdout_empty
	expect_retval_match
}

function expect_stdout_empty {
	if [ -s out/$outfile ]
	then
		printf "${ERROR_STR}: stdout not empty\n"
		count_error
	fi
}

function block_stderr
{
	exec 3>&2 2>/dev/null
}

function unblock_stderr
{
	exec 2>&3
}

function print_summary {
	if [ $error_count -eq 0 ]
	then
		printf "${OK_STAT} $test_name\n"
	else
		printf "${FAIL_STAT} $test_name ($error_count errors)\n"
	fi
}

function test_setup
{
	test_name=${FUNCNAME[1]}
	printf "${START_STAT} $test_name\n"
	error_count="0"
	pathvar=""
	pipex_exe=$(realpath ../pipex)
	errfile="stderr.txt"
	outfile="stdout.txt"
	file1=""
	file2=""
	cmd1=""
	cmd2=""
	rm -f out/*
	rm -f ref/*
}

test_names=()

function register
{
	test_names[${#test_names[@]}]=$1
}

register TEST_returning_ok
function TEST_returning_ok {
	test_setup

	file1="empty.txt"
	cmd1="/bin/ls"
	file2=$DEFAULT_OUT
	exec_pipex_and_bash
	expect_pipex_eq_bash_behavior

	print_summary
}

register TEST_with_arg
function TEST_with_arg {
	test_setup

	file1="empty.txt"
	cmd1="/bin/ls -l"
	file2=$DEFAULT_OUT
	exec_pipex_and_bash
	expect_pipex_eq_bash_behavior

	print_summary
}

register TEST_returning_error
function TEST_returning_error {
	test_setup


	file1="animals.txt"
	cmd1="/bin/grep banana"
	file2=$DEFAULT_OUT
	exec_pipex_and_bash
	expect_pipex_eq_bash_behavior

	print_summary
}

register TEST_printing_to_stderr
function TEST_printing_to_stderr {
	test_setup

	file1="animals.txt"
	cmd1="/bin/grep"
	file2=$DEFAULT_OUT
	exec_pipex_and_bash
	expect_pipex_eq_bash_behavior

	print_summary
}

register TEST_segfault
function TEST_segfault {
	test_setup

	file1="animals.txt"
	cmd1="./bin/segfaulter.sh"
	file2=$DEFAULT_OUT
	block_stderr
	exec_pipex_and_bash
	unblock_stderr
	expect_pipex_eq_bash_behavior

	print_summary
}

#main

while getopts "vt:lh" opt; do
	case $opt in
	v)
		VALGRIND_EXE="/usr/bin/valgrind -s --tool=memcheck --leak-check=full --log-file=out/$VALGRIND_LOG --trace-children=yes"
		;;
	t)
		test_to_run=$OPTARG
		;;
	l)
		list_tests
		exit
		;;
	h)
		echo "Valid options:"
		echo "-v (use valgrind)"
		echo "-t <TEST_name> (execute single test)"
		echo "-l (list tests)"
		echo "-h (display help)"
		exit
		;;
	\?)
		exit
		;;
	esac
done

if [[ -z "$test_to_run" ]]
then
	for test in ${test_names[@]}
	do
	$test
	done
else
	run_single_test
fi

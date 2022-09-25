#!/bin/bash
cd "$(dirname "$(realpath "$0")")";

BOLD="\e[1m"
RED="\e[31m"
GREEN="\e[32m"
YELLOW="\e[33m"
CYAN="\e[36m"
END="\e[m"
ERROR_STR="${RED}ERROR${END}"
START_STAT="${CYAN}${BOLD}[START ]${END}"
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
	PATH="$pathvar" $VALGRIND_EXE $pipex_exe "in/$file1" "$cmd1" "$cmd2" "out/$file2" 2>"out/$errfile" >"out/$outfile"
	out_retval=$?
	sed -i "s;^$pipex_exe;progname;" out/$errfile
	if [[ ! -z "$VALGRIND_EXE" ]] && cat out/$VALGRIND_LOG | grep -q "ERROR SUMMARY: [1-9]"
	then 
	printf "${ERROR_STR}: Leaks detected\n"
	cat out/$VALGRIND_LOG
	count_error
	fi
}

function exec_bash
{
	( export PATH="$pathvar"; <"in/$file1" $cmd1 | $cmd2 >"ref/$file2" ) 2>"ref/$errfile"
	ref_retval=$?
	sed -i "s;^$0: line [0-9]*;progname;" ref/$errfile
	sed -i "s:ref/:out/:g" ref/$errfile
}

function exec_pipex_and_bash
{
	exec_pipex
	exec_bash
}

function expect_file_match {
	if [[ ! -f "ref/$1" ]]
	then
		if [[ -f "out/$1" ]]	
		then
			count_error
			printf "${ERROR_STR}: $1 should not exist\n"
		fi
	elif ! cmp -s "out/$1" "ref/$1"
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

function expect_pipex_eq_bash_behavior_with_empty_err {
	expect_stderr_empty
	expect_file_match "$file2"
	expect_stdout_empty
	expect_retval_match
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

function expect_stderr_empty {
	if [ -s out/$errfile ]
	then
		printf "${ERROR_STR}: stderr not empty\n"
		count_error
	fi
}

function with_unwriteable_output_file
{
	echo "whatever" >"out/$1"
	chmod -w "out/$1"
	echo "whatever" >"ref/$1"
	chmod -w "ref/$1"
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
	test_names+=("$1")
}

register TEST_returning_ok
function TEST_returning_ok {
	test_setup

	file1="empty.txt"
	cmd1="/bin/ls"
	cmd2="/bin/ls"
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
	cmd2="/bin/ls -l"
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
	cmd2="/bin/grep banana"
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
	cmd2="/bin/grep"
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
	cmd2="./bin/segfaulter.sh"
	file2=$DEFAULT_OUT
	exec_pipex_and_bash
	expect_pipex_eq_bash_behavior_with_empty_err

	print_summary
}

register TEST_full_flow
function TEST_full_flow {
	test_setup

	file1="animals.txt"
	cmd1="/usr/bin/sort"
	cmd2="/bin/grep dog"
	file2=$DEFAULT_OUT
	exec_pipex_and_bash
	expect_pipex_eq_bash_behavior

	print_summary
}

register TEST_no_input_file
function TEST_no_input_file {
	test_setup

	file1="joker.txt"
	cmd1="./bin/tux.sh a"
	cmd2="./bin/tux.sh b"
	file2=$DEFAULT_OUT
	exec_pipex_and_bash
	expect_pipex_eq_bash_behavior

	print_summary
}

register TEST_input_file_no_perm
function TEST_input_file_no_perm {
	test_setup

	file1="forbidden.txt"
	cmd1="./bin/tux.sh a"
	cmd2="./bin/tux.sh b"
	file2=$DEFAULT_OUT
	exec_pipex_and_bash
	expect_pipex_eq_bash_behavior

	print_summary
}

register TEST_no_output_file
function TEST_no_output_file {
	test_setup

	file1="empty.txt"
	cmd1="./bin/tux.sh a"
	cmd2="./bin/tux.sh b"
	file2="./joker/joker.txt"
	exec_pipex_and_bash
	expect_pipex_eq_bash_behavior

	print_summary
}

register TEST_output_file_no_perm
function TEST_output_file_no_perm {
	test_setup

	file1="empty.txt"
	cmd1="./bin/tux.sh a"
	cmd2="./bin/tux.sh b"
	file2="unwriteable.txt"
	with_unwriteable_output_file $file2
	exec_pipex_and_bash
	expect_pipex_eq_bash_behavior

	print_summary
}

register TEST_no_input_or_output
function TEST_no_input_or_output {
	test_setup

	file1="joker.txt"
	cmd1="./bin/tux.sh a"
	cmd2="./bin/tux.sh b"
	file2="no/such/file.txt"
	exec_pipex_and_bash
	expect_pipex_eq_bash_behavior

	print_summary
}

register TEST_invalid_cmd1
function TEST_invalid_cmd1 {
	test_setup

	file1="empty.txt"
	cmd1="./no/such/prog"
	cmd2="./bin/tux.sh b"
	file2=$DEFAULT_OUT
	exec_pipex_and_bash
	expect_pipex_eq_bash_behavior

	print_summary
}

register TEST_invalid_cmd2
function TEST_invalid_cmd2 {
	test_setup

	file1="empty.txt"
	cmd1="./bin/tux.sh b"
	cmd2="./no/such/prog"
	file2=$DEFAULT_OUT
	exec_pipex_and_bash
	expect_pipex_eq_bash_behavior

	print_summary
}

register TEST_path_empty_invalid_cmd2
function TEST_path_empty_invalid_cmd2 {
	test_setup

	file1="empty.txt"
	cmd1="./bin/tux.sh a"
	cmd2="joker"
	file2=$DEFAULT_OUT
	exec_pipex_and_bash
	expect_pipex_eq_bash_behavior

	print_summary
}

register TEST_path_empty_valid_cmd2
function TEST_path_empty_valid_cmd2 {
	test_setup

	file1="empty.txt"
	cmd1="./bin/tux.sh a"
	cmd2="impostor.sh impostor"
	file2=$DEFAULT_OUT
	exec_pipex_and_bash
	expect_pipex_eq_bash_behavior

	print_summary
}

#main

while getopts "vt:lh" opt; do
	case $opt in
	v)
		VALGRIND_EXE="/usr/bin/valgrind -s --tool=memcheck --leak-check=full --log-file=out/$VALGRIND_LOG --trace-children=no"
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
		echo "-v : use valgrind"
		echo "-t <TEST_name> : execute single test (fuzzy name match)"
		echo "-l : list tests"
		echo "-h : display this help"
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

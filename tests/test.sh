#!/bin/bash

BOLD="\e[1m"
GREEN="\e[32m"
RED="\e[31m"
END="\e[m"
ERROR_STR="${RED}ERROR${END}"
START_STAT="${GREEN}${BOLD}[START ]${END}"
OK_STAT="${GREEN}${BOLD}[    OK]${END}"
FAIL_STAT="${RED}${BOLD}[  FAIL]${END}"

function count_error
{
	((error_count++))
}

function exec_pipex
{
	PATH="$pathvar" $pipex_exe "$cmd1" 2>"out/$errfile" >"out/$outfile"
	out_retval=$?
}

function exec_bash
{
	PATH="$pathvar" $cmd1 2>"ref/$errfile" >"ref/$outfile"
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

function expect_retval_match {
	if (( ! $out_retval != ! $ref_retval ))
	then
		count_error
		printf "${ERROR_STR}: return value does not match reference:\nexpected: $ref_retval\n  actual: $out_retval\n"
	fi
}

function expect_pipex_eq_bash_behavior {
	expect_file_match "$errfile"
	expect_file_match "$outfile"
	expect_retval_match
}

function expect_stderr_empty {
	if [ -s $errfile ]
	then
		echo "stderr not empty"
		error_count=$(($error_count + 1))
	fi
}

function expect_retval_ok {
	if [ $out_retval -ne 0 ]
	then
		echo "retval not ok: $out_retval"
		error_count=$(($error_count + 1))
	fi
}

function print_summary {
	if [ $error_count -eq 0 ]
	then
		printf "${OK_STAT} $test_name\n"
	else
		printf "${FAIL_STAT} $test_name ($error_count errors)\n"
	fi
}

function test_setup {
	test_name=${FUNCNAME[1]}
	printf "${START_STAT} $test_name\n"
	error_count="0"
	pathvar=""
	pipex_exe=$(realpath ../pipex)
	errfile="stderr.txt"
	outfile="stdout.txt"
	rm -f out/*
}

function TEST_basic {
	test_setup

	cmd1="echo"
	exec_pipex_and_bash
	expect_pipex_eq_bash_behavior

	print_summary
}

TEST_basic

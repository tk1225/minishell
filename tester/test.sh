#!/bin/bash

# 引数に[pipes, builtins, redirects, syntax]などのファイル名を追加して使用
# KOはlog参照
TESTFILE=$1
TESTCASE=0
PASSED=0
STATUS_PASSED=0

# myVar=$(($myVar + 1))
# echo $myVar
printf '\n%s\n'" minishell" > log

assert() {
    #!/bin/bash
	echo "🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥";
	echo "                                                                                             ";
	echo " ██    ██ █ ██    █ █ █████ █   █ █████ █     █       ██████ █████ █████ ██████ █████ █████  ";
	echo " ███  ███ █ ███   █ █ █     █   █ █     █     █         ██   █     █       ██   █     █   ██ ";
	echo " █ ████ █ █ █ ██  █ █ █████ █████ ████  █     █         ██   ████  █████   ██   ████  █████  ";
	echo " █  ██  █ █ █  ██ █ █     █ █   █ █     █     █         ██   █         █   ██   █     █   ██ ";
	echo " █      █ █ █   ███ █ █████ █   █ █████ █████ █████     ██   █████ █████   ██   █████ █   ██ ";
	echo "                                                                                             ";
	echo "🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥";
	echo "                                                                                              ";
    while IFS= read -r line; do    
        TEST=$line
	TESTCASE=$(($TESTCASE + 1))
	
    # break
    # テストしようとしている内容をprint
	printf '\033[34m%s\033[m\n' "****************************TEST***************************"
	printf '\n%s\n' "****************************TEST***************************" >> log
	printf '%-30s' "$TEST"
	printf '%-30s' "$TEST" >>log

	# bashの出力をcmpに保存
	# echo -n -e "$TEST" | bash >cmp 2>&-
	echo -n -e "$TEST" | ../minishell >out 2>&-
	echo -n -e "$TEST" | bash >cmp 2>&-
	# bashのexit statusをexpectedに代入
	expected=$?
	# minishellの出力をoutに保存
	# minishellのexit statusをactualに代入
	actual=$?

	# bashとminishellの出力を比較
	diff cmp out >>/dev/null && printf '\n\033[34m%s\033[m\n' "  diff OK" || printf '\n\033[31m%s\033[m\n' "  diff KO"
	diff cmp out >>/dev/null || printf '\n%s\n%s\n' "  diff KO" " 本家" >> log
	diff cmp out >>/dev/null || cat cmp >> log
	diff cmp out >>/dev/null || printf '%s\n'" minishell**" >> log
	diff cmp out >>/dev/null || cat out >> log
	diff cmp out >>/dev/null || printf '\n'" **minishell" >> log
	diff cmp out >>/dev/null && PASSED=$(($PASSED + 1))
	

	# bashとminishellのexit statusを比較
	if [ "$actual" = "$expected" ]; then
		printf '\033[34m%s\033[m\n' "  status OK"
		STATUS_PASSED=$(($STATUS_PASSED + 1))
	else
		printf '\033[31m%s\033[m\n' "  status NG, expected $expected but got $actual"
	fi
	echo
	printf '\ndiffPASS:%d/%d\nstatusPASS:%d/%d\n' $PASSED $TESTCASE $STATUS_PASSED $TESTCASE
    done < $TESTFILE
}

# printf '\n%d\n' $PASSED

assert ''
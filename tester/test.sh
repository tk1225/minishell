#!/bin/bash

TESTFILE="builtins"

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
    # break
    # テストしようとしている内容をprint
	printf '\033[34m%s\033[m\n' "****************************TEST***************************"
	printf '%-30s:' "\"$TEST\""

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
	diff cmp out >/dev/null && printf '\n\033[34m%s\033[m\n' "  diff OK" || printf '\n\033[31m%s\033[m\n' "  diff KO"
	# bashとminishellのexit statusを比較
	if [ "$actual" = "$expected" ]; then
		printf '\033[34m%s\033[m\n' "  status OK"
	else
		printf '\033[31m%s\033[m\n' "  status NG, expected $expected but got $actual"
	fi
	echo

    done < $TESTFILE
}

assert ''
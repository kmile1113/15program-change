#!/bin/bash
IFS=$'\n'
user_arr=(`cat mydict.dat |awk '{ print $0}'`)
times=0
time=5
word_res=()
exp_res=()
	line=`cat mydict.dat|wc -l`
	num=$[RANDOM%line+1]
	ju=$[num%2]

	if [ $ju -ne 1 ]
	then
		word=${user_arr[$num]}
		exp=${user_arr[$num+1]}
	else
		word=${user_arr[$num-1]}
		exp=${user_arr[$num]}
	fi
	res=`echo ${word_res[@]} |grep $word`
	if [ ! -n "$res" ];then
		word_res=$word
		exp_res=$exp
	fi

for exp in ${exp_res}
do 
	echo  "The expression is :$exp"
	echo -n "Guess the word:"
done



while true 
do
	read ack
	let times++
	if [[ -n $ack ]]
	then
	if [[ $word == $ack ]]&&[ $times -le $time ]
	then
		echo "*********************************************"
		echo "YOU ARE RIGHT!You guessed $times times in all"
		echo "============================================="
		echo "The word :$word"
		echo "The expression :$exp"
		break
	elif [[ $word != $ack ]]&&[ $times -le $time ]
	then
		echo "Try again! You've guessed $times times"
		echo -n "Guess the word:"	
	else
		echo "Time over!This word is $word"
		break
	fi
	else
		echo "Your input is blank"
		echo -n "Guess the word:"
		let times--
	fi
done

echo

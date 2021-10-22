#!/bin/sh
pause=$1
TEXT=""
empty_text=""
while IFS= read -r line; do
	LEN=$(/bin/echo -e -n "$line" | wc -c)
	TAIL=$(printf %${LEN}s | tr " " "=")
	empty_text=$empty_text$TAIL'\t'
	text=$text$line'\n'
done

EMPTY_LEN=$(/bin/echo -e -n "$empty_text" | wc -c)

SEQ=$(seq $EMPTY_LEN | shuf)
#SEQ="2 9 3 10 6 12 11 4 7 14 5 8 15 13 1"

tput clear

hght=$(tput lines)
wdth=$(tput cols)

for ch in $SEQ; do
	#echo "SEQ: ${ch}"
	CUR_CHAR="$(/bin/echo -e "$text" | cut -z -c${ch})"
	if [ "${CUR_CHAR}" = '' ] || [ "${CUR_CHAR}" = ' ' ] ; then
		continue
	fi
	row=0
	col=0
	CH_MIN="$((ch-1))"
	BEGIN=""
	if [ ${ch} -gt 1 ] ; then
		BEGIN="$(/bin/echo -e "$empty_text" | cut -z -c1-${CH_MIN})"
	fi
	row=$(/bin/echo -n -e "${BEGIN}" | tr -d -c '\t' | wc -c)
	RES=$(/bin/echo -e "\t")
	TAIL=$(/bin/echo "$BEGIN" | rev | cut -d '	' -f1)
	col=${#TAIL}
	if [ $row -ge $hght ] || [ $col -ge $wdth ]; then
		continue
	fi

	tput cup $row $col
	/bin/echo -n -e "$CUR_CHAR\b"
	sleep ${pause}
done

tput cup $((hght-1)) 0


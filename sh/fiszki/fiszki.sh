#!/bin/bash

folder='./folder'
usage='''
Usage
'''

add(){
  case $2 in
    'category')
      [[ -z "$3" ]] && echo Please enter category name || mkdir "$folder/$3";;
    *)
      [[ -z "$2" ]] && { echo Name is empty; exit 1; }
      [[ -d "$folder/$2" ]] && {
        local f="$folder/$2"
        local count="`ls $f | wc -w`"
        local file="$f/$count"
        IFS=''

        echo -n 'Question: '
        read line
        echo -e "$line\n" > "$file"
        echo -n 'Answer: '
        read line
        echo -e "$line\n" >> "$file"
      }
  esac
}

giveQuestion(){
  local file="$folder/$1/$2"
  IFS=$'\n'
  local content=(`cat $file`)

  echo "Question: ${content[0]}"
  echo -n "Answer: "
  read line
  [[ "$line" == "${content[1]}" ]] && echo OK || echo Fail
}

questionFrom(){
  local num=0
  local f="$folder/$1"
  local count="`ls $f | wc -w`"
  (( num = $RANDOM % count ))
  giveQuestion $1 $num
}

questionFromAll(){
  local arr=(`ls $folder`)
  local count=${#arr[@]}
  local rand=0
  (( rand = $RANDOM % count ))
  questionFrom ${arr[$rand]}
}

[[ -d "$folder" ]] || mkdir -p "$folder"

case $1 in
  ''|'q'|'question')
    [[ -z "$2" ]] && questionFromAll || questionFrom $2;;
  'add')
    add $@;;
  *)
    echo $usage
esac


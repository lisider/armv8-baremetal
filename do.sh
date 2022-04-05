#########################################################################
# File Name: do.sh
# Author: SuWeishuai
# mail: suwsl@foxmail.com
# Created Time: Tue 05 Apr 2022 09:20:19 PM CST
# Version : 1.0
#########################################################################
#!/bin/bash

instructions(){
    find . -maxdepth 1 -name "*.asm" \
        | xargs cat \
        | grep  "^ " \
        | grep -v "is out of bounds" \
        | awk -F " " '{print $3}' \
        | sort \
        | uniq > instructions.txt
}


##########################################################
##########################################################


Usage(){
    cat ${CURRENT_SCRIPT} | grep "(){" | grep -v "^ " \
        | egrep -v  "Usage|Main" \
        | awk -F "(" '{print $1}' \
        | while read line
    do
        echo Usage : ${CURRENT_SCRIPT} ${line}
    done
    exit -1
}

Main(){

    CURRENT_SCRIPT=$0

    if [ $# != 1 ];then
        Usage
    fi

    OBJ=$1

    cat ${CURRENT_SCRIPT}  \
        | grep "(){" \
        | grep -v "^ " \
        | egrep -v  "Usage|Main" \
        | grep -w ${OBJ} > /dev/null
    if [ $? -eq 0 ];then
        ${OBJ}
    else
        echo ${OBJ} : NOT DEFINED
        exit -2
    fi
}

Main $*

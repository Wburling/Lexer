#!/bin/bash
for file in files/*.cci
do
    ./Lexer/main $file
    echo "${file}.ANS vs. ${file}.lexer"
    # diff ${file}.ANS  ${file}.lexer
    if [[ $(diff ${file}.ANS  ${file}.lexer) ]]; then #if output of diff command is not zero
        echo "Somthing went wrong"
        # diff ${file}.ANS  ${file}.lexer
        # cat ${file}.ANS | xclip -selection clipboard
        # echo "Copied correct answer"
        # read -r __unused
        # cat ${file}.lexer | xclip -selection clipboard
        # echo "Copied your answer"
        # echo "Press enter to continue"
        # read -r __unused
        echo
    else
       echo "You passed the test" 
       echo
    fi
done

for file in files/*.ccx
do
    ./Lexer/main $file
    echo "${file}.ANS vs. ${file}.lexer"
    #diff ${file}.ANS  ${file}.lexer
    if [[ $(diff ${file}.ANS  ${file}.lexer) ]]; then #if output of diff command is not zero
        echo "Somthing went wrong"
       # diff ${file}.ANS  ${file}.lexer
        echo
    else
       echo "You passed the test" 
       echo
    fi
done

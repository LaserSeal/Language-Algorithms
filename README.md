# Formal Langauge Algorithms

**Languages and Machines: An Introduction to the Theory of Computer Science (3rd Edition)** [Amazon](http://www.amazon.com/Languages-Machines-Introduction-Computer-Science/dp/0321322215)

Download, then navigate to the main folder by:

    cd ~/Formal-Language-Algorithms/Main
   
Then compile:

    make

Then to run:

    ./shell

The Help section in the from the shell program:

    :help - to display this
    :quit OR :q OR CTRL + D OR CRTL + C - to quit
    :ls <ARG> - to list the current files in dir
    :vim <FILE> - to edit a file using vim
    :cat <FILE> - displays a file
    ----------------------------------------
    These are all the algorithms, anything in <ARGUMENT> brackets are the arguments
    alg4_1 <grammar pathIn> <grammer pathOut>	 --remove recursive start symbol	-Page 105
    alg4_2 <grammar pathIn> <grammer pathOut>	 --remove lambda rules			-Page 108
    alg4_3 <grammar pathIn> <grammer pathOut> 	 --remove chain rules			-Page 114
    alg4_4_2 <grammar pathIn> <grammer pathOut>	 --generate rules that derive terminals	-Page 117
    alg4_4_4 <grammar pathIn> <grammer pathOut>	 --remove un-reachable rules	        -Page 119
    alg4_5 <grammar pathIn> <grammer pathOut>	 --convert to Chomsky Normal Form	-Page 122
    alg4_6 <grammar pathIn> <pdf pathOut> <string> --CYK algorithm			-Page 126    
    alg4_7 <grammar pathIn> <grammer pathOut>	--removable of direct left recursion	-Page 129
    alg4_8 <grammar pathIn> <grammer pathOut>	--convert to Greibach Normal Form	-Page 132
    alg5_6 <FA pathIn> <FA pathOut>		--remove non-determinism		-Page 172
    alg5_7 <FA pathIn> <FA pathOut>		--determine equivalent states		-Page 179
    alg6_2 <FA pathIn> <FA pathOut>	        --finite state to regular expression	-Page 194

Also there are some built in grammars and finite states in:
    
    ~/Formal-Language-Algorithms/Main/gram/
    ~/Formal-Language-Algorithms/Main/fa/


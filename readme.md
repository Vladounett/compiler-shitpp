IT IS ONLY WORKING IN LINUX, THE ASM WON'T WORK IN WINDOWS
YOU NEED NASM INSTALLED AS THE "main.cpp" WILL CALL NASM TO MAKE A ".o" THAT WILL BE LINKED WITH "ld"

For now you can use :
(ill do a grammar)

i declare [var_name] = [expression];
i am leaving [expression];

[expression] = [int_literral]//[var_name]

keep in mind that for now, you can't do things like : x = y + 2;
you can only declare a variable by an int or a reference to another var_name, and exit with an int or a reference to a var_name
the only way to see the result of a var declaration is to exit with the value of the var, in the console after executing the "finished_product" file (it is the file that was compiled then linked), you can type "echo $?" to see the code of exit of the last program that was executed

file extension is .shyt, but it doesn't matter right now as the compiler will read any files that you point to, if it exists

i've put semi-colons in the exemple .shyt, and the compiler will make token when encountering a semi-colon, but at this point you could just replace them with a space : ' '. Cause the parser will not look for a semi-colons at the end of instructions (will do in the future)

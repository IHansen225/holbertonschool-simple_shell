<h1>hsh(1) - README/Manual page</h1>

<h3>Prolog</h3>
<hr>
<p>This repository contains all the necessary files to compile and run Holberton Shell (aka. hsh).</p>
<p>It's based on the original $ sh from Linux.</p>

<h3>Name</h3>
<hr>
<p>Holberton Shell - ./hsh</p>

<h3>Description</h3>
<hr>
<p>In this repository you will be find a short descrption of what is a shell.
In programming, a shell is a command-line interpreter, this means that the shell its a traductor between the user and the system.
All the commands entered by the user will be taken over by the terminal and passed to the shell.
If the user enters a invalid command, the shell will display en error message indicating the error type.
</p>

<h3>Usage</h3>
<hr>
<p>First, its necessary to compile it; to do this it's necessary to execute
the following line:
    gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
</p>
<h4>Interactive mode:</h4>
<code>[current directory]/hsh</code>
<p>Prompt:</p>
<code>$ [command insertion]</code>
<h4>Non-interactive mode:</h4>
<code>[input text or file] | ./hsh</code>

<h3>Flowchart</h3>
<hr>
<img src="https://github.com/Nanxuss/holbertonschool-simple_shell/blob/master/HSH%20flowchart.png?raw=true" width="600px">

<h3>Auxiliary functions</h3>
<hr>
<p>- args_isolator: this function make an array of string with the user input. <br>
- check_existance: this function check if the user enter a valid command. <br>
- function_caller: this function executes the command entered by the user. <br>
- free_exit: this function frees all the paths. <br>
</p>

<h3>Examples</h3>
<hr>
<img src="https://i.imgur.com/ZRfbghj.png" width="600px">
<img src="https://i.imgur.com/QiSWNnn.png" width="600px">
<img src="https://i.imgur.com/vOkoVGR.png" width="600px">

<h3>Authors</h3>
<hr>
<p>Gaston Larroque & Ivan Hansen - 2022 / Holberton School</p>
<p>See AUTHORS file in repo for contact info.</p>

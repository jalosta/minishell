*This project has been created as part of the 42 curriculum by jalosta-, synoshah*

# Description

*Minishell* is a project that asked us to recreate the core behaviors of the bash terminal from scratch in C.

# Instructions

Run **make** to compile. Launch the shell by running ./minishell to start using the custom shell.

Clean up using *make clean*. To remove the executable, run *make fclean*.

shell_loop -> readline -> process_input -> lexer -> check_syntax -> parse_input -> execute_cmds

# Resources

Manuals for readline, execve, fork, pipe, and errno.

Medium articles, Youtube videos, and the Wikipedia breakdown of bash architecture and the read–eval–print loop.

Wikipedia article of Read–eval–print loop

minishell_tester by LucasKuhn on git to test for edge cases.

Gemini for testing and proofreading the codebase before submission.

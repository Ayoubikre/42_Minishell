/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   road.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:46:28 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/12 15:46:36 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/* 
1. Input Capture
Goal: Get the raw command string from the user and prepare it for parsing.

Task 1: Set Up readline
Call readline with a prompt (e.g., "minishell$ ") to grab input (e.g., echo "hello $USER" | grep test > out).
Handle NULL (Ctrl+D) to exit the shell.
Skip empty input ("") and loop back to a new prompt.
Task 2: Add to History
Use add_history to store non-empty input for up/down arrow recall.
Ensure this happens before parsing but after validating the input.
Task 3: Initial Cleanup
Check for basic validity (e.g., not just spaces).
Pass the raw string to your tokenizer.


2. Tokenization
Goal: Break the input string into individual tokens using your t_token struct and t_token_type enum.

Task 1: Split the String
Scan the input character by character or use delimiters (spaces).
Respect quotes (' and ")—don’t split inside them, keep them in the token (e.g., "hello $USER" stays whole).
Task 2: Assign Token Types
Write get_token_type to map strings to t_token_type:
"|" → pipe
"<" → in
">" → out
"<<" → heredoc
">>" → append
"(" → left_bracket (optional for bonus)
")" → right_bracket (optional for bonus)
Anything else (e.g., "echo", "hello") → string (drop cmd for simplicity).
Task 3: Create Tokens
For each piece, call ft_creat_new_list with the string and its type.
Fix ft_creat_new_list:
malloc the t_token node and check for NULL.
Copy the string into n->value (e.g., with ft_strdup) instead of pointing to it.
Set type, next, and prev.
Task 4: Build the List
Use ft_add_list_end or ft_add_list_front to link tokens into a doubly linked list.
Add an end token as a sentinel.
Task 5: Handle Errors
Reject unclosed quotes (e.g., echo "hello)—scan for matching pairs.
Collapse multiple spaces (e.g., echo hello → echo, hello).
Output: A linked list of tokens, e.g., [string: echo], [string: "hello $USER"], [pipe: |], [string: grep], [string: test], [out: >], [string: out], [end].



3. Quote Handling
Goal: Process quoted tokens to prepare for expansion, keeping quotes until this step.

Task 1: Identify Quoted Tokens
Scan the token list for string tokens starting with ' or ".
Mark them with their quote type (e.g., add a flag to t_token or track separately).
Task 2: Validate Quotes
Ensure every opening quote has a closing one (already checked in tokenization, but double-check).
Reject invalid cases (subject says not to interpret unclosed quotes).
Task 3: Defer Interpretation
Keep quotes in value (e.g., "hello $USER") until the next step.
Note: Single quotes (') block all interpretation; double quotes (") allow $ expansion.
Output: Tokens tagged with quote info, still unprocessed (e.g., [string: "hello $USER"] marked as double-quoted).
4. Environment Variable Expansion
Goal: Expand $VAR and $? in unquoted or double-quoted string tokens.

Task 1: Scan for Variables
For each string token:
Skip if single-quoted (e.g., '$USER' stays literal).
Check for $ if unquoted or double-quoted (e.g., $USER, "hello $USER").
Task 2: Extract Variable Names
Parse after $ until a non-variable character (e.g., $USER → USER, $? → ?).
Handle edge cases (e.g., $ alone or $ABC123).
Task 3: Expand Values
For $VAR, use getenv to get the value (e.g., $USER → john).
For $?, get the last exit status (coordinate with your teammate—use a placeholder like 0 for now).
Replace the $VAR part with its value, keeping the rest of the string.
Task 4: Strip Quotes
Remove ' or " from the token’s value after expansion.
Example: "hello $USER" → hello john.
Task 5: Update Tokens
Allocate new value strings with expanded results (use malloc).
Free old value strings to avoid leaks.
Output: Expanded tokens, e.g., [string: echo], [string: hello john], [pipe: |], [string: grep], [string: test], [out: >], [string: out], [end].



5. Redirection Parsing
Goal: Identify and structure redirection operators with their targets.

Task 1: Find Redirections
Scan the token list for in, out, heredoc, append.
Ensure each has a following string token (e.g., > out).
Task 2: Pair with Targets
Link each operator to its next token (e.g., [out: >], [string: out] → {type: out, target: out}).
For heredoc, the next token is the delimiter (e.g., << EOF).
Task 3: Remove from List
Extract redirection pairs from the main token list.
Store them separately (e.g., in a t_redir struct or as part of a command).
Task 4: Validate
Check for missing targets (e.g., > alone is invalid).
Reject multiple redirections of the same type if bash does (optional—check reference).
Output: Tokens without redirections + a redirection list, e.g., [string: echo], [string: hello john], [pipe: |], [string: grep], [string: test], [end] + {out: out}.



6. Pipe Splitting
Goal: Divide the token list into separate commands based on pipes.

Task 1: Locate Pipes
Find pipe tokens in the list.
Task 2: Group Commands
Split tokens before and after each pipe into command units.
Example: [string: echo], [string: hello john], [pipe: |], [string: grep], [string: test] → {echo, [hello john]}, {grep, [test]}.
Task 3: Validate
Ensure no empty commands (e.g., | or echo | | grep might need rejection).
Task 4: Link Commands
Mark each command’s pipe connection (e.g., first command’s output goes to second).
Output: A list of command groups, e.g., {cmd: echo, args: [hello john], pipe_to: next}, {cmd: grep, args: [test]}.



7. Built-in Detection
Goal: Flag commands that are built-ins for special handling.

Task 1: Check Command Names
For each command group, test the first string against built-ins: echo, cd, pwd, export, unset, env, exit.
Task 2: Handle Special Cases
For echo, check the next token for -n and flag it.
For others, just mark as built-in with their args.
Task 3: Store the Info
Add a is_builtin flag or type to your command structure.
Output: Commands tagged, e.g., {cmd: echo, args: [hello john], is_builtin: yes, pipe_to: next}.
8. Signal Handling
Goal: Ensure parsing resets or exits cleanly on Ctrl+C/D/\.

Task 1: Set Up Signals
Use signal or sigaction with your global int g_signal to catch SIGINT (Ctrl+C), SIGQUIT (Ctrl+\), and EOF (Ctrl+D).
Task 2: Define Behavior
Ctrl+C: Set g_signal = SIGINT, discard current parsing, call rl_on_new_line and rl_redisplay, restart with new prompt.
Ctrl+D: If readline returns NULL, exit the parsing loop.
Ctrl+\: Set g_signal = SIGQUIT, do nothing (ignore).
Task 3: Integrate with Parsing
Check g_signal between parsing steps—reset if needed.



9. Final Structuring
Goal: Package everything into a format for execution.

Task 1: Define a Command Structure
Create a struct (e.g., t_command) with:
Command name (first string).
Args (remaining string tokens).
Redirections (from step 5).
Pipe connections (from step 6).
Built-in flag (from step 7).
Task 2: Build the Structure
Convert your token list into a list of t_command nodes.
Example: echo "hello $USER" | grep test > out → {cmd: echo, args: [hello john], pipe_to: next}, {cmd: grep, args: [test], redir: {out: out}}.
Task 3: Clean Up
Free the token list with ft_free_list after transferring to commands.
Ensure no memory leaks (free each value too).
Output: A linked list of commands ready for your teammate.



10. Testing and Debugging
Goal: Verify your parser works with all cases.

Task 1: Test Simple Commands
echo hello → [string: echo], [string: hello], [end].
Task 2: Test Quotes and Variables
echo "test $USER" '$HOME' → Expands to echo test john $HOME.
Task 3: Test Redirections and Pipes
cat < in | grep test > out → Correct command groups and redirs.
Task 4: Test Edge Cases
Unclosed quotes, multiple spaces, empty pipes, signals.
Task 5: Use Bash as Reference
Compare your parser’s behavior to bash for unclear spec points.
Your Journey TL;DR
Input Capture: Grab and store the raw string.
Tokenization: Split into typed tokens (keep quotes).
Quote Handling: Tag quoted tokens.
Variable Expansion: Expand $VAR and $?, strip quotes.
Redirection Parsing: Extract <, >, etc.
Pipe Splitting: Group into commands.
Built-in Detection: Flag echo, cd, etc.
Signal Handling: Handle Ctrl+C/D/\.
Final Structuring: Build command list.
Testing: Validate everything.
This roadmap covers your parsing role end-to-end. You’re already rolling with tokenization—next up could be fleshing out get_token_type or testing your token list. Where do you want to jump in?



*/
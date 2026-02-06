*This project has been created as part of the 42 curriculum by Aakritah & Anktiri.*

# 🐚 Minishell

A lightweight yet powerful implementation of a Unix shell, built from scratch in C. Minishell recreates the core functionality of bash, providing a fully interactive command-line interface that handles complex command parsing, process management, and inter-process communication.

## 📋 Description

Minishell is a fully functional shell that interprets and executes commands just like bash. This project represents one of the most challenging endeavors in the 42 curriculum, requiring deep understanding of Unix processes, file descriptors, and system-level programming. We built a complete command interpreter that lexes, parses, expands, and executes user input with proper signal handling and memory management.

## 🎯 The Challenge

Creating a mini version of bash was probably the biggest project in the 42 curriculum. The goal was to build a shell from scratch - one that doesn't just handle built-in commands, but acts as a complete command interpreter. We had to learn how bash takes arguments, parses them, and executes them. The project required implementing:

- **Display a prompt** while waiting for a new command
- **Working history** for command navigation
- **Find and launch executables** using the PATH variable or absolute/relative paths
- **Pipes** (`|`) for chaining commands
- **Environment variables** expansion and `$?` for exit status
- **Quote handling** - single (`'`) and double (`"`) quotes like in bash
- **Redirections**:
  - `<` redirect input
  - `>` redirect output  
  - `<<` heredoc (doesn't affect history)
  - `>>` redirect output in append mode
- **Signal handling** - `ctrl-C`, `ctrl-D`, and `ctrl-\` behaving like in bash
- **Built-in commands**:
  - `echo` with option `-n`
  - `cd` with only a relative or absolute path
  - `pwd` (no flags)
  - `export` (no flags)
  - `unset` (no flags)
  - `env` (no flags or arguments)
  - `exit` (no flags)
- **Wildcard support** - `*` expansion for the current working directory

When in doubt, we took bash as a reference, which sometimes led to discussions about whether we needed to implement something or not. The answer was usually "probably... yeah."

## 🏗️ How Bash Works - Our Implementation

The shell operates as a program that allows users to interact with the operating system's services. Bash is the GNU shell and the most common shell program. We took the challenge of recreating bash very literally, so the first thing we did was learn how bash actually works.

Essentially, bash breaks down command processing into **4 main stages**: **Lexer → Parser → Expander → Executor**, which we replicated in our project.

```
┌─────────────────┐      ┌─────────────┐      ┌─────────────┐      ┌──────────┐
│  Input String   │ ───► │   Lexer     │ ───► │   Parser    │ ───► │ Executor │
│ ls -l | grep a  │      │  (Tokens)   │      │ (Commands)  │      │          │
└─────────────────┘      └─────────────┘      └─────────────┘      └──────────┘
                                │                     │
                                │                     │
                         ┌──────▼────────┐    ┌──────▼──────────┐
                         │ Token Stream  │    │  Command Tree   │
                         │ ls, -l, |,    │    │  cmd: ls -l     │
                         │ grep, a       │    │  pipe           │
                         └───────────────┘    │  cmd: grep a    │
                                              └─────────────────┘
```

### 1️⃣ Lexer (Tokenization)

The lexer is the first stage of processing. It takes the raw input string and breaks it down into **tokens** - the smallest meaningful units.

**What it does:**
- Reads input character by character
- Identifies different token types: words, operators (`|`, `<`, `>`, `<<`, `>>`), quotes
- Handles quote contexts (everything inside quotes is treated as a single token)
- Separates metacharacters from regular characters

**Example:**
```
Input:  echo "hello world" | grep hello > out.txt
Tokens: [WORD: echo] [WORD: hello world] [PIPE: |] [WORD: grep] [WORD: hello] [REDIR_OUT: >] [WORD: out.txt]
```

### 2️⃣ Parser (Syntax Analysis)

The parser takes the token stream and organizes it into a **command structure** that can be executed.

**What it does:**
- Builds a command list from tokens
- Groups arguments with their commands
- Identifies and links redirections to commands
- Creates pipeline connections between commands
- Validates syntax (unclosed quotes, invalid redirections, etc.)

**Example:**
```
Tokens: [ls] [-l] [|] [grep] [minishell]

Parsed Structure:
  Command 1:
    - Program: "ls"
    - Args: ["-l"]
    - Has pipe: YES
  
  Command 2:
    - Program: "grep"
    - Args: ["minishell"]
    - Input: from previous pipe
```

### 3️⃣ Expander (Variable Expansion)

Before execution, the expander processes special characters and variables.

**What it does:**
- Expands environment variables (`$USER`, `$HOME`, `$PATH`)
- Handles `$?` (exit status of last command)
- Processes wildcards (`*`) in the current directory
- Respects quote contexts (no expansion in single quotes, partial in double quotes)

**Example:**
```
Before expansion: echo $USER is in $PWD
After expansion:  echo ayoub is in /home/ayoub/minishell

Before expansion: ls *.c
After expansion:  ls main.c lexer.c parser.c executor.c
```

### 4️⃣ Executor (Command Execution)

The executor is the final stage - it actually runs the commands.

**What it does:**
- Determines if command is built-in or external
- For built-ins: executes directly in the shell process
- For external commands:
  - Searches for executable in PATH or uses provided path
  - Creates child process using `fork()`
  - Sets up redirections and pipes with `dup2()`
  - Executes program with `execve()`
  - Parent waits for child with `waitpid()` and captures exit status
- Handles pipelines by chaining multiple processes

**Pipeline execution example:**
```
Command: ls -l | grep minishell | wc -l

Process tree:
  Parent (minishell)
    │
    ├─► Child 1: ls -l        (stdout → pipe1)
    │
    ├─► Child 2: grep         (stdin ← pipe1, stdout → pipe2)
    │
    └─► Child 3: wc -l        (stdin ← pipe2)
```

## 🔧 Implementation Architecture

Our project is organized into logical modules that mirror the bash processing pipeline:

### Core Components

**Lexer Module** (`lexer.c`, `tokenizer.c`)
- Character-by-character input processing
- Token type identification
- Quote context management
- Token list construction

**Parser Module** (`parser.c`, `parser_utils.c`)
- Syntax validation
- Command structure building
- Redirection parsing
- Pipeline construction

**Expander Module** (`expander.c`, `env_expansion.c`, `wildcard.c`)
- Environment variable lookup and expansion
- Exit status handling
- Wildcard pattern matching with `*`
- Quote-aware expansion

**Executor Module** (`executor.c`, `path_resolver.c`)
- Built-in command dispatcher
- External command execution
- Process creation and management
- Exit status collection

**Redirections** (`redirections.c`, `heredoc.c`)
- File descriptor manipulation
- Input/output file handling
- Heredoc implementation
- Append mode support

**Pipes** (`pipes.c`, `pipeline.c`)
- Pipe creation with `pipe()`
- File descriptor duplication
- Multi-command chaining
- Proper cleanup

**Signals** (`signals.c`, `signal_handlers.c`)
- `SIGINT` (Ctrl-C) - new prompt
- `SIGQUIT` (Ctrl-\) - ignored
- EOF (Ctrl-D) - exit shell
- Different behavior in interactive vs heredoc mode

**Built-ins** (`builtins/`)
- `cd`, `pwd`, `echo`, `env`, `export`, `unset`, `exit`
- Each built-in executes in the main shell process (no fork)
- Direct manipulation of shell environment

**Environment** (`env.c`, `env_utils.c`)
- Environment variable storage and management
- Variable creation, modification, deletion
- Environment array maintenance for `execve()`

## 🚀 Getting Started

### Compilation

Clone the repository and compile the project:

```bash
git clone https://github.com/Ayoubikre/42_Minishell.git
cd 42_Minishell
make
```

The Makefile includes:
- `make` or `make all` - Compiles the project
- `make clean` - Removes object files
- `make fclean` - Removes object files and executable
- `make re` - Recompiles everything from scratch

### Running Minishell

```bash
./minishell
```

You'll see a prompt waiting for your commands!

## 💡 Usage Examples

**Basic commands:**
```bash
minishell$ ls -la
minishell$ pwd
minishell$ echo Hello, World!
minishell$ cat file.txt
minishell$ /bin/ls
```

**Pipelines:**
```bash
minishell$ ls -l | grep minishell
minishell$ cat file.txt | grep "search" | sort | uniq -c
minishell$ echo "test" | wc -l
```

**Redirections:**
```bash
minishell$ echo "Hello" > output.txt
minishell$ cat < input.txt
minishell$ ls -l >> append.txt
minishell$ cat << EOF
> line 1
> line 2  
> EOF
```

**Environment variables:**
```bash
minishell$ echo $USER
minishell$ echo $HOME
minishell$ echo $?          # Exit status of last command
minishell$ export MY_VAR=hello
minishell$ echo $MY_VAR
minishell$ unset MY_VAR
```

**Wildcards:**
```bash
minishell$ ls *.c
minishell$ echo test_*
minishell$ cat *.txt
```

**Quote handling:**
```bash
minishell$ echo 'Single quotes: $USER not expanded'
minishell$ echo "Double quotes: $USER expanded to actual value"
minishell$ echo "You can 'mix' quotes"
```

**Complex combinations:**
```bash
minishell$ < input.txt grep "search" | sort > output.txt
minishell$ export PATH="/custom/path:$PATH"
minishell$ echo *.c | tr ' ' '\n' | wc -l
minishell$ cat << EOF | grep hello | wc -l
> hello world
> test hello
> EOF
```

## 🔥 Technical Challenges & Solutions

### Process Management
**Challenge:** Executing external commands while maintaining shell state.  
**Solution:** Used `fork()` to create child processes, `execve()` to replace process image with the target program, and `waitpid()` in the parent to collect exit status without blocking other operations.

### File Descriptor Juggling
**Challenge:** Managing multiple redirections and pipes without leaking file descriptors.  
**Solution:** Implemented systematic `dup2()` to redirect stdin/stdout/stderr, ensured all pipes are closed in appropriate processes, and maintained file descriptor tracking across command chains.

### Signal Handling
**Challenge:** Different signal behavior in different contexts (interactive vs heredoc).  
**Solution:** Used `sigaction()` with a single global variable to store signal numbers. Implemented signal blocking during critical sections and context-aware handlers that adjust behavior based on shell state.

### Memory Management
**Challenge:** No memory leaks across complex command execution with dynamic allocations.  
**Solution:** Implemented consistent cleanup routines, used valgrind extensively for leak detection, and ensured all malloc'd memory is freed even in error paths. (Note: readline library leaks are acceptable per project requirements)

### Quote Parsing
**Challenge:** Correctly handling nested quotes and metacharacter escaping.  
**Solution:** State machine in lexer tracking quote context (none, single, double), respecting expansion rules within each context.

### Wildcard Expansion
**Challenge:** Expanding `*` patterns correctly in current directory.  
**Solution:** Used `opendir()`, `readdir()` to iterate directory entries, implemented pattern matching algorithm, expanded matches while preserving other tokens.

## ⚙️ Key Technical Concepts

### Pipes & File Descriptors
Pipes are special files with two file descriptors: one for reading, one for writing. We create pipes with `pipe()`, duplicate them onto stdin/stdout with `dup2()`, and close unused ends in each process.

```c
int pipefd[2];
pipe(pipefd);      // pipefd[0] = read end, pipefd[1] = write end

// In child 1 (writer):
dup2(pipefd[1], STDOUT_FILENO);  // stdout → pipe write
close(pipefd[0]);                 // close unused read end
close(pipefd[1]);                 // close original write fd

// In child 2 (reader):
dup2(pipefd[0], STDIN_FILENO);   // stdin ← pipe read
close(pipefd[1]);                 // close unused write end
close(pipefd[0]);                 // close original read fd
```

### Signal Safety
Signals can interrupt execution at any time. We ensure safety by:
- Using only async-signal-safe functions in handlers
- Storing only the signal number in a global `volatile sig_atomic_t`
- Blocking signals during critical sections with `sigprocmask()`
- Never accessing complex data structures from handlers

### Environment Management
The shell maintains its own environment separately from the system environment. When a variable is exported, it's added to both our internal list and the environment array passed to `execve()`.

## 🎓 What We Learned

- **Process control**: Deep understanding of fork, exec, wait family of system calls
- **Inter-process communication**: Pipes, file descriptors, and how processes communicate
- **Parsing techniques**: Lexical analysis, syntax parsing, building executable structures
- **Signal handling**: Asynchronous signals, signal safety, context management  
- **Memory management**: Dynamic allocation, cleanup, leak prevention
- **Error handling**: Comprehensive error checking, graceful failure, user feedback
- **System programming**: Low-level Unix APIs, understanding how shells work internally
- **Team collaboration**: Code organization, Git workflows, peer programming

## 📚 Resources

### Essential Documentation
- [**GNU Bash Manual**](https://www.gnu.org/software/bash/manual/) - The definitive bash reference
- [**Linux man pages**](https://man7.org/linux/man-pages/) - System call documentation
- [**Advanced Programming in the UNIX Environment**](https://stevens.netmeister.org/631/) - The bible of Unix programming

### Understanding Shells
- [Writing Your Own Shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf) - Academic guide to shell implementation
- [Beej's Guide to Unix IPC](https://beej.us/guide/bgipc/) - Inter-process communication explained
- [How Bash Works](https://panix.com/~elflord/unix/bash-tute.html) - Understanding bash internals

### Specific Topics
- **Pipes & Redirections**: Linux pipe(2), dup2(2), open(2) man pages
- **Process Management**: fork(2), execve(2), waitpid(2), exit(3)
- **Signal Handling**: signal(7), sigaction(2), sigprocmask(2)
- **File Descriptors**: Understanding Unix I/O model
- **Parsing**: Lexical analysis and recursive descent parsing

### Debugging & Testing
- **Valgrind**: `valgrind --leak-check=full --show-leak-kinds=all ./minishell`
- **GDB**: For debugging segfaults and understanding process flow
- **Bash comparison**: Always test against real bash behavior

## 📝 Project Notes

- **Readline leaks**: The readline library may produce memory leaks that are not required to be fixed per the subject
- **Global variable restriction**: Only one global variable is allowed, used exclusively for signal number storage
- **Bash as reference**: When in doubt about behavior, bash is the definitive reference
- **No support for**: `\` (backslash), `;` (semicolon), `&&`, `||` (except wildcards `*` which we implemented)
- **Testing**: Extensively tested against bash for identical behavior

## 🏆 Project Stats

- **Team Size**: Group project (typically 2 students)
- **Development Time**: ~3-4 weeks of intensive work
- **Lines of Code**: ~3000-5000 lines of C
- **Functions Used**: 40+ system calls and library functions
- **Difficulty**: Advanced (one of the hardest projects in the 42 common core)

---

*This project pushed our understanding of Unix systems to the limit. It's not just about making commands work - it's about understanding how a shell actually thinks. Every edge case we handled taught us something new about process management, parsing, or Unix design philosophy.*

*For questions or issues, feel free to open an issue on the [repository](https://github.com/Ayoubikre/42_Minishell).*
# Pipex

## Project Overview

The project focuses on learning processes, pipes, and I/O redirections in Unix-like operating systems.

The program, `pipex`, is designed to mimic the following shell command:

```bash
< file1 cmd1 | cmd2 > file2
```

Where:
- `file1` and `file2` are file names.
- `cmd1` and `cmd2` are shell commands with their arguments.

## How to Use

The program should be executed with the following syntax:

```bash
./pipex file1 cmd1 cmd2 file2
```

This command will:
1. Redirect standard input to `file1`.
2. Execute `cmd1` with its arguments, using the contents of `file1` as input.
3. Pipe the output of `cmd1` to `cmd2`.
4. Redirect standard output to `file2`.

### Example Usage

1. **Example 1:**

   ```bash
   $> ./pipex infile "ls -l" "wc -l" outfile
   ```

   This command is equivalent to:

   ```bash
   $> < infile ls -l | wc -l > outfile
   ```

   It lists the files in the directory specified by `infile`, pipes the output to `wc -l`, and writes the result (the number of lines) to `outfile`.

2. **Example 2:**

   ```bash
   $> ./pipex infile "grep a1" "wc -w" outfile
   ```

   This command is equivalent to:

   ```bash
   $> < infile grep a1 | wc -w > outfile
   ```

   It searches for the string "a1" in `infile`, pipes the matching lines to `wc -w`, and writes the word count to `outfile`.

## Error Handling

The program should handle errors in the same way as the shell command. This includes:
- Checking the validity of the provided file names.
- Ensuring that the commands execute successfully.
- Properly managing file descriptors to avoid resource leaks.

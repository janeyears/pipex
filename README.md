# pipex

**pipex** is a Hive project that introduces inter-process communication using Unix pipes. The goal is to reproduce the shell behavior of piping commands together (`< infile cmd1 | cmd2 > outfile`), deepening your understanding of process creation, file descriptors, and system calls in C.

## 🚀 Project Overview

The objective of pipex is to simulate shell pipelines by creating a program that takes input from a file, processes it through two commands connected via a pipe, and writes the output to another file.

Through this project, I learned to:

- Use `fork`, `execve`, `pipe`, `dup2`, and other system calls
- Manage file descriptors and I/O redirection
- Handle environment paths to locate executable commands
- Create robust error handling in a Unix environment

## 📁 Project Structure

### ✅ Mandatory Part

Implement a program with the following usage:

./pipex infile cmd1 cmd2 outfile

Behavior:

Opens infile and redirects its content into cmd1.
Pipes the output of cmd1 into cmd2.
Redirects the output of cmd2 into outfile.
The project replicates this shell command:
< infile cmd1 | cmd2 > outfile

## 🔧 Compilation & Usage
A Makefile is provided for building the project.

## 🧠 What I Learned

- Working with low-level process control (fork, execve, wait)
- Setting up and managing pipes for inter-process communication
- Using dup2 to redirect standard input/output
- Parsing command-line arguments and handling PATH resolution
- Properly managing resources and avoiding leaks or descriptor issues

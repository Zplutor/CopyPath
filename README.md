# CopyPath

## Introduction

We usually need to copy a file path or a file name into the clipboard. Unfortunately, there is no built-in mechanism to helps us to achieve this simple goal conveniently. So I create this tiny tool. After installing, it will add two items, "Copy path" and "Copy name" to the context menu of files and directories - they are very handy. 

## Usage 

Firstly, you need to build the solution with `Release` configuration.

Secondly, run `Install.bat` to install it. The script would modifies the register table using the path of `CopyPath.exe` in `Release` directory. If you desire an alternative path, copy `CopyPath.exe` to another directory, and modify `exe_path` varible in `Install.bat` to point to this file. For example:
```
set exe_path="C:\Windows\CopyPath.exe"
```

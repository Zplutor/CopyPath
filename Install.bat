@echo off

set exe_path="%~dp0Release\CopyPath.exe"

if not exist %exe_path% (
	echo %exe_path% not found. 
	echo Please build the solution with release configuration, 
	echo   or modify this script to point to an existent executable file.
	echo Install failed.
	goto :end
)

set reg_path=HKEY_CURRENT_USER\Software\Classes

reg add %reg_path%\*\shell\CopyPath /f /ve /d "Copy path"
reg add %reg_path%\*\shell\CopyPath\command /f /ve /d "%exe_path% -p \"%%1\""
reg add %reg_path%\*\shell\CopyName /f /ve /d "Copy name"
reg add %reg_path%\*\shell\CopyName\command /f /ve /d "%exe_path% -n \"%%1\""

reg add %reg_path%\Folder\shell\CopyPath /f /ve /d "Copy path"
reg add %reg_path%\Folder\shell\CopyPath\command /f /ve /d "%exe_path% -p \"%%1\""
reg add %reg_path%\Folder\shell\CopyName /f /ve /d "Copy name"
reg add %reg_path%\Folder\shell\CopyName\command /f /ve /d "%exe_path% -n \"%%1\""

echo Install succeeded.

:end
pause

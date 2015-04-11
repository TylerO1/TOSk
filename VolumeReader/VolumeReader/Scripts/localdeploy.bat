@echo off
REM ********************************************************************
REM <license>
REM Copyright (c) 2013, Omar Francisco
REM All rights reserved.
REM 
REM Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
REM 
REM Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
REM Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
REM Neither the name of the <ORGANIZATION> nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
REM THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
REM </license>

REM <filehistory>
REM 08/24/2012 - Omar Francisco - Created
REM </filehistory>
REM ********************************************************************

REM ********************************************************************
REM <documentation>
REM localdeploy.bat excutes batch file with the names local-deployxx.bat in reverse order.  XX is a number
REM between 99 and 00.  This scheme supports up to 100 scripts to run during the pre-build event.
REM
REM List of supported parameters
REM %1 = Solution Directory
REM %2 = Project Directory
REM %3 = AVRDude Path
REM %4 = AVRConfig Path
REM %5 = ATProgram Path
REM %6 = Library Path
REM %7 = Header Path
REM %8 = future1
REM %9 = future2
REM To add additional parameters go to project/properties build events. The same parameters have to be copied for both release and debug configurations.
REM
REM </documenation>
REM ********************************************************************

REM Copy parameters
set P1=%1
set P2=%2
set P3=%3
set P4=%4
set P5=%5
set P6=%6
set P7=%7
set P8=%8
set P9=%9

REM calling sequence
call :SETUP
call :DEBUG
call :MAIN
goto :END

:SETUP
REM ********************************************************************
REM script initialization
set FILE_PATTERN=local-deploy*.bat
set DEBUG_FLAG="OFF"

REM Change to the directory where the script file is running
cd /d %~dp0
goto :END
REM ********************************************************************


:DEBUG
REM ********************************************************************
if %DEBUG_FLAG%=="ON" (
echo ****************************************
echo DEBUG MODE ON - File:%~n0%~x0
echo ****************************************
echo File Pattern: %FILE_PATTERN%
echo Solution Directory: %P1%
echo Project Directory: %P2%
echo AVRDUDE Path: %P3%
echo AVRDUDE Config: %P4%
echo ATPROGRAM Path: %P5%
echo Library Path: %P6%
echo Header Path: %P7%
echo Future1: %P8%
echo Future2: %P9%
echo Current Directory: %CD%
FOR /F "tokens=*" %%G IN ('dir /b %FILE_PATTERN% /O-N') DO ( echo will call %%G %P1% %P2% %P3% %P4% %P5% %P6% %P7% %P8% %P9%)
echo ****************************************
)
goto :END
REM ********************************************************************

:MAIN
REM ********************************************************************
REM - Exectue all batch files matching filepattern in descending order
FOR /F "tokens=*" %%G IN ('dir /b %FILE_PATTERN% /O-N') DO (
	echo Executing %%G
	call %%G %P1% %P2% %P3% %P4% %P5% %P6% %P7% %P8% %P9%
)
goto :END
REM ********************************************************************

:END






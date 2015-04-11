Setlocal EnableDelayedExpansion
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
REM 05/11/2013 - Omar Francisco - Modified to use boards.xml to drive transfering program to board
REM </filehistory>
REM ********************************************************************

REM ********************************************************************
REM <documentation>
REM local-deploy98.bat deploys the binary file to the target device
REM
REM List of supported parameters
REM %1 = Solution Directory
REM %2 = Project Directory
REM To add additional parameters go to project/properties build events. 
REM The same parameters have to be copied for both release and debug configurations.
REM
REM </documenation>
REM ********************************************************************

REM Copy parameters
set P1=%1
set P2=%2

REM Change to the directory where the script file is running
cd /d %~dp0

REM COPY paramaeters and drop quotes
SET SOLUTION_DIR=%~1%
SET PROJECT_DIR=%~2%
SET LOCALBOARDS=targetboards.xml
SET XMLTOOL="%ATE_HOME%\TOOLS\XML.EXE"
set GLOBALBOARDS="%ATE_HOME%\boards.xml"
set NAMESPACE="http://schemas.microsoft.com/developer/msbuild/2003"
set TEMPDATA=tempdata.txt

REM calling sequence
call :SETUP
call :DEBUG
call :MAIN
goto :END

:SETUP
REM ********************************************************************
REM script initialization

REM Deploy Location (STAGE|LIBDIR)
REM STAGE deploys to the stage directory within the solution
REM LIBDIR deploys to the centralized library directory
set DEPLOY_LOCATION=STAGE

REM Allowed values "ON"|"OFF"
set DEBUG_FLAG="ON"

if NOT EXIST %LOCALBOARDS% (
  echo Local board definition "%LOCALBOARDS%" was not FOUND - Script will be aboarted
  set ABORT_SCRIPT="TRUE"
  goto :END
)

if NOT EXIST %GLOBALBOARDS% (
  echo Global board definition "%GLOBALBOARDS%" was not FOUND - Script will be aboarted
  set ABORT_SCRIPT="TRUE"
  goto :END
)

if NOT EXIST %XMLTOOL% (
  echo XML tool "%XMLTOOL%" was not FOUND - Script will be aboarted
  set ABORT_SCRIPT="TRUE"
  goto :END
)

REM Get target board 
%XMLTOOL% sel -N x=%NAMESPACE% -t -v "/x:Project/x:ItemGroup/x:CurrentBoard/x:Name" %LOCALBOARDS% > %TEMPDATA%
set /p TARGET_BOARD=< %TEMPDATA%

REM Get target programmer
%XMLTOOL% sel -N x=%NAMESPACE% -t -v "/x:Project/x:ItemGroup/x:CurrentBoard/x:Programmer" %LOCALBOARDS% > %TEMPDATA%
set /p TARGET_PROGRAMMER=< %TEMPDATA%

REM Get local misc parameters for program transfer
%XMLTOOL% sel -N x=%NAMESPACE% -t -v "/x:Project/x:ItemGroup/x:CurrentBoard/x:MiscParams" %LOCALBOARDS% > %TEMPDATA%
set /p LOCAL_MISC_PARAMS=< %TEMPDATA%

REM Get local misc parameters for program transfer
%XMLTOOL% sel -N x=%NAMESPACE% -t -v "/x:Project/x:ItemGroup/x:CurrentBoard/x:OverrideVerbosity" %LOCALBOARDS% > %TEMPDATA%
set /p OVERRIDE_VERBOSITY=< %TEMPDATA%

REM Get local misc parameters for library directory
%XMLTOOL% sel -N x=%NAMESPACE% -t -v "/x:Project/x:ItemGroup/x:CurrentBoard/x:FrequencyDirectory" %LOCALBOARDS% > %TEMPDATA%
set /p LIB_DIR_FROM_FREQUENCY=< %TEMPDATA%


REM Get Target communication port
%XMLTOOL% sel -N x=%NAMESPACE% -t -v "/x:Project/x:ItemGroup/x:Programmer[@Include='%TARGET_PROGRAMMER%']/x:ComPort" %GLOBALBOARDS% > tempdata.txt
set /p PROGRAMMER_COMPORT=< tempdata.txt

REM Get communication port speed
%XMLTOOL% sel -N x=%NAMESPACE% -t -v "/x:Project/x:ItemGroup/x:Programmer[@Include='%TARGET_PROGRAMMER%']/x:ComPortSpeed" %GLOBALBOARDS% > tempdata.txt
set /p PROGRAMMER_COMPORT_SPEED=< tempdata.txt

REM Get communication port speed
%XMLTOOL% sel -N x=%NAMESPACE% -t -v "/x:Project/x:ItemGroup/x:Programmer[@Include='%TARGET_PROGRAMMER%']/x:ProgTransfer" %GLOBALBOARDS% > tempdata.txt
set /p PROGRAM_TRANSFER=< tempdata.txt

REM Get communication protocol
%XMLTOOL% sel -N x=%NAMESPACE% -t -v "/x:Project/x:ItemGroup/x:Programmer[@Include='%TARGET_PROGRAMMER%']/x:Protocol" %GLOBALBOARDS% > tempdata.txt
set /p PROGRAMMER_PROTOCOL=< tempdata.txt

REM Get EEPROM transfer support
%XMLTOOL% sel -N x=%NAMESPACE% -t -v "/x:Project/x:ItemGroup/x:Programmer[@Include='%TARGET_PROGRAMMER%']/x:SupportEEPROMTransfer" %GLOBALBOARDS% > tempdata.txt
set /p PROGRAMMER_EEPROM_SUPPORT=< tempdata.txt

REM Get transfer verbosity
IF "%OVERRIDE_VERBOSITY%" == "" ( 
%XMLTOOL% sel -N x=%NAMESPACE% -t -v "/x:Project/x:ItemGroup/x:Programmer[@Include='%TARGET_PROGRAMMER%']/x:Verbosity" %GLOBALBOARDS% > tempdata.txt
set /p PROGRAM_TRANSFER_VERBOSITY=< tempdata.txt
) else (
echo OVERRIDING program transfer verbosity witn %OVERRIDE_VERBOSITY%
set PROGRAM_TRANSFER_VERBOSITY=%OVERRIDE_VERBOSITY%
)

REM Get miscelaneous parameters for program transfer
%XMLTOOL% sel -N x=%NAMESPACE% -t -v "/x:Project/x:ItemGroup/x:Programmer[@Include='%TARGET_PROGRAMMER%']/x:MiscParams" %GLOBALBOARDS% > tempdata.txt
set /p PROGRAM_TRANSFER_PARAMS=< tempdata.txt

REM Get communication protocol
%XMLTOOL% sel -N x=%NAMESPACE% -t -v "/x:Project/x:ItemGroup/x:ProgTransfer[@Include='%PROGRAM_TRANSFER%']/x:Path" %GLOBALBOARDS% > tempdata.txt
set /p PROGRAM_TRANSFER_PATH=< tempdata.txt

REM Get communication protocol
%XMLTOOL% sel -N x=%NAMESPACE% -t -v "/x:Project/x:ItemGroup/x:ProgTransfer[@Include='%PROGRAM_TRANSFER%']/x:Config" %GLOBALBOARDS% > tempdata.txt
set /p PROGRAM_TRANSFER_CONFIG=< tempdata.txt


REM File containing the name of the visual studio project - created during preprocessing
set PROJECT_FILE="%PROJECT_DIR%scripts\project.txt"

REM File containing the name of the program that was compiled - created during preprocessing
set OUTPUT_FILE="%PROJECT_DIR%scripts\output.txt"

REM File containing the name of the targeted AVR device - created during preprocessing
set DEVICE_FILE="%PROJECT_DIR%scripts\device.txt"

REM Visual Studio configuration (Release/Debug) - created during preprocessing
set CONFIG_FILE="%PROJECT_DIR%scripts\config.txt"

REM Get the project name, binary file, device and configuration - there is no error checking
set /p PROJECT_NAME= <%PROJECT_FILE%
set /p BINARY_FILE= <%OUTPUT_FILE%



set /p AVRPROCESSOR= <%DEVICE_FILE%
set /p CONFIGURATION= <%CONFIG_FILE%

set BINARY_FILE=%BINARY_FILE:"=%
REM Get hex file name and path
SET DESTINATION_FILE=%BINARY_FILE:.a=%
if "%CONFIGURATION%"=="Debug" ( set DESTINATION_FILE=%DESTINATION_FILE%d.a) else ( set DESTINATION_FILE=%DESTINATION_FILE%.a)

SET BINARY_FILE_PATH="%PROJECT_DIR%%CONFIGURATION%\%BINARY_FILE%"

REM File keeping track of how many sucessfull builds have been done to the project
set BUILD_COUNTER_FILE=buildcounter.txt
set BUILD_COUNTER=0
if exist %BUILD_COUNTER_FILE% ( set /p BUILD_COUNTER= <%BUILD_COUNTER_FILE% )

REM Header path for Arduino board
set ARDUINO_LIBS_HEADER_DIR=%ATE_HOME%\Boards\%TARGET_BOARD%\Headers
set STAGE_HEADER_DIR=%SOLUTION_DIR%_Stage\%TARGET_BOARD%\Headers
set SOLUTION_STAGE=%SOLUTION_DIR%_Stage
rem set PROJECT_STAGE=%PROJECT_DIR%_Stage
rem if EXIST "%SOLUTION_STAGE%" ( rmdir %SOLUTION_STAGE% /S /Q )
rem if EXIST "%PROJECT_STAGE%" ( rmdir %PROJECT_STAGE% /S /Q )

REM Full path of binary file
SET ARDUINO_LIBS_DIR=%ATE_HOME%\Boards\%TARGET_BOARD%\Libs\%LIB_DIR_FROM_FREQUENCY%
SET STAGE_LIBS_DIR=%SOLUTION_DIR%_Stage\%TARGET_BOARD%\Libs\%LIB_DIR_FROM_FREQUENCY%

echo ----------------------------------------------------------
echo Deploying %PROJECT_NAME% - Build %BUILD_COUNTER% - Deployment: %DEPLOY_LOCATION% - Target Device: %AVRPROCESSOR%

goto :END
REM ********************************************************************


:DEBUG
REM ********************************************************************
if %DEBUG_FLAG%=="ON" (
echo ****************************************
echo DEBUG MODE ON - File:%~n0%~x0
echo ****************************************
echo Solution Directory: "%SOLUTION_DIR%"
echo Project Directory: "%PROJECT_DIR%"
echo Target Board: %TARGET_BOARD%
echo Target Programmer: %TARGET_PROGRAMMER%
echo Com Port: %PROGRAMMER_COMPORT%
echo Com Port Speed: %PROGRAMMER_COMPORT_SPEED%
echo Allow EEPROM transfer:%PROGRAMMER_EEPROM_SUPPORT%
echo Prog Transfer: %PROGRAM_TRANSFER%
echo Transfer Protocol: %PROGRAMMER_PROTOCOL%
echo Prog Transfer Path: "%PROGRAM_TRANSFER_PATH%"
echo Prog Transfer Config: "%PROGRAM_TRANSFER_CONFIG%"
echo Prog Trasfer Verbosity: %PROGRAM_TRANSFER_VERBOSITY%
echo Misc Parameters: %PROGRAM_TRANSFER_PARAMS%
echo Local Misc Parameters: %LOCAL_MISC_PARAMS%
echo Template Express Home: "%ATE_HOME%"
echo Library Path: "%ARDUINO_LIBS_DIR%"
echo Header Path: "%ARDUINO_LIBS_HEADER_DIR%"
echo Configuration: %CONFIGURATION%
echo Target Device: %AVRPROCESSOR%
echo Project Name:%PROJECT_NAME%
echo Output File: %BINARY_FILE%
echo Library Path: %BINARY_FILE_PATH%
echo.
echo.

if exist %PROJECT_FILE% (echo Input Project File: %PROJECT_FILE% [CHECKED]) else (echo Input Project File: %PROJECT_FILE% [NOT FOUND])
if exist %DEVICE_FILE% (echo Input Device File: %DEVICE_FILE% [CHECKED]) else (echo Input Device File: %DEVICE_FILE% [NOT FOUND])
if exist %CONFIG_FILE% (echo Input Config File: %CONFIG_FILE% [CHECKED]) else (echo Input Config File: %CONFIG_FILE% [NOT FOUND])
if exist "%SOLUTION_DIR%" (echo Solution Directory:%SOLUTION_DIR% [CHECKED]) else (echo Solution Directory:%SOLUTION_DIR% [NOT FOUND])
if exist "%PROJECT_DIR%" (echo Project Directory:%PROJECT_DIR% [CHECKED]) else (echo Project Directory:%PROJECT_DIR% [NOT FOUND])

if exist %BINARY_FILE_PATH% (echo Binary File: %BINARY_FILE_PATH% [CHECKED]) else (echo Binary File: %BINARY_FILE_PATH% [NOT FOUND])
if exist "%ARDUINO_LIBS_HEADER_DIR%" (echo Arduino Library Header Path:%ARDUINO_LIBS_HEADER_DIR% [CHECKED]) else (echo Arduino Library Header Path:%ARDUINO_LIBS_HEADER_DIR% [NOT FOUND])
if exist "%ARDUINO_LIBS_DIR%" (echo Arduino Library Path:%ARDUINO_LIBS_DIR% [CHECKED]) else (echo Arduino Library Path:%ARDUINO_LIBS_DIR% [NOT FOUND])

if NOT EXIST "%PROJECT_FILE%" (
  echo CANNOT Find project directory "%PROJECT_FILE%" - Aborting script
  goto :END
)

if NOT EXIST "%DEVICE_FILE%" (
  echo CANNOT Find device file "%DEVICE_FILE%" - Aborting script
  goto :END
)


if NOT EXIST "%CONFIG_FILE%" (
  echo CANNOT Find config file "%CONFIG_FILE%" - Aborting script
  goto :END
)

if NOT EXIST "%SOLUTION_DIR%" (
  echo CANNOT Find solution directory "%SOLUTION_DIR%" - Aborting script
  goto :END
)

if NOT EXIST "%PROJECT_DIR%" (
  echo CANNOT Find project directory %PROJECT_DIR% - Aborting script
  goto :END
)

if NOT EXIST "%ARDUINO_LIBS_DIR%" (
  echo [WARNING] CANNOT Find project directory "%ARDUINO_LIBS_DIR%"
  rem goto :END
)

if NOT EXIST "%ARDUINO_LIBS_HEADER_DIR%" (
  echo [WARNING] CANNOT Find header directory "%ARDUINO_LIBS_HEADER_DIR%"
  rem goto :END
)

if NOT EXIST "%BINARY_FILE_PATH%" (
  echo CANNOT Find Binary File path "%BINARY_FILE_PATH%" - Aborting script
  goto :END
)
echo ****************************************
)
goto :END
REM ********************************************************************

:MAIN
REM ********************************************************************

rem ABORT if something failed during setup
if "%ABORT_SCRIPT%"=="TRUE" goto :END

echo Library Path: %BINARY_FILE_PATH%

REM branch to one of the supported program transfers
if "%DEPLOY_LOCATION%"=="STAGE" (
	echo STAGE DEPLOYMENT
	set DEPLOY_HEADER_DIR="%STAGE_HEADER_DIR%"
	set DEPLOY_LIB_DIR=%STAGE_LIBS_DIR%
	goto :DEPLOY_LIB
)

REM branch to one of the supported program transfers
if "%DEPLOY_LOCATION%"=="LIBDIR" (
	set DEPLOY_HEADER_DIR="%ARDUINO_LIBS_HEADER_DIR%"
	set DEPLOY_LIB_DIR=%ARDUINO_LIBS_DIR%
	goto :DEPLOY_LIB
)

echo [ERROR] Invalid program transfer detected [%DEPLOY_LOCATION%] - Aborting Script
goto :END

:DEPLOY_LIB
xcopy /s /Y /I ..\*.h %DEPLOY_HEADER_DIR% 
if %ERRORLEVEL%==1 goto :DEPLOYMENT_FAILED

REM HACK - get rid of stupid "does .... specifiy a file name or directory error from excopy"
if NOT EXIST "%DEPLOY_LIB_DIR%" ( md "%DEPLOY_LIB_DIR%" )
echo.>"%DEPLOY_LIB_DIR%\%DESTINATION_FILE%"
xcopy %BINARY_FILE_PATH% "%DEPLOY_LIB_DIR%\%DESTINATION_FILE%" /Y /I > nul

if %ERRORLEVEL%==1 goto :DEPLOYMENT_FAILED
echo.
goto :DEPLOYMENT_COMPLETE
goto :END

:DEPLOYMENT_FAILED
echo Deployment Failed
call deployfail.bat %1 %2 %3 %4 %5 %6 %7 %8 %9
goto :END


:DEPLOYMENT_COMPLETE
echo Deployment Complete
call deploysuccess.bat %1 %2 %3 %4 %5 %6 %7 
goto :END
REM ********************************************************************



:END
























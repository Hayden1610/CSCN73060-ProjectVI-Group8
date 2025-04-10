@echo off
SETLOCAL ENABLEEXTENSIONS
 
SET "FILE=Telem_2023_3_12 16_26_4.txt"
SET "COUNT=25"
SET /A "OFFSET=1000"
SET /A "INDEX=1"
 
:spawn_loop
IF %INDEX% LEQ %COUNT% (
    SET /A "AIRCRAFT_ID=OFFSET + INDEX"
    CALL START /MIN Client.exe -id %%AIRCRAFT_ID%% -f "%FILE%"
    SET /A INDEX+=1
    GOTO spawn_loop
)
 
ENDLOCAL

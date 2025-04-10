@echo off
SETLOCAL ENABLEDELAYEDEXPANSION
SET "FILENAME=Telem_2023_3_12 16_26_4.txt"
SET /A "batchSize=100"
SET /A "totalClients=1000"

SET /A "index=1"

:outer
IF !index! LEQ !totalClients! (
    SET /A "batchEnd=index + batchSize - 1"
    IF !batchEnd! GTR !totalClients! SET batchEnd=!totalClients!

    echo Starting clients !index! to !batchEnd! at %time%

    :inner
    IF !index! LEQ !batchEnd! (
        START /MIN "" Client.exe -id !index! -f "%FILENAME%"
        echo Started client !index!
        SET /A index += 1
        GOTO inner
    )

    timeout /t 10 > NUL
    GOTO outer
)

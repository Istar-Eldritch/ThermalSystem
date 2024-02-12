#!/bin/bash

cmd.exe /c rmdir "C:\Program Files (x86)\Steam\steamapps\common\DayZ\IE" /s /q
cmd.exe /c rmdir "P:\IE" /s /q

# Community Framework

cmd.exe /c rmdir "P:\JM\COT"
cmd.exe /c rmdir "C:\Program Files (x86)\Steam\steamapps\common\DayZ\JM"
cmd.exe /c rmdir "P:\JM"

# Liquid Framework
cmd.exe /c rmdir "P:\rag" /s /q

/mnt/c/Program\ Files\ \(x86\)/Steam/steamapps/common/DayZ\ Tools/Bin/WorkDrive/WorkDrive.exe /Dismount P

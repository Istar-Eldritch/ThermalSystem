#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

/mnt/c/Program\ Files\ \(x86\)/Steam/steamapps/common/DayZ\ Tools/Bin/WorkDrive/WorkDrive.exe /Mount P \
  "$(wslvar USERPROFILE)\Documents\DayZData"

cmd.exe /c mkdir "C:\Program Files (x86)\Steam\steamapps\common\DayZ\IE"
cmd.exe /c mklink /J "C:\Program Files (x86)\Steam\steamapps\common\DayZ\IE\ThermalSystem" "$(wslpath -w "$SCRIPT_DIR/..")"
cmd.exe /c mkdir "P:\IE"
cmd.exe /c mklink /J "P:\IE\ThermalSystem" "$(wslpath -w "$SCRIPT_DIR/..")"

# Community Framework

cmd.exe /c mklink /J "C:\Program Files (x86)\Steam\steamapps\common\DayZ\JM" "$(wslpath -w "$SCRIPT_DIR/../../CommunityFramework/JM")"

cmd.exe /c mklink /J "P:\JM" "$(wslpath -w "$SCRIPT_DIR/../../CommunityFramework/JM")"

cmd.exe /c mklink /J "P:\JM\COT" "$(wslpath -w "$SCRIPT_DIR/../../DayZ-CommunityOnlineTools/JM/COT")"

#Liquid Framework
cmd.exe /c mkdir "P:\rag\rag_stuff"
cmd.exe /c mklink /J "P:\rag\rag_stuff\rag_liquid_framework" "$(wslpath -w "$SCRIPT_DIR/../../LiquidFramework")"
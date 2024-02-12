#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

WIN_PROGRAMS_PATH=$(wslvar "programfiles(x86)")
WIN_DZ_TOOL_PATH="$WIN_PROGRAMS_PATH\Steam\steamapps\common\DayZ Tools\Bin\AddonBuilder"

WIN_MOD_PATH="$(wslvar "userprofile")\Documents\DayZData\Mods\@IEThermalSystem"
MOD_PATH=$(wslpath "$WIN_MOD_PATH")

echo $MOD_PATH
rm -fr "$MOD_PATH"
mkdir -p "$MOD_PATH/addons"
cp -r "$SCRIPT_DIR/../keys" "$MOD_PATH/keys"
cp -r "$SCRIPT_DIR/../LICENSE" "$MOD_PATH/LICENSE"
cp -r "$SCRIPT_DIR/../README.md" "$MOD_PATH/README.md"
cp -r "$SCRIPT_DIR/../mod.cpp" "$MOD_PATH/mod.cpp"

cmd.exe /c start /D "$WIN_DZ_TOOL_PATH" AddonBuilder.exe "P:\IE\ThermalSystem\scripts" "$WIN_MOD_PATH\addons" -project="P:" -prefix="IE/ThermalSystem" -clear -binarizeFullLogs -sign="$(wslvar "userprofile")\Documents\Keys\IstarIE.biprivatekey"

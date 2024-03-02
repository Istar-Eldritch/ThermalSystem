#!/bin/bash
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
WIN_SCRIPT_DIR=$(wslupath "$SCRIPT_DIR")

WIN_PROGRAMS_PATH=$(wslvar "programfiles(x86)")
WIN_DZ_PATH="$WIN_PROGRAMS_PATH\Steam\steamapps\common\DayZ"
WIN_DZS_PATH="$WIN_PROGRAMS_PATH\Steam\steamapps\common\DayZServer"

if [ ! -d "$SCRIPT_DIR/mission" ]; then
    DZS_PATH="$(wslpath "$WIN_DZS_PATH")"
    mkdir mission
    cp -r "$DZS_PATH"/mpmissions/dayzOffline.chernarusplus "$SCRIPT_DIR/mission/dayzOffline.chernarusplus"
fi

#cmd.exe /c start /D "$WIN_DZ_PATH" DayZDiag_x64.exe -mission="$WIN_SCRIPT_DIR\mission\dayzOffline.chernarusplus" -mod="P:\Mods\@CF;P:\Mods\@COT;P:\Mods\@RaG_Liquid_Framework;P:\Mods\@IEThermalSystem;P:\Mods\@NamalskSurvival" -filePatching -server -profiles="$WIN_SCRIPT_DIR"\\profiles -config="$WIN_SCRIPT_DIR"\\serverDZ.cfg
cmd.exe /c start /D "$WIN_DZ_PATH" DayZDiag_x64.exe -mission="$WIN_SCRIPT_DIR\mission\dayzOffline.chernarusplus" -mod="P:\Mods\@CF;P:\Mods\@COT;P:\Mods\@RaG_Liquid_Framework;P:\Mods\@IEThermalSystem" -filePatching -server -profiles="$WIN_SCRIPT_DIR"\\profiles -config="$WIN_SCRIPT_DIR"\\serverDZ.cfg

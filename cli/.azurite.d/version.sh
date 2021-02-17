#!/bin/bash

# AZURITE CLI VERSION SCRIPT

source $AZURITE_DIR/../azurite "__including"

azurite_log "Parsing azurite files..."

if [ -d `dirname $0`/data ];
then azurite_raw "§l🗸\n";
else azurite_raw "\nAzurite isn't installed on you computer yet, run §lazurite install§c to get it\n" && azurite_endlog && exit 1;
fi

azurite_raw "§cAzurite engine version §l"

cat `dirname $0`/data/CMakeLists.txt | grep "project(Azurite VERSION" | cut -f 3 -d " " | cut -f 1 -d ")"

azurite_endlog

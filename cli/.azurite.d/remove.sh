#!/bin/bash

# AZURITE CLI UPDATE SCRIPT

source $AZURITE_DIR/../azurite "__including"

azurite_log "Parsing current files..."

if [ -d `dirname $0`/data ];
then azurite_raw "§l🗸\n";
else azurite_raw "\nAzurite isn't installed on you computer\n" && azurite_endlog && exit 1;
fi


azurite_speach "Goodbye dear user :'("

azurite_log "Removing local files..."

rm -rf `dirname $0`/data && azurite_raw "§l🗸\n" || exit 1

azurite_raw "§cI don't feel so good mr Stark :/\n"

azurite_endlog

#!/bin/bash

# AZURITE CLI UPDATE SCRIPT

source $AZURITE_DIR/../azurite "__including"


azurite_speach "Looking for new versions"

azurite_log "Updating remotes..."

cd `dirname $0`/data

git remote update

LOCAL=$(git rev-parse main)
REMOTE=$(git rev-parse origin/main)
BASE=$(git merge-base main origin/main)

if [ $LOCAL = $REMOTE ]; then
    azurite_raw "Everything is §lUp-to-date §c!\n" && azurite_endlog && exit 0
elif [ $LOCAL = $BASE ]; then
    azurite_raw "New version found !\n" && azurite_log "Downloading new version..." && git pull origin main \
    && azurite_log "installing binaries..." && azurite_raw "§lroot §cpermissions needed: " && \
    sudo libtool --mode=install install -c ./lib/libazurite_engine.so `systemd-path system-library-private` && azurite_raw "§l🗸\n" || exit 1 && \
    azurite_log "installing headers..." && \
    sudo cp -r ../engine/include/Azurite `systemd-path system-include` && azurite_raw "§l🗸\n" || exit 1 && \
    azurite_speach "Update complete !"
else
    azurite_raw "Found some weird shit in your local datas, you should try to run §lazurite install§c to reinstall the library" && exit 1
fi



#!/bin/bash

# AZURITE CLI INSTALL SCRIPT

source $AZURITE_DIR/../azurite "__including"

azurite_speach "Looking for previous installation"

azurite_log "Parsing azurite files..."

[ -d `dirname $0`/data ]\
|| (azurite_raw "§l🗸" && azurite_raw "\n§c§iFound nothing !\n")\
&& (azurite_raw "§l✖\n" && azurite_raw "§cFound some old files\n"\
    && azurite_log "Deleting old files..." && rm -rf `dirname $0`/data || exit 1 && azurite_raw "§l🗸\n")

azurite_endlog

azurite_speach "Downloading latest sources"

azurite_log "creating installation directory..."

mkdir `dirname $0`/data && azurite_raw "§l🗸\n" || exit 1

azurite_log "cloning github repository...\n"

git clone https://github.com/Suraii/Azurite.git `dirname $0`/data && azurite_raw "§l🗸\n" || exit 1

azurite_endlog


azurite_speach "Building Azurite..."

azurite_log "creating build directory..."

mkdir `dirname $0`/data/build && azurite_raw "§l🗸\n" && cd `dirname $0`/data/build || exit 1

azurite_log "installing §lconan§c dependencies\n"

conan install .. --build=missing && azurite_raw "§l🗸\n" || exit 1

azurite_log "generating §lcmake§c files...\n"

cmake .. && azurite_raw "§l🗸\n" || exit 1

azurite_log "compiling sources...\n"

(cmake --build . -- -j) && azurite_raw "§l🗸\n" || exit 1

azurite_endlog

azurite_speach "Installing Azurite"

azurite_log "installing binaries..."

azurite_raw "§lroot §cpermissions needed: "

sudo libtool --mode=install install -c ./lib/libazurite_engine.so `systemd-path system-library-private` && azurite_raw "§l🗸\n" || exit 1

azurite_log "installing headers..."

sudo cp -r ../engine/include/Azurite `systemd-path system-include` && azurite_raw "§l🗸\n" || exit 1

azurite_speach "Installation complete !"

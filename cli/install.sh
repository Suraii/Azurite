#!/bin/bash

# AZURITE CLI Installer

cp ./azurite $HOME/.local/bin/

mkdir $HOME/.azurite.d

cp ./.azurite.d/*.sh $HOME/.azurite.d

echo "Installer installed !, yo this is meta AF"

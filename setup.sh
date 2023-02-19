#!/bin/bash
curl -fsSL https://raw.githubusercontent.com/mfunyu/config/main/42homebrew_install.sh | zsh
brew install readline
echo "set echo-control-characters off" > ~/.inputrc
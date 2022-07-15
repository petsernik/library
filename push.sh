#!/bin/bash
git add -u *
git commit -am "$1"
git pull --rebase
git push
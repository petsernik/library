#!/bin/bash
git add -u *
git commit -am "$1 $2 $3 $4 $5 $6 $7"
git pull --rebase
git push
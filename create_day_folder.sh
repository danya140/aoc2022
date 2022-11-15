#!/usr/bin/bash

cp -r day_template day_$1 # copy template
cd day_$1

# Read cookies from file and download input
cookies="$(cat ../cookies.txt)"
curl https://adventofcode.com/2022/day/$1/input --output input.txt --cookie "$cookies"
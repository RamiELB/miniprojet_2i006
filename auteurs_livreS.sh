#! /bin/bash


cut -d' ' -f3 GdeBiblio.txt |sort | uniq -D | uniq -c

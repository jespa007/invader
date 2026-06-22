@echo off
if not exist BUILD mkdir BUILD
if not exist BUILD\DEBUG mkdir BUILD\DEBUG
if not exist BUILD\RELEASE mkdir BUILD\RELEASE
if not exist BIN mkdir BIN

make %1 %2 %3 %4
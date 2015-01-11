@echo off
echo Deleting any folders...
FOR /D /R "%cd%" %%X in (build*) DO RD /S "%%X"
FOR /D /R "%cd%" %%X in (dist*) DO RD /S "%%X"
pause
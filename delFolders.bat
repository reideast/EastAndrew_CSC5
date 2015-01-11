FOR /D /R "%cd%" %%X in (build*) DO RD /S /Q "%%X"
FOR /D /R "%cd%" %%X in (dist*) DO RD /S /Q "%%X"

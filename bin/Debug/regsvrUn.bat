
@echo off  
cd /d %~dp0   


set _addin=".\TGCAD.dll" 


%systemroot%\syswow64\regsvr32.exe -u %_addin%
  
goto exit  
:exit  
exit  
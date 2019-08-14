@rem 图像处理库清理脚本
@rem 本清理脚本由周中亚编写，欢迎传播

@echo off
echo -------------------------------------------------------

echo -------------------------------------------------------

cd /d %~dp0
del /S *.tmp
del /S *.positions
del /S *.obj 
del /S *.ilk 
del /S *.pdb 
del /S *.plg 
del /S *.bsc 
del /S *.trc 
del /S *.pch 
del /S *.idb 
del /S *.exp 
del /S *.sbr 
del /S *.ncb
del /S *.opt
del /S *.o
del /S *.sup
del /S *.aps
del /S *.sdf
rd /S /q .\ipch\
rd /S /q .\x64\

rd /S /q .\Release\
rd /S /q  .\Debug\


@echo off

for /r  %%i in (debug, release) do @if exist "%%i" @rd/s/q "%%i" 
echo 清除完成！ 
echo. & pause 


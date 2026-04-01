@echo off
chcp 65001 >nul
echo 开始批量格式化C代码文件...
echo.

REM 使用绝对路径指向astyle.exe（请根据您的实际安装位置修改）
set "ASTYLE_PATH=C:\Program Files\RedPanda-Cpp\astyle.exe"

if not exist "%ASTYLE_PATH%" (
    echo 错误: 在 '%ASTYLE_PATH%' 未找到astyle.exe
    echo 请检查AStyle安装路径，或修改脚本中的ASTYLE_PATH变量
    pause
    exit /b 1
)

echo 正在递归格式化 .c 和 .h 文件...
echo 使用的样式: Java风格 (--style=java)
echo.

REM 递归处理所有.c和.h文件
for /R %%f in (*.c *.h) do (
    echo 正在格式化: %%~nxf
    "%ASTYLE_PATH%" ^
        --style=java ^
        --indent=tab=4 ^
        --indent-switches ^
        --indent-namespaces ^
        --indent-preproc-block ^
        --min-conditional-indent=1 ^
        --pad-oper ^
        --pad-comma ^
        --pad-header ^
        --suffix=none ^
        --lineend=windows ^
        --quiet ^
        "%%f"
)

echo.
echo 完成！所有C代码文件已格式化。
pause
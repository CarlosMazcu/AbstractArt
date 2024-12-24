rmdir /s /q build
mkdir build
cd build

cmake ..
cmake --build .

cd ..
    
if exist ".\build\Debug" (
    echo Copiando las DLLs a la carpeta Debug...
    xcopy /y /d ".\libs\sfml64\bin\*d-2.dll" ".\build\Debug\"
)


if exist ".\build\Release" (
    echo Copiando las DLLs a la carpeta Release...
    xcopy /y /d ".\libs\sfml64\bin\*2.dll" ".\build\Release\"
)
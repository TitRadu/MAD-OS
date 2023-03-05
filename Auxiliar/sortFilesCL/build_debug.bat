@CD /D "%~dp0"
if not exist "obj\Debug" mkdir "obj\Debug"

gcc.exe -Wall -g  -c "..\..\Command Line\Navigator\Navigator.c" -o "obj\Debug\Navigator.o"
gcc.exe -Wall -g  -c "..\..\Command Line\Operations\FileOperations\FileOperations.c" -o "obj\Debug\FileOperations.o"
gcc.exe -Wall -g  -c "..\..\Command Line\Operations\ProcessOperations\ProcessOperations.c" -o "obj\Debug\ProcessOperations.o"
gcc.exe -Wall -g  -c "..\..\Command Line\Runners\InternalRunner\InternalRunner.c" -o "obj\Debug\InternalRunner.o"
gcc.exe -Wall -g  -c "..\..\Helpers\GeneralHelper\GeneralHelper.c" -o obj\Debug\GeneralHelper.o
gcc.exe -Wall -g  -c "..\..\Helpers\WcharHelper\WcharHelper.c" -o obj\Debug\WcharHelper.o
gcc.exe -Wall -g  -c "sortFilesCL.c" -o obj\Debug\sortFilesCL.o

if not exist "bin\Debug" mkdir "bin\Debug"

gcc.exe  -o bin\Debug\sortFilesCL.exe "obj\Debug\Navigator.o" "obj\Debug\FileOperations.o" "obj\Debug\ProcessOperations.o" "obj\Debug\InternalRunner.o" obj\Debug\GeneralHelper.o obj\Debug\WcharHelper.o obj\Debug\sortFilesCL.o   "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\NetAPI32.Lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\Psapi.Lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\wlanapi.lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\Ole32.Lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\BluetoothApis.lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\bthprops.lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\bcrypt.lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\dxva2.lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\ShLwApi.Lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\mfuuid.lib"

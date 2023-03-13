@CD /D "%~dp0"
if not exist "obj\Debug" mkdir "obj\Debug"

gcc.exe -Wall -g  -c "..\..\Helpers\GeneralHelper\GeneralHelper.c" -o obj\Debug\GeneralHelper.o
gcc.exe -Wall -g  -c "..\..\Helpers\WcharHelper\WcharHelper.c" -o obj\Debug\WcharHelper.o
gcc.exe -Wall -g  -c "contentCL.c" -o obj\Debug\contentCL.o

if not exist "bin\Debug" mkdir "bin\Debug"

gcc.exe  -o bin\Debug\contentCL.exe obj\Debug\GeneralHelper.o obj\Debug\WcharHelper.o obj\Debug\contentCL.o   "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\NetAPI32.Lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\Psapi.Lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\wlanapi.lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\Ole32.Lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\BluetoothApis.lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\bthprops.lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\bcrypt.lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\dxva2.lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\ShLwApi.Lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\mfuuid.lib"
 
if not exist "..\..\CommandLine\bin\Debug" mkdir "..\..\CommandLine\bin\Debug"

gcc.exe  -o ..\..\CommandLine\bin\Debug\contentCL.exe obj\Debug\GeneralHelper.o obj\Debug\WcharHelper.o obj\Debug\contentCL.o   "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\NetAPI32.Lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\Psapi.Lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\wlanapi.lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\Ole32.Lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\BluetoothApis.lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\bthprops.lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\bcrypt.lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\dxva2.lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\ShLwApi.Lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\mfuuid.lib"
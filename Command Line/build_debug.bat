@CD /D "%~dp0"
if not exist "obj\Debug" mkdir "obj\Debug"

gcc.exe -Wall -g  -c "cline.c" -o obj\Debug\cline.o
gcc.exe -Wall -g  -c "..\Helpers\GeneralHelper\GeneralHelper.c" -o obj\Debug\GeneralHelper.o
gcc.exe -Wall -g  -c "..\Helpers\UcharHelper\UcharHelper.c" -o obj\Debug\UcharHelper.o
gcc.exe -Wall -g  -c "..\Helpers\WcharHelper\WcharHelper.c" -o obj\Debug\WcharHelper.o
gcc.exe -Wall -g  -c "Initialization\Initialization.c" -o obj\Debug\Initialization.o
gcc.exe -Wall -g  -c "InternalDirectories\Backup\Backup.c" -o obj\Debug\Backup.o
gcc.exe -Wall -g  -c "InternalDirectories\Path\Path.c" -o obj\Debug\Path.o
gcc.exe -Wall -g  -c "Math\BasicCalculator\BasicCalculator.c" -o obj\Debug\BasicCalculator.o
gcc.exe -Wall -g  -c "Math\Fibonacci\Fibonacci.c" -o obj\Debug\Fibonacci.o
gcc.exe -Wall -g  -c "Navigator\Navigator.c" -o obj\Debug\Navigator.o
gcc.exe -Wall -g  -c "Operations\ComputerOperations\ComputerOperations.c" -o obj\Debug\ComputerOperations.o
gcc.exe -Wall -g  -c "Operations\ConsoleOperations\ConsoleProprierties.c" -o obj\Debug\ConsoleProprierties.o
gcc.exe -Wall -g  -c "Operations\FileOperations\FileOperations.c" -o obj\Debug\FileOperations.o
gcc.exe -Wall -g  -c "Operations\ProcessOperations\ProcessOperations.c" -o obj\Debug\ProcessOperations.o
gcc.exe -Wall -g  -c "Operations\RadioOperations\BluetoothOperations\BluetoothOperations.c" -o obj\Debug\BluetoothOperations.o
gcc.exe -Wall -g  -c "Operations\RadioOperations\WlanOperations\WlanOperations.c" -o obj\Debug\WlanOperations.o
gcc.exe -Wall -g  -c "Runners\CmdCommandsRunner\CmdCommandsRunner.c" -o obj\Debug\CmdCommandsRunner.o
gcc.exe -Wall -g  -c "Runners\CmdRunner\CmdRunner.c" -o obj\Debug\CmdRunner.o
gcc.exe -Wall -g  -c "Runners\GeneralRunner\GeneralRunner.c" -o obj\Debug\GeneralRunner.o
gcc.exe -Wall -g  -c "Runners\InternalRunner\InternalRunner.c" -o obj\Debug\InternalRunner.o
gcc.exe -Wall -g  -c "Runners\UrlRunner\UrlRunner.c" -o obj\Debug\UrlRunner.o
gcc.exe -Wall -g  -c "Time\Time.c" -o obj\Debug\Time.o
gcc.exe -Wall -g  -c "User\User.c" -o obj\Debug\User.o

if not exist "bin\Debug" mkdir "bin\Debug"

gcc.exe  -o "bin\Debug\Command Line.exe" obj\Debug\cline.o obj\Debug\GeneralHelper.o obj\Debug\UcharHelper.o obj\Debug\WcharHelper.o obj\Debug\Initialization.o obj\Debug\Backup.o obj\Debug\Path.o obj\Debug\BasicCalculator.o obj\Debug\Fibonacci.o obj\Debug\Navigator.o obj\Debug\ComputerOperations.o obj\Debug\ConsoleProprierties.o obj\Debug\FileOperations.o obj\Debug\ProcessOperations.o obj\Debug\BluetoothOperations.o obj\Debug\WlanOperations.o obj\Debug\CmdCommandsRunner.o obj\Debug\CmdRunner.o obj\Debug\GeneralRunner.o obj\Debug\InternalRunner.o obj\Debug\UrlRunner.o obj\Debug\Time.o obj\Debug\User.o   "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\NetAPI32.Lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\Psapi.Lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\wlanapi.lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\Ole32.Lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\BluetoothApis.lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\bthprops.lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\bcrypt.lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\dxva2.lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\ShLwApi.Lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64\mfuuid.lib"

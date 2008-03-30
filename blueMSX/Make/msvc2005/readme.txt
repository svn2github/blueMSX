
- install vs2005                (ie. Microsoft Visual C++ 2005 Express Edition_vc.iso 462MB)
- install the platform SDK      (ie. Microsoft Platform SDK R2.iso 409MB)
- install the DirectX SDK       (ie. dxsdk_feb2007.exe 432MB)Make sure you have the Platform SDK installed.

- add c:\Program Files\Microsoft Platform SDK for Windows Server 2003 R2\Include\atl 
  to the "additional include directories"
  
- add to additional dependencies: comsuppw.lib to release builds, and comsuppwd.lib to debug build

if you're missing atlthunk.lib, find altbase.h in C:\Program Files\Microsoft Platform SDK for Windows Server 2003 R2\Include\atl 
and comment the line:
#pragma comment(lib, "atlthunk.lib")

alternatively, you could probably install the DDK
(http://www.microsoft.com/whdc/DevTools/ddk/default.mspx) that
contains atlthunk.lib
but I understand it is only needed for 64-bit compatibility.


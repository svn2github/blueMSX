BlueMSX can be build with VS2010.

However, it also requires the qedit.h for the Sample Grabber, they are part of the Windows SDK
that can be installed separately.

BlueMSX will also require the DirectX SDK, I recommend the August 2007 version, since the current version
(June 2010, at the time of this writing) is missing dxtrans.h which it required by DirectShow.


- install VS2010                (ie. Microsoft Visual C++ 2010 Professional)
- install the Windows SDK       (ie. Microsoft Windows Software Development Kit Update for Windows Vista)
- install the DirectX SDK       (ie. dxsdk_aug2007.exe)

- the "additional include directories" are already set in the project to:
  C:\Program Files\Microsoft SDKs\Windows\v6.1\Include
  C:\Program Files\Microsoft DirectX SDK (August 2007)\Include
  
- the "additional library directories" are already set in the project to:
   C:\Program Files\Microsoft SDKs\Windows\v6.1\Lib
   C:\Program Files\Microsoft DirectX SDK (August 2007)\Lib\x86


Note: VS2010 C++ Express requires you to also install support for ATL.

- install Microsoft Windows Server 2003 R2 Platform SDK

- add this to the "additional include directories"
   C:\Program Files\Microsoft Platform SDK for Windows Server 2003 R2\Include\atl

Comments by Jan Wilmans, Jan 23, 2009, check sourceforge for email address

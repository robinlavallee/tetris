# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Tetris - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Tetris - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Tetris - Win32 Release" && "$(CFG)" != "Tetris - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Tetris.mak" CFG="Tetris - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Tetris - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Tetris - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "Tetris - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "Tetris - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\Tetris.exe"

CLEAN : 
	-@erase ".\Release\Tetris.exe"
	-@erase ".\Release\font.obj"
	-@erase ".\Release\tetris.obj"
	-@erase ".\Release\Dsutil.obj"
	-@erase ".\Release\bitmap.obj"
	-@erase ".\Release\sound.obj"
	-@erase ".\Release\tetris.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/Tetris.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0xc0c /d "NDEBUG"
# ADD RSC /l 0xc0c /d "NDEBUG"
RSC_PROJ=/l 0xc0c /fo"$(INTDIR)/tetris.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Tetris.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ddraw.lib dxguid.lib dsound.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ddraw.lib dxguid.lib dsound.lib /nologo /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/Tetris.pdb" /machine:I386\
 /out:"$(OUTDIR)/Tetris.exe" 
LINK32_OBJS= \
	"$(INTDIR)/font.obj" \
	"$(INTDIR)/tetris.obj" \
	"$(INTDIR)/Dsutil.obj" \
	"$(INTDIR)/bitmap.obj" \
	"$(INTDIR)/sound.obj" \
	"$(INTDIR)/tetris.res"

"$(OUTDIR)\Tetris.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Tetris - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\Tetris.exe" "$(OUTDIR)\Tetris.bsc"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\Tetris.bsc"
	-@erase ".\Debug\tetris.sbr"
	-@erase ".\Debug\bitmap.sbr"
	-@erase ".\Debug\sound.sbr"
	-@erase ".\Debug\Dsutil.sbr"
	-@erase ".\Debug\font.sbr"
	-@erase ".\Debug\Tetris.exe"
	-@erase ".\Debug\Dsutil.obj"
	-@erase ".\Debug\font.obj"
	-@erase ".\Debug\tetris.obj"
	-@erase ".\Debug\bitmap.obj"
	-@erase ".\Debug\sound.obj"
	-@erase ".\Debug\tetris.res"
	-@erase ".\Debug\Tetris.ilk"
	-@erase ".\Debug\Tetris.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/Tetris.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0xc0c /d "_DEBUG"
# ADD RSC /l 0xc0c /d "_DEBUG"
RSC_PROJ=/l 0xc0c /fo"$(INTDIR)/tetris.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Tetris.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/tetris.sbr" \
	"$(INTDIR)/bitmap.sbr" \
	"$(INTDIR)/sound.sbr" \
	"$(INTDIR)/Dsutil.sbr" \
	"$(INTDIR)/font.sbr"

"$(OUTDIR)\Tetris.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ddraw.lib dxguid.lib dsound.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ddraw.lib dxguid.lib dsound.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/Tetris.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/Tetris.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Dsutil.obj" \
	"$(INTDIR)/font.obj" \
	"$(INTDIR)/tetris.obj" \
	"$(INTDIR)/bitmap.obj" \
	"$(INTDIR)/sound.obj" \
	"$(INTDIR)/tetris.res"

"$(OUTDIR)\Tetris.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "Tetris - Win32 Release"
# Name "Tetris - Win32 Debug"

!IF  "$(CFG)" == "Tetris - Win32 Release"

!ELSEIF  "$(CFG)" == "Tetris - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\tetris.cpp
DEP_CPP_TETRI=\
	{$(INCLUDE)}"\Dsound.h"\
	{$(INCLUDE)}"\Ddraw.h"\
	".\Tetris.h"\
	".\Bitmap.h"\
	".\Sound.h"\
	".\Font.h"\
	".\Dsutil.h"\
	{$(INCLUDE)}"\D3dtypes.h"\
	
NODEP_CPP_TETRI=\
	".\..\..\INCLUDE\subwtype.h"\
	

!IF  "$(CFG)" == "Tetris - Win32 Release"


"$(INTDIR)\tetris.obj" : $(SOURCE) $(DEP_CPP_TETRI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Tetris - Win32 Debug"


"$(INTDIR)\tetris.obj" : $(SOURCE) $(DEP_CPP_TETRI) "$(INTDIR)"

"$(INTDIR)\tetris.sbr" : $(SOURCE) $(DEP_CPP_TETRI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\bitmap.cpp
DEP_CPP_BITMA=\
	{$(INCLUDE)}"\Ddraw.h"\
	".\Bitmap.h"\
	

!IF  "$(CFG)" == "Tetris - Win32 Release"


"$(INTDIR)\bitmap.obj" : $(SOURCE) $(DEP_CPP_BITMA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Tetris - Win32 Debug"


"$(INTDIR)\bitmap.obj" : $(SOURCE) $(DEP_CPP_BITMA) "$(INTDIR)"

"$(INTDIR)\bitmap.sbr" : $(SOURCE) $(DEP_CPP_BITMA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\sound.cpp
DEP_CPP_SOUND=\
	{$(INCLUDE)}"\Dsound.h"\
	".\Sound.h"\
	{$(INCLUDE)}"\D3dtypes.h"\
	{$(INCLUDE)}"\Ddraw.h"\
	
NODEP_CPP_SOUND=\
	".\..\..\INCLUDE\subwtype.h"\
	

!IF  "$(CFG)" == "Tetris - Win32 Release"


"$(INTDIR)\sound.obj" : $(SOURCE) $(DEP_CPP_SOUND) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Tetris - Win32 Debug"


"$(INTDIR)\sound.obj" : $(SOURCE) $(DEP_CPP_SOUND) "$(INTDIR)"

"$(INTDIR)\sound.sbr" : $(SOURCE) $(DEP_CPP_SOUND) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\font.cpp
DEP_CPP_FONT_=\
	{$(INCLUDE)}"\Ddraw.h"\
	".\Font.h"\
	

!IF  "$(CFG)" == "Tetris - Win32 Release"


"$(INTDIR)\font.obj" : $(SOURCE) $(DEP_CPP_FONT_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Tetris - Win32 Debug"


"$(INTDIR)\font.obj" : $(SOURCE) $(DEP_CPP_FONT_) "$(INTDIR)"

"$(INTDIR)\font.sbr" : $(SOURCE) $(DEP_CPP_FONT_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dsutil.c
DEP_CPP_DSUTI=\
	{$(INCLUDE)}"\Dsound.h"\
	".\Dsutil.h"\
	{$(INCLUDE)}"\D3dtypes.h"\
	{$(INCLUDE)}"\Ddraw.h"\
	
NODEP_CPP_DSUTI=\
	".\..\..\INCLUDE\subwtype.h"\
	

!IF  "$(CFG)" == "Tetris - Win32 Release"


"$(INTDIR)\Dsutil.obj" : $(SOURCE) $(DEP_CPP_DSUTI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Tetris - Win32 Debug"


"$(INTDIR)\Dsutil.obj" : $(SOURCE) $(DEP_CPP_DSUTI) "$(INTDIR)"

"$(INTDIR)\Dsutil.sbr" : $(SOURCE) $(DEP_CPP_DSUTI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\tetris.rc
DEP_RSC_TETRIS=\
	".\Filedone.wav"\
	

"$(INTDIR)\tetris.res" : $(SOURCE) $(DEP_RSC_TETRIS) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################

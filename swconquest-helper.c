#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#include <windows.h>

BOOL FileExists(LPCTSTR szPath)
{
  DWORD dwAttrib = GetFileAttributes(szPath);

  return (dwAttrib != INVALID_FILE_ATTRIBUTES && 
         !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

char* SetActiveMod(){

  char filename[MAX_PATH];
  GetModuleFileName( NULL, filename, MAX_PATH );

  //find the latest slash, get the string until that and return the pointer following the next occurence
  char*lslash = strrchr(filename, '\\');
  filename[(lslash-filename)]=0;
  
  char*szModName = strrchr(filename, '\\')+1;

  // some undefined constants in TinyCC's headers
  #define KEY_WOW64_64KEY 0x0100
  #define KEY_WOW64_32KEY 0x0200

  HKEY keyThingie;
  RegOpenKeyEx(
    HKEY_CURRENT_USER,
   "Software\\MountAndBladeKeys",
    0,
    KEY_READ|KEY_WRITE|KEY_WOW64_32KEY,
    &keyThingie
    );
    
  if(keyThingie){
    RegSetValueEx(
        keyThingie,
       "last_module",
        0,
        REG_SZ,
        szModName,
        strlen(szModName)
        );
    RegCloseKey(keyThingie);
    return szModName;
  }
  
  return 0;
}


DWORD LaunchGame(){
  STARTUPINFO Startup = {0};
  PROCESS_INFORMATION processInformation = {0};
  
  int proc = CreateProcess("../../mount&blade.exe",
                           NULL,
                           NULL,
                           NULL,
                           FALSE,
                           HIGH_PRIORITY_CLASS,//|CREATE_SUSPENDED,
                           NULL,
                           "../..",
                           &Startup,
                           &processInformation
                           );
  
  if(proc){
    WaitForInputIdle(
      processInformation.hProcess,
      INFINITE
    );
    return processInformation.dwProcessId;
    
  }else{
    return 0;
  }
}
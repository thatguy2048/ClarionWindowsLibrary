OMIT('_END_OF_CODE_',_WINDOWS_FILE_API_INC_)
_WINDOWS_FILE_API_INC_        EQUATE(1)

INCLUDE('WindowsTypes.inc'),ONCE

WIN:FIL:OVERLAPPED_GROUP    GROUP,TYPE
internalPtr                     &WIN:DWORD
internalPtrHigh                 &WIN:DWORD
offsetLow                       WIN:DWORD
offsetHigh                      WIN:DWORD
eventHandle                     WIN:HANDLE
                            END


WIN:FIL:ACCESS:FLAG ITEMIZE,PRE
READ                    EQUATE(80000000H)
WRITE                   EQUATE(40000000H)
EXEC                    EQUATE(20000000H)
ALL                     EQUATE(10000000H)
READWRITE               EQUATE(BOR(WIN:FIL:ACCESS:FLAG:READ,WIN:FIL:ACCESS:FLAG:WRITE))
                    END

WIN:FIL:SHARE:FLAG  ITEMIZE,PRE
NONE                    EQUATE(0) ! Do not share
DELETE                  EQUATE(4H) ! Share delete/rename access
READ                    EQUATE(1H) ! Share read access
WRITE                   EQUATE(2H) ! Share write access
READWRITE               EQUATE(BOR(WIN:FIL:SHARE:FLAG:READ,WIN:FIL:SHARE:FLAG:WRITE))
ALL                     EQUATE(BOR(WIN:FIL:SHARE:FLAG:READWRITE,WIN:FIL:SHARE:FLAG:DELETE))
                    END


WIN:FIL:DISPOSITION  ITEMIZE,PRE
CREATE_NEW                  EQUATE(1) ! Create a new file if it does not exist
CREATE_ALWAYS               EQUATE(2) ! Create a new file, even if it exists
OPEN_EXISTING               EQUATE(3) ! Open the file if it exists
OPEN_ALWAYS                 EQUATE(4) ! Create a file if it does not exist, then open the file either way
TRUNCATE_EXISTING           EQUATE(5) ! Open a file and clear it, if it exists
                            END

WIN:FIL:ATTRIBUTE:FLAG      ITEMIZE,PRE ! https://learn.microsoft.com/en-us/windows/win32/fileio/file-attribute-constants
READONLY                        EQUATE(00001H)
HIDDEN                          EQUATE(00002H)
SYSTEM                          EQUATE(00004H)
DIRECTORY                       EQUATE(00010H)
ARCHIVE                         EQUATE(00020H)
DEVICE                          EQUATE(00000040H)
NORMAL                          EQUATE(00000080H) ! The default
TEMPORARY                       EQUATE(00000100H)
SPARSE_FILE                     EQUATE(00000200H)
REPARSE_POINT                   EQUATE(00000400H)
COMPRESSED                      EQUATE(00000800H)
OFFLINE                         EQUATE(00001000H)
NOT_CONTENT_INDEXED             EQUATE(00002000H)
ENCRYPTED                       EQUATE(00004000H)
INTEGRITY_STREAM                EQUATE(00008000H)
VIRTUAL                         EQUATE(00010000H)
NO_SCRUB_DATA                   EQUATE(00020000H)
EA                              EQUATE(00040000H)
PINNED                          EQUATE(00080000H)
UNPINNED                        EQUATE(00100000H)
RECALL_ON_OPEN                  EQUATE(00040000H)
RECALL_ON_DATA_ACCESS           EQUATE(00400000H)
                            END

WIN:FIL:PROPERTY:FLAG       ITEMIZE,PRE
                            END

! Not sure what the values are in the WIN32 library
WIN:FIL:SECURITY:IMPERSONATE:FLAG       ITEMIZE,PRE
                            END

WIN:FIL:OPEN_MAX_PATH_NAME  EQUATE(128)

WIN:FIL:OFSTRUCT    GROUP,TYPE ! https://learn.microsoft.com/en-us/windows/win32/api/winbase/ns-winbase-ofstruct
sizeInBytes             WIN:BYTE
isOnDisk                WIN:BYTE
errorCode               WIN:WORD
reserved1               WIN:WORD
reserved2               WIN:WORD
pathName                WIN:BYTE,DIM(WIN:FIL:OPEN_MAX_PATH_NAME) ! Hopefully correct
                    END


WIN:FIL:OPEN:FLAG   ITEMIZE,PRE
CANCEL                  EQUATE(00000800H)
CREATE                  EQUATE(00001000H)
DELETE                  EQUATE(00000200H)
EXIST                   EQUATE(00004000H)
PARSE                   EQUATE(00000100H)
PROMT                   EQUATE(00002000H)
READ                    EQUATE(00000000H)
READWRITE               EQUATE(00000002H)
REOPEN                  EQUATE(00008000H)
SHARE_COMPAT            EQUATE(00000000H)
SHARE_DENY_NONE         EQUATE(00000040H)
SHARE_DENY_READ         EQUATE(00000030H)
SHARE_DENY_WRITE        EQUATE(00000020H)
SHARE_EXCLUSIVE         EQUATE(00000010H)
VERIFY                  EQUATE(00000) ! Has no definition in WIN32, but is defined
WRITE                   EQUATE(00000001H)
                    END


WIN:FIL:TYPE   ITEMIZE,PRE
CHAR                EQUATE(0002H)
DISK                EQUATE(0001H)
PIPE                EQUATE(0003H)
REMOTE              EQUATE(8000H)
UNKNOWN             EQUATE(0000H)
                END

WIN:FIL:TIME        GROUP,TYPE
low                     WIN:DWORD
high                    WIN:DWORD
                    END


WIN:FIL:NAME:GET:TYPE       ITEMIZE,PRE
NORMALIZED                      EQUATE(0H)
OPENED                          EQUATE(8H)
VOLUME_DOS                      EQUATE(0H)
VOLUME_GUID                     EQUATE(1H)
VOLUME_NONE                     EQUATE(4H)
VOLUME_NT                       EQUATE(2H)
                            END


    MAP
        MODULE('WinFileAPI')
            ! https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea
            WIN:FIL:CreateFile(*WIN:CSTR fileName, | ! filename string pointer
                WIN:DWORD desiredAccessFlag = WIN:FIL:ACCESS:FLAG:ALL, | ! WIN:FIL:ACCESS:FLAG
                WIN:DWORD shareFlag = WIN:FIL:SHARE:FLAG:ALL, | ! WIN:FIL:SHARE:FLAG
                WIN:LPVOID securityAttributesPtr = WIN:NULL, | ! Pointer to security attribute object not yet defined, can be NULL
                WIN:DWORD creationDisposition = WIN:FIL:DISPOSITION:CREATE_NEW, | ! WIN:FIL:DISPOSITION
                WIN:DWORD flagsAndAttributesFlags = WIN:FIL:ATTRIBUTE:FLAG:NORMAL, | ! WIN:FIL:ATTRIBUTE:FLAG and/or WIN:FIL:PROPERTY:FLAG and/or WIN:FIL:SECURITY:FLAG
                WIN:HANDLE optionalTemplateFileHandle = WIN:NULL | ! Copy the attributes of this file when creating a file
                ),WIN:HANDLE,RAW,PASCAL,NAME('CreateFileA')

            WIN:FIL:OpenFile(*WIN:CSTR fileName, | ! filename string pointer
                *WIN:FIL:OFSTRUCT openFileInfo, | ! WIN:FIL:OFSTRUCT
                WIN:DWORD openFileOptionFlag | ! WIN:FIL:OPEN:FLAG
                ),WIN:HANDLE,RAW,PASCAL,NAME('OpenFile')

            WIN:FIL:CloseFile(WIN:HANDLE fileHandle),BOOL,PASCAL,PROC,NAME('CloseHandle')
            WIN:FIL:ReadFile(WIN:HANDLE fileHandle, WIN:LPVOID bufferPtr, WIN:DWORD numberOfBytesToRead, *WIN:DWORD numberOfBytesRead, *WIN:FIL:OVERLAPPED_GROUP overlappedGroup),BOOl,RAW,PASCAL,NAME('ReadFile');
            WIN:FIL:WriteFile(WIN:HANDLE fileHandle, WIN:LPVOID bufferPointer, WIN:DWORD numberOfBytesToWrite, *WIN:DWORD numberOfByteWritten, *WIN:FIL:OVERLAPPED_GROUP overlappedGroup),BOOl,RAW,PASCAL,NAME('WriteFile');
            WIN:FIL:GetFileSize(WIN:HANDLE fileHandle, *WIN:DWORD fileSizeHigh),WIN:DWORD,RAW,PASCAL,NAME('GetFileSize') 
            WIN:FIL:GetFileSizeEx(WIN:HANDLE fileHandle, *WIN:LARGE_INT fileSize),BOOL,RAW,PASCAL,NAME('GetFileSizeEx')
            WIN:FIL:GetFileType(WIN:HANDLE fileHandle),WIN:DWORD,RAW,PASCAL,NAME('GetFileType') ! returns WIN:FIL:TYPE
            WIN:FIL:GetFileTime(WIN:HANDLE fileHandle, *WIN:FIL:TIME creationTime, *WIN:FIL:TIME accessTime, *WIN:FIL:TIME writeTime),BOOL,RAW,PASCAL,NAME('GetFileTime')
            WIN:FIL:GetFinalPathNameByHandle(WIN:HANDLE fileHandle, *WIN:CSTR outputFilePath, WIN:DWORD filePathSize, WIN:DWORD nameTypeFlag | ! WIN:FIL:NAME:GET:TYPE
                ),WIN:DWORD, | ! The number of bytes written to outputFilePath, if the number is larger than filePathSize, then a larger buffer is needed
                RAW,PASCAL,NAME('GetFinalPathNameByHandleA')
            WIN:FIL:GetFullPathName(*WIN:CSTR fileName, | ! input file name string
                WIN:DWORD fullFileNameBufferSize, | ! input the size of the fullPathBufer to write too
                *WIN:CSTR fullPathBuffer, | ! output buffer to write the full path too
                *WIN:CSTR fileNameComponentPtr | ! Output pointer to position in fullPathBuffer where the file name begins
                ),WIN:DWORD, | ! The number of bytes written to fullPathBuffer, if the number is larger than filePathSize, then a larger buffer is needed
                RAW,PASCAL,NAME('GetFullPathNameA')
            WIN:FIL:GetLongPathName(*WIN:CSTR shortPath, *WIN:CSTR outputLongPath, WIN:DWORD outputLongPathBufferSize),WIN:DWORD,RAW,PASCAL,NAME('GetLongPathNameA')
            WIN:FIL:GetTempPath(WIN:DWORD nameBufferLength, *WIN:CSTR outputNameBuffer),WIN:DWORD,RAW,PASCAL,NAME('GetTempPathA')
        END
    END

_END_OF_CODE_
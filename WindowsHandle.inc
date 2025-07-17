!ABCIncludeFile(WindowsHandle)

! https://learn.microsoft.com/en-us/windows/win32/api/handleapi/

OMIT('_END_OF_CODE_',_WINDOWS_HANDLE_INC_)
_WINDOWS_HANDLE_INC_ EQUATE(1)

INCLUDE('WindowsTypes.inc'),ONCE

WIN:HAN:VALUE       EQUATE(WIN:HANDLE)
WIN:HAN:INVALID_VALUE       EQUATE(WIN:INVALID_HANDLE_VALUE)

WIN:HAN:FLAG        ITEMIZE,PRE ! https://learn.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-gethandleinformation
INHERIT                 EQUATE(1)
PROTECT_FROM_CLOSE      EQUATE(2)
                    END


                    MAP
                        MODULE('WinAPI')
                            WIN:HAN:Close(WIN:HAN:VALUE hObject),BOOL,PASCAL,RAW,PROC,NAME('CloseHandle') ! Close a handle
                            WIN:HAN:GetInformation(WIN:HAN:VALUE hObject, *WIN:DWORD hFlags),BOOL,PASCAL,RAW,NAME('GetHandleInformation') ! Get information about a handle in the out value hFlags, WIN:HAN:FLAG
                            WIN:HAN:SetInformation(WIN:HAN:VALUE hObject, WIN:DWORD dwMask, WIN:DWORD dwFlags),BOOL,PASCAL,RAW,NAME('SetHandleInformation') ! https://learn.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-sethandleinformation
                            WIN:HAN:Compare(WIN:HAN:VALUE left, WIN:HAN:VALUE right), BOOL,PASCAL,RAW,NAME('CompareObjectHandles') ! Determine if two handles point to the same object
                            WIN:HAN:Duplicate(WIN:HAN:VALUE sourceProcessHandle, WIN:HAN:VALUE sourceHandle, WIN:HAN:VALUE targetProcessHandle, *WIN:HAN:VALUE outputTargetHandle, WIN:DWORD desiredAccess, BOOL inheritHandle, WIN:DWORD options), BOOL, PASCAL, RAW, NAME('DuplicateHandle') ! https://learn.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-duplicatehandle
                        END
                        MODULE('WindowsHandle.CLW')
                            WIN:HAN:IsValid(WIN:HANDLE),BOOL
                        END

                    END

WIN:HAN:Scoped      CLASS,MODULE('WindowsHandle.CLW'),LINK('WindowsHandle.CLW',_ABCLinkMode_),TYPE ! Closes a handle on destruction
handle                  WIN:HANDLE(WIN:HAN:INVALID_VALUE), PROTECTED

Destruct                PROCEDURE()
isValid                 PROCEDURE(),BOOL, PROTECTED
get                     PROCEDURE(),WIN:HAN:VALUE, PROTECTED ! get a copy of the handle value (not a handle copy)
release                 PROCEDURE(WIN:HAN:VALUE newValue = WIN:HAN:INVALID_VALUE),WIN:HAN:VALUE, PROTECTED ! get the current handle value, and set the stored value to the new value
reset                   PROCEDURE(WIN:HAN:VALUE newValue = WIN:HAN:INVALID_VALUE), PROTECTED ! Closes the current handle if valid, set a new value for the handle
getStoredInformation    PROCEDURE(*WIN:DWORD hFlags),BOOL, PROTECTED ! WIN:HAN:GetInformation
setInformation          PROCEDURE(WIN:DWORD dwMask,WIN:DWORD dwFlags),BOOL, PROTECTED ! WIN:HAN:SetInformation
compare                 PROCEDURE(WIN:HAN:VALUE otherHandle),BOOL, PROTECTED ! WIN:HAN:Compare
compare                 PROCEDURE(WIN:HAN:Scoped otherHandle),BOOL, PROTECTED ! WIN:HAN:Compare
                    END

_END_OF_CODE_
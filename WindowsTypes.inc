!Some base WIN32 Types

OMIT('_END_OF_CODE_',_WINDOWS_TYPE_INC_)
_WINDOWS_TYPE_INC_ EQUATE(1)

NULL                EQUATE(0)
VOID                EQUATE(LONG)

WIN:NULL            EQUATE(NULL)

WIN:HANDLE          EQUATE(LONG)
WIN:HWND            EQUATE(WIN:HANDLE)
WIN:HINSTANCE       EQUATE(WIN:HANDLE)
WIN:HMODULE         EQUATE(WIN:HANDLE)
WIN:HMENU           EQUATE(WIN:HANDLE)
WIN:HDC             EQUATE(WIN:HANDLE)
WIN:HICON           EQUATE(WIN:HANDLE)
WIN:HCURSOR         EQUATE(WIN:HANDLE)
WIN:HBRUSH          EQUATE(WIN:HANDLE)
WIN:HBITMAP         EQUATE(WIN:HANDLE)
WIN:HGDIOBJ         EQUATE(WIN:HANDLE)
WIN:HFONT           EQUATE(WIN:HANDLE)
WIN:HRGN            EQUATE(WIN:HANDLE)
WIN:HGLOBAL         EQUATE(WIN:HANDLE)
WIN:HPEN            EQUATE(WIN:HANDLE)
WIN:HRESULT         EQUATE(LONG)
WIN:WORD            EQUATE(LONG)
WIN:DWORD           EQUATE(ULONG)
WIN:VOID            EQUATE(VOID)
WIN:SHORT           EQUATE(SHORT)

! Not defining pointers, as they are better represented by using *TYPE notation
! LPCSTR                  EQUATE(CSTRING)
! LPSTR                   EQUATE(CSTRING)
! LPVOID                  EQUATE(LONG)
! LPCVOID                 EQUATE(LONG)
! PLONG                   EQUATE(LONG)
WIN:LPVOID                  EQUATE(LONG) !Using *VOID in the function definitions caused errors

!TRUE                    EQUATE(1) !In EQUATES.CLW
!FALSE                   EQUATE(0) !In EQUATES.CLW

WIN:ERROR_CODE              EQUATE(WIN:DWORD) ! Windows error code
WIN:NO_ERROR                EQUATE(0)

WIN:INVALID_HANDLE_VALUE    EQUATE(-1)

_END_OF_CODE_
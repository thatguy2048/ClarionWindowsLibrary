!ABCIncludeFile(WindowsError)

INCLUDE('WindowsExtended.inc'),ONCE

    MAP
        MODULE('WindowsErrorAPI')
            WIN:ERR:GetLast(),LONG,PASCAL,RAW,NAME('GetLastError')
            WIN:ERR:SetLast(WIN:DWORD errorCode),PASCAL,RAW,NAME('SetLastError')
        END
        MODULE('WindowsError.CLW')
            WIN:ERR:ConvertToString(WIN:ERROR_CODE ec),STRING ! Converts the error code returned by WIN:GetLastError() into a string. If empty there was an error with the conversion, call WIN:GetLastError() for the code.
            WIN:ERR:GetLastString(),STRING ! Calls WIN:ConvertErrroCodeToString() with the result of WIN:GetLastError()
        END
    END

! This class exists mostly for the LINK statement, without it Clarion will not compile WindowsError.CLW (Unlesss it's included in the project directly)
WIN:ERR:Container   CLASS,MODULE('WindowsError.CLW'),LINK('WindowsError.CLW', _ABCLinkMode_), TYPE
errorCode           WIN:ERROR_CODE

init                PROCEDURE(WIN:ERROR_CODE ec)
toString            PROCEDURE(),STRING
                    END
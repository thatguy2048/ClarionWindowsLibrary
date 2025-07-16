!ABCIncludeFile(WindowsError)

INCLUDE('WindowsExtended.inc'),ONCE

    MAP
        MODULE('WindowsError.CLW')
            WIN:ERR:LastError(),LONG
            WIN:ERR:ConvertToString(WIN:ERROR_CODE ec),STRING ! Converts the error code returned by WIN:GetLastError() into a string. If empty there was an error with the conversion, call WIN:GetLastError() for the code.
            WIN:ERR:LastErrorString(),STRING ! Calls WIN:ConvertErrroCodeToString() with the result of WIN:GetLastError()
        END
    END

WIN:ERR:Container   CLASS,MODULE('WindowsError.CLW'),LINK('WindowsError.CLW', _ABCLinkMode_), TYPE
errorCode           WIN:ERROR_CODE

init                PROCEDURE(WIN:ERROR_CODE ec)
toString            PROCEDURE(),STRING
                    END
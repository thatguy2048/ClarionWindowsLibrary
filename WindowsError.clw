MEMBER()
    INCLUDE('WindowsError.inc'),ONCE

WIN:ERR:ConvertToString         PROCEDURE(WIN:ERROR_CODE ec)
dwFlags                                 EQUATE(1200h) !system format the message and don't allocate a buffer
outputBuffer                            CSTRING(256)
outputCharsWritten                      WIN:DWORD
    CODE
        outputCharsWritten = WIN:FormatMessage(dwFlags, NULL, ec, NULL, outputBuffer, 256, NULL) 
        RETURN outputBuffer


WIN:ERR:GetLastString           PROCEDURE()
    CODE
        RETURN WIN:ERR:ConvertToString(WIN:ERR:GetLast())    

WIN:ERR:Container.init          PROCEDURE(WIN:ERROR_CODE ec)
    CODE
        self.errorCode = ec

WIN:ERR:Container.toString      PROCEDURE()
    CODE
        RETURN 'JUAN MO TIME'             
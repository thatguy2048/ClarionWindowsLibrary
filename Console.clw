

  MEMBER()
    INCLUDE('Console.inc'),ONCE

  MAP
        MODULE('WinConsoleAPI')
            WIN:CON:AllocConsole(),BOOL,PASCAL,RAW,NAME('AllocConsole'); ! Allocate a new console and attach this process to it
            WIN:CON:AttachConsole(WIN:DWORD dwProcessId = -1),BOOL,PASCAL,RAW,NAME('AttachConsole'); ! Attach this process to a console identified by the id, -1 is the parent process
            WIN:CON:FreeConsole(),BOOL,PASCAL,RAW,NAME('FreeConsole'); ! Detach from a console
            WIN:CON:GetStdHandle(WIN:DWORD consoleHandleType = WIN:CON:STD_OUTPUT_HANDLE),WIN:HANDLE,PASCAL,PROC,RAW,NAME('GetStdHandle') ! Retrieves a handle to the specified standard device (standard input, standard output, or standard error).
            WIN:CON:WriteConsole(WIN:HANDLE consoleHandle,CONST *CSTRING buffer, WIN:DWORD bufferLength, *WIN:DWORD outputBytesWritten, WIN:LPVOID reserved = NULL),BOOL,RAW,PASCAL,NAME('WriteConsoleA') ! Writes a character string to a console screen buffer beginning at the current cursor location.  
            WIN:CON:ReadConsole(WIN:HANDLE consoleHandle, *CSTRING outputBuffer, WIN:DWORD numberOfCharactersToRead, *WIN:DWORD numberOfCharactersRead, WIN:LPVOID readConsoleConstrolStruct = NULL),BOOL,RAW,PASCAL,PROC,NAME('ReadConsoleA') ! Reads character input from the console input buffer and removes it from the buffer.
            WIN:CON:SetConsoleTitle(*CSTRING titleStr),BOOL,RAW,PASCAL,NAME('SetConsoleTitleA') ! Sets the title for the current console window.
            WIN:CON:GetConsoleTitle(*CSTRING outputTitleBuffer, WIN:DWORD outputTitleBufferSize),BOOL,RAW,PASCAL,NAME('GetConsoleTitleA') ! Retrieves the title for the current console window.
            WIN:CON:SetConsoleMode(WIN:HANDLE consoleHandle, WIN:DWORD modeFlag),BOOL,RAW,PASCAL,NAME('SetConsoleMode') ! Sets the input mode of a console's input buffer or the output mode of a console screen buffer.
            WIN:CON:GetConsoleMode(WIN:HANDLE consoleHandle, *WIN:DWORD outputModeFlag),BOOL,RAW,PASCAL,NAME('GetConsoleMode') ! Retrieves the current input mode of a console's input buffer or the current output mode of a console screen buffer.
            WIN:CON:GetConsoleCP(),UNSIGNED,RAW,PASCAL,NAME('GetConsoleCP') ! Get the console code page identifier (also a reliable way to determine if the console is attached)
        END
  END

WIN:CON:AttachOrCreateConsole       PROCEDURE()
    CODE
        IF WIN:CON:AttachConsole(-1) THEN
            RETURN TRUE
        ELSE
            IF WIN:CON:AllocConsole() THEN
                RETURN TRUE
            END
            
        END
        RETURN FALSE
        
WIN:CON:InitializeConsole   PROCEDURE()
    CODE
        WIN:CON:AttachOrCreateConsole()
        RETURN WIN:CON:GetConsoleCP()
 
!!ConsoleBase!!
WIN:CON:_Base.Construct     PROCEDURE()
    CODE
        !MESSAGE('BASE CONSTRUCTOR');
       
WIN:CON:_Base.Destruct       PROCEDURE()
    CODE
        IF self.hasValidHandle() THEN
            WIN:CloseHandle(SELF.handle);
        END        

WIN:CON:_Base.hasValidHandle        PROCEDURE()
    CODE
        IF (self.handle ~= WIN:NULL AND self.handle ~= WIN:INVALID_HANDLE_VALUE) THEN
            RETURN TRUE
        END
        RETURN FALSE
        
WIN:CON:_Base.init    PROCEDURE (WIN:HANDLE newHandle)
    CODE
        !MESSAGE('INIT WITH HANDLE '&newHandle)
        self.handle = newHandle
        RETURN self.hasValidHandle()
            
    
WIN:CON:_Base.getByteCount    PROCEDURE()
    CODE
        RETURN SELF.byteCount;
        
WIN:CON:_Base.setConsoleMode  PROCEDURE(WIN:DWORD modeFlag)
    CODE
        RETURN WIN:CON:SetConsoleMode(SELF.handle, modeFlag)
        
WIN:CON:_Base.getConsoleMode  PROCEDURE(*WIN:DWORD outModeFlag) 
    CODE
        RETURN WIN:CON:SetConsoleMode(SELF.handle, outModeFlag)

WIN:CON:_Base.addConsoleMode  PROCEDURE(WIN:DWORD modeFlag) 
tmpMode                                 WIN:DWORD
    CODE
        IF SELF.GetConsoleMode(tmpMode) THEN
            RETURN SELF.SetConsoleMode(BOR(tmpMode, modeFlag))
        END
        RETURN FALSE
        
        
WIN:CON:_Base.removeConsoleMode       PROCEDURE(WIN:DWORD modeFlag)
tmpMode                                         WIN:DWORD
    CODE
        IF SELF.GetConsoleMode(tmpMode) THEN
            RETURN SELF.SetConsoleMode(BAND(tmpMode, BXOR(-1, modeFlag)))
        END
        RETURN FALSE
        



!!ConsoleWriter!!
WIN:CON:Writer.Construct     PROCEDURE()
    CODE
        !MESSAGE('WRITER CONSTRUCTOR');       
        
WIN:CON:Writer.Destructor     PROCEDURE()
    CODE
        SELF.writeLine()         
        
WIN:CON:Writer.init  PROCEDURE ()
    CODE
        !MESSAGE('INIT WRITER')
        RETURN self.init(WIN:CON:GetStdHandle(WIN:CON:STD_OUTPUT_HANDLE))
    
WIN:CON:Writer.getBytesWritten      PROCEDURE()
    CODE
        RETURN SELF.getByteCount();
        

WIN:CON:Writer.write        PROCEDURE (CONST *CSTRING buffer, WIN:DWORD bufferLength)
    CODE
       RETURN WIN:CON:WriteConsole(SELF.handle, buffer, bufferLength, SELF.byteCount)        
        
WIN:CON:Writer.write        PROCEDURE (CONST *STRING strToWrite)
strref                                  &CSTRING
    CODE 
        strref &= ADDRESS(strToWrite)
        RETURN self.Write(strref, LEN(strToWrite))
        
        
WIN:CON:Writer.write        PROCEDURE (CONST *CSTRING strToWrite)
    CODE
        RETURN self.Write(strToWrite, LEN(strToWrite))        

WIN:CON:Writer.write        PROCEDURE (STRING strToWrite)
    CODE
        RETURN SELF.Write(strToWrite)
        
WIN:CON:Writer.writeLine    PROCEDURE ()
    CODE
        RETURN SELF.Write(WIN:CON:NEW_LINE_STR, 2)        
      
WIN:CON:Writer.writeLine    PROCEDURE (CONST *CSTRING pText, WIN:DWORD textLength)
tmpByteCount                            LIKE(SELF.byteCount)
    CODE
        IF SELF.Write(pText, textLength) THEN
            tmpByteCount = SELF.byteCount
            IF SELF.WriteLine() THEN
                SELF.byteCount+=tmpByteCount
                RETURN TRUE;
            END            
        END
        RETURN FALSE        
        
WIN:CON:Writer.writeLine    PROCEDURE (CONST *CSTRING pText)
    CODE
        RETURN SELF.WriteLine(pText, LEN(pText))
        
WIN:CON:Writer.writeLine     PROCEDURE (CONST *STRING pText)
strref                                  &CSTRING
    CODE
        strref &= ADDRESS(pText) ! DANGEROUS !
        RETURN SELF.WriteLine(strref, LEN(pText))
        
WIN:CON:Writer.writeLine     PROCEDURE (STRING strToWrite)
    CODE
        RETURN SELF.WriteLine(strToWrite)           
            
!!ConsoleReader!!        
WIN:CON:Reader.init  PROCEDURE()
    CODE        
        IF SELF.init(WIN:CON:GetStdHandle(WIN:CON:STD_INPUT_HANDLE)) THEN
            RETURN SELF.setConsoleMode(WIN:CON:ENABLE_PROCESSED_INPUT)
        END
        RETURN FALSE
        
!WIN:CON:Reader.init  PROCEDURE(BOOL enableLineInput)
!    CODE        
!        IF SELF.init(WIN:CON:GetStdHandle(WIN:CON:STD_INPUT_HANDLE)) THEN
!            IF SELF.setConsoleMode(WIN:CON:ENABLE_PROCESSED_INPUT) THEN
!                IF enableLineInput THEN
!                    SELF.addConsoleMode(WIN:CON:ENABLE_LINE_INPUT)
!                END
!                RETURN TRUE
!            END
!        END
!        RETURN FALSE        
        
WIN:CON:Reader.getBytesRead PROCEDURE()
    CODE
        RETURN SELF.getByteCount()      
        
WIN:CON:Reader.read  PROCEDURE(*CSTRING outputBuffer, WIN:DWORD bufferLength)
    CODE
        RETURN WIN:CON:ReadConsole(SELF.handle, outputBuffer, bufferLength, SELF.byteCount)
                
        
WIN:CON:Reader.readLine      PROCEDURE ()
readBuff                                CSTRING(256)
    CODE
        IF SELF.Read(readBuff, 255) = FALSE THEN
            CLEAR(readBuff)
        ELSE
            readBuff[SELF.byteCount+1] = CHR(0)!'<0>' ! Cheating? CLEAR(CSTRING) does not work for this as it only sets the first byte to \0
        END
        RETURN readBuff;
        
!!Console R/W Object!!
WIN:CON:ConsoleRW.Construct PROCEDURE()
    CODE
        SELF.reader &= NEW WIN:CON:Reader
        SELF.writer &= NEW WIN:CON:Writer
        IF WIN:CON:InitializeConsole() THEN
            SELF.reader.init()
            SELF.writer.init()
            SELF.reader.addConsoleMode(BOR(WIN:CON:ENABLE_LINE_INPUT,WIN:CON:ENABLE_ECHO_INPUT))
        END
        
   
WIN:CON:ConsoleRW.Destruct  PROCEDURE()
    CODE
        DISPOSE(SELF.reader)
        DISPOSE(SELF.writer)        
        
WIN:CON:ConsoleRW.init      PROCEDURE()
    CODE
        RETURN SELF.writer.init() & SELF.reader.init()
        
WIN:CON:ConsoleRW.askForInput       PROCEDURE(STRING question)
    CODE
        IF SELF.writer.write(question) THEN
            RETURN SELF.reader.readLine()
        END
        RETURN ''
            

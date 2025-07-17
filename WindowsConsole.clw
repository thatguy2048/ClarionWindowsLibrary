

  MEMBER()
    INCLUDE('WindowsConsole.inc'),ONCE
    INCLUDE('WindowsConsoleAPI.inc'),ONCE


WIN:CON:AttachOrCreate       PROCEDURE()
    CODE
        IF WIN:CON:Attach(-1) THEN
            RETURN TRUE
        ELSE
            IF WIN:CON:Alloc() THEN
                RETURN TRUE
            END
            
        END
        RETURN FALSE
        
WIN:CON:Initialize   PROCEDURE()
    CODE
        WIN:CON:AttachOrCreate()
        RETURN WIN:CON:GetCP()
 
!!ConsoleBase!!
WIN:CON:_Base.Construct     PROCEDURE()
    CODE
        !MESSAGE('BASE CONSTRUCTOR');
       
WIN:CON:_Base.Destruct       PROCEDURE()
    CODE
!        IF self.hasValidHandle() THEN
!            WIN:CloseHandle(SELF.handle);
!        END        

WIN:CON:_Base.hasValidHandle        PROCEDURE()
    CODE
        return SELF.isValid()
        
WIN:CON:_Base.init    PROCEDURE (WIN:HANDLE newHandle)
    CODE
        SELF.reset(newHandle)
        RETURN self.hasValidHandle()
            
    
WIN:CON:_Base.getByteCount    PROCEDURE()
    CODE
        RETURN SELF.byteCount;
        
WIN:CON:_Base.setMode  PROCEDURE(WIN:DWORD modeFlag)
    CODE
        RETURN WIN:CON:SetMode(SELF.handle, modeFlag)
        
WIN:CON:_Base.getMode  PROCEDURE(*WIN:DWORD outModeFlag) 
    CODE
        RETURN WIN:CON:GetMode(SELF.handle, outModeFlag)

WIN:CON:_Base.addMode  PROCEDURE(WIN:DWORD modeFlag) 
tmpMode                                 WIN:DWORD
    CODE
        IF SELF.GetMode(tmpMode) THEN
            RETURN SELF.SetMode(BOR(tmpMode, modeFlag))
        END
        RETURN FALSE
        
        
WIN:CON:_Base.removeMode       PROCEDURE(WIN:DWORD modeFlag)
tmpMode                                         WIN:DWORD
    CODE
        IF SELF.GetMode(tmpMode) THEN
            RETURN SELF.SetMode(BAND(tmpMode, BXOR(-1, modeFlag)))
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
        RETURN self.init(WIN:CON:GetStdHandle(WIN:CON:STD_HANDLE:OUTPUT))
    
WIN:CON:Writer.getBytesWritten      PROCEDURE()
    CODE
        RETURN SELF.getByteCount();
        

WIN:CON:Writer.write        PROCEDURE (CONST *CSTRING buffer, WIN:DWORD bufferLength)
    CODE
       RETURN WIN:CON:Write(SELF.handle, buffer, bufferLength, SELF.byteCount)        
        
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
        IF SELF.init(WIN:CON:GetStdHandle(WIN:CON:STD_HANDLE:INPUT)) THEN
            RETURN SELF.setMode(WIN:CON:INPUT_MODE_FLAGS:PROCESSED_INPUT)
        END
        RETURN FALSE    
        
WIN:CON:Reader.getBytesRead PROCEDURE()
    CODE
        RETURN SELF.getByteCount()      
        
WIN:CON:Reader.read  PROCEDURE(*CSTRING outputBuffer, WIN:DWORD bufferLength)
    CODE
        RETURN WIN:CON:Read(SELF.handle, outputBuffer, bufferLength, SELF.byteCount)
                
        
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
        IF WIN:CON:Initialize() THEN
            SELF.reader.init()
            SELF.writer.init()
            SELF.reader.addMode(BOR(WIN:CON:INPUT_MODE_FLAGS:LINE_INPUT,WIN:CON:INPUT_MODE_FLAGS:ECHO_INPUT))
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
            

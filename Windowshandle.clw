MEMBER()
    INCLUDE('WindowsHandle.inc')

WIN:HAN:IsValid     PROCEDURE(WIN:HANDLE handleToCheck)
    CODE
        IF (handleToCheck ~= WIN:NULL AND handleToCheck ~= WIN:INVALID_HANDLE_VALUE) THEN
            RETURN TRUE
        END
        RETURN FALSE

WIN:HAN:Scoped.Destructor   PROCEDURE()
    CODE
        IF self.isValid() THEN
            WIN:HAN:Close(SELF.handle)
        END
       
WIN:HAN:Scoped.isValid      PROCEDURE()
    CODE
        RETURN WIN:HAN:IsValid(SELF.handle);


WIN:HAN:Scoped.get  PROCEDURE()
    CODE
        RETURN SELF.handle        
        
WIN:HAN:Scoped.release        PROCEDURE(WIN:HAN:VALUE newValue) 
outputValue                     WIN:HAN:VALUE
    CODE
        outputValue = SELF.handle;
        SELF.handle = newValue;
        RETURN outputValue;
        
WIN:HAN:Scoped.reset        PROCEDURE(WIN:HAN:VALUE newValue)    
    CODE
        IF WIN:HAN:IsValid(SELF.handle) THEN
            WIN:HAN:Close(SELF.handle)
        END
        SELF.handle = newValue
        
WIN:HAN:Scoped.getStoredInformation PROCEDURE(*WIN:DWORD hFlags)
    CODE
        RETURN WIN:HAN:GetInformation(SELF.handle,hFlags)
        
WIN:HAN:Scoped.setInformation       PROCEDURE(WIN:DWORD dwMask,WIN:DWORD dwFlags)
    CODE
        RETURN WIN:HAN:SetInformation(SELF.handle, dwMask, dwFlags)
        
WIN:HAN:Scoped.compare      PROCEDURE(WIN:HAN:VALUE otherHandle)
    CODE
        RETURN WIN:HAN:Compare(SELF.handle, otherHandle)
        
WIN:HAN:Scoped.compare      PROCEDURE(WIN:HAN:Scoped otherHandle)      
    CODE
        RETURN SELF.compare(otherHandle.get())
        
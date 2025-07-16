
# ClarionWindowsLibrary
Wrapper for WIN32 API calls in Clarion. In an attempt to make them easier to add to multiple projects.

The general theme is implementing "namespaces" for the different aspects of the Windows Win32 api available in Clarion. Using the preface "WIN:" followed by more speficic classifications like "WIN:CON:" to access the methods pertaining to the Windows console.

This is not comprehensive, and I will only add functions as I need.

##  To Use
> This has only been used with the latest version of Clarion (12).

Include  the files directory in your Clarion project. 
OR
Put the files in your LibSrc directory ...Clarion12\LibSrc\... and add that directory to the places clarion uses to search for Classes.
In the IDE, Tools -> Options -> Clarion -> Versions -> Directories scanned for ABC Classes -> Add

<img width="422" height="540" alt="image" src="https://github.com/user-attachments/assets/e6c8f0c6-c9b6-455c-b7e0-38fbae516b30" />

<img width="716" height="526" alt="image" src="https://github.com/user-attachments/assets/f83b5b16-4acc-42c9-ab52-92b0be865149" />

### But that did not work?
I have been unable to get Clarion to find classes in any other directory than %ROOT%\LibSrc\win (%ROOT% = Install directory "C:\Clarion12" for me), but adding the directory to the redirect file does work.

In the IDE, Tools -> Edit base redirection file -> (Current Version)

<img width="549" height="532" alt="image" src="https://github.com/user-attachments/assets/6446fe1a-3477-481a-8d45-baf186f5d713" />

Add the path to the directory to the "\*.\*" search criteria under the "[Common]" section.
  
  <code> \*.\*   = .; %ROOT%\libsrc\win; %ROOT%\libsrc\custom\ClarionWindowsLibrary; %ROOT%\images; %ROOT%\template\win; %ROOT%\convsrc </code>

<img width="1045" height="403" alt="image" src="https://github.com/user-attachments/assets/f421a995-9f71-4dfd-a493-4069e663a71d" />

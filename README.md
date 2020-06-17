# Athena
Athena is a stealthy injector that creates a RW section in the Athena process then maps that section as RX into a remote process. Shellcode is then written to the remote processand executed. This project was heavily inspired by [Urban Bishop](https://github.com/FuzzySecurity/Sharp-Suite/tree/master/UrbanBishop).

## Usage
Replace the prexisting buf array with your shellcode.
```C
unsigned char buf[] = "\x90\x90\x90\x90";
```

### Athena CLI
```bash
Athena.exe notepad.exe
```

The shellcode used in Athena by default is from a project called [donut](https://github.com/TheWover/donut) created with the following settings.

### VBScript
```vbscript
MsgBox "Hello From Shellcode!", VBOKOnly
```

### Donut CLI
```bash
donut.exe C:\Path\to\VB\file.vbs -f 4
```

Then copy the code from loader.c into the buf array and you're set.

## Screenshots

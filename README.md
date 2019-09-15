# SIM-Card-Emulator-Tool
A tool that records the live behaviour of a SIM card when connected to the local network within any handset device available in the market today. All SIM card communication, in the form of APDU commands are traced and logged by this tool.


### Release new version

1. Update package.xml
2. Run Release.bat

## Release new installer

1. Update config.xml
2. E:\Qt\QtIFW-3.1.1\bin\binarycreator.exe -c config\config.xml -p packages "ScET Installer.exe"

# passwordGenerator

# YOU'LL NEED LIBSODIUM INSTALLED ON YOUR COMPUTER FOR BUILDS OVER 5 

## I'll try to include libsodium here

## A powerful password generator.
### It basically takes some letters from a list and randomizes them. 
### But it first takes the first and second argument inputted by the user to determine the amount of passwords generated and length., and it has a chance to capatilize the letter or not. After this it will print the final result.

* Usage: : <numPasswords> <passwordLength>
* Example : " passwordGenerator.exe 30 50 " OR "passwordGenerator account OR email

## The recommended length for a password is 50 or more.
## Adjust the length as you need.
# LIBSODIUM Install
* Libsodium can be downloaded from https://download.libsodium.org/libsodium/releases/

## For eg. https://download.libsodium.org/libsodium/releases/libsodium-1.0.17-msvc.zip

* Extract the files from the zip file

* There are two extracted directories: x64 and Win32. Select x64 for 64-bit or Win32 for 32-bit versions of Windows, and search for libsodium.dll. You can find one inside Release/v141/dynamic/libsodium.dll

* Copy this libsodium.dll file and paste it in C:\Windows\system32

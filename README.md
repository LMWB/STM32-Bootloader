# STM32-Bootloader
Bootloader, External Flash Loader, OTA Firmwareupdate
## Discription
This is my own little wiki on how to build a custom Bootloader for STM32 F446 Series of Microcontroller. This repo contains usefull links to other smart distributors on git-hub and youtube.

## External Loader
How to write code to read and write an external Flash connected via SPI (later for advanced speed with Quad-SPI in single dual or quad mode). The ext. flash is supposed to store new firmware which the bootloader has to load to internal flash. There is a possibility to map external flash to STM32's internal flash address space. Maybe this could become handy. Refer to reference manual section 12.1 "memory-mapped mode: the external Flash memory is mapped to the device address space and is seen by the system as if it was an internal memory".

## Bootloader
todo

## Firmware-Update OTA
Firmware Update over the air combines all the features discused so far. The binaries have to be transmitted throught e.g. wifi and stored in the flash. After, the device has to force reboot and bootloader does its job.

### Git Commands
test commit from local git account with local (not gloable) account details

[how to use multiple git accounts](https://www.howtogeek.com/devops/how-to-manage-multiple-git-accounts-on-one-system/)
[how to show git config](https://stackoverflow.com/questions/12254076/how-do-i-show-my-global-git-configuration)

Regular workflow using command line tool

`git add .`

`git commit -m "whats new - my notes on this commit"`

`git push`

Show basic informations

`git status`

`gitk`

Merge branches

`git checkout destination-branch`

`git pull`

`git merge branch-that-has-newes-features`

`git push`

`git checkout back-to-working-branch`

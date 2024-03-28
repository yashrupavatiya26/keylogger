
# Keylogger with RPC Functionality

Hey, want to spy on someone, this project is for you.

Just Kidding my project is soley for information and showcase of basic functionality of key-logger and RPC. 




## Run Locally

#1. Clone the project

```bash
  git clone https://github.com/yashrupavatiya26/keylogger-with-rpc-functionality.git
```

#2 Go to the project directory

```bash
  cd keylogger
```

#3 Run the following commands in Victing system.

- When you will execute sh or exe on victim system, it will ask you for ip address and port number specify both the things. And it will run continuously unit it stop.

```bash
  sudo shell.sh  // for linux/unix/mac users
  sudo windows.exe  // for windows user 
```

#4 Run the following commands in Attacker system
- Update the IP and Port number specified in victim system

```bash
  gcc server.c -o server  // for all the user mac/linux/windows
``` 



## Things to keep in mind while executing the keylogger

- This support cross platform connectivity.
- If you want to execute keylogger in windows environment run the windows.exe and if you are executing on mac/linux run the command windows.exe
- The server.c file which you see in keylogger folder will by executed by attacker in his system. And rest all the data present in the folder need to be in victing system.
- The attacker need to be in same network with victim.





## Features

- Cross Platform Support
- Get new logged data every 3 minutes.


## TIPS

- If you want to execute the keylogger every time PC start up. move the folder to bootup folder, where everytime it will get executed when PC start.




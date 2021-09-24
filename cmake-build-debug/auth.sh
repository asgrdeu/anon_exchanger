#!/usr/bin/env bash

# https://linuxhint.com/bash_read_command/
# bash read command help

echo -n "Login: "
read -r login

echo -n "Password: "
read -rs password

echo -e "\n"

touch .auth_data

echo "login:$login" >> .auth_data
echo "password:$(md5 -qs "$password")" >> .auth_data

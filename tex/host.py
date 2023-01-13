#!/usr/bin/env python
import os
import subprocess

os.system("echo Hello from the other side!")

#inet_ip = subprocess.run(['ifconfig | grep "inet "'])

inet_ip = subprocess.run(['ifconfig'], stdout=subprocess.PIPE, text=True)
last_module = inet_ip.stdout[inet_ip.stdout.rfind("inet ") : ]
ip=last_module[5 : last_module[5 : ].find(' ') + 5]
os.system("jupyter-lab --ip {} --port 5000 --NotebookApp.token='' --NotebookApp.password=''".format(ip))
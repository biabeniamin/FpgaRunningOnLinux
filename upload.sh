#!/bin/bash
sftp ubuntu@192.168.0.107 <<< 'put * functional'

ssh ubuntu@192.168.0.107  'gcc -o functional/exec functional/Keyboard.c functional/Memory.c functional/Relay.c functional/WebServer.c  functional/Temperature.c functional/Main.c functional/Dma.c'
#ssh ubuntu@192.168.0.107  'functional/exec'
#ssh ubuntu@192.168.0.107  'functional/exec'
#ssh ubuntu@192.168.0.107  'rm functional/exec'


echo "1" >> doExecute
sftp ubuntu@192.168.0.107 <<< 'put doExecute functional'

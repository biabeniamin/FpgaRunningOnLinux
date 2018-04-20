#!/bin/bash
sftp ubuntu@192.168.0.107 <<< 'put * functional'

#ssh ubuntu@192.168.0.107  'gcc -o functional/exec functional/FrameChecker.c functional/Keyboard.c functional/Memory.c functional/Relay.c functional/WebServer.c  functional/Temperature.c functional/Main.c functional/Dma.c'
echo "starting"
ssh ubuntu@192.168.0.107  'rm functional/build/exec'
ssh ubuntu@192.168.0.107  'make  --directory=functional/build && echo '1' > functional/doExecute'
#ssh ubuntu@192.168.0.107  'sudo functional/waitCommand.sh'
#ssh ubuntu@192.168.0.107  'rm functional/exec'


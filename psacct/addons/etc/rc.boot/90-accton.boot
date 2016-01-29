#!/bin/bash

if [ -f /var/log/pacct ]; then
	accton /var/log/pacct
fi

ifconfig|sed -r 's/.*(([0-9,a-f]{2}:){5}[0-9,a-f]{2}).*/\1/g'|sed -r '/.*(([0-9,a-f]{2}:){5}[0-9,a-f]{2}).*/!d'
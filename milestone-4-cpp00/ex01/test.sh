#!/home/elagouch/bin/expect -f
set timeout -1

# Start ("spawn") the program under valgrind with your given command
spawn valgrind --show-leak-kinds=all --track-fds=yes --leak-check=full --trace-children=yes --trace-children-skip=/bin/*,/usr/bin/* --track-origins=yes --suppressions=$env(HOME)/readline.supp ./phonebook

# Function to send a sequence for the given contact name
proc add_contact {name} {
    send "ADD\r"
    for {set i 0} {$i < 5} {incr i} {
        send "$name\r"
    }
}
proc add_contact_confirm {name} {
    send "ADD\ry\r"
    for {set i 0} {$i < 5} {incr i} {
        send "$name\r"
    }
}
proc add_big_contact_confirm {name} {
    send "ADD\ry\r"
    for {set i 0} {$i < 5} {incr i} {
        for {set j 0} {$j < 50} {incr j} {
            send "$name"
        }
        send "\r"
    }
}

# Loop over contact names ("A" to "G", 7 times)
foreach n {A B C D E F G H} {
    add_contact $n
}
send "SEARCH\r0\r"
foreach n {I J K L M N O P} {
    add_big_contact_confirm $n
}
send "SEARCH\r0\r"
foreach n {Q R S T U V W X Y Z} {
    add_contact_confirm $n
}
send "SEARCH\r0\r"

# Hand control back to the user interactively
interact

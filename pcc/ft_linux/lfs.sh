#!/usr/bin/env bash

# ==============================================================================
# Configuration
# ==============================================================================

# Determine ROOT_DIR based on the script's location (assumes script is in ROOT/scripts/)
ROOT_DIR=$(realpath $( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd ))

# Path definitions
DISK_IMG_MAIN="$ROOT_DIR/images/tooling.qcow2"
DISK_IMG_LFS="$ROOT_DIR/images/lfs.qcow2"

# VM Resources
# LFS_NPROC="20"
LFS_NPROC="$(nproc)"
LFS_RAM="8"

# Rclone Target
RCLONE_TARGET="GDrive:/LinuxBackups/lsb"

# ==============================================================================
# Helper Functions
# ==============================================================================

confirm_and_run() {
    local cmd_str="$1"
    
    echo -e "\n\033[1;33mPreparing to execute:\033[0m"
    echo -e "\033[0;32m$ $cmd_str\033[0m"
    
    read -p "Execute this command? [y/N] " response
    if [[ "$response" =~ ^[yY]$ ]]; then
        eval "$cmd_str"
    else
        echo "Operation cancelled."
    fi
    
    echo
    read -p "Press Enter to continue..."
}

run_backup_tooling() {
    local max_id=0
    
    # Loop through files matching the pattern in ROOT_DIR
    # We use nullglob to handle the case where no files exist
    shopt -s nullglob
    for archive in "$ROOT_DIR"/tooling.*.tar.gz; do
        # Extract filename
        local fname=$(basename "$archive")
        # Extract the number between 'tooling.' and '.tar.gz'
        local num="${fname#tooling.}"
        num="${num%.tar.gz}"
        
        # Check if it is an integer and greater than current max
        if [[ "$num" =~ ^[0-9]+$ ]] && (( num > max_id )); then
            max_id=$num
        fi
    done
    shopt -u nullglob
    
    local next_id=$((max_id + 1))
    local backup_file="$ROOT_DIR/tooling.${next_id}.tar.gz"
    
    local total_size=$(du -cb "$DISK_IMG_MAIN" 2>/dev/null | tail -n1 | awk '{print $1}')

    read -p "Enter compression level for tooling (recommended 6) [0-9]: " level
    while [[ ! "$level" =~ ^[0-9]$ ]] || [ "$level" -lt 0 ] || [ "$level" -gt 9 ]; do
        echo "Invalid input. Please enter a number between 0 and 9."
        read -p "Enter compression level for tooling (recommended 6) [0-9]: " level
    done

    local cmd="tar -C \"$ROOT_DIR/images/\" -cf - \"tooling.qcow2\" | pv -s $total_size | gzip -$level > \"$backup_file\""
    
    confirm_and_run "$cmd"
}

run_backup_lfs() {
    local max_id=0
    
    # Loop through files matching the pattern in ROOT_DIR
    # We use nullglob to handle the case where no files exist
    shopt -s nullglob
    for archive in "$ROOT_DIR"/lfs.*.tar.gz; do
        # Extract filename
        local fname=$(basename "$archive")
        # Extract the number between 'lfs.' and '.tar.gz'
        local num="${fname#lfs.}"
        num="${num%.tar.gz}"
        
        # Check if it is an integer and greater than current max
        if [[ "$num" =~ ^[0-9]+$ ]] && (( num > max_id )); then
            max_id=$num
        fi
    done
    shopt -u nullglob
    
    local next_id=$((max_id + 1))
    local backup_file="$ROOT_DIR/lfs.${next_id}.tar.gz"
    
    local total_size=$(du -cb "$DISK_IMG_LFS" 2>/dev/null | tail -n1 | awk '{print $1}')

    read -p "Enter compression level for LFS (recommended 6) [0-9]: " level
    while [[ ! "$level" =~ ^[0-9]$ ]] || [ "$level" -lt 0 ] || [ "$level" -gt 9 ]; do
        echo "Invalid input. Please enter a number between 0 and 9."
        read -p "Enter compression level for LFS (recommended 6) [0-9]: " level
    done

    local cmd="tar -C \"$ROOT_DIR/images/\" -cf - \"lfs.qcow2\" | pv -s $total_size | gzip -$level > \"$backup_file\""
    
    confirm_and_run "$cmd"
}

display_title() {
  echo -e "\033[1;35m   __   ________"
  echo "  / /  / __/ __/ __ _  ___ ____  ___ ____ ____ ____"
  echo " / /__/ _/_\\ \\  /  ' \\/ _ \`/ _ \\/ _ \`/ _ \`/ -_) __/"
  echo "/____/_/ /___/ /_/_/_/\\_,_/_//_/\\_,_/\\_, /\\__/_/"
  echo -e " LFS 12.4                           /___/\033[0m"
  echo
}

# ==============================================================================
# Main Menu
# ==============================================================================

PS3="Select an option (Ctrl+D to quit): "
options=(
    "Start LFS (GUI)"
    "Start tooling distro (GUI)"
    "Start tooling distro (headless)"
    "Compress and backup the tooling disk"
    "Compress and backup the LFS disk"
    "Sync to Google Drive (rclone)"
)

display_title

select opt in "${options[@]}"
do
    case $opt in
        "Start LFS (GUI)")
            CMD="qemu-system-x86_64 -enable-kvm -m ${LFS_RAM}G -smp $LFS_NPROC -drive file=\"$DISK_IMG_LFS\",format=qcow2 -nic user,model=virtio-net-pci,hostfwd=tcp::2222-:22 -vga virtio"
            confirm_and_run "$CMD"
            ;;
        "Start LFS (headless)")
            CMD="qemu-system-x86_64 -enable-kvm -m ${LFS_RAM}G -smp $LFS_NPROC -drive file=\"$DISK_IMG_LFS\",format=qcow2 -nic user,model=virtio-net-pci,hostfwd=tcp::2222-:22 -nographic"
            confirm_and_run "$CMD"
            ;;
        "Start tooling distro (GUI)")
            CMD="qemu-system-x86_64 -enable-kvm -m ${LFS_RAM}G -smp $LFS_NPROC -drive file=\"$DISK_IMG_MAIN\",format=qcow2 -drive file=\"$DISK_IMG_LFS\",format=qcow2 -nic user,model=virtio-net-pci,hostfwd=tcp::2222-:22 -vga virtio"
            confirm_and_run "$CMD"
            ;;
        "Start tooling distro (headless)")
            echo "Note: Press 'Ctrl+A' then 'x' to terminate the VM."
            CMD="qemu-system-x86_64 -enable-kvm -m ${LFS_RAM}G -smp $LFS_NPROC -drive file=\"$DISK_IMG_MAIN\",format=qcow2 -drive file=\"$DISK_IMG_LFS\",format=qcow2 -nic user,model=virtio-net-pci,hostfwd=tcp::2222-:22 -nographic"
            confirm_and_run "$CMD"
            ;;
        "Compress and backup the tooling disk")
            run_backup_tooling
            ;;
        "Compress and backup the LFS disk")
            run_backup_lfs
            ;;
        "Sync to Google Drive (rclone)")
            CMD="rclone sync -P \"$ROOT_DIR\" \"$RCLONE_TARGET\" --exclude \"images/**\""
            confirm_and_run "$CMD"
            ;;
        *)
            # Standard bash 'select' behavior is to just reprint the prompt 
            # if input is invalid, but we can explicitly scold the user if desired.
            echo "Invalid option \"$REPLY\". Please try again."
            ;;
    esac
done

# If loop ends via ^D
exit 0

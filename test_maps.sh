#!/bin/bash

# Function to display usage instructions
usage() {
    echo "Usage: $0 <use_bonus>"
    echo "  use_bonus: 0 for regular scenes, 1 for bonus scenes"
    exit 1
}

# Check if the correct number of arguments is provided
if [ "$#" -ne 1 ]; then
    usage
fi

# Check if the argument is either 0 or 1
if [ "$1" -ne 0 ] && [ "$1" -ne 1 ]; then
    usage
fi

# Determine make command based on the argument
if [ "$1" -eq 0 ]; then
    make_cmd="make"
    scenes=("scenes/main/all_objects.rt" "scenes/main/camera_behind_top.rt" "scenes/main/camera_front_top.rt" "scenes/main/camera_right_top.rt" "scenes/main/camera_behind_bottom.rt" "scenes/main/camera_front_bottom.rt" "scenes/main/camera_right_bottom.rt")
else
    make_cmd="make bonus"
    scenes=("scenes/bonus/test/all_objects.rt" "scenes/bonus/test/camera_behind_top.rt" "scenes/bonus/test/camera_front_bottom.rt" "scenes/bonus/test/camera_right_top.rt" "scenes/bonus/test/camera_behind_bottom.rt" "scenes/bonus/test/camera_front_top.rt" "scenes/bonus/test/camera_right_bottom.rt")
fi

# Run make command
$make_cmd

# Sort scenes alphabetically by name
scenes=($(printf "%s\n" "${scenes[@]}" | sort))

# Loop through each scene file
for scene_file in "${scenes[@]}"; do
    echo "Testing scene: $scene_file"  # Print the scene being tested
    # Launch the process
    ./miniRT "$scene_file" &
    pid=$! # Get the process ID of the last background command
    
    # Wait for 5 seconds
    sleep 5
    
    # Kill the process
    kill $pid
    wait $pid 2>/dev/null # Suppress error message if process has already exited
    
    # Add any cleanup or setup code here if needed
    
    # Add some delay between switching scenes if necessary
    sleep 1
done

# Simple script to automate compilation and execution
echo "INFO: This script assumes that you have cloned the repository in your home directory."
echo "Compiling..."

# Check if a directory does not exist
# if [ -d "/test_bed/build" ]
# then
#     echo "Build folder exists." 
# else
#     echo "Creating build folder..." 
mkdir -p ~/test_bed/build
# fi

cd ~/test_bed/build

# Compilation
cc -I ../include/ -c ../app/app_shape_database.c
cc -I ../include/ -c ../src/menu_components.c

# Linking
cc app_shape_database.o menu_components.o -o app_main

# Execution
~/test_bed/build/app_main
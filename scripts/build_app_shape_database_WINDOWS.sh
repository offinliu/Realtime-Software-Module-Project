# Simple script to automate compilation and execution
echo "INFO: This script assumes that you are running from the \"scripts\" folder."
echo "Compiling..."

# Check if a directory does not exist
# if [ -d "/test_bed/build" ]
# then
#     echo "Build folder exists." 
# else
#     echo "Creating build folder..." 
mkdir -p ../build
# fi

cd ../build

# Compilation
gcc -I ../include/ -c ../app/app_shape_database_WIN.c
gcc -I ../include/ -c ../src/menu_components_WIN.c
gcc -I ../include/ -c ../src/linked_list_struct_WIN.c
gcc -I ../include/ -c ../src/graphical_WIN.c

# Linking
gcc app_shape_database_WIN.o menu_components_WIN.o linked_list_struct_WIN.o graphical_WIN.o -o app_main_WIN -lm

# Execution
app_main_WIN

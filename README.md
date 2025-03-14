# Thermal-EX

In this project, shell will print the logo of Arknights and Thermal-EX. Ready to add other functions.
## How to use

```cmake
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
# cmake .. -DCMAKE_BUILD_TYPE=Release
make -j
./light
```

For clean: in the /build , `make clean`

## version
### Unreleased Edition
1.0.0: Print logo of original game and THRM-EX.  
1.1.0: Add new function about light on and off.  
1.2.0: Using libgpio to control the GPIO, instead of ~~antique~~ wiringPi. Add Doxygen comments.
1.3.0: New function about ultrasonic, but wiringPi.
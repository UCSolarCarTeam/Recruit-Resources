if ! echo $PWD | grep "arm-none-eabi-gcc"; then
    echo "gcc"
fi

if ! echo $PWD | grep "st-flash"; then
    echo "st-flash"
fi

if ! echo $PWD | grep "CubeMX2Makefile"; then
    echo "CubeMX2Makefile"
fi

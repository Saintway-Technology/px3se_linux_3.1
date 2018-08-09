mkdir -p $(pwd)/buildroot/output/target/system/vendor/firmware
mkdir -p $(pwd)/buildroot/output/target/system/etc/firmware
cp $(pwd)/device/rockchip/px3-se/firmware/bcm43438a1.hcd $(pwd)/buildroot/output/target/system/vendor/firmware
cp $(pwd)/device/rockchip/px3-se/wifi/firmware/* $(pwd)/buildroot/output/target/system/etc/firmware
cp $(pwd)/device/rockchip/px3-se/wifi/iw* $(pwd)/buildroot/output/target/bin
chmod 777 $(pwd)/buildroot/output/target/system/vendor/firmware/*
chmod 777 $(pwd)/buildroot/output/target/system/etc/firmware/*
chmod 777 $(pwd)/buildroot/output/target/bin/iw*


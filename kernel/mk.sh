if [ $1 = vehicle ]
then 
	echo -e "\e[31m make px3se_linux_vehicle_defconfig used vehicle \e[0m"
	make ARCH=arm px3se_linux_vehicle_defconfig
	make ARCH=arm px3se-sdk.img -j8
else
	echo -e "\e[31m make px3se_linux_camera_defconfig used camera \e[0m"
	make ARCH=arm px3se_linux_camera_defconfig
	make ARCH=arm px3se-sdk.img -j8
fi

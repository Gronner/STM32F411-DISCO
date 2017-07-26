# STM32F411-DISCO

A code repository of libraries to interact with the on-board electronics of the STM32F411E-Discovery Board by STMicroelectronics

## Goal

In the end a set of libraries will be present in this repository that allows the user to interact with:

1. The four LEDs;
2. the user push button;
3. the diverse MEMS chips:
  * L3GD20 3-axis gyroscope (SPI),
  * LSM303DLHC 3D linear acceleration sensor and 3D digital magnetic sensor (I2C),
  * MP45DT02 audio sensor,
4. CS43L22 audio DAC;
5. USB OTG

This is done as a learning experince.

## Resources

Any documentation for the STM32F411E-DISCO Board can be found at the official STMicroelectronics webpage: <http://www.st.com/en/evaluation-tools/32f411ediscovery.html>

Any documentation for the STM32F411VET6 chip that is used by the discovery board can also be found on the offical STMicroelectronics web page: <http://www.st.com/en/microcontrollers/stm32f411ve.html>

#Balance-Car
The Dream Car
#这是一个平衡车
PCB踩坑：1、MPU6050模块和OLED模块位置干涉
        2、电机的接口发生编码器的电源错误的变成了3V3，但是在原理图中并没有出现错误。
        3、SWD调试接口的电源和地的位置画反了。
        4、PCB上的实时时钟没有用到，所以不需要32K晶振。
        5、USART通信模块的引脚顺序画错。

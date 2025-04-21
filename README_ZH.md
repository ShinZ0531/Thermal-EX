# Thermal-EX

<p align="center">
<a href="https://ak.hypergryph.com/">
  <img src="image/THRM-EX.png" alt="Thermal-EX" width="300"/>
</a>
</p>
<h3 align="center">欢迎回来，博士！今天您也是如此充满着光与热啊！</h3>

<br />
<p align="center">
  <a href="https://github.com/ShinZ0531/Thermal-EX/blob/main/LICENSE"><img src="https://img.shields.io/badge/License-Apache%202.0-blue.svg" alt="License"></a>
  <a href="https://github.com/ShinZ0531/Thermal-EX/releases"><img src="https://img.shields.io/github/v/release/ShinZ0531/Thermal-EX" alt="Release Version"></a>
  <br/>
</p>

<hr class="solid">


[Want to see English README?](README.md)  

在这个项目，我们打算使用树莓派5制作一个基于Thermal-EX的智能机器人，Thermal-EX是游戏《明日方舟》中的一个角色，非常热情，时刻准备着给予你帮助。我们希望通过这种方式来让更多的人感受到这个角色的有趣之处，用Thermal-EX给大家带来笑容。

### 查看我们的视频演示
成品功能展示：  
**目标追踪**    
[THERMAL-EX 即将完工！](https://www.bilibili.com/video/BV1Ac51znESn/)  
或油管↓  
[![视频封面描述](https://img.youtube.com/vi/ErilsZ5SbGk/0.jpg)](https://www.youtube.com/shorts/ErilsZ5SbGk)  

**多功能头部支架**  
[THERMAL-EX 功能展示](https://www.bilibili.com/video/BV1tQ5yz4ENp/)
或油管↓  
[![视频封面描述](https://img.youtube.com/vi/UxmqShul9XQ/0.jpg)](https://www.youtube.com/shorts/UxmqShul9XQ)  

早期功能展示：  
[老大说4月前看不到视频就不让我玩太刀喵](https://www.bilibili.com/video/BV16FZzYbERi) (bilibili连接)

或油管↓  
[![视频封面描述](https://img.youtube.com/vi/FJetTLFNYLg/0.jpg)](https://www.youtube.com/watch?v=FJetTLFNYLg)

### 计划中的更新功能

加入麦克风和音响，以提供更好的互动体验。

增加摄像头和人脸识别功能。
 
![Preview](image/EX.jpg)  

## 📜 如何使用

```cmake
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j
```

在build文件夹中，可以看到很多可执行文件，具体功能请查阅tests文件夹下的README.md或wiki。

### 库要求
gpiod 




## 🛠️ 硬件
| **Device**               | **Model/Usage**                              |
|--------------------------|---------------------------------------------|
| 🖥️ **树莓派**      | 5 (主控制器)                   |
| 📡 **超声波传感器** | HC-SR04 (用于测距)              |
| ⚙️ **伺服电机**       | SG90 (旋转头部)                   |
| 💡 **LED**         | 普通的小灯泡 (氛围状态指示)              |
| 🔊 **USB音响**        | 不限            |


组装的时候请自由发挥——包括但不限于使用电工胶带、面包板、502胶水、铁丝。等等。有想要的装饰也请随意添加。OvO

3D打印外壳的部分在`3Dprinting`文件夹里，推荐对尺寸和细节再进行调整。


## 📦  版本

### 发行版
#### 2.3.0
在这个版本中，加入了SG90舵机来驱动头旋转（旋转！），键盘输入监控类和使用usb音响的音频播放系统。

除此之外，还有整合了HCSR04超声波传感器、LED和SG90舵机的一个综合的功能：当超声波探测到的距离小于阈值的时候，LED会加快闪烁预警，同时舵机会停止——Thermal-EX会开始盯着这个方向！

3D打印外壳也基本完成了，可爱的Thermal-EX已经初具雏形。

#### 2.2.0
给LED和HCSR04超声波传感器添加回调接口。每个功能都有单独的测试。

#### 2.0.0
第一个正式发行的版本！它提供了两个主要功能，LED灯闪烁和超声波测距。

### 未发行版
#### 2.1.0
代码调整。

#### 1.4.0
超声波测距，但是使用libgpio而不是wiringPi。终于啊终于！

#### 1.3.0
关于超声波的新功能，但还是使用wiringPi。

#### 1.2.0
使用libgpio来控制GPIO，而不是~~古老的~~wiringPi。  

#### 1.1.0
灯闪烁的新功能。  


#### 1.0.0
打印游戏和Thermal-EX的logo。  


## 😙 贡献
<table>
  <tr>
    <td width="150" align="center">
      <a href="https://github.com/ShinZ0531">
        <img src="https://github.com/ShinZ0531.png" width="100" style="border-radius:50%">
      </a>
    </td>
    <!-- 右侧对话 -->
    <td>
      <div style="position: relative; padding: 15px; background: #f0f2f5; border-radius: 10px; margin: 10px 0;">
        <div style="position: absolute; left: -10px; top: 20px; width: 0; height: 0; border-top: 10px solid transparent; border-bottom: 10px solid transparent; border-right: 10px solid #f0f2f5;"></div>
        <strong>Jin Zhou</strong>: 莱伊是我老婆！
        <br>
        <em>负责管理项目进度，代码的修改和文档的编写</em>
      </div>
    </td>
  </tr>

  <tr>
    <td align="center">
      <a href="https://github.com/Cliay193">
        <img src="https://github.com/Cliay193.png" width="100" style="border-radius:50%">
      </a>
    </td>
    <td>
      <div style="position: relative; padding: 15px; background: #f0f2f5; border-radius: 10px; margin: 10px 0;">
        <div style="position: absolute; left: -10px; top: 20px; width: 0; height: 0; border-top: 10px solid transparent; border-bottom: 10px solid transparent; border-right: 10px solid #f0f2f5;"></div>
        <strong>Juekun Jiang</strong>: crazy Thursday v me 50
        <br>
        <em>负责硬件电机驱动部分，完成了基础的HCSR04超声波传感器和电机驱动的代码，参与了组装工作</em>
      </div>
    </td>
  </tr>

  <tr>
    <td align="center">
      <a href="https://github.com/Dreamshrimp-gg">
        <img src="https://github.com/Dreamshrimp-gg.png" width="100" style="border-radius:50%">
      </a>
    </td>
    <td>
      <div style="position: relative; padding: 15px; background: #f0f2f5; border-radius: 10px; margin: 10px 0;">
        <div style="position: absolute; left: -10px; top: 20px; width: 0; height: 0; border-top: 10px solid transparent; border-bottom: 10px solid transparent; border-right: 10px solid #f0f2f5;"></div>
        <strong>Xiaxi Li</strong>: 敢惹我 那你算是踢到棉花了
        <!--If you dare mess with me, you're picking on cotton.-->
        <br>
        <em>负责宣传工作、视频制作，完成了摄像头的基础代码</em>
      </div>
    </td>
  </tr>

  <tr>
    <td align="center">
      <a href="https://github.com/ninuin11">
        <img src="https://github.com/ninuin11.png" width="100" style="border-radius:50%">
      </a>
    </td>
    <td>
      <div style="position: relative; padding: 15px; background: #f0f2f5; border-radius: 10px; margin: 10px 0;">
        <div style="position: absolute; left: -10px; top: 20px; width: 0; height: 0; border-top: 10px solid transparent; border-bottom: 10px solid transparent; border-right: 10px solid #f0f2f5;"></div>
        <strong>Ziyuan Liu</strong>: 罗德岛拆迁工程师
        <!--Rhode Island Demolition Engineer-->
        <br>
        <em>负责绝大部分3D打印，硬件组装，宣传视频发布，完成了SG90舵机的代码</em>
      </div>
    </td>
  </tr>

  <tr>
    <td align="center">
      <a href="https://github.com/成员B账号">
        <img src="https://github.com/成员B账号.png" width="100" style="border-radius:50%">
      </a>
    </td>
    <td>
      <div style="position: relative; padding: 15px; background: #f0f2f5; border-radius: 10px; margin: 10px 0;">
        <div style="position: absolute; left: -10px; top: 20px; width: 0; height: 0; border-top: 10px solid transparent; border-bottom: 10px solid transparent; border-right: 10px solid #f0f2f5;"></div>
        <strong>Han Jiang</strong>: 离线中
        <br>
        <em>负责一部分3D打印</em>
      </div>
    </td>
  </tr>

  
</table>

## ✈️ 时间线
`📅 2025.02.06 -> 2025.02.16` **项目启动**  
🟦⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 10%
- 确定目标，做智能小车 
- 主题为明日方舟角色Thermal-EX  
<br>  

`📅 2025.02.17 -> 2025.02.23` **项目规划**  
🟦🟦⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 20%
- 功能划分：电机与驱动、语音播放、3D打印外壳、摄像头、超声波、灯光  
- 分工并寻找可用参考  
<br>  

`📅 2025.02.24 -> 2025.03.09` **开始尝试**  
🟦🟦🟦🟦⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜ 30%  
- 制定GitHub仓库使用和代码编写规范   
- 开始编写代码
- 3D打印开始画图
<br> 

`📅 2025.03.10 -> 2025.03.23` **初步完成**  
🟦🟦🟦🟦🟦🟦🟦🟦⬜⬜⬜⬜⬜⬜ 50%  
- 熟练c++类编程
- 初步完成LED类和基于HCSR04的超声波传感器类 
- 确定接下来使用的传感器等组件
- 尝试3D打印，修改预计大小
- 对于现阶段功能进行宣传
<br> 

`📅 2025.03.24 -> 2025.03.30` **中场休息**  
🟦🟦🟦🟦🟦🟦🟦🟦🟦⬜⬜⬜⬜⬜ 55%  
- 休息和调整
<br> 

`📅 2025.03.31 -> 2025.04.13` **挫折阶段**  
🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦⬜⬜ 75%  
- 尝试解决电机驱动TB6612和L298N和电机无法使用的问题  
- 尝试解决ov5647无法使用的问题  
- 尝试解决无法在调用imx219的问题  
- 尝试使用I2S
- 调整项目进度
- 3D打印外壳
<br> 

`📅 2025.04.14 -> 2025-04-21` **项目提交**  
🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦 100%  
- 调整代码结构  
- 增加使用pwm控制的SG90舵机、键盘输入监控和音响输出类
- 整合了一个复杂功能的示例
- 3D打印外壳  
- 组装成品  
- 进行最终版本宣传  
<br> 

## 💬 参考
使用了来自于[rpi_pwm](https://github.com/berndporr/rpi_pwm)的pwm控制库

## ⚖️ 证书

这个项目使用Apache 2.0证书。在这里查看[证书](https://github.com/ShinZ0531/Thermal-EX/blob/main/LICENSE)。
# QT-based-SMPC-test-and-demonstration-program-under-Linux

开发系统:ubuntu 18.0.4

开发平台:QT5.12.3

算法测试方向：安全多方计算SMPC，不经意传输协议，混淆电路，隐私保护，同态加密

----------------------------------------
该项目是我加入学校实验室未来技术实验室(FTG Group)做的项目作业，指导老师是蒋林智老师。该项目我了解的不是很多，但是根据指导老师基本的说法，他是准备将机器学习和隐私保护相结合，进行深度学习图像识别的隐私保护训练(具体详细信息可以看一下链接：https://blog.openmined.org/encrypted-training-on-mnist/ 这是老师当时给我的提示)。老师要求我进行相关隐私保护算法的算法库的编译和测试，其中很大部分都是基于linux系统。在对几个算法进行测试之后，老师要求我使用QT对这些算法和测试程序进行封装，通过使用QT来调用编译好的算法测试程序，并将相关信息输出到QT程序界面上，这样就可以展示老师的算法和研究成果，该项目主要的部分还是在于深度学习和隐私保护的结合。

很遗憾，最终我还是退出了实验室，这个项目也就搁置了，这个项目中的深度学习和隐私保护内容对于我们本科生来说可能难度有点大，但是如果做出来的话将会是很漂亮的成果。

----------------------------------------

GUI界面左边为算法的单元测试部分，右边部分的按钮包括算法详解（pdf文档），算法示例（多
媒体视频播放），算法文献与来源（相关网页链接）。

①目前由于需要进行的单元测试比较多，算法测试部分可能还有一些路径问题，需要注意绝对路
径和相对路径问题和权限问题；

②pdf文档打开还是通过调用linux系统自带office软件查看；

③多媒体视频根据自己的视频添加到/usr/src/FTGtest/media/路径下，并在cpp文件中进行路径
修改。同时，linux下的视频播放需要下载相关解码器才能正常播放视频；

④qt调用的算法包括frontend_libOTe,Palisade,UC,MP-SPDZ,Swanky。相关github链接如下：

https://github.com/osu-crypto/libOTe

https://gitlab.com/palisade/palisade-development.git

https://github.com/encryptogroup/UC

https://github.com/data61/MP-SPDZ

https://github.com/GaloisInc/swanky

程序运行界面如下：
![}NNHX7E~2TN} 0DM4WTN4G0](https://user-images.githubusercontent.com/95836373/180630802-6bc9f895-5eb4-45d9-b44a-17996a83d7a9.png)

----------------------------------------

在QT程序完成之后需要将程序打包，我首先是使用linuxdeployqt将QT编译生成的可执行程序打包，再使用dpkg命令按以下文件路径制作deb安装包。
![未命名文件](https://user-images.githubusercontent.com/95836373/179399328-99ba8ae2-ec2c-4f45-9cd4-14d43e57a245.png)

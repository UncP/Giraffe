##Giraffe Distributed Monte Carlo Ray Tracer
[English Version of README](./README.en.md)

###Giraffe 是一个拥有自己的光线追踪语言的分布式蒙特卡洛光线追踪器，采用C++11/14实现。
###它的中文名字是`长颈鹿`。

***

###特点
* 多种表面的BRDF(reflect, refract, glossy, specular...)
* 反走样
* 全局光照
* 蒙特卡洛积分
* 分布式路径追踪
* Explicit Lighting
* Russian Roulette
* Procedural Texture（砖块，条纹，图像, 格子, 圆点）
* 凹凸映射
* Perlin Noise（大理石）
* Depth of field
* Sampler(Uniform, Stratified, Halton)
* 光源（点光源，方向光，区域光，纹理光）
* 物体（平面，三角形，球，四棱柱，圆柱，圆盘）
* 加速数据结构
	- BVH
		+	AABB (Axis-Aligned Bounding Box)
		+	DOP	(Discrete Oriented Polytopes)
* Giraffe光线追踪语言


####反射折射
![](./image/reflect_refract.png)

####砖块纹理
![](./image/brick.png)

####景深
![](./image/depth_of_field.png)

####Puppy
![](./image/puppy.png)

####Bear
![](./image/bear.png)

***

####如果你有兴趣尝试一下Giraffe
`在*nix环境下进入src目录然后 make && ./Giraffe puppy 4 (puppy是文件名,在scene文件夹里,以Giraffe为后缀的都可以,4是采样数,默认为1,还可以是8, 16...另外你需要有头文件png.h以及支持C++11/14的编译器，若不能支持C++14，将Makefile里的参数14改为11)`

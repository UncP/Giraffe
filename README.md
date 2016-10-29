##Giraffe Distributed Monte Carlo Ray Tracer
[English Version of README](./README.en.md)

###Giraffe 是一个拥有自己的光线追踪语言的分布式蒙特卡洛光线追踪器，采用C++11/14实现。
***

###特点
* 漫反射, 镜面反射, 折射
* 反走样
* 全局光照
* 蒙特卡洛积分
* 分布式路径追踪
* Explicit Lighting
* Russian Roulette
* Procedural Texture（砖块，条纹，图像）
* Perlin Noise（大理石）
* Depth of field
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

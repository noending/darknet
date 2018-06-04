# 通过darknet玩转yolov3

YOLO(you only look once)是一个非常快的实时物体检测的算法，这次我们通过darknet来快速识别定位图片中的物体。

## 用预先训练的模型检测
通过预先训练的模型加YOLO算法，先git clone darknet：
```
git clone https://github.com/pjreddie/darknet
cd darknet
make
```
然后就会有编译好的YOLO文件在cfg文件夹里，这里你需要下载预训练的[权重文件](pjreddie.com/media/files/yolov3.weights)到darknet文件夹里(yolov3文件237mb，太大就没放在github)，也可以通过
```
wget https://pjreddie.com/media/files/yolov3.weights
```
现在就可以在终端里运行监测器了
```
./darknet detect cfg/yolov3.cfg yolov3.weights data/person.jpg

```
运行结果
![](https://github.com/noending/darknet/blob/master/result/02.png)
![](https://github.com/noending/darknet/blob/master/result/01.png)

![](https://github.com/noending/darknet/blob/master/result/predictions.png)

你也可以在data文件夹里放任何你喜欢的图片 运行命令检测，结果会在主文件夹里生成新的带有标框的图片.

### 多张图片
除了在命令后面跟图片名称，你也可以直接输入不加图片路径的命令：
```
./darknet detect cfg/yolov3.cfg yolov3.weights
```
然后在命令行提示输入图片路径，在输入图片路径，你可以多说输入图片路径，直到按Ctrl-C退出

### 改变识别的阀值
YOLO默认的显示置信度在0.25以上的物体，你可以通过 -thresh <val>. 比如把阀置改为0.5
```
./darknet detect cfg/yolov3.cfg yolov3.weights data/dog.jpg -thresh 0.5
```

### Tiny YOLOv3
---
我们有一个非常小的模型可以用在算力有限的环境，yolov3-tiny.首先下载权重：
```
wget https://pjreddie.com/media/files/yolov3-tiny.weights
```
然后和配置文件权重一起运行识别器
```
./darknet detect cfg/yolov3-tiny.cfg yolov3-tiny.weights data/dog.jpg
```




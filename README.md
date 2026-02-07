# 将YOLOV5 的裸数据集 转化为 train/val/test

我们拿到的数据集可能是这样的
```
dataset/
├── images/
│   ├── 0001.jpg
│   ├── 0002.jpg
├── labels/
│   ├── 0001.txt
│   └── 0002.txt
```
没有区分train/val/test，但是yolov5训练时需要前者

这个程序，可以将以上的文件结构，在一个新的目录下展开为这样:
```
dataset/
├── images/
│   ├── train/
│   │   ├── 0001.jpg
│   └── val/
│       ├── 0002.jpg
├── labels/
│   ├── train/
│   │   ├── 0001.txt
│   └── val/
│       ├── 0002.txt
```
不仅支持GUI操作，还支持自定义划分百分比，支持一定的数据校验\[1\]

![界面截图](https://drive.google.com/thumbnail?id=1QYSd7iIypwSQQrVXRQIA79dmdvuS3MRp&sz=w1484)

\[1\]:验证每个图片文件都有对应的.txt标注文件

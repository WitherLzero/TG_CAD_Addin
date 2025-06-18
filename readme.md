## 第四次作业 TG CAD 插件

##### 主要代码结构：

- TGUSER
  - Dialog
    - MyDialog.cpp
    - MyDialog.h
  - Func
    - Func.cpp
    - Func.h
  - DialogCmd.cpp
  - DialogCmd.h
  - SaveCmd.cpp
  - SaveCmd.h
  - TGUserCmd.cpp (旧版测试cmd)
  - TGUserCmd.h

##### 实现功能：

1. 在打开的当前零件文档中 绘制草图并进行拉伸除料等建模操作
2. 对指定路径中的par文件，创建图纸工程文件，并绘制俯视图，前视图
3. 文件保存功能，可对当前页面的activeDoc进行保存，可在windows窗口选择指定路径
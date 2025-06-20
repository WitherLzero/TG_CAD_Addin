## SUCT实训开发 TG CAD Addin 项目

#### TODO：

- [ ] MFC 插件UI窗口设计
- [ ] 配置命令模块功能
- [ ] 参数驱动模块功能
- [ ] 文件加载与保存

#### 团队成员：

> [!TIP]
>
> 以下相关Git操作，推荐使用vs2022自带的Git工具，详情可参考官网文档：
>
> [关于 Visual Studio 中的 Git](https://learn.microsoft.com/zh-cn/visualstudio/version-control/git-with-visual-studio?view=vs-2022) 
>
> [git 提取、拉取、推送和同步 - Visual Studio (Windows) | Microsoft Learn](https://learn.microsoft.com/zh-cn/visualstudio/version-control/git-fetch-pull-sync?view=vs-2022)) 

1. 克隆主仓库

   ```powershell
   git clone https://gitee.com/lzero47/TG_CAD_Addin.git
   ```

2. 参考实训资料—***天工CAD定制开发教程-C++模板介绍***    进行编译/选择调试程序/注册 等操作

3. 创建开发分支：

   ```powershell
   #eg： create a branch for developing config ui
   git checkout -b config_ui 
   ```

4. 开发/修改代码，进行commit与push操作：

   ```powershell
   # 修改代码
   git add .
   git commit -m "config ui initial version"
   
   # 推送分支
   git push origin config_ui
   ```

5. 由管理员进行合并branch

6. 每次打开项目进行开发时，推荐进行pull操作进行更新

   ```powershell
   git pull origin master
   ```

   
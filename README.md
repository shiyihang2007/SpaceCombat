## Space Combat

### Overview

```plain
+----------+
|  ^   W   |
|   ^  :   |
| V ^  :  v|
| .  ^v:   |
| .  ^ : v |
| .  o :   |
| .    :   |
+----------+
```

Just like this.

### Build

**不再需要手动更新，CMake 会在构建时自动下载子模块。**

~~注意： 本项目使用 git submodule，在执行下面的操作之前，你需要运行以下指令以确保第三方文件完整：~~

```shell
git submodule update --init --recursive
```

#### Linux

首先，使用以下指令安装依赖（如果你使用 root 账户，可删去 sudo）：

```shell
sudo apt install cmake ninja g++ gcc libgl-dev libx11-dev libpthread-stubs0-dev libxrandr-dev libxi-dev
```

然后，将项目克隆至你喜欢的目录下，（后文中提到的 `${srcDir}` 均指代该目录），运行以下命令：

```shell
mkdir ${srcDir}/build && cd ${srcDir} && cmake -G Ninja .. && ninja SpaceCombat
```

完成后，你将会在 `${srcDir}` 下找到生成的 `SpaceCombat` 可执行文件。
你可以将此文件和 `${srcDir}` 下的 `shader`，`texture` 和 `level` 文件夹一同打包或移至你喜欢的位置。

#### Windows

首先，安装 [CMake](https://cmake.org/download/) 和 [Ninja](https://github.com/ninja-build/ninja/releases/) 构建系统。

然后，将项目克隆至你喜欢的目录下，（后文中提到的 `${srcDir}` 均指代该目录），运行以下命令：

```shell
mkdir ${srcDir}/build && cd ${srcDir} && cmake -G Ninja .. && ninja SpaceCombat
```

完成后，你将会在 `${srcDir}` 下找到生成的 `SpaceCombat.exe` 可执行文件。
你可以将此文件和 `${srcDir}` 下的 `shader`，`texture` 和 `level` 文件夹一同打包或移至你喜欢的位置。

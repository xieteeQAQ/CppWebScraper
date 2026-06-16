# WebScraper - C++ 学生信息爬虫

一个用 C++ 编写的网络爬虫项目，用于搜索和爬取学生信息

## 项目描述

这是一个学习项目，演示如何使用 C++ 结合现代网络库来实现网络爬虫功能。程序通过 HTTP 请求查询特定学校的学生信息数据库，解析返回的 JSON 数据，并将结果展示给用户

## 主要功能

- 交互式命令行界面，支持多次查询
- 按学生姓名搜索学生信息
- 支持多个学年的数据搜索（2023、2024、2025）
- 实时进度条显示搜索进度
- 自动保存爬取的数据到本地文件
- 内置自动重试机制，处理网络异常
- ⏱随机延迟以避免频繁请求

## 🛠️ 技术栈

- **语言**: C++11
- **构建系统**: CMake 3.10+
- **主要依赖**:
  - **CURL**: 用于 HTTP 请求
  - **nlohmann/json**: 用于 JSON 解析和处理

## 项目结构

```
CppWebScraper/
├── CMakeLists.txt          # CMake 构建配置文件
├── README.md               # 项目说明文档
├── .gitignore              # Git 忽略文件
├── bin/
│   └── WebScraper          # 编译后的可执行文件
├── build/                  # 构建输出目录
├── include/
│   └── request.hpp         # 请求相关的头文件
├── receive/
│   └── receive.txt         # 爬取数据的输出文件
└── src/
    ├── main.cpp            # 主程序入口
    └── request.cpp         # 网络请求实现
```

##  快速开始

### 前置要求

- windows 或 macOS 或 Linux 系统
- CMake 3.10 或以上
- C++11 兼容的编译器（GCC、Clang 等）
- 已安装 CURL 库和 nlohmann/json 库

### 安装依赖

**macOS（使用 Homebrew）**:
```bash
brew install curl nlohmann-json
```

**Linux（Ubuntu/Debian）**:
```bash
sudo apt-get install libcurl4-openssl-dev nlohmann-json3-dev
```

- 暂不提供 windows系统 的安装方式

### 编译

```bash
# 创建并进入构建目录
mkdir -p build
cd build

# 运行 CMake 配置
cmake ..

# 编译
make

# 或使用 ninja（如果已安装）
ninja
```

编译成功后，可执行文件位于 `bin/WebScraper`。

### 运行

```bash
./bin/WebScraper
```

## 使用说明

1. 程序启动后会显示欢迎信息
2. 输入要搜索的学生姓名，按 Enter 确认
3. 程序将在 2023-2025 年级中搜索该学生
4. 搜索完成后显示结果（学号、姓名、班级信息）
5. 输入 `q` 或 `Q` 退出程序，其他输入继续下一次查询

**示例运行**:
```
>>> coded by C++

hello world!
who would you want to find? (press "q" or "Q" to exit)
name: anyone

it will take about half a minute

finding in 2023...
[#########################################] 100% (32/32) done

finding in 2024...
[#########################################] 100% (36/36) done

finding in 2025...
[#########################################] 100% (36/36) done


Successfully found: 
code: a unmber | name: anyone | dept: ...
code: a number | name: anyone | dept: ...

press "q" or "Q" to exit, else continue: q
```

## 核心代码说明

### 主要函数

| 函数 | 说明 |
|------|------|
| `WriteCallback` | CURL 回调函数，处理响应数据 |
| `WriteData` | 将爬取的数据写入文件 |
| `GenerateID` | 生成学生 ID |
| `GenerateURL` | 生成 API 请求 URL |
| `Request` | 执行 HTTP 请求并处理响应 |
| `printProgress` | 显示搜索进度条 |
| `clear` | 清空终端屏幕 |

### 关键特性

- **自动重试**: 网络请求失败时自动重试，最多重试 3 次
- **随机延迟**: 请求间隔为 100-400ms 的随机值(可在源码中修改)，避免被服务器限流
- **进度显示**: 实时显示当前学年的搜索进度
- **数据持久化**: 所有响应数据保存到 `receive/receive.txt`

## 数据输出

爬取的数据保存在 `receive/receive.txt` 文件中，包括：
- JSON 格式的成功响应
- HTML 格式的错误页面

成功的响应格式：
```json
{
  "rs": [
    {
      "ROW_NUMBER": "1",
      "personcode": "a number",
      "personname": "anyone",
      "dptlongname": "..."
    }
  ],
  "state": "1"
}
```

## 注意事项

- 程序包含服务器特定的 Cookie 和 Referer，如需修改目标服务器请更新相关配置
- 请合理控制请求频率，避免对目标服务器造成压力
- 此项目仅作学习用途，使用请遵守法律和道德规范

## 许可证

学习项目，可自由修改和使用。

---

**最后更新**: 2026年6月16日

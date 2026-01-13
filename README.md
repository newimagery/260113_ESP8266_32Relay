# 260113_ESP8266_32Relay

## 项目介绍

这是一个基于ESP8266微控制器的32路继电器控制项目，支持通过WiFi和MQTT协议远程控制继电器。

## 功能特性

- 支持32路继电器独立控制
- 通过WiFi连接网络
- 使用MQTT协议进行远程通信
- 支持单路继电器的开启和关闭
- 可通过MQTT客户端（如MQTTX）进行控制
- 提供Arduino IDE兼容的示例代码

## 硬件需求

- ESP8266开发板（如ESP-12F）
- 32路继电器模块（使用HC595移位寄存器驱动）
- HC595移位寄存器
- 电源供应（根据继电器模块需求）
- 连接线若干

## 软件需求

### 开发环境
- VS Code + PlatformIO插件
- 或 Arduino IDE

### 依赖库
- ESP8266WiFi
- PubSubClient

## 快速开始

### 使用VS Code + PlatformIO

1. 克隆整个项目到本地：
   ```bash
   git clone <repository-url>
   ```

2. 打开VS Code并安装PlatformIO插件

3. 打开项目文件夹

4. 根据需要修改WiFi和MQTT配置（`src/main.cpp`）：
   ```cpp
   // WiFi Configuration
   const char* ssid = "Your_WiFi_SSID";
   const char* password = "Your_WiFi_Password";
   
   // MQTT Configuration
   const char* mqtt_server = "broker.emqx.io";
   const int mqtt_port = 1883;
   ```

5. 编译并上传代码到ESP8266开发板

### 使用Arduino IDE

1. 从`Docs/ArduinoSampleCode`目录获取示例代码

2. 打开Arduino IDE并安装ESP8266开发板支持

3. 安装所需库：ESP8266WiFi, PubSubClient

4. 打开`ESP8266_X32_TEST.ino`文件

5. 根据需要修改WiFi和MQTT配置

6. 编译并上传代码到ESP8266开发板

## 使用说明

### MQTT控制命令

通过MQTT客户端发送以下格式的命令到主题`relay/control`：

- 开启继电器：`on_X`（X为继电器编号，1-32）
  示例：`on_1` - 开启继电器1

- 关闭继电器：`off_X`（X为继电器编号，1-32）
  示例：`off_1` - 关闭继电器1

### MQTT客户端推荐

推荐使用[MQTTX](https://mqttx.app/downloads)作为MQTT客户端进行测试和控制。

## 项目结构

```
260113_ESP8266_32Relay/
├── .gitignore          # Git忽略文件配置
├── Docs/               # 项目文档
│   ├── ArduinoSampleCode/  # Arduino IDE兼容的示例代码
│   └── EN/             # 英文文档
├── include/            # 头文件目录
├── lib/                # 库目录
├── platformio.ini      # PlatformIO配置文件
├── src/                # 源代码目录
│   └── main.cpp        # 主程序文件
└── test/               # 测试目录
```

## 引脚定义

| 功能 | ESP8266引脚 |
|------|-------------|
| HC595_SI (数据) | D5 (GPIO14) |
| HC595_SCK (时钟) | D7 (GPIO13) |
| HC595_RCK (锁存) | D6 (GPIO12) |
| HC595_G (使能) | D1 (GPIO5) |

## 示例代码

### 开启继电器1

```cpp
RelayON(1);
```

### 关闭继电器1

```cpp
RelayOFF(1);
```

### 循环控制所有继电器

```cpp
for (int i = 1; i <= 32; i++) {
  RelayON(i);
  delay(100);
}

for (int i = 1; i <= 32; i++) {
  RelayOFF(i);
  delay(100);
}
```

## 文档

- `Docs/EN/`：包含ESP8266相关的英文文档
- `Docs/ArduinoSampleCode/`：Arduino IDE兼容的示例代码

## 许可证

本项目采用MIT许可证。

## 联系方式

如有问题或建议，请通过以下方式联系：

- Email: [your-email@example.com]
- GitHub: [your-github-username]

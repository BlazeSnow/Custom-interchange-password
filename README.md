# 自定义密码

1. 此项目使用csv文件作为自定义密码的存放文件
2. 密码互换方式可以通过修改csv文件进行自定义

## 如何下载？

前往 [GitHub Release](https://github.com/BlazeSnow/Custom-interchange-password/releases/latest) 下载对应系统的可执行文件。

文件命名格式为 `Custom-interchange-password-<版本>-<系统>-<架构>`，各平台对应关系如下：

| 文件名后缀           | 适用平台               |
| -------------------- | ---------------------- |
| `-windows-x64.exe`   | Windows x64            |
| `-windows-arm64.exe` | Windows ARM64          |
| `-linux-x64`         | Linux x64              |
| `-linux-arm64`       | Linux ARM64            |
| `-macos-x64`         | macOS（Intel）         |
| `-macos-arm64`       | macOS（Apple Silicon） |

## Linux / macOS 额外处理

```sh
sudo chmod +x <可执行文件>
```

## 更新日志

见 [CHANGELOG.md](./CHANGELOG.md)

## 许可证

[MIT](./LICENSE)

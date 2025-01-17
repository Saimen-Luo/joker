# Joker

[English](readme.md)

[🗣 News](https://t.me/txthinking_news)
[💬 Chat](https://join.txthinking.com)
[🩸 Youtube](https://www.youtube.com/txthinking) 
[❤️ Sponsor](https://github.com/sponsors/txthinking)

Joker可以将进程变成守护进程.

❤️ A project by [txthinking.com](https://www.txthinking.com)

### 用 [nami](https://github.com/txthinking/nami) 安装

```
$ nami install joker
```

或者从源码编译

```
$ make
$ make LDFLAGS=-static -s # statically link and strip
```

### 使用

    joker: run command as daemon

    	<command>   run your command

    	help        show help
    	version     show version

### 举例

    $ joker brook server -l :9999 -p password

### 日志文件在哪里?

/tmp/joker.log

### 为什么

已经有几个类似软件, 比如 systemd, supervisord, 等.
但是我需要一个简单, 小巧, 干净, 无需配置的软件. 所以写了joker. joker不依赖systemd.

### 开机自动启动

你可能喜欢 [txthinking/jinbe](https://github.com/txthinking/jinbe)

## 开源协议

基于 GPLv3 协议开源

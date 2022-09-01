# Joker

[中文](readme_zh.md)

[🗣 News](https://t.me/txthinking_news)
[💬 Chat](https://join.txthinking.com)
[🩸 Youtube](https://www.youtube.com/txthinking) 
[❤️ Sponsor](https://github.com/sponsors/txthinking)

Joker can turn process into daemon.

❤️ A project by [txthinking.com](https://www.txthinking.com)

### Install via [nami](https://github.com/txthinking/nami)

```
$ nami install joker
```

or build from Source

```
$ make
$ make LDFLAGS=-static -s # statically link and strip
```

### Usage

    joker: run command as daemon

    	<command>   run your command

    	help        show help
    	version     show version

### Example

    $ joker brook server -l :9999 -p password

### Where are log files?

/tmp/joker.log

### Why

There are many tools, such as systemd, supervisord, etc.
But I need a simple, small, clean, no configuration tool. Joker does **not** depend on systemd.

### Auto start command at boot

You may like [txthinking/jinbe](https://github.com/txthinking/jinbe)

## License

Licensed under The GPLv3 License

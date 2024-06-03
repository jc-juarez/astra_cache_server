# Astra Cache Server ⚡🌗

Astra Cache Server is a fast performance local-storage HTTP caching server implemented in C++ for GNU/Linux derived operating systems.

How to Run Astra
==========

First, ensure syslog is running on the GNU/Linux system:
```shell
sudo service rsyslog start
```

Then, run astra as follows:
```shell
./astra
```

Astra allows configuration changes through command line arguments. Currently supported configurable options are as follows:

* Debug mode flag `-d`: This flag allows to turn on/off debug logs printed to the console. Example usage: `-d=on`, `-d=off`.

* Logs directoy location flag `-l`: This flag allows to sepcify the location where the logs for the given session will be stored. Example usage: `-l=/home/astra-user/logs`.

* Server port number flag `-p`: This flag allows to sepcify the port number to run the server. Example usage: `-p=8000`.

How to Build Astra from source
==========

For building Astra Cache Server from source in a GNU/Linux distribution, first ensure that you have a C++ compiler that supports `C++20`.

After doing so, follow the instructions listed in the [libhttpserver repository](https://github.com/etr/libhttpserver) for installing the required HTTP server dependencies.

Then, clone this repository:
```shell
git clone https://github.com/jc-juarez/modula_replication_engine/
```
And finally run the build script:
```shell
chmod +x build.sh && ./build.sh
```
The output `modula` file will be located under the `build` directory.
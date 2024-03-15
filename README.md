# php-webview

This is a simple PHP extension for writing simple, cross-platform GUI applications using PHP. It uses the webview library to create a small, lightweight, cross-platform application that can be used to create simple GUI applications.

Internally, it uses the [webview](https://github.com/webview/webview) library.

# Supported Platforms

In theory, this extension should work on windows, mac & linux but only tested on windows & mac so far.

# Before you start
You'll need basic tools for C compilation. On mac, the gnu compiler is recommended. On windows, you can use the Visual Studio compiler.

Before compiling the extension, you'll need to install the webview library. Example commands for mac are:

```bash
brew install gcc git
git clone https://github.com/webview/webview.git
cd webview
./script/build.sh build
cp build/library/libwebview.dylib /usr/local/lib
cp webview.h /usr/local/include
```

For linux, you can use the following commands:

```bash
sudo apt-get install -y libgtk-3-dev libwebkit2gtk-4.0-dev
git clone https://github.com/webview/webview.git
cd webview
./script/build.sh build
sudo cp build/library/libwebview.so /usr/lib
sudo cp webview.h /usr/include
```

If you face any issue, or you want to work in windows, please consult the [Getting Started](https://github.com/webview/webview?tab=readme-ov-file#getting-started) section of the webview library.

# Installation
On linux the process is simple. Just run the following commands after cloning the repository:

```bash
phpize
./configure
make
sudo make install
```

On mac, you might have to set a few environment variables before running the above commands. For example:

```bash
export LDFLAGS="-L/usr/local/lib -lwebview"
export CFLAGS="-I/usr/local/include"
export CC=gcc-13 # or whatever version of gcc you have
phpize
./configure
make
make install
```
Note that you can pass these env variables as arguments for the configure command. This will be fixed in the future so that you don't have to do this.

# Usage

See the [webview.stub.php](webview.stub.php) file for the class signature. Also, checkout the [examples](examples) directory for some examples.

# Known Issues
There's a few issues like some random crashes especially during the creation and destruction of the webview object. Also, all the functions are not yet implemented. They'll be implemented in the future when needed.
 The installation process should also be improved. In theory, it should be possible to skip the installation of the webview library.
If you face any issue, please open an issue in the repository. If you can fix it, please open a pull request.

# License

MIT

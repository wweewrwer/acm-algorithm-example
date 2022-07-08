#### QT安装

请不要选择6.0以上的版本，没有charts支持且资料少，选用5.x的版本，安装时把QT charts、Qt Data Visualization圈上即可

#### 常用组件

##### 对话框

```
QDialog dialog(this);
dialog.exec();//模态对话框
dialog->show();//非模态对话框
```

##### 文件对话框

一律通过打开文件名的方式，然后用cpp的其它方式去读

```
QFileDialog::getOpenFileName(this,"open file","/","text file(*.txt);;C file(*.cpp);;All file(*.*)");
```

c++自身的读文件：

https://blog.csdn.net/weixin_43229348/article/details/124585553

方便起鉴，一律采用c的方式读文件：

https://www.runoob.com/cprogramming/c-file-io.html

| 模式 | 描述                                                         |
| :--- | :----------------------------------------------------------- |
| r    | 打开一个已有的文本文件，允许读取文件。                       |
| w    | 打开一个文本文件，允许写入文件。如果文件不存在，则会创建一个新文件。在这里，您的程序会从文件的开头写入内容。如果文件存在，则该会被截断为零长度，重新写入。 |
| a    | 打开一个文本文件，以追加模式写入文件。如果文件不存在，则会创建一个新文件。在这里，您的程序会在已有的文件内容中追加内容。 |
| r+   | 打开一个文本文件，允许读写文件。                             |
| w+   | 打开一个文本文件，允许读写文件。如果文件已存在，则文件会被截断为零长度，如果文件不存在，则会创建一个新文件。 |
| a+   | 打开一个文本文件，允许读写文件。如果文件不存在，则会创建一个新文件。读取会从文件的开头开始，写入则只能是追加模式。 |

如果处理的是二进制文件，则需使用下面的访问模式来取代上面的访问模式：

```
"rb", "wb", "ab", "rb+", "r+b", "wb+", "w+b", "ab+", "a+b"
```

开关文件：

```
FILE *fopen( const char *filename, const char *mode );
int fclose( FILE *fp );
```

读写文件一律用fprintf或者fscanf或fgets(fgets包含\n）。

```
char *fgets( char *buf, int n, FILE *fp );
```

##### 输入对话框

在ui界面拖动text edit即可，假设名字为strInput,则获取输入窗口内容函数为

```
QString s=ui->strInput->toPlainText();
```

之后所有的类型转换都手动通过sscanf和sprintf完成。

##### 其它作图

https://www.cnblogs.com/arv000/p/16410386.html


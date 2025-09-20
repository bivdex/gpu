# Vanity Search
作用：在指定Bitcoin地址的前缀或前缀+后缀的情况下，搜索得到符合条件的私钥；该项目采用CUDA加速了搜索过程。

## 编译
在Visual Studio中打开VanitySearch.sln，选择Release配置，编译后运行VanitySearch.exe。

在NVidia RTX4090显卡上，其计算架构参数为compute_89, sm_89，要在nvcc的编译参数中加上。

目前是在Visual Studio 2022 + CUDA 12.6的环境下编译通过的。

## 运行
VanitySearch运行参数众多，下面就常用的地址搜索情况进行示例说明。

1. ./VanitySearch.exe -stop -gpu 1abcdef

该命令表示搜索以1abcdef为prefix的的Bitcoin地址，-stop表示搜索到第一个符合条件的地址就停止，-gpu表示使用GPU加速。

2. ./VanitySearch.exe -stop -gpu 1abc*def

该命令表示搜索以1abc为prefix，def为suffix的Bitcoin地址，中间可以有任意字符。

3. ./VanitySearch.exe -stop -gpu 3abc * def * （实际运行时把*前后的空格去掉）

该命令表示搜索以3abc为prefix，中间包含def为suffix的Bitcoin地址。

需要说明的是，在只包含prefix的搜索中，支持1开头，3开头及bc1开头的地址搜索；

在包含prefix和suffix的搜索中，只支持1开头、3开头的地址搜索，bc1开头的地址尚未支持。

4. ./VanitySearch.exe -stop -cpu -i prefix1.txt,prefix2.txt,prefix3.txt

其中-i表示输入文件，各文件以逗号分隔，每个文件中包含一类prefix，每行一个prefix。

程序会依次搜索每个文件，每个文件中的每个prefix运行5分钟，如果5分钟内没有找到符合条件的地址，就开启一个新任务继续搜索。

## 运行时间参考
下面是在NVidia RTX4090显卡上运行的部分实验时间参考（以下时间仅供参考，因为尚未进行充分的多次试验，也没有对算法运行时间进行理论分析）：

1. ./VanitySearch.exe -stop -gpu bc1qautumnau

prefix=8字符，约3mins找到结果，如bc1qautumnau；

prefix=9字符，在15-20mins内找到结果，如bc1qautumnaut；

prefix=10字符，在2.5h内没有找到结果，如bc1qautumnautm。

2. ./VanitySearch.exe -stop -gpu 1abc*def

在prefix=suffix=2字符的情况下，在1秒内得到结果；

在prefix=suffix=3字符的情况下，在5-10分钟内得到结果；

在prefix=3/4，suffix=4/3字符的情况下，进行了2次实验，分别在16/36小时得到结果；

在prefix=suffix=4字符的情况下，在17小时内没有得到结果。

3. ./VanitySearch.exe -stop -gpu 3abc * def * （实际运行时把*前后的空格去掉）

在prefix=suffix=2字符的情况下，在1秒内得到结果；

在prefix=suffix=3字符的情况下，在40秒-2.3分钟内得到结果；

在prefix=3/4，suffix=4/3字符的情况下，进行了2次实验，分别在1/2小时内得到结果；

在prefix=suffix=4字符的情况下，在72小时内没有得到结果。
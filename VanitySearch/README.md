# Vanity Search
���ã���ָ��Bitcoin��ַ��ǰ׺��ǰ׺+��׺������£������õ�����������˽Կ������Ŀ����CUDA�������������̡�

## ����
��Visual Studio�д�VanitySearch.sln��ѡ��Release���ã����������VanitySearch.exe��

��NVidia RTX4090�Կ��ϣ������ܹ�����Ϊcompute_89, sm_89��Ҫ��nvcc�ı�������м��ϡ�

Ŀǰ����Visual Studio 2022 + CUDA 12.6�Ļ����±���ͨ���ġ�

## ����
VanitySearch���в����ڶ࣬����ͳ��õĵ�ַ�����������ʾ��˵����

1. ./VanitySearch.exe -stop -gpu 1abcdef

�������ʾ������1abcdefΪprefix�ĵ�Bitcoin��ַ��-stop��ʾ��������һ�����������ĵ�ַ��ֹͣ��-gpu��ʾʹ��GPU���١�

2. ./VanitySearch.exe -stop -gpu 1abc*def

�������ʾ������1abcΪprefix��defΪsuffix��Bitcoin��ַ���м�����������ַ���

3. ./VanitySearch.exe -stop -gpu 3abc * def * ��ʵ������ʱ��*ǰ��Ŀո�ȥ����

�������ʾ������3abcΪprefix���м����defΪsuffix��Bitcoin��ַ��

��Ҫ˵�����ǣ���ֻ����prefix�������У�֧��1��ͷ��3��ͷ��bc1��ͷ�ĵ�ַ������

�ڰ���prefix��suffix�������У�ֻ֧��1��ͷ��3��ͷ�ĵ�ַ������bc1��ͷ�ĵ�ַ��δ֧�֡�

4. ./VanitySearch.exe -stop -cpu -i prefix1.txt,prefix2.txt,prefix3.txt

����-i��ʾ�����ļ������ļ��Զ��ŷָ���ÿ���ļ��а���һ��prefix��ÿ��һ��prefix��

�������������ÿ���ļ���ÿ���ļ��е�ÿ��prefix����5���ӣ����5������û���ҵ����������ĵ�ַ���Ϳ���һ�����������������

## ����ʱ��ο�
��������NVidia RTX4090�Կ������еĲ���ʵ��ʱ��ο�������ʱ������ο�����Ϊ��δ���г�ֵĶ�����飬Ҳû�ж��㷨����ʱ��������۷�������

1. ./VanitySearch.exe -stop -gpu bc1qautumnau

prefix=8�ַ���Լ3mins�ҵ��������bc1qautumnau��

prefix=9�ַ�����15-20mins���ҵ��������bc1qautumnaut��

prefix=10�ַ�����2.5h��û���ҵ��������bc1qautumnautm��

2. ./VanitySearch.exe -stop -gpu 1abc*def

��prefix=suffix=2�ַ�������£���1���ڵõ������

��prefix=suffix=3�ַ�������£���5-10�����ڵõ������

��prefix=3/4��suffix=4/3�ַ�������£�������2��ʵ�飬�ֱ���16/36Сʱ�õ������

��prefix=suffix=4�ַ�������£���17Сʱ��û�еõ������

3. ./VanitySearch.exe -stop -gpu 3abc * def * ��ʵ������ʱ��*ǰ��Ŀո�ȥ����

��prefix=suffix=2�ַ�������£���1���ڵõ������

��prefix=suffix=3�ַ�������£���40��-2.3�����ڵõ������

��prefix=3/4��suffix=4/3�ַ�������£�������2��ʵ�飬�ֱ���1/2Сʱ�ڵõ������

��prefix=suffix=4�ַ�������£���72Сʱ��û�еõ������
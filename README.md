# UpdateVersion  
  
![版本更新](https://img.shields.io/badge/build-passing-green.svg)
[![版本更新](https://img.shields.io/badge/release-v1.0.0.1-blue.svg)](https://github.com/Doctor-Feng/UpdateVersion)
![logo](https://img.shields.io/badge/license-MIT-9cf.svg)

## 简介 

版本更新系统，基于C++编写的下载文件程序。本程序的设计目的是，如果系统复杂，配置文件繁多，在版本更新或者更新程序的时候，需要有较专业的知识，

将不同的更新文件复制到不同的路径下，这对技术服务人员或者现场工作人员的要求较高。为了降低或者消除这种压力，故设计了这个更换程序的更新系统。

只需要点击下按钮，就可以实现更新了。

## 先决条件

本程序是在 `Visual Studio 2010 `下生成的<B> EXE </B>可执行程序。  

所需动态库文件:  
``` 
UrlMon.h
UrlMon.Lib
```
系统配置文件:  默认生成

数据库文件:  无


## 软件界面

   <figure class="half">
   <img src="https://github.com/fdh0/files/blob/master/3.gif?raw=true" height="300" title="软件使用">
   <img src="https://github.com/fdh0/files/blob/master/081702.PNG?raw=true" height="300" title="软件主界面">
   <img src="https://github.com/fdh0/files/blob/master/081703.PNG?raw=true" height="300" title="软件设置界面">

   </figure>  

## 注意事项

1. 无

## 版本更新

#### 版本号：1.0.0.1 --  `[2019-08-17]`

<b>主要更新如下:</b> 

1. 增加了服务器网址和文件保存路径的配置；![](https://github.com/fdh0/files/blob/master/improved.png?raw=true)

2. 通过正则匹配网页中指定的文件类型；

<b>关键代码：</b>  

搜索关键词： GetDataFromHtml

```
afx_msg bool GetDataFromHtml(const char *html, regex patterns,std::vector<CString> &results)
	{
		std::smatch match;
		std::string html_data = html;
		while (std::regex_search(html_data, match, patterns))
		{
			results.push_back(match[0].str().c_str());
			html_data = match.suffix();
		}

		if(results.size()>0)
			return true;
		else
			return false;
	}
```


## 作者
 
* ** 冯东海 ** 


## 许可证

该项目根据MIT许可证授权。

版权所有?2019 ****************公司

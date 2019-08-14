# pdateVersion  
  
![版本更新](https://img.shields.io/badge/build-passing-green.svg)
[![版本更新](https://img.shields.io/badge/release-v4.4.8.6637-blue.svg)](http://coding.daheng-imavision.com/p/BQ_PDF_Check/git/blob/master/README.md#user-content-%E7%89%88%E6%9C%AC%E6%9B%B4%E6%96%B0)
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
系统配置文件:  无

数据库文件:  无


## 软件界面

   <figure class="half">
  
   <img src="https://github.com/fdh0/files/blob/master/%E6%90%9C%E7%8B%97%E6%88%AA%E5%9B%BE20190214141957.jpg?raw=true" height="300" title="软件主界面">
   <img src="https://github.com/fdh0/files/blob/master/%E6%90%9C%E7%8B%97%E6%88%AA%E5%9B%BE20190214141852.jpg?raw=true" height="300" title="软件使用界面">

   </figure>  

## 注意事项

1. 由于采用光流法，与之前的不同，需要调整变形系数。但具体调整多少，尚没有一个较好的定式，并且会出现校正过度的问题，因此调整参数是个问题。   ![](https://github.com/fdh0/files/blob/master/question.png?raw=true)
 
      
2. 由于使用了光流法，会导致缺陷的显示位置有所偏差，大约在几个像素内。  当前未想到较好的解决方法。   ![](https://github.com/fdh0/files/blob/master/question.png?raw=true)
   
   <figure class="center">
   <img src="https://github.com/fdh0/files/blob/master/position_shift_PDF.PNG?raw=true" width="800" title="位置偏移">
   </figure>    
   <br>
  
   <figure class="half">
   <img src="https://github.com/fdh0/files/blob/master/shape_factor_0.05.PNG?raw=true" width="400" title="变形因子0.05">
   <img src="https://github.com/fdh0/files/blob/master/shape_factor_0.15.PNG?raw=true" width="400" title="变形因子0.15">
   </figure>  


## 版本更新

#### 版本号：1.0.0.0 --  `[2019-08-14]`

<b>主要更新如下:</b> 

1. 对于大变形区域，根据区域进行读取、保存参数。这样能够允许检测中绘制多个检测参数不同的大变形区域。![](https://github.com/fdh0/files/blob/master/improved.png?raw=true)

2. 修改大变形区域自动阈值的方法。 这一点需要说明，之前使用大小模板的时候，是将当前检测图像与大小模板进行比较，阈值范围比较小。

目前使用的是当前检测图直接与建模模板图比较，这就导致可能不同的环境下不同的检测产品，检测阈值就不同。没有一个较好的指导准则。
 
因此，引出自动阈值的方法。使其自动寻求一个较合理的阈值。

<b>关键代码：</b> 

ParaDlg.cpp   -- OnInitDialog  

搜索关键词： 3/21/2019

```
//[11/29//2018 fdh] 增加大变形特检对话框
if (PM_AT_DBX == nInnerAlgType)
{
  nParamID =  m_lstAlgRegPro.at(0).sAlgRegCheckPro.ParamID;
  // [3/21/2019 fdh] 在这里加上大变形按区域保存的参数
  m_sTempCheckParam.sDBXParam.nHThresh = m_sTempCheckParam.lstPrevelExt.at(nParamID).Upper.Tolerance;
  m_sTempCheckParam.sDBXParam.dArea_white=m_sTempCheckParam.lstPrevelExt.at(nParamID).Upper.dArea;		
  m_sTempCheckParam.sDBXParam.nLThresh = m_sTempCheckParam.lstPrevelExt.at(nParamID).Lower.Tolerance;
  m_sTempCheckParam.sDBXParam.dArea=m_sTempCheckParam.lstPrevelExt.at(nParamID).Lower.dArea;
}
```


## 作者
 
* ** 冯东海 ** 


## 许可证

该项目根据MIT许可证授权。

版权所有?2019 ****************公司

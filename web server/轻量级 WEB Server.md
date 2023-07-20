## 轻量级 WEB Server

### 1. 需求分析

需要在设备内部集成WEB管理功能，类似于家用路由器，通过网页浏览器登陆设备，实现对设备进行状态监视、参数设置、固件升级等功能。

硬件条件：设备内部主控制器的嵌入式CPU普遍低端，主频只有几百兆，内存有128M的，也有的只有几百K片上配置，WEB管理功能的集成不能影响设备网络主业务性能，可能无文件系统。

轻量级 WEB Server
首先要找一个合适的轻量级的WEB Server，最好是C/C++实现的，有OS和没有OS都能方便移植。WEB Server不需要太复杂，能支持1种动态语言，提供良好的CGI接口。
设备管理架构 Device Manager Framework
以轻量级的WEB Server为基础，提供一个设备管理框架，可通过代码直接定制目录结构，可直接修改模板增减状态和配置页面。

使用AJAX等技术实现不重新加载页面的情况下，刷新网页局部，实现设备状态“实时”监视功能。

### 2. 轻量级WEB Server 对比

开源的轻量级WEB Server很多，比如GoAhead、Shttpd、Thttpd、Lighttpd、BOA、mathopd、minihttpd、appweb，但适合于移植到嵌入式平台的并不多。

#### GoAhead
GoAhead基于C语言的嵌入式WEB Server，由Embedthis公司维护，实现了服务端的嵌入式Javascript、CGI、DHTML,支持文件上传，网上资料比较多，最新V3.6.3源码在这。

GoAhead本身自带Windows、Linux、各种RTOS的移植子目录文件，其他服务器公共模块移植性做的很好，可不使用文件系统而将所有WEB资源文件ROM化，是学习进阶C语言的很好例子。若开发linux平台下的web监控，你可以利用windows下的vs先调试好JS+CSS前端，再去linux平台下解决数据交互层面的问题。

#### BOA
BOA 服务器是一个小巧高效的web服务器，是一个运行于unix或linux下的，支持CGI的、适合于嵌入式系统的单任务的http服务器。
源代码开放、性能高。由于它是一个单任务的Web服务器,只能一次完成用户的请求,而不会fork出新的进程来处理并发的链接请求。但是Boa支持Cgi,能够为Cgi程序fork出一个进程来执行相应的客户请求。

#### Lighttpd
Lighttpd是一个德国人领导的开源Web服务器软件，具有非常低的内存开销、cpu占用率低、性能好以及丰富的模块等特点，相比GoAhead更专业，支持php，当然更占点资源。Lighttpd是众多OpenSource轻量级的web server中较为优秀的一个。支持FastCGI，CGI，Auth，输出压缩（output compress），URL重写，Alias等重要功能。

lighttpd针对web并发请求的特点，采用事件驱动模式架构以提高性能，可以看作是一个轻量级的Apache，消耗内存更少，Apahche的很多功能在lighttpd上都有相应的实现。lighttpd支持FastCGI，利用临时内存文件快速响应HTTP请求；支持COMET，服务器端的主动推送技术；并支持异步IO模式的响应。

#### uHttpd
uHTTPd是一个OpenWrt/LUCI 开发者从头编写的Web服务器，能满足嵌入式设备在linux平台下的轻量级任务需求，使用select模型进行多请求并发处理。

uHTTPd是OpenWRT上默认的Web服务器，支持CGI，以及静态文件的服务，很多路由器使用OpenWRT架构，顺便使用支持lua的uHTTPd开发管理界面。通过Luci处理CGI请求，实现基于Lua脚本的web开发。

#### busybox httpd
busybox是嵌入式Linux下的开发“瑞士军刀”，基本上Android手机上都有安装；httpd是busybox的附带工具之一，轻量级，支持CGI。用的人少


问题记录
========

在 “7.6.1 链接器如何解析多重定义的全局符号” 中，有给出Unix链接器处理多重定义符号的规则：

1. 规则1：不允许有多个强符号
2. 规则2：如果有一个强符号和多个弱符号，那么选择强符号
3. 规则3：如果有多个弱符号，那么从中选择任意一个

但是在实际的编译过程中，编译器都会对多重定义的全局符号报错。
Introduction
============


## Problems

### 1. 7.6.1 实际编译错误

在 “7.6.1 链接器如何解析多重定义的全局符号” 中，有给出Unix链接器处理多重定义符号的规则：

1. 规则1：不允许有多个强符号
2. 规则2：如果有一个强符号和多个弱符号，那么选择强符号
3. 规则3：如果有多个弱符号，那么从中选择任意一个

但是在实际的编译过程中，编译器都会对多重定义的全局符号报错。（GCC版本信息 `gcc (Debian 10.2.1-6) 10.2.1 20210110`）

### 2. What is different of R_X86_64_PC32 and R_X86_64_PLT32

The main difference between R_X86_64_PC32 and R_X86_64_PLT32 is that R_X86_64_PC32 is a **PC-relative** relocation, while R_X86_64_PLT32 is a **PLT-relative** relocation.

A PC-relative relocation is a relocation that is calculated relative to the current instruction pointer. This means that the value of the relocation is the address of the symbol plus the offset of the instruction pointer from the start of the instruction.

A PLT-relative relocation is a relocation that is calculated relative to the address of the Procedure Linkage Table (PLT). The PLT is a table of addresses that is used to resolve calls to external functions. When a call to an external function is made, the address of the function is not known at compile time. Instead, the address of the function is stored in the PLT. When the call is executed, the address of the function is looked up in the PLT and the call is then redirected to the correct address.

The main difference between PC-relative and PLT-relative relocations is that PC-relative relocations are more efficient. This is because the value of the relocation can be calculated directly from the instruction pointer, without having to access the PLT. However, PC-relative relocations can only be used for functions that are within the same module. If a function is in a different module, then a PLT-relative relocation must be used.

In general, R_X86_64_PC32 should be used whenever possible. However, if a function is in a different module, then R_X86_64_PLT32 must be used.

Here is a table that summarizes the differences between R_X86_64_PC32 and R_X86_64_PLT32:

| Feature | R_X86_64_PC32 | R_X86_64_PLT32 |
|---|---|---|
| Type | PC-relative | PLT-relative |
| Efficiency | More efficient | Less efficient |
| Scope | Within the same module | Different modules |
| When to use | When possible | When necessary |

### 3. What is different of --reloc and --dynamic-reloc in objdump

The `-r` and `-R` options in objdump are used to print the relocation entries in an object file. The main difference between the two options is that `-r` prints all relocation entries, while `-R` only prints dynamic relocation entries.

* **Relocation entries** are used to modify the addresses of symbols in an object file so that they can be resolved at runtime.
* **Dynamic relocation entries** are a special type of relocation entry that is used for shared libraries.

When a shared library is loaded into memory, the dynamic linker will resolve the dynamic relocation entries in the library. This allows the library to be used by multiple different programs without having to modify the programs themselves.

The `-r` option is useful for debugging and understanding how relocations work. The `-R` option is useful for understanding how shared libraries work.

Here is a table that summarizes the differences between `-r` and `-R`:

| Option | Description |
|---|---|
| `-r` | Prints all relocation entries. |
| `-R` | Prints dynamic relocation entries only. |

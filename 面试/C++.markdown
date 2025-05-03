# C++ 面试知识点整理

## 一、核心语言与基础特性
在C++面试中，关于“**基本语法与数据类型**”的知识点，可能会被问到以下内容：

### 1.1. **基本类型**
---

#### **C++ 中常见的基本数据类型及范围和存储大小**
C++ 中常见的基本数据类型及其对应范围和存储大小（按标准）：
- **`int`**：整数类型，通常占用 **4T (32位)**，范围：
  - 有符号：`-2,147,483,648` 到 `2,147,483,647`
  - 无符号：`0` 到 `4,294,967,295`
- **`float`**：单精度浮点数，占用 **4字节 (32位)**，范围约为：
  - `±1.2 × 10^-38` 到 `±3.4 × 10^38`，精度为 6~7 位有效数字。
- **`double`**：双精度浮点数，占用 **8字节 (64位)**，范围约为：
  - `±2.3 × 10^-308` 到 `±1.7 × 10^308`，精度为 15~16 位有效数字。
- **`char`**：字符类型，占用 **1字节 (8位)**，范围：
  - 有符号：`-128` 到 `127`。
  - 无符号：`0` 到 `255`。
- **`bool`**：布尔类型，占用 **1字节**，值为 `true` 或 `false`。

---

#### **`signed` 和 `unsigned` 的区别**
- **`signed`**：表示有符号数，最高位为符号位（0 表示正数，1 表示负数）。如：
  - `signed int`：范围 `-2,147,483,648` 到 `2,147,483,647`。
- **`unsigned`**：表示无符号数，所有位用于表示值，范围更大，但不支持负数。如：
  - `unsigned int`：范围 `0` 到 `4,294,967,295`。

**注意：** 使用 `unsigned` 时需要小心溢出和下溢。例如：
```cpp
unsigned int x = 0;
x -= 1; // 溢出，结果为最大值 4,294,967,295。
```

---
                
### 1.2 **类型转换**
#### 1. **隐式类型转换**
- 编译器自动进行的类型转换，一般从 **低精度到高精度** 或 **兼容类型**。
- 例如：
  ```cpp
  int a = 10;
  double b = a; // 隐式转换：int 转为 double
  ```

#### 2. **显式类型转换**
- 程序员手动指定的类型转换，通常使用 C++ 提供的类型转换操作符：
  - **`static_cast`**：
    - 用于相关类型之间的安全转换，例如 `int` 到 `double`。
    - 示例：
      ```cpp
      int a = 10;
      double b = static_cast<double>(a);
      ```
  - **`reinterpret_cast`**：
    - 强制转换指针类型，用于重新解释内存地址，不保证安全性。
    - 示例：
      ```cpp
      int a = 10;
      int* p = &a;
      void* v = reinterpret_cast<void*>(p);
      ```
  - **`const_cast`**：
    - 用于去掉或添加 `const` 限定符。
    - 示例：
      ```cpp
      const int a = 10;
      int* p = const_cast<int*>(&a); // 去掉 const 限定
      ```
  - **`dynamic_cast`**：
    - 用于多态类型之间的安全转换，通常用于类的指针或引用。
    - 示例：
      ```cpp
      class Base { virtual void func() {} };
      class Derived : public Base {};
      Base* b = new Derived;
      Derived* d = dynamic_cast<Derived*>(b); // 安全的向下转换
      ```

#### 3. **C 风格类型转换与 C++ 类型转换的区别**
- C 风格类型转换：使用 `(type)` 的形式，没有安全检查，容易导致错误。
  - 示例：
    ```cpp
    int a = 10;
    double b = (double)a; // C 风格转换
    ```
- C++ 类型转换：
  - 引入了类型转换操作符（如 `static_cast`），在编译期进行类型检查，更安全。

**推荐：** 在 C++ 中优先使用 `static_cast`、`const_cast` 等。

---

### 1.3. **变量**
#### **1. 变量的定义与初始化方式**
- **变量的定义**：
  - 声明变量时需要指定其类型，例如：`int a;`。
  - 变量在使用前必须初始化，否则可能导致未定义行为（尤其是局部变量）。

- **初始化方式**：
  - **直接初始化**（Direct Initialization）：
    ```cpp
    int a(10);
    ```
  - **拷贝初始化**（Copy Initialization）：
    ```cpp
    int a = 10; // 编译器通过拷贝构造或赋值构造来初始化
    ```
  - **列表初始化**（List Initialization, C++11 引入）：
    ```cpp
    int a{10}; // 更安全，防止窄化转换（narrowing conversion）
    int b{};   // 初始化为默认值（如 0）
    ```

---

#### **2. 局部变量与全局变量的作用域和生命周期**
- **作用域**：
  - **局部变量**（Local Variables）：
    - 定义在函数或代码块内部，仅在所在的作用域内可见。
    - 超出作用域后，变量被销毁。
    ```cpp
    void func() {
        int a = 10; // 局部变量
    }
    // 变量 a 在此处不可见
    ```
  - **全局变量**（Global Variables）：
    - 定义在所有函数外部，整个程序都可访问。
    - 使用 `::` 作用域解析操作符可以显式访问全局变量。
    ```cpp
    int a = 10; // 全局变量
    void func() {
        ::a = 20; // 修改全局变量
    }
    ```

- **生命周期**：
  - **局部变量**：在所在作用域开始时创建，结束时销毁。
  - **全局变量**：在程序启动时创建，程序结束时销毁。

---

#### **3. 默认值（未初始化变量的行为）**
- **局部变量**：
  - 没有显式初始化的局部变量会保留内存中的原始值（**未定义行为**）。
  ```cpp
  void func() {
      int a; // 未定义行为，值不可预测
  }
  ```
- **全局变量和静态变量**：
  - 如果未初始化，会自动初始化为零值：
    - 整数类型初始化为 `0`。
    - 浮点类型初始化为 `0.0`。
    - 指针类型初始化为 `nullptr`。
    - 布尔类型初始化为 `false`。

---

####     **4. 变量的存储类别**
C++ 中变量的存储类别定义了变量的存储方式、作用域和生命周期。主要包括：
- **自动变量（Automatic Variables）**：
  - 默认存储类别（如局部变量）。
  - 在栈上分配内存，作用域结束后自动释放。
  ```cpp
  void func() {
      int a = 10; // 自动变量
  }
  ```

- **静态变量（Static Variables）**：
  - 使用 `static` 关键字定义。
  - **局部静态变量**：在函数内定义，但生命周期为整个程序期间，作用域仍为局部。
    ```cpp
    void func() {
        static int count = 0; // 初次调用时初始化，仅初始化一次
        count++;
    }
    ```
  - **全局静态变量**：仅在当前文件内可见，其他文件无法访问。

- **寄存器变量（Register Variables）**：
  - 使用 `register` 关键字（现代编译器已不推荐）。
  - 提示编译器将变量存储在 CPU 寄存器中以提高访问速度（但不保证一定会存储在寄存器中）。

- **外部变量（External Variables）**：
  - 使用 `extern` 关键字声明，指向其他文件定义的全局变量。
  ```cpp
  extern int a; // 引用其他文件的全局变量
  ```

---

### 1.4. **常量**

#### **1. `const` 的使用**
##### 1.1. **常量变量的定义**
- 使用 `const` 关键字可以定义不可修改的变量：
  ```cpp
  const int a = 10; // a 是常量，不能修改其值
  // a = 20; // 错误：常量不能被修改
  ```

##### 1.2. **指针与 `const` 的结合**
`const` 与指针结合时，根据位置的不同，含义有所区别：
1. **`const int*`**：指向常量的指针，指针自身可以修改，但不能通过指针修改指向的值：
   ```cpp
   const int val = 10;
   const int* p = &val; // p 是指向 const int 的指针
   // *p = 20; // 错误：不能修改 p 所指向的值
   int other = 30;
   p = &other; // 正确：可以修改指针本身指向的地址
   ```

2. **`int* const`**：常量指针，指针本身不能修改，但可以通过指针修改其指向的值：
   ```cpp
   int val = 10;
   int* const p = &val; // p 是常量指针
   *p = 20; // 正确：可以修改 p 指向的值
   // p = &other; // 错误：不能修改指针本身的指向
   ```

3. **`const int* const`**：指向常量的常量指针，既不能通过指针修改指向的值，也不能修改指针本身：
   ```cpp
   const int val = 10;
   const int* const p = &val; // p 是指向 const int 的 const 指针
   // *p = 20; // 错误：不能修改 p 所指向的值
   // p = &other; // 错误：不能修改指针本身的指向
   ```

---

#### **2. `constexpr` 和 `const` 的区别及应用场景**
1. **`const`**：
   - 表示不可修改的变量。
   - 变量的值在运行时确定。
   - 常用于需要只读属性的变量或函数参数。
   ```cpp
   const int a = 10; // 编译时或运行时确定
   ```

2. **`constexpr`**：
   - 表示常量表达式，值必须在编译时确定。
   - 常用于需要在编译期进行计算的场景（如数组大小、模板参数）。
   - C++11 引入，适用于更严格的编译期常量。
   ```cpp
   constexpr int a = 10; // 必须在编译时确定
   constexpr int square(int x) { return x * x; }
   constexpr int b = square(5); // 编译时计算
   ```

**应用场景区别：**
- 使用 `const` 时，值可以在运行时确定：
  ```cpp
  int x = 10;
  const int a = x; // 正确：x 的值在运行时确定
  ```
- 使用 `constexpr` 时，值必须在编译时确定：
  ```cpp
  int x = 10;
  // constexpr int a = x; // 错误：x 的值在运行时确定
  ```

---

#### **3. 宏定义 (`#define`) 与 `const` 的区别**
1. **宏定义 (`#define`)**：
   - 宏定义是预处理指令，在预处理阶段简单的文本替换，没有类型检查。
   - 不会生成符号表，不能调试。
   ```cpp
   #define PI 3.14159
   double area = PI * r * r; // PI 被简单替换为 3.14159
   ```

2. **`const`**：
   - 是类型安全的常量，具有作用域和类型检查。
   - 可以调试。
   ```cpp
   const double PI = 3.14159;
   double area = PI * r * r; // 受到类型检查
   ```

**优缺点比较：**
- `const` 优点：
  - 类型安全，有作用域限制。
  - 支持调试。
- 宏定义优点：
  - 适用于简单文本替换。
  - 可定义复杂的宏函数。
- **推荐**：优先使用 `const` 或 `constexpr`，尽量避免使用 `#define`。

---

### 1.5. **作用域**
#### **1. 局部作用域、全局作用域、块作用域（`{}`）**
##### **局部作用域**：
- **定义**：局部变量是定义在函数或代码块（`{}`）内的变量，它只能在定义它的作用域内访问。
- **生命周期**：局部变量在其作用域开始时创建，在作用域结束（如代码块结束或函数返回）时销毁。
- **示例**：
  ```cpp
  void func() {
      int a = 10; // 局部变量
      std::cout << a << std::endl;
  }
  // a 在此处不可见
  ```

##### **全局作用域**：
- **定义**：全局变量是定义在所有函数和类之外的变量，可以在整个文件中访问。
- **生命周期**：全局变量在程序启动时创建，在程序结束时销毁。
- **示例**：
  ```cpp
  int globalVar = 100; // 全局变量
  void func() {
      std::cout << globalVar << std::endl; // 全局变量可直接访问
  }
  ```

##### **块作用域**：
- **定义**：块作用域是由大括号 `{}` 定义的一个作用域，任何变量在该块中定义后，只能在该块内访问。
- **示例**：
  ```cpp
  void func() {
      {
          int blockVar = 20; // 块作用域变量
          std::cout << blockVar << std::endl;
      }
      // std::cout << blockVar << std::endl; // 错误：blockVar 在块外不可见
  }
  ```

---

#### **2. 名字冲突的解决：局部变量 vs 全局变量（`::` 作用域解析运算符）**
- **问题**：局部变量和全局变量同名时，局部变量会覆盖全局变量，导致全局变量在该作用域内不可直接访问。
- **解决方法**：使用作用域解析运算符（`::`）显式访问全局变量。
- **示例**：
  ```cpp
  int var = 100; // 全局变量
  void func() {
      int var = 10; // 局部变量
      std::cout << var << std::endl;  // 输出：10（局部变量）
      std::cout << ::var << std::endl; // 输出：100（全局变量）
  }
  ```

---

#### **3. 静态变量的作用域与生命周期**
##### **定义**：
- 静态变量（`static`）的存储在静态存储区，生命周期贯穿整个程序运行过程，但作用域可以是局部或全局。

##### **局部静态变量**：
- **作用域**：局限于定义它的函数或代码块中。
- **生命周期**：在程序运行期间始终存在，仅初始化一次。
- **示例**：
  ```cpp
  void func() {
      static int count = 0; // 局部静态变量
      count++;
      std::cout << "Count: " << count << std::endl;
  }
  int main() {
      func(); // 输出：Count: 1
      func(); // 输出：Count: 2
  }
  ```

##### **全局静态变量**：
- **作用域**：仅限于定义它的文件，不能被其他文件访问。
- **生命周期**：在程序启动时创建，程序结束时销毁。
- **示例**：
  ```cpp
  static int globalStaticVar = 100; // 全局静态变量，仅限当前文件
  void func() {
      std::cout << globalStaticVar << std::endl;
  }
  ```

**总结**：
1. 局部变量的作用范围限于其作用域，超出后被销毁。
2. 全局变量作用于整个程序生命周期，但容易引起名字冲突，用 `::` 可解决。
3. 静态变量即使局部作用域，也具有全局生命周期，适合记录跨调用的状态数据。

---

### 1.6. **命名空间**

#### **1. 命名空间的定义与使用 (`namespace`)**
##### **定义**：
- 命名空间（`namespace`）是 C++ 提供的一种机制，用于将标识符（如变量、函数、类等）组织到逻辑单元中，以避免名字冲突。
- 定义方式：
  ```cpp
  namespace myNamespace {
      int a = 10;
      void func() {
          std::cout << "Hello from myNamespace!" << std::endl;
      }
  }
  ```

##### **使用命名空间**：
- 使用命名空间中的成员时，可以通过作用域解析符（`::`）访问：
  ```cpp
  std::cout << myNamespace::a << std::endl; // 访问 myNamespace 中的变量
  myNamespace::func(); // 调用 myNamespace 中的函数
  ```

---

#### **2. `std` 命名空间及其作用**
- **`std` 命名空间**：
  - C++ 标准库（如 `iostream`、`vector`、`string` 等）中的所有标识符都位于命名空间 `std` 中。
  - 示例：
    ```cpp
    #include <iostream>

    int main() {
        std::cout << "Hello, World!" << std::endl; // 使用 std 命名空间中的 cout 和 endl
        return 0;
    }
    ```

- **作用**：
  - 避免与用户定义的标识符发生冲突。
  - 将标准库中的所有内容组织起来，方便管理。

---

#### **3. `using namespace` 的使用及注意事项**
- 使用 `using namespace` 可以简化命名空间的使用：
  ```cpp
  using namespace std;

  int main() {
      cout << "Hello, World!" << endl; // 不需要显式写 std::
      return 0;
  }
  ```

- **注意事项**：
  1. **命名冲突问题**：
     - 如果多个命名空间中有同名标识符，可能会导致冲突或含义模糊。
     - 例如：
       ```cpp
       namespace A { int value = 10; }
       namespace B { int value = 20; }

       using namespace A;
       using namespace B;

       int main() {
           // std::cout << value; // 错误：value 的定义不明确
       }
       ```
  2. **最佳实践**：
     - 尽量避免在全局作用域中使用 `using namespace`。
     - 在函数或局部作用域中使用 `using namespace` 以减少范围。
       ```cpp
       void func() {
           using namespace std; // 仅在函数内部使用
           cout << "Hello!" << endl;
       }
       ```

---

#### **4. 命名空间的嵌套与匿名命名空间**
##### **命名空间的嵌套**：
- 命名空间可以嵌套定义：
  ```cpp
  namespace outer {
      namespace inner {
          void func() {
              std::cout << "Inside inner namespace" << std::endl;
          }
      }
  }
  ```

- 使用嵌套命名空间时，可以通过完整路径访问：
  ```cpp
  outer::inner::func();
  ```

- **C++17** 引入了嵌套命名空间的简化写法：
  ```cpp
  namespace outer::inner {
      void func() {
          std::cout << "Inside inner namespace" << std::endl;
      }
  }
  ```

##### **匿名命名空间**：
- 匿名命名空间（`namespace {}`）用于将标识符限制在当前文件内，起到类似 `static` 的作用。
  ```cpp
  namespace {
      int a = 42; // 只能在当前文件中访问
  }

  void func() {
      std::cout << a << std::endl; // 正确
  }
  ```

- **作用**：
  - 防止全局标识符的名字冲突。
  - 常用于定义仅在当前文件中使用的变量或函数。

---

**总结**：
1. 命名空间可以有效解决名字冲突问题，尤其在大规模工程中非常重要。
2. 标准库中的所有内容位于 `std` 命名空间中，应优先使用作用域解析符访问。
3. 使用 `using namespace` 时需谨慎，避免在全局作用域中滥用。
4. 嵌套命名空间和匿名命名空间是组织和保护代码的重要工具。

### 1.7. **`struct` vs `class`**

#### **1. `struct` 和 `class` 的区别**
##### **默认访问修饰符**
- **`struct`**：
  - 默认的访问修饰符是 **`public`**。
  ```cpp
  struct MyStruct {
      int x; // 默认是 public
  };
  MyStruct obj;
  obj.x = 10; // 可以直接访问
  ```

- **`class`**：
  - 默认的访问修饰符是 **`private`**。
  ```cpp
  class MyClass {
      int x; // 默认是 private
  };
  MyClass obj;
  // obj.x = 10; // 错误：x 是 private，不能直接访问
  ```

##### **继承的默认访问级别**
- **`struct`**：默认继承模式为 **`public`**。
  ```cpp
  struct Base {};
  struct Derived : Base {}; // 等价于 struct Derived : public Base {};
  ```
- **`class`**：默认继承模式为 **`private`**。
  ```cpp
  class Base {};
  class Derived : Base {}; // 等价于 class Derived : private Base {};
  ```

---

#### **2. 何时使用 `struct`，何时使用 `class`**
##### **使用 `struct` 的场景**
- 主要用于 **数据存储**，即表示一个纯粹的数据结构。
- 场景：
  - **POD 类型**（Plain Old Data）：仅包含数据成员，没有复杂的逻辑或行为。
  - 小型的数据对象。
  - 接口简单、逻辑直接的类型。
  ```cpp
  struct Point {
      int x;
      int y;
  };
  ```

##### **使用 `class` 的场景**
- 主要用于实现复杂的 **对象行为**，即面向对象的编程场景。
- 场景：
  - 包含成员函数、封装、继承、多态等复杂行为。
  - 涉及到访问控制（`private`、`protected`）、抽象类、多态的场景。
  ```cpp
  class Rectangle {
  private:
      int width;
      int height;

  public:
      Rectangle(int w, int h) : width(w), height(h) {}
      int area() { return width * height; }
  };
  ```

##### **总结**：
- 使用 `struct` 表示简单的数据结构。
- 使用 `class` 表示复杂的对象行为。

---

#### **3. C 语言中的 `struct` 和 C++ 的 `struct` 的区别**
##### **C 语言中的 `struct`**
- C 的 `struct` 只能存储数据成员，不能包含成员函数。
- 没有访问控制，所有成员默认是 **`public`**。
- 使用时必须显式添加 `struct` 关键字：
  ```c
  struct Point {
      int x;
      int y;
  };

  struct Point p; // 必须加 struct 关键字
  ```

##### **C++ 中的 `struct`**
- C++ 的 `struct` 是对 C 的扩展，允许包含：
  - **成员函数**：
    ```cpp
    struct Point {
        int x;
        int y;

        void print() {
            std::cout << "(" << x << ", " << y << ")" << std::endl;
        }
    };
    ```
  - **访问控制**：支持 `public`、`private`、`protected`。
  - **继承**：支持继承与多态功能。
  - **构造函数和析构函数**：可以定义构造函数、析构函数。
  - **模板支持**：`struct` 也可以定义为模板类型。
  - 使用时可以省略 `struct` 关键字：
    ```cpp
    Point p; // 直接使用，不需要加 struct 关键字
    ```

##### **总结：**
- **C 语言** 的 `struct` 更适合纯数据结构。
- **C++** 的 `struct` 功能上几乎与 `class` 一样强大。

---

### 1.8 面试中的常见问题

#### **1. 关于类型**
##### **`sizeof` 操作符的作用及其结果（如 `sizeof(char)` 是否总是 1？）**
- **作用**：
  - `sizeof` 是一个编译时操作符，用于获取变量或类型的大小（以字节为单位）。
- **结果**：
  - `sizeof(char)` 总是 `1`，这是因为 C++ 标准规定每个 `char` 占用 1 字节（即 1 个字节是 `sizeof(char)` 的单位）。
  - 对于其他类型的大小，例如 `sizeof(int)` 和 `sizeof(double)`，取决于具体的编译器和平台（如 32 位或 64 位系统）。
- 示例：
  ```cpp
  std::cout << sizeof(char) << std::endl;  // 输出 1
  std::cout << sizeof(int) << std::endl;   // 通常是 4（依赖平台）
  std::cout << sizeof(double) << std::endl; // 通常是 8（依赖平台）
  ```

##### **为什么 `float` 和 `double` 存在精度问题？**
- **原因**：
  - 浮点数使用 **IEEE 754 标准**表示，采用二进制科学计数法存储（即 `sign + exponent + mantissa`）。
  - 并非所有十进制小数都能精确表示为二进制（例如 `0.1` 无法用有限的二进制位精确表示），因此会存在舍入误差。
- **精度问题**：
  - `float`（单精度）有 23 位尾数，精度约为 6~7 位有效数字。
  - `double`（双精度）有 52 位尾数，精度约为 15~16 位有效数字。
- 示例：
  ```cpp
  float a = 0.1f;
  double b = 0.1;
  std::cout << a << std::endl; // 输出 0.1，但可能带有舍入误差
  std::cout << b << std::endl; // 输出更精确的 0.1
  ```

---

#### **2. 关于 `const`**
##### **如何理解 `const` 修饰符的行为？**
- **`const` 的作用**：
  - 指定某个变量或对象不可被修改。
- **用法**：
  - 修饰变量：
    ```cpp
    const int a = 10; // a 是常量，不能被修改
    ```
  - 修饰指针：
    ```cpp
    const int* p; // 指向常量的指针，不能通过指针修改指向的值
    int* const p; // 常量指针，指针本身不能修改
    const int* const p; // 指向常量的常量指针
    ```
  - 修饰函数参数：
    ```cpp
    void func(const int x); // 函数内不能修改参数 x
    ```
  - 修饰成员函数：
    ```cpp
    class MyClass {
        void func() const; // 表示该成员函数不会修改类的成员变量
    };
    ```

##### **`const` 和指针的组合在实际应用中的用法**
1. **`const int*`（指向常量的指针）**：
   - 指针指向的值不可修改，但指针本身可以修改。
   ```cpp
   const int val = 10;
   const int* p = &val;
   // *p = 20; // 错误：不能修改 p 指向的值
   int other = 30;
   p = &other; // 正确：可以修改指针本身指向的地址
   ```

2. **`int* const`（常量指针）**：
   - 指针本身不可修改，但可以通过指针修改指向的值。
   ```cpp
   int val = 10;
   int* const p = &val;
   *p = 20; // 正确：可以修改 p 指向的值
   // p = &other; // 错误：不能修改指针本身的指向
   ```

3. **`const int* const`（指向常量的常量指针）**：
   - 既不能通过指针修改指向的值，也不能修改指针本身。
   ```cpp
   const int val = 10;
   const int* const p = &val;
   // *p = 20; // 错误
   // p = &other; // 错误
   ```

##### **如何避免 `const` 的误用？**
- 确保 `const` 的语义清晰，避免滥用或误解。
- 在需要保护数据不可被改变时明确使用 `const`。
- 避免在不必要的场景下使用 `const`，增加代码复杂性。

---

#### **3. 关于命名空间**
##### **如何避免命名空间冲突？**
- 使用唯一的命名空间名称，避免与其他库或代码冲突。
  ```cpp
  namespace MyUniqueNamespace {
      void func();
  }
  ```
- 避免全局使用 `using namespace`，尤其是标准命名空间 `std`。
  ```cpp
  using namespace std; // 谨慎使用，可能导致命名冲突
  ```
- 使用作用域解析符（`::`）明确指定命名空间成员。

##### **匿名命名空间与 `static` 的区别**
- **匿名命名空间**：
  - 定义在匿名命名空间中的标识符只在当前编译单元内可见。
  ```cpp
  namespace {
      int a = 42; // 仅在当前文件中可见
  }
  ```
- **`static`**：
  - 用于变量或函数时，限制其作用域在当前编译单元。
  ```cpp
  static int b = 42; // 仅在当前文件中可见
  ```

**区别**：
- 匿名命名空间是 C++ 提供的语法，推荐在现代 C++ 中使用匿名命名空间替代 `static`。

---

#### **4. 关于 `struct` 和 `class`**
##### **在什么时候优先使用 `struct` 而不是 `class`？**
- 使用 `struct`：
  - 用于表示纯数据结构（POD，Plain Old Data）。
  - 数据逻辑简单，仅包含公共成员变量。
  ```cpp
  struct Point {
      int x;
      int y;
  };
  ```
- 使用 `class`：
  - 用于表示复杂的对象行为，包含封装、继承、多态等特性。
  ```cpp
  class Rectangle {
  private:
      int width, height;
  public:
      int area() { return width * height; }
  };
  ```

##### **5. 如何设计一个 `struct` 或 `class` 来存储数据？**
- **设计时考虑以下原则**：
  1. **数据的封装**：根据需要决定成员变量和函数的访问级别（`public`、`private`、`protected`）。
  2. **构造函数**：初始化成员变量，保证数据一致性。
  3. **操作接口**：根据需求设计成员函数，避免直接操作成员变量。
  4. **是否需要继承**：如果需要继承和多态，使用 `class`。

---

#### **6. 控制流**
- **`if/else`、`switch`**：用于分支选择，`switch` 适合枚举值或常量。
- **各种循环**：`for`（确定循环次数）、`while`（条件控制）、`do-while`（至少执行一次）。
- **`goto`**：一般不推荐，容易导致代码难以维护。
- **三目运算符**：简洁表达条件选择。
  ```cpp
  int a = (x > 0) ? x : -x;
  ```

---

#### **7. 指针与引用**
- **指针算术**：指针可进行地址偏移操作。
- **引用的本质**：引用是对象的别名，必须初始化且不可改变绑定对象。
- **左值/右值**：左值有地址，可赋值；右值是临时值。
- **`nullptr`**：用于表示空指针，替代 `NULL`。
- **`&` 与 `*` 的区别**：
  - `&` 获取地址或引用。
  - `*` 解引用指针。

### 1.9 函数适配器相关
#### **什么是函数适配器？**

##### **定义**
- **函数适配器（Function Adapter）** 是一种将函数、函数对象或成员函数的接口进行调整或包装的技术，使得它们可以满足不同场景的需求。
- 在 C++ 中，函数适配器常用于：
  1. **修改函数的参数数量或顺序**。
  2. **绑定部分参数（即固定某些参数的值）**。
  3. **将不同的调用目标（普通函数、成员函数、函数对象等）统一为一个可调用对象**。

##### **常见的函数适配器**
- C++ 提供了多种函数适配器工具，包括：
  1. **`std::function`**（通用的可调用对象）。
  2. **`std::bind`**（绑定参数，创建新的函数对象）。
  3. **Lambda 表达式**（也可以看作一种灵活的函数适配器）。

---

#### **如何使用 `std::bind` 和 `std::function`？**

##### **1. `std::function`**

###### **定义**
- `std::function` 是一个通用的函数包装器，可以保存普通函数、成员函数、仿函数或 Lambda 表达式。
- 它提供了统一的接口来调用不同类型的可调用对象。

###### **用法示例**
```cpp
#include <iostream>
#include <functional>

// 普通函数
int add(int a, int b) {
    return a + b;
}

// 仿函数
struct Multiply {
    int operator()(int a, int b) const {
        return a * b;
    }
};

int main() {
    // 使用 std::function 包装普通函数
    std::function<int(int, int)> funcAdd = add;
    std::cout << "Add: " << funcAdd(3, 5) << std::endl; // 输出：Add: 8

    // 使用 std::function 包装仿函数
    Multiply multiply;
    std::function<int(int, int)> funcMultiply = multiply;
    std::cout << "Multiply: " << funcMultiply(3, 5) << std::endl; // 输出：Multiply: 15

    // 使用 Lambda 表达式
    std::function<int(int, int)> funcLambda = [](int a, int b) { return a - b; };
    std::cout << "Lambda (Subtract): " << funcLambda(5, 3) << std::endl; // 输出：Lambda (Subtract): 2

    return 0;
}
```

###### **优点**
1. 提供统一的接口，支持各种类型的可调用对象。
2. 灵活且易于使用，适用于泛型编程。

---

##### **2. `std::bind`**

###### **定义**
- `std::bind` 用于生成一个新的可调用对象，通过固定某些参数或调整参数顺序来适配原始函数。
- 形式：`std::bind(callable, arg1, arg2, ...)`。

###### **用法示例**

###### **绑定部分参数**
```cpp
#include <iostream>
#include <functional>

// 普通函数
int add(int a, int b) {
    return a + b;
}

int main() {
    // 使用 std::bind 绑定第一个参数为 5
    auto add5 = std::bind(add, 5, std::placeholders::_1); // _1 表示第一个占位参数
    std::cout << "5 + 3 = " << add5(3) << std::endl; // 输出：5 + 3 = 8

    return 0;
}
```

###### **绑定成员函数**
```cpp
#include <iostream>
#include <functional>

class Calculator {
public:
    int add(int a, int b) const {
        return a + b;
    }
};

int main() {
    Calculator calc;

    // 使用 std::bind 绑定成员函数
    auto boundAdd = std::bind(&Calculator::add, &calc, std::placeholders::_1, std::placeholders::_2);
    std::cout << "Bound Add: " << boundAdd(3, 5) << std::endl; // 输出：Bound Add: 8

    return 0;
}
```

###### **调整参数顺序**
```cpp
#include <iostream>
#include <functional>

// 普通函数
int subtract(int a, int b) {
    return a - b;
}

int main() {
    // 使用 std::bind 调整参数顺序
    auto reverseSubtract = std::bind(subtract, std::placeholders::_2, std::placeholders::_1);
    std::cout << "Reverse Subtract: " << reverseSubtract(3, 5) << std::endl; // 输出：Reverse Subtract: 2

    return 0;
}
```

##### **优点**
1. 提供了灵活的参数绑定和调整功能。
2. 适用于需要修改函数接口或固定部分参数的场景。

##### **注意事项**
1. 使用 `std::placeholders::_1`, `_2`, ... 表示占位符，用于指定新函数的参数位置。
2. 与 `std::function` 配合使用可以实现强大的函数适配。

---

#### **总结**

1. **`std::function`**
   - 是一个通用的函数包装器，能够保存任何可调用对象。
   - 提供统一的接口，常用于泛型编程和回调函数。

2. **`std::bind`**
   - 生成一个新的函数对象，通过绑定部分参数或调整参数顺序来适配原始函数。
   - 适合需要修改函数参数接口的场景。

3. **实际使用场景**
   - `std::function` 和 `std::bind` 在事件驱动编程（如回调函数）和泛型算法中非常常见。
   - 它们与 STL 算法、线程库（如 `std::thread`）、信号/槽机制等结合使用时非常强大。


---

#### **`const` 限定符**
- **`const int*`**：指向常量的指针。
- **`int* const`**：常量指针。
- **成员函数后缀 `const`**：表示成员函数不会修改类的成员变量。

## 二、内存管理

### **1. 动态内存分配：`new/delete` 与 `malloc/free` 的区别与内存对齐**
#### **`new/delete`**
- **特点**：
  - C++ 中的运算符，既分配内存又调用构造函数。
  - 使用 `delete` 释放内存，同时调用析构函数。
- **适用场景**：推荐在 C++ 中使用，尤其是需要调用构造和析构函数的对象。
- **示例**：
  ```cpp
  int* p = new int(10); // 动态分配内存并初始化为 10
  delete p;            // 释放内存并调用析构函数（如果是对象）
  ```

#### **`malloc/free`**
- **特点**：
  - C 中的标准库函数，仅分配内存，不调用构造函数。
  - 使用 `free` 释放内存，不调用析构函数。
- **适用场景**：主要用于 C 语言或需要与 C 代码兼容的场景。
- **示例**：
  ```cpp
  int* p = (int*)malloc(sizeof(int)); // 动态分配内存
  *p = 10;                           // 手动初始化
  free(p);                           // 释放内存
  ```

#### **区别**
| 特性              | `new/delete`               | `malloc/free`            |
| ----------------- | -------------------------- | ------------------------ |
| 调用构造/析构函数 | 是                         | 否                       |
| 返回类型          | 类型安全（不需要强制转换） | 返回 `void*`，需强制转换 |
| 内存分配失败      | 抛出 `std::bad_alloc` 异常 | 返回 `nullptr`           |
| 用法复杂度        | 更高（适合对象）           | 较低（适合简单数据）     |

#### **内存对齐问题**
- 动态分配的内存通常是按平台默认对齐的（如 4 字节、8 字节）。
- 如果需要特定对齐，可以使用 `std::align` 或 C++17 的 `std::aligned_alloc`。

---

### **2. 深拷贝 vs 浅拷贝**
#### **浅拷贝**
- 对象的拷贝仅复制指针或引用，不复制指针所指向的内存。
- **问题**：多个对象共享同一块内存，可能导致 **双重释放** 或 **数据污染**。
- **示例**：
  ```cpp
  class MyClass {
      int* data;
  public:
      MyClass(int val) { data = new int(val); }
      ~MyClass() { delete data; } // 内存释放
  };
  ```

#### **深拷贝**
- 对象的拷贝会分配新内存，并复制原对象中的内容。
- 解决了浅拷贝的问题，但实现复杂，性能开销较大。
- **示例**：
  ```cpp
  class MyClass {
      int* data;
  public:
      MyClass(int val) { data = new int(val); }
      MyClass(const MyClass& other) { data = new int(*other.data); } // 深拷贝
      ~MyClass() { delete data; } // 内存释放
  };
  ```

#### **拷贝构造函数与拷贝赋值操作符**
- **拷贝构造函数**：用于初始化新对象。
- **拷贝赋值操作符**：用于将已有对象赋值给另一个对象。实现时需要小心释放已有资源（避免内存泄漏）。

---

### **3. 虚析构函数**
#### **问题描述**
- 如果基类的析构函数不是虚函数，删除指向派生类的基类指针时，只会调用基类的析构函数，可能导致 **内存泄漏**。
- **示例**：
  ```cpp
  class Base {
  public:
      ~Base() { std::cout << "Base Destructor\n"; }
  };

  class Derived : public Base {
  public:
      ~Derived() { std::cout << "Derived Destructor\n"; }
  };

  Base* p = new Derived();
  delete p; // 只调用 Base 的析构函数，导致 Derived 的资源泄漏
  ```

#### **解决方案**
- 将基类的析构函数声明为虚函数：
  ```cpp
  class Base {
  public:
      virtual ~Base() { std::cout << "Base Destructor\n"; }
  };
  ```

---

### **4. 智能指针**
C++11 引入智能指针，用于自动管理动态内存。
#### **常见类型**
1. **`std::unique_ptr`**：
   - 独占所有权，不能复制，只能转移所有权。
   - **适用场景**：单一对象的生命周期管理。
   - **示例**：
     ```cpp
     std::unique_ptr<int> p = std::make_unique<int>(10);
     ```

2. **`std::shared_ptr`**：
   - 多个指针共享所有权，使用引用计数管理资源。
   - **适用场景**：需要多个对象共享同一资源。
   - **示例**：
     ```cpp
     std::shared_ptr<int> p1 = std::make_shared<int>(10);
     std::shared_ptr<int> p2 = p1; // 引用计数增加
     ```

3. **`std::weak_ptr`**：
   - 弱引用，不增加引用计数，避免循环引用。
   - **适用场景**：需要观察 `shared_ptr` 管理的资源。
   - **示例**：
     ```cpp
     std::shared_ptr<int> sp = std::make_shared<int>(10);
     std::weak_ptr<int> wp = sp;
     ```

#### ⭐手动实现 std::unique_ptr、std::shared_ptr 和 std::weak_ptr
1. **手动实现unique_ptr**
```cpp
template <typename T>
class UniquePtr{
private:
    T* ptr; //原始指针
public:
    // 构造函数
    // 使用 explicit 可以提高代码的清晰度和安全性，防止意外的类型转换，从而减少潜在的错误。
    explicit UniquePtr(T* p = nullptr) : ptr(p) {}

    // 禁止拷贝构造和拷贝赋值
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    // 转移构造
    UniquePtr& operator=(UniquePtr && other) noexcept {
      if (this != &other){
        delete ptr;       // 释放当前资源
        ptr = other.ptr;  // 转移所有权
        other.ptr = nullptr;
      }
      return *this;
    }

    // 重载 * 和 -> 操作符
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }

    // 获取指针
    T* get() const { return ptr; }

    // 释放所有权
    T* release() {
      T* temp = ptr;
      ptr = nullptr;
      return temp;
    }

    // 重置指针
    void reset(T* p = nullptr){
      delete ptr;
      ptr = p;
    }

    // 析构函数
    ~UniquePtr(){
      delete ptr;
    }
}
```
2. **手动实现shared_ptr**
```cpp
template <typename T>
class SharedPtr {
private:
    T* ptr;             // 原始指针
    size_t* ref_count;  // 引用计数

    void release() {
        if (ref_count && --(*ref_count) == 0) {
            delete ptr;
            delete ref_count;
        }
    }

public:
    // 构造函数
    explicit SharedPtr(T* p = nullptr) : ptr(p), ref_count(new size_t(1)) {}

    // 拷贝构造
    SharedPtr(const SharedPtr& other) : ptr(other.ptr), ref_count(other.ref_count) {
        if (ref_count) {
            ++(*ref_count); // 引用计数增加
        }
    }

    // 拷贝赋值
    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();             // 释放当前资源
            ptr = other.ptr;
            ref_count = other.ref_count;
            if (ref_count) {
                ++(*ref_count);  // 引用计数增加
            }
        }
        return *this;
    }

    // 重载 * 和 -> 操作符
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }

    // 获取引用计数
    size_t use_count() const { return ref_count ? *ref_count : 0; }

    // 析构函数
    ~SharedPtr() {
        release();
    }
};

```

3. 手动实现weak_ptr
```cpp

template <typename T>
class SharedPtr; // 前向声明

template <typename T>
class WeakPtr {
private:
    T* ptr;             // 原始指针
    size_t* ref_count;  // 引用计数

public:
    // 构造函数
    WeakPtr() : ptr(nullptr), ref_count(nullptr) {}

    // 从 shared_ptr 构造
    WeakPtr(const SharedPtr<T>& sp) : ptr(sp.ptr), ref_count(sp.ref_count) {}

    // 检查指针是否有效
    bool expired() const {
        return !ref_count || *ref_count == 0;
    }

    // 锁定并返回 shared_ptr
    SharedPtr<T> lock() const {
        if (expired()) {
            return SharedPtr<T>();
        }
        return SharedPtr<T>(*this);
    }
};

```

---

### **5. 规则三/五/零**
#### **规则三（Rule of Three）**
- 如果类需要显式定义 **析构函数**、**拷贝构造函数** 或 **拷贝赋值操作符**，则通常需要定义所有三个。

#### **规则五（Rule of Five）**
- C++11 引入了移动语义，需要额外定义 **移动构造函数** 和 **移动赋值操作符**：
  ```cpp
  MyClass(MyClass&& other) noexcept; // 移动构造函数
  MyClass& operator=(MyClass&& other) noexcept; // 移动赋值操作符
  ```

#### **规则零（Rule of Zero）**
- 如果类的成员变量由标准库容器或智能指针管理，通常不需要显式定义五个函数（依赖默认生成）。

---

### **6. 移动语义与 `std::move`**
#### **右值引用**
- 右值引用（`T&&`）绑定到临时对象，允许资源转移而非复制。
- **示例**：
  ```cpp
  class MyClass {
      int* data;
  public:
      MyClass(MyClass&& other) noexcept : data(other.data) { other.data = nullptr; } // 移动构造
  };
  ```

#### **`std::move`**
- 将对象显式转换为右值引用，允许调用移动构造或移动赋值。
- **示例**：
  ```cpp
  std::vector<int> v1 = {1, 2, 3};
  std::vector<int> v2 = std::move(v1); // v1 的资源转移到 v2
  ```

---

### **7. RAII 与异常安全**
#### **RAII（Resource Acquisition Is Initialization）**
- 将资源管理与对象生命周期绑定，确保资源在对象析构时释放。
- **示例**：
  ```cpp
  class FileHandler {
      std::fstream file;
  public:
      FileHandler(const std::string& filename) { file.open(filename); }
      ~FileHandler() { file.close(); } // 确保资源释放
  };
  ```

#### **异常安全**
- 利用 RAII 技术，确保即使发生异常，资源也会被正确释放，避免内存泄漏。

---


## 三、面向对象特性
### 面向对象特性详解

#### **1. 类与封装**
- **访问控制**：
  - 使用 `public`、`protected` 和 `private` 关键字控制类成员的访问权限：
    - `public`：成员对所有代码可见。
    - `protected`：成员对子类和本类可见。
    - `private`：成员仅对本类可见，不能直接被子类访问。
  - 示例：
    ```cpp
    class MyClass {
      private:
        int privateVar;

      protected:
        int protectedVar;

      public:
        int publicVar;
    };
    ```

- **成员函数**：
  - 成员函数是类中的函数，用于操作类的成员变量。
  - 可以通过对象调用成员函数。
  - 示例：
    ```cpp
    class MyClass {
      private:
        int val;

      public:
        void setVal(int v) { val = v; }
        int getVal() const { return val; }
    };
    ```

- **内联函数**：
  - 使用 `inline` 关键字声明的函数，编译器可能会将其展开为内联代码（减少函数调用开销）。
  - 示例：
    ```cpp
    class MyClass {
      public:
        inline int add(int a, int b) { return a + b; }
    };
    ```

- **友元函数/类**：
  - 使用 `friend` 声明的函数或类，可以访问类的私有和保护成员。
  - 示例：
    ```cpp
    class MyClass {
      private:
        int val;

      public:
        MyClass(int v) : val(v) {}

        friend void printVal(const MyClass& obj);
    };

    void printVal(const MyClass& obj) {
        std::cout << "Value: " << obj.val << std::endl;
    }
    ```

---

#### **2. 继承**
- **公有/私有/保护继承的区别及应用**：
  - **公有继承（`public`）**：
    - 基类的 `public` 成员在派生类中保持 `public`，`protected` 成员保持 `protected`。
    - 示例：
      ```cpp
      class Base {
        public:
          void func() {}
      };

      class Derived : public Base {};
      ```

  - **私有继承（`private`）**：
    - 基类的 `public` 和 `protected` 成员在派生类中变为 `private`。
    - 示例：
      ```cpp
      class Base {
        public:
          void func() {}
      };

      class Derived : private Base {};
      ```

  - **保护继承（`protected`）**：
    - 基类的 `public` 和 `protected` 成员在派生类中变为 `protected`。
    - 示例：
      ```cpp
      class Base {
        public:
          void func() {}
      };

      class Derived : protected Base {};
      ```

  - **应用场景**：
    - 公有继承：用于实现“是一个”的关系。
    - 私有继承：用于实现“以某种方式实现”的关系。
    - 保护继承：较少使用，主要用于内部实现。

- **多重继承与虚继承**：
  - **多重继承**：
    - 一个类可以从多个基类继承。
    - 示例：
      ```cpp
      class Base1 { public: void func1() {} };
      class Base2 { public: void func2() {} };

      class Derived : public Base1, public Base2 {};
      ```

  - **虚继承**：
    - 用于解决多重继承中的“钻石继承”问题（见下面的钻石继承介绍）。

---

#### **3. 多态**
- **虚函数表（vtable）**：
  - 多态是通过虚函数表实现的。
  - 基类包含一个虚函数表指针（vptr），派生类覆盖虚函数时，虚函数表指针指向派生类的虚函数表。
  - 示例：
    ```cpp
    class Base {
      public:
        virtual void func() { std::cout << "Base" << std::endl; }
    };

    class Derived : public Base {
      public:
        void func() override { std::cout << "Derived" << std::endl; }
    };
    ```
    ### 虚函数表指针（vptr）
    - **vptr** 是虚函数表的指针，属于类对象的成员，但它是编译器自动添加的隐式成员。

    #### **存储位置**
    - 如果对象是分配在 **栈上**（局部对象），则 **vptr** 存储在栈上，与对象一起分配。
    - 如果对象是分配在 **堆上**（通过 `new` 分配），则 **vptr** 存储在堆上，与对象一起分配。
    - 如果对象是 **全局或静态变量**，则 **vptr** 存储在全局或静态存储区。

    #### **扩展问题**
    1. **虚函数表（vtable）存储在哪里？**
         - 虚函数表是针对类而存在的，它是全局唯一的，通常存储在程序的静态存储区（`.data` 或 `.rodata` 段）。

    2. **每个对象都有 vptr 吗？**
         - 是的，每个具有虚函数的类对象都会有一个 **vptr**，用于指向虚函数表。

- **纯虚函数与抽象类**：
  - 纯虚函数：在基类中声明但不实现的虚函数，定义为 `= 0`。
  - 抽象类：包含至少一个纯虚函数的类，不能实例化。
  - 示例：
    ```cpp
    class Abstract {
      public:
        virtual void func() = 0; // 纯虚函数
    };

    class Derived : public Abstract {
      public:
        void func() override { std::cout << "Implemented" << std::endl; }
    };
    ```

- **对象切割（object slicing）问题**：
  - 当基类对象接收派生类对象时，派生类的扩展部分会被切割。
  - 示例：
    ```cpp
    class Base {
      public:
        int baseVal;
    };

    class Derived : public Base {
      public:
        int derivedVal;
    };

    Base b = Derived(); // derivedVal 被切割
    ```

---

#### **4. 钻石继承（Diamond Problem）**
- **问题描述**：
  - 当一个类从多个基类继承，而这些基类有一个共同的基类时，会导致基类成员的二义性。
  - 示例：
    ```cpp
    class A { public: int val; };
    class B : public A {};
    class C : public A {};
    class D : public B, public C {}; // A 的成员存在二义性
    ```

- **解决方案（虚继承）**：
  - 使用虚继承可以避免重复继承基类成员。
  - 示例：
    ```cpp
    class A {
      public:
        int val;
    };

    class B : virtual public A {};
    class C : virtual public A {};
    class D : public B, public C {};
    ```

---

#### **5. 运算符重载**
- **常见运算符重载的实现**：
  - 运算符重载是在类中定义特殊函数，允许对自定义类型使用运算符。
  - 示例：
    ```cpp
    class MyClass {
      private:
        int val;

      public:
        MyClass(int v) : val(v) {}

        // 重载加号运算符
        MyClass operator+(const MyClass& other) const {
          return MyClass(this->val + other.val);
        }

        // 重载等于运算符
        bool operator==(const MyClass& other) const {
          return this->val == other.val;
        }

        // 重载输出流运算符
        friend std::ostream& operator<<(std::ostream& os, const MyClass& obj) {
          os << obj.val;
          return os;
        }
    };
    ```

- **最佳实践**：
  - 尽量保持运算符的语义一致性，例如 `+` 应表示加法。
  - 使用 `friend` 重载非成员运算符（如 `<<`）。
  - 返回值应尽量避免返回临时对象（可使用右值引用或 `std::move` 进行优化）。

上述内容涵盖了类与封装、继承、多态、钻石继承、运算符重载的核心特性与实现。

## 四、模板与泛型编程
### **模板与泛型编程详解**

#### **1. 函数模板 vs 类模板**
- **函数模板**：
  - 用于定义通用的函数，通过模板参数实现对不同类型的操作。
  - 编译器自动推导模板参数类型，简化调用。
  - 示例：
    ```cpp
    template <typename T>
    T add(T a, T b) {
        return a + b;
    }

    int main() {
        std::cout << add(3, 5) << std::endl; // 自动推导为 int
        std::cout << add(3.5, 5.2) << std::endl; // 自动推导为 double
    }
    ```

- **类模板**：
  - 用于定义通用的类，通过模板参数实现对不同类型的封装。
  - 类模板不能自动推导，需要显式指定模板参数。
  - 示例：
    ```cpp
    template <typename T>
    class Box {
      private:
        T value;
      public:
        Box(T v) : value(v) {}
        T getValue() const { return value; }
    };

    int main() {
        Box<int> intBox(10); // 显式指定类型
        Box<double> doubleBox(3.14);
        std::cout << intBox.getValue() << std::endl;
        std::cout << doubleBox.getValue() << std::endl;
    }
    ```

- **显式/部分特化**：
  - 特化是针对特定类型提供特殊化的实现。
  - 部分特化仅适用于类模板（函数模板不能部分特化）。
  - 示例（类模板部分特化）：
    ```cpp
    template <typename T>
    class Box {
      public:
        void display() { std::cout << "Generic Box" << std::endl; }
    };

    // 特化为 int 类型
    template <>
    class Box<int> {
      public:
        void display() { std::cout << "Int Box" << std::endl; }
    };

    int main() {
        Box<double> genericBox;
        genericBox.display(); // 输出：Generic Box

        Box<int> intBox;
        intBox.display(); // 输出：Int Box
    }
    ```

#### **2. 可变参数模板（Variadic Templates）**
- **定义**：
  - 可变参数模板允许模板接收任意数量的模板参数。
  - 通过递归展开或折叠表达式处理参数包。

- **递归展开**：
  - 示例：
    ```cpp
    template <typename T>
    void print(T arg) {
        std::cout << arg << std::endl;
    }

    template <typename T, typename... Args>
    void print(T first, Args... rest) {
        std::cout << first << std::endl;
        print(rest...); // 递归调用
    }

    int main() {
        print(1, 2.5, "Hello", true); // 输出每个参数
    }
    ```

- **折叠表达式（C++17 引入）**：
  - 用于简化参数包处理，将参数包中的所有参数合并为单一表达式。
  - 示例：
    ```cpp
    template <typename... Args>
    auto sum(Args... args) {
        return (... + args); // 使用折叠表达式求和
    }

    int main() {
        std::cout << sum(1, 2, 3, 4) << std::endl; // 输出 10
    }
    ```

#### **3. SFINAE 与 `std::enable_if`**
- **SFINAE（Substitution Failure Is Not An Error）**：
  - 在模板参数替换过程中，如果某种模板不适用，编译器会尝试其他模板，而不会报错。
  - 示例：
    ```cpp
    template <typename T>
    typename std::enable_if<std::is_integral<T>::value, T>::type
    func(T val) {
        return val * 2; // 仅适用于整型
    }

    template <typename T>
    typename std::enable_if<std::is_floating_point<T>::value, T>::type
    ```

## 五、STL 容器与算法
### **STL 容器与算法详解**

#### **1. 顺序容器**
- **`vector`**:
  - **底层实现**：动态数组，连续存储。
  - **特点**：支持随机访问，插入和删除的时间复杂度为：
    - 末尾插入/删除：O(1)（均摊）。
    - 中间插入/删除：O(n)。
  - **适用场景**：需要快速随机访问，元素数量动态变化，但插入/删除操作较少。
  - **示例**：
    ```cpp
    std::vector<int> v = {1, 2, 3};
    v.push_back(4); // 插入
    v.erase(v.begin() + 1); // 删除
    ```

- **`list`**:
  - **底层实现**：双向链表。
  - **特点**：
    - 插入和删除的时间复杂度为 O(1)。
    - 不支持随机访问，查找需要 O(n)。
  - **适用场景**：频繁插入/删除操作，且不需要随机访问。
  - **示例**：
    ```cpp
    std::list<int> l = {1, 2, 3};
    l.push_back(4); // 添加到末尾
    l.push_front(0); // 添加到开头
    ```

- **`deque`**:
  - **底层实现**：双端队列，分段连续存储。
  - **特点**：
    - 支持在两端快速插入和删除，时间复杂度为 O(1)。
    - 支持随机访问，复杂度为 O(1)。
  - **适用场景**：需要在两端高效插入/删除，且需要随机访问。
  - **示例**：
    ```cpp
    std::deque<int> dq = {1, 2, 3};
    dq.push_front(0); // 前端插入
    dq.push_back(4); // 后端插入
    ```

- **`array`**:
  - **底层实现**：静态数组，固定大小。
  - **特点**：
    - 占用栈空间，大小在编译期确定。
    - 支持快速随机访问，时间复杂度为 O(1)。
  - **适用场景**：大小固定的数组。
  - **示例**：
    ```cpp
    std::array<int, 3> arr = {1, 2, 3};
    arr[0] = 10;
    ```

- **`forward_list`**:
  - **底层实现**：单向链表。
  - **特点**：
    - 插入和删除操作的时间复杂度为 O(1)。
    - 不支持随机访问。
  - **适用场景**：需要简单链表结构且操作较少。
  - **示例**：
    ```cpp
    std::forward_list<int> fl = {1, 2, 3};
    fl.push_front(0); // 插入
    ```

---

#### **2. 关联容器**
- **`set` / `map`**:
  - **底层实现**：红黑树（平衡二叉搜索树）。
  - **特点**：
    - 元素有序。
    - 插入、删除、查找的时间复杂度为 O(log n)。
  - **适用场景**：
    - `set`：需要存储唯一有序元素。
    - `map`：需要存储键值对，且键有序。
  - **示例**：
    ```cpp
    std::set<int> s = {3, 1, 4};
    s.insert(2); // 插入
    s.erase(1); // 删除

    std::map<int, std::string> m = {{1, "one"}, {2, "two"}};
    m[3] = "three"; // 插入
    ```

- **`unordered_set` / `unordered_map`**:
  - **底层实现**：哈希表。
  - **特点**：
    - 元素无序。
    - 插入、删除、查找的时间复杂度为 O(1)（均摊）。
  - **适用场景**：
    - `unordered_set`：需要存储唯一无序元素。
    - `unordered_map`：需要存储键值对且键无序。
  - **示例**：
    ```cpp
    std::unordered_set<int> us = {1, 2, 3};
    us.insert(4); // 插入
    us.erase(2); // 删除

    std::unordered_map<int, std::string> um = {{1, "one"}, {2, "two"}};
    um[3] = "three"; // 插入
    ```

- **关联容器对比**：
  | 容器                            | 底层实现 | 是否有序 | 时间复杂度   |
  | ------------------------------- | -------- | -------- | ------------ |
  | `set`/`map`                     | 红黑树   | 有序     | O(log n)     |
  | `unordered_set`/`unordered_map` | 哈希表   | 无序     | O(1)（均摊） |

---

#### **3. 迭代器**
- **迭代器种类**：
  - **输入迭代器**：只支持读取，单向移动。
  - **输出迭代器**：只支持写入，单向移动。
  - **前向迭代器**：支持读取和写入，单向移动。
  - **双向迭代器**：支持读取和写入，支持双向移动。
  - **随机访问迭代器**：支持读取和写入，可随机跳转。
- **示例**：
  ```cpp
  std::vector<int> v = {1, 2, 3};
  for (auto it = v.begin(); it != v.end(); ++it) {
      std::cout << *it << std::endl;
  }
  ```

---

#### **4. 常用算法**
- **`sort`**：
  - 用于排序。
  - 时间复杂度：O(n log n)。
  - 示例：
    ```cpp
    std::vector<int> v = {3, 1, 4};
    std::sort(v.begin(), v.end());
    ```

- **`find`**：
  - 用于查找值。
  - 时间复杂度：O(n)。
  - 示例：
    ```cpp
    auto it = std::find(v.begin(), v.end(), 3);
    ```

- **`binary_search`**：
  - 用于二分查找，要求容器有序。
  - 时间复杂度：O(log n)。
  - 示例：
    ```cpp
    bool found = std::binary_search(v.begin(), v.end(), 3);
    ```

- **`accumulate`**：
  - 用于累加容器中的值。
  - 示例：
    ```cpp
    int sum = std::accumulate(v.begin(), v.end(), 0);
    ```

---

#### **5. 其他**
- **`std::span`**（C++20）：
  - 表示固定大小的连续内存范围。
  - 不会复制数据，适用于高效的数组访问。
  - 示例：
    ```cpp
    std::vector<int> v = {1, 2, 3};
    std::span<int> s(v.data(), v.size());
    ```

- **`std::string_view`**（C++17）：
  - 表示不可变的字符串视图，避免字符串复制。
  - 示例：
    ```cpp
    std::string str = "hello";
    std::string_view sv = str;
    ```

- **`emplace` vs `insert`**：
  - **`emplace`**：直接在容器中构造对象，避免额外的拷贝或移动。
  - **`insert`**：将已有对象插入容器，可能涉及拷贝或移动。
  - 示例：
    ```cpp
    std::vector<std::pair<int, std::string>> v;
    v.emplace_back(1, "one"); // 构造对象
    v.push_back({2, "two"}); // 插入现有对象
    ```
## 六、异常处理
### **六、异常处理详解**

#### **1. `try/catch/throw`**
- **`try` 块**：
  - 用于包含可能抛出异常的代码。
  - 如果发生异常，程序会直接跳到相应的 `catch` 块，不再执行 `try` 块中剩余的代码。
- **`throw` 语句**：
  - 用于抛出异常对象，可以是任意类型（通常是 `std::exception` 或其派生类）。
  - 示例：
    ```cpp
    throw std::runtime_error("Error occurred");
    ```
- **`catch` 块**：
  - 捕获异常并处理。
  - 可以定义多个 `catch` 块来处理不同类型的异常。
  - 示例：
    ```cpp
    try {
        throw std::runtime_error("Some error");
    }
    catch (const std::runtime_error& e) {
        std::cout << "Runtime error: " << e.what() << std::endl;
    }
    catch (...) { // 捕获所有其他未捕获的异常
        std::cout << "Unknown error" << std::endl;
    }
    ```

- **异常传递机制**：
  - 当异常被抛出时，程序会沿着调用栈向上传递，直到找到匹配的 `catch` 块。如果没有找到匹配的 `catch`，程序会调用 `std::terminate()` 并终止。

- **异常安全等级**：
  - **基本异常安全**：
    - 保证程序不会泄漏资源或损坏数据，但可能处于不一致状态。
    - 示例：`std::vector::push_back`（如果分配失败，容器可能未改变）。
  - **强异常安全**：
    - 保证操作要么完全完成，要么完全不影响程序状态（事务性）。
    - 示例：`std::vector::swap`。
  - **无异常保证**：
    - 保证函数不会抛出异常。
    - 示例：`std::vector::size`。

---

#### **2. `noexcept`**
- **作用**：
  - 用于标记函数不会抛出异常。
  - 编译器可以对 `noexcept` 函数进行优化，例如内联调用、消除异常检查。
  - 示例：
    ```cpp
    void func() noexcept {
        // 不会抛出异常
    }
    ```

- **语法**：
  - `noexcept` 可以用在函数声明上：
    ```cpp
    void func() noexcept; // 声明
    void func() noexcept {} // 定义
    ```
  - `noexcept(expr)`：根据表达式 `expr` 的值（布尔值）决定是否标记函数为 noexcept。
    ```cpp
    void func() noexcept(false); // 明确声明可能抛出异常
    ```

- **使用场景**：
  - 标记不会抛出异常的函数（如析构函数、性能关键代码）。
  - 避免不必要的异常检查。

- **注意事项**：
  - 如果 `noexcept` 函数确实抛出异常，会调用 `std::terminate()`。
  - 示例：
    ```cpp
    void func() noexcept {
        throw std::runtime_error("Error"); // 程序终止
    }
    ```

---

#### **3. 自定义异常类**
- **继承自 `std::exception`**：
  - 自定义异常类应该继承自 `std::exception` 或其派生类。
  - 重写 `what()` 函数以返回异常信息。
  - 示例：
    ```cpp
    class MyException : public std::exception {
      private:
        std::string message;
      public:
        MyException(const std::string& msg) : message(msg) {}
        const char* what() const noexcept override {
            return message.c_str();
        }
    };

    int main() {
        try {
            throw MyException("Custom exception occurred");
        }
        catch (const MyException& e) {
            std::cout << e.what() << std::endl;
        }
    }
    ```

- **设计规范**：
  - 异常类应尽量简单，避免复杂的逻辑。
  - 提供直观的异常信息，便于调试和定位问题。

---

#### **4. 栈展开（Stack Unwinding）**
- **定义**：
  - 栈展开是指在异常传播过程中，沿调用栈逐层退出，销毁局部对象的过程。
  - 在栈展开的每一层，局部对象的析构函数会被调用，确保资源正确释放。

- **工作机制**：
  - 当异常被抛出时，`try` 块中的剩余代码将被跳过。
  - 调用栈的每一层会自动调用已创建对象的析构函数，直到找到匹配的 `catch` 块。

- **示例**：
  ```cpp
  class Resource {
  public:
      Resource() { std::cout << "Resource acquired" << std::endl; }
      ~Resource() { std::cout << "Resource released" << std::endl; }
  };

  void func() {
      Resource res; // 栈上的资源
      throw std::runtime_error("Error"); // 抛出异常
  }

  int main() {
      try {
          func();
      }
      catch (const std::exception& e) {
          std::cout << e.what() << std::endl;
      }
  }
  ```
  **输出**：
  ```
  Resource acquired
  Resource released
  Error
  ```

- **注意事项**：
  - 析构函数中抛出异常是危险的，可能导致程序终止。
    ```cpp
    class Resource {
    public:
        ~Resource() noexcept(false) {
            throw std::runtime_error("Error in destructor"); // 不推荐
        }
    };
    ```

---

#### **补充知识**
- **标准库异常类层次结构**：
  - `std::exception`：所有异常的基类。
  - 常见派生类：
    - `std::logic_error`：
      - 用于逻辑错误，例如 `std::invalid_argument`、`std::out_of_range`。
    - `std::runtime_error`：
      - 用于运行时错误，例如 `std::overflow_error`、`std::underflow_error`。
  - 示例：
    ```cpp
    try {
        throw std::out_of_range("Out of range error");
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    ```

- **`catch` 顺序**：
  - 捕获异常时，`catch` 块的顺序很重要，应从派生类到基类排序。
  - 示例：
    ```cpp
    try {
        throw std::out_of_range("Error");
    }
    catch (const std::out_of_range& e) {
        std::cout << "Out of range: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    ```

- **`std::terminate()` 和 `std::unexpected()`**：
  - 如果异常未被捕获或 `noexcept` 函数中抛出异常，会调用 `std::terminate()`。
  - `std::unexpected()` 是一个已废弃的机制，用于处理异常规范不匹配的情况。

---

### **总结**
1. 使用 `try/catch/throw` 实现异常处理机制，合理设计异常安全等级。
2. 使用 `noexcept` 明确声明无异常函数，提升运行时性能。
3. 定义自定义异常类时，继承自 `std::exception` 并重写 `what()` 函数。
4. 理解栈展开过程，确保资源在异常传播中的正确释放。
5. 避免析构函数中抛出异常，防止程序终止。

## 七、并发与多线程
### **七、并发与多线程**

#### **1. 线程管理：`std::thread` vs `std::async`**
- **`std::thread`**:
  - 用于创建和管理线程。
  - 需要显式地管理线程的生命周期（如调用 `join()` 或 `detach()`）。
  - 示例：
    ```cpp
    void worker() {
        std::cout << "Thread is running" << std::endl;
    }

    int main() {
        std::thread t(worker); // 创建线程
        t.join(); // 等待线程完成
    }
    ```

- **`std::async`**:
  - 高层次的异步操作工具，自动管理线程。
  - 返回一个 `std::future` 对象，用于获取异步操作的结果。
  - 默认行为由 `std::launch` 决定：
    - `std::launch::async`：异步启动任务。
    - `std::launch::deferred`：延迟启动任务，直到调用 `get()`。
  - 示例：
    ```cpp
    int worker() {
        return 42;
    }

    int main() {
        auto fut = std::async(std::launch::async, worker); // 异步启动
        std::cout << fut.get() << std::endl; // 获取结果
    }
    ```

- **区别**:
  | 特性         | `std::thread`                     | `std::async`                       |
  | ------------ | --------------------------------- | ---------------------------------- |
  | 生命周期管理 | 手动管理线程 (`join` 或 `detach`) | 自动管理线程（通过 `std::future`） |
  | 适用场景     | 需要显式线程控制                  | 任务更高级抽象，处理异步结果       |
  | 返回值       | 不支持                            | 返回 `std::future`，支持结果获取   |

---

#### **2. 同步原语**

- **`std::mutex`**:
  - 用于保护共享资源，防止多个线程同时访问引发数据竞争。
  - 示例：
    ```cpp
    std::mutex mtx;

    void worker() {
        std::lock_guard<std::mutex> lock(mtx); // 自动加锁和解锁
        std::cout << "Thread-safe output" << std::endl;
    }
    ```

- **`std::recursive_mutex`**:
  - 允许同一线程多次加锁（递归加锁）。
  - 示例：
    ```cpp
    std::recursive_mutex rmtx;

    void recursive_func(int count) {
        if (count <= 0) return;
        rmtx.lock();
        std::cout << "Recursive count: " << count << std::endl;
        recursive_func(count - 1);
        rmtx.unlock();
    }
    ```

- **`std::lock_guard`**:
  - RAII 风格的加锁工具，在构造时加锁，析构时解锁。
  - 适用于简单的加锁场景。
  - 示例：
    ```cpp
    std::mutex mtx;

    void worker() {
        std::lock_guard<std::mutex> lock(mtx); // 自动加锁和解锁
        std::cout << "Thread-safe output" << std::endl;
    }
    ```

- **`std::unique_lock`**:
  - 灵活的加锁工具，支持延迟加锁、解锁后再加锁等操作。
  - 示例：
    ```cpp
    std::mutex mtx;

    void worker() {
        std::unique_lock<std::mutex> lock(mtx, std::defer_lock); // 延迟加锁
        lock.lock(); // 手动加锁
        std::cout << "Thread-safe output" << std::endl;
    }
    ```

- **条件变量 (`std::condition_variable`)**:
  - 用于线程间的条件同步，让线程等待某个条件满足。
  - 示例：
    ```cpp
    std::mutex mtx;
    std::condition_variable cv;
    bool ready = false;

    void worker() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return ready; }); // 等待条件满足
        std::cout << "Worker thread is running" << std::endl;
    }

    int main() {
        std::thread t(worker);
        {
            std::lock_guard<std::mutex> lock(mtx);
            ready = true;
        }
        cv.notify_one(); // 通知一个线程
        t.join();
    }
    ```

---

#### **3. 原子操作：`std::atomic` 和内存序**

- **`std::atomic`**:
  - 提供原子操作，避免使用锁来保护共享数据。
  - 示例：
    ```cpp
    std::atomic<int> counter(0);

    void increment() {
        counter.fetch_add(1, std::memory_order_relaxed);
    }
    ```

- **内存序（Memory Ordering）**:
  - 控制线程之间对内存的可见性和操作顺序。
  - 常见内存序：
    - `std::memory_order_relaxed`: 无序，适合不依赖同步的场景。
    - `std::memory_order_acquire`: 获取操作，保证后续操作不会在此操作之前执行。
    - `std::memory_order_release`: 释放操作，保证之前的操作不会在此操作之后执行。
    - `std::memory_order_acq_rel`: 同时满足获取和释放语义。
    - `std::memory_order_seq_cst`: 顺序一致性，最严格的内存序。

---

#### **4. 死锁、竞态**

- **死锁的常见陷阱**:
  1. **多个线程以不同顺序加锁**:
     - 示例：
       ```cpp
       std::mutex mtx1, mtx2;

       void thread1() {
           std::lock_guard<std::mutex> lock1(mtx1);
           std::lock_guard<std::mutex> lock2(mtx2);
       }

       void thread2() {
           std::lock_guard<std::mutex> lock1(mtx2);
           std::lock_guard<std::mutex> lock2(mtx1); // 引发死锁
       }
       ```

  2. **一个线程持有锁后等待另一个线程的资源**:
     - 示例：线程 A 持有资源 1，等待资源 2；线程 B 持有资源 2，等待资源 1。

- **预防策略**:
  1. **加锁顺序一致性**:
     - 始终以相同的顺序加锁。
  2. **使用 `std::lock` 防止死锁**:
     - 示例：
       ```cpp
       std::mutex mtx1, mtx2;

       void thread_safe() {
           std::lock(mtx1, mtx2); // 一次性加锁，避免死锁
           std::lock_guard<std::mutex> lock1(mtx1, std::adopt_lock);
           std::lock_guard<std::mutex> lock2(mtx2, std::adopt_lock);
       }
       ```

  3. **避免持有锁时执行耗时操作**:
     - 在加锁范围内，尽量减少耗时操作。

- **竞态条件**:
  - 当多个线程同时访问共享数据且至少有一个线程对数据进行写操作时发生。
  - **解决方法**:
    - 使用 `std::mutex` 保证互斥访问。
    - 使用 `std::atomic` 进行原子操作。

---

#### **5. 线程池设计**

- **线程池的概念**:
  - 创建一组固定数量的线程，通过任务队列分配任务，提高线程复用率。

- **简单实现**:
  ```cpp
  #include <iostream>
  #include <thread>
  #include <vector>
  #include <queue>
  #include <condition_variable>
  #include <functional>
  #include <atomic>

  class ThreadPool {
      std::vector<std::thread> workers;
      std::queue<std::function<void()>> tasks;
      std::mutex mtx;
      std::condition_variable cv;
      std::atomic<bool> stop;

  public:
      ThreadPool(size_t numThreads) : stop(false) {
          for (size_t i = 0; i < numThreads; ++i) {
              workers.emplace_back([this] {
                  while (true) {
                      std::function<void()> task;
                      {
                          std::unique_lock<std::mutex> lock(mtx);
                          cv.wait(lock, [this] { return stop || !tasks.empty(); });
                          if (stop && tasks.empty()) return;
                          task = std::move(tasks.front());
                          tasks.pop();
                      }
                      task();
                  }
              });
          }
      }

      ~ThreadPool() {
          {
              std::lock_guard<std::mutex> lock(mtx);
              stop = true;
          }
          cv.notify_all();
          for (std::thread &worker : workers) {
              if (worker.joinable()) worker.join();
          }
      }

      void enqueue(std::function<void()> task) {
          {
              std::lock_guard<std::mutex> lock(mtx);
              tasks.emplace(std::move(task));
          }
          cv.notify_one();
      }
  };

  int main() {
      ThreadPool pool(4);

      for (int i = 0; i < 8; ++i) {
          pool.enqueue([i] {
              std::cout << "Task " << i << " is running" << std::endl;
          });
      }
  }
  ```

- **注意事项**:
  - 线程池需要正确处理任务队列的线程安全。
  - 需要合法终止线程池（如等待所有线程完成后销毁）。

---

### **总结**
1. 使用 `std::thread` 和 `std::async` 管理线程，根据需求选择高效工具。
2. 利用 `std::mutex`、`std::lock_guard`、`std::unique_lock` 等同步原语保护共享数据。
3. 使用 `std::atomic` 和内存序优化原子操作，确保数据一致性。
4. 通过一致的加锁顺序和 `std::lock` 避免死锁，设计线程池提高线程复用率。

## 八、现代 C++ 新特性
### **现代 C++ 新特性详解**

#### **1. C++11/14 新特性**

- **`auto`**:
  - 自动类型推导，让编译器根据初始化表达式推导变量类型。
  - **适用场景**：简化代码，尤其是复杂类型（如迭代器）。
  - **示例**:
    ```cpp
    auto x = 10;       // 推导为 int
    auto y = 3.14;     // 推导为 double
    auto z = "hello";  // 推导为 const char*
    ```

- **`decltype`**:
  - 用于推导表达式的类型，与 `auto` 不同，`decltype` 仅推导类型，不进行变量初始化。
  - **适用场景**：需要明确表达式类型时。
  - **示例**:
    ```cpp
    int x = 10;
    decltype(x) y = 20; // y 的类型为 int
    ```

- **范围 `for` 循环**:
  - 用于遍历容器或数组，简化代码。
  - **示例**:
    ```cpp
    std::vector<int> v = {1, 2, 3};
    for (auto& item : v) {
        std::cout << item << std::endl;
    }
    ```

- **Lambda 表达式**:
  - 用于定义匿名函数，简化回调或内联代码。
  - **语法**: `[捕获列表](参数列表) -> 返回类型 { 函数体 }`
  - **示例**:
    ```cpp
    auto add = [](int a, int b) -> int { return a + b; };
    std::cout << add(3, 4) << std::endl; // 输出 7
    ```

- **右值引用与移动语义**:
  - **右值引用 (`T&&`)**:
    - 允许绑定右值，避免不必要的拷贝。
    - 用于实现 **移动语义** 和 **完美转发**。
    - **示例**:
      ```cpp
      int x = 10;
      int&& r = 20;  // r 是右值引用
      ```
  - **移动语义**:
    - 提供资源转移的能力，避免拷贝开销。
    - **示例**:
      ```cpp
      std::vector<int> v1 = {1, 2, 3};
      std::vector<int> v2 = std::move(v1); // v1 的资源转移给 v2
      ```

---

#### **2. C++17 新特性**

- **结构化绑定**:
  - 将数据解构为多个变量，简化代码。
  - **示例**:
    ```cpp
    std::tuple<int, double, std::string> t = {1, 2.5, "hello"};
    auto [i, d, s] = t; // 解构 t
    ```

- **`if constexpr`**:
  - 编译期条件判断，替代 `SFINAE` 实现更简单的模板代码。
  - **示例**:
    ```cpp
    template <typename T>
    void print(T value) {
        if constexpr (std::is_integral<T>::value) {
            std::cout << "Integral: " << value << std::endl;
        } else {
            std::cout << "Non-integral: " << value << std::endl;
        }
    }
    ```

- **并行算法**:
  - C++17 为标准库算法添加了并行执行策略。
  - **执行策略**:
    - `std::execution::seq`：顺序执行。
    - `std::execution::par`：并行执行。
    - `std::execution::par_unseq`：并行且无序执行。
  - **示例**:
    ```cpp
    #include <execution>
    std::vector<int> v = {1, 2, 3, 4};
    std::sort(std::execution::par, v.begin(), v.end());
    ```

- **`std::optional`**:
  - 表示一个可能为空的值，避免使用指针或魔法值。
  - **示例**:
    ```cpp
    std::optional<int> opt = 42;
    if (opt) {
        std::cout << *opt << std::endl; // 输出 42
    }
    ```

- **`std::variant`**:
  - 类型安全的联合体，用于存储多个类型中的一个。
  - **示例**:
    ```cpp
    std::variant<int, std::string> var = "hello";
    std::cout << std::get<std::string>(var) << std::endl;
    ```

---

#### **3. C++20/23 新特性**

- **概念（Concepts）**:
  - 用于约束模板参数类型，提升模板代码的可读性和错误诊断。
  - **示例**:
    ```cpp
    template <typename T>
    concept Integral = std::is_integral<T>::value;

    template <Integral T>
    void print(T value) {
        std::cout << value << std::endl;
    }
    ```

- **范围库（Ranges）**:
  - 提供更强大的范围操作（过滤、变换、组合）。
  - **示例**:
    ```cpp
    #include <ranges>
    std::vector<int> v = {1, 2, 3, 4};
    for (auto x : v | std::ranges::views::filter([](int n) { return n % 2 == 0; })) {
        std::cout << x << std::endl; // 输出 2, 4
    }
    ```

- **协程（Coroutines）**:
  - C++20 引入协程支持，用于实现异步或生成器模式。
  - **关键字**:
    - `co_await`：等待异步操作。
    - `co_yield`：生成值。
    - `co_return`：返回值。
  - **示例**:
    ```cpp
    std::generator<int> generate_numbers() {
        for (int i = 0; i < 5; ++i) {
            co_yield i;
        }
    }
    ```

- **模块（Modules）**:
  - 提供更高效的代码组织方式，替代头文件机制。
  - **语法**:
    - 定义模块：`export module MyModule;`
    - 导入模块：`import MyModule;`

- **三向比较运算符 (`<=>`)**:
  - 提供统一的比较操作，返回 `std::strong_ordering` 或类似类型。
  - **示例**:
    ```cpp
    #include <compare>
    int a = 1, b = 2;
    if (a <=> b < 0) { // 等价于 a < b
        std::cout << "a is less than b" << std::endl;
    }
    ```

---

### **总结**
1. **C++11/14**：简化代码的 `auto`、`decltype`，强大的 Lambda 表达式，右值引用和移动语义。
2. **C++17**：增强的模板支持（`if constexpr`）、并行算法、类型安全的 `std::optional` 和 `std::variant`。
3. **C++20/23**：概念、范围库、协程、模块，以及统一的三向比较运算符。
4. 现代 C++ 特性旨在提高代码可读性、性能和安全性，面试中常被问及使用场景和具体实现。

## 九、性能优化与调试
### **九、性能优化与调试详解**

#### **1. 性能剖析**
性能剖析是分析程序执行效率的关键技术，用于定位性能瓶颈并优化代码。

- **`gprof`**：
  - **用途**：GNU 提供的性能分析工具，用于采样程序的函数调用次数和运行时间。
  - **使用步骤**：
    1. 编译时添加 `-pg` 选项：
       ```bash
       g++ -pg -o my_program my_program.cpp
       ```
    2. 运行程序，生成 `gmon.out` 文件：
       ```bash
       ./my_program
       ```
    3. 使用 `gprof` 解析数据：
       ```bash
       gprof my_program gmon.out > analysis.txt
       ```
  - **输出**：显示函数调用次数、运行时间等。

- **`perf`**：
  - **用途**：Linux 的性能剖析工具，可分析 CPU 使用率、缓存命中率等。
  - **使用步骤**：
    1. 安装 `perf`：
       ```bash
       sudo apt install linux-tools-common linux-tools-generic
       ```
    2. 运行程序并记录性能数据：
       ```bash
       perf record ./my_program
       ```
    3. 查看性能报告：
       ```bash
       perf report
       ```
  - **输出**：函数调用的耗时、CPU 占用等。

- **Sanitizer**：
  - **`AddressSanitizer` (ASan)**：
    - 用于检测内存越界、非法访问等问题。
    - 编译时添加 `-fsanitize=address`：
      ```bash
      g++ -fsanitize=address -o my_program my_program.cpp
      ./my_program
      ```
  - **`ThreadSanitizer` (TSan)**：
    - 用于检测数据竞争问题。
    - 编译时添加 `-fsanitize=thread`：
      ```bash
      g++ -fsanitize=thread -o my_program my_program.cpp
      ./my_program
      ```

---

#### **2. 内存对齐与缓存优化**
内存对齐和缓存优化能够显著提升程序的性能，特别是在数据密集型场景中。

- **局部性原理**：
  - **时间局部性**：最近访问的内存地址很可能在不久后再次被访问。
  - **空间局部性**：与当前访问的地址相邻的地址很可能被访问。
  - **优化策略**：
    - 合理布局数据结构，尽量减少缓存行失效。
    - 使用连续存储的容器（如 `std::vector`）。

- **数据对齐 `alignas`**：
  - **作用**：确保数据按照特定字节对齐，提高内存访问效率。
  - **示例**：
    ```cpp
    struct alignas(16) MyStruct {
        int a;
        float b;
    };
    ```

- **内存填充（padding）**：
  - **问题**：数据对齐可能导致内存浪费。
  - **优化**：调整数据成员顺序，减少填充。
  - **示例**：
    ```cpp
    struct MyStruct {
        char a;    // 1 字节
        // 3 字节填充
        int b;     // 4 字节
    }; // 总大小为 8 字节
    ```

---

#### **3. `inline` 与 `constexpr` 优化**
减少函数调用开销是优化程序性能的重要手段之一。

- **`inline`**：
  - **作用**：提示编译器将函数展开为内联代码，避免函数调用开销。
  - **使用场景**：
    - 小型、频繁调用的函数。
  - **示例**：
    ```cpp
    inline int add(int a, int b) {
        return a + b;
    }
    ```

- **`constexpr`**：
  - **作用**：在编译期计算函数结果，避免运行时计算。
  - **使用场景**：
    - 值在编译期已知的函数。
  - **示例**：
    ```cpp
    constexpr int square(int x) {
        return x * x;
    }

    constexpr int result = square(5); // 编译期计算
    ```

- **注意**：
  - `inline` 不适用于大型函数，可能导致代码膨胀。
  - `constexpr` 要求函数是纯函数，即不依赖运行时状态。

---

#### **4. 调试工具**

- **`gdb`**：
  - **用途**：GNU 调试器，用于调试 C++ 程序。
  - **常用命令**：
    - 启动调试：
      ```bash
      gdb ./my_program
      ```
    - 设置断点：
      ```bash
      break main
      ```
    - 单步执行：
      ```bash
      step
      ```
    - 查看变量值：
      ```bash
      print var_name
      ```

- **`valgrind`**：
  - **用途**：内存泄漏检测工具。
  - **使用步骤**：
    1. 安装 `valgrind`：
       ```bash
       sudo apt install valgrind
       ```
    2. 运行程序：
       ```bash
       valgrind --leak-check=full ./my_program
       ```
  - **输出**：显示内存泄漏的详细信息。

- **IDE 集成调试**：
  - 大多数现代 IDE（如 VSCode、CLion）都提供了集成调试工具，支持断点、变量查看等功能。
  - **示例（VSCode + gdb）**：
    1. 配置 `launch.json`：
       ```json
       {
           "version": "0.2.0",
           "configurations": [
               {
                   "name": "g++ Debug",
                   "type": "cppdbg",
                   "request": "launch",
                   "program": "${workspaceFolder}/my_program",
                   "args": [],
                   "stopAtEntry": false,
                   "cwd": "${workspaceFolder}",
                   "environment": [],
                   "externalConsole": false,
                   "MIMode": "gdb",
                   "setupCommands": [
                       {
                           "description": "Enable pretty-printing for gdb",
                           "text": "-enable-pretty-printing",
                           "ignoreFailures": true
                       }
                   ],
                   "preLaunchTask": "build"
               }
           ]
       }
       ```

---

### **总结**
1. 使用性能剖析工具（如 `gprof`、`perf`）定位性能瓶颈。
2. 合理利用内存对齐和缓存优化，提升数据访问效率。
3. 利用 `inline` 和 `constexpr` 减少函数调用和运行时计算开销。
4. 熟练掌握调试工具（如 `gdb`、`valgrind`）的使用，快速定位问题并优化代码。

## 十、设计模式与架构
### **十、设计模式与架构详解**

#### **1. 常用设计模式**

1. **单例模式（Singleton）**
   - **作用**：确保一个类只有一个实例，提供全局访问点。
   - **实现**：
     ```cpp
     class Singleton {
       public:
         static Singleton& getInstance() {
             static Singleton instance; // 静态局部变量，线程安全（C++11及以上）
             return instance;
         }
         Singleton(const Singleton&) = delete; // 禁止拷贝构造
         Singleton& operator=(const Singleton&) = delete; // 禁止赋值

       private:
         Singleton() {} // 私有构造函数
     };
     ```
   - **应用场景**：配置管理、日志系统、线程池等。

2. **工厂模式（Factory）**
   - **作用**：将对象的创建与使用分离，统一对象创建逻辑。
   - **实现**：
     ```cpp
     class Product {
       public:
         virtual void use() = 0;
         virtual ~Product() {}
     };

     class ConcreteProductA : public Product {
       public:
         void use() override { std::cout << "Using Product A" << std::endl; }
     };

     class ConcreteProductB : public Product {
       public:
         void use() override { std::cout << "Using Product B" << std::endl; }
     };

     class Factory {
       public:
         static std::unique_ptr<Product> createProduct(const std::string& type) {
             if (type == "A") return std::make_unique<ConcreteProductA>();
             if (type == "B") return std::make_unique<ConcreteProductB>();
             return nullptr;
         }
     };

     int main() {
         auto product = Factory::createProduct("A");
         product->use();
     }
     ```
   - **应用场景**：对象创建逻辑复杂或类型动态变化的场景。

3. **观察者模式（Observer）**
   - **作用**：当一个对象的状态发生变化时，通知所有依赖者。
   - **实现**：
     ```cpp
     class Observer {
       public:
         virtual void update(int value) = 0;
     };

     class Subject {
       private:
         std::vector<Observer*> observers;
         int state;

       public:
         void attach(Observer* observer) { observers.push_back(observer); }
         void setState(int value) {
             state = value;
             notify();
         }
         void notify() {
             for (auto observer : observers) observer->update(state);
         }
     };

     class ConcreteObserver : public Observer {
       public:
         void update(int value) override {
             std::cout << "Observer updated with value: " << value << std::endl;
         }
     };

     int main() {
         Subject subject;
         ConcreteObserver observer;
         subject.attach(&observer);
         subject.setState(42);
     }
     ```
   - **应用场景**：事件系统、GUI 框架、订阅-发布模型。

4. **策略模式（Strategy）**
   - **作用**：定义一组算法，将其封装并使它们可以互换。
   - **实现**：
     ```cpp
     class Strategy {
       public:
         virtual void execute() = 0;
         virtual ~Strategy() {}
     };

     class ConcreteStrategyA : public Strategy {
       public:
         void execute() override { std::cout << "Strategy A executed" << std::endl; }
     };

     class ConcreteStrategyB : public Strategy {
       public:
         void execute() override { std::cout << "Strategy B executed" << std::endl; }
     };

     class Context {
       private:
         std::unique_ptr<Strategy> strategy;

       public:
         void setStrategy(std::unique_ptr<Strategy> s) { strategy = std::move(s); }
         void executeStrategy() { strategy->execute(); }
     };

     int main() {
         Context context;
         context.setStrategy(std::make_unique<ConcreteStrategyA>());
         context.executeStrategy();
         context.setStrategy(std::make_unique<ConcreteStrategyB>());
         context.executeStrategy();
     }
     ```
   - **应用场景**：支付方式选择、排序算法切换等。

5. **适配器模式（Adapter）**
   - **作用**：将一个类的接口转换为客户端期望的接口。
   - **实现**：
     ```cpp
     class Target {
       public:
         virtual void request() = 0;
     };

     class Adaptee {
       public:
         void specificRequest() { std::cout << "Specific request executed" << std::endl; }
     };

     class Adapter : public Target {
       private:
         Adaptee& adaptee;

       public:
         Adapter(Adaptee& a) : adaptee(a) {}
         void request() override { adaptee.specificRequest(); }
     };

     int main() {
         Adaptee adaptee;
         Adapter adapter(adaptee);
         adapter.request();
     }
     ```
   - **应用场景**：接口兼容性问题、第三方库集成。

---

#### **2. CRTP（Curiously Recurring Template Pattern）**
- **定义**：使用模板实现静态多态，让派生类将自身作为模板参数传递给基类。
- **优点**：
  - 编译期多态（无需虚函数表开销）。
  - 可继承基类的功能，同时在派生类中自定义行为。
- **实现**：
  ```cpp
  template <typename Derived>
  class Base {
    public:
      void interface() {
          static_cast<Derived*>(this)->implementation();
      }
  };

  class Derived : public Base<Derived> {
    public:
      void implementation() { std::cout << "Derived implementation" << std::endl; }
  };

  int main() {
      Derived d;
      d.interface(); // 调用 Derived 的实现
  }
  ```
- **应用场景**：实现静态多态、编译期优化（如 `std::enable_shared_from_this`、Active Record 模式）。

---

#### **3. Pimpl（Pointer to Implementation）习惯用法**
- **定义**：通过指针隐藏实现细节，以实现编译期隔离和 ABI 稳定。
- **优点**：
  - 减少编译依赖，降低编译时间。
  - 提供更好的封装性，隐藏实现细节。
  - 保持二进制接口（ABI）稳定。
- **实现**：
  ```cpp
  // Header file
  class MyClass {
    public:
      MyClass();
      ~MyClass();
      void doSomething();

    private:
      class Impl;
      std::unique_ptr<Impl> pImpl;
  };

  // Source file
  class MyClass::Impl {
    public:
      void doSomething() { std::cout << "Doing something" << std::endl; }
  };

  MyClass::MyClass() : pImpl(std::make_unique<Impl>()) {}
  MyClass::~MyClass() = default;

  void MyClass::doSomething() { pImpl->doSomething(); }

  int main() {
      MyClass obj;
      obj.doSomething();
  }
  ```
- **应用场景**：库开发、隐藏复杂实现、实现模块化设计。

---

#### **4. SOLID 原则**
1. **单一职责原则（SRP）**：
   - 每个类只负责一个功能或职责。
   - 示例：
     ```cpp
     class Logger {
       public:
         void log(const std::string& message) { std::cout << message << std::endl; }
     };
     ```

2. **开闭原则（OCP）**：
   - 类对扩展开放，对修改关闭。
   - 示例：通过继承扩展功能。
     ```cpp
     class Shape {
       public:
         virtual void draw() = 0;
     };

     class Circle : public Shape {
       public:
         void draw() override { std::cout << "Drawing Circle" << std::endl; }
     };

     class Rectangle : public Shape {
       public:
         void draw() override { std::cout << "Drawing Rectangle" << std::endl; }
     };
     ```

3. **里氏替换原则（LSP）**：
   - 子类必须能够替换基类而不影响程序行为。
   - 示例：确保继承关系的行为一致。

4. **接口隔离原则（ISP）**：
   - 接口应小而专，避免庞大接口。
   - 示例：拆分接口。
     ```cpp
     class Printable {
       public:
         virtual void print() = 0;
     };

     class Scannable {
       public:
         virtual void scan() = 0;
     };
     ```

5. **依赖倒置原则（DIP）**：
   - 高层模块不应依赖低层模块，它们都应依赖抽象。
   - 示例：
     ```cpp
     class IDataStorage {
       public:
         virtual void save(const std::string& data) = 0;
     };

     class Database : public IDataStorage {
       public:
         void save(const std::string& data) override {
             std::cout << "Saving to database: " << data << std::endl;
         }
     };

     class Application {
       private:
         IDataStorage& storage;

       public:
         Application(IDataStorage& s) : storage(s) {}
         void saveData(const std::string& data) { storage.save(data); }
     };
     ```

---

### **总结**
1. 熟悉常见设计模式（单例、工厂、观察者、策略、适配器）的实现和应用场景。
2. 掌握 CRTP 以实现静态多态和编译期优化。
3. 使用 Pimpl 习惯用法隐藏实现细节，确保 ABI 稳定。
4. 遵循 SOLID 原则，编写高内聚、低耦合的代码结构。

## 十一、嵌入式与底层编程

#### **1. `volatile` 与内存屏障**
- **`volatile`**:
  - **作用**:
    - 告诉编译器不要优化对变量的访问。
    - 通常用于硬件寄存器、中断服务程序和共享内存的变量。
  - **工作原理**:
    - 每次访问 `volatile` 变量时，都会直接从内存中读取或写入，而不是从寄存器或优化后的值中获取。
  - **示例**:
    ```cpp
    volatile int flag = 0;

    void checkFlag() {
        while (flag == 0) {
            // 等待其他线程或硬件修改 flag
        }
    }
    ```
  - **使用场景**:
    - 硬件寄存器访问：
      ```cpp
      #define REG_STATUS (*(volatile unsigned int*)0x40001000)
      unsigned int status = REG_STATUS; // 确保直接读取寄存器值
      ```
    - 中断处理和多线程共享变量。

- **内存屏障（Memory Barrier）**:
  - **作用**:
    - 确保指令或内存操作的执行顺序不被编译器或 CPU 改变。
  - **分类**:
    - **编译器屏障**: 防止编译器重排序。
    - **硬件屏障**: 防止 CPU 重排序。
  - **实现**:
    - 编译器屏障（GCC）:
      ```cpp
      #define COMPILER_BARRIER() __asm__ __volatile__ ("" ::: "memory")
      ```
    - 硬件屏障（例如 ARM 架构）:
      ```cpp
      #define MEMORY_BARRIER() __asm__ __volatile__ ("dmb sy" ::: "memory")
      ```

---

#### **2. 位运算与位域**
- **位运算**：
  - **常见操作**:
    - 按位与 (`&`): 用于清除某些位。
    - 按位或 (`|`): 用于设置某些位。
    - 按位异或 (`^`): 用于翻转某些位。
    - 按位取反 (`~`): 用于反转所有位。
    - 左移 (`<<`): 用于将位向左移。
    - 右移 (`>>`): 用于将位向右移。
  - **示例**:
    ```cpp
    unsigned int x = 0b1010;
    x |= 0b0100;  // 设置第3位，结果为 0b1110
    x &= ~0b0010; // 清除第2位，结果为 0b1100
    x ^= 0b1000;  // 翻转第4位，结果为 0b0100
    ```

- **位域**:
  - **定义**:
    - 位域用于在结构体中按位定义变量，以节省存储空间。
  - **示例**:
    ```cpp
    struct Flags {
        unsigned int flag1 : 1; // 1 位
        unsigned int flag2 : 3; // 3 位
        unsigned int flag3 : 4; // 4 位
    };

    int main() {
        Flags flags = {0, 5, 10};
        std::cout << flags.flag2 << std::endl; // 输出 5
    }
    ```
  - **注意事项**:
    - 位域的位数不能超过其类型的总位数。
    - 位域的存储方式（按高位或低位分配）取决于具体的编译器和平台。

- **常见技巧**:
  - **判断某个位是否为 1**:
    ```cpp
    if (x & (1 << 3)) { /* 第 4 位为 1 */ }
    ```
  - **设置某个位为 1**:
    ```cpp
    x |= (1 << 3); // 设置第 4 位为 1
    ```
  - **清除某个位**:
    ```cpp
    x &= ~(1 << 3); // 清除第 4 位
    ```
  - **翻转某个位**:
    ```cpp
    x ^= (1 << 3); // 翻转第 4 位
    ```

---

#### **3. 硬件接口**
- **中断处理**:
  - **中断的定义**:
    - 中断是硬件设备向 CPU 发出的信号，用于通知某些事件的发生。
    - 中断服务程序（ISR，Interrupt Service Routine）用于处理中断。
  - **中断处理流程**:
    1. 保存当前 CPU 状态（寄存器、程序计数器等）。
    2. 跳转到 ISR 执行中断处理逻辑。
    3. 恢复 CPU 状态并返回正常执行。
  - **注意事项**:
    - ISR 应尽量简短，避免阻塞。
    - 禁止在 ISR 中调用耗时操作（如动态内存分配）。
    - 使用 `volatile` 变量与主程序通信。
  - **示例**（伪代码）:
    ```c
    void __attribute__((interrupt)) ISR_Handler() {
        volatile int flag = 1; // 设置中断标志
    }
    ```

- **DMA（直接内存访问）**:
  - **定义**:
    - DMA 控制器允许外设直接与内存交互，而无需 CPU 参与。
  - **工作原理**:
    1. CPU 配置 DMA 控制器的源地址、目标地址和数据大小。
    2. DMA 控制器执行数据传输。
    3. 传输完成后，通过中断通知 CPU。
  - **优势**:
    - 减轻 CPU 的数据传输负担。
    - 提高系统效率。
  - **应用场景**:
    - 大量数据传输（如音视频流、网络数据包）。
    - 外设与内存之间的数据交换。

- **裸机启动流程**:
  - **定义**:
    - 裸机启动是指在没有操作系统的情况下直接启动应用程序。
  - **流程**:
    1. **硬件初始化**:
       - 配置时钟、GPIO、中断控制器等硬件资源。
    2. **堆栈与内存初始化**:
       - 设置堆栈指针。
       - 初始化全局变量和静态变量。
    3. **调用 `main` 函数**:
       - 跳转到应用程序的入口点执行。
  - **代码示例**（伪代码）:
    ```asm
    .section .reset
    Reset_Handler:
        ldr sp, =_stack_top    // 初始化堆栈
        bl  SystemInit         // 初始化硬件
        bl  main               // 调用 main 函数
        b   .                  // 死循环
    ```

---

### **补充知识**

- **嵌入式开发常见问题**:
  1. **软件与硬件同步问题**:
     - 使用锁或信号量同步多线程访问。
  2. **外设驱动开发**:
     - 了解硬件手册，准确配置寄存器。
  3. **功耗优化**:
     - 使用低功耗模式、定时唤醒等技术。

- **嵌入式调试工具**:
  - **JTAG/ SWD**: 硬件调试接口，用于单步调试和断点设置。
  - **逻辑分析仪/示波器**: 分析信号和总线数据。

---

### **总结**
1. **`volatile` 和内存屏障** 是嵌入式开发中关键的优化控制工具，用于确保数据一致性。
2. **位运算** 和 **位域** 提供高效的数据操作方式，适用于寄存器和标志位访问。
3. **中断处理、DMA 和裸机启动** 是嵌入式开发的重要硬件接口和启动流程，开发中需注意效率和稳定性。
4. 熟悉嵌入式开发工具与调试方法，有助于快速定位和解决问题。
 


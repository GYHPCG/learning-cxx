# c++学习思考
## static关键字的作用
### 修饰函数
在C++中，`static`关键字用于函数前面时，它具有两种主要的作用，具体取决于这个函数是在文件作用域（全局）还是在类作用域内定义的。

1. **文件作用域内的静态函数**：
   当`static`关键字用于一个非成员函数（即在文件作用域或全局作用域中的函数）时，它会限制该函数的可见性。这意味着该函数仅对包含它的源文件可见，而不能从其他源文件访问。这有助于防止命名冲突，尤其是在大型项目中多个源文件可能使用相同或相似的函数名的情况下。

2. **类作用域内的静态成员函数**：
   当`static`关键字用于类成员函数时，它表示这是一个静态成员函数。静态成员函数有以下特点：
   - 它们不属于任何特定的对象实例，而是属于整个类。
   - 它们可以不通过对象直接由类名调用。
   - 它们不能访问类的非静态数据成员，因为这些成员是与对象实例相关的。
   - 它们可以通过未初始化的类指针或引用调用。
   - 它们可以访问类的静态数据成员和静态成员函数。

例如，在类作用域内定义一个静态成员函数：

```cpp
class MyClass {
public:
    static void myStaticFunction() {
        // 函数体
    }
};

// 调用静态成员函数
MyClass::myStaticFunction();
```

而在文件作用域内定义一个静态函数：

```cpp
static void myStaticFunction() {
    // 函数体
}

// 在同一个源文件内调用静态函数
myStaticFunction();
```

请注意，你不能在其他源文件中直接调用`myStaticFunction()`，除非你显式地声明它为`extern`：

```cpp
extern void myStaticFunction();  // 在其他源文件中声明
```
### 修饰变量
在C++中，`static`关键字用于变量时，它可以应用于局部变量、全局变量以及类的成员变量。`static`关键字改变变量的存储期和可见性，具体影响如下：

1. **局部静态变量**：
   当`static`关键字用于局部变量时，该变量变为静态局部变量。这意味着：
   - 变量的生存期延长至整个程序运行期间，即使函数调用结束，变量也不会被销毁。
   - 变量只初始化一次，后续函数调用时保留上次函数调用结束时的值。
   - 变量的可见性仍限于定义它的函数内部。

   示例：
   ```cpp
   void func() {
       static int count = 0; // 静态局部变量
       count++;
       cout << "Count: " << count << endl;
   }
   ```

2. **全局静态变量**：
   当`static`关键字用于全局变量时，该变量变为静态全局变量。这意味着：
   - 变量的可见性仅限于定义它的源文件，不能被其他源文件访问。
   - 这有助于避免不同源文件间可能产生的命名冲突。

   示例：
   ```cpp
   static int global_count = 0; // 静态全局变量
   ```

3. **静态成员变量**：
   当`static`关键字用于类的成员变量时，该成员变量称为静态成员变量。这意味着：
   - 所有类的实例共享同一份静态成员变量，而不是每个对象都有一份拷贝。
   - 静态成员变量必须在类外部进行初始化，并且可以通过类名直接访问，无需创建对象。
   - 静态成员变量可以在静态成员函数或其他成员函数中使用。

   示例：
   ```cpp
   class MyClass {
   public:
       static int myStaticVar; // 声明静态成员变量
   };

   int MyClass::myStaticVar = 0; // 外部初始化静态成员变量
   ```

总结来说，`static`关键字可以用来控制变量的存储期（使局部变量的生存期扩展到整个程序运行期间）和可见性（限制变量的访问范围）。

### 个人错误点
这段代码中，`func`函数的`static_`变量是一个静态局部变量，意味着每次函数调用后，它的值会被保留。但是，在函数体中，`static_`被初始化为`param`的值，然后立即输出并递增。然而，初始化只会在第一次调用`func`时发生，之后的调用中`static_`的值将基于上一次调用后的值继续递增。

在你的`main`函数中，你使用了`ASSERT`来检查`func`返回的值是否符合预期。根据你的`ASSERT`语句，你期望`func`返回的值依次为6, 5, 4, 3, 2，但实际上，由于`static_`变量在每次调用`func`后保留其值并递增，因此在连续调用`func`时，返回的值应该是递增的，而不是递减的。

要修正`ASSERT`检查，你可以更改`ASSERT`的条件以匹配`static_`变量的实际行为。考虑到`static_`的初始值是5，并且每次调用都会递增，正确的`ASSERT`语句应该检查`func`是否从6开始递增。

下面是修改后的`main`函数：

```cpp
int main(int argc, char **argv) {
    ASSERT(func(5) == 6, "static variable value incorrect");
    ASSERT(func(4) == 7, "static variable value incorrect"); // 注意这里应该是7
    ASSERT(func(3) == 8, "static variable value incorrect");
    ASSERT(func(2) == 9, "static variable value incorrect");
    ASSERT(func(1) == 10, "static variable value incorrect");
    return 0;
}
```

这样修改后，`ASSERT`检查将正确反映`static_`变量的行为。但是，需要注意的是，首次传递给`func`的参数值（这里是5）实际上并没有影响后续的函数行为，因为`static_`变量在初始化后将独立于传入的参数值递增。如果你想要测试不同的初始值对`static_`的影响，你需要在每次调用`func`之前重置`static_`的值或者修改函数逻辑使其依赖于传入的参数。

## 15题 class_derive
1. 单纯的一个类的大小取决于成员变量的大小。空类的大小为1字节，为了确保类在存储时能够被正确地初始化，编译器会为类添加一个字节的填充，有继承的类的大小等于父类大小加上子类大小。
2. 虚函数表指针的大小为8字节，因为指针的大小为8字节。
```c++
#include "../exercise.h"

// READ: 派生类 <https://zh.cppreference.com/w/cpp/language/derived_class>

// 三个类型的定义在下方，它们的关系是：B 派生自 A 并包含一个 X 类型的成员。

// ↓↓↓ 这是声明
struct X;
struct A;
struct B;
// ↑↑↑ 这是声明

// ↓↓↓ 这是定义

struct X {
    int x;

    X(int x_) : x(x_) {
        std::cout << "X(" << x << ')' << std::endl;
    }
    X(X const &other) : x(other.x) {
        std::cout << "X(X const &) : x(" << x << ')' << std::endl;
    }
    ~X() {
        std::cout << "~X(" << x << ')' << std::endl;
    }
};
struct A {
    int a;

    A(int a_) : a(a_) {
        std::cout << "A(" << a << ')' << std::endl;
    }
    A(A const &other) : A(other.a) {
        std::cout << "A(A const &) : a(" << a << ')' << std::endl;
    }
    ~A() {
        std::cout << "~A(" << a << ')' << std::endl;
    }
};
struct B : public A {
    X x;

    B(int b) : A(1), x(b) {
        std::cout << "B(" << a << ", X(" << x.x << "))" << std::endl;
    }
    B(B const &other) : A(other.a), x(other.x) {
        std::cout << "B(B const &) : A(" << a << "), x(X(" << x.x << "))" << std::endl;
    }
    ~B() {
        std::cout << "~B(" << a << ", X(" << x.x << "))" << std::endl;
    }
};
int main(int argc, char **argv) {
    X x = X(1);
    A a = A(2);
    B b = B(3);

    // TODO: 补全三个类型的大小
    static_assert(sizeof(X) == 4, "There is an int in X");
    static_assert(sizeof(A) == 4, "There is an int in A");
    static_assert(sizeof(B) == 8, "B is an A with an X");

    std::cout << std::endl
              << "-------------------------" << std::endl
              << std::endl;

    // 这是不可能的，A 无法提供 B 增加的成员变量的值
    // B ba = A(4);

    // 这也是不可能的，因为 A 是 B 的一部分，就好像不可以把套娃🪆的外层放进内层里。
    A ab = B(5);// 然而这个代码可以编译和运行！
    // 动态类型转换，因为 B 是 A 的派生类，A 是 B 的基类。
    // THINK: 观察打印出的信息，推测把大象放进冰箱分几步？
    // THINK: 这样的代码是“安全”的吗？ 
    // NOTICE: 真实场景中不太可能出现这样的代码

    return 0;
}
```
对于15题的这个操作`A ab = B(5)` 这是一个动态类型转换，因为 B 是 A 的派生类，A 是 B 的基类。至于执行结果输出
```shell
A(1)
X(5)
B(1, X(5))
A(1)
A(A const &) : a(1)
~B(1, X(5))
~X(5)
~A(1)
~A(1)
~B(1, X(3))
~X(3)
~A(1)
~A(2)
~X(1)
```
对于第4，5行的A`A(1),
A(A const &) : a(1)`输出个人开始不理解，了解后发现是 **当派生类被赋值给基类时，派生类特有的成员会被“切片”掉，只保留基类的部分。**
执行 A ab = B(5); 这行代码时，以下是发生的情况：

1. 一个临时的 B 对象被创建，通过调用 B(5)。在这个过程中，A 的构造函数首先被调用，传入参数 1，所以你看到 A(1) 的输出。
2. 然后，B 的构造函数继续执行，创建 X 成员，这里传入了参数 5，所以你看到 X(5) 的输出。
3. 一旦 B 完全构造好，它的 A 部分被用来初始化 ab。但是，因为 ab 只是一个 A 类型的变量，所以实际上这里发生了所谓的“切片”，B 的 X 成员被忽略，而 A 的部分被保留。
4. 为了将 B 的 A 部分赋值给 ab，A 的拷贝构造函数被调用，这就是你看到 A(A const &) : a(1) 的输出的原因。这表示 ab 正在从 B 的 A 部分拷贝构造，而 a 的值仍然为 1。  
总结来说，A(1) 是 A 的构造函数被调用的标志，而 A(A const &) : a(1) 显示了 A 的拷贝构造函数正在使用 1 来初始化 a

### 18题
```c++
// THINK: 浮点数何时可以判断 ==？何时必须判断差值？
    ASSERT(plus(1.25f, 2.5f) == 3.75f, "Plus two float");
    ASSERT(plus(1.25, 2.5) == 3.75, "Plus two double");
    // TODO: 修改判断条件使测试通过
    ASSERT(plus(0.1, 0.2) - 0.30 <= 1e-9, "How to make this pass?");
```
对于前面两个测试，浮点数可以精确表示出来，所以可以直接使用 == 比较。但是对于第三个测试，由于浮点数的精度问题，不能直接使用 == 比较，而是需要使用差值来判断。差值小于一个给定的阈值，就可以认为两个浮点数相等。
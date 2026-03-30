# Linux 学习

## 在 Linux 中，`{}` 和 `()` 的区别

### 1. 使用 `{}` 开启进程：

- **`{}`** 用于命令分组（grouping commands），它不会开启新的进程，而是在当前的 shell 环境中顺序执行其中的命令。

- 例如：

  ```bash
  { echo "Hello"; echo "World"; }
  ```

  这个命令将依次在当前的 shell 中执行 `echo "Hello"` 和 `echo "World"`，它们会在同一个 shell 进程中执行。

- **注意**：`{}` 只是将命令组合在一起执行，并没有创建新的进程，所有命令都在同一个进程内运行。

### 2. 使用 `()` 开启进程：

- **`()`** 用于启动 **子 shell**（subshell），即将括号内的命令在一个新的子进程中执行。这样可以让命令在一个独立的进程中运行，且对当前 shell 环境的修改（如环境变量）不会影响到父 shell。

- 例如：

  ```bash
  (echo "Hello"; echo "World")
  ```

  这里，`echo "Hello"` 和 `echo "World"` 将在子 shell 中执行，且它们的执行不会影响到父 shell 的环境。

- 使用 `()` 时，命令会在子进程中执行。这个子进程会继承父进程的环境，但它的环境改变（如修改变量等）不会影响到父进程。

### 3. 对比：

- **`{}`**：在当前进程中执行多个命令，没有新进程的创建。
- **`()`**：在子进程中执行命令，新进程会创建。

### 示例：

```bash
# 使用 {}
{ echo "This is in the current process"; sleep 2; echo "This is still in the current process"; }
```

这将会在当前 shell 环境中执行 `echo` 和 `sleep` 命令，命令的执行不会创建新的进程。

```bash
# 使用 ()
(echo "This is in a subshell"; sleep 2; echo "This is still in a subshell")
```

这将会在一个新的子 shell 中执行命令。即使你在子 shell 中做了修改，也不会影响到父 shell。

### 总结：

- **`{}`** 用于命令分组，在当前进程中执行命令。
- **`()`** 用于创建子 shell，命令将在新的进程中执行。



## 在 Linux 中的`{}` 和 `&` 的组合 

### 解释：

- **`{}`** 用于命令分组，它会将多个命令放在一起，在当前进程中依次执行。
- **`&`** 将命令放到后台执行，这样命令不会阻塞当前的 shell。

### 组合 `{}` 和 `&`：

当你使用 `{}` 和 `&` 一起时，它的作用是将一组命令放入后台执行，而这些命令会在当前 shell 环境中执行。

### 示例：

```bash
{ echo "Hello"; echo "World"; } &
```

### 运行机制：

1. `{ echo "Hello"; echo "World"; }` 这部分是将 `echo "Hello"` 和 `echo "World"` 两个命令组合在一起执行。
2. **`&`** 将整个命令组放到后台执行。

这意味着：

- `echo "Hello"` 和 `echo "World"` 会在当前 shell 中执行，但不会阻塞其他操作。
- 由于命令在后台执行，后面的命令可以继续执行，不需要等待这两个 `echo` 命令完成。

### 使用场景：

这种方式适合你需要在后台执行一组命令，但不希望它们阻塞当前 shell 的时候。例如，你可能在做一些长时间运行的任务（如下载、编译、备份等），并且希望这些任务在后台执行，不影响其他操作。

### 示例：

```bash
{ sleep 10; echo "Task completed"; } &
echo "This will run immediately."
```

在这个例子中：

- `sleep 10` 会让命令休眠 10 秒。
- 然后输出 `"Task completed"`。
- 这整个过程会在后台进行。
- `"This will run immediately."` 会立即显示，不会被 `sleep 10` 命令影响。

### 总结：

- **`{}`** 用于将多个命令分组，并在当前进程中执行它们。
- **`&`** 将命令放到后台执行，避免阻塞当前 shell。
- 组合使用 `{}` 和 `&` 时，多个命令会在后台执行，且不会阻塞当前 shell 的其他操作。



## Linux 中的wait命令

在 Linux 中，`wait` 命令用于等待后台进程的完成，并返回该进程的退出状态。它通常与后台执行的进程结合使用，用来确保脚本或命令在某些任务完成后再继续执行。

### 1. 基本用法：

`wait` 命令会阻塞当前的 shell，直到指定的后台进程完成执行。它的语法如下：

```bash
wait [pid]
```

- **`pid`**：指定一个进程 ID，表示等待这个特定的进程完成。
- 如果没有指定 `pid`，`wait` 会等待所有后台进程完成。

### 2. 示例：

#### 示例 1：等待指定进程 ID 的进程完成

```bash
#!/bin/bash

# 启动一个后台进程
sleep 5 &

# 获取后台进程的 PID
pid=$!

# 使用 wait 命令等待该进程完成
wait $pid

echo "The background process has completed."
```

在这个脚本中：

- `sleep 5 &` 启动了一个后台进程，`$!` 获取到该进程的进程 ID (`pid`)。
- `wait $pid` 会阻塞脚本，直到指定的后台进程（由 `pid` 指定的进程）执行完成。

#### 示例 2：等待所有后台进程完成

```bash
#!/bin/bash

# 启动两个后台进程
sleep 3 &
sleep 5 &

# 等待所有后台进程完成
wait

echo "Both background processes have completed."
```

在这个脚本中，`wait` 不带任何参数，它会等待所有的后台进程完成。在后台执行的 `sleep 3` 和 `sleep 5` 两个进程都结束后，脚本会继续执行并输出结果。

### 3. 返回值：

`wait` 命令的返回值是被等待进程的退出状态。

- 如果没有指定 `pid`，则 `wait` 返回最后一个后台进程的退出状态。
- 如果指定了一个进程 ID，`wait` 返回该进程的退出状态。

```bash
$ wait $pid
$ echo $?
```

`$?` 显示的是上一个命令的退出状态码。在这里，`$?` 显示的是被等待进程的退出状态。

### 4. `wait` 与 `$!` 配合使用：

- **`$!`**：返回最后一个后台进程的进程 ID。
- 可以结合 `wait` 命令来等待该进程完成并获取其状态。

### 5. `wait` 和多进程的配合使用：

在同时启动多个后台进程时，可以使用 `wait` 来确保所有后台进程完成后再进行下一步操作。例如：

```bash
#!/bin/bash

# 启动多个后台进程
sleep 2 &
sleep 4 &
sleep 6 &

# 等待所有后台进程完成
wait

echo "All background processes have completed."
```

这个脚本会在所有 `sleep` 命令完成后输出消息。

### 6. 总结：

- `wait` 用于等待后台进程完成执行。
- 如果没有指定进程 ID，它会等待所有后台进程。
- 可以通过 `wait $pid` 来等待特定进程完成。
- 返回值是进程的退出状态，可以用 `$?` 查看。

通过 `wait` 命令，你可以在 shell 脚本中控制进程的顺序，确保特定任务在继续执行其他操作之前完成。



## 在 Linux 中的`(())`

### 1. 基本用法：

`(())` 用于算术运算，能够处理整数的加、减、乘、除等基本运算。表达式中的结果会直接返回。

### 示例：

```bash
#!/bin/bash

a=5
b=3

# 使用 (()) 执行算术运算
result=$((a + b))
echo "Result of a + b: $result"

result=$((a - b))
echo "Result of a - b: $result"

result=$((a * b))
echo "Result of a * b: $result"

result=$((a / b))
echo "Result of a / b: $result"
```

输出：

```
Result of a + b: 8
Result of a - b: 2
Result of a * b: 15
Result of a / b: 1
```

### 2. 特点：

- `(( ))` 是一个 **算术扩展**，并不仅仅局限于简单的运算，还能用于表达式的比较。
- 可以直接进行整数的加减乘除等运算。
- 它支持更复杂的表达式，比如：
  - **自增和自减**：`((a++))` 或 `((a--))`
  - **复合运算**：`((a += 5))`, `((a *= 3))`
- 支持 **逻辑运算**：如 `&&`、`||` 等。

### 3. 赋值与自增自减：

```bash
#!/bin/bash

a=5
b=3

# 复合赋值运算
((a += 2))
echo "a after a += 2: $a"  # a = 5 + 2 = 7

# 自增运算
((a++))
echo "a after a++: $a"  # a = 7 + 1 = 8

# 自减运算
((a--))
echo "a after a--: $a"  # a = 8 - 1 = 7
```

### 4. 条件判断（支持整数比较）：

`(( ))` 也可以用于 **整数的条件判断**。通过返回值来判断条件是否成立。

```bash
#!/bin/bash

a=5
b=3

if ((a > b)); then
    echo "a is greater than b"
else
    echo "a is not greater than b"
fi
```

输出：

```
a is greater than b
```

### 5. 注意事项：

- `(( ))` 只支持 **整数** 运算，不能用于浮点数运算。如果需要进行浮点数运算，可以使用 `bc` 或者 `awk`。
- 在 `(( ))` 中，运算符周围的空格是 **不需要的**，它可以直接写成 `((a+b))` 或者 `((a * b))`。

### 总结：

- **`(())`** 用于在 Shell 中执行 **整数运算**，包括加减乘除、比较、赋值等。
- 支持 **复合赋值**、**自增自减**、**条件判断**。
- 适用于简单的 **整数算术运算**，但对于浮点数或更复杂的数学计算，可能需要使用其他工具（如 `bc`）。

`(())` 是 Shell 中强大且高效的算术计算工具，使得我们可以在脚本中进行更复杂的数学操作。



## Linux for循环写法

### 1. C 风格的 `for` 循环

```bash
for ((i = 0; i < 5; i++)); do
  echo "$i"
done
```

### 2.  一般写法

```bash
for item in a b c; do
  echo "$item"
done
```

在 Linux 的 Bash 脚本中，进行算术运算是常见的需求。Bash 提供了多种方式来执行整数运算。以下是常用的几种方法及其示例：

------

## Linux 中的算数运算

### 1. 算术扩展（Arithmetic Expansion）

这是 Bash 中推荐的算术运算方式，语法简洁，支持常见的数学运算。

### 示例：

```bash
#!/bin/bash

a=10
b=3

echo $((a + b))  # 输出：13
echo $((a - b))  # 输出：7
echo $((a * b))  # 输出：30
echo $((a / b))  # 输出：3
echo $((a % b))  # 输出：1
echo $((a ** b)) # 输出：1000
```



在此示例中，`$((...))` 用于执行算术运算，支持加、减、乘、除、取余和指数运算。

------

### 2. `let` 命令

`let` 是 Bash 的内建命令，用于执行算术运算。

### 示例：

```bash
#!/bin/bash

x=10
y=3

let "z = x * y"
echo $z  # 输出：30

let z=x/y
echo $z  # 输出：3
```



注意，`let` 命令不需要 `$` 来引用变量，且支持增量（`++`）和减量（`--`）操作。

------

### 3. `expr` 命令

`expr` 是一个外部命令，用于计算表达式的值。需要注意，运算符两边必须有空格，且乘法运算符 `*` 需要转义。

### 示例：

```bash
#!/bin/bash

a=10
b=3

sum=$(expr $a + $b)
echo $sum  # 输出：13

diff=$(expr $a - $b)
echo $diff  # 输出：7

prod=$(expr $a \* $b)
echo $prod  # 输出：30

quot=$(expr $a / $b)
echo $quot  # 输出：3

mod=$(expr $a % $b)
echo $mod  # 输出：1

exp=$(expr $a \*\* $b)
echo $exp  # 输出：1000
```



`expr` 命令适用于简单的算术运算，但在处理复杂表达式时可能不如其他方法方便。([learning-ocean.com](https://learning-ocean.com/tutorials/shellscript/shellscript-arithmetic-operations/?utm_source=chatgpt.com))

------

### 4. `bc` 命令（支持浮点运算）

`bc` 是一个功能强大的计算器工具，支持浮点运算和更复杂的数学函数。

### 示例：

```bash
#!/bin/bash

result=$(echo "scale=2; 5 / 3" | bc)
echo $result  # 输出：1.66

result=$(echo "scale=2; 5 * 3.5" | bc)
echo $result  # 输出：17.50

result=$(echo "scale=2; 2^3" | bc)
echo $result  # 输出：8

result=$(echo "scale=2; sqrt(16)" | bc)
echo $result  # 输出：4.00
```



使用 `scale=2` 设置小数点后保留两位。

------

### 5. `awk` 命令（适用于文本处理中的计算）

`awk` 是一个强大的文本处理工具，也支持算术运算。

### 示例：

```bash
#!/bin/bash

result=$(awk "BEGIN {print 5 / 3}")
echo $result  # 输出：1.66666666666667

result=$(awk "BEGIN {print 5 * 3.5}")
echo $result  # 输出：17.5

result=$(awk "BEGIN {print 2^3}")
echo $result  # 输出：8

result=$(awk "BEGIN {print sqrt(16)}")
echo $result  # 输出：4
```



`awk` 适用于处理文本数据时进行计算。

------

### 6. 使用 `declare` 声明整数变量

`declare -i` 用于声明整数类型的变量，赋值时会自动进行算术运算。([gnu.org](https://www.gnu.org/s/bash/manual/html_node/Shell-Arithmetic.html?utm_source=chatgpt.com))

### 示例：

```bash
#!/bin/bash

declare -i x=10
declare -i y=3

z=$((x + y))
echo $z  # 输出：13

z=$((x - y))
echo $z  # 输出：7

z=$((x * y))
echo $z  # 输出：30

z=$((x / y))
echo $z  # 输出：3

z=$((x % y))
echo $z  # 输出：1

z=$((x ** y))
echo $z  # 输出：1000
```



使用 `declare -i` 可以确保变量仅为整数类型，并自动进行算术运算。([gnu.org](https://www.gnu.org/s/bash/manual/html_node/Shell-Arithmetic.html?utm_source=chatgpt.com))

------

### 总结

| 方法         | 支持浮点数 | 支持运算符        | 示例用途           |
| ------------ | ---------- | ----------------- | ------------------ |
| `$((...))`   | 否         | + - * / % **      | 简单整数运算       |
| `let`        | 否         | + - * / % ++ --   | 简洁的算术运算     |
| `expr`       | 否         | + - * / %         | 兼容性需求         |
| `bc`         | 是         | + - * / % ** sqrt | 高精度浮点运算     |
| `awk`        | 是         | + - * / % ** sqrt | 文本处理中的计算   |
| `declare -i` | 否         | + - * / % **      | 强制整数类型的变量 |



## Linux 中的 until

在 Linux 的 Bash 脚本中，`until` 循环是一种控制结构，用于在指定条件为 **假** 时重复执行一段代码块。与 `while` 循环相反，`while` 循环在条件为真时执行，而 `until` 循环在条件为假时执行。这种结构特别适用于等待某个条件成立之前执行任务的场景。([labex.io](https://labex.io/tutorials/shell-how-to-use-the-bash-until-loop-for-automation-413770?utm_source=chatgpt.com))

------

### 📌 基本语法

```bash
until [ 条件 ]; do
  # 循环体
done
```



在每次迭代之前，`until` 会检查条件。如果条件为假（即返回非零退出状态），则执行循环体；如果条件为真（即返回零退出状态），则退出循环。

------

### ✅ 示例：计数器

```bash
#!/bin/bash

counter=1
until [ $counter -gt 5 ]; do
  echo "计数：$counter"
  ((counter++))
done
```



输出：

```
计数：1
计数：2
计数：3
计数：4
计数：5
```



在这个示例中，`counter` 从 1 开始，每次循环递增，直到其值大于 5 时退出循环。

------

### 🕒 示例：等待文件出现

```bash
#!/bin/bash

file="/path/to/file"
until [ -f "$file" ]; do
  echo "等待文件 $file 出现..."
  sleep 1
done
echo "文件 $file 已出现，继续执行..."
```



此脚本会每秒检查一次指定路径下的文件是否存在，直到文件出现为止。([labex.io](https://labex.io/tutorials/shell-how-to-use-the-bash-until-loop-for-automation-413770?utm_source=chatgpt.com))

------

### 🔁 示例：无限循环

```bash
#!/bin/bash

until false; do
  echo "这是一个无限循环"
  sleep 1
done
```



由于条件始终为假，循环将无限执行，直到手动中断（如按 `Ctrl+C`）。([rtfm.co.ua](https://rtfm.co.ua/en/bash-using-loops-for-while-until-with-examples/?utm_source=chatgpt.com))

------

### 🧩 示例：结合 `break` 和 `continue`

```bash
#!/bin/bash

count=1
until [ $count -gt 10 ]; do
  if [ $count -eq 5 ]; then
    ((count++))
    continue
  fi
  echo "计数：$count"
  if [ $count -eq 8 ]; then
    break
  fi
  ((count++))
done
```



在这个示例中，循环从 1 开始，跳过计数为 5 的迭代，并在计数达到 8 时退出循环。([phoenixnap.com](https://phoenixnap.com/kb/bash-loop-until?utm_source=chatgpt.com))

------

### 🧠 使用场景

- **等待某个条件成立**：如等待文件生成、服务启动或网络连接建立。
- **重试机制**：在操作失败时，重复尝试直到成功。
- **用户输入验证**：提示用户输入有效数据，直到满足要求。

------

### ⚠️ 注意事项

- `until` 循环在条件为假时执行，因此在设置条件时需要特别小心。
- 在某些情况下，可能需要使用 `break` 或 `continue` 来控制循环的执行。
- 确保循环条件最终会变为真，否则可能导致无限循环。([stackoverflow.com](https://stackoverflow.com/questions/8287757/difference-between-while-and-until-in-bash?utm_source=chatgpt.com))

------

通过合理使用 `until` 循环，可以有效地控制脚本的执行流程，处理各种需要等待条件成立的场景。

## Linux 中的continue 

```bash
#!/bin/bash

for i in {1..3}; do  # 2. 外层循环
  for j in {1..3}; do  # 1. 中层循环
    if [ "$i" -eq "$j" ]; then
      echo "跳过外层循环: $i = $j"
      continue 2  # 跳过外层循环的本次迭代
    fi
    echo "$i != $j"
  done
done
```

## Linux 中的 case 分支语句

在 Linux 的 Bash 脚本中，`case` 语句用于根据变量的值匹配不同的模式，并执行相应的命令。它类似于其他编程语言中的 `switch` 语句，适用于处理多个条件判断，使代码更加简洁和可读。

------

### 📌 基本语法

```bash
case $variable in
  pattern1)
    commands;;
  pattern2)
    commands;;
  *)
    default_commands;;
esac
```



- **`$variable`**：要进行匹配的变量。
- **`pattern1`, `pattern2`, ...**：用于匹配变量值的模式。
- **`commands`**：当模式匹配成功时执行的命令。
- **`\*`**：默认模式，匹配所有未被前面模式匹配的情况。
- **`;;`**：结束当前模式的命令块。
- **`esac`**：结束 `case` 语句（`case` 的反写）。

------

### ✅ 示例：文件类型识别

```bash
#!/bin/bash
for file in *; do
  case $file in
    *.txt)
      echo "$file 是文本文件"
      ;;
    *.sh)
      echo "$file 是脚本文件"
      ;;
    *.jpg | *.png)
      echo "$file 是图片文件"
      ;;
    *)
      echo "$file 是其他类型的文件"
      ;;
  esac
done
```



该脚本遍历当前目录中的所有文件，根据文件扩展名输出文件类型。

------

### 🧠 使用建议

- 当需要对同一个变量进行多个值的匹配时，使用 `case` 语句比多个 `if` 语句更简洁。
- 使用 `|` 分隔多个模式，可以让多个值共享相同的命令块。
- 在最后使用 `*` 作为默认模式，处理所有未被前面模式匹配的情况。

------

## Linux HereDoc 区别

### 📌 `cat << EOF` 的行为

```bash
cat << EOF
  Hello, World!
EOF
```



- **功能**：将 `<< EOF` 和 `EOF` 之间的文本传递给 `cat` 命令，`cat` 会将其输出到标准输出（通常是终端）。
- **缩进处理**：不会自动去除文本前的空格或制表符。
- **适用场景**：适用于需要保留文本缩进的情况。([zh.wikipedia.org](https://zh.wikipedia.org/wiki/Here文档?utm_source=chatgpt.com))

------

### 📌 `cat <<- EOF` 的行为

```bash
cat <<- EOF
  Hello, World!
EOF
```



- **功能**：与 `cat << EOF` 相同，将 `<<- EOF` 和 `EOF` 之间的文本传递给 `cat` 命令。
- **缩进处理**：会自动去除文本前的所有制表符（Tab）。
- **适用场景**：适用于脚本中需要缩进 Here 文档内容，但又不希望这些缩进出现在输出中的情况。([zh.wikipedia.org](https://zh.wikipedia.org/wiki/Here文档?utm_source=chatgpt.com))

------

### ✅ 示例对比

```bash
#!/bin/bash

echo "使用 << EOF："
cat << EOF
    这是第一行
    这是第二行
EOF

echo -e "\n使用 <<- EOF："
cat <<- EOF
    这是第一行
    这是第二行
EOF
```



**输出：**

```bash
使用 << EOF：
    这是第一行
    这是第二行

使用 <<- EOF：
这是第一行
这是第二行
```



在上述示例中，使用 `<< EOF` 时，文本前的空格被保留；而使用 `<<- EOF` 时，文本前的制表符被自动去除。

------

### 🧠 小结

- **`<< EOF`**：适用于需要保留文本缩进的情况。
- **`<<- EOF`**：适用于脚本中需要缩进 Here 文档内容，但又不希望这些缩进出现在输出中的情况。([zh.wikipedia.org](https://zh.wikipedia.org/wiki/Here文档?utm_source=chatgpt.com), [kodekloud.com](https://kodekloud.com/blog/eof-bash/?utm_source=chatgpt.com))

需要注意的是，`<<-` 只会去除制表符（Tab），而不会去除空格。如果需要去除空格。



## Linux trap命令

`trap` 命令用于捕捉信号并在接收到信号时执行指定的命令。它是 Unix 系统中用于处理异步事件的一种常用机制。例如，当程序接收到某个信号时，你可以让它执行清理操作或其他预定义的任务。

### 基本语法

```bash
trap COMMAND SIGNALS
```

- `COMMAND`：当信号发生时要执行的命令。
- `SIGNALS`：一个或多个信号类型，可以是信号的名字（如 `SIGINT`）或信号的编号（如 `2`）。

### 常见信号

- `SIGINT`（2）：中断信号，通常由按 `Ctrl+C` 发送。
- `SIGTERM`（15）：终止信号，通常由 `kill` 命令发送。
- `SIGKILL`（9）：强制终止信号，无法捕捉或处理。
- `SIGQUIT`（3）：退出信号，通常由 `Ctrl+\` 发送。
- `SIGUSR1` 和 `SIGUSR2`：用户定义的信号。
- `SIGEXIT`：程序退出时的信号。

### 示例

1. **捕捉 `SIGINT`（Ctrl+C）信号**：
    如果你想捕捉 `Ctrl+C` 信号并执行自定义命令，可以这样做：

   ```bash
   trap 'echo "捕获到 SIGINT，执行清理操作..."' SIGINT
   ```

2. **捕捉 `SIGTERM` 信号**：
    如果你希望捕捉到进程被终止时执行清理操作：

   ```bash
   trap 'echo "捕获到 SIGTERM，清理资源..."' SIGTERM
   ```

3. **捕捉多个信号**：
    你可以同时捕捉多个信号并执行相同的命令：

   ```bash
   trap 'echo "捕获到终止信号或中断信号..."' SIGINT SIGTERM
   ```

4. **捕捉信号并执行多个命令**：
    你可以在 `trap` 后面执行多个命令：

   ```bash
   trap 'echo "清理任务开始..."; rm -f temp_file; echo "清理任务完成."' SIGINT
   ```

5. **捕捉信号并退出脚本**：
    可以使用 `exit` 来在捕捉到信号时退出脚本：

   ```bash
   trap 'echo "捕获到信号，退出脚本..."; exit 1' SIGTERM
   ```

6. **忽略信号**：
    如果你希望忽略某个信号，可以使用 `-` 来删除默认的信号处理方式：

   ```bash
   trap '' SIGINT
   ```

### 示例：捕捉退出信号

下面是一个简单的脚本，它捕捉脚本退出时的 `EXIT` 信号并执行清理工作：

```bash
#!/bin/bash

# 捕捉退出信号（EXIT）
trap 'echo "脚本正在退出，执行清理任务..."' EXIT

# 模拟一个长时间运行的任务
echo "脚本开始执行..."
sleep 10
echo "脚本执行完毕"
```

在脚本结束时，无论是正常退出还是收到信号，都会触发 `EXIT` 信号，并执行清理命令。

### 信号处理的实际应用

- **捕获中断信号来保存数据**：例如，在程序中，如果用户按下 `Ctrl+C`，可以捕捉到 `SIGINT` 信号并保存工作数据。
- **优雅退出**：捕捉 `SIGTERM` 信号，优雅地退出程序，释放资源，保存状态。
- **调试脚本**：捕捉不同的信号来调试脚本的行为，查看脚本在特定条件下的表现。

### 结语

`trap` 是处理信号的强大工具，可以帮助你编写更健壮的脚本，优雅地处理各种意外中断，确保资源被正确释放。

## Linux 中的 install 命令

在 Linux 中，`install` 命令用于复制文件并设置文件的权限，通常用于安装程序、脚本或其他文件。`install` 命令不仅能够复制文件，还可以设置目标文件的权限和拥有者。

### 基本语法

```bash
install [OPTION]... SOURCE... DIRECTORY
```

- `SOURCE`：源文件（一个或多个）。
- `DIRECTORY`：目标目录，`SOURCE` 文件会被复制到这个目录。
- `OPTION`：`install` 命令支持许多选项来控制行为。

### 常见选项

- `-d`：创建目录而非复制文件。可以用来创建目录结构。
- `-m`：设置目标文件的权限模式。
- `-o`：设置目标文件的用户所有者。
- `-g`：设置目标文件的组所有者。
- `-t`：指定目标目录，而不是最后一个参数。
- `-v`：显示详细的操作过程（verbose）。
- `-b`：如果目标文件已经存在，创建一个备份。
- `-p`：保留文件的修改时间和访问时间。

### 常见用法

#### 1. 将文件复制到目标目录

```bash
install myfile.txt /usr/local/bin/
```

这会将 `myfile.txt` 复制到 `/usr/local/bin/` 目录。

#### 2. 设置文件权限

你可以使用 `-m` 选项来设置目标文件的权限：

```bash
install -m 755 myscript.sh /usr/local/bin/
```

这将把 `myscript.sh` 复制到 `/usr/local/bin/` 目录，并设置文件权限为 `755`（可执行）。

#### 3. 设置文件的用户和组所有者

你可以使用 `-o` 和 `-g` 选项来设置目标文件的所有者和组：

```bash
install -o root -g root myfile.txt /usr/local/bin/
```

这会将 `myfile.txt` 复制到 `/usr/local/bin/`，并将文件的所有者和组设置为 `root`。

#### 4. 创建目录结构

你可以使用 `-d` 选项来创建目录而不是复制文件：

```bash
install -d /path/to/newdir
```

这将创建目录 `/path/to/newdir`，如果父目录不存在，它也会创建父目录。

#### 5. 复制并保留时间戳

如果你想在复制文件时保留文件的时间戳，可以使用 `-p` 选项：

```bash
install -p myfile.txt /usr/local/bin/
```

这将保留 `myfile.txt` 的修改时间和访问时间。

#### 6. 批量复制多个文件

你可以使用 `install` 同时复制多个文件：

```bash
install file1.txt file2.txt /usr/local/bin/
```

这会将 `file1.txt` 和 `file2.txt` 复制到 `/usr/local/bin/` 目录。

#### 7. 创建备份

如果目标文件已经存在，可以使用 `-b` 选项来创建备份：

```bash
install -b myfile.txt /usr/local/bin/
```

如果 `/usr/local/bin/myfile.txt` 已经存在，`install` 将创建一个备份文件，如 `myfile.txt~`。

### 示例

1. **将文件复制到目录，并设置权限**：

   ```bash
   install -m 644 README.md /usr/local/share/
   ```

   这将 `README.md` 复制到 `/usr/local/share/` 目录，并将文件权限设置为 `644`（只读）。

2. **创建目录并复制文件**：

   ```bash
   install -d /usr/local/myapp
   install myapp /usr/local/myapp/
   ```

   这将创建目录 `/usr/local/myapp` 并将 `myapp` 文件复制到该目录。

3. **复制文件并设置所有者和权限**：

   ```bash
   install -o john -g admin -m 755 script.sh /usr/local/bin/
   ```

   这将 `script.sh` 复制到 `/usr/local/bin/`，并将文件的所有者设置为 `john`，组设置为 `admin`，权限设置为 `755`（可执行）。

### 总结

`install` 命令非常有用，特别是在安装软件或脚本时，可以轻松地将文件复制到指定位置，并同时设置文件的权限、所有者、组等属性。它相比于 `cp` 命令更加灵活，可以自动创建目录、设置权限等，使得文件管理更加方便。

## LInux 中的 awk

------

### 一、基本语法结构

```bash
awk [options] 'pattern {action}' file
```

- `pattern`：匹配模式（可选）。
- `action`：对匹配行执行的动作（可选）。
- 若省略`pattern`则对所有行生效。
- 若省略`action`则默认输出匹配行。

**示例**：

```bash
awk '/error/{print}' file
awk '{print $2}' file
awk 'NR==10' file
```

------

### 二、内置变量（Built-in Variables）

| 变量       | 描述                     |
| ---------- | ------------------------ |
| `$0`       | 当前整行内容             |
| `$n`       | 当前行第n个字段          |
| `NF`       | 当前行字段个数           |
| `NR`       | 当前处理的行号           |
| `FNR`      | 当前文件内的行号         |
| `FS`       | 字段分隔符，默认空格     |
| `OFS`      | 输出字段分隔符，默认空格 |
| `RS`       | 输入记录分隔符，默认换行 |
| `ORS`      | 输出记录分隔符，默认换行 |
| `FILENAME` | 当前文件名               |
| `ARGC`     | 命令行参数总数           |
| `ARGV`     | 命令行参数数组           |

**示例**：

```bash
awk -F':' '{print NF}' /etc/passwd
awk '{print NR,$0}' file.txt
```

------

### 三、模式匹配（Pattern Matching）

#### 3.1 正则表达式匹配

- `/regex/` 匹配正则表达式
- `! /regex/` 取反匹配

```bash
awk '/^root/' /etc/passwd
awk '!/^root/' /etc/passwd
```

#### 3.2 数值和表达式匹配

- 比较运算：`<` `<=` `>` `>=` `==` `!=`
- 逻辑运算：`&&`（与） `||`（或） `!`（非）

```bash
awk '$3>100 && $3<500' file
```

#### 3.3 范围匹配

- 从匹配到不匹配的区间：

```bash
awk '/start/,/end/' file
awk 'NR==10,NR==20' file
```

------

### 四、动作（Action）语法

#### 4.1 条件判断（if-else）

```bash
awk '{if($1>0) print "正"; else print "负或零"}' file
```

#### 4.2 循环语句

**for循环**

```bash
awk '{for(i=1;i<=NF;i++) print $i}' file
```

**while循环**

```bash
awk '{i=1;while(i<=NF){print $i;i++}}' file
```

**do-while循环**

```bash
awk '{i=1; do{print $i;i++}while(i<=NF)}' file
```

#### 4.3 控制语句

- `next`：跳过当前行
- `exit`：终止awk执行

```bash
awk '{if(NR==5) next; print}' file
awk '{if($1=="end") exit; print}' file
```

------

### 五、函数（Functions）

#### 5.1 字符串函数

| 函数                     | 说明               |
| ------------------------ | ------------------ |
| `length(str)`            | 字符串长度         |
| `substr(str,pos,len)`    | 提取子串           |
| `index(str,substr)`      | 子串首次出现的位置 |
| `match(str,regex)`       | 正则匹配           |
| `split(str,array,sep)`   | 拆分字符串到数组   |
| `tolower(str)`           | 转小写             |
| `toupper(str)`           | 转大写             |
| `gsub(regex,rep,str)`    | 替换所有匹配       |
| `sub(regex,rep,str)`     | 替换首次匹配       |
| `sprintf(format,exp...)` | 格式化字符串       |

**示例**：

```bash
awk '{print length($0)}' file
awk '{print substr($0,1,3)}' file
awk '{gsub(/a/,"A");print}' file
```

#### 5.2 数学函数

| 函数             | 说明              |
| ---------------- | ----------------- |
| `int(x)`         | 向下取整          |
| `sqrt(x)`        | 平方根            |
| `rand()`         | 生成随机数（0~1） |
| `sin(x), cos(x)` | 正弦、余弦        |
| `exp(x), log(x)` | 指数、对数        |

**示例**：

```bash
awk '{print sqrt($1)}' file
awk 'BEGIN{srand(); print rand()}'
```

#### 5.3 时间函数

| 函数                      | 说明       |
| ------------------------- | ---------- |
| `systime()`               | 返回时间戳 |
| `strftime(fmt,timestamp)` | 格式化时间 |

```bash
awk 'BEGIN{print strftime("%Y-%m-%d %H:%M:%S",systime())}'
```

------

### 六、数组（Array）用法

```bash
awk '{a[$1]++}END{for(i in a) print i,a[i]}' file
```

- 删除元素：`delete a[i]`
- 判断是否存在：`if(i in a)`

------

### 七、BEGIN和END规则

- `BEGIN{}`：awk执行前运行一次
- `END{}`：awk执行完成后运行一次

```bash
awk 'BEGIN{print "开始"} {print $0} END{print "结束"}' file
```

------

### 八、自定义函数（User-defined Functions）

```awk
awk '
function add(a,b){
    return a+b
}
{print add($1,$2)}' file
```

------

### 九、命令行常用选项（Options）

| 选项 | 含义                  |
| ---- | --------------------- |
| `-F` | 指定字段分隔符        |
| `-v` | 设置变量              |
| `-f` | 从脚本文件读取awk代码 |

```bash
awk -F',' '{print $1}' file
awk -v name="Tom" '{print name,$1}' file
awk -f script.awk file
```

------

### 十、进阶示例

- **多文件处理**：

```bash
awk '{print FILENAME, FNR, $0}' file1 file2
```

- **模拟grep -v**：

```bash
awk '!/pattern/' file
```

- **去重统计**：

```bash
awk '{count[$1]++} END {for(i in count) print i, count[i]}' file
```

- **统计文件大小总和**：

```bash
ls -l | awk '{sum+=$5} END {print sum}'
```

- **打印文件指定范围行**：

```bash
awk 'NR>=10 && NR<=20' file
```

------

 Linux 中 `rsync` 命令

------

## Linux 中的 rsync 命令

### 一、命令简介

`rsync` 是远程文件和目录同步工具，常用于备份、镜像和数据迁移，支持增量同步，具有高效、快速、安全等特点。

**语法结构：**

```bash
rsync [选项] 源路径 目标路径
```

------

### 二、常用选项说明

| 选项         | 含义                           |
| ------------ | ------------------------------ |
| `-a`         | 归档模式，等同于`-rlptgoD`     |
| `-v`         | 显示详细信息                   |
| `-z`         | 传输时压缩数据                 |
| `-r`         | 递归模式（包含子目录）         |
| `-l`         | 同步符号链接                   |
| `-p`         | 保持文件权限                   |
| `-t`         | 保持文件时间戳                 |
| `-g`         | 保持文件所属组                 |
| `-o`         | 保持文件所属用户               |
| `-H`         | 保持硬链接                     |
| `--progress` | 显示同步进度                   |
| `--delete`   | 删除目标路径中源中不存在的文件 |
| `-e`         | 指定传输使用的协议，如`ssh`    |
| `--exclude`  | 排除指定文件或目录             |
| `--include`  | 包含指定文件或目录             |
| `--bwlimit`  | 限制传输带宽（KB/s）           |

------

### 三、常用示例（本地同步）

#### 3.1 本地目录同步

```bash
rsync -av /src/dir/ /dest/dir/
```

- `/src/dir/`中所有文件同步到`/dest/dir/`下。

#### 3.2 保持目录结构

- 注意斜线的差异：

```bash
rsync -av /src/dir /dest/
```

- 同步后生成`/dest/dir`。

------

### 四、远程主机同步

#### 4.1 本地目录→远程主机

```bash
rsync -avz /local/path/ user@remote_host:/remote/path/
```

- `-z`表示压缩数据传输，更快更节省带宽。

#### 4.2 远程主机→本地目录

```bash
rsync -avz user@remote_host:/remote/path/ /local/path/
```

------

### 五、增量同步

- 只同步差异内容，极大提高效率：

```bash
rsync -avz --progress /src/dir/ /dest/dir/
```

------

### 六、删除目标多余文件

- 若目标目录有额外文件，使用`--delete`删除：

```bash
rsync -avz --delete /src/dir/ /dest/dir/
```

------

### 七、排除与包含文件

#### 排除指定文件或目录：

```bash
rsync -avz --exclude "*.log" /src/dir/ /dest/dir/
```

#### 排除多个文件或目录：

```bash
rsync -avz --exclude-from 'exclude.txt' /src/dir/ /dest/dir/
```

- `exclude.txt`示例：

```
*.log
temp/
cache/
```

#### 指定包含文件或目录（exclude配合include）：

```bash
rsync -avz --include 'dir1/***' --exclude '*' /src/ /dest/
```

------

### 八、限制带宽

- 限制传输带宽为5000KB/s：

```bash
rsync -avz --bwlimit=5000 /src/dir/ user@host:/dest/
```

------

### 九、指定SSH端口

```bash
rsync -avz -e 'ssh -p 2222' /src/dir/ user@host:/dest/
```

------

### 十、其他高级用法

#### 10.1 干运行（测试不实际传输）：

```bash
rsync -avz --dry-run /src/dir/ /dest/dir/
```

#### 10.2 同步符号链接：

- 同步符号链接本身：

```bash
rsync -avzl /src/dir/ /dest/dir/
```

- 同步符号链接指向的文件：

```bash
rsync -avzL /src/dir/ /dest/dir/
```

------

### 十一、常见使用场景总结

#### 11.1 本地备份：

```bash
rsync -av --delete /home/user/ /backup/home_user/
```

#### 11.2 远程备份（增量同步）：

```bash
rsync -avz --progress user@remote_host:/var/www/ /backup/www/
```

#### 11.3 网站迁移：

```bash
rsync -avz --delete /var/www/html/ user@new_host:/var/www/html/
```

------

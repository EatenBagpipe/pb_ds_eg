### 引言

pb_ds（全称Policy-Based Data Structures，俗称平板电视）是G++编译器默认附带的一个扩展库，封装了许多数据结构,如HashTable、trie、rb_tree、priority_queue等等。本次推送将以堆优化的Dijkstra算法为例，为大家介（an）绍（li）pb_ds库，其中将重点介绍pb_ds库中的优先队列及其复杂度分析，并与STL中的优先队列进行对比。

在求解单源最短路径的Dijkstra算法中，我们注意到，在更新最短路径树到不在树上的点的距离时，O(n²)的算法是选择枚举所有的边从而得到最小值并进行更新。由于这一过程相当于选取一个集合中的最小值，所以我们考虑使用堆对这一过程进行优化。

在后文中，我们约定m表示无向图中边集的大小，n表示点集的大小，log(a)表示以2为底a的对数。



### std::priority_queue

很多同学都已经发现，c++的标准模板库已经为我们准备了优先队列这一容器，而它在底层正是用堆实现的。但注意到，在很多时候，优先队列的队首元素所对应的点都已经在最短路径树上了，所以需要进行大量的pop操作。通过分析可知，其时间复杂度为O(mlog(m))，优先队列空间复杂度为O(m)。同时，手写堆优化Dijkstra的时间复杂度是O(mlog(n))，堆的空间复杂度为O(n)。所以，在稠密图中，使用std::priority_queue是劣于手写堆的。

那么现在问题来了，如何在保持std::priority_queue优秀的代码复杂度的同时，获得和手写堆一样的各项复杂度呢？这个时候就需要pb_ds出场辣。



### __gnu_pbds::priority_queue

```
template<
    typename Value_Type,
    typename Cmp_Fn = std::less<Value_Type>,
    typename Tag = pairing_heap_tag,
    typename Allocator = std::allocator<char> >
class priority_queue;
```

pb_ds中优先队列的声明如上。其中，Value_Type指优先队列中存放元素的类型，Cmp_Fn为元素的比较方法（默认调用std::less），Tag指实现时用的堆的类型，Allocator指内存分配的方法。

__gnu_pbds::priority_queue提供了如下几种堆可供选择：

pairing_heap_tag：配对堆

binary_heap_tag：二叉堆

binomial_heap_tag：二项堆

rc_binomial_heap_tag：冗余计数二项堆（网上并没有找到比较大众的译名）

thin_heap_tag：优化过的斐波那契堆

__gnu_pbds::priority_queue提供的接口与std::priority_queue类似，但它还提供了很多更加强大的功能，例如：

modify(point_iterator it,const_reference r_new_val)：修改某个迭代器所指向的点的值

join(priority_queue &other)：合并两个优先队列~~（妈妈再也不用担心我不会写可并堆辣）~~



### 复杂度对比

在队列大小为n时，各种优先队列的各种操作复杂度如下：

|                      | push                     | pop                      | modify                   | erase                    | join       |
| -------------------- | ------------------------ | ------------------------ | ------------------------ | ------------------------ | ---------- |
| std::priority_queue  | 最坏Θ(n) ，均摊Θ(log(n)) | 最坏Θ(log(n))            | 最坏Θ(nlog(n))           | Θ(nlog(n))               | Θ(nlog(n)) |
| pairing_heap_tag     | O(1)                     | 最坏Θ(n) ，均摊Θ(log(n)) | 最坏Θ(n) ，均摊Θ(log(n)) | 最坏Θ(n) ，均摊Θ(log(n)) | O(1)       |
| binary_heap_tag      | 最坏Θ(n) ，均摊Θ(log(n)) | 最坏Θ(n) ，均摊Θ(log(n)) | Θ(n)                     | Θ(n)                     | Θ(n)       |
| binomial_heap_tag    | 最坏Θ(n) ，均摊O(1)      | Θ(log(n))                | Θ(log(n))                | Θ(log(n))                | Θ(log(n))  |
| rc_binomial_heap_tag | O(1)                     | Θ(log(n))                | Θ(log(n))                | Θ(log(n))                | Θ(log(n))  |
| thin_heap_tag        | O(1)                     | 最坏Θ(n) ，均摊Θ(log(n)) | 最坏Θ(log(n)) ，均摊O(1) | 最坏Θ(n) ，均摊Θ(log(n)) | Θ(n)       |

可见，pb_ds中的优先队列更加优秀。

### 小结

除了文中所提到的一些操作外，pb_ds库还有很多强大的功能，感兴趣的同学可以移步[官方文档](https://gcc.gnu.org/onlinedocs/libstdc++/ext/pb_ds/)进行更深入的了解。文中提到的优化代码也可以在[我的Github仓库](https://github.com/EatenBagpipe/pb_ds_eg)中下载/查看。
 C++ 原子操作中用于控制内存顺序（Memory Order） 的标识符


要理解这些指令，首先要明白现代计算机为了追求性能，允许编译器和CPU在不改变单线程执行结果的前提下，对指令进行重排（Reordering）

memory_order_relaxed (宽松顺序)

    核心语义：只保证原子性，不提供任何跨线程的同步或顺序保证。编译器和CPU可以随意重排该操作前后的其他内存访问

memory_order_consume (消费顺序)

    核心语义：一种比 acquire 更弱、更精细的定序。一个带有此标记的加载（load）操作，会阻止当前线程中依赖于该加载结果的后续读写操作被重排到该加载之前。


memory_order_acquire (获得顺序)

    核心语义：通常用于加载（load）操作。它像一个“屏障”，禁止当前线程中任何后续的读写操作被重排到此加载之前。同时，它能“看到”所有释放（release） 了同一个原子变量的线程在释放操作之前所做的所有写入


memory_order_release (释放顺序)

    核心语义：通常用于存储（store）操作。它也是一个“屏障”，禁止当前线程中任何在此存储之前的读写操作被重排到此存储之后。同时，它确保当前线程在此存储之前的所有写入，对于后续获取（acquire） 了同一个原子变量的线程是可见的。


memory_order_acq_rel (获得-释放顺序)

    核心语义：同时具备 acquire 和 release 的语义，通常用于读-修改-写（Read-Modify-Write, RMW） 操作（如 fetch_add, exchange）。它既禁止前面的操作重排到它之后，也禁止后面的操作重排到它之前。


memory_order_seq_cst (顺序一致顺序)

    核心语义：这是最强的约束，也是所有原子操作的默认值。它除了包含 acquire/release 的语义外，还保证所有线程以完全相同的顺序观察到所有 seq_cst 原子操作，形成一个单一的全局总顺序。



memory_order_acquire 和 memory_order_release 的配对使用至关重要，它们共同建立了线程间的同步关系。


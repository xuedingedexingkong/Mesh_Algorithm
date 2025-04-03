注意：
1. 采用共享指针储存网格数据；
2. 所有Edge、Triangle共用一份Point；
3. 每个Triangle内的Edge是独立的，即使是对共享边；
4. 添加了自定义的Hash函数和()重载，以便于unordered_set(E)的键根据Edge是否储存了相同的Point进行判断；

Deleunay网格划分，随机点集结果：

![image](https://github.com/user-attachments/assets/e934f411-9a1e-48e0-aaff-463ccdffcf68)

均匀点集结果：

![image](https://github.com/user-attachments/assets/d765f14e-b29c-45f8-9e78-09699fa2e8f8)

非均匀点集结果：

![image](https://github.com/user-attachments/assets/054834b9-508a-4f3f-a146-0cf3fbf1956a)

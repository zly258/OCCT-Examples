# 架构设计 — 基于 AutoCAD 的 DBObject / Entity / Database / Table 概念

本文描述如何在本项目中采用与 AutoCAD 类似的数据模型与架构，便于后续实现对象持久化、图元管理、事务与插件扩展。

1. 核心概念映射
- DBObject: 抽象的持久化对象基类。拥有唯一 ID、元数据（图层、颜色、线型）与序列化接口。
- Entity: 几何图元的抽象（例如线、圆、样条），继承自 `DBObject` 并包含几何表示与绘制属性。
- Table: 保存同类对象的容器（类似 AutoCAD 的表格，如 `LayerTable`, `BlockTable`, `EntityTable`）。负责索引、查找与序列化集合。
- Database: 整个文档级别的数据持有者，包含多个 `Table`，支持事务、Undo/Redo 与持久化（读/写到文件）。

2. 交互与职责
- View/Viewport: 只负责渲染与用户交互，会通过 `Document`/`Database` 获取 `Entity` 的几何和显示属性。
- Commands: 通过命令模式修改 `Database`（例如创建实体、移动、删除），命令负责构建 undo/redo 信息。
- IO: `io/` 模块负责把 `Database` 序列化到文件（内部格式、DXF/STEP），以及从文件还原到 `Database`。

3. 重要设计要点
- 唯一标识: 每个 `DBObject` 使用全局唯一 ID（例如 UUID 或项目内部递增 ID 与版本），便于跨文件引用。
- 表（Table）应支持：按 ID 查找、按属性索引（按图层、类型）、遍历、批量操作。
- 事务模型: 在修改多对象时使用事务或命令批（Command Group），以保证原子性与可撤销性。
- 插件扩展: 插件通过 `PluginInterface` 可以注册新的 `Entity` 类型与序列化处理器。

4. 类草图（C++ 接口草案）
- `occt_autocad::db::DBObject` — 基类，提供 `id()`, `clone()`, `serialize()/deserialize()`。
- `occt_autocad::db::Entity : public DBObject` — 抽象绘图实体，提供 `draw()`, `boundingBox()` 等。
- `occt_autocad::db::Table<T>` — 模板化表容器，存储 `T : DBObject`。
- `occt_autocad::db::Database` — 持有多个 `Table` 实例，提供 `createEntity()`, `eraseEntity()`, `findById()` 等 API。

5. 示例用法
```cpp
// 创建文档并添加一个圆实体
Database db;
auto circle = db.createEntity<CircleEntity>(/*params*/);
circle->setLayer("0");
db.commit();
```

6. 后续工作项
- 细化 `Table` 索引策略（哈希表、B树或缓存层）。
- 设计 `DBObject` 二进制序列化格式（便于快速读写）。
- 实现命令事务与 Undo/Redo 集成。

如需我将上面的接口草案转为实际头文件（`include/occt_autocad/db/*.h`）与基础实现（`src/db/*.cpp`），我可以继续创建这些模板并添加简单单元测试。 

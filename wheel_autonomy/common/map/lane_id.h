#pragma once

#include <cstdint>  // uint32_t uint16_t uint8_t

namespace wheel_autonomy {
namespace common {
namespace map {

struct MeshId {
  // 高精度地图中一般使用Level13，可视化参考链接：https://oxidase.github.io/nds/#
  // https://justforfunok.atlassian.net/wiki/spaces/AUT/pages/1251540993/Tile
  uint32_t mesh_id;    // 全球唯一的ID，计算方式参考上述链接
  uint16_t region_id;  // 该Mesh所在区域代码
  uint16_t version;  // 记录版本，可用于以Mesh为单位的局部地图升级
};

struct LaneGroupId {
  MeshId mesh_id;             // 该lane group所在的Mesh的ID
  uint32_t lane_group_index;  // 一个Mesh中，lane_group_id是全局唯一的
};

struct LaneId {
  LaneGroupId lane_group_id;  // 该lane所在lane group的ID
  uint8_t lane_index;         // lane在lane group中的序号
};

}  // namespace map
}  // namespace common
}  // namespace wheel_autonomy
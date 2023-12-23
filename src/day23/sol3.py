from z3 import *

# 假设有一个图 G，节点集合为 V，边集合为 E
# 每个节点都有一个相应的权值

N, M = input().split(' ')
N = int(N)
M = int(M)

st, ed = input().split(' ')
st = int(st)
ed = int(ed)

V = {}
E = []

for i in range(1, N + 1):
  value = int(input())
  V[i] = value

for i in range(M):
  u, v = input().split(' ')
  E.append((int(u), int(v)))

# 创建一个 Z3 优化器实例
opt = Optimize()

# 为图中的每条边创建一个布尔变量
edge_vars = {e: Bool(f"edge_{e[0]}_{e[1]}") for e in E}

# 为图中的每个节点创建一个布尔变量，表示该节点是否在路径上
node_vars = {v: Bool(f"node_{v}") for v in V}
link_vars = {v: Bool(f"link_{v}") for v in V}

# 添加路径约束
for v in V:
  # print(f"node: {v}")
  # 每个节点（除了起点和终点）有一个入边和一个出边
  # in_edges = [edge_vars[(u, v)] for u, _ in E if ((u, v) in E)]
  in_edges = [edge_vars[(u, v)] for u in V if v != u and (u, v) in E]
  out_edges = [edge_vars[(v, w)] for w in V if v != w and (v, w) in E]
  # print(f"Add cons {v}: {in_edges} {out_edges}")

  opt.add(Implies(Not(node_vars[v]), Not(link_vars[v])))
  if v == st:
    opt.add(And(
      node_vars[v],
      Sum([If(e, 1, 0) for e in in_edges]) == 0,
      Sum([If(e, 1, 0) for e in out_edges]) == 1))
  elif v == ed:
    opt.add(And(
      node_vars[v],
      Sum([If(e, 1, 0) for e in in_edges]) == 1,
      Sum([If(e, 1, 0) for e in out_edges]) == 0))
  else:
    # 如果一个节点在路径上，它应该有一个入边和一个出边
    opt.add(Implies(node_vars[v], And(
      Sum([If(e, 1, 0) for e in in_edges]) == 1,
      Sum([If(e, 1, 0) for e in out_edges]) == 1)))
    # 如果一个节点不在路径上，它不应该有入边或出边
    opt.add(Implies(Not(node_vars[v]), And(
      Sum([If(e, 1, 0) for e in in_edges]) == 0,
      Sum([If(e, 1, 0) for e in out_edges]) == 0)))

opt.add(node_vars[st])
opt.add(link_vars[st])
for u, v in E:
  opt.add(Implies(And(link_vars[u], edge_vars[(u, v)]), link_vars[v]))

# 定义目标函数：路径上所有点的权值之和
path_weight_sum = Sum([If(node_vars[v], w, 0) for v, w in V.items()])

# 求解目标函数的最大值
opt.maximize(path_weight_sum)

# 求解问题
if opt.check() == sat:
    model = opt.model()
    # 输出结果：选择了哪些边和节点
    solution_edges = [(u, v) for (u, v), e in edge_vars.items() if model[e]]
    solution_nodes = [v for v, n in node_vars.items() if model[n]]
    solution_links = [v for v, n in link_vars.items() if model[n]]
    print("最长简单路径长度:", sum(map(lambda x: V[x], solution_nodes)))
    print("最长简单路径包含的边:", solution_edges)
    print("最长简单路径包含的节点:", solution_nodes)
    print("最长简单路径包含的节点:", solution_links)
else:
    print("没有找到解")
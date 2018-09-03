= 数理最適化サンプルプログラムを軽く解析して今後の応用に備える @ matchbou

== はじめに

大昔の大学受験参考書「チャート式」とか「解法のテクニック」みたいにオペレーションズリサーチの典型問題のパターン毎にサンプルプログラムをそろえて、実行例としてのサンプルデータの内容も含めて整理すれば、今後の業務応用前の予習になるかとトライしてみました。

== 組み合わせ最適化手法の典型問題列挙と整理

ありがたいことに@SaitoTsutomuさんが
https://qiita.com/SaitoTsutomu/items/0f6c1a4415d196e64314
にまとめられていますので、引用させていただきます。
というか、これなしには、私の中では、実務とOR教科書の例題が結びつきませんでした…orz。

//image[Table1][本章で取り扱うORの典型問題]

実行環境は、Windows 10 Pro, Python3.5（Anaconda）を前提とします。


== グラフ・ネットワーク問題

「グラフ」
地下鉄の路線図のように「点（ノード：路線図の駅）」とそれを結ぶ「辺（エッジ：路線図の線路）」からなるもの。
辺の方向性の有無で有向グラフと無向グラフに分類される。

//image[image1][有向グラフと無向グラフ]

また、点や辺に重みを付与する場合もある

//image[image2][重み付きグラフの例]

=== 最小全域木問題（＃１）

適切な辺を経由することで全ての点の間を移動できる閉路（輪）のないグラフ（木：@<img>{image3}）において、上右図2のように辺に重みがある場合に重みの和を最小にするもの。

//image[image3][様々な木]

==== 最小全域木問題の応用例

 * 最小コストでのLANケーブル配線（点はコンピュータ

==== 最小全域木問題のサンプルプログラムと用いているデータ構造の解説

//listnum[No1][最小全域木問題]{
###https://qiita.com/SaitoTsutomu/items/3130634debf561608bd9
from more_itertools import first, pairwise
# CSVデータ
import pandas as pd, networkx as nx, matplotlib.pyplot as plt
from ortoolpy import graph_from_table, networkx_draw
node = pd.read_csv('./node0.csv')
edge = pd.read_csv('./edge0.csv')

# グラフ描画
g = graph_from_table(node, edge)[0] #読み込んだデータからベースグラフを作成
t = nx.minimum_spanning_tree(g) #上記グラフ中の全域最小木を求める
pos = networkx_draw(g) #ortoolpyの関数でベースグラフを描画
nx.draw_networkx_edges(t, pos, width=3) #更に全域最小木を太字（width=3）でプロット
plt.show() #さあ表示！！
//}

//image[image4][#1最小全域木問題のグラフ]

==== データの説明

Node：上記グラフに於ける（頂）点データ。idは頂点の識別番号、x,yは便宜的表示用の座標軸上位置

//image[table2][最小全域木問題におけるノードデータ]

Edge：上記グラフに於ける辺データ。
表示されているnode1とnode2の組み合わせに辺がある。
Weightは辺重みを表す。Weight列がない場合は、nodeデータ座標軸のユークリッド距離を用いる。

//image[table3][最小全域木問題におけるエッジデータ]

=== 最大安定集合問題（最小頂点被覆問題, 補グラフの最大クリーク問題）（＃２）

最大安定集合問題：互いに直結する辺が存在しない頂点の集合で最大の個数をもつ集合を求める問題。
論理的に最大クリーク問題と等価であり、且つ最小頂点被覆問題とも等価である
最小頂点被覆問題：すべての辺のいずれか一端が接する頂点集合のうち個数が最小のものを求める問題。
最大クリーク問題：頂点同士を直結する辺が存在する頂点グループの内、頂点の個数が最大を求めるもの。
計算量クラスNP困難の為、ヒューリスティックに解を求めるアルゴリズムの探索は研究対象となっている。

//image[image5][最大安定集合問題のいくつかのパターン]

==== 最大安定集合問題の応用例

データ分析に於けるクラスタリング手法のひとつとして

==== 最大安定集合問題のサンプルプログラムと用いているデータ構造の解説

//listnum[No2][最大安定集合問題]{
import pandas as pd, networkx as nx, matplotlib.pyplot as plt
from ortoolpy import graph_from_table, networkx_draw, maximum_stable_set
tbn = pd.read_csv('./node0mac1.csv')
tbe = pd.read_csv('./edge0mac1.csv')
g = graph_from_table(tbn, tbe)[0]
t = maximum_stable_set(g)
pos = networkx_draw(g, node_color='white')
nx.draw_networkx_nodes(g, pos, nodelist=t[1])
plt.show()
print(t)
//}

//image[image6][最大安定集合問題のグラフ]

Node：上記グラフに於ける（頂）点データ。idは頂点の識別番号、x,yは便宜的な座標軸上の位置

//image[table4][最大安定集合問題におけるノードデータ]

表示されているnode1とnode2の組み合わせに辺がある。
辺の重みを表すWeightは自明であるが不要。

//image[table5][最大安定集合問題における辺データ]

==== 最小頂点被覆問題

//listnum[No3][最小頂点被覆問題のコード]{
import pandas as pd, networkx as nx, matplotlib.pyplot as plt
from ortoolpy import graph_from_table, networkx_draw, min_node_cover
tbn = pd.read_csv('./node0mac1.csv')
tbe = pd.read_csv('./edge0mac1.csv')
g = graph_from_table(tbn, tbe)[0]
t = min_node_cover(g)
pos = networkx_draw(g, node_color='white')
nx.draw_networkx_nodes(g, pos, nodelist=t)
plt.show()
print(t)
//}

//image[image7][最小頂点被覆問題のグラフ]

データは、最大集合安定問題と同じ。

==== 最大クリーク問題（TBW）
説明がない？確認願います。@matchbou

=== 最大カット問題 （＃３）

グラフ上の頂点をグループ分けするときにグループの分かれ目上にある辺の重み総和が最大となるグルーピングを求める問題。

//image[image8][最大カット問題の概念図]

==== 最大カット問題の応用例

画像の領域抽出（CT画像から臓器の領域のみくりぬく）。
配送担当領域の分割（辺の重みがその間を通る交通のコストと看做した場合など）

==== 最大カット問題のサンプルコードとデータ構造の解説

//listnum[No4][最大カット問題のサンプルコード]{
import pandas as pd, networkx as nx, matplotlib.pyplot as plt
from ortoolpy import graph_from_table, networkx_draw, maximum_cut
tbn = pd.read_csv('./node0mac1.csv')
tbe = pd.read_csv('./edge0mac1.csv')
g = graph_from_table(tbn, tbe)[0]
t = maximum_cut(g)
pos = networkx_draw(g, node_color='white')
nx.draw_networkx_nodes(g, pos, nodelist=t[1])
plt.show()
print(t)
//}

//image[table6][最大カット問題のノード]

//image[table7][最大カット問題の辺]

Node: 最小全域木問題のNodeデータと同じ。
Edge: 最小全域木問題のEdgeデータと同じ。node1,node2でどの辺かを示し、weightで重みを与える。

=== 最短路問題（＃４）

辺に重みのついたグラフで任意の頂点aから別の任意の頂点bへの最短経路（=通過する辺の重みが最小）

==== 最短経路問題の応用例

サプライチェーンにおける最短経路の探索

==== 最短経路問題のサンプルプログラムとデータ

//listnum[No5][最短経路問題のサンプルコード]{
import pandas as pd, networkx as nx, matplotlib.pyplot as plt
from ortoolpy import graph_from_table, networkx_draw, maximum_stable_set
tbn = pd.read_csv('./node0mac1.csv')
tbe = pd.read_csv('./edge0mac1.csv')
g = graph_from_table(tbn, tbe)[0]
route=nx.dijkstra_path(g, 5, 2, weight='weight')# node5と2の間の最短路を求める
print(route)
pos = networkx_draw(g, node_color='white')
nx.draw_networkx_nodes(g, pos, nodelist=route)
plt.show()
//}

//image[image9][最短経路問題のグラフ]

データの解説：最大カット問題と同じ。

=== 最大流問題（＃５）

単一の始点から単一の終点へのフローネットワークで最大となるフローを求める問題。

==== 最大流問題の応用例

サプライチェーンで、とある配送元から配送先に輸送できる最大量の探索など

==== 最大流問題のサンプルコード

//listnum[No6][最大流問題のサンプルコード]{
import pandas as pd, networkx as nx
import matplotlib.pyplot as plt
from ortoolpy import graph_from_table, networkx_draw
tbn = pd.read_csv('./node0mac1.csv')
tbe = pd.read_csv('./edge0.csv')
g = graph_from_table(tbn, tbe)[0]
t = nx.maximum_flow(g, 5, 2)
pos = networkx_draw(g)
nx.draw_networkx_edges(g, pos, width=3, edgelist
  =[(k1, k2) for k1, d in t[1].items() for k2, v in d.items() if v])
plt.show()
for i, d in t[1].items():
    for j, f in d.items():
        if f: print((i, j), f)
//}

//image[image10][最大流問題のグラフ]

//image[table8][最大流問題のノード]

//image[table9][最大流問題のエッジ]

Node:最大カット問題のデータと同じ

Edge:流量の上限制約であるcapacity変数を含む

=== 最小費用流問題（＃６）
最小費用流問題の説明抜けてる。

==== 最小費用流問題の応用



==== 最小費用流問題のサンプルコード
//listnum[No7][最小費用流問題のサンプルコード]{
import pandas as pd, networkx as nx, matplotlib.pyplot as plt
from ortoolpy import graph_from_table, networkx_draw
tbn = pd.read_csv('./node0mac2.csv')
tbe = pd.read_csv('./edge0.csv')
g = graph_from_table(tbn, tbe, directed=True)[0]
pos = networkx_draw(g)
result = nx.min_cost_flow(g)
nx.draw_networkx_edges(g, pos, width=3, edgelist
  =[(k1, k2) for k1, d in result.items() for k2, v in d.items() if v])
nx.draw_networkx_edge_labels(g, pos,
    edge_labels=dict([ ((k1, k2),v) for k1, d in result.items() for k2, v in d.items() if v])
                            )
plt.show()
//}

//image[image11][最小費用流問題のグラフ]

//image[table10][最小費用流問題のノード]

//image[table11][最小費用流問題のエッジ]

Node:各頂点の需要量がdemand列に表される

Edge:最大流問題と同じ。



== 経路問題
=== 運搬経路（配送最適化）問題（＃７）
=== 巡回セールスマン問題（＃８）
=== 中国人郵便配達問題（＃９）
== 集合被覆・分割問題
=== 集合被覆問題（＃１０） 
=== 集合分割問題（＃１１）
=== 組み合わせオークション問題（＃１２）
== スケジューリング問題
=== ジョブショップ問題（＃１３）
=== 勤務スケジューリング問題 （＃１４）

== 切り出し・詰め込み問題
=== ナップサック問題（＃１５）
=== ビンパッキング問題（＃１６）
=== ｎ次元詰め込み問題（＃１７）
== 配置問題
=== 施設配置問題（＃１８）
=== 容量制約なし施設配置問題（＃１９）
== 割り当て・マッチング問題
=== 二次割り当て問題（＃２０）
=== 一般化割り当て問題（＃２１）
=== 最大マッチング問題（＃２２）
=== 重みマッチング問題（＃２３）
==== 重みマッチング問題の応用例

研修医の配属問題、研究室への配属問題
ねるとん紅鯨団

==== 重みマッチング問題のサンプルプログラムとデータ

//listnum[code24][重みマッチング問題のサンプルプログラム]{
from ortoolpy import stable_matching
import numpy as np, pandas as pd, networkx as nx
import IPython.core.getipython
from IPython.display import HTML
from more_itertools import first, pairwise
  
def typical_optimization_impl(sel):
    return HTML("""\
<table>
  <td><a href="http://qiita.com/SaitoTsutomu/items/2ec5f7626054f4b4de63" target="_blank">安定マッチング問題</a></td>
  <td>StableMatching</td>
</tr>
</table>
""")
  
def StableMatching(df, male_label='male', female_label='female',
        pref_male_label='pref_male', pref_female_label='pref_female', **kwargs):
    """
    安定マッチング問題
    入力
        df: 選好のDataFrameもしくはCSVファイル名
        male_label: 男性の属性文字
        female_label: 女性の属性文字
        pref_male_label: 男性から見た順番の属性文字
        pref_female_label: 女性から見た順番の属性文字
    出力
        マッチングのDataFrame(男性優先)
    """
    df = graph_from_table(df, None, no_graph=True, **kwargs)[1]
    m = range(df[male_label].max()+1)
    f = range(df[female_label].max()+1)
    prefm = [[first(df[(df[male_label]==i)&(df[pref_male_label]==j)]
             [female_label],1e6) for j in f] for i in m]
    preff = [[first(df[(df[female_label]==i)&(df[pref_female_label]==j)]
             [male_label],1e6) for j in m] for i in f]
    t = stable_matching(prefm, preff)
    return pd.concat([df[(df[female_label]==i)&(df[male_label]==j)]
        for i,j in t.items()]).sort_values(male_label)
 
if __name__ == '__main__':
    ip = IPython.core.getipython.get_ipython()
    ip.register_magic_function(typical_optimization_impl,
        magic_kind='line', magic_name='typical_optimization')
     
print(stable_matching([[2,0,1],[2,1,0],[0,2,1]], [[0,1,2],[2,0,1],[2,1,0]]))

//}

=== 安定マッチング問題（＃２４）

2部グラフにおいては、各部に属する頂点群が相対する部の頂点群に対する嗜好順位を有する状況下で、マッチングを行う場合に、そのマッチングを崩して別のマッチングを組んだほうがその頂点にとりより高い嗜好順位とのマッチングにならない状態（個人合理性を満たす）を求める問題。

==== 安定マッチング問題の応用例

研修医の配属問題、研究室への配属問題
ねるとん紅鯨団

==== 安定マッチング問題のサンプルプログラムとデータ

== まとめ

早速倉庫の業務、顧客注文に応じて出荷用に棚から物を取ってくる作業時の動線短縮・合理化のお題がでたので巡回セールスマン辺りを深堀中です。サンプルではユークリッドの直線距離だけど、倉庫で隣の棚に行くには通路を回り込まないとってところです。
今後は、こういたカタログのExcel版を作れれば、Excelならなんとかという方々にも数理最適化が布教できるのではないかと思量。

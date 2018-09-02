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

適切な辺を経由することで全ての点の間を移動できる閉路（輪）のないグラフ（木：@img{}）において、上右図2のように辺に重みがある場合に重みの和を最小にするもの。

//image[image3][様々な木]

==== この問題の応用例

 * 最小コストでのLANケーブル配線（点はコンピュータ

==== サンプルプログラムと用いているデータ構造の解説

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


=== 最大カット問題 （＃３）
=== 最短路問題（＃４）
=== 最大流問題（＃５）
=== 最小費用流問題（＃６）
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
=== 安定マッチング問題（＃２４）
== まとめ


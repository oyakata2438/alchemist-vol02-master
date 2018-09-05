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

//image[image2][重み付きグラフの例][scale=0.8]

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

//image[image4][#1最小全域木問題のグラフ][scale=0.5]

==== データの説明

Node：上記グラフに於ける（頂）点データ。idは頂点の識別番号、x,yは便宜的表示用の座標軸上位置

//image[table2][最小全域木問題におけるノードデータ][scale=0.75]

Edge：上記グラフに於ける辺データ。
表示されているnode1とnode2の組み合わせに辺がある。
Weightは辺重みを表す。Weight列がない場合は、nodeデータ座標軸のユークリッド距離を用いる。

//image[table3][最小全域木問題におけるエッジデータ][scale=0.75]

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

//image[image6][最大安定集合問題のグラフ][scale=0.5]

Node：上記グラフに於ける（頂）点データ。idは頂点の識別番号、x,yは便宜的な座標軸上の位置

//image[table4][最大安定集合問題におけるノードデータ][scale=0.75]

表示されているnode1とnode2の組み合わせに辺がある。
辺の重みを表すWeightは自明であるが不要。

//image[table5][最大安定集合問題における辺データ][scale=0.75]

==== 最小頂点被覆問題

//listnum[No2-2][最小頂点被覆問題のコード]{
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

//image[image7][最小頂点被覆問題のグラフ][scale=0.5]

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

//listnum[No3][最大カット問題のサンプルコード]{
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

//image[table6][最大カット問題のノード][scale=0.75]

//image[table7][最大カット問題の辺][scale=0.75]

Node: 最小全域木問題のNodeデータと同じ。

Edge: 最小全域木問題のEdgeデータと同じ。node1,node2でどの辺かを示し、weightで重みを与える。

=== 最短路問題（＃４）

辺に重みのついたグラフで任意の頂点aから別の任意の頂点bへの最短経路（=通過する辺の重みが最小）

==== 最短経路問題の応用例

サプライチェーンにおける最短経路の探索

==== 最短経路問題のサンプルプログラムとデータ

//listnum[No4][最短経路問題のサンプルコード]{
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

//image[image9][最短経路問題のグラフ][scale=0.5]

データの解説：最大カット問題と同じ。

=== 最大流問題（＃５）

単一の始点から単一の終点へのフローネットワークで最大となるフローを求める問題。

==== 最大流問題の応用例

サプライチェーンで、とある配送元から配送先に輸送できる最大量の探索など

==== 最大流問題のサンプルコード

//listnum[No5][最大流問題のサンプルコード]{
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

//image[image10][最大流問題のグラフ][scale=0.5]

//image[table8][最大流問題のノード][scale=0.75]

//image[table9][最大流問題のエッジ][scale=0.75]

Node:最大カット問題のデータと同じ

Edge:流量の上限制約であるcapacity変数を含む

=== 最小費用流問題（＃６）
決まった量をネットワーク上で始点から終点まで流す際にかかる費用（コスト）を最小にしようという問題

==== 最小費用流問題の応用
商品配送網でのコスト削減施策の検討等。


==== 最小費用流問題のサンプルコード
//listnum[No6][最小費用流問題のサンプルコード]{
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

//image[image11][最小費用流問題のグラフ][scale=0.5]

//image[table10][最小費用流問題のノード][scale=0.75]

//image[table11][最小費用流問題のエッジ][scale=0.75]

Node:各頂点の需要量がdemand列に表される

Edge:最大流問題と同じ。



== 経路問題

経路の最適化を行うための問題。（少し追記してほしいかなー）

=== 運搬経路（配送最適化）問題[Vehcle Routing Problem]（＃７）
複数のサービス車（Vehicle）がスタート地点から需要のある地点の巡回を行いゴール地点へ行く。全ての需要を満たし、総経路コストを最小化することを考える問題
==== 運搬経路問題の応用例
説明どおりの配送網に於ける複数台のトラックへの配送物割り当ての他、複数人が働く倉庫での資材取り出しに於ける作業員への振り分け等。
運搬経路最適化

==== 運搬経路問題のサンプルコードとデータ

//listnum[No7][運搬経路問題のサンプルコード]{
import pandas as pd, networkx as nx
import matplotlib.pyplot as plt
from ortoolpy import vrp, graph_from_table, networkx_draw
tbn = pd.read_csv('./node1.csv')
tbe = pd.read_csv('./edge1.csv')
g = graph_from_table(tbn, tbe)[0].to_directed()
networkx_draw(g)
plt.show()
nv, capa = 2, 3 # 車両数、車両容量
print(vrp(g, nv, capa))
//}

//image[image12][運搬経路問題のグラフ][scale=0.5]

//image[table12][運搬経路問題のノード][scale=0.75]

//image[table13][運搬経路問題のエッジ][scale=0.75]

Node:最小費用流問題と異なり、発地の需要がマイナスとなっておらずゼロである。

Edge:配送ルート毎のコストを保持している。







=== 巡回セールスマン問題（＃８）

巡回セールスマン問題（英: traveling salesman problem、TSP）は、都市の集合と各2都市間の移動コスト（たとえば距離）が与えられたとき、全ての都市をちょうど一度ずつ巡り出発地に戻る巡回路の総移動コストが最小のものを求める（セールスマンが所定の複数の都市を1回だけ巡回する場合の最短経路を求める）組合せ最適化問題。

==== 巡回セールスマン問題の応用例

まさにサプライチェーンの業務効率化に資する問題そのもの

==== 巡回セールスマン問題のサンプルプログラムとデータ
NP困難な問題の解法として種々のヒューリスティックな方法がありますが、今回は私的に耳に新しい蟻コロニー最適化（ACO）による解法のプログラムをみてみます。蟻が巣に物資を運ぶ際の最適経路選定に用いている方法の援用のようです。

//listnum[no8][巡回セールスマン問題のサンプルプログラム]{
#巡回セールスマン問題を蟻コロニー最適化と遺伝的アルゴリズムで解いてみる[Python]
#http://tony-mooori.blogspot.com/2016/02/tsppython.html
#coding:utf-8
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from scipy.spatial import distance as dis
"""
参考URL
[1] 蟻コロニー最適化 - Wikipedia https://ja.wikipedia.org/wiki/蟻コロニー最適化
[2] 任意の確率密度分布に従う乱数の生成（von Neumannの棄却法） | Pacocat's Life http://pacocat.com/?p=596
"""
class TSP:
    def __init__(self,path=None,alpha = 1.0,beta = 1.0,Q = 1.0,vanish_ratio = 0.95):
        """ 初期化を行う関数 """
        self.alpha = alpha                    # フェロモンの優先度
        self.beta = beta                    # ヒューリスティック情報(距離)の優先度
        self.Q = Q                            # フェロモン変化量の係数
        self.vanish_ratio = vanish_ratio    # 蒸発率
        if path is not None:
            self.set_loc(np.array(pd.read_csv(path)))
    
    def set_loc(self,locations):
        """ 位置座標を設定する関数 """
        self.loc = locations                            # x,y座標
        self.n_data = len(self.loc)                        # データ数
        self.dist = dis.squareform(dis.pdist(self.loc))    # 距離の表を作成
        self.weight = np.random.random_sample((self.n_data,self.n_data))  # フェロモンの量
        self.result = np.arange(self.n_data)            # もっともよかった順序を保存する
        print("x,y座標")
        print(self.loc)
        #print(self.n_data)
        print("距離の表")
        print(self.dist)
        #print(self.weight)
        #print(self.result)
        
    def cost(self,order):
        """ 指定された順序のコスト計算関数 """
        n_order = len(order)
        return np.sum( [ self.dist[order[i],order[(i+1)%n_order]] for i in np.arange(n_order) ] )
    
    def plot(self,order=None):
        """ 指定された順序でプロットする関数 """
        if order is None:
            plt.plot(self.loc[:,0],self.loc[:,1])
        else:
            plt.plot(self.loc[order,0],self.loc[order,1])
        plt.show()
    
    def solve(self,n_agent=1000):
        """ 巡回セールスマン問題を蟻コロニー最適化で解く """
        
        order = np.zeros(self.n_data,np.int)         # 巡回経路
        delta = np.zeros((self.n_data,self.n_data))    #フェロモン変化量
        
        for k in range(n_agent):
            city = np.arange(self.n_data)
            now_city = np.random.randint(self.n_data)    # 現在居る都市番号
            
            city = city[ city != now_city ]
            order[0] = now_city
            
            for j in range(1,self.n_data):
                upper = np.power(self.weight[now_city,city],self.alpha)*np.power(self.dist[now_city,city],-self.beta)
                
                evaluation = upper / np.sum(upper)                # 評価関数
                percentage = evaluation / np.sum(evaluation)    # 移動確率
                index = self.random_index(percentage)            # 移動先の要素番号取得
                
                # 状態の更新
                now_city = city[ index ]
                city = city[ city != now_city ]
                order[j] = now_city
            
            L = self.cost(order) # 経路のコストを計算
            
            # フェロモンの変化量を計算
            delta[:,:] = 0.0
            c = self.Q / L
            for j in range(self.n_data-1):
                delta[order[j],order[j+1]] = c
                delta[order[j+1],order[j]] = c
            
            # フェロモン更新
            self.weight *= self.vanish_ratio 
            self.weight += delta
            
            # 今までで最も良ければ結果を更新
            if self.cost(self.result) > L:
                self.result = order.copy()
            
            # デバッグ用
            print("Agent ... %d , Cost ... %lf" % (k,self.cost(self.result)))
        
        return self.result

    
    def random_index(self,percentage):
        """ 任意の確率分布に従って乱数を生成する関数 """
        n_percentage = len(percentage)
        
        while True:
            index = np.random.randint(n_percentage)
            y = np.random.random()
            if y < percentage[index]:
                return index
      
if __name__=="__main__":
    tsp = TSP(path="node0mac3-only-xy-figure.csv")
    tsp.solve(n_agent=1000)        # 1000匹の蟻を歩かせる
    tsp.plot(tsp.result)        # 計算後
    plt.show()
//}

出力
//listnum[no8-out][巡回セールスマン問題の出力]{
x,y座標
[[ 5  8]
 [10  5]
 [ 7  0]
 [ 2  2]
 [ 0  5]]
距離の表
[[  0.           5.83095189   8.24621125   6.70820393   5.83095189]
 [  5.83095189   0.           5.83095189   8.54400375  10.        ]
 [  8.24621125   5.83095189   0.           5.38516481   8.60232527]
 [  6.70820393   8.54400375   5.38516481   0.           3.60555128]
 [  5.83095189  10.           8.60232527   3.60555128   0.        ]]
Agent ... 0 , Cost ... 26.483572
Agent ... 1 , Cost ... 26.483572
Agent ... 2 , Cost ... 26.483572
Agent ... 3 , Cost ... 26.483572
…
Agent ... 995 , Cost ... 26.483572
Agent ... 996 , Cost ... 26.483572
Agent ... 997 , Cost ... 26.483572
Agent ... 998 , Cost ... 26.483572
Agent ... 999 , Cost ... 26.483572
//}

//image[image13][巡回セールスマン問題の出力][scale=0.5]

//image[table14][巡回セールスマン問題のノード][scale=0.75]

Nodeデータのみです。列名、行名無です。左からx座標とy座標

==== 巡回セールスマン問題の感想
本件では、入力データのxy座標からユークリッド距離を生成しています。
地点間の距離を任意に投入したい場合は、プログラム中の「距離の表を作成」のところを改変して、地点間距離データを投入することで対応可能と思量します。そうすれば、実務上は必ずしもユークリッド距離に拠らない、輸送料金での最適化なども可能と思量します。


=== 中国人郵便配達問題（＃９）

全ての頂点間をいずれかの辺を通って（必ずしも直結する辺が存在するとは限らない、また辺には重みがある）移動できるときに全ての辺を通り重みの合計が最小となる通り方を求める問題。

==== 中国人郵便配達問題の応用例

まさに郵便配達に類するサプライチェーン問題にどうぞ

==== 中国人郵便配達問題のサンプルコード

//listnum[No9][中国人郵便配達問題のサンプルコード]{
import pandas as pd, networkx as nx, matplotlib.pyplot as plt
from ortoolpy import chinese_postman, graph_from_table, networkx_draw
tbn = pd.read_csv('./node0mac1.csv')
tbe = pd.read_csv('./edge0mac2.csv')
g = graph_from_table(tbn, tbe, multi=True)[0]
networkx_draw(g)
plt.show()
print("重み合計とルート順表示")
print(chinese_postman(g))
//}

//image[image14][中国人郵便配達問題の出力]

重み合計とルート順表示
//listnum[No9-out][出力:重み合計とルート順表示]{
(36, [(0, 4), (4, 5), (5, 4), (4, 3), (3, 2), (2, 3), (3, 0), (0, 5), (5, 1), (1, 2), (2, 0), (0, 1), (1, 0)])
//}

//image[table15][中国人郵便配達問題の問題のノード][scale=0.75]

//image[table16][中国人郵便配達問題の問題のエッジ][scale=0.75]

ノード間の重み（Weight)情報は、ノードテーブルの方に格納される。


== 集合被覆・分割問題
=== 集合被覆問題（＃１０） 

集合の部分集合毎にコストが与えられているときに最小コストで集合の全要素をカバーできるような部分集合の組み合わせを選択する。（複数の部分集合でカバーされている要素があっても構わない）

==== 集合被覆問題の応用例
乗務員スケーリング問題等。

==== 集合被覆問題のサンプルプログラムとデータ
//listnum[No10-1][集合被覆問題のサンプルコード1]{
def set_cover(universe, subsets):
    """Find a family of subsets that covers the universal set"""
    """http://www.martinbroadhurst.com/greedy-set-cover-in-python.html"""
    elements = set(e for s in subsets for e in s)
    # Check the subsets cover the universe
    if elements != universe:
        return None
    covered = set()
    cover = []
    # Greedily add the subsets with the most uncovered points
    while covered != elements:
        subset = max(subsets, key=lambda s: len(s - covered))
        cover.append(subset)
        covered |= subset
 
    return cover
 
def main():
    universe = set(range(1, 11))
    subsets = [set([1, 2, 3, 8, 9, 10]),
        set([1, 2, 3, 4, 5]),
        set([4, 5, 7]),
        set([5, 6, 7]),
        set([6, 7, 8, 9, 10])]
    cover = set_cover(universe, subsets)
    print("whole universe")
    print(universe)
    print("given subsets")
    print(subsets)
    print("cover:chosen subsets")
    print(cover)

if __name__ == '__main__':
    main()
//}

//listnum[No10-2][集合被覆問題の出力1]{
出力：上から全集合、被覆する為に用いる部分集合、解答として選ばれた部分集合群
whole universe
{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
given subsets
[{1, 2, 3, 8, 9, 10}, {1, 2, 3, 4, 5}, {4, 5, 7}, {5, 6, 7}, {8, 9, 10, 6, 7}]
cover:chosen subsets
[{1, 2, 3, 8, 9, 10}, {4, 5, 7}, {5, 6, 7}]
//}



=== 集合分割問題（＃１１）
=== 組み合わせオークション問題（＃１２）⇒組み合わせオークションは割愛しようかと考えています。
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
